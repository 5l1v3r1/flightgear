// rul.cxx -- "RUL" protocal class (for some sort of motion platform
//            some guy was building)
//
// Written by Curtis Olson, started November 1999.
//
// Copyright (C) 1999  Curtis L. Olson - curt@flightgear.org
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


#include <stdio.h>		// sprintf()

#include <simgear/debug/logstream.hxx>
#include <simgear/math/fg_geodesy.hxx>

#include <FDM/flight.hxx>

#include "iochannel.hxx"
#include "rul.hxx"


FGRUL::FGRUL() {
}


FGRUL::~FGRUL() {
}


// "RUL" output format (for some sort of motion platform)
//
// The Baud rate is 2400 , one start bit, eight data bits, 1 stop bit,
// no parity.
//
// For position it requires a 3-byte data packet defined as follows:
//
// First bite: ascII character "P" ( 0x50 or 80 decimal )
// Second byte X pos. (1-255) 1 being 0* and 255 being 359*
// Third byte Y pos.( 1-255) 1 being 0* and 255 359*
//
// So sending 80 127 127 to the two axis motors will position on 180*
// The RS- 232 port is a nine pin connector and the only pins used are
// 3&5.

bool FGRUL::gen_message() {
    // cout << "generating rul message" << endl;
    FGInterface *f = cur_fdm_state;

    // get roll and pitch, convert to degrees
    double roll_deg = f->get_Phi() * RAD_TO_DEG;
    while ( roll_deg < -180.0 ) {
	roll_deg += 360.0;
    }
    while ( roll_deg > 180.0 ) {
	roll_deg -= 360.0;
    }

    double pitch_deg = f->get_Theta() * RAD_TO_DEG;
    while ( pitch_deg < -180.0 ) {
	pitch_deg += 360.0;
    }
    while ( pitch_deg > 180.0 ) {
	pitch_deg -= 360.0;
    }

    // scale roll and pitch to output format (1 - 255)
    // straight && level == (128, 128)

    int roll = (int)( (roll_deg+180.0) * 255.0 / 360.0) + 1;
    int pitch = (int)( (pitch_deg+180.0) * 255.0 / 360.0) + 1;

    sprintf( buf, "p%c%c\n", roll, pitch);
    length = 4;

    FG_LOG( FG_IO, FG_INFO, "p " << roll << " " << pitch );

    return true;
}


// parse RUL message
bool FGRUL::parse_message() {
    FG_LOG( FG_IO, FG_ALERT, "RUL input not supported" );

    return false;
}


// process work for this port
bool FGRUL::process() {
    FGIOChannel *io = get_io_channel();

    if ( get_direction() == out ) {
	gen_message();
	if ( ! io->write( buf, length ) ) {
	    FG_LOG( FG_IO, FG_ALERT, "Error writing data." );
	    return false;
	}
    } else if ( get_direction() == in ) {
	FG_LOG( FG_IO, FG_ALERT, "in direction not supported for RUL." );
	return false;
    }

    return true;
}
