// general.hxx -- a general house keeping data structure definition for 
//                various info that might need to be accessible from all 
//                parts of the sim.
//
// Written by Curtis Olson, started July 1997.
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


#ifndef _GENERAL_HXX
#define _GENERAL_HXX


#ifndef __cplusplus                                                          
# error This library requires C++
#endif                                   


// #define FANCY_FRAME_COUNTER
#ifdef FANCY_FRAME_COUNTER
#define FG_FRAME_RATE_HISTORY 10
#endif


// the general house keeping structure definition
class FGGeneral {
    // Info about OpenGL
    char *glVendor;
    char *glRenderer;
    char *glVersion;

    // Last frame rate measurement
    int frame_rate;
#ifdef FANCY_FRAME_COUNTER
    double frames[FG_FRAME_RATE_HISTORY];
#endif

public:

    inline void set_glVendor( char *str ) { glVendor = str; }
    inline char* get_glRenderer() const { return glRenderer; }
    inline void set_glRenderer( char *str ) { glRenderer = str; }
    inline void set_glVersion( char *str ) { glVersion = str; }
    inline double get_frame_rate() const { return frame_rate; }
#ifdef FANCY_FRAME_COUNTER
    inline double get_frame(int idx) const { return frames[idx]; }
    inline void set_frame( int idx, double value ) { frames[idx] = value; }
    inline void set_frame_rate( double rate ) { frame_rate = rate; }
#else
    inline void set_frame_rate( int rate ) { frame_rate = rate; }
#endif
};

// general contains all the general house keeping parameters.
extern FGGeneral general;


#endif // _GENERAL_HXX


