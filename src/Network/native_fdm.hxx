// native_fdm.hxx -- FGFS "Native" flight dynamics protocal class
//
// Written by Curtis Olson, started September 2001.
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


#ifndef _FG_NATIVE_FDM_HXX
#define _FG_NATIVE_FDM_HXX


#include <simgear/compiler.h>

#include <FDM/flight.hxx>

#include "protocol.hxx"
#include "net_fdm.hxx"


class FGNativeFDM : public FGProtocol, public FGInterface {

    FGNetFDM buf;
    int length;

public:

    FGNativeFDM();
    ~FGNativeFDM();

    // open hailing frequencies
    bool open();

    // process work for this port
    bool process();

    // close the channel
    bool close();
};


// Helper functions which may be useful outside this class

// Populate the FGNetFDM structure from the property tree.
void FGProps2NetFDM( FGNetFDM *net );

// Update the property tree from the FGNetFDM structure.
void FGNetFDM2Props( FGNetFDM *net );


#endif // _FG_NATIVE_FDM_HXX


