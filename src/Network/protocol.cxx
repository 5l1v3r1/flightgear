// protocol.cxx -- High level protocal class
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


#include <simgear/debug/logstream.hxx>
#include <simgear/io/iochannel.hxx>

#include "protocol.hxx"


FGProtocol::FGProtocol() :
    hz(0.0),
    count_down(0),
    enabled(false)
{
}


FGProtocol::~FGProtocol() {
}


// standard I/O channel open routine
bool FGProtocol::open() {
    if ( is_enabled() ) {
	SG_LOG( SG_IO, SG_ALERT, "This shouldn't happen, but the channel " 
		<< "is already in use, ignoring" );
	return false;
    }

    SGIOChannel *io = get_io_channel();

    if ( ! io->open( get_direction() ) ) {
	SG_LOG( SG_IO, SG_ALERT, "Error opening channel communication layer." );
	return false;
    }

    set_enabled( true );

    return true;
}


// dummy process routine
bool FGProtocol::process() {
    SG_LOG( SG_IO, SG_INFO, "dummy FGProtocol::process()" );
    return false;
}


// dummy close routine
bool FGProtocol::close() {
    SG_LOG( SG_IO, SG_INFO, "dummy FGProtocol::close()" );
    return false;
}


// standard I/O channel close routine
bool FGProtocol::gen_message() {
    SGIOChannel *io = get_io_channel();

    set_enabled( false );

    if ( ! io->close() ) {
	return false;
    }

    return true;
}


// dummy close routine
bool FGProtocol::parse_message() {
    SG_LOG( SG_IO, SG_INFO, "dummy FGProtocol::close()" );
    return false;
}


