// dme.cxx - distance-measuring equipment.
// Written by David Megginson, started 2003.
//
// This file is in the Public Domain and comes with no warranty.

#include <simgear/compiler.h>
#include <simgear/math/sg_geodesy.hxx>
#include <simgear/math/sg_random.h>

#include <Main/fg_props.hxx>
#include <Navaids/ilslist.hxx>
#include <Navaids/navlist.hxx>

#include "dme.hxx"


/**
 * Adjust the range.
 *
 * Start by calculating the radar horizon based on the elevation
 * difference, then clamp to the maximum, then add a fudge for
 * borderline reception.
 */
static double
adjust_range (double transmitter_elevation_ft, double aircraft_altitude_ft,
              double max_range_nm)
{
    double delta_elevation_ft =
        fabs(aircraft_altitude_ft - transmitter_elevation_ft);
    double range_nm = 1.23 * sqrt(delta_elevation_ft);
    if (range_nm > max_range_nm)
        range_nm = max_range_nm;
    double rand = sg_random();
    return range_nm + (range_nm * rand * rand);
}


DME::DME ()
    : _last_distance_nm(0),
      _last_frequency_mhz(-1),
      _time_before_search_sec(0),
      _transmitter_valid(false),
      _transmitter_elevation_ft(0),
      _transmitter_range_nm(0)
{
}

DME::~DME ()
{
}

void
DME::init ()
{
    _longitude_node = fgGetNode("/position/longitude-deg", true);
    _latitude_node = fgGetNode("/position/latitude-deg", true);
    _altitude_node = fgGetNode("/position/altitude-ft", true);
    _serviceable_node = fgGetNode("/instrumentation/dme/serviceable", true);
    _electrical_node = fgGetNode("/systems/electrical/outputs/dme", true);
    _source_node = fgGetNode("/instrumentation/dme/frequencies/source", true);
    _frequency_node =
        fgGetNode("/instrumentation/dme/frequencies/selected-mhz", true);

    _in_range_node = fgGetNode("/instrumentation/dme/in-range", true);
    _distance_node =
        fgGetNode("/instrumentation/dme/indicated-distance-nm", true);
    _speed_node =
        fgGetNode("/instrumentation/dme/indicated-ground-speed-kt", true);
    _time_node =
        fgGetNode("/instrumentation/dme/indicated-time-min", true);
}

void
DME::update (double delta_time_sec)
{
                                // Figure out the source
    const char * source = _source_node->getStringValue();
    if (source[0] == '\0') {
        source = "/instrumentation/dme/frequencies/selected-mhz";
        _source_node->setStringValue(source);
    }

                                // Get the frequency
    double frequency_mhz = fgGetDouble(source, 108.0);
    if (frequency_mhz != _last_frequency_mhz) {
        _time_before_search_sec = 0;
        _last_frequency_mhz = frequency_mhz;
    }

                                // Get the aircraft position
    double longitude_rad =
        _longitude_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double latitude_rad =
        _latitude_node->getDoubleValue() * SGD_DEGREES_TO_RADIANS;
    double altitude_m =
        _altitude_node->getDoubleValue() * SG_FEET_TO_METER;

                                // On timeout, scan again
    _time_before_search_sec -= delta_time_sec;
    if (_time_before_search_sec < 0)
        search(frequency_mhz, longitude_rad,
               latitude_rad, altitude_m);

                                // If it's off, don't bother.
    if (!_serviceable_node->getBoolValue() ||
        !_electrical_node->getBoolValue() ||
        !_transmitter_valid) {
        _last_distance_nm = 0;
        _in_range_node->setBoolValue(false);
        _distance_node->setDoubleValue(0);
        _speed_node->setDoubleValue(0);
        _time_node->setDoubleValue(0);
        return;
    }

                                // Calculate the distance to the transmitter
    Point3D location =
        sgGeodToCart(Point3D(longitude_rad, latitude_rad, altitude_m));
    double distance_nm = _transmitter.distance3D(location) * SG_METER_TO_NM;
    double range_nm = adjust_range(_transmitter_elevation_ft,
                                   altitude_m * SG_METER_TO_FEET,
                                   _transmitter_range_nm);
    if (distance_nm <= range_nm) {
        double speed_kt = (fabs(distance_nm - _last_distance_nm) *
                           ((1 / delta_time_sec) * 3600.0));
        _last_distance_nm = distance_nm;

        _in_range_node->setBoolValue(true);
        _distance_node->setDoubleValue(distance_nm);
        _speed_node->setDoubleValue(speed_kt);
        _time_node->setDoubleValue(distance_nm/speed_kt*60.0);
        
    } else {
        _last_distance_nm = 0;
        _in_range_node->setBoolValue(false);
        _distance_node->setDoubleValue(0);
        _speed_node->setDoubleValue(0);
        _time_node->setDoubleValue(0);
    }
}

void
DME::search (double frequency_mhz, double longitude_rad,
             double latitude_rad, double altitude_m)
{
                                // reset search time
    _time_before_search_sec = 1.0;

                                // try the ILS list first
    FGILS * ils = current_ilslist->findByFreq(frequency_mhz,
                                              longitude_rad,
                                              latitude_rad,
                                              altitude_m);
    if (ils !=0) {
        if (ils->get_has_dme()) {
            _transmitter_valid = true;
            _transmitter = Point3D(ils->get_dme_x(),
                                   ils->get_dme_y(),
                                   ils->get_dme_z());
            _transmitter_elevation_ft = ils->get_gselev() * SG_METER_TO_FEET;
            _transmitter_range_nm = 50; // arbitrary
            return;
        } else {
           _transmitter_valid = false;
           return;
        }
    }

                                // try the VORs next
    FGNav * nav = current_navlist->findByFreq(frequency_mhz,
                                              longitude_rad,
                                              latitude_rad,
                                              altitude_m);
    if (nav != 0) {
        if (nav->get_has_dme()) {
            _transmitter_valid = true;
            _transmitter = Point3D(nav->get_x(),
                                   nav->get_y(),
                                   nav->get_z());
            _transmitter_elevation_ft = nav->get_elev() * SG_METER_TO_FEET;
            _transmitter_range_nm = nav->get_range(); // fixme
            return;
        }
    } else {
        _transmitter_valid = false;
        return;
    }

    _transmitter_valid = false;
}

// end of dme.cxx
