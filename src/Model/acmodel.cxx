// model.cxx - manage a 3D aircraft model.
// Written by David Megginson, started 2002.
//
// This file is in the Public Domain, and comes with no warranty.

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>		// for strcmp()

#include <plib/sg.h>
#include <plib/ssg.h>

#include <simgear/compiler.h>
#include <simgear/debug/logstream.hxx>
#include <simgear/misc/exception.hxx>
#include <simgear/misc/sg_path.hxx>
#include <simgear/scene/model/placement.hxx>

#include <Main/globals.hxx>
#include <Main/fg_props.hxx>
#include <Main/viewmgr.hxx>
#include <Scenery/scenery.hxx>

#include "model_panel.hxx"

#include "acmodel.hxx"



////////////////////////////////////////////////////////////////////////
// Implementation of FGAircraftModel
////////////////////////////////////////////////////////////////////////

FGAircraftModel::FGAircraftModel ()
  : _aircraft(0),
    _selector(new ssgSelector),
    _scene(new ssgRoot),
    _nearplane(0.01f),
    _farplane(1000.0f)
{
}

FGAircraftModel::~FGAircraftModel ()
{
  delete _aircraft;
  delete _scene;
				// SSG will delete it
  globals->get_scenery()->get_aircraft_branch()->removeKid(_selector);
}

void 
FGAircraftModel::init ()
{
  _aircraft = new SGModelPlacement;
  string path = fgGetString("/sim/model/path", "Models/Geometry/glider.ac");
  try {
    ssgBranch *model = fgLoad3DModelPanel( globals->get_fg_root(),
                                           path,
                                           globals->get_props(),
                                           globals->get_sim_time_sec() );
    _aircraft->init( model );
  } catch (const sg_exception &ex) {
    SG_LOG(SG_GENERAL, SG_ALERT, "Failed to load aircraft from " << path);
    SG_LOG(SG_GENERAL, SG_ALERT, "(Falling back to glider.ac.)");
    ssgBranch *model = fgLoad3DModelPanel( globals->get_fg_root(),
                                           "Models/Geometry/glider.ac",
                                           globals->get_props(),
                                           globals->get_sim_time_sec() );
    _aircraft->init( model );
  }
  _scene->addKid(_aircraft->getSceneGraph());
  _selector->addKid(_aircraft->getSceneGraph());
  globals->get_scenery()->get_aircraft_branch()->addKid(_selector);
}

void 
FGAircraftModel::bind ()
{
  // No-op
}

void 
FGAircraftModel::unbind ()
{
  // No-op
}

void
FGAircraftModel::update (double dt)
{
  int view_number = globals->get_viewmgr()->get_current();

  if (view_number == 0 && !fgGetBool("/sim/view/internal")) {
    _aircraft->setVisible(false);
  } else {
    _aircraft->setVisible(true);
  }

  _aircraft->setPosition(fgGetDouble("/position/longitude-deg"),
			 fgGetDouble("/position/latitude-deg"),
			 fgGetDouble("/position/altitude-ft"));
  _aircraft->setOrientation(fgGetDouble("/orientation/roll-deg"),
			    fgGetDouble("/orientation/pitch-deg"),
			    fgGetDouble("/orientation/heading-deg"));
  _aircraft->update( globals->get_scenery()->get_center() );

}

void
FGAircraftModel::draw ()
{
				// OK, now adjust the clip planes and draw
				// FIXME: view number shouldn't be 
				// hard-coded.
  int view_number = globals->get_viewmgr()->get_current();
  if (_aircraft->getVisible() && view_number == 0) {
    glClearDepth(1);
    glClear(GL_DEPTH_BUFFER_BIT);
    ssgSetNearFar(_nearplane, _farplane);
    ssgCullAndDraw(_scene);
    _selector->select(0);
  } else {
    _selector->select(1);
  }

}

// end of model.cxx
