// airspeed_indicator.hxx - a regular VSI tied to the static port.
// Written by David Megginson, started 2002.
//
// This file is in the Public Domain and comes with no warranty.


#ifndef __INSTRUMENTS_AIRSPEED_INDICATOR_HXX
#define __INSTRUMENTS_AIRSPEED_INDICATOR_HXX 1

#ifndef __cplusplus
# error This library requires C++
#endif

#include <simgear/misc/props.hxx>
#include <Main/fgfs.hxx>


/**
 * Model an airspeed indicator tied to the pitot and static ports.
 *
 * Input properties:
 *
 * /instrumentation/airspeed-indicator/serviceable
 * /systems/pitot[0]/total-pressure-inhg
 * /systems/static[0]/pressure-inhg
 * /environment/density-slugft3
 *
 * Output properties:
 *
 * /instrumentation/airspeed-indicator/indicated-speed-kt
 */
class AirspeedIndicator : public FGSubsystem
{

public:

    AirspeedIndicator ();
    virtual ~AirspeedIndicator ();

    virtual void init ();
    virtual void update (double dt);

private:

    SGPropertyNode_ptr _serviceable_node;
    SGPropertyNode_ptr _total_pressure_node;
    SGPropertyNode_ptr _static_pressure_node;
    SGPropertyNode_ptr _density_node;
    SGPropertyNode_ptr _speed_node;
    
};

#endif // __INSTRUMENTS_AIRSPEED_INDICATOR_HXX
