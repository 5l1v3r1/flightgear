// AIMgr.hxx - definition of FGAIMgr 
// - a global management class for FlightGear generated AI traffic
//
// Written by David Luff, started March 2002.
//
// Copyright (C) 2002  David C Luff - david.luff@nottingham.ac.uk
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

#ifndef _FG_AIMGR_HXX
#define _FG_AIMGR_HXX

#include <simgear/structure/subsystem_mgr.hxx>

#include <Main/fg_props.hxx>

#include <list>

#include "ATCmgr.hxx"
#include "AIEntity.hxx"

SG_USING_STD(list);


class FGAIMgr : public SGSubsystem
{

private:
	FGATCMgr* ATC;	
	// This is purely for synactic convienience to avoid writing globals->get_ATC_mgr()-> all through the code!

    // A list of pointers to all currently active AI stuff
    typedef list <FGAIEntity*> ai_list_type;
    typedef ai_list_type::iterator ai_list_iterator;
    typedef ai_list_type::const_iterator ai_list_const_iterator;

    // Everything put in this list should be created dynamically
    // on the heap and ***DELETED WHEN REMOVED!!!!!***
    ai_list_type ai_list;
    ai_list_iterator ai_list_itr;
    // Any member function of FGATCMgr is permitted to leave this iterator pointing
    // at any point in or at the end of the list.
    // Hence any new access must explicitly first check for atc_list.end() before dereferencing.
	
	// A list of airport ID's
	typedef list < string > aptID_list_type;
	typedef aptID_list_type::iterator aptID_list_iterator;
	
	// A map of airport-IDs that have taxiway network files against bucket number
	typedef map < int, aptID_list_type* > ai_apt_map_type;
	typedef ai_apt_map_type::iterator ai_apt_map_iterator;
	ai_apt_map_type airports;
	
	// A map of airport ID's that we've activated AI traffic at
	typedef map < string, int > ai_activated_map_type;
	typedef ai_activated_map_type::iterator ai_activated_map_iterator;
	ai_activated_map_type activated;

    // Position of the Users Aircraft
    double lon;
    double lat;
    double elev;
    // Pointers to current users position
    SGPropertyNode *lon_node;
    SGPropertyNode *lat_node;
    SGPropertyNode *elev_node;

public:

    FGAIMgr();
    ~FGAIMgr();

    void init();

    void bind();

    void unbind();

    void update(double dt);

private:

	bool initDone;	// Hack - guard against update getting called before init

    // Remove a class from the ai_list and delete it from memory
    //void RemoveFromList(const char* id, atc_type tp);
	
	// Activate AI traffic at an airport
	void ActivateAirport(string id);
	
	// Search for valid airports in the vicinity of the user and activate them if necessary
	void SearchByPos(double range);

};

#endif  // _FG_AIMGR_HXX
