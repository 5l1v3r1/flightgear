// ExternalPipe.hxx -- a "pipe" interface to an external flight dynamics model
//
// Written by Curtis Olson, started March 2003.
//
// Copyright (C) 2003  Curtis L. Olson  - curt@flightgear.org
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef HAVE_MKFIFO
#  include <sys/types.h>        // mkfifo() open() umask()
#  include <sys/stat.h>         // mkfifo() open() umask()
#  include <fcntl.h>            // open()
#  include <unistd.h>           // unlink()
#endif

#include <simgear/debug/logstream.hxx>
#include <simgear/io/lowlevel.hxx> // endian tests

#include <Main/fg_props.hxx>
#include <Network/native_ctrls.hxx>
#include <Network/native_fdm.hxx>

#include "ExternalPipe.hxx"


FGExternalPipe::FGExternalPipe( double dt, string name ) {
    valid = true;

    buf = new char[sizeof(char) + sizeof(int) + sizeof(ctrls)];

#ifdef HAVE_MKFIFO
    fifo_name_1 = name + "1";
    fifo_name_2 = name + "2";

    SG_LOG( SG_IO, SG_ALERT, "ExternalPipe Inited with " << name );

    // Make the named pipe
    umask(0);
    int result;
    result = mkfifo( fifo_name_1.c_str(), 0644 );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to create named pipe: "
                << fifo_name_1 );
        valid = false;
    }
    result = mkfifo( fifo_name_2.c_str(), 0644 );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to create named pipe: "
                << fifo_name_2 );
        valid = false;
    }

    pd1 = open( fifo_name_1.c_str(), O_RDWR );
    if ( pd1 == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to open named pipe: " << fifo_name_1 );
        valid = false;
    }
    pd2 = open( fifo_name_2.c_str(), O_RDWR );
    if ( pd2 == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to open named pipe: " << fifo_name_2 );
        valid = false;
    }
#endif
}


FGExternalPipe::~FGExternalPipe() {
    delete [] buf;

    SG_LOG( SG_IO, SG_INFO, "Closing up the ExternalPipe." );
    
#ifdef HAVE_MKFIFO
    // close
    int result;
    result = close( pd1 );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to close named pipe: "
                << fifo_name_1 );
    }
    result = close( pd2 );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Unable to close named pipe: "
                << fifo_name_2 );
    }
#endif
}


// Initialize the ExternalPipe flight model, dt is the time increment
// for each subsequent iteration through the EOM
void FGExternalPipe::init() {
    // Explicitly call the superclass's
    // init method first.
    common_init();

    double lon = fgGetDouble( "/sim/presets/longitude-deg" );
    double lat = fgGetDouble( "/sim/presets/latitude-deg" );
    double alt = fgGetDouble( "/sim/presets/altitude-ft" );
    double ground = fgGetDouble( "/environment/ground-elevation-m" );
    double heading = fgGetDouble("/sim/presets/heading-deg");
    double speed = fgGetDouble( "/sim/presets/airspeed-kt" );

#ifdef HAVE_MKFIFO

    char cmd[256];
    int result;

    sprintf( cmd, "1longitude-deg=%.8f", lon );
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    sprintf( cmd, "1latitude-deg=%.8f", lat );
    result = ::write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    sprintf( cmd, "1altitude-ft=%.8f", alt );
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    sprintf( cmd, "1ground-m=%.8f", ground );
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    sprintf( cmd, "1speed-kts=%.8f", speed );
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    sprintf( cmd, "1heading-deg=%.8f", heading );
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    SG_LOG( SG_IO, SG_INFO, "before sending reset command." );

    if( fgGetBool("/sim/presets/onground") ) {
      sprintf( cmd, "1reset=ground" );
    } else {
      sprintf( cmd, "1reset=air" );
    }
    result = write( pd1, cmd, strlen(cmd) );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: " << fifo_name_1 );
    }

    SG_LOG( SG_IO, SG_INFO, "Remote FDM init() finished." );
#endif
}


// Run an iteration of the EOM.
void FGExternalPipe::update( double dt ) {
#ifdef HAVE_MKFIFO
    // SG_LOG( SG_IO, SG_INFO, "Start FGExternalPipe::udpate()" );

    int length;
    int result;

    if ( is_suspended() ) {
        return;
    }

    int iterations = _calc_multiloop(dt);

    // Send control positions to remote fdm
    length = sizeof(ctrls);
    FGProps2NetCtrls( &ctrls, true, false );
    char *ptr = buf;
    *ptr = '2';
    ptr++;
    *((int *)ptr) = iterations;
    ptr += sizeof(int);
    memcpy( ptr, (char *)(&ctrls), length );
    result = write( pd1, buf, length + 1 );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Write error to named pipe: "
                << fifo_name_1 );
    }

    length = sizeof(fdm);
    result = read( pd2, (char *)(& fdm), length );
    if ( result == -1 ) {
        SG_LOG( SG_IO, SG_ALERT, "Read error from named pipe: "
                << fifo_name_2 );
    }
    FGNetFDM2Props( &fdm, false );
#endif
}
