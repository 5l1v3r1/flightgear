// joyclient.hxx -- Agwagon joystick client protocal class
//
// Written by Curtis Olson, started April 2000.
//
// Copyright (C) 2000  Curtis L. Olson - curt@flightgear.org
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


#ifndef _FG_JOYCLIENT_HXX
#define _FG_JOYCLIENT_HXX


#include <simgear/compiler.h>

#include STL_STRING

#include <FDM/flight.hxx>

#include "protocol.hxx"

SG_USING_STD(string);


class FGJoyClient : public FGProtocol {

    char buf[256];
    int length;

public:

    FGJoyClient();
    ~FGJoyClient();

    // open hailing frequencies
    bool open();

    // process work for this port
    bool process();

    // close the channel
    bool close();
};


#endif // _FG_JOYCLIENT_HXX
