// nmea.hxx -- NMEA protocal class
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


#ifndef _FG_NMEA_HXX
#define _FG_NMEA_HXX


#include "Include/compiler.h"

#include STL_STRING

#include "protocol.hxx"

FG_USING_STD(string);


class FGNMEA : public FGProtocol {

    char buf[ FG_MAX_MSG_SIZE ];
    int length;

public:

    FGNMEA();
    ~FGNMEA();

    bool gen_message();
    bool parse_message();

    // open hailing frequencies
    bool open();

    // process work for this port
    bool process();

    // close the channel
    bool close();
};


#endif // _FG_NMEA_HXX


