// FGAIBase - abstract base class for AI objects
// Written by David Culp, started Nov 2003, based on
// David Luff's FGAIEntity class.
// - davidculp2@comcast.net
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

#ifndef _FG_AIBASE_HXX
#define _FG_AIBASE_HXX

#include <string>

#include <simgear/constants.h>
#include <simgear/math/point3d.hxx>
#include <simgear/scene/model/placement.hxx>

#include <Main/fg_props.hxx>

SG_USING_STD(string);

class FGAIManager;

class FGAIBase {

public:

    FGAIBase();
    virtual ~FGAIBase();
    virtual void update(double dt);
    inline Point3D GetPos() { return(pos); }

    virtual bool init();
    virtual void bind();
    virtual void unbind();

    void setPath( const char* model );
    void setSpeed( double speed_KTAS );
    void setAltitude( double altitude_ft );
    void setHeading( double heading );
    void setLatitude( double latitude );
    void setLongitude( double longitude );
    void setBank( double bank );

    void setID( int ID );
    int  getID();
    void setDie( bool die );
    bool getDie();

protected:

    SGPropertyNode *props;
    FGAIManager* manager;

    // these describe the model's actual state
    Point3D pos;	// WGS84 lat & lon in degrees, elev above sea-level in meters
    double hdg;		// True heading in degrees
    double roll;	// degrees, left is negative
    double pitch;	// degrees, nose-down is negative
    double speed;       // knots true airspeed
    double altitude;    // meters above sea level
    double vs;          // vertical speed, feet per minute   

    // these describe the model's desired state
    double tgt_heading;  // target heading, degrees true
    double tgt_altitude; // target altitude, *feet* above sea level
    double tgt_speed;    // target speed, KTAS
    double tgt_roll;
    double tgt_pitch;
    double tgt_yaw;
    double tgt_vs;

    // these describe radar information for the user
    double bearing;      // true bearing from user to this model
    double elevation;    // elevation in degrees from user to this model
    double range;        // range from user to this model, nm
    double rdot;         // range rate, in knots
    double horiz_offset; // look left/right from user to me, deg
    double vert_offset;  // look up/down from user to me, deg
    double x_shift;      // value used by radar display instrument
    double y_shift;      // value used by radar display instrument
    double rotation;     // value used by radar display instrument


    string model_path;	   //Path to the 3D model
    SGModelPlacement aip;
    bool delete_me;
    int id;

    void Transform();

    static FGAIBase *_self;
    const char *_type_str;

public:

    static double _getVS_fps();
    static void _setVS_fps( double _vs );

    static double _getAltitude();
    static void _setAltitude( double _alt );

    static void _setLongitude( double longitude );
    static void _setLatitude ( double latitude );

    static double _getLongitude();
    static double _getLatitude ();

    static double _getBearing();
    static double _getElevation();
    static double _getRange();
    static double _getRdot();
    static double _getH_offset();
    static double _getV_offset();
    static double _getX_shift();
    static double _getY_shift();
    static double _getRotation();

    static bool _isNight();
};


inline void FGAIBase::setPath( const char* model ) {
  model_path.append(model);
}

inline void FGAIBase::setSpeed( double speed_KTAS ) {
  speed = tgt_speed = speed_KTAS;
}

inline void FGAIBase::setHeading( double heading ) {
  hdg = tgt_heading = heading;
}

inline void FGAIBase::setAltitude( double altitude_ft ) {
    altitude = tgt_altitude = altitude_ft;
    pos.setelev(altitude * SG_FEET_TO_METER);
}

inline void FGAIBase::setBank( double bank ) {
  roll = tgt_roll = bank;
}

inline void FGAIBase::setLongitude( double longitude ) {
    pos.setlon( longitude );
}
inline void FGAIBase::setLatitude ( double latitude ) {
    pos.setlat( latitude );
}

inline void FGAIBase::setDie( bool die ) { delete_me = die; }
inline bool FGAIBase::getDie() { return delete_me; }

inline void FGAIBase::_setLongitude( double longitude ) {
    _self->pos.setlon(longitude);
}
inline void FGAIBase::_setLatitude ( double latitude )  {
    _self->pos.setlat(latitude);
}

inline double FGAIBase::_getLongitude() { return _self->pos.lon(); }
inline double FGAIBase::_getLatitude () { return _self->pos.lat(); }

inline double FGAIBase::_getBearing()   { return _self->bearing; }
inline double FGAIBase::_getElevation() { return _self->elevation; }
inline double FGAIBase::_getRange()     { return _self->range; }
inline double FGAIBase::_getRdot()      { return _self->rdot; }
inline double FGAIBase::_getH_offset()  { return _self->horiz_offset; }
inline double FGAIBase::_getV_offset()  { return _self->vert_offset; }
inline double FGAIBase::_getX_shift()   { return _self->x_shift; }
inline double FGAIBase::_getY_shift()   { return _self->y_shift; }
inline double FGAIBase::_getRotation()  { return _self->rotation; }

inline double FGAIBase::_getVS_fps() { return _self->vs*60.0; }
inline void FGAIBase::_setVS_fps( double _vs ) { _self->vs = _vs/60.0; }

inline double FGAIBase::_getAltitude() {
    return _self->altitude;
}
inline void FGAIBase::_setAltitude( double _alt ) {
    _self->setAltitude( _alt );
}

inline bool FGAIBase::_isNight() {
    return (fgGetFloat("/sim/time/sun-angle-rad") > 1.57);
}

inline void FGAIBase::setID( int ID ) { id = ID; }
inline int  FGAIBase::getID() { return id; }

#endif  // _FG_AIBASE_HXX

