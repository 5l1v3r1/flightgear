// hitlist.cxx -
// Height Over Terrain and Assosciated Routines for FlightGear based Scenery
// Written by Norman Vine, started 2000.

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <float.h>
#include <math.h>

#include <simgear/sg_inlines.h>
#include <simgear/debug/logstream.hxx>
#include <simgear/math/point3d.hxx>
#include <simgear/math/sg_geodesy.hxx>
#include <simgear/math/vector.hxx>

#include <Main/globals.hxx>
#include <Main/viewer.hxx>
#include <Scenery/scenery.hxx>

#include "hitlist.hxx"

// forward declaration of our helper/convenience functions
static void sgMultMat4(sgdMat4 dst, sgdMat4 m1, sgMat4 m2);
static void ssgGetEntityTransform(ssgEntity *entity, sgMat4 m );
static void ssgGetCurrentBSphere( ssgEntity *entity, sgVec3 center, float *radius, sgMat4 m );


// ======================
// This is same as PLib's sgdIsectInfLinePlane()
// and can be replaced by it after the next PLib release
static int fgdIsectInfLinePlane( sgdVec3 dst, const sgdVec3 l_org,
                                 const sgdVec3 l_vec, const sgdVec4 plane )
{
    SGDfloat tmp = sgdScalarProductVec3 ( l_vec, plane ) ;

    /* Is line parallel to plane? */

    if ( fabs ( tmp ) < FLT_EPSILON )
        return false ;

    sgdScaleVec3 ( dst, l_vec, -( sgdScalarProductVec3 ( l_org, plane )
                                  + plane[3] ) / tmp ) ;
    sgdAddVec3  ( dst, l_org ) ;

    return true ;
}

// ======================

/*
 * Given a point and a triangle lying on the same plane
 * check to see if the point is inside the triangle
 */
// This is same as PLib's sgdPointInTriangle()
// and can be replaced by it after the next PLib release
static bool fgdPointInTriangle( sgdVec3 point, sgdVec3 tri[3] )
{
    sgdVec3 dif;

    SGDfloat min, max;
    // punt if outside bouding cube
    SG_MIN_MAX3 ( min, max, tri[0][0], tri[1][0], tri[2][0] );
    if( (point[0] < min) || (point[0] > max) )
        return false;
    dif[0] = max - min;

    SG_MIN_MAX3 ( min, max, tri[0][1], tri[1][1], tri[2][1] );
    if( (point[1] < min) || (point[1] > max) )
        return false;
    dif[1] = max - min;

    SG_MIN_MAX3 ( min, max, tri[0][2], tri[1][2], tri[2][2] );
    if( (point[2] < min) || (point[2] > max) )
        return false;
    dif[2] = max - min;

    // drop the smallest dimension so we only have to work in 2d.
    SGDfloat min_dim = SG_MIN3 (dif[0], dif[1], dif[2]);
    SGDfloat x1, y1, x2, y2, x3, y3, rx, ry;
    if ( fabs(min_dim-dif[0]) <= DBL_EPSILON ) {
        // x is the smallest dimension
        x1 = point[1];
        y1 = point[2];
        x2 = tri[0][1];
        y2 = tri[0][2];
        x3 = tri[1][1];
        y3 = tri[1][2];
        rx = tri[2][1];
        ry = tri[2][2];
    } else if ( fabs(min_dim-dif[1]) <= DBL_EPSILON ) {
        // y is the smallest dimension
        x1 = point[0];
        y1 = point[2];
        x2 = tri[0][0];
        y2 = tri[0][2];
        x3 = tri[1][0];
        y3 = tri[1][2];
        rx = tri[2][0];
        ry = tri[2][2];
    } else if ( fabs(min_dim-dif[2]) <= DBL_EPSILON ) {
        // z is the smallest dimension
        x1 = point[0];
        y1 = point[1];
        x2 = tri[0][0];
        y2 = tri[0][1];
        x3 = tri[1][0];
        y3 = tri[1][1];
        rx = tri[2][0];
        ry = tri[2][1];
    } else {
        // all dimensions are really small so lets call it close
        // enough and return a successful match
        return true;
    }

    // check if intersection point is on the same side of p1 <-> p2 as p3
    SGDfloat tmp = (y2 - y3) / (x2 - x3);
    int side1 = SG_SIGN (tmp * (rx - x3) + y3 - ry);
    int side2 = SG_SIGN (tmp * (x1 - x3) + y3 - y1);
    if ( side1 != side2 ) {
        // printf("failed side 1 check\n");
        return false;
    }

    // check if intersection point is on correct side of p2 <-> p3 as p1
    tmp = (y3 - ry) / (x3 - rx);
    side1 = SG_SIGN (tmp * (x2 - rx) + ry - y2);
    side2 = SG_SIGN (tmp * (x1 - rx) + ry - y1);
    if ( side1 != side2 ) {
        // printf("failed side 2 check\n");
        return false;
    }

    // check if intersection point is on correct side of p1 <-> p3 as p2
    tmp = (y2 - ry) / (x2 - rx);
    side1 = SG_SIGN (tmp * (x3 - rx) + ry - y3);
    side2 = SG_SIGN (tmp * (x1 - rx) + ry - y1);
    if ( side1 != side2 ) {
        // printf("failed side 3  check\n");
        return false;
    }

    return true;
}

// ======================

inline static int isZeroAreaTri( sgdVec3 tri[3] )
{
    return( sgdEqualVec3(tri[0], tri[1]) ||
            sgdEqualVec3(tri[1], tri[2]) ||
            sgdEqualVec3(tri[2], tri[0]) );
}

FGHitList::FGHitList() :
        last(NULL), test_dist(DBL_MAX)
{
}

FGHitList::~FGHitList() {}


/*
Find the intersection of an infinite line with a leaf
the line being defined by a point and direction.

Variables
In:
ssgLeaf pointer  -- leaf
qualified matrix -- m
line origin      -- orig
line direction   -- dir
Out:
result  -- intersection point
normal  -- intersected tri's normal

Returns:
true if intersection found
false otherwise

!!! WARNING !!!
If you need an exhaustive list of hitpoints YOU MUST use
the generic version of this function as the specialized
versions will do an early out of expensive tests if the point
can not be the closest one found
!!! WARNING !!!
*/
int FGHitList::IntersectLeaf( ssgLeaf *leaf, sgdMat4 m,
                              sgdVec3 orig, sgdVec3 dir )
{
    int num_hits = 0;
    int i = 0;

    for ( ; i < leaf->getNumTriangles(); ++i ) {
        short i1, i2, i3;
        leaf->getTriangle( i, &i1, &i2, &i3 );

        sgdVec3 tri[3];
        sgdSetVec3( tri[0], leaf->getVertex( i1 ) );
        sgdSetVec3( tri[1], leaf->getVertex( i2 ) );
        sgdSetVec3( tri[2], leaf->getVertex( i3 ) );

        if( isZeroAreaTri( tri ) )
            continue;

        sgdVec4 plane;
        sgdMakePlane( plane, tri[0], tri[1], tri[2] );

        sgdVec3 point;
        if( fgdIsectInfLinePlane( point, orig, dir, plane ) ) {
            if( fgdPointInTriangle( point, tri ) ) {
                // transform point into passed into desired coordinate frame
                sgdXformPnt3( point, point, m );
		sgdXformPnt4(plane,plane,m);
                add(leaf,i,point,plane);
                num_hits++;
            }
        }
    }
    return num_hits;
}

// ======================

int FGHitList::IntersectLeaf( ssgLeaf *leaf, sgdMat4 m,
                              sgdVec3 orig, sgdVec3 dir,
                              GLenum primType )
{
    double tmp_dist;

    // number of hits but there could be more that
    // were not found because of short circut switch !
    // so you may want to use the unspecialized IntersectLeaf()
    int n, num_hits = 0;

    int ntri = leaf->getNumTriangles();
    for ( n = 0; n < ntri; ++n )
    {
        sgdVec3 tri[3];

        switch ( primType )
        {
        case GL_POLYGON :
        case GL_TRIANGLE_FAN :
            if ( !n ) {
                sgdSetVec3( tri[0], leaf->getVertex( short(0) ) );
                sgdSetVec3( tri[1], leaf->getVertex( short(1) ) );
                sgdSetVec3( tri[2], leaf->getVertex( short(2) ) );
            } else {
                sgdCopyVec3( tri[1], tri[2] );
                sgdSetVec3( tri[2], leaf->getVertex( short(n+2) ) );
            }
            break;
        case GL_TRIANGLES :
            sgdSetVec3( tri[0], leaf->getVertex( short(n*3) ) );
            sgdSetVec3( tri[1], leaf->getVertex( short(n*3+1) ) );
            sgdSetVec3( tri[2], leaf->getVertex( short(n*3+2) ) );
            break;
        case GL_TRIANGLE_STRIP :
        case GL_QUAD_STRIP :
            if ( !n ) {
                sgdSetVec3( tri[0], leaf->getVertex( short(0) ) );
                sgdSetVec3( tri[1], leaf->getVertex( short(1) ) );
                sgdSetVec3( tri[2], leaf->getVertex( short(2) ) );
            } else {
                if ( n & 1 ) {
                    sgdSetVec3( tri[0], leaf->getVertex( short(n+2) ) );
                    sgdCopyVec3( tri[1], tri[2] );
                    sgdCopyVec3( tri[2], tri[1] );

                } else {
                    sgdCopyVec3( tri[0], tri[1] );
                    sgdCopyVec3( tri[1], tri[2] );
                    sgdSetVec3( tri[2], leaf->getVertex( short(n+2) ) );
                }
            }
            break;
        case GL_QUADS :
            sgdSetVec3( tri[0], leaf->getVertex( short(n*2) ) );
            sgdSetVec3( tri[1], leaf->getVertex( short(n*2+1) ) );
            sgdSetVec3( tri[2], leaf->getVertex( short(n*2 + 2 - (n&1)*4) ) );
            break;
        default:
            return IntersectLeaf( leaf, m, orig, dir);
        }

        if( isZeroAreaTri( tri ) )
            continue;

        sgdVec4 plane;
        sgdMakePlane( plane, tri[0], tri[1], tri[2] );

        sgdVec3 point;

        // find point of intersection of line from point org
        // in direction dir with triangle's plane
        SGDfloat tmp = sgdScalarProductVec3 ( dir, plane ) ;
        /* Is line parallel to plane? */
        if ( sgdAbs ( tmp ) < FLT_EPSILON /*DBL_EPSILON*/ )
            continue ;

        // find parametric point
        sgdScaleVec3 ( point, dir,
                       -( sgdScalarProductVec3 ( orig, plane ) + plane[3] )
                       / tmp ) ;

        // short circut if this point is further away then a previous hit
        tmp_dist = sgdDistanceSquaredVec3(point, orig );
        if( tmp_dist > test_dist )
            continue;

        // place parametric point in world
        sgdAddVec3 ( point, orig ) ;

        if( fgdPointInTriangle( point, tri ) ) {
            // transform point into passed coordinate frame
            sgdXformPnt3( point, point, m );
	    sgdXformPnt4(plane,plane,m);
            add(leaf,n,point,plane);
            test_dist = tmp_dist;
            num_hits++;
        }
    }
    return num_hits;
}

// ======================
inline static bool IN_RANGE( sgdVec3 v, double radius ) {
    return ( sgdScalarProductVec3(v, v) < (radius*radius) );
}

// ======================
void FGHitList::IntersectBranch( ssgBranch *branch, sgdMat4 m,
                                 sgdVec3 orig, sgdVec3 dir )
{
    /* the lookat vector and matrix in branch's coordinate frame
     * but we won't determine these unless needed,
     * This 'lazy evaluation' is a result of profiling data */
    sgdVec3 orig_leaf, dir_leaf;
    sgdMat4 m_leaf;

    // 'lazy evaluation' flag
    int first_time = 1;

    for ( ssgEntity *kid = branch->getKid( 0 );
            kid != NULL;
            kid = branch->getNextKid() )
    {
        if ( kid->getTraversalMask() & SSGTRAV_HOT
             && !kid->getBSphere()->isEmpty() )
        {
            sgdVec3 center;
            sgdSetVec3( center,
                        kid->getBSphere()->getCenter()[0],
                        kid->getBSphere()->getCenter()[1],
                        kid->getBSphere()->getCenter()[2] );
            sgdXformPnt3( center, m ) ;

            // sgdClosestPointToLineDistSquared( center, orig, dir )
            // inlined here because because of profiling results
            sgdVec3 u, u1, v;
            sgdSubVec3(u, center, orig);
            sgdScaleVec3( u1, dir, sgdScalarProductVec3(u,dir)
                          / sgdScalarProductVec3(dir,dir) );
            sgdSubVec3(v, u, u1);

            // double because of possible overflow
            if ( IN_RANGE( v, double(kid->getBSphere()->getRadius()) ) )
            {
                if ( kid->isAKindOf ( ssgTypeBranch() ) )
                {
                    sgdMat4 m_new;
                    if ( kid->isA( ssgTypeTransform() ) )
                    {
                        sgMat4 fxform;
                        ((ssgTransform *)kid)->getTransform( fxform );
                        sgMultMat4(m_new, m, fxform);
                    } else {
                        sgdCopyMat4(m_new, m);
                    }
                    IntersectBranch( (ssgBranch *)kid, m_new, orig, dir );
                }
                else if ( kid->isAKindOf( ssgTypeLeaf() ) )
                {
                    if ( first_time ) {
                        sgdTransposeNegateMat4( m_leaf, m );
                        sgdXformPnt3( orig_leaf, orig, m_leaf );
                        sgdXformPnt3( dir_leaf,  dir,  m_leaf );
                        first_time = 0;
                    }
                    GLenum primType = ((ssgLeaf *)kid)->getPrimitiveType();
                    IntersectLeaf( (ssgLeaf *)kid, m, orig_leaf, dir_leaf, primType );
                }
            }  // Out of range
        } // branch not requested to be traversed
    } // end for loop
}



// ======================
// a temporary hack until we get everything rewritten with sgdVec3
static inline Point3D operator + (const Point3D& a, const sgdVec3 b)
{
    return Point3D(a.x()+b[0], a.y()+b[1], a.z()+b[2]);
}


// ======================
void FGHitList::Intersect( ssgBranch *scene, sgdVec3 orig, sgdVec3 dir ) {
    sgdMat4 m;
    clear();
    sgdMakeIdentMat4 ( m ) ;
    IntersectBranch( scene, m, orig, dir );
}

// ======================
void FGHitList::Intersect( ssgBranch *scene, sgdMat4 m, sgdVec3 orig, sgdVec3 dir )
{
    clear();
    IntersectBranch( scene, m, orig, dir );
}

// ======================
// Need these because of mixed matrix types
static void sgMultMat4(sgdMat4 dst, sgdMat4 m1, sgMat4 m2)
{
    for ( int j = 0 ; j < 4 ; j++ )
    {
        dst[0][j] = m2[0][0] * m1[0][j] +
                    m2[0][1] * m1[1][j] +
                    m2[0][2] * m1[2][j] +
                    m2[0][3] * m1[3][j] ;

        dst[1][j] = m2[1][0] * m1[0][j] +
                    m2[1][1] * m1[1][j] +
                    m2[1][2] * m1[2][j] +
                    m2[1][3] * m1[3][j] ;

        dst[2][j] = m2[2][0] * m1[0][j] +
                    m2[2][1] * m1[1][j] +
                    m2[2][2] * m1[2][j] +
                    m2[2][3] * m1[3][j] ;

        dst[3][j] = m2[3][0] * m1[0][j] +
                    m2[3][1] * m1[1][j] +
                    m2[3][2] * m1[2][j] +
                    m2[3][3] * m1[3][j] ;
    }
}

// ======================
static void ssgGetEntityTransform(ssgEntity *entity, sgMat4 m )
{
    /*
       Walk backwards up the tree, transforming the
       vertex by all the matrices along the way.

       Upwards recursion hurts my head.
       */

    sgMat4 mat ;

    /*
       If this node has a parent - get the composite
       matrix for the parent.
       */
    if ( entity->getNumParents() > 0 )
        ssgGetEntityTransform ( entity->getParent(0), mat ) ;
    else
        sgMakeIdentMat4 ( mat ) ;

    /*
       If this node has a transform - then concatenate it.
       */
    if ( entity -> isAKindOf ( ssgTypeTransform () ) ) {
        sgMat4 this_mat ;
        ((ssgTransform *) entity) -> getTransform ( this_mat ) ;
        sgPostMultMat4 ( mat, this_mat ) ;
    }

    sgCopyMat4 ( m, mat ) ;
}

// ======================
// return the passed entitity's bsphere's center point radius and
// fully formed current model matrix for entity
static void ssgGetCurrentBSphere( ssgEntity *entity, sgVec3 center, float *radius, sgMat4 m )
{
    sgSphere *bsphere = entity->getBSphere();
    *radius = (double)bsphere->getRadius();
    sgCopyVec3( center, bsphere->getCenter() );
    sgMakeIdentMat4 ( m ) ;
    ssgGetEntityTransform( entity, m );
}


// ======================
// Determine scenery altitude via ssg.
// returned results are in meters
bool fgCurrentElev( sgdVec3 abs_view_pos, sgdVec3 scenery_center,
                    FGHitList *hit_list,
                    double *terrain_elev, double *radius, double *normal)
{
    sgdVec3 view_pos;
    sgdSubVec3( view_pos, abs_view_pos, scenery_center );

    sgdVec3 orig, dir;
    sgdCopyVec3(orig, view_pos );
    sgdCopyVec3(dir, abs_view_pos );

    hit_list->Intersect( globals->get_scenery()->get_terrain_branch(),
                         orig, dir );

    int this_hit=0;
    Point3D geoc;
    double result = -9999;
    Point3D sc(scenery_center[0], scenery_center[1], scenery_center[2]) ;

    // cout << "hits = ";
    int hitcount = hit_list->num_hits();
    for ( int i = 0; i < hitcount; ++i ) {
        geoc = sgCartToPolar3d( sc + hit_list->get_point(i) );
        double lat_geod, alt, sea_level_r;
        sgGeocToGeod(geoc.lat(), geoc.radius(), &lat_geod,
                     &alt, &sea_level_r);
        // cout << alt << " ";
        if ( alt > result && alt < 10000 ) {
            result = alt;
            this_hit = i;
        }
    }
    // cout << endl;

    if ( result > -9000 ) {
        *terrain_elev = result;
        *radius = geoc.radius();
        sgVec3 tmp;
        sgSetVec3(tmp, hit_list->get_normal(this_hit));
        // cout << "cur_normal: " << tmp[0] << " " << tmp[1] << " "  << tmp[2] << endl;
        sgdSetVec3( normal, tmp );
        // float *up = globals->get_current_view()->get_world_up();
	// cout << "world_up  : " << up[0] << " " << up[1] << " " << up[2] << endl;
        /* ssgState *IntersectedLeafState =
              ((ssgLeaf*)hit_list->get_entity(this_hit))->getState(); */
        return true;
    } else {
        SG_LOG( SG_TERRAIN, SG_INFO, "no terrain intersection" );
        *terrain_elev = 0.0;
        float *up = globals->get_current_view()->get_world_up();
        sgdSetVec3(normal, up[0], up[1], up[2]);
        return false;
    }
}


// ======================
// Determine scenery altitude via ssg.
// returned results are in meters
bool fgCurrentElev( sgdVec3 abs_view_pos, sgdVec3 scenery_center,
                    ssgTransform *terra_transform,
                    FGHitList *hit_list,
                    double *terrain_elev, double *radius, double *normal)
{
    sgdVec3 view_pos;
    sgdSubVec3( view_pos, abs_view_pos, scenery_center );

    sgdVec3 orig, dir;
    sgdCopyVec3(orig, view_pos );

    sgdCopyVec3(dir, abs_view_pos );
    sgdNormalizeVec3(dir);

    sgMat4 fxform;
    sgMakeIdentMat4 ( fxform ) ;
    ssgGetEntityTransform( terra_transform, fxform );

    sgdMat4 xform;
    sgdSetMat4(xform,fxform);
    hit_list->Intersect( terra_transform, xform, orig, dir );

    int this_hit=0;
    Point3D geoc;
    double result = -9999;
    Point3D sc(scenery_center[0], scenery_center[1], scenery_center[2]) ;

    int hitcount = hit_list->num_hits();
    for ( int i = 0; i < hitcount; ++i ) {
        geoc = sgCartToPolar3d( sc + hit_list->get_point(i) );
        double lat_geod, alt, sea_level_r;
        sgGeocToGeod(geoc.lat(), geoc.radius(), &lat_geod,
                     &alt, &sea_level_r);
        if ( alt > result && alt < 20000 ) {
            result = alt;
            this_hit = i;
        }
    }

    if ( result > -9000 ) {
        *terrain_elev = result;
        *radius = geoc.radius();
        sgVec3 tmp;
        sgSetVec3(tmp, hit_list->get_normal(this_hit));
        // cout << "cur_normal: " << tmp[0] << " " << tmp[1] << " "  << tmp[2] << endl;
        sgdSetVec3( normal, tmp );
        // float *up = globals->get_current_view()->get_world_up();
       // cout << "world_up  : " << up[0] << " " << up[1] << " " << up[2] << endl;
        /* ssgState *IntersectedLeafState =
              ((ssgLeaf*)hit_list->get_entity(this_hit))->getState(); */
        return true;
    } else {
        SG_LOG( SG_TERRAIN, SG_DEBUG, "DOING FULL TERRAIN INTERSECTION" );
        return fgCurrentElev( abs_view_pos, scenery_center, hit_list,
                              terrain_elev,radius,normal);
    }
}

