// flight.cxx -- a general interface to the various flight models
//
// Written by Curtis Olson, started May 1997.
//
// Copyright (C) 1997  Curtis L. Olson  - curt@infoplane.com
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


#include <stdio.h>

#include <plib/sg.h>

#include <simgear/constants.h>
#include <simgear/debug/logstream.hxx>
#include <simgear/math/sg_geodesy.hxx>
#include <simgear/timing/timestamp.hxx>

#include <Scenery/scenery.hxx>
#include <FDM/LaRCsim/ls_interface.h>
#include <Main/globals.hxx>
#include <Main/fg_props.hxx>

#include "External.hxx"
#include "flight.hxx"
#include "JSBSim.hxx"
#include "LaRCsim.hxx"
#include "Balloon.h"


// base_fdm_state is the internal state that is updated in integer
// multiples of "dt".  This leads to "jitter" with respect to the real
// world time, so we introduce cur_fdm_state which is extrapolated by
// the difference between sim time and real world time

FGInterface *cur_fdm_state;
FGInterface base_fdm_state;

inline void init_vec(FG_VECTOR_3 vec) {
    vec[0] = 0.0; vec[1] = 0.0; vec[2] = 0.0;
}

FGEngInterface::FGEngInterface() {

    // inputs
    Throttle=0;
    Mixture=0;
    Prop_Advance=0;

    // outputs
    RPM=0;
    Manifold_Pressure=0;
    MaxHP=0;
    Percentage_Power=0;
    EGT=0;
    prop_thrust=0;
}

FGEngInterface::~FGEngInterface(void) {
}

FGGearInterface::FGGearInterface(void) {
    x=y=z=0.0;
    brake=rolls=WoW=false;
    position=1.0;
}

FGGearInterface::~FGGearInterface() {
}

// Constructor
FGInterface::FGInterface() {
    _setup();
}

FGInterface::FGInterface( double dt ) {
    _setup();
    delta_t = dt;
    remainder = elapsed = multi_loop = 0;
}

// Destructor
FGInterface::~FGInterface() {
    // unbind();                   // FIXME: should be called explicitly
}


/**
 * Set default values for the state of the FDM.
 *
 * This method is invoked by the constructors.
 */
void
FGInterface::_setup ()
{
    inited = false;
    bound = false;

    init_vec( d_pilot_rp_body_v );
    init_vec( d_cg_rp_body_v );
    init_vec( f_body_total_v );
    init_vec( f_local_total_v );
    init_vec( f_aero_v );
    init_vec( f_engine_v );
    init_vec( f_gear_v );
    init_vec( m_total_rp_v );
    init_vec( m_total_cg_v );
    init_vec( m_aero_v );
    init_vec( m_engine_v );
    init_vec( m_gear_v );
    init_vec( v_dot_local_v );
    init_vec( v_dot_body_v );
    init_vec( a_cg_body_v );
    init_vec( a_pilot_body_v );
    init_vec( n_cg_body_v );
    init_vec( n_pilot_body_v );
    init_vec( omega_dot_body_v );
    init_vec( v_local_v );
    init_vec( v_local_rel_ground_v );
    init_vec( v_local_airmass_v );
    init_vec( v_local_rel_airmass_v );
    init_vec( v_local_gust_v );
    init_vec( v_wind_body_v );
    init_vec( omega_body_v );
    init_vec( omega_local_v );
    init_vec( omega_total_v );
    init_vec( euler_rates_v );
    init_vec( geocentric_rates_v );
    init_vec( geocentric_position_v );
    init_vec( geodetic_position_v );
    init_vec( euler_angles_v );
    init_vec( d_cg_rwy_local_v );
    init_vec( d_cg_rwy_rwy_v );
    init_vec( d_pilot_rwy_local_v );
    init_vec( d_pilot_rwy_rwy_v );
    init_vec( t_local_to_body_m[0] );
    init_vec( t_local_to_body_m[1] );
    init_vec( t_local_to_body_m[2] );

    mass=i_xx=i_yy=i_zz=i_xz=0;
    nlf=0;
    v_rel_wind=v_true_kts=v_rel_ground=v_inertial=0;
    v_ground_speed=v_equiv=v_equiv_kts=0;
    v_calibrated=v_calibrated_kts=0;
    gravity=0;
    centrifugal_relief=0;
    alpha=beta=alpha_dot=beta_dot=0;
    cos_alpha=sin_alpha=cos_beta=sin_beta=0;
    cos_phi=sin_phi=cos_theta=sin_theta=cos_psi=sin_psi=0;
    gamma_vert_rad=gamma_horiz_rad=0;
    sigma=density=v_sound=mach_number=0;
    static_pressure=total_pressure=impact_pressure=0;
    dynamic_pressure=0;
    static_temperature=total_temperature=0;
    sea_level_radius=earth_position_angle=0;
    runway_altitude=runway_latitude=runway_longitude=0;
    runway_heading=0;
    radius_to_rwy=0;
    climb_rate=0;
    sin_lat_geocentric=cos_lat_geocentric=0;
    sin_latitude=cos_latitude=0;
    sin_longitude=cos_longitude=0;
    altitude_agl=0;
}

void
FGInterface::init () {}

/**
 * Initialize the state of the FDM.
 *
 * Subclasses of FGInterface may do their own, additional initialization,
 * but there is some that is common to all.  Normally, they should call
 * this before they begin their own init to make sure the basic structures
 * are set up properly.
 */
void
FGInterface::common_init ()
{
    SG_LOG( SG_FLIGHT, SG_INFO, "Start common FDM init" );

    set_inited( true );

    stamp();
    set_remainder( 0 );

    // Set initial position
    SG_LOG( SG_FLIGHT, SG_INFO, "...initializing position..." );
    set_Longitude( fgGetDouble("/position/longitude-deg")
                   * SGD_DEGREES_TO_RADIANS );
    set_Latitude( fgGetDouble("/position/latitude-deg")
                  * SGD_DEGREES_TO_RADIANS );
    double ground_elev_m = scenery.get_cur_elev();
    double ground_elev_ft = ground_elev_m * SG_METER_TO_FEET;
    if ( fgGetBool("/sim/startup/onground")
         || fgGetDouble("/position/altitude-ft") < ground_elev_ft ) {
        fgSetDouble("/position/altitude-ft", ground_elev_ft);
    }
    set_Altitude( fgGetDouble("/position/altitude-ft") );

    // Set ground elevation
    SG_LOG( SG_FLIGHT, SG_INFO,
            "...initializing ground elevation to " << ground_elev_ft
            << "ft..." );
    SG_LOG( SG_FLIGHT, SG_INFO, "common_init(): set ground elevation "
            << ground_elev_ft );
    base_fdm_state.set_Runway_altitude( ground_elev_ft );
    set_Runway_altitude( ground_elev_ft );

    // Set sea-level radius
    SG_LOG( SG_FLIGHT, SG_INFO, "...initializing sea-level radius..." );
    SG_LOG( SG_FLIGHT, SG_INFO, " lat = "
            << fgGetDouble("/position/latitude-deg")
            << " alt = " << fgGetDouble("/position/altitude-ft") );
    double sea_level_radius_meters;
    double lat_geoc;
    sgGeodToGeoc( fgGetDouble("/position/latitude-deg")
                    * SGD_DEGREES_TO_RADIANS,
                  fgGetDouble("/position/altitude-ft") * SG_FEET_TO_METER,
                  &sea_level_radius_meters, &lat_geoc );
    set_Sea_level_radius( sea_level_radius_meters * SG_METER_TO_FEET );

    // Set initial velocities
    SG_LOG( SG_FLIGHT, SG_INFO, "...initializing velocities..." );
    if ( !fgHasNode("/sim/startup/speed-set") ) {
        set_V_calibrated_kts(0.0);
    } else {
        const string speedset = fgGetString("/sim/startup/speed-set");
        if ( speedset == "knots" || speedset == "KNOTS" ) {
            set_V_calibrated_kts( fgGetDouble("/velocities/airspeed-kt") );
        } else if ( speedset == "mach" || speedset == "MACH" ) {
            set_Mach_number( fgGetDouble("/velocities/mach") );
        } else if ( speedset == "UVW" || speedset == "uvw" ) {
            set_Velocities_Wind_Body(
                                     fgGetDouble("/velocities/uBody-fps"),
                                     fgGetDouble("/velocities/vBody-fps"),
                                     fgGetDouble("/velocities/wBody-fps") );
        } else if ( speedset == "NED" || speedset == "ned" ) {
            set_Velocities_Local(
                                 fgGetDouble("/velocities/speed-north-fps"),
                                 fgGetDouble("/velocities/speed-east-fps"),
                                 fgGetDouble("/velocities/speed-down-fps") );
        } else {
            SG_LOG( SG_FLIGHT, SG_ALERT,
                    "Unrecognized value for /sim/startup/speed-set: "
                    << speedset);
            set_V_calibrated_kts( 0.0 );
        }
    }

    // Set initial Euler angles
    SG_LOG( SG_FLIGHT, SG_INFO, "...initializing Euler angles..." );
    set_Euler_Angles( fgGetDouble("/orientation/roll-deg")
                        * SGD_DEGREES_TO_RADIANS,
                      fgGetDouble("/orientation/pitch-deg")
                        * SGD_DEGREES_TO_RADIANS,
                      fgGetDouble("/orientation/heading-deg")
                        * SGD_DEGREES_TO_RADIANS );

    SG_LOG( SG_FLIGHT, SG_INFO, "End common FDM init" );
}


/**
 * Bind getters and setters to properties.
 *
 * The bind() method will be invoked after init().  Note that unlike
 * the usual implementations of FGSubsystem::bind(), this method does
 * not automatically pick up existing values for the properties at
 * bind time; instead, all values are set explicitly in the init()
 * method.
 */
void
FGInterface::bind ()
{
  bound = true;

                                // Time management (read-only)
  fgTie("/fdm/time/delta_t", this,
        &FGInterface::get_delta_t); // read-only
  fgTie("/fdm/time/elapsed", this,
        &FGInterface::get_elapsed); // read-only
  fgTie("/fdm/time/remainder", this,
        &FGInterface::get_remainder); // read-only
  fgTie("/fdm/time/multi_loop", this,
        &FGInterface::get_multi_loop); // read-only

			// Aircraft position
  fgTie("/position/latitude-deg", this,
        &FGInterface::get_Latitude_deg,
        &FGInterface::set_Latitude_deg,
        false);
  fgSetArchivable("/position/latitude-deg");
  fgTie("/position/longitude-deg", this,
        &FGInterface::get_Longitude_deg,
        &FGInterface::set_Longitude_deg,
        false);
  fgSetArchivable("/position/longitude-deg");
  fgTie("/position/altitude-ft", this,
        &FGInterface::get_Altitude,
        &FGInterface::set_Altitude,
        false);
  fgSetArchivable("/position/altitude-ft");
  fgTie("/position/altitude-agl-ft", this,
        &FGInterface::get_Altitude_AGL); // read-only

				// Orientation
  fgTie("/orientation/roll-deg", this,
	&FGInterface::get_Phi_deg,
	&FGInterface::set_Phi_deg);
  fgSetArchivable("/orientation/roll-deg");
  fgTie("/orientation/pitch-deg", this,
	&FGInterface::get_Theta_deg,
	&FGInterface::set_Theta_deg);
  fgSetArchivable("/orientation/pitch-deg");
  fgTie("/orientation/heading-deg", this,
	&FGInterface::get_Psi_deg,
	&FGInterface::set_Psi_deg);
  fgSetArchivable("/orientation/heading-deg");

				// Calibrated airspeed
  fgTie("/velocities/airspeed-kt", this,
	&FGInterface::get_V_calibrated_kts,
	&FGInterface::set_V_calibrated_kts,
	false);

				// Local velocities
//   fgTie("/velocities/speed-north-fps", this,
// 	&FGInterface::get_V_north,
// 	&FGInterface::set_V_north);
//   fgSetArchivable("/velocities/speed-north-fps");
//   fgTie("/velocities/speed-east-fps", this,
// 	&FGInterface::get_V_east,
// 	&FGInterface::set_V_east);
//   fgSetArchivable("/velocities/speed-east-fps");
//   fgTie("/velocities/speed-down-fps", this,
// 	&FGInterface::get_V_down,
// 	&FGInterface::set_V_down);
//   fgSetArchivable("/velocities/speed-down-fps");
				// FIXME: Temporarily read-only, until the
				// incompatibilities between JSBSim and
				// LaRCSim are fixed (LaRCSim adds the
				// earth's rotation to the east velocity).
  fgTie("/velocities/speed-north-fps", this,
	&FGInterface::get_V_north);
  fgTie("/velocities/speed-east-fps", this,
	&FGInterface::get_V_east);
  fgTie("/velocities/speed-down-fps", this,
	&FGInterface::get_V_down);

				// Relative wind
				// FIXME: temporarily archivable, until
				// the NED problem is fixed.
  fgTie("/velocities/uBody-fps", this,
	&FGInterface::get_uBody,
	&FGInterface::set_uBody,
	false);
  fgSetArchivable("/velocities/uBody-fps");
  fgTie("/velocities/vBody-fps", this,
	&FGInterface::get_vBody,
	&FGInterface::set_vBody,
	false);
  fgSetArchivable("/velocities/vBody-fps");
  fgTie("/velocities/wBody-fps", this,
	&FGInterface::get_wBody,
	&FGInterface::set_wBody,
	false);
  fgSetArchivable("/velocities/wBody-fps");

				// Climb and slip (read-only)
  fgTie("/velocities/vertical-speed-fps", this,
	&FGInterface::get_Climb_Rate); // read-only
  fgTie("/velocities/side-slip-rad", this,
	&FGInterface::get_Beta); // read-only

				// Powerplant
  for (int i = 0; i < get_num_engines(); i++) {
    char buf[64];

    sprintf(buf, "/engines/engine[%d]/rpm", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_RPM);

    sprintf(buf, "/engines/engine[%d]/egt-degf", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_EGT);

    sprintf(buf, "/engines/engine[%d]/cht-degf", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_CHT);

    sprintf(buf, "/engines/engine[%d]/oil-temperature-degf", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_Oil_Temp);

    sprintf(buf, "/engines/engine[%d]/mp-osi", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_Manifold_Pressure);

    sprintf(buf, "/engines/engine[%d]/fuel-flow-gph", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_Fuel_Flow);

    sprintf(buf, "/engines/engine[%d]/running", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_Running_Flag);

    sprintf(buf, "/engines/engine[%d]/cranking", i);
    fgTie(buf, get_engine(i), &FGEngInterface::get_Cranking_Flag);

  }
}


/**
 * Unbind any properties bound to this FDM.
 *
 * This method allows the FDM to release properties so that a new
 * FDM can bind them instead.
 */
void
FGInterface::unbind ()
{
  bound = false;

  fgUntie("/fdm/time/delta_t");
  fgUntie("/fdm/time/elapsed");
  fgUntie("/fdm/time/remainder");
  fgUntie("/fdm/time/multi_loop");
  fgUntie("/position/latitude-deg");
  fgUntie("/position/longitude-deg");
  fgUntie("/position/altitude-ft");
  fgUntie("/position/altitude-agl-ft");
  fgUntie("/orientation/heading-deg");
  fgUntie("/orientation/pitch-deg");
  fgUntie("/orientation/roll-deg");
  fgUntie("/velocities/airspeed-kt");
  fgUntie("/velocities/speed-north-fps");
  fgUntie("/velocities/speed-east-fps");
  fgUntie("/velocities/speed-down-fps");
  fgUntie("/velocities/uBody-fps");
  fgUntie("/velocities/vBody-fps");
  fgUntie("/velocities/wBody-fps");
  fgUntie("/velocities/vertical-speed-fps");
  fgUntie("/velocities/side-slip-rad");
  for (int i = 0; i < get_num_engines(); i++) {
    char buf[64];
    sprintf(buf, "/engines/engine[%d]/rpm", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/egt-degf", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/cht-degf", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/oil-temperature-degf", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/mp-osi", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/fuel-flow-gph", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/running", i);
    fgUntie(buf);
    sprintf(buf, "/engines/engine[%d]/cranking", i);
    fgUntie(buf);
  }
}

void
FGInterface::free_engines ()
{
    int i;
    for ( i = 0; i < get_num_engines(); ++i ) {
        delete get_engine(i);
    }
    engines.clear();
}

void
FGInterface::free_gear_units ()
{
    int i;
    for ( i = 0; i < get_num_gear(); ++i ) {
        delete [] get_gear_unit(i);
    }
    gear.clear();
}

/**
 * Update the state of the FDM (i.e. run the equations of motion).
 */
void
FGInterface::update ()
{
  update(1);
}


bool FGInterface::update( int multi_loop ) {
    cout << "dummy update() ... SHOULDN'T BE CALLED!" << endl;
    return false;
}


void FGInterface::_updateGeodeticPosition( double lat, double lon, double alt )
{
    double lat_geoc, sl_radius;

    // cout << "starting sea level rad = " << get_Sea_level_radius() << endl;

    sgGeodToGeoc( lat, alt * SG_FEET_TO_METER, &sl_radius, &lat_geoc );

    SG_LOG( SG_FLIGHT, SG_DEBUG, "lon = " << lon 
	    << " lat_geod = " << lat
	    << " lat_geoc = " << lat_geoc
	    << " alt = " << alt 
	    << " sl_radius = " << sl_radius * SG_METER_TO_FEET
	    << " Equator = " << SG_EQUATORIAL_RADIUS_FT );

    _set_Geocentric_Position( lat_geoc, lon, 
			      sl_radius * SG_METER_TO_FEET + alt );
	
    _set_Geodetic_Position( lat, lon, alt );

    _set_Sea_level_radius( sl_radius * SG_METER_TO_FEET );
    _set_Runway_altitude( scenery.get_cur_elev() * SG_METER_TO_FEET );

    _set_sin_lat_geocentric( lat_geoc );
    _set_cos_lat_geocentric( lat_geoc );

    _set_sin_cos_longitude( lon );

    _set_sin_cos_latitude( lat );

    /* Norman's code for slope of the terrain */
    /* needs to be tested -- get it on the HUD and taxi around */
    /* double *tnorm = scenery.cur_normal;

       double sy = sin ( -get_Psi() ) ;
       double cy = cos ( -get_Psi() ) ;

       double phitb, thetatb, psitb;
       if ( tnorm[1] != 0.0 ) {
           psitb = -atan2 ( tnorm[0], tnorm[1] );
       }
       if ( tnorm[2] != 0.0 ) {	
	   thetatb =  atan2 ( tnorm[0] * cy - tnorm[1] * sy, tnorm[2] );
	   phitb = -atan2 ( tnorm[1] * cy + tnorm[0] * sy, tnorm[2] );  
       }	
	
       _set_terrain_slope(phitb, thetatb, psitb) 
     */
}


void FGInterface::_updateGeocentricPosition( double lat_geoc, double lon,
					     double alt )
{
    double lat_geod, tmp_alt, sl_radius1, sl_radius2, tmp_lat_geoc;

    // cout << "starting sea level rad = " << get_Sea_level_radius() << endl;

    sgGeocToGeod( lat_geoc, ( get_Sea_level_radius() + alt ) * SG_FEET_TO_METER,
		  &lat_geod, &tmp_alt, &sl_radius1 );
    sgGeodToGeoc( lat_geod, alt * SG_FEET_TO_METER, &sl_radius2, &tmp_lat_geoc );

    SG_LOG( SG_FLIGHT, SG_DEBUG, "lon = " << lon 
	    << " lat_geod = " << lat_geod
	    << " lat_geoc = " << lat_geoc
	    << " alt = " << alt 
	    << " tmp_alt = " << tmp_alt * SG_METER_TO_FEET
	    << " sl_radius1 = " << sl_radius1 * SG_METER_TO_FEET
	    << " sl_radius2 = " << sl_radius2 * SG_METER_TO_FEET
	    << " Equator = " << SG_EQUATORIAL_RADIUS_FT );

    _set_Geocentric_Position( lat_geoc, lon, 
			      sl_radius2 * SG_METER_TO_FEET + alt );
	
    _set_Geodetic_Position( lat_geod, lon, alt );

    _set_Sea_level_radius( sl_radius2 * SG_METER_TO_FEET );
    _set_Runway_altitude( scenery.get_cur_elev() * SG_METER_TO_FEET );

    _set_sin_lat_geocentric( lat_geoc );
    _set_cos_lat_geocentric( lat_geoc );

    _set_sin_cos_longitude( lon );

    _set_sin_cos_latitude( lat_geod );

    /* Norman's code for slope of the terrain */
    /* needs to be tested -- get it on the HUD and taxi around */
    /* double *tnorm = scenery.cur_normal;

       double sy = sin ( -get_Psi() ) ;
       double cy = cos ( -get_Psi() ) ;

       double phitb, thetatb, psitb;
       if ( tnorm[1] != 0.0 ) {
           psitb = -atan2 ( tnorm[0], tnorm[1] );
       }
       if ( tnorm[2] != 0.0 ) {	
	   thetatb =  atan2 ( tnorm[0] * cy - tnorm[1] * sy, tnorm[2] );
	   phitb = -atan2 ( tnorm[1] * cy + tnorm[0] * sy, tnorm[2] );  
       }	
	
       _set_terrain_slope(phitb, thetatb, psitb) 
     */
}


// Extrapolate fdm based on time_offset (in usec)
void FGInterface::extrapolate( int time_offset ) {
    double dt = time_offset / 1000000.0;

    // -dw- metrowerks complains about ambiguous access, not critical
    // to keep this ;)
#ifndef __MWERKS__
    cout << "extrapolating FDM by dt = " << dt << endl;
#endif

    double lat = geodetic_position_v[0] + geocentric_rates_v[0] * dt;
    double lat_geoc = geocentric_position_v[0] + geocentric_rates_v[0] * dt;

    double lon = geodetic_position_v[1] + geocentric_rates_v[1] * dt;
    double lon_geoc = geocentric_position_v[1] + geocentric_rates_v[1] * dt;

    double alt = geodetic_position_v[2] + geocentric_rates_v[2] * dt;
    double radius = geocentric_position_v[2] + geocentric_rates_v[2] * dt;

    geodetic_position_v[0] = lat;
    geocentric_position_v[0] = lat_geoc;

    geodetic_position_v[1] = lon;
    geocentric_position_v[1] = lon_geoc;

    geodetic_position_v[2] = alt;
    geocentric_position_v[2] = radius;
}


// Set the altitude (force)
void fgFDMForceAltitude(const string &model, double alt_meters) {
    SG_LOG(SG_FLIGHT,SG_INFO, "fgFDMForceAltitude: " << alt_meters );

    double sea_level_radius_meters;
    double lat_geoc;

    // Set the FG variables first
    sgGeodToGeoc( base_fdm_state.get_Latitude(), alt_meters, 
		  &sea_level_radius_meters, &lat_geoc);

    base_fdm_state.set_Altitude( alt_meters * SG_METER_TO_FEET );
    base_fdm_state.set_Sea_level_radius( sea_level_radius_meters *
					 SG_METER_TO_FEET ); 
		
    cur_fdm_state->set_Altitude( alt_meters * SG_METER_TO_FEET );
    cur_fdm_state->set_Sea_level_radius( sea_level_radius_meters * 
                                         SG_METER_TO_FEET );			  

    // additional work needed for some flight models
    if ( model == "larcsim" ) {
	ls_ForceAltitude( base_fdm_state.get_Altitude() );
    }
}


// Positions
void FGInterface::set_Latitude(double lat) {
    geodetic_position_v[0] = lat;
}

void FGInterface::set_Longitude(double lon) {
    geodetic_position_v[1] = lon;
}

void FGInterface::set_Altitude(double alt) {
    geodetic_position_v[2] = alt;
}

void FGInterface::set_AltitudeAGL(double altagl) {
    altitude_agl=altagl;
}

// Velocities
void FGInterface::set_V_calibrated_kts(double vc) {
    v_calibrated_kts = vc;
}

void FGInterface::set_Mach_number(double mach) {
    mach_number = mach;
}

void FGInterface::set_Velocities_Local( double north, 
					double east, 
					double down ){
    v_local_v[0] = north;
    v_local_v[1] = east;
    v_local_v[2] = down;
}

void FGInterface::set_Velocities_Wind_Body( double u, 
					    double v, 
					    double w){
    v_wind_body_v[0] = u;
    v_wind_body_v[1] = v;
    v_wind_body_v[2] = w;
}

// Euler angles 
void FGInterface::set_Euler_Angles( double phi, 
				    double theta, 
				    double psi ) {
    euler_angles_v[0] = phi;
    euler_angles_v[1] = theta;
    euler_angles_v[2] = psi;                                            
}  

// Flight Path
void FGInterface::set_Climb_Rate( double roc) {
    climb_rate = roc;
}

void FGInterface::set_Gamma_vert_rad( double gamma) {
    gamma_vert_rad = gamma;
}

// Earth
void FGInterface::set_Sea_level_radius(double slr) {
    sea_level_radius = slr;
}

void FGInterface::set_Runway_altitude(double ralt) {
    runway_altitude = ralt;
}

void FGInterface::set_Static_pressure(double p) { static_pressure = p; }
void FGInterface::set_Static_temperature(double T) { static_temperature = T; }
void FGInterface::set_Density(double rho) { density = rho; }

void FGInterface::set_Velocities_Local_Airmass (double wnorth, 
						double weast, 
						double wdown ) {
    v_local_airmass_v[0] = wnorth;
    v_local_airmass_v[1] = weast;
    v_local_airmass_v[2] = wdown;
}


void FGInterface::_busdump(void) {

    SG_LOG(SG_FLIGHT,SG_INFO,"d_pilot_rp_body_v[3]: " << d_pilot_rp_body_v[0] << ", " << d_pilot_rp_body_v[1] << ", " << d_pilot_rp_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"d_cg_rp_body_v[3]: " << d_cg_rp_body_v[0] << ", " << d_cg_rp_body_v[1] << ", " << d_cg_rp_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"f_body_total_v[3]: " << f_body_total_v[0] << ", " << f_body_total_v[1] << ", " << f_body_total_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"f_local_total_v[3]: " << f_local_total_v[0] << ", " << f_local_total_v[1] << ", " << f_local_total_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"f_aero_v[3]: " << f_aero_v[0] << ", " << f_aero_v[1] << ", " << f_aero_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"f_engine_v[3]: " << f_engine_v[0] << ", " << f_engine_v[1] << ", " << f_engine_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"f_gear_v[3]: " << f_gear_v[0] << ", " << f_gear_v[1] << ", " << f_gear_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"m_total_rp_v[3]: " << m_total_rp_v[0] << ", " << m_total_rp_v[1] << ", " << m_total_rp_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"m_total_cg_v[3]: " << m_total_cg_v[0] << ", " << m_total_cg_v[1] << ", " << m_total_cg_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"m_aero_v[3]: " << m_aero_v[0] << ", " << m_aero_v[1] << ", " << m_aero_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"m_engine_v[3]: " << m_engine_v[0] << ", " << m_engine_v[1] << ", " << m_engine_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"m_gear_v[3]: " << m_gear_v[0] << ", " << m_gear_v[1] << ", " << m_gear_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_dot_local_v[3]: " << v_dot_local_v[0] << ", " << v_dot_local_v[1] << ", " << v_dot_local_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_dot_body_v[3]: " << v_dot_body_v[0] << ", " << v_dot_body_v[1] << ", " << v_dot_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"a_cg_body_v[3]: " << a_cg_body_v[0] << ", " << a_cg_body_v[1] << ", " << a_cg_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"a_pilot_body_v[3]: " << a_pilot_body_v[0] << ", " << a_pilot_body_v[1] << ", " << a_pilot_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"n_cg_body_v[3]: " << n_cg_body_v[0] << ", " << n_cg_body_v[1] << ", " << n_cg_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"n_pilot_body_v[3]: " << n_pilot_body_v[0] << ", " << n_pilot_body_v[1] << ", " << n_pilot_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"omega_dot_body_v[3]: " << omega_dot_body_v[0] << ", " << omega_dot_body_v[1] << ", " << omega_dot_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_local_v[3]: " << v_local_v[0] << ", " << v_local_v[1] << ", " << v_local_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_local_rel_ground_v[3]: " << v_local_rel_ground_v[0] << ", " << v_local_rel_ground_v[1] << ", " << v_local_rel_ground_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_local_airmass_v[3]: " << v_local_airmass_v[0] << ", " << v_local_airmass_v[1] << ", " << v_local_airmass_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_local_rel_airmass_v[3]: " << v_local_rel_airmass_v[0] << ", " << v_local_rel_airmass_v[1] << ", " << v_local_rel_airmass_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_local_gust_v[3]: " << v_local_gust_v[0] << ", " << v_local_gust_v[1] << ", " << v_local_gust_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"v_wind_body_v[3]: " << v_wind_body_v[0] << ", " << v_wind_body_v[1] << ", " << v_wind_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"omega_body_v[3]: " << omega_body_v[0] << ", " << omega_body_v[1] << ", " << omega_body_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"omega_local_v[3]: " << omega_local_v[0] << ", " << omega_local_v[1] << ", " << omega_local_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"omega_total_v[3]: " << omega_total_v[0] << ", " << omega_total_v[1] << ", " << omega_total_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"euler_rates_v[3]: " << euler_rates_v[0] << ", " << euler_rates_v[1] << ", " << euler_rates_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"geocentric_rates_v[3]: " << geocentric_rates_v[0] << ", " << geocentric_rates_v[1] << ", " << geocentric_rates_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"geocentric_position_v[3]: " << geocentric_position_v[0] << ", " << geocentric_position_v[1] << ", " << geocentric_position_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"geodetic_position_v[3]: " << geodetic_position_v[0] << ", " << geodetic_position_v[1] << ", " << geodetic_position_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"euler_angles_v[3]: " << euler_angles_v[0] << ", " << euler_angles_v[1] << ", " << euler_angles_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"d_cg_rwy_local_v[3]: " << d_cg_rwy_local_v[0] << ", " << d_cg_rwy_local_v[1] << ", " << d_cg_rwy_local_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"d_cg_rwy_rwy_v[3]: " << d_cg_rwy_rwy_v[0] << ", " << d_cg_rwy_rwy_v[1] << ", " << d_cg_rwy_rwy_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"d_pilot_rwy_local_v[3]: " << d_pilot_rwy_local_v[0] << ", " << d_pilot_rwy_local_v[1] << ", " << d_pilot_rwy_local_v[2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"d_pilot_rwy_rwy_v[3]: " << d_pilot_rwy_rwy_v[0] << ", " << d_pilot_rwy_rwy_v[1] << ", " << d_pilot_rwy_rwy_v[2]);

    SG_LOG(SG_FLIGHT,SG_INFO,"t_local_to_body_m[0][3]: " << t_local_to_body_m[0][0] << ", " << t_local_to_body_m[0][1] << ", " << t_local_to_body_m[0][2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"t_local_to_body_m[1][3]: " << t_local_to_body_m[1][0] << ", " << t_local_to_body_m[1][1] << ", " << t_local_to_body_m[1][2]);
    SG_LOG(SG_FLIGHT,SG_INFO,"t_local_to_body_m[2][3]: " << t_local_to_body_m[2][0] << ", " << t_local_to_body_m[2][1] << ", " << t_local_to_body_m[2][2]);

    SG_LOG(SG_FLIGHT,SG_INFO,"mass: " << mass );
    SG_LOG(SG_FLIGHT,SG_INFO,"i_xx: " << i_xx );
    SG_LOG(SG_FLIGHT,SG_INFO,"i_yy: " << i_yy );
    SG_LOG(SG_FLIGHT,SG_INFO,"i_zz: " << i_zz );
    SG_LOG(SG_FLIGHT,SG_INFO,"i_xz: " << i_xz );
    SG_LOG(SG_FLIGHT,SG_INFO,"nlf: " << nlf );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_rel_wind: " << v_rel_wind );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_true_kts: " << v_true_kts );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_rel_ground: " << v_rel_ground );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_inertial: " << v_inertial );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_ground_speed: " << v_ground_speed );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_equiv: " << v_equiv );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_equiv_kts: " << v_equiv_kts );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_calibrated: " << v_calibrated );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_calibrated_kts: " << v_calibrated_kts );
    SG_LOG(SG_FLIGHT,SG_INFO,"gravity: " << gravity );
    SG_LOG(SG_FLIGHT,SG_INFO,"centrifugal_relief: " << centrifugal_relief );
    SG_LOG(SG_FLIGHT,SG_INFO,"alpha: " << alpha );
    SG_LOG(SG_FLIGHT,SG_INFO,"beta: " << beta );
    SG_LOG(SG_FLIGHT,SG_INFO,"alpha_dot: " << alpha_dot );
    SG_LOG(SG_FLIGHT,SG_INFO,"beta_dot: " << beta_dot );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_alpha: " << cos_alpha );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_alpha: " << sin_alpha );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_beta: " << cos_beta );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_beta: " << sin_beta );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_phi: " << cos_phi );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_phi: " << sin_phi );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_theta: " << cos_theta );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_theta: " << sin_theta );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_psi: " << cos_psi );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_psi: " << sin_psi );
    SG_LOG(SG_FLIGHT,SG_INFO,"gamma_vert_rad: " << gamma_vert_rad );
    SG_LOG(SG_FLIGHT,SG_INFO,"gamma_horiz_rad: " << gamma_horiz_rad );
    SG_LOG(SG_FLIGHT,SG_INFO,"sigma: " << sigma );
    SG_LOG(SG_FLIGHT,SG_INFO,"density: " << density );
    SG_LOG(SG_FLIGHT,SG_INFO,"v_sound: " << v_sound );
    SG_LOG(SG_FLIGHT,SG_INFO,"mach_number: " << mach_number );
    SG_LOG(SG_FLIGHT,SG_INFO,"static_pressure: " << static_pressure );
    SG_LOG(SG_FLIGHT,SG_INFO,"total_pressure: " << total_pressure );
    SG_LOG(SG_FLIGHT,SG_INFO,"impact_pressure: " << impact_pressure );
    SG_LOG(SG_FLIGHT,SG_INFO,"dynamic_pressure: " << dynamic_pressure );
    SG_LOG(SG_FLIGHT,SG_INFO,"static_temperature: " << static_temperature );
    SG_LOG(SG_FLIGHT,SG_INFO,"total_temperature: " << total_temperature );
    SG_LOG(SG_FLIGHT,SG_INFO,"sea_level_radius: " << sea_level_radius );
    SG_LOG(SG_FLIGHT,SG_INFO,"earth_position_angle: " << earth_position_angle );
    SG_LOG(SG_FLIGHT,SG_INFO,"runway_altitude: " << runway_altitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"runway_latitude: " << runway_latitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"runway_longitude: " << runway_longitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"runway_heading: " << runway_heading );
    SG_LOG(SG_FLIGHT,SG_INFO,"radius_to_rwy: " << radius_to_rwy );
    SG_LOG(SG_FLIGHT,SG_INFO,"climb_rate: " << climb_rate );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_lat_geocentric: " << sin_lat_geocentric );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_lat_geocentric: " << cos_lat_geocentric );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_longitude: " << sin_longitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_longitude: " << cos_longitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"sin_latitude: " << sin_latitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"cos_latitude: " << cos_latitude );
    SG_LOG(SG_FLIGHT,SG_INFO,"altitude_agl: " << altitude_agl );
}


void fgToggleFDMdataLogging(void) {
  cur_fdm_state->ToggleDataLogging();
}
