// generic.cxx -- generic protocal class
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
#include <simgear/structure/exception.hxx>
#include <simgear/misc/sg_path.hxx>
#include <simgear/props/props.hxx>
#include <simgear/props/props_io.hxx>

#include <Main/globals.hxx>
#include <Main/fg_props.hxx>

#include "generic.hxx"


FGGeneric::FGGeneric(string& config) {

    string file = config+".xml";

    SGPath path( globals->get_fg_root() );
    path.append("Protocol");
    path.append(file.c_str());
    SG_LOG(SG_GENERAL, SG_INFO, "Reading communication protocol from "
                                << path.str());

    SGPropertyNode root;
    try {
        readProperties(path.str(), &root);
     } catch (const sg_exception &e) {
        SG_LOG(SG_GENERAL, SG_ALERT,
         "Unable to load the protocol configuration file");
         return;
    }

    SGPropertyNode *output = root.getNode("generic/output");

        /* These variables specified in the fgfsbase/Properties/xxxx.xml file for each format
         * var_sep_string = the string/charachter to place between variables
         * line_sep_string = the string/charachter to place at the end of each lot of variables
         */
    var_sep_string = output->getStringValue("var_separator");
    line_sep_string = output->getStringValue("line_separator");

        if ( var_sep_string == "newline" )
                var_separator = '\n';
        else if ( var_sep_string == "tab" )
                var_separator = '\t';
        else if ( var_sep_string == "space" )
                var_separator = ' ';
        else if ( var_sep_string == "formfeed" )
                var_separator = '\f';
        else if ( var_sep_string == "carriagereturn" )
                var_sep_string = '\r';
        else if ( var_sep_string == "verticaltab" )
                var_separator = '\v';
        else
                var_separator = var_sep_string;

        if ( line_sep_string == "newline" )
                line_separator = '\n';
        if ( line_sep_string == "tab" )
                line_separator = '\t';
        if ( line_sep_string == "space" )
                line_separator = ' ';
        else if ( line_sep_string == "formfeed" )
                line_separator = '\f';
        else if ( line_sep_string == "carriagereturn" )
                line_separator = '\r';
        else if ( line_sep_string == "verticaltab" )
                line_separator = '\v';
        else
                line_separator = line_sep_string;


    vector<SGPropertyNode_ptr> chunks = output->getChildren("chunk");
    for (unsigned int i = 0; i < chunks.size(); i++) {

        _serial_prot chunk;

     // chunk.name = chunks[i]->getStringValue("name");
        chunk.format = chunks[i]->getStringValue("format", "%d");
        chunk.offset = chunks[i]->getDoubleValue("offset");
        chunk.factor = chunks[i]->getDoubleValue("offset", 1.0);

        string node = chunks[i]->getStringValue("node");
        chunk.prop = fgGetNode(node.c_str(), true);

        string type = chunks[i]->getStringValue("type");
        if (type == "bool")
            chunk.type = FG_BOOL;
        else if (type == "float")
            chunk.type = FG_DOUBLE;
        else if (type == "string")
            chunk.type = FG_STRING;
        else
            chunk.type = FG_INT;

        _message.push_back(chunk);
        
    }

}

FGGeneric::~FGGeneric() {
    _message.clear();
}


// generate the message
bool FGGeneric::gen_message() {

    string generic_sentence;
    char tmp[255];

    int v;
    double d;

    for (unsigned int i = 0; i < _message.size(); i++) {

        if (i > 0)
           generic_sentence += var_separator;

        switch (_message[i].type) {
        case FG_INT:
            v = _message[i].offset +
                    _message[i].prop->getIntValue() * _message[i].factor;
            snprintf(tmp, 255, _message[i].format.c_str(), v);
            break;

        case FG_BOOL:
            snprintf(tmp, 255, _message[i].format.c_str(),
                               _message[i].prop->getBoolValue());
            break;

        case FG_DOUBLE:
            d = _message[i].offset +
                       _message[i].prop->getDoubleValue() * _message[i].factor;
            snprintf(tmp, 255, _message[i].format.c_str(), d);
            break;

        default: // SG_STRING
             snprintf(tmp, 255, _message[i].format.c_str(),
                               _message[i].prop->getStringValue());
        }

        generic_sentence += tmp;
    }

    /* After each lot of variables has been added, put the line separator char/string */
    generic_sentence += line_separator;
 
            
    length =  generic_sentence.length();
    strncpy( buf, generic_sentence.c_str(), length );

    return true;
}

bool FGGeneric::parse_message() {
        return true;
}



// open hailing frequencies
bool FGGeneric::open() {
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


// process work for this port
bool FGGeneric::process() {
    SGIOChannel *io = get_io_channel();

    if ( get_direction() == SG_IO_OUT ) {
        gen_message();
        if ( ! io->write( buf, length ) ) {
            SG_LOG( SG_IO, SG_WARN, "Error writing data." );
            return false;
        }
    } else if ( get_direction() == SG_IO_IN ) {
        // Temporarliy disable this as output only!
        //if ( (length = io->readline( buf, FG_MAX_MSG_SIZE )) > 0 ) {
        //    parse_message();
        //} else {
        //    SG_LOG( SG_IO, SG_ALERT, "Error reading data." );
        //    return false;
        //}
    }

    return true;
}


// close the channel
bool FGGeneric::close() {
    SGIOChannel *io = get_io_channel();

    set_enabled( false );

    if ( ! io->close() ) {
        return false;
    }

    return true;
}
