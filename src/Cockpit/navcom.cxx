// navcom.cxx -- class to manage a navcom instance
//
// Written by Curtis Olson, started April 2000.
//
// Copyright (C) 2000 - 2002  Curtis L. Olson - curt@flightgear.org
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

#include <stdio.h>	// snprintf

#include <simgear/compiler.h>
#include <simgear/math/sg_random.h>
#include <simgear/math/vector.hxx>

#include <Aircraft/aircraft.hxx>
#include <Navaids/ilslist.hxx>
#include <Navaids/navlist.hxx>
#include <Time/FGEventMgr.hxx>

#include "navcom.hxx"

#include <string>
SG_USING_STD(string);


// Constructor
FGNavCom::FGNavCom() :
    lon_node(fgGetNode("/position/longitude-deg", true)),
    lat_node(fgGetNode("/position/latitude-deg", true)),
    alt_node(fgGetNode("/position/altitude-ft", true)),
    last_nav_id(""),
    last_nav_vor(false),
    nav_play_count(0),
    nav_last_time(0),
    need_update(true),
    power_btn(true),
    audio_btn(true),
    comm_freq(0.0),
    comm_alt_freq(0.0),
    comm_vol_btn(0.0),
    nav_freq(0.0),
    nav_alt_freq(0.0),
    nav_radial(0.0),
    nav_vol_btn(0.0),
    nav_ident_btn(true)
{
    SGPath path( globals->get_fg_root() );
    SGPath term = path;
    term.append( "Navaids/range.term" );
    SGPath low = path;
    low.append( "Navaids/range.low" );
    SGPath high = path;
    high.append( "Navaids/range.high" );

    term_tbl = new SGInterpTable( term.str() );
    low_tbl = new SGInterpTable( low.str() );
    high_tbl = new SGInterpTable( high.str() );

}


// Destructor
FGNavCom::~FGNavCom() 
{
    delete term_tbl;
    delete low_tbl;
    delete high_tbl;
}


void
FGNavCom::init ()
{
    morse.init();

    // We assume that index is valid now (it must be set before init()
    // is called.)
    char propname[256];
    // FIXME: Get rid of snprintf

    snprintf(propname, 256, "/systems/electrical/outputs/navcom[%d]", index);
    // default to true in case no electrical system defined.
    fgSetDouble( propname, 60.0 );
    bus_power = fgGetNode( propname, true );

    snprintf(propname, 256, "/instrumentation/comm[%d]/servicable", index);
    com_servicable = fgGetNode( propname, true );
    com_servicable->setBoolValue( true );

    snprintf(propname, 256, "/instrumentation/nav[%d]/servicable", index);
    nav_servicable = fgGetNode( propname, true );
    nav_servicable->setBoolValue( true );

    snprintf(propname, 256, "/instrumentation/vor[%d]/cdi/servicable", index);
    cdi_servicable = fgGetNode( propname, true );
    cdi_servicable->setBoolValue( true );

    snprintf(propname, 256, "/instrumentation/vor[%d]/gs/servicable", index);
    gs_servicable = fgGetNode( propname, true );
    gs_servicable->setBoolValue( true );

    snprintf(propname, 256, "/instrumentation/vor[%d]/to-from/servicable", index);
    tofrom_servicable = fgGetNode( propname, true );
    tofrom_servicable->setBoolValue( true );
}

void
FGNavCom::bind ()
{
    char propname[256];
    // FIXME: Get rid of snprintf

				// User inputs
    snprintf(propname, 256, "/radios/comm[%d]/inputs/power-btn", index);
    fgTie( propname, this,
           &FGNavCom::get_power_btn, &FGNavCom::set_power_btn );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/comm[%d]/frequencies/selected-mhz", index);
    fgTie( propname, this, &FGNavCom::get_comm_freq, &FGNavCom::set_comm_freq );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/comm[%d]/frequencies/standby-mhz", index);
    fgTie( propname, this,
           &FGNavCom::get_comm_alt_freq, &FGNavCom::set_comm_alt_freq );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/comm[%d]/volume", index);
    fgTie( propname, this,
           &FGNavCom::get_comm_vol_btn, &FGNavCom::set_comm_vol_btn );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/frequencies/selected-mhz", index);
    fgTie( propname, this,
	  &FGNavCom::get_nav_freq, &FGNavCom::set_nav_freq );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/frequencies/standby-mhz", index);
    fgTie( propname , this,
           &FGNavCom::get_nav_alt_freq, &FGNavCom::set_nav_alt_freq);
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/radials/selected-deg", index);
    fgTie( propname, this,
           &FGNavCom::get_nav_sel_radial, &FGNavCom::set_nav_sel_radial );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/volume", index);
    fgTie( propname, this,
           &FGNavCom::get_nav_vol_btn, &FGNavCom::set_nav_vol_btn );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/ident", index);
    fgTie( propname, this,
           &FGNavCom::get_nav_ident_btn, &FGNavCom::set_nav_ident_btn );
    fgSetArchivable( propname );

				// Radio outputs
    snprintf(propname, 256, "/radios/nav[%d]/audio-btn", index);
    fgTie( propname, this,
           &FGNavCom::get_audio_btn, &FGNavCom::set_audio_btn );
    fgSetArchivable( propname );

    snprintf(propname, 256, "/radios/nav[%d]/radials/actual-deg", index);
    fgTie( propname,  this, &FGNavCom::get_nav_radial );

    snprintf(propname, 256, "/radios/nav[%d]/to-flag", index);
    fgTie( propname, this, &FGNavCom::get_nav_to_flag );

    snprintf(propname, 256, "/radios/nav[%d]/from-flag", index);
    fgTie( propname, this, &FGNavCom::get_nav_from_flag );

    snprintf(propname, 256, "/radios/nav[%d]/in-range", index);
    fgTie( propname, this, &FGNavCom::get_nav_inrange );

    snprintf(propname, 256, "/radios/nav[%d]/heading-needle-deflection", index);
    fgTie( propname, this, &FGNavCom::get_nav_heading_needle_deflection );

    snprintf(propname, 256, "/radios/nav[%d]/has-gs", index);
    fgTie( propname, this, &FGNavCom::get_nav_has_gs );

    snprintf(propname, 256, "/radios/nav[%d]/gs-needle-deflection", index);
    fgTie( propname, this, &FGNavCom::get_nav_gs_needle_deflection );

    snprintf(propname, 256, "/radios/nav[%d]/nav-id", index);
    fgTie( propname, this, &FGNavCom::get_nav_id );

    // put nav_id characters into seperate properties for instrument displays
    snprintf(propname, 256, "/radios/nav[%d]/nav-id_asc1", index);
    fgTie( propname, this, &FGNavCom::get_nav_id_c1 );

    snprintf(propname, 256, "/radios/nav[%d]/nav-id_asc2", index);
    fgTie( propname, this, &FGNavCom::get_nav_id_c2 );

    snprintf(propname, 256, "/radios/nav[%d]/nav-id_asc3", index);
    fgTie( propname, this, &FGNavCom::get_nav_id_c3 );

    snprintf(propname, 256, "/radios/nav[%d]/nav-id_asc4", index);
    fgTie( propname, this, &FGNavCom::get_nav_id_c4 );

    // end of binding
}


void
FGNavCom::unbind ()
{
    char propname[256];
    // FIXME: Get rid of snprintf

    snprintf(propname, 256, "/radios/comm[%d]/inputs/power-btn", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/comm[%d]/frequencies/selected-mhz", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/comm[%d]/frequencies/standby-mhz", index);
    fgUntie( propname );

    snprintf(propname, 256, "/radios/nav[%d]/frequencies/selected-mhz", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/frequencies/standby-mhz", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/radials/actual-deg", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/radials/selected-deg", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/ident", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/to-flag", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/from-flag", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/in-range", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/heading-needle-deflection", index);
    fgUntie( propname );
    snprintf(propname, 256, "/radios/nav[%d]/gs-needle-deflection", index);
    fgUntie( propname );
}


// model standard VOR/DME/TACAN service volumes as per AIM 1-1-8
double FGNavCom::adjustNavRange( double stationElev, double aircraftElev,
                                 double nominalRange )
{
    // extend out actual usable range to be 1.3x the published safe range
    const double usability_factor = 1.3;

    // assumptions we model the standard service volume, plus
    // ... rather than specifying a cylinder, we model a cone that
    // contains the cylinder.  Then we put an upside down cone on top
    // to model diminishing returns at too-high altitudes.

    // altitude difference
    double alt = ( aircraftElev * SG_METER_TO_FEET - stationElev );
    // cout << "aircraft elev = " << aircraftElev * SG_METER_TO_FEET
    //      << " station elev = " << stationElev << endl;

    if ( nominalRange < 25.0 + SG_EPSILON ) {
	// Standard Terminal Service Volume
	return term_tbl->interpolate( alt ) * usability_factor;
    } else if ( nominalRange < 50.0 + SG_EPSILON ) {
	// Standard Low Altitude Service Volume
	// table is based on range of 40, scale to actual range
	return low_tbl->interpolate( alt ) * nominalRange / 40.0
	    * usability_factor;
    } else {
	// Standard High Altitude Service Volume
	// table is based on range of 130, scale to actual range
	return high_tbl->interpolate( alt ) * nominalRange / 130.0
	    * usability_factor;
    }
}


// model standard ILS service volumes as per AIM 1-1-9
double FGNavCom::adjustILSRange( double stationElev, double aircraftElev,
				     double offsetDegrees, double distance )
{
    // assumptions we model the standard service volume, plus

    // altitude difference
    // double alt = ( aircraftElev * SG_METER_TO_FEET - stationElev );
//     double offset = fabs( offsetDegrees );

//     if ( offset < 10 ) {
// 	return FG_ILS_DEFAULT_RANGE;
//     } else if ( offset < 35 ) {
// 	return 10 + (35 - offset) * (FG_ILS_DEFAULT_RANGE - 10) / 25;
//     } else if ( offset < 45 ) {
// 	return (45 - offset);
//     } else if ( offset > 170 ) {
//         return FG_ILS_DEFAULT_RANGE;
//     } else if ( offset > 145 ) {
// 	return 10 + (offset - 145) * (FG_ILS_DEFAULT_RANGE - 10) / 25;
//     } else if ( offset > 135 ) {
//         return (offset - 135);
//     } else {
// 	return 0;
//     }
    return FG_ILS_DEFAULT_RANGE;
}


// Update the various nav values based on position and valid tuned in navs
void 
FGNavCom::update(double dt) 
{
    double lon = lon_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double lat = lat_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double elev = alt_node->getDoubleValue() * SG_FEET_TO_METER;

    need_update = false;

    Point3D aircraft = sgGeodToCart( Point3D( lon, lat, elev ) );
    Point3D station;
    double az1, az2, s;

    ////////////////////////////////////////////////////////////////////////
    // Nav.
    ////////////////////////////////////////////////////////////////////////

    if ( nav_valid && power_btn && (bus_power->getDoubleValue() > 1.0)
         && nav_servicable->getBoolValue() )
    {
	station = Point3D( nav_x, nav_y, nav_z );
	nav_loc_dist = aircraft.distance3D( station );

	if ( nav_has_gs ) {
            // find closest distance to the gs base line
            sgdVec3 p;
            sgdSetVec3( p, aircraft.x(), aircraft.y(), aircraft.z() );
            sgdVec3 p0;
            sgdSetVec3( p0, nav_gs_x, nav_gs_y, nav_gs_z );
            double dist = sgdClosestPointToLineDistSquared( p, p0,
                                                            gs_base_vec );
            nav_gs_dist = sqrt( dist );
            // cout << nav_gs_dist;

            // Point3D tmp( nav_gs_x, nav_gs_y, nav_gs_z );
            // cout << " (" << aircraft.distance3D( tmp ) << ")" << endl;

            // wgs84 heading to glide slope (to determine sign of distance)
            geo_inverse_wgs_84( elev,
                                lat * SGD_RADIANS_TO_DEGREES,
                                lon * SGD_RADIANS_TO_DEGREES, 
                                nav_gslat, nav_gslon,
                                &az1, &az2, &s );
            double r = az1 - nav_radial;
            while ( r >  180.0 ) { r -= 360.0;}
            while ( r < -180.0 ) { r += 360.0;}
            if ( r >= -90.0 && r <= 90.0 ) {
                nav_gs_dist_signed = nav_gs_dist;
            } else {
                nav_gs_dist_signed = -nav_gs_dist;
            }
            /* cout << "Target Radial = " << nav_radial 
                 << "  Bearing = " << az1
                 << "  dist (signed) = " << nav_gs_dist_signed
                 << endl; */
            
	} else {
	    nav_gs_dist = 0.0;
	}
	
	// wgs84 heading to localizer
	geo_inverse_wgs_84( elev,
                            lat * SGD_RADIANS_TO_DEGREES,
                            lon * SGD_RADIANS_TO_DEGREES, 
			    nav_loclat, nav_loclon,
			    &az1, &az2, &s );
	// cout << "az1 = " << az1 << " magvar = " << nav_magvar << endl;
	nav_heading = az1 - nav_magvar;
	// cout << " heading = " << nav_heading
	//      << " dist = " << nav_dist << endl;

	if ( nav_loc ) {
	    double offset = nav_heading - nav_radial;
	    while ( offset < -180.0 ) { offset += 360.0; }
	    while ( offset > 180.0 ) { offset -= 360.0; }
	    // cout << "ils offset = " << offset << endl;
	    nav_effective_range = adjustILSRange(nav_elev, elev, offset,
						  nav_loc_dist * SG_METER_TO_NM );
	} else {
	    nav_effective_range = adjustNavRange(nav_elev, elev, nav_range);
	}
	// cout << "nav range = " << nav_effective_range
	//      << " (" << nav_range << ")" << endl;

	if ( nav_loc_dist < nav_effective_range * SG_NM_TO_METER ) {
	    nav_inrange = true;
	} else if ( nav_loc_dist < 2 * nav_effective_range * SG_NM_TO_METER ) {
	    nav_inrange = sg_random() < 
		( 2 * nav_effective_range * SG_NM_TO_METER - nav_loc_dist ) /
		(nav_effective_range * SG_NM_TO_METER);
	} else {
	    nav_inrange = false;
	}

	if ( !nav_loc ) {
	    nav_radial = nav_sel_radial;
	}
    } else {
	nav_inrange = false;
	// cout << "not picking up vor. :-(" << endl;
    }

    if ( nav_valid && nav_inrange && nav_servicable->getBoolValue() ) {
	// play station ident via audio system if on + ident,
	// otherwise turn it off
	if ( power_btn && (bus_power->getDoubleValue() > 1.0)
             && nav_ident_btn && audio_btn )
        {
	    SGSimpleSound *sound;
	    sound = globals->get_soundmgr()->find( nav_fx_name );
            if ( sound != NULL ) {
                sound->set_volume( nav_vol_btn );
            } else {
                SG_LOG( SG_COCKPIT, SG_ALERT,
                        "Can't find nav-vor-ident sound" );
            }
	    sound = globals->get_soundmgr()->find( dme_fx_name );
            if ( sound != NULL ) {
                sound->set_volume( nav_vol_btn );
            } else {
                SG_LOG( SG_COCKPIT, SG_ALERT,
                        "Can't find nav-dme-ident sound" );
            }
            // cout << "nav_last_time = " << nav_last_time << " ";
            // cout << "cur_time = "
            //      << globals->get_time_params()->get_cur_time();
	    if ( nav_last_time <
		 globals->get_time_params()->get_cur_time() - 30 ) {
		nav_last_time = globals->get_time_params()->get_cur_time();
		nav_play_count = 0;
	    }
            // cout << " nav_play_count = " << nav_play_count << endl;
            // cout << "playing = "
            //      << globals->get_soundmgr()->is_playing(nav_fx_name)
            //      << endl;
	    if ( nav_play_count < 4 ) {
		// play VOR ident
		if ( !globals->get_soundmgr()->is_playing(nav_fx_name) ) {
		    globals->get_soundmgr()->play_once( nav_fx_name );
		    ++nav_play_count;
                }
	    } else if ( nav_play_count < 5 && nav_has_dme ) {
		// play DME ident
		if ( !globals->get_soundmgr()->is_playing(nav_fx_name) &&
		     !globals->get_soundmgr()->is_playing(dme_fx_name) ) {
		    globals->get_soundmgr()->play_once( dme_fx_name );
		    ++nav_play_count;
		}
	    }
	} else {
	    globals->get_soundmgr()->stop( nav_fx_name );
	    globals->get_soundmgr()->stop( dme_fx_name );
	}
    }
}


// Update current nav/adf radio stations based on current postition
void FGNavCom::search() 
{
    double lon = lon_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double lat = lat_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double elev = alt_node->getDoubleValue() * SG_FEET_TO_METER;

    FGILS *ils;
    FGNav *nav;

    ////////////////////////////////////////////////////////////////////////
    // Nav.
    ////////////////////////////////////////////////////////////////////////

    if ( (ils = current_ilslist->findByFreq(nav_freq, lon, lat, elev)) != NULL ) {
	nav_id = ils->get_locident();
	nav_valid = true;
	if ( last_nav_id != nav_id || last_nav_vor ) {
	    nav_trans_ident = ils->get_trans_ident();
	    last_nav_id = nav_id;
	    last_nav_vor = false;
	    nav_loc = true;
	    nav_has_dme = ils->get_has_dme();
	    nav_has_gs = ils->get_has_gs();

	    nav_loclon = ils->get_loclon();
	    nav_loclat = ils->get_loclat();
	    nav_gslon = ils->get_gslon();
	    nav_gslat = ils->get_gslat();
	    nav_elev = ils->get_gselev();
	    nav_magvar = 0;
	    nav_range = FG_ILS_DEFAULT_RANGE;
	    nav_effective_range = nav_range;
	    nav_target_gs = ils->get_gsangle();
	    nav_radial = ils->get_locheading();
	    while ( nav_radial <   0.0 ) { nav_radial += 360.0; }
	    while ( nav_radial > 360.0 ) { nav_radial -= 360.0; }
	    nav_x = ils->get_x();
	    nav_y = ils->get_y();
	    nav_z = ils->get_z();
	    nav_gs_x = ils->get_gs_x();
	    nav_gs_y = ils->get_gs_y();
	    nav_gs_z = ils->get_gs_z();

            // derive GS baseline
            double tlon, tlat, taz;
            geo_direct_wgs_84 ( 0.0, nav_gslat, nav_gslon, nav_radial + 90,  
                                100.0, &tlat, &tlon, &taz );
            // cout << nav_gslon << "," << nav_gslat << "  "
            //      << tlon << "," << tlat << "  (" << nav_elev << ")" << endl;
            Point3D p1 = sgGeodToCart( Point3D(tlon*SGD_DEGREES_TO_RADIANS,
                                               tlat*SGD_DEGREES_TO_RADIANS,
                                               nav_elev*SG_FEET_TO_METER) );
            // cout << nav_gs_x << "," << nav_gs_y << "," << nav_gs_z << endl;
            // cout << p1 << endl;
            sgdSetVec3( gs_base_vec,
                        p1.x()-nav_gs_x, p1.y()-nav_gs_y, p1.z()-nav_gs_z );
            // cout << gs_base_vec[0] << "," << gs_base_vec[1] << ","
            //      << gs_base_vec[2] << endl;

	    if ( globals->get_soundmgr()->exists( nav_fx_name ) ) {
		globals->get_soundmgr()->remove( nav_fx_name );
	    }
	    SGSimpleSound *sound;
	    sound = morse.make_ident( nav_trans_ident, LO_FREQUENCY );
	    sound->set_volume( 0.3 );
	    globals->get_soundmgr()->add( sound, nav_fx_name );

	    if ( globals->get_soundmgr()->exists( dme_fx_name ) ) {
		globals->get_soundmgr()->remove( dme_fx_name );
	    }
	    sound = morse.make_ident( nav_trans_ident, HI_FREQUENCY );
	    sound->set_volume( 0.3 );
	    globals->get_soundmgr()->add( sound, dme_fx_name );

	    int offset = (int)(sg_random() * 30.0);
	    nav_play_count = offset / 4;
	    nav_last_time = globals->get_time_params()->get_cur_time() -
		offset;
	    // cout << "offset = " << offset << " play_count = "
	    //      << nav_play_count
	    //      << " nav_last_time = " << nav_last_time
	    //      << " current time = "
	    //      << globals->get_time_params()->get_cur_time() << endl;

	    // cout << "Found an ils station in range" << endl;
	    // cout << " id = " << ils->get_locident() << endl;
	}
    } else if ( (nav = current_navlist->findByFreq(nav_freq, lon, lat, elev)) != NULL ) {
	nav_id = nav->get_ident();
	nav_valid = (nav->get_type() == 'V');
	if ( last_nav_id != nav_id || !last_nav_vor ) {
	    last_nav_id = nav_id;
	    last_nav_vor = true;
	    nav_trans_ident = nav->get_trans_ident();
	    nav_loc = false;
	    nav_has_dme = nav->get_has_dme();
	    nav_has_gs = false;
	    nav_loclon = nav->get_lon();
	    nav_loclat = nav->get_lat();
	    nav_elev = nav->get_elev();
	    nav_magvar = nav->get_magvar();
	    nav_range = nav->get_range();
	    nav_effective_range = adjustNavRange(nav_elev, elev, nav_range);
	    nav_target_gs = 0.0;
	    nav_radial = nav_sel_radial;
	    nav_x = nav->get_x();
	    nav_y = nav->get_y();
	    nav_z = nav->get_z();

	    if ( globals->get_soundmgr()->exists( nav_fx_name ) ) {
		globals->get_soundmgr()->remove( nav_fx_name );
	    }
	    SGSimpleSound *sound;
	    sound = morse.make_ident( nav_trans_ident, LO_FREQUENCY );
	    sound->set_volume( 0.3 );
	    if ( globals->get_soundmgr()->add( sound, nav_fx_name ) ) {
                // cout << "Added nav-vor-ident sound" << endl;
            } else {
                SG_LOG(SG_COCKPIT, SG_WARN, "Failed to add v1-vor-ident sound");
            }

	    if ( globals->get_soundmgr()->exists( dme_fx_name ) ) {
		globals->get_soundmgr()->remove( dme_fx_name );
	    }
	    sound = morse.make_ident( nav_trans_ident, HI_FREQUENCY );
	    sound->set_volume( 0.3 );
	    globals->get_soundmgr()->add( sound, dme_fx_name );

	    int offset = (int)(sg_random() * 30.0);
	    nav_play_count = offset / 4;
	    nav_last_time = globals->get_time_params()->get_cur_time() -
		offset;
	    // cout << "offset = " << offset << " play_count = "
	    //      << nav_play_count << " nav_last_time = "
	    //      << nav_last_time << " current time = "
	    //      << globals->get_time_params()->get_cur_time() << endl;

	    // cout << "Found a vor station in range" << endl;
	    // cout << " id = " << nav->get_ident() << endl;
	}
    } else {
	nav_valid = false;
	nav_id = "";
	nav_radial = 0;
	nav_trans_ident = "";
	last_nav_id = "";
	if ( ! globals->get_soundmgr()->remove( nav_fx_name ) ) {
            SG_LOG(SG_COCKPIT, SG_WARN, "Failed to remove nav-vor-ident sound");
        }
	globals->get_soundmgr()->remove( dme_fx_name );
	// cout << "not picking up vor1. :-(" << endl;
    }
}


// return the amount of heading needle deflection, returns a value
// clamped to the range of ( -10 , 10 )
double FGNavCom::get_nav_heading_needle_deflection() const {
    double r;

    if ( nav_inrange
         && nav_servicable->getBoolValue() && cdi_servicable->getBoolValue() )
    {
        r = nav_heading - nav_radial;
	// cout << "Radial = " << nav_radial 
	//      << "  Bearing = " << nav_heading << endl;
    
	while ( r >  180.0 ) { r -= 360.0;}
	while ( r < -180.0 ) { r += 360.0;}
	if ( fabs(r) > 90.0 )
	    r = ( r<0.0 ? -r-180.0 : -r+180.0 );

	// According to Robin Peel, the ILS is 4x more sensitive than a vor
	if ( nav_loc ) { r *= 4.0; }
	if ( r < -10.0 ) { r = -10.0; }
	if ( r >  10.0 ) { r = 10.0; }
    } else {
	r = 0.0;
    }

    return r;
}


// return the amount of glide slope needle deflection (.i.e. the
// number of degrees we are off the glide slope * 5.0
double FGNavCom::get_nav_gs_needle_deflection() const {
    if ( nav_inrange && nav_has_gs
         && nav_servicable->getBoolValue() && gs_servicable->getBoolValue() )
    {
	double x = nav_gs_dist;
	double y = (fgGetDouble("/position/altitude-ft") - nav_elev)
            * SG_FEET_TO_METER;
        // cout << "dist = " << x << " height = " << y << endl;
	double angle = asin( y / x ) * SGD_RADIANS_TO_DEGREES;
	return (nav_target_gs - angle) * 5.0;
    } else {
	return 0.0;
    }
}


/**
 * Return true if the NAV TO flag should be active.
 */
bool 
FGNavCom::get_nav_to_flag () const
{
    if ( nav_inrange
         && nav_servicable->getBoolValue()
         && tofrom_servicable->getBoolValue() )
    {
        double offset = fabs(nav_heading - nav_radial);
        if (nav_loc) {
            return true;
        } else {
            return (offset <= 90.0 || offset >= 270.0);
        }
    } else {
        return false;
    }
}


/**
 * Return true if the NAV FROM flag should be active.
 */
bool
FGNavCom::get_nav_from_flag () const
{
    if ( nav_inrange
         && nav_servicable->getBoolValue()
         && tofrom_servicable->getBoolValue() ) {
        double offset = fabs(nav_heading - nav_radial);
        if (nav_loc) {
            return false;
        } else {
          return (offset > 90.0 && offset < 270.0);
        }
    } else {
        return false;
    }
}
