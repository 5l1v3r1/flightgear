// fg_props.cxx -- support for FlightGear properties.
//
// Written by David Megginson, started 2000.
//
// Copyright (C) 2000, 2001 David Megginson - david@megginson.com
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
#  include <simgear/compiler.h>
#endif

#include <simgear/misc/exception.hxx>
#include <simgear/magvar/magvar.hxx>
#include <simgear/timing/sg_time.hxx>
#include <simgear/misc/sg_path.hxx>
#include <simgear/sound/soundmgr.hxx>

#include STL_IOSTREAM

#include <ATC/ATCdisplay.hxx>
#include <Aircraft/aircraft.hxx>
#include <Time/tmp.hxx>
#include <FDM/UIUCModel/uiuc_aircraftdir.h>
#ifdef FG_WEATHERCM
#  include <WeatherCM/FGLocalWeatherDatabase.h>
#else
#  include <Environment/environment.hxx>
#endif // FG_WEATHERCM
#include <Objects/matlib.hxx>

#include <GUI/gui.h>

#include "globals.hxx"
#include "fgfs.hxx"
#include "fg_props.hxx"

SG_USING_STD(istream);
SG_USING_STD(ostream);

#ifdef FG_WEATHERCM
static double getWindNorth ();
static double getWindEast ();
static double getWindDown ();
#endif // FG_WEATHERCM

static bool winding_ccw = true; // FIXME: temporary

static bool fdm_data_logging = false; // FIXME: temporary

static bool frozen = false;	// FIXME: temporary



////////////////////////////////////////////////////////////////////////
// Default property bindings (not yet handled by any module).
////////////////////////////////////////////////////////////////////////

struct LogClassMapping {
  sgDebugClass c;
  string name;
  LogClassMapping(sgDebugClass cc, string nname) { c = cc; name = nname; }
};

LogClassMapping log_class_mappings [] = {
  LogClassMapping(SG_NONE, "none"),
  LogClassMapping(SG_TERRAIN, "terrain"),
  LogClassMapping(SG_ASTRO, "astro"),
  LogClassMapping(SG_FLIGHT, "flight"),
  LogClassMapping(SG_INPUT, "input"),
  LogClassMapping(SG_GL, "gl"),
  LogClassMapping(SG_VIEW, "view"),
  LogClassMapping(SG_COCKPIT, "cockpit"),
  LogClassMapping(SG_GENERAL, "general"),
  LogClassMapping(SG_MATH, "math"),
  LogClassMapping(SG_EVENT, "event"),
  LogClassMapping(SG_AIRCRAFT, "aircraft"),
  LogClassMapping(SG_AUTOPILOT, "autopilot"),
  LogClassMapping(SG_IO, "io"),
  LogClassMapping(SG_CLIPPER, "clipper"),
  LogClassMapping(SG_NETWORK, "network"),
  LogClassMapping(SG_UNDEFD, "")
};


/**
 * Get the logging classes.
 */
static const char *
getLoggingClasses ()
{
  sgDebugClass classes = logbuf::get_log_classes();
  static string result = "";	// FIXME
  for (int i = 0; log_class_mappings[i].c != SG_UNDEFD; i++) {
    if ((classes&log_class_mappings[i].c) > 0) {
      if (!result.empty())
	result += '|';
      result += log_class_mappings[i].name;
    }
  }
  return result.c_str();
}


static void
addLoggingClass (const string &name)
{
  sgDebugClass classes = logbuf::get_log_classes();
  for (int i = 0; log_class_mappings[i].c != SG_UNDEFD; i++) {
    if (name == log_class_mappings[i].name) {
      logbuf::set_log_classes(sgDebugClass(classes|log_class_mappings[i].c));
      return;
    }
  }
  SG_LOG(SG_GENERAL, SG_ALERT, "Unknown logging class: " << name);
}


/**
 * Set the logging classes.
 */
static void
setLoggingClasses (const char * c)
{
  string classes = c;
  logbuf::set_log_classes(SG_NONE);

  if (classes == "none") {
    SG_LOG(SG_GENERAL, SG_INFO, "Disabled all logging classes");
    return;
  }

  if (classes.empty() || classes == "all") { // default
    logbuf::set_log_classes(SG_ALL);
    SG_LOG(SG_GENERAL, SG_INFO, "Enabled all logging classes: "
	   << getLoggingClasses());
    return;
  }

  string rest = classes;
  string name = "";
  int sep = rest.find('|');
  while (sep > 0) {
    name = rest.substr(0, sep);
    rest = rest.substr(sep+1);
    addLoggingClass(name);
    sep = rest.find('|');
  }
  addLoggingClass(rest);
  SG_LOG(SG_GENERAL, SG_INFO, "Set logging classes to "
	 << getLoggingClasses());
}


/**
 * Get the logging priority.
 */
static const char *
getLoggingPriority ()
{
  switch (logbuf::get_log_priority()) {
  case SG_BULK:
    return "bulk";
  case SG_DEBUG:
    return "debug";
  case SG_INFO:
    return "info";
  case SG_WARN:
    return "warn";
  case SG_ALERT:
    return "alert";
  default:
    SG_LOG(SG_GENERAL, SG_WARN, "Internal: Unknown logging priority number: "
	   << logbuf::get_log_priority());
    return "unknown";
  }
}


/**
 * Set the logging priority.
 */
static void
setLoggingPriority (const char * p)
{
  string priority = p;
  if (priority == "bulk") {
    logbuf::set_log_priority(SG_BULK);
  } else if (priority == "debug") {
    logbuf::set_log_priority(SG_DEBUG);
  } else if (priority.empty() || priority == "info") { // default
    logbuf::set_log_priority(SG_INFO);
  } else if (priority == "warn") {
    logbuf::set_log_priority(SG_WARN);
  } else if (priority == "alert") {
    logbuf::set_log_priority(SG_ALERT);
  } else {
    SG_LOG(SG_GENERAL, SG_WARN, "Unknown logging priority " << priority);
  }
  SG_LOG(SG_GENERAL, SG_INFO, "Logging priority is " << getLoggingPriority());
}


/**
 * Return the current frozen state.
 */
static bool
getFreeze ()
{
  return frozen;
}


/**
 * Set the current frozen state.
 */
static void
setFreeze (bool f)
{
    frozen = f;

    // Stop sound on a pause
    SoundMgr *s = globals->get_soundmgr();
    if ( s != NULL ) {
        if ( f ) {
            s->pause();
        } else {
            s->resume();
        }
    }
}


/**
 * Return the current aircraft directory (UIUC) as a string.
 */
static const char *
getAircraftDir ()
{
  return aircraft_dir.c_str();
}


/**
 * Set the current aircraft directory (UIUC).
 */
static void
setAircraftDir (const char * dir)
{
  aircraft_dir = dir;
}


/**
 * Return the number of milliseconds elapsed since simulation started.
 */
static double
getElapsedTime_sec ()
{
  return globals->get_sim_time_sec();
}


/**
 * Return the current Zulu time.
 */
static const char *
getDateString ()
{
  static char buf[64];		// FIXME
  struct tm * t = globals->get_time_params()->getGmt();
  sprintf(buf, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2d",
	  t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
	  t->tm_hour, t->tm_min, t->tm_sec);
  return buf;
}


/**
 * Set the current Zulu time.
 */
static void
setDateString (const char * date_string)
{
  static const SGPropertyNode *cur_time_override
	= fgGetNode("/sim/time/cur-time-override", true);

  SGTime * st = globals->get_time_params();
  struct tm * current_time = st->getGmt();
  struct tm new_time;

				// Scan for basic ISO format
				// YYYY-MM-DDTHH:MM:SS
  int ret = sscanf(date_string, "%d-%d-%dT%d:%d:%d",
		   &(new_time.tm_year), &(new_time.tm_mon),
		   &(new_time.tm_mday), &(new_time.tm_hour),
		   &(new_time.tm_min), &(new_time.tm_sec));

				// Be pretty picky about this, so
				// that strange things don't happen
				// if the save file has been edited
				// by hand.
  if (ret != 6) {
    SG_LOG(SG_INPUT, SG_ALERT, "Date/time string " << date_string
	   << " not in YYYY-MM-DDTHH:MM:SS format; skipped");
    return;
  }

				// OK, it looks like we got six
				// values, one way or another.
  new_time.tm_year -= 1900;
  new_time.tm_mon -= 1;

				// Now, tell flight gear to use
				// the new time.  This was far
				// too difficult, by the way.
  long int warp =
    mktime(&new_time) - mktime(current_time) + globals->get_warp();
  double lon = current_aircraft.fdm_state->get_Longitude();
  double lat = current_aircraft.fdm_state->get_Latitude();
  globals->set_warp(warp);
  st->update(lon, lat, cur_time_override->getLongValue(), warp);
  fgUpdateSkyAndLightingParams();
}

/**
 * Return the GMT as a string.
 */
static const char *
getGMTString ()
{
  static char buf[16];		// FIXME
  struct tm *t = globals->get_time_params()->getGmt();
  sprintf(buf, " %.2d:%.2d:%.2d",
	  t->tm_hour, t->tm_min, t->tm_sec);
  // cout << t << " " << buf << endl;
  return buf;
}


/**
 * Get the texture rendering state.
 */
static bool
getTextures ()
{
  return (material_lib.get_step() == 0);
}


/**
 * Set the texture rendering state.
 */
static void
setTextures (bool textures)
{
  if (textures)
    material_lib.set_step(0);
  else
    material_lib.set_step(1);
}


/**
 * Return the magnetic variation
 */
static double
getMagVar ()
{
  return globals->get_mag()->get_magvar() * SGD_RADIANS_TO_DEGREES;
}


/**
 * Return the magnetic dip
 */
static double
getMagDip ()
{
  return globals->get_mag()->get_magdip() * SGD_RADIANS_TO_DEGREES;
}


/**
 * Return the current heading in degrees.
 */
static double
getHeadingMag ()
{
  return current_aircraft.fdm_state->get_Psi() * SGD_RADIANS_TO_DEGREES - getMagVar();
}


#ifdef FG_WEATHERCM

/**
 * Get the current visibility (meters).
 */
static double
getVisibility ()
{
  return WeatherDatabase->getWeatherVisibility();
}


/**
 * Set the current visibility (meters).
 */
static void
setVisibility (double visibility)
{
  WeatherDatabase->setWeatherVisibility(visibility);
}

/**
 * Get the current wind north velocity (feet/second).
 */
static double
getWindNorth ()
{
  return current_aircraft.fdm_state->get_V_north_airmass();
}


/**
 * Set the current wind north velocity (feet/second).
 */
static void
setWindNorth (double speed)
{
  current_aircraft.fdm_state
    ->set_Velocities_Local_Airmass(speed, getWindEast(), getWindDown());
}


/**
 * Get the current wind east velocity (feet/second).
 */
static double
getWindEast ()
{
  return current_aircraft.fdm_state->get_V_east_airmass();
}


/**
 * Set the current wind east velocity (feet/second).
 */
static void
setWindEast (double speed)
{
  SG_LOG(SG_GENERAL, SG_INFO,, "Set wind-east to " << speed );
  current_aircraft.fdm_state->set_Velocities_Local_Airmass(getWindNorth(),
							   speed,
							   getWindDown());
}


/**
 * Get the current wind down velocity (feet/second).
 */
static double
getWindDown ()
{
  return current_aircraft.fdm_state->get_V_down_airmass();
}


/**
 * Set the current wind down velocity (feet/second).
 */
static void
setWindDown (double speed)
{
  current_aircraft.fdm_state->set_Velocities_Local_Airmass(getWindNorth(),
							   getWindEast(),
							   speed);
}

#endif // FG_WEATHERCM

static long
getWarp ()
{
  return globals->get_warp();
}

static void
setWarp (long warp)
{
  globals->set_warp(warp);
}

static long
getWarpDelta ()
{
  return globals->get_warp_delta();
}

static void
setWarpDelta (long delta)
{
  globals->set_warp_delta(delta);
}

static bool
getWindingCCW ()
{
  return winding_ccw;
}

static void
setWindingCCW (bool state)
{
  winding_ccw = state;
  if ( winding_ccw )
    glFrontFace ( GL_CCW );
  else
    glFrontFace ( GL_CW );
}

static bool
getFullScreen ()
{
#if defined(FX) && !defined(WIN32)
  return globals->get_fullscreen();
#else
  return false;
#endif
}

static void
setFullScreen (bool state)
{
#if defined(FX) && !defined(WIN32)
  globals->set_fullscreen(state);
#  if defined(XMESA_FX_FULLSCREEN) && defined(XMESA_FX_WINDOW)
  XMesaSetFXmode( state ? XMESA_FX_FULLSCREEN : XMESA_FX_WINDOW );
#  endif
#endif
}

static bool
getFDMDataLogging ()
{
  return fdm_data_logging;
}

static void
setFDMDataLogging (bool state)
{
				// kludge; no getter or setter available
  if (state != fdm_data_logging) {
    fgToggleFDMdataLogging();
    fdm_data_logging = state;
  }
}


////////////////////////////////////////////////////////////////////////
// Tie the properties.
////////////////////////////////////////////////////////////////////////

void
fgInitProps ()
{
  SG_LOG(SG_GENERAL, SG_DEBUG, "start of fgInitProps()" );
				// Simulation
  fgTie("/sim/logging/priority", getLoggingPriority, setLoggingPriority);
  fgTie("/sim/logging/classes", getLoggingClasses, setLoggingClasses);
  fgTie("/sim/freeze/master", getFreeze, setFreeze);
  fgTie("/sim/aircraft-dir", getAircraftDir, setAircraftDir);

  fgTie("/sim/time/elapsed-sec", getElapsedTime_sec);
  fgTie("/sim/time/gmt", getDateString, setDateString);
  fgSetArchivable("/sim/time/gmt");
  fgTie("/sim/time/gmt-string", getGMTString);
  fgTie("/sim/rendering/textures", getTextures, setTextures);

				// Orientation
  fgTie("/orientation/heading-magnetic-deg", getHeadingMag);

				// Environment
#ifdef FG_WEATHERCM
  fgTie("/environment/visibility-m", getVisibility, setVisibility);
  fgSetArchivable("/environment/visibility-m");
  fgTie("/environment/wind-from-north-fps", getWindNorth, setWindNorth);
  fgSetArchivable("/environment/wind-from-north-fps");
  fgTie("/environment/wind-from-east-fps", getWindEast, setWindEast);
  fgSetArchivable("/environment/wind-from-east-fps");
  fgTie("/environment/wind-from-down-fps", getWindDown, setWindDown);
  fgSetArchivable("/environment/wind-from-down-fps");
#endif

  fgTie("/environment/magnetic-variation-deg", getMagVar);
  fgTie("/environment/magnetic-dip-deg", getMagDip);

  fgTie("/sim/time/warp", getWarp, setWarp, false);
  fgTie("/sim/time/warp-delta", getWarpDelta, setWarpDelta);

				// Misc. Temporary junk.
  fgTie("/sim/temp/winding-ccw", getWindingCCW, setWindingCCW, false);
  fgTie("/sim/temp/full-screen", getFullScreen, setFullScreen);
  fgTie("/sim/temp/fdm-data-logging", getFDMDataLogging, setFDMDataLogging);

  SG_LOG(SG_GENERAL, SG_DEBUG, "end of fgInitProps()" );
}


void
fgUpdateProps ()
{
}



////////////////////////////////////////////////////////////////////////
// Save and restore.
////////////////////////////////////////////////////////////////////////


/**
 * Save the current state of the simulator to a stream.
 */
bool
fgSaveFlight (ostream &output, bool write_all)
{

  fgSetBool("/sim/presets/onground", false);
  fgSetArchivable("/sim/presets/onground");
  fgSetBool("/sim/presets/trim", false);
  fgSetArchivable("/sim/presets/trim");
  fgSetString("/sim/presets/speed-set", "UVW");
  fgSetArchivable("/sim/presets/speed-set");

  try {
    writeProperties(output, globals->get_props(), write_all);
  } catch (const sg_exception &e) {
    guiErrorMessage("Error saving flight: ", e);
    return false;
  }
  return true;
}


/**
 * Restore the current state of the simulator from a stream.
 */
bool
fgLoadFlight (istream &input)
{
  SGPropertyNode props;
  try {
    readProperties(input, &props);
  } catch (const sg_exception &e) {
    guiErrorMessage("Error reading saved flight: ", e);
    return false;
  }

  fgSetBool("/sim/presets/onground", false);
  fgSetBool("/sim/presets/trim", false);
  fgSetString("/sim/presets/speed-set", "UVW");

  copyProperties(&props, globals->get_props());
  // When loading a flight, make it the
  // new initial state.
  globals->saveInitialState();
  return true;
}


bool
fgLoadProps (const char * path, SGPropertyNode * props, bool in_fg_root)
{
    string fullpath;
    if (in_fg_root) {
        SGPath loadpath(globals->get_fg_root());
        loadpath.append(path);
        fullpath = loadpath.str();
    } else {
        fullpath = path;
    }

    try {
        readProperties(fullpath, props);
    } catch (const sg_exception &e) {
        guiErrorMessage("Error reading properties: ", e);
        return false;
    }
    return true;
}



////////////////////////////////////////////////////////////////////////
// Property convenience functions.
////////////////////////////////////////////////////////////////////////

SGPropertyNode *
fgGetNode (const char * path, bool create)
{
  return globals->get_props()->getNode(path, create);
}

SGPropertyNode * 
fgGetNode (const char * path, int index, bool create)
{
  return globals->get_props()->getNode(path, index, create);
}

bool
fgHasNode (const char * path)
{
  return (fgGetNode(path, false) != 0);
}

void
fgAddChangeListener (SGPropertyChangeListener * listener, const char * path)
{
  fgGetNode(path, true)->addChangeListener(listener);
}

void
fgAddChangeListener (SGPropertyChangeListener * listener,
		     const char * path, int index)
{
  fgGetNode(path, index, true)->addChangeListener(listener);
}

bool
fgGetBool (const char * name, bool defaultValue)
{
  return globals->get_props()->getBoolValue(name, defaultValue);
}

int
fgGetInt (const char * name, int defaultValue)
{
  return globals->get_props()->getIntValue(name, defaultValue);
}

int
fgGetLong (const char * name, long defaultValue)
{
  return globals->get_props()->getLongValue(name, defaultValue);
}

float
fgGetFloat (const char * name, float defaultValue)
{
  return globals->get_props()->getFloatValue(name, defaultValue);
}

double
fgGetDouble (const char * name, double defaultValue)
{
  return globals->get_props()->getDoubleValue(name, defaultValue);
}

const char *
fgGetString (const char * name, const char * defaultValue)
{
  return globals->get_props()->getStringValue(name, defaultValue);
}

bool
fgSetBool (const char * name, bool val)
{
  return globals->get_props()->setBoolValue(name, val);
}

bool
fgSetInt (const char * name, int val)
{
  return globals->get_props()->setIntValue(name, val);
}

bool
fgSetLong (const char * name, long val)
{
  return globals->get_props()->setLongValue(name, val);
}

bool
fgSetFloat (const char * name, float val)
{
  return globals->get_props()->setFloatValue(name, val);
}

bool
fgSetDouble (const char * name, double val)
{
  return globals->get_props()->setDoubleValue(name, val);
}

bool
fgSetString (const char * name, const char * val)
{
  return globals->get_props()->setStringValue(name, val);
}

void
fgSetArchivable (const char * name, bool state)
{
  SGPropertyNode * node = globals->get_props()->getNode(name);
  if (node == 0)
    SG_LOG(SG_GENERAL, SG_ALERT,
	   "Attempt to set archive flag for non-existant property "
	   << name);
  else
    node->setAttribute(SGPropertyNode::ARCHIVE, state);
}

void
fgSetReadable (const char * name, bool state)
{
  SGPropertyNode * node = globals->get_props()->getNode(name);
  if (node == 0)
    SG_LOG(SG_GENERAL, SG_ALERT,
	   "Attempt to set read flag for non-existant property "
	   << name);
  else
    node->setAttribute(SGPropertyNode::READ, state);
}

void
fgSetWritable (const char * name, bool state)
{
  SGPropertyNode * node = globals->get_props()->getNode(name);
  if (node == 0)
    SG_LOG(SG_GENERAL, SG_ALERT,
	   "Attempt to set write flag for non-existant property "
	   << name);
  else
    node->setAttribute(SGPropertyNode::WRITE, state);
}

void
fgUntie (const char * name)
{
  if (!globals->get_props()->untie(name))
    SG_LOG(SG_GENERAL, SG_WARN, "Failed to untie property " << name);
}


// end of fg_props.cxx
