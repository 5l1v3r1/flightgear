// \file telnet.hxx
// Property server class.
//
// Written by Bernie Bright, started May 2002.
//
// Copyright (C) 2002  Bernie Bright - bbright@bigpond.net.au
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

#ifndef TELNET_HXX_INCLUDED
#define TELNET_HXX_INCLUDED 1

#include <simgear/compiler.h>
#include STL_STRING
#include <vector>

SG_USING_STD(string);
SG_USING_STD(vector);

#include <plib/netChannel.h>

#include "protocol.hxx"

/**
 * Property server class.
 * This class provides a telnet-like server for remote access to
 * FlightGear properties.
 */
class FGTelnet : public FGProtocol,
		 public netChannel
{
private:

    /**
     * Server port to listen on.
     */
    int port;

public:
    /**
     * Create a new TCP server.
     * 
     * @param tokens Tokenized configuration parameters
     */
    FGTelnet( const vector<string>& tokens );

    /**
     * Destructor.
     */
    ~FGTelnet();

    /**
     * Start the telnet server.
     */
    bool open();

    /**
     * Process network activity.
     */
    bool process();

    /**
     * 
     */
    bool close();

    /**
     * Accept a new client connection.
     */
    void handleAccept();

};

#endif //TELNET_HXX_INCLUDED

