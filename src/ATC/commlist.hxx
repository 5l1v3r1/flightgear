// commlist.hxx -- comm frequency lookup class
//
// Written by David Luff and Alexander Kappes, started Jan 2003.
// Based on navlist.hxx by Curtis Olson, started April 2000.
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

/*****************************************************************
*
* FGCommList is used to store communication frequency information
* for the ATC and AI subsystems.  Two maps are maintained - one
* searchable by location and one searchable by frequency.  The
* data structure returned from the search is the ATCData struct
* defined in ATC.hxx, containing location, frequency, name, range
* and type of the returned station.
*
******************************************************************/

#ifndef _FG_COMMLIST_HXX
#define _FG_COMMLIST_HXX


#include <simgear/compiler.h>
#include <simgear/misc/sg_path.hxx>

#include <map>
#include <list>
#include <string>

#include "ATC.hxx"
#include "atis.hxx"

SG_USING_STD(map);
SG_USING_STD(vector);
SG_USING_STD(string);

// A list of ATC stations
typedef list < ATCData > comm_list_type;
typedef comm_list_type::iterator comm_list_iterator;
typedef comm_list_type::const_iterator comm_list_const_iterator;

// A map of ATC station lists
typedef map < int, comm_list_type > comm_map_type;
typedef comm_map_type::iterator comm_map_iterator;
typedef comm_map_type::const_iterator comm_map_const_iterator;


class FGCommList {
	
public:

    FGCommList();
    ~FGCommList();

    // load all comm frequencies and build the map
    bool init( SGPath path );

    // query the database for the specified frequency, lon and lat are
    // in degrees, elev is in meters
	// If no atc_type is specified, it returns true if any non-invalid type is found
	// If atc_type is specifed, returns true only if the specified type is found
	// The data found is written into the passed-in ATCData structure.
    bool FindByFreq( double lon, double lat, double elev, double freq, ATCData* ad, atc_type tp = INVALID );
	
    // query the database by location, lon and lat are
    // in degrees, elev is in meters
	// Returns the number of stations of the specified type that are in range, and pushes them into stations
	// If atc_type is specifed, returns the number of all stations in range, and pushes them into stations
	// ** stations is erased before use **
    int FindByPos( double lon, double lat, double elev, comm_list_type* stations, atc_type tp = INVALID );

    // Return the callsign for an ATIS transmission given transmission time and airpord id
	// This maybe should get moved somewhere else!!
    int GetCallSign( string apt_id, int hours, int mins );
	
private:
	
	// Comm stations mapped by frequency
	comm_map_type commlist_freq;	
	
	// Comm stations mapped by bucket
	comm_map_type commlist_bck;

	// Load comms from a specified path (which must include the filename)	
	bool LoadComms(SGPath path);

//----------- This stuff is left over from atislist.[ch]xx and maybe should move somewhere else
	// Add structure and map for storing a log of atis transmissions
	// made in this session of FlightGear.  This allows the callsign
	// to be allocated correctly wrt time.
	typedef struct {
		int hours;
		int mins;
		int callsign;
	} atis_transmission_type;

    typedef map < string, atis_transmission_type > atis_log_type;
    typedef atis_log_type::iterator atis_log_iterator;
    typedef atis_log_type::const_iterator atis_log_const_iterator;

    atis_log_type atislog;
//-----------------------------------------------------------------------------------------------

};


extern FGCommList *current_commlist;


#endif // _FG_COMMLIST_HXX
