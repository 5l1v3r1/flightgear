// xmlauto.cxx - a more flexible, generic way to build autopilots
//
// Written by Curtis Olson, started January 2004.
//
// Copyright (C) 2004  Curtis L. Olson  - curt@flightgear.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// $Id$


#include <simgear/structure/exception.hxx>
#include <simgear/misc/sg_path.hxx>

#include <Main/fg_props.hxx>
#include <Main/globals.hxx>

#include "xmlauto.hxx"


FGPIDController::FGPIDController( SGPropertyNode *node ):
    debug( false ),
    y_n( 0.0 ),
    r_n( 0.0 ),
    Kp( 0.0 ),
    alpha( 0.1 ),
    beta( 1.0 ),
    gamma( 0.0 ),
    Ti( 0.0 ),
    Td( 0.0 ),
    u_min( 0.0 ),
    u_max( 0.0 ),
    ep_n_1( 0.0 ),
    edf_n_1( 0.0 ),
    edf_n_2( 0.0 ),
    u_n_1( 0.0 )
{
    int i;
    for ( i = 0; i < node->nChildren(); ++i ) {
        SGPropertyNode *child = node->getChild(i);
        string cname = child->getName();
        string cval = child->getStringValue();
        if ( cname == "name" ) {
            name = cval;
        } else if ( cname == "debug" ) {
            debug = child->getBoolValue();
        } else if ( cname == "enable" ) {
            // cout << "parsing enable" << endl;
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                // cout << "prop = " << prop->getStringValue() << endl;
                enable_prop = fgGetNode( prop->getStringValue(), true );
            } else {
                // cout << "no prop child" << endl;
            }
            SGPropertyNode *val = child->getChild( "value" );
            if ( val != NULL ) {
                enable_value = val->getStringValue();
            }
        } else if ( cname == "input" ) {
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                input_prop = fgGetNode( prop->getStringValue(), true );
            }
        } else if ( cname == "reference" ) {
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                r_n_prop = fgGetNode( prop->getStringValue(), true );
            } else {
                prop = child->getChild( "value" );
                if ( prop != NULL ) {
                    r_n = prop->getDoubleValue();
                }
            }
        } else if ( cname == "output" ) {
            int i = 0;
            SGPropertyNode *prop;
            while ( (prop = child->getChild("prop", i)) != NULL ) {
                SGPropertyNode *tmp = fgGetNode( prop->getStringValue(), true );
                output_list.push_back( tmp );
                i++;
            }
        } else if ( cname == "config" ) {
            SGPropertyNode *prop;

            prop = child->getChild( "Kp" );
            if ( prop != NULL ) {
                Kp = prop->getDoubleValue();
            }

            prop = child->getChild( "beta" );
            if ( prop != NULL ) {
                beta = prop->getDoubleValue();
            }

            prop = child->getChild( "alpha" );
            if ( prop != NULL ) {
                alpha = prop->getDoubleValue();
            }

            prop = child->getChild( "gamma" );
            if ( prop != NULL ) {
                gamma = prop->getDoubleValue();
            }

            prop = child->getChild( "Ti" );
            if ( prop != NULL ) {
                Ti = prop->getDoubleValue();
            }

            prop = child->getChild( "Td" );
            if ( prop != NULL ) {
                Td = prop->getDoubleValue();
            }

            prop = child->getChild( "u_min" );
            if ( prop != NULL ) {
                u_min = prop->getDoubleValue();
            }

            prop = child->getChild( "u_max" );
            if ( prop != NULL ) {
                u_max = prop->getDoubleValue();
            }
        } else {
            SG_LOG( SG_AUTOPILOT, SG_WARN, "Error in autopilot config logic" );
            if ( name.length() ) {
                SG_LOG( SG_AUTOPILOT, SG_WARN, "Section = " << name );
            }
        }
    }   
}


/*
 * Roy Vegard Ovesen:
 *
 * Ok! Here is the PID controller algorithm that I would like to see
 * implemented:
 *
 *   delta_u_n = Kp * [ (ep_n - ep_n-1) + ((Ts/Ti)*e_n)
 *               + (Td/Ts)*(edf_n - 2*edf_n-1 + edf_n-2) ]
 *
 *   u_n = u_n-1 + delta_u_n
 *
 * where:
 *
 * delta_u : The incremental output
 * Kp      : Proportional gain
 * ep      : Proportional error with reference weighing
 *           ep = beta * r - y
 *           where:
 *           beta : Weighing factor
 *           r    : Reference (setpoint)
 *           y    : Process value, measured
 * e       : Error
 *           e = r - y
 * Ts      : Sampling interval
 * Ti      : Integrator time
 * Td      : Derivator time
 * edf     : Derivate error with reference weighing and filtering
 *           edf_n = edf_n-1 / ((Ts/Tf) + 1) + ed_n * (Ts/Tf) / ((Ts/Tf) + 1)
 *           where:
 *           Tf : Filter time
 *           Tf = alpha * Td , where alpha usually is set to 0.1
 *           ed : Unfiltered derivate error with reference weighing
 *             ed = gamma * r - y
 *             where:
 *             gamma : Weighing factor
 * 
 * u       : absolute output
 * 
 * Index n means the n'th value.
 * 
 * 
 * Inputs:
 * enabled ,
 * y_n , r_n , beta=1 , gamma=0 , alpha=0.1 ,
 * Kp , Ti , Td , Ts (is the sampling time available?)
 * u_min , u_max
 * 
 * Output:
 * u_n
 */

void FGPIDController::update( double dt ) {
    double ep_n;         // proportional error with reference weighing
    double e_n;          // error
    double ed_n;         // derivative error
    double edf_n;        // derivative error filter
    double Tf;           // filter time
    double delta_u_n;    // incremental output
    double u_n;          // absolute output
    double Ts = dt;      // Sampling interval (sec)

    if ( Ts <= 0.0 ) {
        // do nothing if time step is not positive (i.e. no time has
        // elapsed)
        return;
    }

    if (enable_prop != NULL && enable_prop->getStringValue() == enable_value) {
        enabled = true;
    } else {
        enabled = false;
    }

    if ( enabled ) {
        if ( debug ) cout << "Updating " << name << endl;

        double y_n = 0.0;
        if ( input_prop != NULL ) {
            y_n = input_prop->getDoubleValue();
        }

        double r_n = 0.0;
        if ( r_n_prop != NULL ) {
            r_n = r_n_prop->getDoubleValue();
        } else {
            r_n = r_n_value;
        }
                      
        if ( debug ) cout << "  input = " << y_n << " ref = " << r_n << endl;

        // Calculates proportional error:
        ep_n = beta * r_n - y_n;
        if ( debug ) cout << "  ep_n = " << ep_n;
        if ( debug ) cout << "  ep_n_1 = " << ep_n_1;

        // Calculates error:
        e_n = r_n - y_n;
        if ( debug ) cout << " e_n = " << e_n;

        // Calculates derivate error:
        ed_n = gamma * r_n - y_n;
        if ( debug ) cout << " ed_n = " << ed_n;

        // Calculates filter time:
        Tf = alpha * Td;
        if ( debug ) cout << " Tf = " << Tf;

        // Filters the derivate error:
        edf_n = edf_n_1 / (Ts/Tf + 1)
            + ed_n * (Ts/Tf) / (Ts/Tf + 1);
        if ( debug ) cout << " edf_n = " << edf_n;

        // Calculates the incremental output:
        delta_u_n = Kp * ( (ep_n - ep_n_1)
                           + ((Ts/Ti) * e_n)
                           + ((Td/Ts) * (edf_n - 2*edf_n_1 + edf_n_2)) );
        if ( debug ) cout << " delta_u_n = " << delta_u_n << endl;

        // Integrator anti-windup logic:
        if ( delta_u_n > (u_max - u_n_1) ) {
            delta_u_n = 0;
        } else if ( delta_u_n < (u_min - u_n_1) ) {
            delta_u_n = 0;
        }

        // Calculates absolute output:
        u_n = u_n_1 + delta_u_n;
        if ( debug ) cout << "  output = " << u_n << endl;

        // Updates indexed values;
        u_n_1   = u_n;
        ep_n_1  = ep_n;
        edf_n_2 = edf_n_1;
        edf_n_1 = edf_n;

        unsigned int i;
        for ( i = 0; i < output_list.size(); ++i ) {
            output_list[i]->setDoubleValue( u_n );
        }
    } else if ( !enabled ) {
        u_n   = 0.0;
        ep_n  = 0.0;
        edf_n = 0.0;
        // Updates indexed values;
        u_n_1   = u_n;
        ep_n_1  = ep_n;
        edf_n_2 = edf_n_1;
        edf_n_1 = edf_n;
    }
}


FGPISimpleController::FGPISimpleController( SGPropertyNode *node ):
    proportional( false ),
    Kp( 0.0 ),
    offset_prop( NULL ),
    offset_value( 0.0 ),
    integral( false ),
    Ki( 0.0 ),
    int_sum( 0.0 ),
    clamp( false ),
    debug( false ),
    y_n( 0.0 ),
    r_n( 0.0 ),
    u_min( 0.0 ),
    u_max( 0.0 )
{
    int i;
    for ( i = 0; i < node->nChildren(); ++i ) {
        SGPropertyNode *child = node->getChild(i);
        string cname = child->getName();
        string cval = child->getStringValue();
        if ( cname == "name" ) {
            name = cval;
        } else if ( cname == "debug" ) {
            debug = child->getBoolValue();
        } else if ( cname == "enable" ) {
            // cout << "parsing enable" << endl;
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                // cout << "prop = " << prop->getStringValue() << endl;
                enable_prop = fgGetNode( prop->getStringValue(), true );
            } else {
                // cout << "no prop child" << endl;
            }
            SGPropertyNode *val = child->getChild( "value" );
            if ( val != NULL ) {
                enable_value = val->getStringValue();
            }
        } else if ( cname == "input" ) {
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                input_prop = fgGetNode( prop->getStringValue(), true );
            }
        } else if ( cname == "reference" ) {
            SGPropertyNode *prop = child->getChild( "prop" );
            if ( prop != NULL ) {
                r_n_prop = fgGetNode( prop->getStringValue(), true );
            } else {
                prop = child->getChild( "value" );
                if ( prop != NULL ) {
                    r_n = prop->getDoubleValue();
                }
            }
        } else if ( cname == "output" ) {
            int i = 0;
            SGPropertyNode *prop;
            while ( (prop = child->getChild("prop", i)) != NULL ) {
                SGPropertyNode *tmp = fgGetNode( prop->getStringValue(), true );
                output_list.push_back( tmp );
                i++;
            }
        } else if ( cname == "config" ) {
            SGPropertyNode *prop;

            prop = child->getChild( "Kp" );
            if ( prop != NULL ) {
                Kp = prop->getDoubleValue();
                proportional = true;
            }

            prop = child->getChild( "Ki" );
            if ( prop != NULL ) {
                Ki = prop->getDoubleValue();
                integral = true;
            }

            prop = child->getChild( "u_min" );
            if ( prop != NULL ) {
                u_min = prop->getDoubleValue();
                clamp = true;
            }

            prop = child->getChild( "u_max" );
            if ( prop != NULL ) {
                u_max = prop->getDoubleValue();
                clamp = true;
            }
        } else {
            SG_LOG( SG_AUTOPILOT, SG_WARN, "Error in autopilot config logic" );
            if ( name.length() ) {
                SG_LOG( SG_AUTOPILOT, SG_WARN, "Section = " << name );
            }
        }
    }   
}


void FGPISimpleController::update( double dt ) {
    if (enable_prop != NULL && enable_prop->getStringValue() == enable_value) {
        if ( !enabled ) {
            // we have just been enabled, zero out int_sum
            int_sum = 0.0;
        }
        enabled = true;
    } else {
        enabled = false;
    }

    if ( enabled ) {
        if ( debug ) cout << "Updating " << name << endl;
        double input = 0.0;
        if ( input_prop != NULL ) {
            input = input_prop->getDoubleValue();
        }

        double r_n = 0.0;
        if ( r_n_prop != NULL ) {
            r_n = r_n_prop->getDoubleValue();
        } else {
            r_n = r_n_value;
        }
                      
        double error = r_n - input;
        if ( debug ) cout << "input = " << input
                          << " reference = " << r_n
                          << " error = " << error
                          << endl;

        double prop_comp = 0.0;
        double offset = 0.0;
        if ( offset_prop != NULL ) {
            offset = offset_prop->getDoubleValue();
            if ( debug ) cout << "offset = " << offset << endl;
        } else {
            offset = offset_value;
        }

        if ( proportional ) {
            prop_comp = error * Kp + offset;
        }

        if ( integral ) {
            int_sum += error * Ki * dt;
        } else {
            int_sum = 0.0;
        }

        if ( debug ) cout << "prop_comp = " << prop_comp
                          << " int_sum = " << int_sum << endl;

        double output = prop_comp + int_sum;

        if ( clamp ) {
            if ( output < u_min ) {
                output = u_min;
            }
            if ( output > u_max ) {
                output = u_max;
            }
        }
        if ( debug ) cout << "output = " << output << endl;

        unsigned int i;
        for ( i = 0; i < output_list.size(); ++i ) {
            output_list[i]->setDoubleValue( output );
        }
    }
}


FGXMLAutopilot::FGXMLAutopilot() {
}


FGXMLAutopilot::~FGXMLAutopilot() {
}

 
void FGXMLAutopilot::init() {
    config_props = fgGetNode( "/autopilot/new-config", true );

    SGPropertyNode *path_n = fgGetNode("/sim/systems/autopilot/path");

    if ( path_n ) {
        SGPath config( globals->get_fg_root() );
        config.append( path_n->getStringValue() );

        SG_LOG( SG_ALL, SG_INFO, "Reading autopilot configuration from "
                << config.str() );
        try {
            readProperties( config.str(), config_props );

            if ( ! build() ) {
                SG_LOG( SG_ALL, SG_ALERT,
                        "Detected an internal inconsistancy in the autopilot");
                SG_LOG( SG_ALL, SG_ALERT,
                        " configuration.  See earlier errors for" );
                SG_LOG( SG_ALL, SG_ALERT,
                        " details.");
                exit(-1);
            }        
        } catch (const sg_exception& exc) {
            SG_LOG( SG_ALL, SG_ALERT, "Failed to load autopilot configuration: "
                    << config.str() );
        }

    } else {
        SG_LOG( SG_ALL, SG_WARN,
                "No autopilot configuration specified for this model!");
    }
}


void FGXMLAutopilot::reinit() {
    components.clear();
    init();
    build();
}


void FGXMLAutopilot::bind() {
}

void FGXMLAutopilot::unbind() {
}

bool FGXMLAutopilot::build() {
    SGPropertyNode *node;
    int i;

    int count = config_props->nChildren();
    for ( i = 0; i < count; ++i ) {
        node = config_props->getChild(i);
        string name = node->getName();
        // cout << name << endl;
        if ( name == "pid-controller" ) {
            FGXMLAutoComponent *c = new FGPIDController( node );
            components.push_back( c );
        } else if ( name == "pi-simple-controller" ) {
            FGXMLAutoComponent *c = new FGPISimpleController( node );
            components.push_back( c );
        } else {
            SG_LOG( SG_ALL, SG_ALERT, "Unknown top level section: " 
                    << name );
            return false;
        }
    }

    return true;
}


/*
 * Update helper values
 */
static void update_helper( double dt ) {
    // Estimate speed in 5,10 seconds
    static SGPropertyNode *vel = fgGetNode( "/velocities/airspeed-kt", true );
    static SGPropertyNode *lookahead5
        = fgGetNode( "/autopilot/internal/lookahead-5-sec-airspeed-kt", true );
    static SGPropertyNode *lookahead10
        = fgGetNode( "/autopilot/internal/lookahead-10-sec-airspeed-kt", true );

    static double average = 0.0; // average/filtered prediction
    static double v_last = 0.0;  // last velocity

    double v = vel->getDoubleValue();
    double a = 0.0;
    if ( dt > 0.0 ) {
        a = (v - v_last) / dt;

        if ( dt < 1.0 ) {
            average = (1.0 - dt) * average + dt * a;
        } else {
            average = a;
        }

        lookahead5->setDoubleValue( v + average * 5.0 );
        lookahead10->setDoubleValue( v + average * 10.0 );
        v_last = v;
    }

    // Calculate heading bug error normalized to +/- 180.0 (based on
    // DG indicated heading)
    static SGPropertyNode *bug
        = fgGetNode( "/autopilot/settings/heading-bug-deg", true );
    static SGPropertyNode *ind_hdg
        = fgGetNode( "/instrumentation/heading-indicator/indicated-heading-deg",
                     true );
    static SGPropertyNode *ind_bug_error
        = fgGetNode( "/autopilot/internal/heading-bug-error-deg", true );

    double diff = bug->getDoubleValue() - ind_hdg->getDoubleValue();
    if ( diff < -180.0 ) { diff += 360.0; }
    if ( diff > 180.0 ) { diff -= 360.0; }
    ind_bug_error->setDoubleValue( diff );

    // Calculate heading bug error normalized to +/- 180.0 (based on
    // actual/nodrift magnetic-heading, i.e. a DG slaved to magnetic
    // compass.)
    static SGPropertyNode *mag_hdg
        = fgGetNode( "/orientation/heading-magnetic-deg", true );
    static SGPropertyNode *fdm_bug_error
        = fgGetNode( "/autopilot/internal/fdm-heading-bug-error-deg", true );

    diff = bug->getDoubleValue() - mag_hdg->getDoubleValue();
    if ( diff < -180.0 ) { diff += 360.0; }
    if ( diff > 180.0 ) { diff -= 360.0; }
    fdm_bug_error->setDoubleValue( diff );

    // Calculate true heading error normalized to +/- 180.0
    static SGPropertyNode *target_true
        = fgGetNode( "/autopilot/settings/true-heading-deg", true );
    static SGPropertyNode *true_hdg
        = fgGetNode( "/orientation/heading-deg", true );
    static SGPropertyNode *true_error
        = fgGetNode( "/autopilot/internal/true-heading-error-deg", true );

    diff = target_true->getDoubleValue() - true_hdg->getDoubleValue();
    if ( diff < -180.0 ) { diff += 360.0; }
    if ( diff > 180.0 ) { diff -= 360.0; }
    true_error->setDoubleValue( diff );

    // Calculate nav1 target heading error normalized to +/- 180.0
    static SGPropertyNode *target_nav1
        = fgGetNode( "/radios/nav[0]/radials/target-auto-hdg-deg", true );
    static SGPropertyNode *true_nav1
        = fgGetNode( "/autopilot/internal/nav1-heading-error-deg", true );

    diff = target_nav1->getDoubleValue() - true_hdg->getDoubleValue();
    if ( diff < -180.0 ) { diff += 360.0; }
    if ( diff > 180.0 ) { diff -= 360.0; }
    true_nav1->setDoubleValue( diff );

    // Calculate vertical speed in fpm
    static SGPropertyNode *vs_fps
        = fgGetNode( "/velocities/vertical-speed-fps", true );
    static SGPropertyNode *vs_fpm
        = fgGetNode( "/autopilot/internal/vert-speed-fpm", true );

    vs_fpm->setDoubleValue( vs_fps->getDoubleValue() * 60.0 );  
}


/*
 * Update the list of autopilot components
 */

void FGXMLAutopilot::update( double dt ) {
    update_helper( dt );

    unsigned int i;
    for ( i = 0; i < components.size(); ++i ) {
        components[i]->update( dt );
    }
}
