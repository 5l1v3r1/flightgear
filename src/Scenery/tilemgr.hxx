// tilemgr.hxx -- routines to handle dynamic management of scenery tiles
//
// Written by Curtis Olson, started January 1998.
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


#ifndef _TILEMGR_HXX
#define _TILEMGR_HXX


#ifndef __cplusplus                                                          
# error This library requires C++
#endif                                   

#include <simgear/compiler.h>
#include <simgear/math/point3d.hxx>

#include <queue>

#include <plib/ssg.h>

#include <simgear/bucket/newbucket.hxx>
#ifdef ENABLE_THREADS
#  include <simgear/threads/SGQueue.hxx>
#endif // ENABLE_THREADS

#include <Main/location.hxx>

#include "FGTileLoader.hxx"
#include "hitlist.hxx"
#include "newcache.hxx"

#if defined(USE_MEM) || defined(WIN32)
#  define FG_MEM_COPY(to,from,n)        memcpy(to, from, n)
#else
#  define FG_MEM_COPY(to,from,n)        bcopy(from, to, n)
#endif

SG_USING_STD( queue );


// forward declaration
class FGTileEntry;
class FGDeferredModel;


class FGTileMgr {

private:

    // Tile loading state
    enum load_state {
	Start = 0,
	Inited = 1,
	Running = 2
    };

    load_state state;

    // initialize the cache
    void initialize_queue();

    // schedule a tile for loading
    void sched_tile( const SGBucket& b );

    // schedule a needed buckets for loading
    void schedule_needed(double visibility_meters, SGBucket curr_bucket);

    // see comment at prep_ssg_nodes()
    void prep_ssg_node( int idx );
	
    FGHitList hit_list;

    SGBucket previous_bucket;
    SGBucket current_bucket;
    SGBucket pending;
	
    FGTileEntry *current_tile;
	
    // x and y distance of tiles to load/draw
    float vis;
    int xrange, yrange;
	
    // current longitude latitude
    double longitude;
    double latitude;
    double last_longitude;
    double last_latitude;

    /**
     * tile cache
     */
    FGNewCache tile_cache;

    /**
     * Queue tiles for loading.
     */
    FGTileLoader loader;
    int counter_hack;

    /**
     * Work queues.
     *
     * attach_queue is the tiles that have been loaded [by the pager]
     * that can be attached to the scene graph by the render thread.
     *
     * model_queue is the set of models that need to be loaded by the
     * primary render thread.
     */
#ifdef ENABLE_THREADS
    static SGLockedQueue<FGTileEntry *> attach_queue;
    static SGLockedQueue<FGDeferredModel *> model_queue;
#else
    static queue<FGTileEntry *> attach_queue;
    static queue<FGDeferredModel *> model_queue;
#endif // ENABLE_THREADS
    static queue<FGTileEntry *> delete_queue;

public:

    /**
     * Add a loaded tile to the 'attach to the scene graph' queue.
     */
    static void ready_to_attach( FGTileEntry *t ) { attach_queue.push( t ); }

    /**
     * Add a pending model to the 'deferred model load' queue
     */
    static void model_ready( FGDeferredModel *dm ) { model_queue.push( dm ); }

public:

    // Constructor
    FGTileMgr();

    // Destructor
    ~FGTileMgr();

    // Initialize the Tile Manager subsystem
    int init();

    // Update the various queues maintained by the tilemagr (private
    // internal function, do not call directly.)
    void update_queues();

    // given the current lon/lat (in degrees), fill in the array of
    // local chunks.  If the chunk isn't already in the cache, then
    // read it from disk.
    int update( double lon, double lat, double visibility_meters );
    int update( double lon, double lat, double visibility_meters, sgdVec3 abs_pos_vector, SGBucket p_current, SGBucket p_previous, Point3D center );
    void setCurrentTile( double longitude, double latitude );
    int updateCurrentElevAtPos(sgdVec3 abs_pos_vector, Point3D center );

    // Determine scenery altitude.  Normally this just happens when we
    // render the scene, but we'd also like to be able to do this
    // explicitely.  lat & lon are in radians.  abs_view_pos in
    // meters.  Returns result in meters.
    void my_ssg_los( string s, ssgBranch *branch, sgdMat4 m, 
		     const sgdVec3 p, const sgdVec3 dir, sgdVec3 normal );
	
    void my_ssg_los( ssgBranch *branch, sgdMat4 m, 
		     const sgdVec3 p, const sgdVec3 dir,
		     FGHitList *list );

    // Prepare the ssg nodes corresponding to each tile.  For each
    // tile, set the ssg transform and update it's range selector
    // based on current visibilty void prep_ssg_nodes( float
    // visibility_meters );
    void prep_ssg_nodes( FGLocation *location, float visibility_meters );

    // Set flag with event manager so that non-moving view refreshes
    // tiles...
    void refresh_view_timestamps();

    inline SGBucket get_current_bucket () { return current_bucket; }
    inline SGBucket get_previous_bucket () { return previous_bucket; }
};


// the tile manager
extern FGTileMgr global_tile_mgr;


#endif // _TILEMGR_HXX
