// main.cxx -- top level sim routines
//
// Written by Curtis Olson, started May 1997.
//
// Copyright (C) 1997 - 2002  Curtis L. Olson  - curt@flightgear.org
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

#include <simgear/compiler.h>

#if defined(__linux__) && defined(__i386__)
#  include <fpu_control.h>
#  include <signal.h>
#endif

#ifdef SG_MATH_EXCEPTION_CLASH
#  include <math.h>
#endif

#ifdef HAVE_WINDOWS_H
#  include <windows.h>
#  include <float.h>
#endif

#include <plib/ssg.h>
#include <plib/pu.h>

#include <simgear/screen/extensions.hxx>
#include <simgear/scene/material/matlib.hxx>
#include <simgear/props/props.hxx>
#include <simgear/scene/sky/sky.hxx>
#include <simgear/timing/sg_time.hxx>
#include <simgear/scene/model/animation.hxx>
#include <simgear/ephemeris/ephemeris.hxx>
#include <simgear/scene/model/placement.hxx>
#include <simgear/math/sg_random.h>
#include <simgear/route/route.hxx>
#include <simgear/scene/model/modellib.hxx>

#ifdef FG_USE_CLOUDS_3D
#  include <simgear/scene/sky/clouds3d/SkySceneLoader.hpp>
#  include <simgear/scene/sky/clouds3d/SkyUtil.hpp>
#endif

#include <Include/general.hxx>
#include <Scenery/tileentry.hxx>
#include <Time/FGEventMgr.hxx>
#include <Time/light.hxx>
#include <Time/light.hxx>
#include <Aircraft/aircraft.hxx>
#include <Cockpit/panel.hxx>
#include <Cockpit/cockpit.hxx>
#include <Cockpit/radiostack.hxx>
#include <Cockpit/hud.hxx>
#include <Model/panelnode.hxx>
#include <Model/modelmgr.hxx>
#include <Model/acmodel.hxx>
#include <Scenery/scenery.hxx>
#include <Scenery/tilemgr.hxx>
#include <FDM/flight.hxx>
#include <FDM/UIUCModel/uiuc_aircraftdir.h>
#include <FDM/ADA.hxx>
#include <ATC/ATCdisplay.hxx>
#include <ATC/ATCmgr.hxx>
#include <ATC/AIMgr.hxx>
#include <Autopilot/newauto.hxx>
#include <Replay/replay.hxx>
#include <Time/tmp.hxx>
#include <Time/fg_timer.hxx>
#include <Environment/environment_mgr.hxx>

#ifdef FG_NETWORK_OLK
#include <NetworkOLK/network.h>
#endif

#ifdef FG_MPLAYER_AS
#include <MultiPlayer/multiplaytxmgr.hxx>
#include <MultiPlayer/multiplayrxmgr.hxx>
#endif

#include "splash.hxx"
#include "fg_commands.hxx"
#include "fg_io.hxx"


glPointParameterfProc glPointParameterfPtr = 0;
glPointParameterfvProc glPointParameterfvPtr = 0;
bool glPointParameterIsSupported = false;

float default_attenuation[3] = {1.0, 0.0, 0.0};
//Required for using GL_extensions
void fgLoadDCS (void);
void fgUpdateDCS (void);
ssgSelector *ship_sel=NULL;
// upto 32 instances of a same object can be loaded.
ssgTransform *ship_pos[32];
double obj_lat[32],obj_lon[32],obj_alt[32],obj_pitch[32],obj_roll[32];
int objc=0;
ssgSelector *lightpoints_brightness = new ssgSelector;
ssgTransform *lightpoints_transform = new ssgTransform;
FGTileEntry *dummy_tile;
sgVec3 rway_ols;
// ADA
// Clip plane settings...
float scene_nearplane = 0.5f;
float scene_farplane = 120000.0f;

static double delta_time_sec = 0.0;


#ifdef FG_WEATHERCM
#  include <WeatherCM/FGLocalWeatherDatabase.h>
#endif

#ifdef macintosh
#  include <console.h>		// -dw- for command line dialog
#endif

FGEventMgr global_events;

// This is a record containing a bit of global housekeeping information
FGGeneral general;

// Specify our current idle function state.  This is used to run all
// our initializations out of the glutIdleLoop() so that we can get a
// splash screen up and running right away.
static int idle_state = 0;
static long global_multi_loop;

// fog constants.  I'm a little nervous about putting actual code out
// here but it seems to work (?)
static const double m_log01 = -log( 0.01 );
static const double sqrt_m_log01 = sqrt( m_log01 );
static GLfloat fog_exp_density;
static GLfloat fog_exp2_density;
static GLfloat rwy_exp2_punch_through;
static GLfloat taxi_exp2_punch_through;
static GLfloat ground_exp2_punch_through;

#ifdef FG_NETWORK_OLK
ssgSelector *fgd_sel = NULL;
ssgTransform *fgd_pos = NULL;
#endif

// Sky structures
SGSky *thesky;

#ifdef FG_USE_CLOUDS_3D
  SkySceneLoader *sgClouds3d;
  bool _bcloud_orig = true;
#endif

// hack
sgMat4 copy_of_ssgOpenGLAxisSwapMatrix =
{
  {  1.0f,  0.0f,  0.0f,  0.0f },
  {  0.0f,  0.0f, -1.0f,  0.0f },
  {  0.0f,  1.0f,  0.0f,  0.0f },
  {  0.0f,  0.0f,  0.0f,  1.0f }
};

// The following defines flightgear options. Because glutlib will also
// want to parse its own options, those options must not be included here
// or they will get parsed by the main program option parser. Hence case
// is significant for any option added that might be in conflict with
// glutlib's parser.
//
// glutlib parses for:
//    -display
//    -direct   (invalid in Win32)
//    -geometry
//    -gldebug
//    -iconized
//    -indirect (invalid in Win32)
//    -synce
//
// Note that glutlib depends upon strings while this program's
// option parser wants only initial characters followed by numbers
// or pathnames.
//


ssgSimpleState *cloud3d_imposter_state;
ssgSimpleState *default_state;
ssgSimpleState *hud_and_panel;
ssgSimpleState *menus;

SGTimeStamp last_time_stamp;
SGTimeStamp current_time_stamp;


void fgBuildRenderStates( void ) {
    default_state = new ssgSimpleState;
    default_state->ref();
    default_state->disable( GL_TEXTURE_2D );
    default_state->enable( GL_CULL_FACE );
    default_state->enable( GL_COLOR_MATERIAL );
    default_state->setColourMaterial( GL_AMBIENT_AND_DIFFUSE );
    default_state->setMaterial( GL_EMISSION, 0, 0, 0, 1 );
    default_state->setMaterial( GL_SPECULAR, 0, 0, 0, 1 );
    default_state->disable( GL_BLEND );
    default_state->disable( GL_ALPHA_TEST );
    default_state->disable( GL_LIGHTING );

    cloud3d_imposter_state = new ssgSimpleState;
    cloud3d_imposter_state->ref();
    cloud3d_imposter_state->enable( GL_TEXTURE_2D );
    cloud3d_imposter_state->enable( GL_CULL_FACE );
    cloud3d_imposter_state->enable( GL_COLOR_MATERIAL );
    cloud3d_imposter_state->setColourMaterial( GL_AMBIENT_AND_DIFFUSE );
    cloud3d_imposter_state->setMaterial( GL_DIFFUSE, 1, 1, 1, 1 );
    cloud3d_imposter_state->setMaterial( GL_AMBIENT, 1, 1, 1, 1 );
    cloud3d_imposter_state->setMaterial( GL_EMISSION, 0, 0, 0, 1 );
    cloud3d_imposter_state->setMaterial( GL_SPECULAR, 0, 0, 0, 1 );
    cloud3d_imposter_state->enable( GL_BLEND );
    cloud3d_imposter_state->enable( GL_ALPHA_TEST );
    cloud3d_imposter_state->disable( GL_LIGHTING );

    hud_and_panel = new ssgSimpleState;
    hud_and_panel->ref();
    hud_and_panel->disable( GL_CULL_FACE );
    hud_and_panel->disable( GL_TEXTURE_2D );
    hud_and_panel->disable( GL_LIGHTING );
    hud_and_panel->enable( GL_BLEND );

    menus = new ssgSimpleState;
    menus->ref();
    menus->disable( GL_CULL_FACE );
    menus->disable( GL_TEXTURE_2D );
    menus->enable( GL_BLEND );
}


// fgInitVisuals() -- Initialize various GL/view parameters
void fgInitVisuals( void ) {
    fgLIGHT *l;

    l = &cur_light_params;

#ifndef GLUT_WRONG_VERSION
    // Go full screen if requested ...
    if ( fgGetBool("/sim/startup/fullscreen") ) {
        glutFullScreen();
    }
#endif

    // If enabled, normal vectors specified with glNormal are scaled
    // to unit length after transformation.  Enabling this has
    // performance implications.  See the docs for glNormal.
    // glEnable( GL_NORMALIZE );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    // glLightfv( GL_LIGHT0, GL_POSITION, l->sun_vec );  // done later with ssg

    sgVec3 sunpos;
    sgSetVec3( sunpos, l->sun_vec[0], l->sun_vec[1], l->sun_vec[2] );
    ssgGetLight( 0 ) -> setPosition( sunpos );

    glFogi (GL_FOG_MODE, GL_EXP2);
    if ( (!strcmp(fgGetString("/sim/rendering/fog"), "disabled")) || 
         (!fgGetBool("/sim/rendering/shading"))) {
        // if fastest fog requested, or if flat shading force fastest
        glHint ( GL_FOG_HINT, GL_FASTEST );
    } else if ( !strcmp(fgGetString("/sim/rendering/fog"), "nicest") ) {
        glHint ( GL_FOG_HINT, GL_NICEST );
    }
    if ( fgGetBool("/sim/rendering/wireframe") ) {
        // draw wire frame
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    // This is the default anyways, but it can't hurt
    glFrontFace ( GL_CCW );

    // Just testing ...
    // glEnable(GL_POINT_SMOOTH);
    // glEnable(GL_LINE_SMOOTH);
    // glEnable(GL_POLYGON_SMOOTH);      
}


// For HiRes screen Dumps using Brian Pauls TR Library
void trRenderFrame( void ) {

    if ( fgPanelVisible() ) {
        GLfloat height = fgGetInt("/sim/startup/ysize");
        GLfloat view_h =
            (globals->get_current_panel()->getViewHeight() - globals->get_current_panel()->getYOffset())
            * (height / 768.0) + 1;
        glTranslatef( 0.0, view_h, 0.0 );
    }

    static GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
    static GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };

    fgLIGHT *l = &cur_light_params;

    glClearColor(l->adj_fog_color[0], l->adj_fog_color[1], 
                 l->adj_fog_color[2], l->adj_fog_color[3]);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // set the opengl state to known default values
    default_state->force();

    glEnable( GL_FOG );
    glFogf  ( GL_FOG_DENSITY, fog_exp2_density);
    glFogi  ( GL_FOG_MODE,    GL_EXP2 );
    glFogfv ( GL_FOG_COLOR,   l->adj_fog_color );

    // GL_LIGHT_MODEL_AMBIENT has a default non-zero value so if
    // we only update GL_AMBIENT for our lights we will never get
    // a completely dark scene.  So, we set GL_LIGHT_MODEL_AMBIENT
    // explicitely to black.
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, black );
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );

    ssgGetLight( 0 ) -> setColour( GL_AMBIENT, l->scene_ambient );

    // texture parameters
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ) ;
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ) ;

    // we need a white diffuse light for the phase of the moon
    ssgGetLight( 0 ) -> setColour( GL_DIFFUSE, white );
    thesky->preDraw();

    // draw the ssg scene
    // return to the desired diffuse color
    ssgGetLight( 0 ) -> setColour( GL_DIFFUSE, l->scene_diffuse );
    glEnable( GL_DEPTH_TEST );
    ssgSetNearFar( scene_nearplane, scene_farplane );
    ssgCullAndDraw( globals->get_scenery()->get_scene_graph() );

    // draw the lights
    glFogf (GL_FOG_DENSITY, rwy_exp2_punch_through);
    ssgSetNearFar( scene_nearplane, scene_farplane );
    ssgCullAndDraw( globals->get_scenery()->get_rwy_lights_root() );

    ssgCullAndDraw( globals->get_scenery()->get_gnd_lights_root() );

    if (fgGetBool("/environment/clouds/status"))
        thesky->postDraw( cur_fdm_state->get_Altitude() * SG_FEET_TO_METER );

    globals->get_model_mgr()->draw();
    globals->get_aircraft_model()->draw();
}


// Update all Visuals (redraws anything graphics related)
void fgRenderFrame() {
    bool draw_otw = fgGetBool("/sim/rendering/draw-otw");
    bool skyblend = fgGetBool("/sim/rendering/skyblend");
    bool enhanced_lighting = fgGetBool("/sim/rendering/enhanced-lighting");
    bool distance_attenuation = fgGetBool("/sim/rendering/distance-attenuation");

    GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };

    // Process/manage pending events
    global_events.update( delta_time_sec );

    // static const SGPropertyNode *longitude
    //     = fgGetNode("/position/longitude-deg");
    // static const SGPropertyNode *latitude
    //     = fgGetNode("/position/latitude-deg");
    // static const SGPropertyNode *altitude
    //     = fgGetNode("/position/altitude-ft");
    static const SGPropertyNode *groundlevel_nearplane
        = fgGetNode("/sim/current-view/ground-level-nearplane-m");

    // Update the default (kludged) properties.
    fgUpdateProps();

    FGViewer *current__view = globals->get_current_view();

    fgLIGHT *l = &cur_light_params;
    static double last_visibility = -9999;

    // update fog params
    double actual_visibility;
    if (fgGetBool("/environment/clouds/status"))
        actual_visibility = thesky->get_visibility();
    else
        actual_visibility = fgGetDouble("/environment/visibility-m");
    if ( actual_visibility != last_visibility ) {
        last_visibility = actual_visibility;

        fog_exp_density = m_log01 / actual_visibility;
        fog_exp2_density = sqrt_m_log01 / actual_visibility;
        ground_exp2_punch_through = sqrt_m_log01 / (actual_visibility * 1.5);
        if ( actual_visibility < 8000 ) {
            rwy_exp2_punch_through = sqrt_m_log01 / (actual_visibility * 2.5);
            taxi_exp2_punch_through = sqrt_m_log01 / (actual_visibility * 1.5);
        } else {
            rwy_exp2_punch_through = sqrt_m_log01 / ( 8000 * 2.5 );
            taxi_exp2_punch_through = sqrt_m_log01 / ( 8000 * 1.5 );
        }
    }

    // double angle;
    // GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
    // GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
    // GLfloat terrain_color[4] = { 0.54, 0.44, 0.29, 1.0 };
    // GLfloat mat_shininess[] = { 10.0 };
    GLbitfield clear_mask;

    if ( idle_state != 1000 ) {
        // still initializing, draw the splash screen
        if ( fgGetBool("/sim/startup/splash-screen") ) {
            fgSplashUpdate(0.0, 1.0);
        }
        // Keep resetting sim time while the sim is initializing
        globals->set_sim_time_sec( 0.0 );
        SGAnimation::set_sim_time_sec( 0.0 );
    } else {
        // idle_state is now 1000 meaning we've finished all our
        // initializations and are running the main loop, so this will
        // now work without seg faulting the system.

        // calculate our current position in cartesian space
        globals->get_scenery()->set_center( globals->get_scenery()->get_next_center() );

        // update view port
        fgReshape( fgGetInt("/sim/startup/xsize"),
                   fgGetInt("/sim/startup/ysize") );

        if ( fgGetBool("/sim/rendering/clouds3d") ) {
            glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
            cloud3d_imposter_state->force();
            glDisable( GL_FOG );
            glColor4f( 1.0, 1.0, 1.0, 1.0 );
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA ) ;

#ifdef FG_USE_CLOUDS_3D
            if ( _bcloud_orig ) {
                Point3D c = globals->get_scenery()->get_center();
                sgClouds3d->Set_Cloud_Orig( &c );
                _bcloud_orig = false;
            }
            sgClouds3d->Update( current__view->get_absolute_view_pos() );
#endif
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) ;
            glDisable(GL_DEPTH_TEST);
        }

        clear_mask = GL_DEPTH_BUFFER_BIT;
        if ( fgGetBool("/sim/rendering/wireframe") ) {
            clear_mask |= GL_COLOR_BUFFER_BIT;
        }

        if ( skyblend ) {
            if ( fgGetBool("/sim/rendering/textures") ) {
            // glClearColor(black[0], black[1], black[2], black[3]);
            glClearColor(l->adj_fog_color[0], l->adj_fog_color[1],
                         l->adj_fog_color[2], l->adj_fog_color[3]);
            clear_mask |= GL_COLOR_BUFFER_BIT;
            }
        } else {
            glClearColor(l->sky_color[0], l->sky_color[1],
                     l->sky_color[2], l->sky_color[3]);
            clear_mask |= GL_COLOR_BUFFER_BIT;
        }
        glClear( clear_mask );

        // Tell GL we are switching to model view parameters

        // I really should create a derived ssg node or use a call
        // back or something so that I can draw the sky within the
        // ssgCullAndDraw() function, but for now I just mimic what
        // ssg does to set up the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        ssgSetCamera( (sgVec4 *)current__view->get_VIEW() );

        // set the opengl state to known default values
        default_state->force();

        // update fog params if visibility has changed
        double visibility_meters = fgGetDouble("/environment/visibility-m");
        thesky->set_visibility(visibility_meters);

        thesky->modify_vis( cur_fdm_state->get_Altitude() * SG_FEET_TO_METER,
                            ( global_multi_loop * fgGetInt("/sim/speed-up") )
                            / (double)fgGetInt("/sim/model-hz") );

        // Set correct opengl fog density
        glFogf (GL_FOG_DENSITY, fog_exp2_density);

        // update the sky dome
        if ( skyblend ) {
            /*
             SG_LOG( SG_GENERAL, SG_BULK, "thesky->repaint() sky_color = "
             << cur_light_params.sky_color[0] << " "
             << cur_light_params.sky_color[1] << " "
             << cur_light_params.sky_color[2] << " "
             << cur_light_params.sky_color[3] );
            SG_LOG( SG_GENERAL, SG_BULK, "    fog = "
             << cur_light_params.fog_color[0] << " "
             << cur_light_params.fog_color[1] << " "
             << cur_light_params.fog_color[2] << " "
             << cur_light_params.fog_color[3] ); 
            SG_LOG( SG_GENERAL, SG_BULK,
                    "    sun_angle = " << cur_light_params.sun_angle
             << "    moon_angle = " << cur_light_params.moon_angle );
            */

            static SGSkyColor scolor;

            scolor.sky_color   = cur_light_params.sky_color;
            scolor.fog_color   = cur_light_params.adj_fog_color;
            scolor.cloud_color = cur_light_params.cloud_color;
            scolor.sun_angle   = cur_light_params.sun_angle;
            scolor.moon_angle  = cur_light_params.moon_angle;
            scolor.nplanets    = globals->get_ephem()->getNumPlanets();
            scolor.nstars      = globals->get_ephem()->getNumStars();
            scolor.planet_data = globals->get_ephem()->getPlanets();
            scolor.star_data   = globals->get_ephem()->getStars();

            thesky->repaint( scolor );

            /*
            SG_LOG( SG_GENERAL, SG_BULK,
                    "thesky->reposition( view_pos = " << view_pos[0] << " "
             << view_pos[1] << " " << view_pos[2] );
            SG_LOG( SG_GENERAL, SG_BULK,
                    "    zero_elev = " << zero_elev[0] << " "
             << zero_elev[1] << " " << zero_elev[2]
             << " lon = " << cur_fdm_state->get_Longitude()
             << " lat = " << cur_fdm_state->get_Latitude() );
            SG_LOG( SG_GENERAL, SG_BULK,
                    "    sun_rot = " << cur_light_params.sun_rotation
             << " gst = " << SGTime::cur_time_params->getGst() );
            SG_LOG( SG_GENERAL, SG_BULK,
                 "    sun ra = " << globals->get_ephem()->getSunRightAscension()
              << " sun dec = " << globals->get_ephem()->getSunDeclination()
              << " moon ra = " << globals->get_ephem()->getMoonRightAscension()
              << " moon dec = " << globals->get_ephem()->getMoonDeclination() );
            */

            // The sun and moon distances are scaled down versions
            // of the actual distance to get both the moon and the sun
            // within the range of the far clip plane.
            // Moon distance:    384,467 kilometers
            // Sun distance: 150,000,000 kilometers
            double sun_horiz_eff, moon_horiz_eff;
            if (fgGetBool("/sim/rendering/horizon-effect")) {
            sun_horiz_eff = 0.67+pow(0.5+cos(cur_light_params.sun_angle*2)/2,0.33)/3;
            moon_horiz_eff = 0.67+pow(0.5+cos(cur_light_params.moon_angle*2)/2,0.33)/3;
            } else {
               sun_horiz_eff = moon_horiz_eff = 1.0;
            }

            static SGSkyState sstate;

            sstate.view_pos  = current__view->get_view_pos();
            sstate.zero_elev = current__view->get_zero_elev();
            sstate.view_up   = current__view->get_world_up();
            sstate.lon       = current__view->getLongitude_deg()
                                * SGD_DEGREES_TO_RADIANS;
            sstate.lat       = current__view->getLatitude_deg()
                                * SGD_DEGREES_TO_RADIANS;
            sstate.alt       = current__view->getAltitudeASL_ft()
                                * SG_FEET_TO_METER;
            sstate.spin      = cur_light_params.sun_rotation;
            sstate.gst       = globals->get_time_params()->getGst();
            sstate.sun_ra    = globals->get_ephem()->getSunRightAscension();
            sstate.sun_dec   = globals->get_ephem()->getSunDeclination();
            sstate.sun_dist  = 50000.0 * sun_horiz_eff;
            sstate.moon_ra   = globals->get_ephem()->getMoonRightAscension();
            sstate.moon_dec  = globals->get_ephem()->getMoonDeclination();
            sstate.moon_dist = 40000.0 * moon_horiz_eff;

            thesky->reposition( sstate, delta_time_sec );
        }

        glEnable( GL_DEPTH_TEST );
        if ( strcmp(fgGetString("/sim/rendering/fog"), "disabled") ) {
            glEnable( GL_FOG );
            glFogi( GL_FOG_MODE, GL_EXP2 );
            glFogfv( GL_FOG_COLOR, l->adj_fog_color );
        }

        // set sun/lighting parameters
        ssgGetLight( 0 ) -> setPosition( l->sun_vec );

        // GL_LIGHT_MODEL_AMBIENT has a default non-zero value so if
        // we only update GL_AMBIENT for our lights we will never get
        // a completely dark scene.  So, we set GL_LIGHT_MODEL_AMBIENT
        // explicitely to black.
        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, black );

        ssgGetLight( 0 ) -> setColour( GL_AMBIENT, l->scene_ambient );
        ssgGetLight( 0 ) -> setColour( GL_DIFFUSE, l->scene_diffuse );
        ssgGetLight( 0 ) -> setColour( GL_SPECULAR, l->scene_specular );

        // texture parameters
        // glEnable( GL_TEXTURE_2D );
        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ) ;
        glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ) ;

        // glMatrixMode( GL_PROJECTION );
        // glLoadIdentity();
        ssgSetFOV( current__view->get_h_fov(),
                   current__view->get_v_fov() );

        double agl =
            current_aircraft.fdm_state->get_Altitude() * SG_FEET_TO_METER
            - globals->get_scenery()->get_cur_elev();

        if ( agl > 10.0 ) {
            scene_nearplane = 10.0f;
            scene_farplane = 120000.0f;
        } else {
            scene_nearplane = groundlevel_nearplane->getDoubleValue();
            scene_farplane = 120000.0f;
        }

        ssgSetNearFar( scene_nearplane, scene_farplane );

        // $$$ begin - added VS Renganthan 17 Oct 2K
        if(objc)
          fgUpdateDCS();
        // $$$ end - added VS Renganthan 17 Oct 2K

# ifdef FG_NETWORK_OLK
        if ( fgGetBool("/sim/networking/network-olk") ) {
            sgCoord fgdpos;
            other = head->next;             /* put listpointer to start  */
            while ( other != tail) {        /* display all except myself */
            if ( strcmp( other->ipadr, fgd_mcp_ip) != 0) {
                other->fgd_sel->select(1);
                sgSetCoord( &fgdpos, other->sgFGD_COORD );
                other->fgd_pos->setTransform( &fgdpos );
            }
            other = other->next;
            }

            // fgd_sel->select(1);
            // sgCopyMat4( sgTUX, current_view.sgVIEW);
            // sgCoord fgdpos;
            // sgSetCoord( &fgdpos, sgFGD_VIEW );
            // fgd_pos->setTransform( &fgdpos);
        }
# endif

#ifdef FG_MPLAYER_AS
        // Update any multiplayer models
        globals->get_multiplayer_rx_mgr()->Update();
#endif

        if ( draw_otw && skyblend )
        {
            // draw the sky backdrop

            // we need a white diffuse light for the phase of the moon
            ssgGetLight( 0 ) -> setColour( GL_DIFFUSE, white );

            thesky->preDraw();

            // return to the desired diffuse color
            ssgGetLight( 0 ) -> setColour( GL_DIFFUSE, l->scene_diffuse );

            // FIXME: This should not be needed, but at this time (08/15/2003)
            //        certain NVidia drivers don't seem to implement
            //        fgPushAttrib(FG_FOG_BIT) properly. The result is that
            //        there is not fog when looking at the sun.
            glFogf ( GL_FOG_DENSITY, fog_exp2_density );
        }

        // draw the ssg scene
        glEnable( GL_DEPTH_TEST );

        ssgSetNearFar( scene_nearplane, scene_farplane );

        if ( fgGetBool("/sim/rendering/wireframe") ) {
            // draw wire frame
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        if ( draw_otw ) {
            ssgCullAndDraw( globals->get_scenery()->get_scene_graph() );
        }

        // This is a bit kludgy.  Every 200 frames, do an extra
        // traversal of the scene graph without drawing anything, but
        // with the field-of-view set to 360x360 degrees.  This
        // ensures that out-of-range random objects that are not in
        // the current view frustum will still be freed properly.
        static int counter = 0;
        counter++;
        if (counter == 200) {
          sgFrustum f;
          f.setFOV(360, 360);
                            // No need to put the near plane too close;
                            // this way, at least the aircraft can be
                            // culled.
          f.setNearFar(1000, 1000000);
          sgMat4 m;
          ssgGetModelviewMatrix(m);
          globals->get_scenery()->get_scene_graph()->cull(&f, m, true);
          counter = 0;
        }

        // change state for lighting here

        // draw runway lighting
        glFogf (GL_FOG_DENSITY, rwy_exp2_punch_through);
        ssgSetNearFar( scene_nearplane, scene_farplane );

        if ( enhanced_lighting ) {

            // Enable states for drawing points with GL_extension
            glEnable(GL_POINT_SMOOTH);

            if ( distance_attenuation && glPointParameterIsSupported )
            {
                // Enable states for drawing points with GL_extension
                glEnable(GL_POINT_SMOOTH);

                float quadratic[3] = {1.0, 0.001, 0.0000001};
                // makes the points fade as they move away
                glPointParameterfvPtr(GL_DISTANCE_ATTENUATION_EXT, quadratic);
                glPointParameterfPtr(GL_POINT_SIZE_MIN_EXT, 1.0); 
            }

            glPointSize(4.0);

            // blending function for runway lights
            glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
        }

        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glPolygonMode(GL_FRONT, GL_POINT);

        // draw runway lighting
        if ( draw_otw ) {
            ssgCullAndDraw( globals->get_scenery()->get_rwy_lights_root() );
        }

        // change punch through and then draw taxi lighting
        glFogf ( GL_FOG_DENSITY, fog_exp2_density );
        // sgVec3 taxi_fog;
        // sgSetVec3( taxi_fog, 0.0, 0.0, 0.0 );
        // glFogfv ( GL_FOG_COLOR, taxi_fog );
        if ( draw_otw ) {
            ssgCullAndDraw( globals->get_scenery()->get_taxi_lights_root() );
        }

        // clean up lighting
        glPolygonMode(GL_FRONT, GL_FILL);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);

        //static int _frame_count = 0;
        //if (_frame_count % 30 == 0) {
        //  printf("SSG: %s\n", ssgShowStats());
        //}
        //else {
        //  ssgShowStats();
        //}
        //_frame_count++;


        if ( enhanced_lighting ) {
            if ( distance_attenuation && glPointParameterIsSupported )
            {
                glPointParameterfvPtr(GL_DISTANCE_ATTENUATION_EXT,
                                      default_attenuation);
            }

            glPointSize(1.0);
            glDisable(GL_POINT_SMOOTH);
        }

        // draw ground lighting
        glFogf (GL_FOG_DENSITY, ground_exp2_punch_through);
        if ( draw_otw ) {
            ssgCullAndDraw( globals->get_scenery()->get_gnd_lights_root() );
        }

        if ( skyblend ) {
            // draw the sky cloud layers
            if ( draw_otw && fgGetBool("/environment/clouds/status") )
            {
                thesky->postDraw( cur_fdm_state->get_Altitude()
                                  * SG_FEET_TO_METER );
            }
        }

        if ( draw_otw && fgGetBool("/sim/rendering/clouds3d") )
        {
            glDisable( GL_FOG );
            glDisable( GL_LIGHTING );
            // cout << "drawing new clouds" << endl;

            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA ) ;

            /*
            glEnable( GL_TEXTURE_2D );
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            */

#ifdef FG_USE_CLOUDS_3D
            sgClouds3d->Draw((sgVec4 *)current__view->get_VIEW());
#endif
            glEnable( GL_FOG );
            glEnable( GL_LIGHTING );
            glEnable( GL_DEPTH_TEST );
            glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) ;
        }

        if ( draw_otw ) {
            globals->get_model_mgr()->draw();
            globals->get_aircraft_model()->draw();
        }

        // display HUD && Panel
        glDisable( GL_FOG );
        glDisable( GL_DEPTH_TEST );
        // glDisable( GL_CULL_FACE );
        // glDisable( GL_TEXTURE_2D );

        // update the controls subsystem
        globals->get_controls()->update(delta_time_sec);

        hud_and_panel->apply();
        fgCockpitUpdate();

        // Use the hud_and_panel ssgSimpleState for rendering the ATC output
        // This only works properly if called before the panel call
        if((fgGetBool("/sim/ATC/enabled")) || (fgGetBool("/sim/ai-traffic/enabled")))
            globals->get_ATC_display()->update(delta_time_sec);

        // update the panel subsystem
        if ( globals->get_current_panel() != NULL ) {
            globals->get_current_panel()->update(delta_time_sec);
        }
        fgUpdate3DPanels();

        // We can do translucent menus, so why not. :-)
        menus->apply();
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) ;
        puDisplay();
        // glDisable ( GL_BLEND ) ;

        glEnable( GL_DEPTH_TEST );
        glEnable( GL_FOG );

        // Fade out the splash screen over the first three seconds.
        double t = globals->get_sim_time_sec();
        if ( t <= 1.0 ) {
            fgSplashUpdate(0.0, 1.0);
        } else if ( t <= 3.0) {
            fgSplashUpdate(0.0, (3.0 - t) / 2.0);
        }
    }

    glutSwapBuffers();
}


// Update internal time dependent calculations (i.e. flight model)
// FIXME: this distinction is obsolete; all subsystems now get delta
// time on update.
void fgUpdateTimeDepCalcs() {
    static bool inited = false;

    static const SGPropertyNode *replay_master
        = fgGetNode( "/sim/freeze/replay", true );
    static SGPropertyNode *replay_time
        = fgGetNode( "/sim/replay/time", true );
    static const SGPropertyNode *replay_end_time
        = fgGetNode( "/sim/replay/end-time", true );

    //SG_LOG(SG_FLIGHT,SG_INFO, "Updating time dep calcs()");

    fgLIGHT *l = &cur_light_params;

    // Initialize the FDM here if it hasn't been and if we have a
    // scenery elevation hit.

    // cout << "cur_fdm_state->get_inited() = " << cur_fdm_state->get_inited() 
    //      << " cur_elev = " << scenery.get_cur_elev() << endl;

    if ( !cur_fdm_state->get_inited() &&
         globals->get_scenery()->get_cur_elev() > -9990 )
    {
        SG_LOG(SG_FLIGHT,SG_INFO, "Finally initializing fdm");  
        cur_fdm_state->init();
        if ( cur_fdm_state->get_bound() ) {
            cur_fdm_state->unbind();
        }
        cur_fdm_state->bind();
    }

    // conceptually, the following block could be done for each fdm
    // instance ...
    if ( cur_fdm_state->get_inited() ) {
        // we have been inited, and  we are good to go ...

        if ( !inited ) {
            inited = true;
        }

        if ( ! replay_master->getBoolValue() ) {
            globals->get_autopilot()->update( delta_time_sec );
            cur_fdm_state->update( delta_time_sec );
        } else {
            FGReplay *r = (FGReplay *)(globals->get_subsystem( "replay" ));
            r->replay( replay_time->getDoubleValue() );
            replay_time->setDoubleValue( replay_time->getDoubleValue()
                                         + ( delta_time_sec
                                             * fgGetInt("/sim/speed-up") ) );
        }
    } else {
        // do nothing, fdm isn't inited yet
    }

    globals->get_model_mgr()->update(delta_time_sec);
    globals->get_aircraft_model()->update(delta_time_sec);

    // update the view angle
    globals->get_viewmgr()->update(delta_time_sec);

    l->UpdateAdjFog();

    // Update solar system
    globals->get_ephem()->update( globals->get_time_params()->getMjd(),
                              globals->get_time_params()->getLst(),
                              cur_fdm_state->get_Latitude() );

    // Update radio stack model
    current_radiostack->update(delta_time_sec);
}


void fgInitTimeDepCalcs( void ) {
    // noop for now
}


static const double alt_adjust_ft = 3.758099;
static const double alt_adjust_m = alt_adjust_ft * SG_FEET_TO_METER;


// What should we do when we have nothing else to do?  Let's get ready
// for the next move and update the display?
static void fgMainLoop( void ) {
    int model_hz = fgGetInt("/sim/model-hz");

    static const SGPropertyNode *longitude
        = fgGetNode("/position/longitude-deg");
    static const SGPropertyNode *latitude
        = fgGetNode("/position/latitude-deg");
    static const SGPropertyNode *altitude
        = fgGetNode("/position/altitude-ft");
    static const SGPropertyNode *clock_freeze
        = fgGetNode("/sim/freeze/clock", true);
    static const SGPropertyNode *cur_time_override
        = fgGetNode("/sim/time/cur-time-override", true);
    static const SGPropertyNode *replay_master
        = fgGetNode("/sim/freeze/replay", true);

    // Update the elapsed time.
    static bool first_time = true;
    if ( first_time ) {
        last_time_stamp.stamp();
        first_time = false;
    }

    double throttle_hz = fgGetDouble("/sim/frame-rate-throttle-hz", 0.0);
    if ( throttle_hz > 0.0 ) {
        // simple frame rate throttle
        double dt = 1000000.0 / throttle_hz;
        current_time_stamp.stamp();
        while ( current_time_stamp - last_time_stamp < dt ) {
            current_time_stamp.stamp();
        }
    } else {
        // run as fast as the app will go
        current_time_stamp.stamp();
    }

    delta_time_sec = double(current_time_stamp - last_time_stamp) / 1000000.0;
    if ( clock_freeze->getBoolValue() ) {
        delta_time_sec = 0;
    } 
    last_time_stamp = current_time_stamp;
    globals->inc_sim_time_sec( delta_time_sec );
    SGAnimation::set_sim_time_sec( globals->get_sim_time_sec() );

    static long remainder = 0;
    long elapsed;
#ifdef FANCY_FRAME_COUNTER
    int i;
    double accum;
#else
    static time_t last_time = 0;
    static int frames = 0;
#endif // FANCY_FRAME_COUNTER

    SGTime *t = globals->get_time_params();

    sglog().setLogLevels( SG_ALL, (sgDebugPriority)fgGetInt("/sim/log-level") );
    sglog().setLogLevels( SG_ALL, SG_INFO );

    SGLocation * acmodel_location = 0;
    if(cur_fdm_state->getACModel() != 0) {
      acmodel_location = (SGLocation *)  cur_fdm_state->getACModel()->get3DModel()->getSGLocation();
    }

    SG_LOG( SG_ALL, SG_DEBUG, "Running Main Loop");
    SG_LOG( SG_ALL, SG_DEBUG, "======= ==== ====");

#ifdef FG_NETWORK_OLK
    if ( fgGetBool("/sim/networking/network-olk") ) {
        if ( net_is_registered == 0 ) {	     // We first have to reg. to fgd
            // printf("FGD: Netupdate\n");
            fgd_send_com( "A", FGFS_host);   // Send Mat4 data
            fgd_send_com( "B", FGFS_host);   // Recv Mat4 data
        }
    }
#endif

#if defined( ENABLE_PLIB_JOYSTICK )
    // Read joystick and update control settings
    // if ( fgGetString("/sim/control-mode") == "joystick" )
    // {
    //    fgJoystickRead();
    // }
#elif defined( ENABLE_GLUT_JOYSTICK )
    // Glut joystick support works by feeding a joystick handler
    // function to glut.  This is taken care of once in the joystick
    // init routine and we don't have to worry about it again.
#endif

    // Fix elevation.  I'm just sticking this here for now, it should
    // probably move eventually

    /* printf("Before - ground = %.2f  runway = %.2f  alt = %.2f\n",
           scenery.get_cur_elev(),
           cur_fdm_state->get_Runway_altitude() * SG_FEET_TO_METER,
           cur_fdm_state->get_Altitude() * SG_FEET_TO_METER); */

#if 0
// This code is used by LaRCsim/UIUC to position the aircraft at a proper
// place. This code should eventually go into the LaRCsim directory.
// Commented out at Jul 27 2003 because tests show it is not needed.
// Can probbaly be safely removed after Spet. 2003 - EMH

    if ( acmodel_location != 0 ) {
      if ( acmodel_location->get_cur_elev_m() > -9990 && cur_fdm_state->get_inited() ) {
        if ( cur_fdm_state->get_Altitude() * SG_FEET_TO_METER < 
             (acmodel_location->get_cur_elev_m() + alt_adjust_m - 130.0) ) {
            // now set aircraft altitude above ground
            printf("(*) Current Altitude = %.2f < %.2f forcing to %.2f\n", 
               cur_fdm_state->get_Altitude() * SG_FEET_TO_METER,
               acmodel_location->get_cur_elev_m() + alt_adjust_m - 130.0,
               acmodel_location->get_cur_elev_m() + alt_adjust_m );
            cur_fdm_state->set_Altitude( (acmodel_location->get_cur_elev_m() 
                                                + alt_adjust_m) * SG_METER_TO_FEET );
            SG_LOG( SG_ALL, SG_DEBUG, 
                "<*> resetting altitude to " 
                << cur_fdm_state->get_Altitude() * SG_FEET_TO_METER
                << " meters" );
        }
      }
    }
// End of code in question. (see Curt is this code used? above)
#endif

    /* printf("Adjustment - ground = %.2f  runway = %.2f  alt = %.2f\n",
           scenery.get_cur_elev(),
           cur_fdm_state->get_Runway_altitude() * SG_FEET_TO_METER,
           cur_fdm_state->get_Altitude() * SG_FEET_TO_METER); */

    // cout << "Warp = " << globals->get_warp() << endl;

    // update "time"
    static bool last_clock_freeze = false;

    if ( clock_freeze->getBoolValue() ) {
        // clock freeze requested
        if ( cur_time_override->getLongValue() == 0 ) {
            fgSetLong( "/sim/time/cur-time-override", t->get_cur_time() );
            globals->set_warp( 0 );
        }
    } else {
        // no clock freeze requested
        if ( last_clock_freeze == true ) {
            // clock just unfroze, let's set warp as the difference
            // between frozen time and current time so we don't get a
            // time jump (and corresponding sky object and lighting
            // jump.)
            globals->set_warp( cur_time_override->getLongValue() - time(NULL) );
            fgSetLong( "/sim/time/cur-time-override", 0 );
        }
        if ( globals->get_warp_delta() != 0 ) {
            globals->inc_warp( globals->get_warp_delta() );
        }
    }

    last_clock_freeze = clock_freeze->getBoolValue();

    t->update( longitude->getDoubleValue() * SGD_DEGREES_TO_RADIANS,
               latitude->getDoubleValue() * SGD_DEGREES_TO_RADIANS,
               cur_time_override->getLongValue(),
               globals->get_warp() );

    if ( globals->get_warp_delta() != 0 ) {
        fgUpdateSkyAndLightingParams();
    }

    // update magvar model
    globals->get_mag()->update( longitude->getDoubleValue()
                              * SGD_DEGREES_TO_RADIANS,
                            latitude->getDoubleValue()
                              * SGD_DEGREES_TO_RADIANS,
                            altitude->getDoubleValue() * SG_FEET_TO_METER,
                            globals->get_time_params()->getJD() );

    // Get elapsed time (in usec) for this past frame
    elapsed = fgGetTimeInterval();
    SG_LOG( SG_ALL, SG_DEBUG, 
            "Elapsed time interval is = " << elapsed 
            << ", previous remainder is = " << remainder );

    // Calculate frame rate average
#ifdef FANCY_FRAME_COUNTER
    /* old fps calculation */
    if ( elapsed > 0 ) {
        double tmp;
        accum = 0.0;
        for ( i = FG_FRAME_RATE_HISTORY - 2; i >= 0; i-- ) {
            tmp = general.get_frame(i);
            accum += tmp;
            // printf("frame[%d] = %.2f\n", i, g->frames[i]);
            general.set_frame(i+1,tmp);
        }
        tmp = 1000000.0 / (float)elapsed;
        general.set_frame(0,tmp);
        // printf("frame[0] = %.2f\n", general.frames[0]);
        accum += tmp;
        general.set_frame_rate(accum / (float)FG_FRAME_RATE_HISTORY);
        // printf("ave = %.2f\n", general.frame_rate);
    }
#else
    if ( (t->get_cur_time() != last_time) && (last_time > 0) ) {
        general.set_frame_rate( frames );
        fgSetInt("/sim/frame-rate", frames);
        SG_LOG( SG_ALL, SG_DEBUG, 
            "--> Frame rate is = " << general.get_frame_rate() );
        frames = 0;
    }
    last_time = t->get_cur_time();
    ++frames;
#endif

    // Run ATC subsystem
    if (fgGetBool("/sim/ATC/enabled"))
        globals->get_ATC_mgr()->update(delta_time_sec);

    // Run the AI subsystem
    if (fgGetBool("/sim/ai-traffic/enabled"))
        globals->get_AI_mgr()->update(delta_time_sec);

    // Run flight model

    // Calculate model iterations needed for next frame
    elapsed += remainder;

    global_multi_loop = (long)(((double)elapsed * 0.000001) * model_hz );
    remainder = elapsed - ( (global_multi_loop*1000000) / model_hz );
    SG_LOG( SG_ALL, SG_DEBUG, 
            "Model iterations needed = " << global_multi_loop
            << ", new remainder = " << remainder );
        
    // chop max interations to something reasonable if the sim was
    // delayed for an excesive amount of time
    if ( global_multi_loop > 2.0 * model_hz ) {
        global_multi_loop = (int)(2.0 * model_hz );
        remainder = 0;
    }

    // flight model
    if ( global_multi_loop > 0 ) {
        fgUpdateTimeDepCalcs();
    } else {
        SG_LOG( SG_ALL, SG_DEBUG, 
            "Elapsed time is zero ... we're zinging" );
    }

    // Do any I/O channel work that might need to be done
    globals->get_io()->update( delta_time_sec );

    // see if we need to load any deferred-load textures
    globals->get_matlib()->load_next_deferred();

    // Run audio scheduler
#ifdef ENABLE_AUDIO_SUPPORT
    if ( fgGetBool("/sim/sound/audible")
           && globals->get_soundmgr()->is_working() ) {
        globals->get_soundmgr()->update( delta_time_sec );
    }
#endif

    globals->get_subsystem_mgr()->update(delta_time_sec);

    //
    // Tile Manager updates - see if we need to load any new scenery tiles.
    //   this code ties together the fdm, viewer and scenery classes...
    //   we may want to move this to it's own class at some point
    //
    double visibility_meters = fgGetDouble("/environment/visibility-m");
    FGViewer *current_view = globals->get_current_view();

    // update tile manager for FDM...
    // ...only if location is different than the viewer (to avoid duplicating effort)
    if( acmodel_location != current_view->getSGLocation() ) {
      if( acmodel_location != 0 ) {
        globals->get_tile_mgr()->prep_ssg_nodes( acmodel_location,
                                                 visibility_meters );
        globals->get_tile_mgr()->
            update( acmodel_location, visibility_meters,
                    acmodel_location->get_absolute_view_pos(globals->get_scenery()->get_center()) );
        // save results of update in SGLocation for fdm...
        if ( globals->get_scenery()->get_cur_elev() > -9990 ) {
          acmodel_location->
              set_cur_elev_m( globals->get_scenery()->get_cur_elev() );
        }
        acmodel_location->
            set_tile_center( globals->get_scenery()->get_next_center() );
      }
    }

    globals->get_tile_mgr()->prep_ssg_nodes( current_view->getSGLocation(),
                                             visibility_meters );
    // update tile manager for view...
    // IMPORTANT!!! the tilemgr update for view location _must_ be done last 
    // after the FDM's until all of Flight Gear code references the viewer's location
    // for elevation instead of the "scenery's" current elevation.
    SGLocation *view_location = globals->get_current_view()->getSGLocation();
    globals->get_tile_mgr()->update( view_location, visibility_meters,
                                     current_view->get_absolute_view_pos() );
    // save results of update in SGLocation for fdm...
    if ( globals->get_scenery()->get_cur_elev() > -9990 ) {
      current_view->getSGLocation()->set_cur_elev_m( globals->get_scenery()->get_cur_elev() );
    }
    current_view->getSGLocation()->set_tile_center( globals->get_scenery()->get_next_center() );

    // If fdm location is same as viewer's then we didn't do the update for fdm location 
    //   above so we need to save the viewer results in the fdm SGLocation as well...
    if( acmodel_location == current_view->getSGLocation() ) {
      if( acmodel_location != 0 ) {
        if ( globals->get_scenery()->get_cur_elev() > -9990 ) {
          acmodel_location->set_cur_elev_m( globals->get_scenery()->get_cur_elev() );
        }
        acmodel_location->set_tile_center( globals->get_scenery()->get_next_center() );
      }
    }

    // END Tile Manager udpates

    // redraw display
    fgRenderFrame();

    SG_LOG( SG_ALL, SG_DEBUG, "" );
}


// This is the top level master main function that is registered as
// our idle funciton

// The first few passes take care of initialization things (a couple
// per pass) and once everything has been initialized fgMainLoop from
// then on.

static void fgIdleFunction ( void ) {
    // printf("idle state == %d\n", idle_state);

    if ( idle_state == 0 ) {
        // Initialize the splash screen right away
        if ( fgGetBool("/sim/startup/splash-screen") ) {
            fgSplashInit();
        }
        
        idle_state++;
    } else if ( idle_state == 1 ) {
        // Initialize audio support
#ifdef ENABLE_AUDIO_SUPPORT

        // Start the intro music
        if ( fgGetBool("/sim/startup/intro-music") ) {
            SGPath mp3file( globals->get_fg_root() );
            mp3file.append( "Sounds/intro.mp3" );

            SG_LOG( SG_GENERAL, SG_INFO, 
                "Starting intro music: " << mp3file.str() );

#if defined( __CYGWIN__ )
            string command = "start /m `cygpath -w " + mp3file.str() + "`";
#elif defined( WIN32 )
            string command = "start /m " + mp3file.str();
#else
            string command = "mpg123 " + mp3file.str() + "> /dev/null 2>&1";
#endif

            system ( command.c_str() );
        }
#endif

        idle_state++;
    } else if ( idle_state == 2 ) {
        // These are a few miscellaneous things that aren't really
        // "subsystems" but still need to be initialized.

#ifdef USE_GLIDE
        if ( strstr ( general.get_glRenderer(), "Glide" ) ) {
            grTexLodBiasValue ( GR_TMU0, 1.0 ) ;
        }
#endif

        idle_state++;
    } else if ( idle_state == 3 ) {
        // This is the top level init routine which calls all the
        // other subsystem initialization routines.  If you are adding
        // a subsystem to flightgear, its initialization call should
        // located in this routine.
        if( !fgInitSubsystems()) {
            SG_LOG( SG_GENERAL, SG_ALERT,
                "Subsystem initializations failed ..." );
            exit(-1);
        }

        idle_state++;
    } else if ( idle_state == 4 ) {
        // setup OpenGL view parameters
        fgInitVisuals();

        // Read the list of available aircrafts
        fgReadAircraft();

        idle_state++;
    } else if ( idle_state == 5 ) {

        idle_state++;
    } else if ( idle_state == 6 ) {
        // sleep(1);
        idle_state = 1000;

        SG_LOG( SG_GENERAL, SG_INFO, "Panel visible = " << fgPanelVisible() );
        fgReshape( fgGetInt("/sim/startup/xsize"),
               fgGetInt("/sim/startup/ysize") );
    } 

    if ( idle_state == 1000 ) {
        // We've finished all our initialization steps, from now on we
        // run the main loop.

        glutIdleFunc(fgMainLoop);
    } else {
        if ( fgGetBool("/sim/startup/splash-screen") ) {
            fgSplashUpdate(0.0, 1.0);
        }
    }
}

// options.cxx needs to see this for toggle_panel()
// Handle new window size or exposure
void fgReshape( int width, int height ) {
    int view_h;

    if ( (!fgGetBool("/sim/virtual-cockpit"))
         && fgPanelVisible() && idle_state == 1000 ) {
        view_h = (int)(height * (globals->get_current_panel()->getViewHeight() -
                             globals->get_current_panel()->getYOffset()) / 768.0);
    } else {
        view_h = height;
    }

    // for all views
    FGViewMgr *viewmgr = globals->get_viewmgr();
    for ( int i = 0; i < viewmgr->size(); ++i ) {
      viewmgr->get_view(i)->
        set_aspect_ratio((float)view_h / (float)width);
    }

    glViewport( 0, (GLint)(height - view_h), (GLint)(width), (GLint)(view_h) );

    fgSetInt("/sim/startup/xsize", width);
    fgSetInt("/sim/startup/ysize", height);
    guiInitMouse(width, height);

    ssgSetFOV( viewmgr->get_current_view()->get_h_fov(),
               viewmgr->get_current_view()->get_v_fov() );

    fgHUDReshape();

#ifdef FG_USE_CLOUDS_3D
    sgClouds3d->Resize( viewmgr->get_current_view()->get_h_fov(),
                        viewmgr->get_current_view()->get_v_fov() );
#endif

}

// Initialize GLUT and define a main window
static bool fgGlutInit( int *argc, char **argv ) {

#if !defined( macintosh )
    // GLUT will extract all glut specific options so later on we only
    // need wory about our own.
    glutInit(argc, argv);
#endif

    // Define Display Parameters. Clouds3d works best with --bpp32 option
    if ( fgGetBool("/sim/rendering/clouds3d") ) {
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA );
    } else {
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    }

    SG_LOG( SG_GENERAL, SG_INFO, "Opening a window: " <<
            fgGetInt("/sim/startup/xsize") << "x"
            << fgGetInt("/sim/startup/ysize") );

    // Define initial window size
    glutInitWindowSize( fgGetInt("/sim/startup/xsize"),
                    fgGetInt("/sim/startup/ysize") );

    // Initialize windows
    if ( !fgGetBool("/sim/startup/game-mode")) {
        // Open the regular window
        glutCreateWindow("FlightGear");
#ifndef GLUT_WRONG_VERSION
    } else {
        // Open the cool new 'game mode' window
        char game_mode_str[256];
//#define SYNC_OPENGL_WITH_DESKTOP_SETTINGS
#if defined(WIN32) && defined(SYNC_OPENGL_WITH_DESKTOP_SETTINGS)
#ifndef ENUM_CURRENT_SETTINGS
#define ENUM_CURRENT_SETTINGS       ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS      ((DWORD)-2)
#endif

        DEVMODE dm;
        dm.dmSize = sizeof(DEVMODE);
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
        fgSetInt("/sim/startup/xsize", dm.dmPelsWidth);
        fgSetInt("/sim/startup/ysize", dm.dmPelsHeight);
        glutInitWindowSize( fgGetInt("/sim/startup/xsize"),
                            fgGetInt("/sim/startup/ysize") );
        sprintf( game_mode_str, "%dx%d:%d@%d",
                     dm.dmPelsWidth,
                     dm.dmPelsHeight,
                     dm.dmBitsPerPel,
                     dm.dmDisplayFrequency );
#else
        // Open the cool new 'game mode' window
        sprintf( game_mode_str, "width=%d height=%d bpp=%d",
             fgGetInt("/sim/startup/xsize"),
             fgGetInt("/sim/startup/ysize"),
             fgGetInt("/sim/rendering/bits-per-pixel"));

#endif // HAVE_WINDOWS_H
        SG_LOG( SG_GENERAL, SG_INFO, 
            "game mode params = " << game_mode_str );
        glutGameModeString( game_mode_str );
        glutEnterGameMode();
#endif // GLUT_WRONG_VERSION
    }

    // This seems to be the absolute earliest in the init sequence
    // that these calls will return valid info.  Too bad it's after
    // we've already created and sized out window. :-(
    general.set_glVendor( (char *)glGetString ( GL_VENDOR ) );
    general.set_glRenderer( (char *)glGetString ( GL_RENDERER ) );
    general.set_glVersion( (char *)glGetString ( GL_VERSION ) );
    SG_LOG( SG_GENERAL, SG_INFO, general.get_glRenderer() );

    GLint tmp;
    glGetIntegerv( GL_MAX_TEXTURE_SIZE, &tmp );
    general.set_glMaxTexSize( tmp );
    SG_LOG ( SG_GENERAL, SG_INFO, "Max texture size = " << tmp );

    glGetIntegerv( GL_DEPTH_BITS, &tmp );
    general.set_glDepthBits( tmp );
    SG_LOG ( SG_GENERAL, SG_INFO, "Depth buffer bits = " << tmp );

    return true;
}


// Initialize GLUT event handlers
static bool fgGlutInitEvents( void ) {
    // call fgReshape() on window resizes
    glutReshapeFunc( fgReshape );

    // keyboard and mouse callbacks are set in FGInput::init

    // call fgMainLoop() whenever there is
    // nothing else to do
    glutIdleFunc( fgIdleFunction );

    // draw the scene
    glutDisplayFunc( fgRenderFrame );

    return true;
}

// Main top level initialization
bool fgMainInit( int argc, char **argv ) {

#if defined( macintosh )
    freopen ("stdout.txt", "w", stdout );
    freopen ("stderr.txt", "w", stderr );
    argc = ccommand( &argv );
#endif

    // set default log levels
    sglog().setLogLevels( SG_ALL, SG_INFO );

    string version;
#ifdef FLIGHTGEAR_VERSION
    version = FLIGHTGEAR_VERSION;
#else
    version = "unknown version";
#endif
    SG_LOG( SG_GENERAL, SG_INFO, "FlightGear:  Version "
            << version );
    SG_LOG( SG_GENERAL, SG_INFO, "Built with " << SG_COMPILER_STR << endl );

    // Allocate global data structures.  This needs to happen before
    // we parse command line options

    globals = new FGGlobals;

    // seed the random number generater
    sg_srandom_time();

    SGRoute *route = new SGRoute;
    globals->set_route( route );

    FGControls *controls = new FGControls;
    globals->set_controls( controls );

    string_list *col = new string_list;
    globals->set_channel_options_list( col );

    // Scan the config file(s) and command line options to see if
    // fg_root was specified (ignore all other options for now)
    fgInitFGRoot(argc, argv);

    // Check for the correct base package version
    static char required_version[] = "0.9.2";
    string base_version = fgBasePackageVersion();
    if ( !(base_version == required_version) ) {
        // tell the operator how to use this application

        cerr << endl << "Base package check failed ... " \
             << "Found version " << base_version << " at: " \
             << globals->get_fg_root() << endl;
        cerr << "Please upgrade to version: " << required_version << endl;
        exit(-1);
    }

    // Initialize the Aircraft directory to "" (UIUC)
    aircraft_dir = "";

    // Load the configuration parameters.  (Command line options
    // overrides config file options.  Config file options override
    // defaults.)
    if ( !fgInitConfig(argc, argv) ) {
        SG_LOG( SG_GENERAL, SG_ALERT, "Config option parsing failed ..." );
        exit(-1);
    }

    // Initialize the Window/Graphics environment.
    if( !fgGlutInit(&argc, argv) ) {
        SG_LOG( SG_GENERAL, SG_ALERT, "GLUT initialization failed ..." );
        exit(-1);
    }

    // Initialize the various GLUT Event Handlers.
    if( !fgGlutInitEvents() ) {
        SG_LOG( SG_GENERAL, SG_ALERT, 
        	"GLUT event handler initialization failed ..." );
        exit(-1);
    }

    // Initialize plib net interface
    netInit( &argc, argv );

    // Initialize ssg (from plib).  Needs to come before we do any
    // other ssg stuff, but after opengl/glut has been initialized.
    ssgInit();

    // Initialize the user interface (we need to do this before
    // passing off control to glut and before fgInitGeneral to get our
    // fonts !!!
    guiInit();

    // Read the list of available aircrafts
    fgReadAircraft();

#ifdef GL_EXT_texture_lod_bias
    glTexEnvf( GL_TEXTURE_FILTER_CONTROL_EXT, GL_TEXTURE_LOD_BIAS_EXT, -0.5 ) ;
#endif

            // get the address of our OpenGL extensions
    if ( fgGetBool("/sim/rendering/distance-attenuation") )
    {
        if (SGIsOpenGLExtensionSupported("GL_EXT_point_parameters") ) {
            glPointParameterIsSupported = true;
            glPointParameterfPtr = (glPointParameterfProc)
                                   SGLookupFunction("glPointParameterfEXT");
            glPointParameterfvPtr = (glPointParameterfvProc)
                                    SGLookupFunction("glPointParameterfvEXT");

        } else if ( SGIsOpenGLExtensionSupported("GL_ARB_point_parameters") ) {
            glPointParameterIsSupported = true;
            glPointParameterfPtr = (glPointParameterfProc)
                                   SGLookupFunction("glPointParameterfARB");
            glPointParameterfvPtr = (glPointParameterfvProc)
                                    SGLookupFunction("glPointParameterfvARB");
        } else
            glPointParameterIsSupported = false;
   }

    // based on the requested presets, calculate the true starting
    // lon, lat
    fgInitNav();
    fgInitPosition();

    SGTime *t = fgInitTime();
    globals->set_time_params( t );

    // Do some quick general initializations
    if( !fgInitGeneral()) {
        SG_LOG( SG_GENERAL, SG_ALERT, 
            "General initializations failed ..." );
        exit(-1);
    }

    SGPath modelpath( globals->get_fg_root() );
    ssgModelPath( (char *)modelpath.c_str() );

    ////////////////////////////////////////////////////////////////////
    // Initialize the property-based built-in commands
    ////////////////////////////////////////////////////////////////////
    fgInitCommands();

    ////////////////////////////////////////////////////////////////////
    // Initialize the material manager
    ////////////////////////////////////////////////////////////////////
    globals->set_matlib( new SGMaterialLib );

    globals->set_model_lib(new SGModelLib);

    ////////////////////////////////////////////////////////////////////
    // Initialize the TG scenery subsystem.
    ////////////////////////////////////////////////////////////////////
    globals->set_scenery( new FGScenery );
    globals->get_scenery()->init();
    globals->get_scenery()->bind();
    globals->set_tile_mgr( new FGTileMgr );

    ////////////////////////////////////////////////////////////////////
    // Initialize the general model subsystem.
    ////////////////////////////////////////////////////////////////////
    globals->set_model_mgr(new FGModelMgr);
    globals->get_model_mgr()->init();
    globals->get_model_mgr()->bind();

    ////////////////////////////////////////////////////////////////////
    // Initialize the 3D aircraft model subsystem (has a dependency on
    // the scenery subsystem.)
    ////////////////////////////////////////////////////////////////////
    globals->set_aircraft_model(new FGAircraftModel);
    globals->get_aircraft_model()->init();
    globals->get_aircraft_model()->bind();

    ////////////////////////////////////////////////////////////////////
    // Initialize the view manager subsystem.
    ////////////////////////////////////////////////////////////////////
    FGViewMgr *viewmgr = new FGViewMgr;
    globals->set_viewmgr( viewmgr );
    viewmgr->init();
    viewmgr->bind();


    // Initialize the sky
    SGPath ephem_data_path( globals->get_fg_root() );
    ephem_data_path.append( "Astro" );
    SGEphemeris *ephem = new SGEphemeris( ephem_data_path.c_str() );
    ephem->update( globals->get_time_params()->getMjd(),
               globals->get_time_params()->getLst(),
               0.0 );
    globals->set_ephem( ephem );

                            // TODO: move to environment mgr
    thesky = new SGSky;
    SGPath texture_path(globals->get_fg_root());
    texture_path.append("Textures");
    texture_path.append("Sky");
    for (int i = 0; i < FGEnvironmentMgr::MAX_CLOUD_LAYERS; i++) {
        SGCloudLayer * layer = new SGCloudLayer(texture_path.str());
        thesky->add_cloud_layer(layer);
    }


    SGPath sky_tex_path( globals->get_fg_root() );
    sky_tex_path.append( "Textures" );
    sky_tex_path.append( "Sky" );
    thesky->texture_path( sky_tex_path.str() );

    // The sun and moon diameters are scaled down numbers of the
    // actual diameters. This was needed to fit bot the sun and the
    // moon within the distance to the far clip plane.
    // Moon diameter:    3,476 kilometers
    // Sun diameter: 1,390,000 kilometers
    thesky->build( 80000.0, 80000.0,
                   463.3, 361.8,
                   globals->get_ephem()->getNumPlanets(), 
                   globals->get_ephem()->getPlanets(),
                   globals->get_ephem()->getNumStars(),
                   globals->get_ephem()->getStars() );

    // Initialize MagVar model
    SGMagVar *magvar = new SGMagVar();
    globals->set_mag( magvar );


                                // kludge to initialize mag compass
                                // (should only be done for in-flight
                                // startup)
    // update magvar model
    globals->get_mag()->update( fgGetDouble("/position/longitude-deg")
                                * SGD_DEGREES_TO_RADIANS,
                                fgGetDouble("/position/latitude-deg")
                                * SGD_DEGREES_TO_RADIANS,
                                fgGetDouble("/position/altitude-ft")
                                * SG_FEET_TO_METER,
                                globals->get_time_params()->getJD() );
    double var = globals->get_mag()->get_magvar() * SGD_RADIANS_TO_DEGREES;
    fgSetDouble("/instrumentation/heading-indicator/offset-deg", -var);

    // airport = new ssgBranch;
    // airport->setName( "Airport Lighting" );
    // lighting->addKid( airport );

    // ADA
    fgLoadDCS();
    // ADA

#ifdef FG_NETWORK_OLK
    // Do the network intialization
    if ( fgGetBool("/sim/networking/network-olk") ) {
        printf("Multipilot mode %s\n",
               fg_net_init( globals->get_scenery()->get_scene_graph() ) );
    }
#endif

    // build our custom render states
    fgBuildRenderStates();
    
    // pass control off to the master GLUT event handler
    glutMainLoop();

    // we never actually get here ... but to avoid compiler warnings,
    // etc.
    return false;
}


// $$$ end - added VS Renganathan, 15 Oct 2K
//         - added Venky         , 12 Nov 2K


void fgLoadDCS(void) {

    ssgEntity *ship_obj = NULL;

    char obj_filename[25];

    for ( int k = 0; k < 32; k++ ) {
        ship_pos[k]=NULL;
    }

    SGPath tile_path( globals->get_fg_root());
    tile_path.append( "Scenery" );
    tile_path.append( "Objects.txt" );
    sg_gzifstream in( tile_path.str() );
    if ( ! in.is_open() ) {
        SG_LOG( SG_TERRAIN, SG_ALERT, "Cannot open file: " << tile_path.str() );
    } else {

        SGPath modelpath( globals->get_fg_root() );
        modelpath.append( "Models" );
        modelpath.append( "Geometry" );
  
        SGPath texturepath( globals->get_fg_root() );
        texturepath.append( "Models" );
        texturepath.append( "Textures" );
 
        ssgModelPath( (char *)modelpath.c_str() );
        ssgTexturePath( (char *)texturepath.c_str() );

        ship_sel = new ssgSelector;

        char c;
        while ( ! in.eof() ) {
            in >> ::skipws;
            if ( in.get( c ) && c == '#' ) { 
                in >> skipeol;
            } else { 
                in.putback(c);
                in >> obj_filename >> obj_lat[objc] >> obj_lon[objc] >> obj_alt[objc];
                /* cout << endl << obj_filename << " " << obj_lat[objc] << " " << obj_lon[objc] <<  " " << obj_alt[objc] << endl;
                   int chj=getchar();*/
                
                obj_lon[objc] *=SGD_DEGREES_TO_RADIANS;
                obj_lat[objc] *=SGD_DEGREES_TO_RADIANS;
                
                ship_pos[objc] = new ssgTransform;
       
                // type "repeat" in objects.txt to load one more
                // instance of the last object.

                if ( strcmp(obj_filename,"repeat") != 0) {
                    ship_obj =
                      globals->get_model_lib()->load_model( globals->get_fg_root(), obj_filename, globals->get_props(), globals->get_sim_time_sec() );
                }
      
                if ( ship_obj != NULL ) {
                            	ship_obj->setName(obj_filename);
                            if (objc == 0)
                            		ship_obj->clrTraversalMaskBits( SSGTRAV_HOT );
                            	else
                            		ship_obj->setTraversalMaskBits( SSGTRAV_HOT );
                    ship_pos[objc]->addKid( ship_obj ); // add object to transform node
                    ship_sel->addKid( ship_pos[objc] ); // add transform node to selector
                    SG_LOG( SG_TERRAIN, SG_ALERT, "Loaded file: "
                            << obj_filename );
                } else {
                    SG_LOG( SG_TERRAIN, SG_ALERT, "Cannot open file: "
                            << obj_filename );
                }
            
                            // temporary hack for deck lights - ultimately should move to PLib (when??)
                            //const char *extn = file_extension ( obj_filename ) ;
                            if ( objc == 1 ){
                                // ssgVertexArray *lights = new ssgVertexArray( 100 );
                            	ssgVertexArray *lightpoints = new ssgVertexArray( 100 );
                            	ssgVertexArray *lightnormals = new ssgVertexArray( 100 );
                            	ssgVertexArray *lightdir = new ssgVertexArray( 100 );
                            	int ltype[500], light_type = 0;
                            	static int ltcount = 0;
                                string token;
                            	sgVec3 rway_dir,rway_normal,lightpt;
                            	Point3D node;
                            	modelpath.append(obj_filename);
                            	sg_gzifstream in1( modelpath.str() );
                            	if ( ! in1.is_open() ) {
                            		SG_LOG( SG_TERRAIN, SG_ALERT, "Cannot open file: " << modelpath.str() );
                            	} else {
                            		while ( ! in1.eof() ) {
                                                        in1 >> ::skipws;
                            			if ( in1.get( c ) && c == '#' ) { 
                            				in1 >> skipeol;
                            			} else { 
                            				in1.putback(c);
                            				in1 >> token;
                            				//cout << token << endl;
                            				if ( token == "runway" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_dir, node[0], node[1], node[2] );			 
                            				} else if ( token == "edgelight" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );
                            					light_type = 1;
                            				} else if ( token == "taxi" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );			 
                            					light_type = 2;
                            				} else if ( token == "vasi" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );			 
                            					light_type = 3;
                            				} else if ( token == "threshold" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );			 
                            					light_type = 4;
                            				} else if ( token == "rabbit" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );
                            					light_type = 5;
                            				} else if ( token == "ols" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_ols, node[0], node[1], node[2] );
                            					light_type = 6;
                            				} else if ( token == "red" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );
                            					light_type = 7;
                            				} else if ( token == "green" ) {
                            					in1 >> node;
                            					sgSetVec3 (rway_normal, node[0], node[1], node[2] );
                            					light_type = 8;
                            				} else if ( token == "lp" ) {
                            					in1 >> node;
                            					sgSetVec3 (lightpt, node[0], node[1], node[2] );
                            					lightpoints->add( lightpt );
                            					lightnormals->add( rway_normal );
                            					lightdir->add( rway_dir );
                            					ltype[ltcount]= light_type;
                            					ltcount++;
                            				}
                            				if (in1.eof()) break;
                            			} 
                            		}  //while

#if 0        
                            		if ( lightpoints->getNum() ) {
                            			ssgBranch *lightpoints_branch;
                            			long int dummy = -999;
                            			dummy_tile = new FGTileEntry((SGBucket)dummy);
                            			dummy_tile->lightmaps_sequence = new ssgSelector;
                            			dummy_tile->ols_transform = new ssgTransform;

                            			// call function to generate the runway lights
                            			lightpoints_branch = 
                            			dummy_tile->gen_runway_lights( lightpoints, lightnormals,
                            												lightdir, ltype);
                            			lightpoints_brightness->addKid(lightpoints_branch);
                            			lightpoints_transform->addKid(lightpoints_brightness);
                            		    //dummy_tile->lightmaps_sequence->setTraversalMaskBits( SSGTRAV_HOT );
                            			lightpoints_transform->addKid( dummy_tile->lightmaps_sequence );
                            			lightpoints_transform->ref();
                            			globals->get_scenery()->get_gnd_lights_root()->addKid( lightpoints_transform );
                            		} 
#endif
                            	} //if in1 
                } //if objc
                            // end hack for deck lights

                objc++;

                if (in.eof()) break;
            }
        } // while

        SG_LOG ( SG_TERRAIN, SG_ALERT, "Finished object processing." );

        globals->get_scenery()->get_terrain_branch()->addKid( ship_sel ); //add selector node to root node 
    }

    return;
 }


void fgUpdateDCS (void) {

    // double eye_lat,eye_lon,eye_alt;
    // static double obj_head;
    double sl_radius,obj_latgc;
    // float nresultmat[4][4];
    // sgMat4 Trans,rothead,rotlon,rot180,rotlat,resultmat1,resultmat2,resultmat3;
    double bz[3];

    // Instantaneous Geodetic Lat/Lon/Alt of moving object
    FGADA *fdm = (FGADA *)current_aircraft.fdm_state;
    
    // Deck should be the first object in objects.txt in case of fdm=ada

    if (!strcmp(fgGetString("/sim/flight-model"), "ada")) {
            if ((fdm->get_iaux(1))==1)
            {
                    obj_lat[1] = fdm->get_daux(1)*SGD_DEGREES_TO_RADIANS;
                    obj_lon[1] = fdm->get_daux(2)*SGD_DEGREES_TO_RADIANS;
                    obj_alt[1] = fdm->get_daux(3);
                    obj_pitch[1] = fdm->get_faux(1);
                    obj_roll[1] = fdm->get_faux(2);
            }
    }
    
    for ( int m = 0; m < objc; m++ ) {
    	//cout << endl <<  obj_lat[m]*SGD_RADIANS_TO_DEGREES << " " << obj_lon[m]*SGD_RADIANS_TO_DEGREES << " " << obj_alt[m] << " " << objc << endl;
        //int v=getchar();

        //Geodetic to Geocentric angles for rotation
        sgGeodToGeoc(obj_lat[m],obj_alt[m],&sl_radius,&obj_latgc);

        //moving object gbs-posn in cartesian coords
        Point3D obj_posn = Point3D( obj_lon[m],obj_lat[m],obj_alt[m]);
        Point3D obj_pos = sgGeodToCart( obj_posn );

        // Translate moving object w.r.t eye
        Point3D Objtrans = obj_pos - globals->get_scenery()->get_center();
        bz[0]=Objtrans.x();
        bz[1]=Objtrans.y();
        bz[2]=Objtrans.z();

       // rotate dynamic objects for lat,lon & alt and other motion about its axes
        
        sgMat4 sgTRANS;
        sgMakeTransMat4( sgTRANS, bz[0],bz[1],bz[2]);

        sgVec3 ship_fwd,ship_rt,ship_up;
        sgSetVec3( ship_fwd, 1.0, 0.0, 0.0);//east,roll
        sgSetVec3( ship_rt, 0.0, 1.0, 0.0);//up,pitch
        sgSetVec3( ship_up, 0.0, 0.0, 1.0); //north,yaw

        sgMat4 sgROT_lon, sgROT_lat, sgROT_hdg, sgROT_pitch, sgROT_roll;
        sgMakeRotMat4( sgROT_lon, obj_lon[m]*SGD_RADIANS_TO_DEGREES, ship_up );
        sgMakeRotMat4( sgROT_lat, 90-obj_latgc*SGD_RADIANS_TO_DEGREES, ship_rt );
        sgMakeRotMat4( sgROT_hdg, 180.0, ship_up );
        sgMakeRotMat4( sgROT_pitch, obj_pitch[m], ship_rt );
        sgMakeRotMat4( sgROT_roll, obj_roll[m], ship_fwd );
        
        sgMat4 sgTUX;
        sgCopyMat4( sgTUX, sgROT_hdg );
        sgPostMultMat4( sgTUX, sgROT_pitch );
        sgPostMultMat4( sgTUX, sgROT_roll );
        sgPostMultMat4( sgTUX, sgROT_lat );
        sgPostMultMat4( sgTUX, sgROT_lon );
        sgPostMultMat4( sgTUX, sgTRANS );

        sgCoord shippos;
        sgSetCoord(&shippos, sgTUX );
        ship_pos[m]->setTransform( &shippos );
        // temporary hack for deck lights - ultimately should move to PLib (when ??)
        if (m == 1) {
            if (lightpoints_transform) {
                    lightpoints_transform->setTransform( &shippos );
                    float sun_angle = cur_light_params.sun_angle * SGD_RADIANS_TO_DEGREES;
                    if ( sun_angle > 89 ) {
                            lightpoints_brightness->select(0x01);
                    } else {
                            lightpoints_brightness->select(0x00);
                    }
            }

            float elev;
            sgVec3 rp,to;
            float *vp;
            float alt;
            float ref_elev;
            sgXformPnt3( rp, rway_ols, sgTUX );
            vp = globals->get_current_view()->get_view_pos();
            to[0] = rp[0]-vp[0];
            to[1] = rp[1]-vp[1];
            to[2] = rp[2]-vp[2];
            float dist = sgLengthVec3( to );
            alt = (current_aircraft.fdm_state->get_Altitude() * SG_FEET_TO_METER)-rway_ols[2];

            elev = asin(alt/dist)*SGD_RADIANS_TO_DEGREES;

            ref_elev = elev - 3.75; // +ve above, -ve below
        
            unsigned int sel;
            sel = 0xFF;
// DO NOT DELETE THIS CODE - This is to compare a discrete FLOLS (without LOD) with analog FLOLS
//		if (ref_elev > 0.51) sel = 0x21;
//		if ((ref_elev <= 0.51) & (ref_elev > 0.17)) sel = 0x22;
//		if ((ref_elev <= 0.17) & (ref_elev >= -0.17)) sel = 0x24;
//		if ((ref_elev < -0.17) & (ref_elev >= -0.51)) sel = 0x28;
//		if (ref_elev < -0.51) sel = 0x30;
// DO NOT DELETE THIS CODE - This is to compare a discrete FLOLS (without LOD) with analog FLOLS
            // dummy_tile->lightmaps_sequence->select(sel);

            sgVec3 up;
            sgCopyVec3 (up, ship_up);
            if (dist > 750) 
                    sgScaleVec3 (up, 4.0*ref_elev*dist/750.0);
            else
                    sgScaleVec3 (up, 4.0*ref_elev);
            // dummy_tile->ols_transform->setTransform(up);
            //cout << "ref_elev  " << ref_elev << endl;
        }
    // end hack for deck lights

    }
    if ( ship_sel != NULL ) {
        ship_sel->select(0xFFFFFFFE); // first object is ownship, added to acmodel
    }
}

// $$$ end - added VS Renganathan, 15 Oct 2K
//           added Venky         , 12 Nov 2K
