// bootstrap.cxx -- bootstrap routines: main()
//
// Written by Curtis Olson, started May 1997.
//
// Copyright (C) 1997 - 2002  Curtis L. Olson  - curt@flightgear.org
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

#if defined(__linux__) && defined(__i386__)
#  include <fpu_control.h>
#  include <signal.h>
#endif

#include <stdlib.h>

#include <simgear/compiler.h>
#include <simgear/structure/exception.hxx>
#include <simgear/debug/logstream.hxx>

#include STL_IOSTREAM
SG_USING_STD(cerr);
SG_USING_STD(endl);

#include "main.hxx"


#ifdef HAVE_WINDOWS_H
#  include <windows.h>
#  include <float.h>
#endif

#include FG_GLUT_H

#ifdef macintosh
#  include <console.h>		// -dw- for command line dialog
#endif


#if defined(__linux__) && defined(__i386__)

static void handleFPE (int);

static void
initFPE ()
{
    fpu_control_t fpe_flags = 0;
    _FPU_GETCW(fpe_flags);
//     fpe_flags &= ~_FPU_MASK_IM;	// invalid operation
//     fpe_flags &= ~_FPU_MASK_DM;	// denormalized operand
//     fpe_flags &= ~_FPU_MASK_ZM;	// zero-divide
//     fpe_flags &= ~_FPU_MASK_OM;	// overflow
//     fpe_flags &= ~_FPU_MASK_UM;	// underflow
//     fpe_flags &= ~_FPU_MASK_PM;	// precision (inexact result)
    _FPU_SETCW(fpe_flags);
    signal(SIGFPE, handleFPE);
}

static void
handleFPE (int num)
{
  initFPE();
  SG_LOG(SG_GENERAL, SG_ALERT, "Floating point interrupt (SIGFPE)");
}
#endif

#ifdef __APPLE__

typedef struct
{
  int  lo;
  int  hi;
} PSN;

extern "C" {
  short CPSGetCurrentProcess(PSN *psn);
  short CPSSetProcessName (PSN *psn, char *processname);
  short CPSEnableForegroundOperation(PSN *psn, int _arg2, int _arg3, int _arg4, int _arg5);
  short CPSSetFrontProcess(PSN *psn);
};

#define CPSEnableFG(psn) CPSEnableForegroundOperation(psn,0x03,0x3C,0x2C,0x1103)

#endif

#ifdef _MSC_VER
int main ( int argc, char **argv );
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                             LPSTR lpCmdLine, int nCmdShow) {

  main( __argc, __argv );
}
#endif

// Main entry point; catch any exceptions that have made it this far.
int main ( int argc, char **argv ) {

    // Enable floating-point exceptions for Linux/x86
#if defined(__linux__) && defined(__i386__)
    initFPE();
#endif

    // Enable floating-point exceptions for Windows
#if defined( _MSC_VER ) && defined( DEBUG )
    // Christian, we should document what this does
    _control87( _EM_INEXACT, _MCW_EM );
#endif

#if defined( HAVE_BC5PLUS )
    _control87(MCW_EM, MCW_EM);  /* defined in float.h */
#endif

    // Keyboard focus hack
#if defined(__APPLE__) && !defined(OSX_BUNDLE)
    {
      PSN psn;

      glutInit (&argc, argv);

      CPSGetCurrentProcess(&psn);
      CPSSetProcessName(&psn, "FlightGear");
      CPSEnableFG(&psn);
      CPSSetFrontProcess(&psn);
    }
#endif

    // FIXME: add other, more specific
    // exceptions.
    try {
        fgMainInit(argc, argv);
    } catch (sg_throwable &t) {
                            // We must use cerr rather than
                            // logging, since logging may be
                            // disabled.
        cerr << "Fatal error: " << t.getFormattedMessage()
             << "\n (received from " << t.getOrigin() << ')' << endl;
        exit(1);
    }

    return 0;
}


