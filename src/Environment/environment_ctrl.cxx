// environment_ctrl.cxx -- manager for natural environment information.
//
// Written by David Megginson, started February 2002.
//
// Copyright (C) 2002  David Megginson - david@megginson.com
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

#include <simgear/debug/logstream.hxx>

#include <stdlib.h>
#include <algorithm>

#include <simgear/structure/commands.hxx>
#include <simgear/structure/exception.hxx>

#include <Airports/simple.hxx>
#include <Main/fg_props.hxx>
#include <Main/util.hxx>

#include "environment_mgr.hxx"
#include "environment_ctrl.hxx"

SG_USING_STD(sort);



////////////////////////////////////////////////////////////////////////
// Implementation of FGEnvironmentCtrl abstract base class.
////////////////////////////////////////////////////////////////////////

FGEnvironmentCtrl::FGEnvironmentCtrl ()
  : _environment(0),
    _lon_deg(0),
    _lat_deg(0),
    _elev_ft(0)
{
}

FGEnvironmentCtrl::~FGEnvironmentCtrl ()
{
}

void
FGEnvironmentCtrl::setEnvironment (FGEnvironment * environment)
{
  _environment = environment;
}

void
FGEnvironmentCtrl::setLongitudeDeg (double lon_deg)
{
  _lon_deg = lon_deg;
}

void
FGEnvironmentCtrl::setLatitudeDeg (double lat_deg)
{
  _lat_deg = lat_deg;
}

void
FGEnvironmentCtrl::setElevationFt (double elev_ft)
{
  _elev_ft = elev_ft;
}

void
FGEnvironmentCtrl::setPosition (double lon_deg, double lat_deg, double elev_ft)
{
  _lon_deg = lon_deg;
  _lat_deg = lat_deg;
  _elev_ft = elev_ft;
}



////////////////////////////////////////////////////////////////////////
// Implementation of FGUserDefEnvironmentCtrl.
////////////////////////////////////////////////////////////////////////

FGUserDefEnvironmentCtrl::FGUserDefEnvironmentCtrl ()
  : _base_wind_speed_node(0),
    _gust_wind_speed_node(0),
    _current_wind_speed_kt(0),
    _delta_wind_speed_kt(0)
{
}

FGUserDefEnvironmentCtrl::~FGUserDefEnvironmentCtrl ()
{
}

void
FGUserDefEnvironmentCtrl::init ()
{
				// Fill in some defaults.
  if (!fgHasNode("/environment/params/base-wind-speed-kt"))
    fgSetDouble("/environment/params/base-wind-speed-kt",
		fgGetDouble("/environment/wind-speed-kt"));
  if (!fgHasNode("/environment/params/gust-wind-speed-kt"))
    fgSetDouble("/environment/params/gust-wind-speed-kt",
		fgGetDouble("/environment/params/base-wind-speed-kt"));

  _base_wind_speed_node =
    fgGetNode("/environment/params/base-wind-speed-kt", true);
  _gust_wind_speed_node =
    fgGetNode("/environment/params/gust-wind-speed-kt", true);

  _current_wind_speed_kt = _base_wind_speed_node->getDoubleValue();
  _delta_wind_speed_kt = 0.1;
}

void
FGUserDefEnvironmentCtrl::update (double dt)
{
  double base_wind_speed = _base_wind_speed_node->getDoubleValue();
  double gust_wind_speed = _gust_wind_speed_node->getDoubleValue();

  if (gust_wind_speed < base_wind_speed) {
      gust_wind_speed = base_wind_speed;
      _gust_wind_speed_node->setDoubleValue(gust_wind_speed);
  }

  if (base_wind_speed == gust_wind_speed) {
    _current_wind_speed_kt = base_wind_speed;
  } else {
    int rn = rand() % 128;
    int sign = (_delta_wind_speed_kt < 0 ? -1 : 1);
    double gust = _current_wind_speed_kt - base_wind_speed;
    double incr = gust / 50;

    if (rn == 0)
      _delta_wind_speed_kt = - _delta_wind_speed_kt;
    else if (rn < 4)
      _delta_wind_speed_kt -= incr * sign;
    else if (rn < 16)
      _delta_wind_speed_kt += incr * sign;

    _current_wind_speed_kt += _delta_wind_speed_kt;

    if (_current_wind_speed_kt < base_wind_speed) {
      _current_wind_speed_kt = base_wind_speed;
      _delta_wind_speed_kt = 0.01;
    } else if (_current_wind_speed_kt > gust_wind_speed) {
      _current_wind_speed_kt = gust_wind_speed;
      _delta_wind_speed_kt = -0.01;
    }
  }
  
  if (_environment != 0)
    _environment->set_wind_speed_kt(_current_wind_speed_kt);
}



////////////////////////////////////////////////////////////////////////
// Implementation of FGInterpolateEnvironmentCtrl.
////////////////////////////////////////////////////////////////////////

FGInterpolateEnvironmentCtrl::FGInterpolateEnvironmentCtrl ()
{
}

FGInterpolateEnvironmentCtrl::~FGInterpolateEnvironmentCtrl ()
{
    unsigned int i;
    for (i = 0; i < _boundary_table.size(); i++)
        delete _boundary_table[i];
    for (i = 0; i < _aloft_table.size(); i++)
        delete _aloft_table[i];
}



void
FGInterpolateEnvironmentCtrl::init ()
{
    read_table(fgGetNode("/environment/config/boundary", true),
               _boundary_table);
    read_table(fgGetNode("/environment/config/aloft", true),
               _aloft_table);
}

void
FGInterpolateEnvironmentCtrl::reinit ()
{
    unsigned int i;
    for (i = 0; i < _boundary_table.size(); i++)
        delete _boundary_table[i];
    for (i = 0; i < _aloft_table.size(); i++)
        delete _aloft_table[i];
    _boundary_table.clear();
    _aloft_table.clear();
    init();
}

void
FGInterpolateEnvironmentCtrl::read_table (const SGPropertyNode * node,
                                          vector<bucket *> &table)
{
    for (int i = 0; i < node->nChildren(); i++) {
        const SGPropertyNode * child = node->getChild(i);
        if ( strcmp(child->getName(), "entry") == 0
	     && child->getStringValue("elevation-ft", "")[0] != '\0'
	     && ( child->getDoubleValue("elevation-ft") > 0.1 || i == 0 ) )
	{
            bucket * b = new bucket;
            if (i > 0)
                b->environment.copy(table[i-1]->environment);
            b->environment.read(child);
            b->altitude_ft = b->environment.get_elevation_ft();
            table.push_back(b);
        }
    }
    sort(table.begin(), table.end());
}

void
FGInterpolateEnvironmentCtrl::update (double delta_time_sec)
{
                                // FIXME
    double altitude_ft = fgGetDouble("/position/altitude-ft");
    double altitude_agl_ft = fgGetDouble("/position/altitude-agl-ft");
    double boundary_transition =
        fgGetDouble("/environment/config/boundary-transition-ft", 500);

    // double ground_elevation_ft = altitude_ft - altitude_agl_ft;

    int length = _boundary_table.size();

    if (length > 0) {
                                // boundary table
        double boundary_limit = _boundary_table[length-1]->altitude_ft;
        if (boundary_limit >= altitude_agl_ft) {
            do_interpolate(_boundary_table, altitude_agl_ft,
                           _environment);
            return;
        } else if ((boundary_limit + boundary_transition) >= altitude_agl_ft) {
                                // both tables
            do_interpolate(_boundary_table, altitude_agl_ft, &env1);
            do_interpolate(_aloft_table, altitude_ft, &env2);
            double fraction =
                (altitude_agl_ft - boundary_limit) / boundary_transition;
            interpolate(&env1, &env2, fraction, _environment);
            return;
        }
    }

                                // aloft table
    do_interpolate(_aloft_table, altitude_ft, _environment);
}

void
FGInterpolateEnvironmentCtrl::do_interpolate (vector<bucket *> &table,
                                              double altitude_ft,
                                              FGEnvironment * environment)
{
    int length = table.size();
    if (length == 0)
        return;

                                // Boundary conditions
    if ((length == 1) || (table[0]->altitude_ft >= altitude_ft)) {
        environment->copy(table[0]->environment);
        return;
    } else if (table[length-1]->altitude_ft <= altitude_ft) {
        environment->copy(table[length-1]->environment);
        return;
    }
        
                                // Search the interpolation table
    for (int i = 0; i < length - 1; i++) {
        if ((i == length - 1) || (table[i]->altitude_ft <= altitude_ft)) {
                FGEnvironment * env1 = &(table[i]->environment);
                FGEnvironment * env2 = &(table[i+1]->environment);
                double fraction;
                if (table[i]->altitude_ft == table[i+1]->altitude_ft)
                    fraction = 1.0;
                else
                    fraction =
                        ((altitude_ft - table[i]->altitude_ft) /
                         (table[i+1]->altitude_ft - table[i]->altitude_ft));
                interpolate(env1, env2, fraction, environment);

                return;
        }
    }
}

bool
FGInterpolateEnvironmentCtrl::bucket::operator< (const bucket &b) const
{
    return (altitude_ft < b.altitude_ft);
}



////////////////////////////////////////////////////////////////////////
// Implementation of FGMetarEnvironmentCtrl.
////////////////////////////////////////////////////////////////////////

FGMetarEnvironmentCtrl::FGMetarEnvironmentCtrl ()
    : env( new FGInterpolateEnvironmentCtrl ),
      _icao( fgGetString("/sim/presets/airport-id") ),
      search_interval_sec( 60.0 ),        // 1 minute
      same_station_interval_sec( 900.0 ), // 15 minutes
      search_elapsed( 9999.0 ),
      fetch_elapsed( 9999.0 ),
      proxy_host( fgGetNode("/sim/presets/proxy/host", true) ),
      proxy_port( fgGetNode("/sim/presets/proxy/port", true) ),
      proxy_auth( fgGetNode("/sim/presets/proxy/authentication", true) )
{
#ifdef ENABLE_THREADS
    thread = new MetarThread(this);
    thread->start();
#endif // ENABLE_THREADS
}

FGMetarEnvironmentCtrl::~FGMetarEnvironmentCtrl ()
{
#ifdef ENABLE_THREADS
   thread->cancel();
   thread->join();
#endif // ENABLE_THREADS

   delete env;
   env = NULL;
}


// use a "command" to set station temp at station elevation
static void set_temp_at_altitude( float temp_degc, float altitude_ft ) {
    SGPropertyNode args;
    SGPropertyNode *node = args.getNode("temp-degc", 0, true);
    node->setFloatValue( temp_degc );
    node = args.getNode("altitude-ft", 0, true);
    node->setFloatValue( altitude_ft );
    globals->get_commands()->execute("set-outside-air-temp-degc", &args);
}


static void set_dewpoint_at_altitude( float dewpoint_degc, float altitude_ft ) {
    SGPropertyNode args;
    SGPropertyNode *node = args.getNode("dewpoint-degc", 0, true);
    node->setFloatValue( dewpoint_degc );
    node = args.getNode("altitude-ft", 0, true);
    node->setFloatValue( altitude_ft );
    globals->get_commands()->execute("set-dewpoint-temp-degc", &args);
}


void
FGMetarEnvironmentCtrl::update_env_config ()
{
    double wind_dir1 = fgGetDouble("/environment/metar/base-wind-range-from");
    double wind_dir2 = fgGetDouble("/environment/metar/base-wind-range-to");

    wind_dir1 = fmod (wind_dir1 + 180.0, 360.0);
    wind_dir2 = fmod (wind_dir2 + 180.0, 360.0);

    fgSetupWind( wind_dir1, wind_dir2,
                 fgGetDouble("/environment/metar/base-wind-speed-kt"),
                 fgGetDouble("/environment/metar/gust-wind-speed-kt") );

    fgDefaultWeatherValue( "visibility-m",
                           fgGetDouble("/environment/metar/min-visibility-m") );
    set_temp_at_altitude( fgGetDouble("/environment/metar/temperature-degc"),
                          station_elevation_ft );
    set_dewpoint_at_altitude( fgGetDouble("/environment/metar/dewpoint-degc"),
                              station_elevation_ft );
    fgDefaultWeatherValue( "pressure-sea-level-inhg",
                           fgGetDouble("/environment/metar/pressure-inhg") );
}

void
FGMetarEnvironmentCtrl::init ()
{
    const SGPropertyNode *longitude
        = fgGetNode( "/position/longitude-deg", true );
    const SGPropertyNode *latitude
        = fgGetNode( "/position/latitude-deg", true );

    bool found_metar = false;
    while ( !found_metar ) {
        FGAirport a = globals->get_airports()
            ->search( longitude->getDoubleValue(),
                      latitude->getDoubleValue(),
                      true );
        if ( fetch_data( a.id ) ) {
            cout << "closest station w/ metar = " << a.id << endl;
            last_apt = a;
            _icao = a.id;
            search_elapsed = 0.0;
            fetch_elapsed = 0.0;
            update_env_config();
            env->init();
            found_metar = true;
        } else {
            // mark as no metar so it doesn't show up in subsequent
            // searches.
            cout << "no metar at metar = " << a.id << endl;
            globals->get_airports()->no_metar( a.id );
        }
    }
}

void
FGMetarEnvironmentCtrl::reinit ()
{
#if 0
    update_env_config();
#endif

    env->reinit();
}

void
FGMetarEnvironmentCtrl::update(double delta_time_sec)
{
    static const SGPropertyNode *longitude
        = fgGetNode( "/position/longitude-deg", true );
    static const SGPropertyNode *latitude
        = fgGetNode( "/position/latitude-deg", true );
    search_elapsed += delta_time_sec;
    fetch_elapsed += delta_time_sec;
    if ( search_elapsed > search_interval_sec ) {
        FGAirport a = globals->get_airports()
            ->search( longitude->getDoubleValue(),
                      latitude->getDoubleValue(),
                      true );
        if ( last_apt.id != a.id
             || fetch_elapsed > same_station_interval_sec )
        {
            if ( fetch_data( a.id ) ) {
                cout << "closest station w/ metar = " << a.id << endl;
                last_apt = a;
                _icao = a.id;
                search_elapsed = 0.0;
                fetch_elapsed = 0.0;
                update_env_config();
                env->reinit();
            } else {
                // mark as no metar so it doesn't show up in subsequent
                // searches.
                cout << "no metar at metar = " << a.id << endl;
                globals->get_airports()->no_metar( a.id );
            }
        } else {
            search_elapsed = 0.0;
            // cout << "same station, waiting = "
            //      << same_station_interval_sec - fetch_elapsed << endl;
        }
    }

    env->update(delta_time_sec);
}

void
FGMetarEnvironmentCtrl::setEnvironment (FGEnvironment * environment)
{
    env->setEnvironment(environment);
}

bool
FGMetarEnvironmentCtrl::fetch_data (const string &icao)
{
    char s[128];
    double d, dt;
    int i;

    if ((icao == "") && (_icao == "")) {
        _icao = fgGetString("/sim/presets/airport-id");

    } else if (icao != "") {
        _icao = icao;
    }

    // fetch station elevation if exists
    FGAirport a = globals->get_airports()->search( _icao );
    station_elevation_ft = a.elevation;

    // fetch current metar data
    SGMetar *m = NULL;
#ifdef ENABLE_THREADS

    // We are only interested in the latest metar report
    // FIXME: Do we want to keep the latest valid report instead?
    while (!metar_queue.empty()) {
 
        if (m != NULL)
            delete m;

        m = metar_queue.pop();
    }

    if ( m != NULL ) {

#else
    try {
        string host = proxy_host->getStringValue();
        string auth = proxy_auth->getStringValue();
        string port = proxy_port->getStringValue();
        m = new SGMetar( _icao, host, port, auth);

#endif // ENABLE_THREADS

        d = m->getMinVisibility().getVisibility_m();
        d = (d != SGMetarNaN) ? d : 10000;
        fgSetDouble("/environment/metar/min-visibility-m", d);

        dt =  m->getMaxVisibility().getVisibility_m();
        d = (dt != SGMetarNaN) ? dt : d;
        fgSetDouble("/environment/metar/max-visibility-m", d);

        SGMetarVisibility *dirvis = m->getDirVisibility();
        for (i = 0; i < 8; i++, dirvis++) {
            const char *min = "/environment/metar/visibility[%d]/min-m";
            const char *max = "/environment/metar/visibility[%d]/max-m";
            char s[128];

            d = dirvis->getVisibility_m();
            d = (d != SGMetarNaN) ? d : 10000;

            snprintf(s, 128, min, i);
            fgSetDouble(s, d);
            snprintf(s, 128, max, i);
            fgSetDouble(s, d);
        }

        i = m->getWindDir();
        if ( i == -1 ) {
            fgSetInt("/environment/metar/base-wind-range-from",
                        m->getWindRangeFrom() );
            fgSetInt("/environment/metar/base-wind-range-to",
                        m->getWindRangeTo() );
        } else {
            fgSetInt("/environment/metar/base-wind-range-from", i);
            fgSetInt("/environment/metar/base-wind-range-to", i);
        }
        fgSetDouble("/environment/metar/base-wind-speed-kt",
                    m->getWindSpeed_kt() );

        d = m->getGustSpeed_kt();
        d = (d != SGMetarNaN) ? d : 0.0;
        fgSetDouble("/environment/metar/gust-wind-speed-kt", d);

        d = m->getTemperature_C();
        if (d != SGMetarNaN) {
            dt = m->getDewpoint_C();
            dt = (dt != SGMetarNaN) ? dt : 0.0;
            fgSetDouble("/environment/metar/dewpoint-degc", dt);
            fgSetDouble("/environment/metar/rel-humidity-norm",
                        m->getRelHumidity() );
        }   
        d = (d != SGMetarNaN) ? d : 15.0;
        fgSetDouble("/environment/metar/temperature-degc", d);

        d = m->getPressure_inHg();
        d = (d != SGMetarNaN) ? d : 30.0;
        fgSetDouble("/environment/metar/pressure-inhg", d);

        vector<SGMetarCloud> cv = m->getClouds();
        vector<SGMetarCloud>::iterator cloud;

        const char *cl = "/environment/clouds/layer[%i]";
        for (i = 0, cloud = cv.begin(); cloud != cv.end(); cloud++, i++) {
            const char *coverage_string[5] = 
                          { "clear", "few", "scattered", "broken", "overcast" };
            const double thickness[5] = { 0, 65, 600,750, 1000};
            int q;

            snprintf(s, 128, cl, i);
            strncat(s, "/coverage", 128);
            q = cloud->getCoverage();
            q = (q != -1 ) ? q : 0;
            fgSetString(s, coverage_string[q] );

            snprintf(s, 128, cl, i);
            strncat(s, "/elevation-ft", 128);
            d = cloud->getAltitude_ft();
            d = (d != SGMetarNaN) ? d : -9999;
            fgSetDouble(s, d + station_elevation_ft);

            snprintf(s, 128, cl, i);
            strncat(s, "/thickness-ft", 128);
            fgSetDouble(s, thickness[q]);

            snprintf(s, 128, cl, i);
            strncat(s, "/span-m", 128);
            fgSetDouble(s, 40000.0);
        }
        for (; i < FGEnvironmentMgr::MAX_CLOUD_LAYERS; i++) {
            snprintf(s, 128, cl, i);
            strncat(s, "/coverage", 128);
            fgSetString(s, "clear");

            snprintf(s, 128, cl, i);
            strncat(s, "/elevation-ft", 128);
            fgSetDouble(s, -9999);

            snprintf(s, 128, cl, i);
            strncat(s, "/thickness-ft", 128);
            fgSetDouble(s, 0);

            snprintf(s, 128, cl, i);
            strncat(s, "/span-m", 128);
            fgSetDouble(s, 40000.0);
        }

        delete m;

    }
#ifdef ENABLE_THREADS

    mutex.lock();
    metar_cond.signal();
    mutex.unlock();

    if (m == NULL)
        return false;

#else
    catch (const sg_io_exception& e) {
        SG_LOG( SG_GENERAL, SG_WARN, "Error fetching live weather data: "
                                      << e.getFormattedMessage().c_str() );
        return false;
    }
#endif // ENABLE_THREADS

    return true;
}

#ifdef ENABLE_THREADS
/**
 *
 */
void
FGMetarEnvironmentCtrl::MetarThread::run()
{
    SGMetar *m = NULL;

    // pthread_cleanup_push( metar_cleanup_handler, fetcher );
    while ( true )
    {
        set_cancel( SGThread::CANCEL_DISABLE );
        try
        {
            cout << "Fetching ..." << endl;
            // if (m != NULL)  m = NULL;
            string host = fetcher->proxy_host->getStringValue();
            string auth = fetcher->proxy_auth->getStringValue();
            string port = fetcher->proxy_port->getStringValue();
            m = new SGMetar( fetcher->_icao, host, port, auth );

        } catch (const sg_io_exception& e) {
            // SG_LOG( SG_GENERAL, SG_WARN, "Error fetching live weather data: "
            //                             << e.getFormattedMessage().c_str() );
            m = NULL;
        }
        set_cancel( SGThread::CANCEL_DEFERRED );

        fetcher->metar_queue.push( m );

        // Wait for the next frame signal before we fetch the next metar data
        fetcher->mutex.lock();
        fetcher->metar_cond.wait( fetcher->mutex );
        fetcher->mutex.unlock();
    }
    // pthread_cleanup_pop(1);
}

/**
 * Ensure mutex is unlocked.
 */
void
metar_cleanup_handler( void* arg )
{
    FGMetarEnvironmentCtrl* fetcher = (FGMetarEnvironmentCtrl*) arg;
    fetcher->mutex.unlock();
}
#endif // ENABLE_THREADS


// end of environment_ctrl.cxx
