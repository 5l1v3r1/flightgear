// globals.hxx -- Global state that needs to be shared among the sim modules
//
// Written by Curtis Olson, started July 2000.
//
// Copyright (C) 2000  Curtis L. Olson - curt@flightgear.org
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


#ifndef _GLOBALS_HXX
#define _GLOBALS_HXX

#include <simgear/compiler.h>

#include <vector>
#include STL_STRING

#include "fgfs.hxx"


SG_USING_STD( vector );
SG_USING_STD( string );

typedef vector<string> string_list;


// Forward declarations

// This file is included, directly or indirectly, almost everywhere in
// FlightGear, so if any of its dependencies changes, most of the sim
// has to be recompiled.  Using these forward declarations helps us to
// avoid including a lot of header files (and thus, a lot of
// dependencies).  Since Most of the methods simply set or return
// pointers, we don't need to know anything about the class details
// anyway.

class SGEphemeris;

class SGCommandMgr;
class SGMagVar;
class SGPropertyNode;
class SGRoute;
class SGTime;

class FGAIMgr;
class FGATCMgr;
class FGATCDisplay;
class FGAircraftModel;
class FGAutopilot;
class FGControls;
class FGEnvironment;
class FGEnvironmentMgr;
class FGIO;
class FGModelLoader;
class FGModelMgr;
class FGScenery;
#ifdef FG_MPLAYER_AS
class FGMultiplayRxMgr;
class FGMultiplayTxMgr;
#endif
class FGPanel;
class FGSoundMgr;
class FGTileMgr;
class FGViewMgr;
class FGViewer;


/**
 * Bucket for subsystem pointers representing the sim's state.
 */
class FGGlobals
{

private:

    FGSubsystemMgr * subsystem_mgr;

    // Number of milliseconds elapsed since the start of the program.
    double sim_time_sec;

    // Root of FlightGear data tree
    string fg_root;

    // Root of FlightGear scenery tree
    string fg_scenery;

    // Fullscreen mode for old 3DFX cards.
#if defined(FX) && defined(XMESA)
    bool fullscreen;
#endif

    // An offset in seconds from the true time.  Allows us to adjust
    // the effective time of day.
    long int warp;

    // How much to change the value of warp each iteration.  Allows us
    // to make time progress faster than normal (or even run in reverse.)
    long int warp_delta;

    // Time structure
    SGTime *time_params;

    // Sky structures
    SGEphemeris *ephem;

    // Magnetic Variation
    SGMagVar *mag;

    // Current autopilot
    FGAutopilot *autopilot;

    // Global autopilot "route"
    SGRoute *route;

    // 2D panel
    FGPanel *current_panel;

    // sound manager
    FGSoundMgr *soundmgr;

    // environment information
    FGEnvironmentMgr * environment_mgr;

    // ATC manager
    FGATCMgr *ATC_mgr;

    // ATC Renderer
    FGATCDisplay *ATC_display;

    // AI manager
    FGAIMgr *AI_mgr;

    // control input state
    FGControls *controls;

    // viewer manager
    FGViewMgr *viewmgr;

    // properties
    SGPropertyNode *props;
    SGPropertyNode *initial_state;

    // localization
    SGPropertyNode *locale;

    SGCommandMgr *commands;

    FGModelLoader * model_loader;

    FGAircraftModel *acmodel;

    FGModelMgr * model_mgr;

    // list of serial port-like configurations
    string_list *channel_options_list;

    // FlightGear scenery manager
    FGScenery *scenery;

    // Tile manager
    FGTileMgr *tile_mgr;

    FGIO* io;

#ifdef FG_MPLAYER_AS
    //Mulitplayer managers
    FGMultiplayTxMgr *multiplayer_tx_mgr;

    FGMultiplayRxMgr *multiplayer_rx_mgr;
#endif

public:

    FGGlobals();
    virtual ~FGGlobals();

    virtual FGSubsystemMgr * get_subsystem_mgr () const;

    virtual FGSubsystem * get_subsystem (const char * name);

    virtual void add_subsystem (const char * name,
                                FGSubsystem * subsystem,
                                FGSubsystemMgr::GroupType
                                  type = FGSubsystemMgr::GENERAL,
                                double min_time_sec = 0);

    inline double get_sim_time_sec () const { return sim_time_sec; }
    inline void inc_sim_time_sec (double dt) { sim_time_sec += dt; }
    inline void set_sim_time_sec (double t) { sim_time_sec = t; }

    inline const string &get_fg_root () const { return fg_root; }
    void set_fg_root (const string &root);

    inline const string &get_fg_scenery () const { return fg_scenery; }
    inline void set_fg_scenery (const string &scenery) {
      fg_scenery = scenery;
    }

#if defined(FX) && defined(XMESA)
    inline bool get_fullscreen() const { return fullscreen; }
    inline bool set_fullscreen( bool f ) { fullscreen = f; }
#endif

    inline long int get_warp() const { return warp; }
    inline void set_warp( long int w ) { warp = w; }
    inline void inc_warp( long int w ) { warp += w; }

    inline long int get_warp_delta() const { return warp_delta; }
    inline void set_warp_delta( long int d ) { warp_delta = d; }
    inline void inc_warp_delta( long int d ) { warp_delta += d; }

    inline SGTime *get_time_params() const { return time_params; }
    inline void set_time_params( SGTime *t ) { time_params = t; }

    inline SGEphemeris *get_ephem() const { return ephem; }
    inline void set_ephem( SGEphemeris *e ) { ephem = e; }

    inline SGMagVar *get_mag() const { return mag; }
    inline void set_mag( SGMagVar *m ) { mag = m; }

    inline FGAutopilot *get_autopilot() const { return autopilot; }
    inline void set_autopilot( FGAutopilot *ap) { autopilot = ap; }

    inline SGRoute *get_route() const { return route; }
    inline void set_route( SGRoute *r ) { route = r; }

    inline FGEnvironmentMgr * get_environment_mgr() {
      return environment_mgr;
    }
    inline void set_environment_mgr(FGEnvironmentMgr * mgr) {
      environment_mgr = mgr;
    }

    inline FGATCMgr *get_ATC_mgr() const { return ATC_mgr; }
    inline void set_ATC_mgr( FGATCMgr *a ) {ATC_mgr = a; }

    inline FGATCDisplay *get_ATC_display() const { return ATC_display; }
    inline void set_ATC_display( FGATCDisplay *d ) {ATC_display = d; }

    inline FGAIMgr *get_AI_mgr() const { return AI_mgr; }
    inline void set_AI_mgr( FGAIMgr *a ) {AI_mgr = a; }

    inline FGPanel *get_current_panel() const { return current_panel; }
    inline void set_current_panel( FGPanel *cp ) { current_panel = cp; }

    inline FGSoundMgr *get_soundmgr() const { return soundmgr; }
    inline void set_soundmgr( FGSoundMgr *sm ) { soundmgr = sm; }

    inline FGControls *get_controls() const { return controls; }
    inline void set_controls( FGControls *c ) { controls = c; }

    inline FGViewMgr *get_viewmgr() const { return viewmgr; }
    inline void set_viewmgr( FGViewMgr *vm ) { viewmgr = vm; }
    FGViewer *get_current_view() const;

    inline SGPropertyNode *get_props () { return props; }
    inline void set_props( SGPropertyNode *n ) { props = n; }

    inline SGPropertyNode *get_locale () { return locale; }
    inline void set_locale( SGPropertyNode *n ) { locale = n; }

    inline SGCommandMgr *get_commands () { return commands; }

    inline FGModelLoader * get_model_loader () { return model_loader; }

    inline void set_model_loader (FGModelLoader * loader) {
        model_loader = loader;
    }

    inline FGAircraftModel *get_aircraft_model () { return acmodel; }

    inline void set_aircraft_model (FGAircraftModel * model)
    {
        acmodel = model;
    }

    inline FGModelMgr *get_model_mgr () { return model_mgr; }

    inline void set_model_mgr (FGModelMgr * mgr)
    {
      model_mgr = mgr;
    }

#ifdef FG_MPLAYER_AS
    inline FGMultiplayTxMgr *get_multiplayer_tx_mgr () { return multiplayer_tx_mgr; }

    inline void set_multiplayer_tx_mgr (FGMultiplayTxMgr * mgr)
    {
      multiplayer_tx_mgr = mgr;
    }

    inline FGMultiplayRxMgr *get_multiplayer_rx_mgr () { return multiplayer_rx_mgr; }

    inline void set_multiplayer_rx_mgr (FGMultiplayRxMgr * mgr)
    {
      multiplayer_rx_mgr = mgr;
    }
#endif

    inline string_list *get_channel_options_list () {
	return channel_options_list;
    }
    inline void set_channel_options_list( string_list *l ) {
	channel_options_list = l;
    }

    inline FGScenery * get_scenery () const { return scenery; }
    inline void set_scenery ( FGScenery *s ) { scenery = s; }

    inline FGTileMgr * get_tile_mgr () const { return tile_mgr; }
    inline void set_tile_mgr ( FGTileMgr *t ) { tile_mgr = t; }

    FGIO* get_io() const { return io; }


    /**
     * Save the current state as the initial state.
     */
    void saveInitialState ();


    /**
     * Restore the saved initial state, if any.
     */
    void restoreInitialState ();

};


extern FGGlobals *globals;


#endif // _GLOBALS_HXX
