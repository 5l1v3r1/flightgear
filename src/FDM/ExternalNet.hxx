// ExternalNet.hxx -- an net interface to an external flight dynamics model
//
// Written by Curtis Olson, started November 2001.
//
// Copyright (C) 2001  Curtis L. Olson  - curt@flightgear.org
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

#ifndef _EXTERNAL_NET_HXX
#define _EXTERNAL_NET_HXX

#include <plib/netBuffer.h>
#include <plib/netSocket.h>

#include <Network/raw_ctrls.hxx>
#include <Network/net_fdm.hxx>

#include "flight.hxx"


class HTTPClient : public netBufferChannel
{
public:

    HTTPClient ( cchar* host, int port, cchar* path ) {
	open ();
	connect (host, port);

	cchar* s = netFormat ( "GET %s HTTP/1.0\r\n\r\n", path );
	bufferSend( s, strlen(s) ) ;
    }

    virtual void handleBufferRead (netBuffer& buffer)
    {
	const char* s = buffer.getData();
	while (*s)
	    fputc(*s++,stdout);

	printf("done\n");
	buffer.remove();
	printf("after buffer.remove()\n");
    }
};


class FGExternalNet: public FGInterface {

private:

    int data_in_port;
    int data_out_port;
    int cmd_port;
    string fdm_host;

    netSocket data_client;
    netSocket data_server;

    bool valid;

    FGRawCtrls ctrls;
    FGNetFDM fdm;

public:

    // Constructor
    FGExternalNet::FGExternalNet( double dt,
                                  string host, int dop, int dip, int cp );

    // Destructor
    FGExternalNet::~FGExternalNet();

    // Reset flight params to a specific position
    void init();

    // update the fdm
    void update( double dt );

};


#endif // _EXTERNAL_NET_HXX
