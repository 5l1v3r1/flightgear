// native_ctrls.cxx -- FGFS "Native" controls I/O class
//
// Written by Curtis Olson, started July 2001.
//
// Copyright (C) 2001  Curtis L. Olson - curt@flightgear.org
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <simgear/debug/logstream.hxx>
#include <simgear/io/iochannel.hxx>
#include <simgear/io/lowlevel.hxx> // endian tests

#include <FDM/flight.hxx>
#include <Main/fg_props.hxx>
#include <Scenery/scenery.hxx>	// ground elevation

#include "native_ctrls.hxx"

// FreeBSD works better with this included last ... (?)
#if defined(WIN32) && !defined(__CYGWIN__)
#  include <windows.h>
#else
#  include <netinet/in.h>	// htonl() ntohl()
#endif


FGNativeCtrls::FGNativeCtrls() {
}

FGNativeCtrls::~FGNativeCtrls() {
}


// open hailing frequencies
bool FGNativeCtrls::open() {
    if ( is_enabled() ) {
	SG_LOG( SG_IO, SG_ALERT, "This shouldn't happen, but the channel " 
		<< "is already in use, ignoring" );
	return false;
    }

    SGIOChannel *io = get_io_channel();

    if ( ! io->open( get_direction() ) ) {
	SG_LOG( SG_IO, SG_ALERT, "Error opening channel communication layer." );
	return false;
    }

    set_enabled( true );

    return true;
}


// The function htond is defined this way due to the way some
// processors and OSes treat floating point values.  Some will raise
// an exception whenever a "bad" floating point value is loaded into a
// floating point register.  Solaris is notorious for this, but then
// so is LynxOS on the PowerPC.  By translating the data in place,
// there is no need to load a FP register with the "corruped" floating
// point value.  By doing the BIG_ENDIAN test, I can optimize the
// routine for big-endian processors so it can be as efficient as
// possible
static void htond (double &x)	
{
    if ( sgIsLittleEndian() ) {
        int    *Double_Overlay;
        int     Holding_Buffer;
    
        Double_Overlay = (int *) &x;
        Holding_Buffer = Double_Overlay [0];
    
        Double_Overlay [0] = htonl (Double_Overlay [1]);
        Double_Overlay [1] = htonl (Holding_Buffer);
    } else {
        return;
    }
}


// Populate the FGNetCtrls structure from the property tree.
void FGProps2NetCtrls( FGNetCtrls *net, bool honor_freezes,
                       bool net_byte_order )
{
    int i;
    SGPropertyNode * node;
    SGPropertyNode * tempnode;

    // fill in values
    node  = fgGetNode("/controls/flight", true);
    net->version = FG_NET_CTRLS_VERSION;
    net->aileron = node->getDoubleValue( "aileron" );
    net->elevator = node->getDoubleValue( "elevator" );
    net->elevator_trim = node->getDoubleValue( "elevator-trim" );
    net->rudder = node->getDoubleValue( "rudder" );
    net->flaps = node->getDoubleValue( "flaps" );
    node = fgGetNode("/controls", true); 
    net->flaps_power
            = node->getDoubleValue( "/systems/electrical/outputs/flaps",
                                    1.0 ) >= 1.0;
    net->num_engines = FGNetCtrls::FG_MAX_ENGINES;
    for ( i = 0; i < FGNetCtrls::FG_MAX_ENGINES; ++i ) {
        node = fgGetNode("/controls/engines/engine", i );
	net->throttle[i] = node->getDoubleValue( "throttle", 0.0 );
	net->mixture[i] = node->getDoubleValue( "mixture", 0.0 );
	net->prop_advance[i] = node->getDoubleValue( "propeller-pitch", 0.0 );
	net->magnetos[i] = node->getIntValue( "magnetos", 0 );
	if ( i == 0 ) {
	  // cout << "Magnetos -> " << node->getIntValue( "magnetos", 0 );
	}
	if ( i == 0 ) {
	  // cout << "Starter -> " << node->getIntValue( "starter", false )
	  //      << endl;
	}
        node = fgGetNode("/controls", true);
	net->fuel_pump_power[i]
            = node->getDoubleValue( "/systems/electrical/outputs/fuel-pump",
                                    1.0 ) >= 1.0;

	net->starter_power[i]
            = node->getDoubleValue( "/systems/electrical/outputs/starter",
                                    1.0 ) >= 1.0;
    }
    net->num_tanks = FGNetCtrls::FG_MAX_TANKS;
    for ( i = 0; i < FGNetCtrls::FG_MAX_TANKS; ++i ) {
        node = fgGetNode("/controls/fuel/tank", i);
        if ( node->getChild("fuel_selector") != 0 ) {
            net->fuel_selector[i]
                = node->getChild("fuel_selector")->getBoolValue();
        } else {
            net->fuel_selector[i] = false;
        }
    }
    net->num_wheels = FGNetCtrls::FG_MAX_WHEELS;
    tempnode = fgGetNode("/controls/gear", true);
    for ( i = 0; i < FGNetCtrls::FG_MAX_WHEELS; ++i ) {
        node = fgGetNode("/controls/gear/wheel", i);
        if ( node->getChild("brake") != NULL ) {
            if ( tempnode->getChild("parking-brake")->getDoubleValue() > 0.0 ) {
                net->brake[i] = 1.0;
           } else {
                net->brake[i]
                    = node->getChild("brake")->getDoubleValue();
            }
        } else {
            net->brake[i] = 0.0;
        }
    }

    node = fgGetNode("/controls/switches", true);
    tempnode = node->getChild("master-bat");
    if ( tempnode != NULL ) {
        net->master_bat = tempnode->getBoolValue();
    }
    tempnode = node->getChild("master-alt");
    if ( tempnode != NULL ) {
        net->master_alt = tempnode->getBoolValue();
    }
    tempnode = node->getChild("master-avionics");
    if ( tempnode != NULL ) {
        net->master_avionics = tempnode->getBoolValue();
    }

    net->wind_speed_kt = fgGetDouble("/environment/wind-speed-kt");
    net->wind_dir_deg = fgGetDouble("/environment/wind-from-heading-deg");
    net->turbulence_norm =
        fgGetDouble("/environment/turbulence/magnitude-norm");

    // cur_fdm_state->get_ground_elev_ft() is what we want ... this
    // reports the altitude of the aircraft.
    // "/environment/ground-elevation-m" reports the ground elevation
    // of the current view point which could change substantially if
    // the user is switching views.
    net->hground = cur_fdm_state->get_ground_elev_ft() * SG_FEET_TO_METER;
    net->magvar = fgGetDouble("/environment/magnetic-variation-deg");
    net->speedup = fgGetInt("/sim/speed-up");
    net->freeze = 0;
    if ( honor_freezes ) {
        if ( fgGetBool("/sim/freeze/master") ) {
            net->freeze |= 0x01;
        }
        if ( fgGetBool("/sim/freeze/position") ) {
            net->freeze |= 0x02;
        }
        if ( fgGetBool("/sim/freeze/fuel") ) {
            net->freeze |= 0x04;
        }
    }

    if ( net_byte_order ) {
        // convert to network byte order
        net->version = htonl(net->version);
        htond(net->aileron);
        htond(net->elevator);
        htond(net->elevator_trim);
        htond(net->rudder);
        htond(net->flaps);
        net->flaps_power = htonl(net->flaps_power);
        for ( i = 0; i < FGNetCtrls::FG_MAX_ENGINES; ++i ) {
            htond(net->throttle[i]);
            htond(net->mixture[i]);
            net->fuel_pump_power[i] = htonl(net->fuel_pump_power[i]);
            htond(net->prop_advance[i]);
            net->magnetos[i] = htonl(net->magnetos[i]);
            net->starter_power[i] = htonl(net->starter_power[i]);
        }
        net->num_engines = htonl(net->num_engines);
        for ( i = 0; i < FGNetCtrls::FG_MAX_TANKS; ++i ) {
            net->fuel_selector[i] = htonl(net->fuel_selector[i]);
        }
        net->num_tanks = htonl(net->num_tanks);
        for ( i = 0; i < FGNetCtrls::FG_MAX_WHEELS; ++i ) {
            htond(net->brake[i]);
        }
        net->num_wheels = htonl(net->num_wheels);
        net->gear_handle = htonl(net->gear_handle);
        net->master_bat = htonl(net->master_bat);
        net->master_alt = htonl(net->master_alt);
        net->master_avionics = htonl(net->master_avionics);
        htond(net->wind_speed_kt);
        htond(net->wind_dir_deg);
        htond(net->turbulence_norm);
        htond(net->hground);
        htond(net->magvar);
        net->speedup = htonl(net->speedup);
        net->freeze = htonl(net->freeze);
    }
}


// Update the property tree from the FGNetCtrls structure.
void FGNetCtrls2Props( FGNetCtrls *net, bool honor_freezes,
                       bool net_byte_order )
{
    int i;

    SGPropertyNode * node;

    if ( net_byte_order ) {
        // convert from network byte order
        net->version = htonl(net->version);
        htond(net->aileron);
        htond(net->elevator);
        htond(net->elevator_trim);
        htond(net->rudder);
        htond(net->flaps);
        net->flaps_power = htonl(net->flaps_power);
        net->num_engines = htonl(net->num_engines);
        for ( i = 0; i < net->num_engines; ++i ) {
            net->magnetos[i] = htonl(net->magnetos[i]);
            net->starter_power[i] = htonl(net->starter_power[i]);
            htond(net->throttle[i]);
            htond(net->mixture[i]);
            net->fuel_pump_power[i] = htonl(net->fuel_pump_power[i]);
            htond(net->prop_advance[i]);
        }
        net->num_tanks = htonl(net->num_tanks);
        for ( i = 0; i < net->num_tanks; ++i ) {
            net->fuel_selector[i] = htonl(net->fuel_selector[i]);
        }
        net->num_wheels = htonl(net->num_wheels);
        for ( i = 0; i < net->num_wheels; ++i ) {
            htond(net->brake[i]);
        }
        net->gear_handle = htonl(net->gear_handle);
        net->master_bat = htonl(net->master_bat);
        net->master_alt = htonl(net->master_alt);
        net->master_avionics = htonl(net->master_avionics);
        htond(net->wind_speed_kt);
        htond(net->wind_dir_deg);
        htond(net->turbulence_norm);
        htond(net->hground);
        htond(net->magvar);
        net->speedup = htonl(net->speedup);
        net->freeze = htonl(net->freeze);
    }

    if ( net->version != FG_NET_CTRLS_VERSION ) {
	SG_LOG( SG_IO, SG_ALERT,
                "Version mismatch with raw controls packet format." );
        SG_LOG( SG_IO, SG_ALERT,
                "FlightGear needs version = " << FG_NET_CTRLS_VERSION
                << " but is receiving version = "  << net->version );
    }
    node = fgGetNode("/controls/flight", true);
    node->setDoubleValue( "aileron", net->aileron );
    node->setDoubleValue( "elevator", net->elevator );
    node->setDoubleValue( "elevator-trim", net->elevator_trim );
    node->setDoubleValue( "rudder", net->rudder );
    node->setDoubleValue( "flaps", net->flaps );

    fgSetBool( "/systems/electrical/outputs/flaps", net->flaps_power );

    for ( i = 0; i < FGNetCtrls::FG_MAX_ENGINES; ++i ) {
        node = fgGetNode("/controls/engines/engine", i);
        node->getChild( "throttle" )->setDoubleValue( net->throttle[i] );
        node->getChild( "mixture" )->setDoubleValue( net->mixture[i] );
        node->getChild( "propeller-pitch" )
            ->setDoubleValue( net->prop_advance[i] );
        node->getChild( "magnetos" )->setDoubleValue( net->magnetos[i] );
    }

    fgSetBool( "/systems/electrical/outputs/fuel-pump",
               net->fuel_pump_power[0] );
    fgSetBool( "/systems/electrical/outputs/starter",
               net->starter_power[0] );

    for ( i = 0; i < FGNetCtrls::FG_MAX_TANKS; ++i ) {
        node = fgGetNode( "/controls/fuel/tank", i );
        node->getChild( "fuel_selector" )
            ->setBoolValue( net->fuel_selector[i] );
    }
    for ( i = 0; i < FGNetCtrls::FG_MAX_WHEELS; ++i ) {
        node = fgGetNode( "/controls/gear/wheel", i );
        node->getChild( "brake" )->setDoubleValue( net->brake[i] );
    }

    node = fgGetNode( "/controls/gear", true );
    node->setBoolValue( "gear-down", net->gear_handle );

    node = fgGetNode( "/controls/switches", true );
    node->setBoolValue( "master-bat", net->master_bat );
    node->setBoolValue( "master-alt", net->master_alt );
    node->setBoolValue( "master-avionics", net->master_avionics );
    
    node = fgGetNode( "/environment", true );
    node->setDoubleValue( "wind-speed-kt", net->wind_speed_kt );
    node->setDoubleValue( "wind-from-heading-deg", net->wind_dir_deg );
    node->setDoubleValue( "turbulence/magnitude-norm", net->turbulence_norm );
    node->setBoolValue( "magnetic-variation-deg", net->magvar );

    // ground elevation ???

    fgSetInt( "/sim/speed-up", net->speedup );

    if ( honor_freezes ) {
        node = fgGetNode( "/sim/freeze", true );
        node->setBoolValue( "master", net->freeze & 0x01 );
        node->setBoolValue( "position", net->freeze & 0x02 );
        node->setBoolValue( "fuel", net->freeze & 0x04 );
    }
}


// process work for this port
bool FGNativeCtrls::process() {
    SGIOChannel *io = get_io_channel();
    int length = sizeof(FGNetCtrls);

    if ( get_direction() == SG_IO_OUT ) {
	// cout << "size of cur_fdm_state = " << length << endl;

	FGProps2NetCtrls( &net_ctrls, true, true );

	if ( ! io->write( (char *)(& net_ctrls), length ) ) {
	    SG_LOG( SG_IO, SG_ALERT, "Error writing data." );
	    return false;
	}
    } else if ( get_direction() == SG_IO_IN ) {
	if ( io->get_type() == sgFileType ) {
	    if ( io->read( (char *)(& net_ctrls), length ) == length ) {
		SG_LOG( SG_IO, SG_DEBUG, "Success reading data." );
		FGNetCtrls2Props( &net_ctrls, true, true );
	    }
	} else {
	    while ( io->read( (char *)(& net_ctrls), length ) == length ) {
		SG_LOG( SG_IO, SG_DEBUG, "Success reading data." );
		FGNetCtrls2Props( &net_ctrls, true, true );
	    }
	}
    }

    return true;
}


// close the channel
bool FGNativeCtrls::close() {
    SGIOChannel *io = get_io_channel();

    set_enabled( false );

    if ( ! io->close() ) {
	return false;
    }

    return true;
}
