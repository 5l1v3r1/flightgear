// beacon.cxx -- Morse code generation class
//
// Written by Curtis Olson, started March 2001.
//
// Copyright (C) 2001  Curtis L. Olson - curt@flightgear.org
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


#include "beacon.hxx"


// constructor
FGBeacon::FGBeacon() {
}

// destructor
FGBeacon::~FGBeacon() {
}


// allocate and initialize sound samples
bool FGBeacon::init() {
    int i;
    int len;
    unsigned char *ptr;

    // Make inner marker beacon sound
    len= (int)(INNER_DIT_LEN / 2.0 );
    unsigned char inner_dit[INNER_DIT_LEN];
    make_tone( inner_dit, INNER_FREQ, len, INNER_DIT_LEN,
	       TRANSITION_BYTES );

    ptr = inner_buf;
    for ( i = 0; i < 6; ++i ) {
	memcpy( ptr, inner_dit, INNER_DIT_LEN );
	ptr += INNER_DIT_LEN;
    }

    inner = new FGSimpleSound( inner_buf, INNER_SIZE );

    // Make middle marker beacon sound
    len= (int)(MIDDLE_DIT_LEN / 2.0 );
    unsigned char middle_dit[MIDDLE_DIT_LEN];
    make_tone( middle_dit, MIDDLE_FREQ, len, MIDDLE_DIT_LEN,
	       TRANSITION_BYTES );

    len= (int)(MIDDLE_DAH_LEN * 3 / 4.0 );
    unsigned char middle_dah[MIDDLE_DAH_LEN];
    make_tone( middle_dah, MIDDLE_FREQ, len, MIDDLE_DAH_LEN,
	       TRANSITION_BYTES );

    ptr = middle_buf;
    memcpy( ptr, middle_dit, MIDDLE_DIT_LEN );
    ptr += MIDDLE_DIT_LEN;
    memcpy( ptr, middle_dah, MIDDLE_DAH_LEN );

    middle = new FGSimpleSound( middle_buf, MIDDLE_SIZE );

    // Make outer marker beacon sound
    len= (int)(OUTER_DAH_LEN * 3.0 / 4.0 );
    unsigned char outer_dah[OUTER_DAH_LEN];
    make_tone( outer_dah, OUTER_FREQ, len, OUTER_DAH_LEN,
	       TRANSITION_BYTES );
    
    ptr = outer_buf;
    memcpy( ptr, outer_dah, OUTER_DAH_LEN );
    ptr += OUTER_DAH_LEN;
    memcpy( ptr, outer_dah, OUTER_DAH_LEN );

    outer = new FGSimpleSound( outer_buf, OUTER_SIZE );

    return true;
}
