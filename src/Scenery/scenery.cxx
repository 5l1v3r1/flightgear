// scenery.cxx -- data structures and routines for managing scenery.
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef HAVE_WINDOWS_H
#  include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>

#include <stdio.h>
#include <string.h>

#include <simgear/debug/logstream.hxx>

#include <Main/fg_props.hxx>

#include "scenery.hxx"


// Scenery Management system
FGScenery::FGScenery() {
    SG_LOG( SG_TERRAIN, SG_INFO, "Initializing scenery subsystem" );

    center = Point3D(0.0);
    cur_elev = -9999;
}


// Initialize the Scenery Management system
FGScenery::~FGScenery() {
}


void FGScenery::init() {
    // Scene graph root
    scene_graph = new ssgRoot;
    scene_graph->setName( "Scene" );

    // Terrain branch
    terrain_branch = new ssgBranch;
    terrain_branch->setName( "Terrain" );
    scene_graph->addKid( terrain_branch );

    models_branch = new ssgBranch;
    models_branch->setName( "Models" );
    scene_graph->addKid( models_branch );

    aircraft_branch = new ssgBranch;
    aircraft_branch->setName( "Aircraft" );
    scene_graph->addKid( aircraft_branch );

    // Lighting
    gnd_lights_root = new ssgRoot;
    gnd_lights_root->setName( "Ground Lighting Root" );

    rwy_lights_root = new ssgRoot;
    rwy_lights_root->setName( "Runway Lighting Root" );

    taxi_lights_root = new ssgRoot;
    taxi_lights_root->setName( "Taxi Lighting Root" );
}


void FGScenery::update(double dt) {
}


void FGScenery::bind() {
    fgTie("/environment/ground-elevation-m", this,
	  &FGScenery::get_cur_elev, &FGScenery::set_cur_elev);
}


void FGScenery::unbind() {
    fgUntie("/environment/ground-elevation-m");
}
