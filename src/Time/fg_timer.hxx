// fg_timer.hxx -- time handling routines
//
// Written by Curtis Olson, started June 1997.
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


#ifndef _FG_TIMER_HXX
#define _FG_TIMER_HXX


#ifndef __cplusplus                                                          
# error This library requires C++
#endif                                   


extern unsigned long int fgSimTime;

// this routine initializes the interval timer to generate a SIGALRM
// after the specified interval (dt) the function f() will be called
// at each signal
void fgTimerInit( float dt, void (*f)( int ) );

// This function returns the number of milleseconds since the last
// time it was called.
int fgGetTimeInterval( void );


#endif // _FG_TIMER_HXX


