// auto_gui.cxx -- autopilot gui interface
//
// Written by Norman Vine <nhv@cape.com>
// Arranged by Curt Olson <curt@flightgear.org>
//
// Copyright (C) 1998 - 2000
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

#include <simgear/compiler.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include STL_STRING

#include <Aircraft/aircraft.hxx>
#include <FDM/flight.hxx>
#include <Controls/controls.hxx>
#include <Scenery/scenery.hxx>

#include <simgear/constants.h>
#include <simgear/sg_inlines.h>
#include <simgear/debug/logstream.hxx>
#include <simgear/math/sg_geodesy.hxx>
#include <simgear/misc/sg_path.hxx>

#include <Airports/simple.hxx>
#include <GUI/gui.h>
#include <Main/fg_init.hxx>
#include <Main/globals.hxx>
#include <Main/fg_props.hxx>
#include <Navaids/fixlist.hxx>

#include "auto_gui.hxx"
#include "newauto.hxx"

SG_USING_STD(string);


#define mySlider puSlider

// Climb speed constants
const double min_climb = 70.0;	// kts
const double best_climb = 75.0;	// kts
const double ideal_climb_rate = 500.0; // fpm

/// These statics will eventually go into the class
/// they are just here while I am experimenting -- NHV :-)
// AutoPilot Gain Adjuster members
static double MaxRollAdjust;        // MaxRollAdjust       = 2 * APData->MaxRoll;
static double RollOutAdjust;        // RollOutAdjust       = 2 * APData->RollOut;
static double MaxAileronAdjust;     // MaxAileronAdjust    = 2 * APData->MaxAileron;
static double RollOutSmoothAdjust;  // RollOutSmoothAdjust = 2 * APData->RollOutSmooth;

static float MaxRollValue;          // 0.1 -> 1.0
static float RollOutValue;
static float MaxAileronValue;
static float RollOutSmoothValue;

static float TmpMaxRollValue;       // for cancel operation
static float TmpRollOutValue;
static float TmpMaxAileronValue;
static float TmpRollOutSmoothValue;

static puDialogBox *APAdjustDialog;
static puFrame     *APAdjustFrame;
static puText      *APAdjustDialogMessage;
static puFont      APAdjustLegendFont;
static puFont      APAdjustLabelFont;

static puOneShot *APAdjustOkButton;
static puOneShot *APAdjustResetButton;
static puOneShot *APAdjustCancelButton;

//static puButton        *APAdjustDragButton;

static puText *APAdjustMaxRollTitle;
static puText *APAdjustRollOutTitle;
static puText *APAdjustMaxAileronTitle;
static puText *APAdjustRollOutSmoothTitle;

static puText *APAdjustMaxAileronText;
static puText *APAdjustMaxRollText;
static puText *APAdjustRollOutText;
static puText *APAdjustRollOutSmoothText;

static mySlider *APAdjustHS0;
static mySlider *APAdjustHS1;
static mySlider *APAdjustHS2;
static mySlider *APAdjustHS3;

static char SliderText[ 4 ][ 8 ];

///////// AutoPilot New Heading Dialog

static puDialogBox     *ApHeadingDialog;
static puFrame         *ApHeadingDialogFrame;
static puText          *ApHeadingDialogMessage;
static puInput         *ApHeadingDialogInput;
static puOneShot       *ApHeadingDialogOkButton;
static puOneShot       *ApHeadingDialogCancelButton;


///////// AutoPilot New Altitude Dialog

static puDialogBox     *ApAltitudeDialog = 0;
static puFrame         *ApAltitudeDialogFrame = 0;
static puText          *ApAltitudeDialogMessage = 0;
static puInput         *ApAltitudeDialogInput = 0;

static puOneShot       *ApAltitudeDialogOkButton = 0;
static puOneShot       *ApAltitudeDialogCancelButton = 0;


/// The beginnings of Lock AutoPilot to target location :-)
//  Needs cleaning up but works
//  These statics should disapear when this is a class
static puDialogBox     *TgtAptDialog = 0;
static puFrame         *TgtAptDialogFrame = 0;
static puText          *TgtAptDialogMessage = 0;
static puInput         *TgtAptDialogInput = 0;
static puListBox       *TgtAptDialogWPList = 0;
static puSlider        *TgtAptDialogSlider = 0;
static puArrowButton   *TgtAptDialogUPArrow = 0;
static puArrowButton   *TgtAptDialogDNArrow = 0;
static char**          WPList;
static int             WPListsize;

static char NewTgtAirportId[16];
static char NewTgtAirportLabel[] = "New Apt/Fix ID";

static puOneShot       *TgtAptDialogOkButton = 0;
static puOneShot       *TgtAptDialogCancelButton = 0;
static puOneShot       *TgtAptDialogResetButton = 0;


// extern char *coord_format_lat(float);
// extern char *coord_format_lon(float);

// THIS NEEDS IMPROVEMENT !!!!!!!!!!!!!
static int scan_number(char *s, double *new_value)
{
    int ret = 0;
    char WordBuf[64];
    char *cptr = s;
    char *WordBufPtr = WordBuf;
    if (*cptr == '+')
	cptr++;
    if (*cptr == '-') {
	*WordBufPtr++ = *cptr++;
    }
    while (isdigit(*cptr) ) {
	*WordBufPtr++ = *cptr++;
	ret = 1;
    }
    if (*cptr == '.') 
	*WordBufPtr++ = *cptr++;  // put the '.' into the string
    while (isdigit(*cptr)) {
	*WordBufPtr++ = *cptr++;
	ret = 1;
    }
    if( ret == 1 ) {
	*WordBufPtr = '\0';
	sscanf(WordBuf, "%lf", new_value);
    }

    return(ret);
} // scan_number


void ApHeadingDialog_Cancel(puObject *)
{
    ApHeadingDialogInput->rejectInput();
    FG_POP_PUI_DIALOG( ApHeadingDialog );
}

void ApHeadingDialog_OK (puObject *me)
{
    int error = 0;
    char *c;
    string s;
    ApHeadingDialogInput -> getValue( &c );

    if( strlen(c) ) {
	double NewHeading;
	if( scan_number( c, &NewHeading ) )
	    {
		if ( !current_autopilot->get_HeadingEnabled() ) {
		    current_autopilot->set_HeadingEnabled( true );
		}
		current_autopilot->HeadingSet( NewHeading );
	    } else {
		error = 1;
		s = c;
		s += " is not a valid number.";
	    }
    }
    ApHeadingDialog_Cancel(me);
    if( error )  mkDialog(s.c_str());
}

void NewHeading(puObject *cb)
{
    //	string ApHeadingLabel( "Enter New Heading" );
    //	ApHeadingDialogMessage  -> setLabel(ApHeadingLabel.c_str());
    float heading = current_autopilot->get_DGTargetHeading();
    while ( heading < 0.0 ) { heading += 360.0; }
    ApHeadingDialogInput   ->    setValue ( heading );
    ApHeadingDialogInput    -> acceptInput();
    FG_PUSH_PUI_DIALOG( ApHeadingDialog );
}

void NewHeadingInit()
{
    //	printf("NewHeadingInit\n");
    char NewHeadingLabel[] = "Enter New Heading";
    char *s;

    float heading = fgGetDouble("/orientation/heading-deg");
    int len = 260/2 -
	(puGetDefaultLabelFont().getStringWidth( NewHeadingLabel ) / 2 );

    ApHeadingDialog = new puDialogBox (150, 50);
    {
	ApHeadingDialogFrame   = new puFrame (0, 0, 260, 150);

	ApHeadingDialogMessage = new puText   (len, 110);
	ApHeadingDialogMessage    -> setDefaultValue (NewHeadingLabel);
	ApHeadingDialogMessage    -> getDefaultValue (&s);
	ApHeadingDialogMessage    -> setLabel        (s);

	ApHeadingDialogInput   = new puInput  ( 50, 70, 210, 100 );
	ApHeadingDialogInput   ->    setValue ( heading );

	ApHeadingDialogOkButton     =  new puOneShot         (50, 10, 110, 50);
	ApHeadingDialogOkButton     ->     setLegend         (gui_msg_OK);
	ApHeadingDialogOkButton     ->     makeReturnDefault (TRUE);
	ApHeadingDialogOkButton     ->     setCallback       (ApHeadingDialog_OK);

	ApHeadingDialogCancelButton =  new puOneShot         (140, 10, 210, 50);
	ApHeadingDialogCancelButton ->     setLegend         (gui_msg_CANCEL);
	ApHeadingDialogCancelButton ->     setCallback       (ApHeadingDialog_Cancel);

    }
    FG_FINALIZE_PUI_DIALOG( ApHeadingDialog );
}

void ApAltitudeDialog_Cancel(puObject *)
{
    ApAltitudeDialogInput -> rejectInput();
    FG_POP_PUI_DIALOG( ApAltitudeDialog );
}

void ApAltitudeDialog_OK (puObject *me)
{
    int error = 0;
    string s;
    char *c;
    ApAltitudeDialogInput->getValue( &c );

    if( strlen( c ) ) {
	double NewAltitude;
	if( scan_number( c, &NewAltitude) )
	    {
		if ( !current_autopilot->get_AltitudeEnabled() ) {
		    current_autopilot->set_AltitudeEnabled( true );
		}
		current_autopilot->AltitudeSet( NewAltitude );
	    } else {
		error = 1;
		s = c;
		s += " is not a valid number.";
	    }
    }
    ApAltitudeDialog_Cancel(me);
    if( error )  mkDialog(s.c_str());
}

void NewAltitude(puObject *cb)
{
    float altitude = current_autopilot->get_TargetAltitude() * SG_METER_TO_FEET;
    ApAltitudeDialogInput -> setValue( altitude );
    ApAltitudeDialogInput -> acceptInput();
    FG_PUSH_PUI_DIALOG( ApAltitudeDialog );
}

void NewAltitudeInit()
{
    //	printf("NewAltitudeInit\n");
    char NewAltitudeLabel[] = "Enter New Altitude";
    char *s;

    float alt = cur_fdm_state->get_Altitude();

    if ( fgGetString("/sim/startup/units") == "meters") {
	alt *= SG_FEET_TO_METER;
    }

    int len = 260/2 -
	(puGetDefaultLabelFont().getStringWidth( NewAltitudeLabel ) / 2);

    //	ApAltitudeDialog = new puDialogBox (150, 50);
    ApAltitudeDialog = new puDialogBox (150, 200);
    {
	ApAltitudeDialogFrame   = new puFrame  (0, 0, 260, 150);
	ApAltitudeDialogMessage = new puText   (len, 110);
	ApAltitudeDialogMessage    -> setDefaultValue (NewAltitudeLabel);
	ApAltitudeDialogMessage    -> getDefaultValue (&s);
	ApAltitudeDialogMessage    -> setLabel (s);

	ApAltitudeDialogInput   = new puInput  ( 50, 70, 210, 100 );
	ApAltitudeDialogInput      -> setValue ( alt );
	// Uncomment the next line to have input active on startup
	// ApAltitudeDialogInput   ->    acceptInput       ( );
	// cursor at begining or end of line ?
	//len = strlen(s);
	//		len = 0;
	//		ApAltitudeDialogInput   ->    setCursor         ( len );
	//		ApAltitudeDialogInput   ->    setSelectRegion   ( 5, 9 );

	ApAltitudeDialogOkButton     =  new puOneShot         (50, 10, 110, 50);
	ApAltitudeDialogOkButton     ->     setLegend         (gui_msg_OK);
	ApAltitudeDialogOkButton     ->     makeReturnDefault (TRUE);
	ApAltitudeDialogOkButton     ->     setCallback       (ApAltitudeDialog_OK);

	ApAltitudeDialogCancelButton =  new puOneShot         (140, 10, 210, 50);
	ApAltitudeDialogCancelButton ->     setLegend         (gui_msg_CANCEL);
	ApAltitudeDialogCancelButton ->     setCallback       (ApAltitudeDialog_Cancel);

    }
    FG_FINALIZE_PUI_DIALOG( ApAltitudeDialog );
}


static void maxroll_adj( puObject *hs ) {
    float val ;
    
    hs-> getValue ( &val ) ;
    SG_CLAMP_RANGE ( val, 0.1f, 1.0f ) ;
    //    printf ( "maxroll_adj( %p ) %f %f\n", hs, val, MaxRollAdjust * val ) ;
    current_autopilot->set_MaxRoll( MaxRollAdjust * val );
    sprintf( SliderText[ 0 ], "%05.2f", current_autopilot->get_MaxRoll() );
    APAdjustMaxRollText -> setLabel ( SliderText[ 0 ] ) ;
}

static void rollout_adj( puObject *hs ) {
    float val ;

    hs-> getValue ( &val ) ;
    SG_CLAMP_RANGE ( val, 0.1f, 1.0f ) ;
    //    printf ( "rollout_adj( %p ) %f %f\n", hs, val, RollOutAdjust * val ) ;
    current_autopilot->set_RollOut( RollOutAdjust * val );
    sprintf( SliderText[ 1 ], "%05.2f", current_autopilot->get_RollOut() );
    APAdjustRollOutText -> setLabel ( SliderText[ 1 ] );
}

static void maxaileron_adj( puObject *hs ) {
    float val ;

    hs-> getValue ( &val ) ;
    SG_CLAMP_RANGE ( val, 0.1f, 1.0f ) ;
    //    printf ( "maxaileron_adj( %p ) %f %f\n", hs, val, MaxAileronAdjust * val ) ;
    current_autopilot->set_MaxAileron( MaxAileronAdjust * val );
    sprintf( SliderText[ 3 ], "%05.2f", current_autopilot->get_MaxAileron() );
    APAdjustMaxAileronText -> setLabel ( SliderText[ 3 ] );
}

static void rolloutsmooth_adj( puObject *hs ) {
    float val ;

    hs -> getValue ( &val ) ;
    SG_CLAMP_RANGE ( val, 0.1f, 1.0f ) ;
    //    printf ( "rolloutsmooth_adj( %p ) %f %f\n", hs, val, RollOutSmoothAdjust * val ) ;
    current_autopilot->set_RollOutSmooth( RollOutSmoothAdjust * val );
    sprintf( SliderText[ 2 ], "%5.2f", current_autopilot->get_RollOutSmooth() );
    APAdjustRollOutSmoothText-> setLabel ( SliderText[ 2 ] );

}

static void goAwayAPAdjust (puObject *)
{
    FG_POP_PUI_DIALOG( APAdjustDialog );
}

void cancelAPAdjust( puObject *self ) {
    current_autopilot->set_MaxRoll( TmpMaxRollValue );
    current_autopilot->set_RollOut( TmpRollOutValue );
    current_autopilot->set_MaxAileron( TmpMaxAileronValue );
    current_autopilot->set_RollOutSmooth( TmpRollOutSmoothValue );

    goAwayAPAdjust(self);
}

void resetAPAdjust( puObject *self ) {
    current_autopilot->set_MaxRoll( MaxRollAdjust / 2 );
    current_autopilot->set_RollOut( RollOutAdjust / 2 );
    current_autopilot->set_MaxAileron( MaxAileronAdjust / 2 );
    current_autopilot->set_RollOutSmooth( RollOutSmoothAdjust / 2 );

    FG_POP_PUI_DIALOG( APAdjustDialog );

    fgAPAdjust( self );
}

void fgAPAdjust( puObject *self ) {
    TmpMaxRollValue       = current_autopilot->get_MaxRoll();
    TmpRollOutValue       = current_autopilot->get_RollOut();
    TmpMaxAileronValue    = current_autopilot->get_MaxAileron();
    TmpRollOutSmoothValue = current_autopilot->get_RollOutSmooth();

    MaxRollValue       = current_autopilot->get_MaxRoll() / MaxRollAdjust;
    RollOutValue       = current_autopilot->get_RollOut() / RollOutAdjust;
    MaxAileronValue    = current_autopilot->get_MaxAileron() / MaxAileronAdjust;
    RollOutSmoothValue = current_autopilot->get_RollOutSmooth()
	/ RollOutSmoothAdjust;

    APAdjustHS0-> setValue ( MaxRollValue ) ;
    APAdjustHS1-> setValue ( RollOutValue ) ;
    APAdjustHS2-> setValue ( RollOutSmoothValue ) ;
    APAdjustHS3-> setValue ( MaxAileronValue ) ;

    FG_PUSH_PUI_DIALOG( APAdjustDialog );
}

// Done once at system initialization
void fgAPAdjustInit() {

    //	printf("fgAPAdjustInit\n");
#define HORIZONTAL  FALSE

    int DialogX = 40;
    int DialogY = 100;
    int DialogWidth = 230;

    char Label[] =  "AutoPilot Adjust";
    char *s;

    int labelX = (DialogWidth / 2) -
	(puGetDefaultLabelFont().getStringWidth( Label ) / 2);
    labelX -= 30;  // KLUDGEY

    int nSliders = 4;
    int slider_x = 10;
    int slider_y = 55;
    int slider_width = 210;
    int slider_title_x = 15;
    int slider_value_x = 160;
    float slider_delta = 0.1f;

    TmpMaxRollValue       = current_autopilot->get_MaxRoll();
    TmpRollOutValue       = current_autopilot->get_RollOut();
    TmpMaxAileronValue    = current_autopilot->get_MaxAileron();
    TmpRollOutSmoothValue = current_autopilot->get_RollOutSmooth();

    MaxRollAdjust = 2 * current_autopilot->get_MaxRoll();
    RollOutAdjust = 2 * current_autopilot->get_RollOut();
    MaxAileronAdjust = 2 * current_autopilot->get_MaxAileron();
    RollOutSmoothAdjust = 2 * current_autopilot->get_RollOutSmooth();

    MaxRollValue       = current_autopilot->get_MaxRoll() / MaxRollAdjust;
    RollOutValue       = current_autopilot->get_RollOut() / RollOutAdjust;
    MaxAileronValue    = current_autopilot->get_MaxAileron() / MaxAileronAdjust;
    RollOutSmoothValue = current_autopilot->get_RollOutSmooth()
	/ RollOutSmoothAdjust;

    puGetDefaultFonts (  &APAdjustLegendFont,  &APAdjustLabelFont );
    APAdjustDialog = new puDialogBox ( DialogX, DialogY ); {
	int horiz_slider_height = APAdjustLabelFont.getStringHeight() +
	    APAdjustLabelFont.getStringDescender() +
	    PUSTR_TGAP + PUSTR_BGAP + 5;

	APAdjustFrame = new puFrame ( 0, 0,
				      DialogWidth,
				      85 + nSliders * horiz_slider_height );

	APAdjustDialogMessage = new puText ( labelX,
					     52 + nSliders
					     * horiz_slider_height );
	APAdjustDialogMessage -> setDefaultValue ( Label );
	APAdjustDialogMessage -> getDefaultValue ( &s );
	APAdjustDialogMessage -> setLabel        ( s );

	APAdjustHS0 = new mySlider ( slider_x, slider_y,
				     slider_width, HORIZONTAL ) ;
	APAdjustHS0-> setDelta ( slider_delta ) ;
	APAdjustHS0-> setValue ( MaxRollValue ) ;
	APAdjustHS0-> setCBMode ( PUSLIDER_DELTA ) ;
	APAdjustHS0-> setCallback ( maxroll_adj ) ;

	sprintf( SliderText[ 0 ], "%05.2f", current_autopilot->get_MaxRoll() );
	APAdjustMaxRollTitle = new puText ( slider_title_x, slider_y ) ;
	APAdjustMaxRollTitle-> setDefaultValue ( "MaxRoll" ) ;
	APAdjustMaxRollTitle-> getDefaultValue ( &s ) ;
	APAdjustMaxRollTitle-> setLabel ( s ) ;
	APAdjustMaxRollText = new puText ( slider_value_x, slider_y ) ;
	APAdjustMaxRollText-> setLabel ( SliderText[ 0 ] ) ;

	slider_y += horiz_slider_height;

	APAdjustHS1 = new mySlider ( slider_x, slider_y, slider_width,
				     HORIZONTAL ) ;
	APAdjustHS1-> setDelta ( slider_delta ) ;
	APAdjustHS1-> setValue ( RollOutValue ) ;
	APAdjustHS1-> setCBMode ( PUSLIDER_DELTA ) ;
	APAdjustHS1-> setCallback ( rollout_adj ) ;

	sprintf( SliderText[ 1 ], "%05.2f", current_autopilot->get_RollOut() );
	APAdjustRollOutTitle = new puText ( slider_title_x, slider_y ) ;
	APAdjustRollOutTitle-> setDefaultValue ( "AdjustRollOut" ) ;
	APAdjustRollOutTitle-> getDefaultValue ( &s ) ;
	APAdjustRollOutTitle-> setLabel ( s ) ;
	APAdjustRollOutText = new puText ( slider_value_x, slider_y ) ;
	APAdjustRollOutText-> setLabel ( SliderText[ 1 ] );

	slider_y += horiz_slider_height;

	APAdjustHS2 = new mySlider ( slider_x, slider_y, slider_width,
				     HORIZONTAL ) ;
	APAdjustHS2-> setDelta ( slider_delta ) ;
	APAdjustHS2-> setValue ( RollOutSmoothValue ) ;
	APAdjustHS2-> setCBMode ( PUSLIDER_DELTA ) ;
	APAdjustHS2-> setCallback ( rolloutsmooth_adj ) ;

	sprintf( SliderText[ 2 ], "%5.2f", 
		 current_autopilot->get_RollOutSmooth() );
	APAdjustRollOutSmoothTitle = new puText ( slider_title_x, slider_y ) ;
	APAdjustRollOutSmoothTitle-> setDefaultValue ( "RollOutSmooth" ) ;
	APAdjustRollOutSmoothTitle-> getDefaultValue ( &s ) ;
	APAdjustRollOutSmoothTitle-> setLabel ( s ) ;
	APAdjustRollOutSmoothText = new puText ( slider_value_x, slider_y ) ;
	APAdjustRollOutSmoothText-> setLabel ( SliderText[ 2 ] );

	slider_y += horiz_slider_height;

	APAdjustHS3 = new mySlider ( slider_x, slider_y, slider_width,
				     HORIZONTAL ) ;
	APAdjustHS3-> setDelta ( slider_delta ) ;
	APAdjustHS3-> setValue ( MaxAileronValue ) ;
	APAdjustHS3-> setCBMode ( PUSLIDER_DELTA ) ;
	APAdjustHS3-> setCallback ( maxaileron_adj ) ;

	sprintf( SliderText[ 3 ], "%05.2f", 
		 current_autopilot->get_MaxAileron() );
	APAdjustMaxAileronTitle = new puText ( slider_title_x, slider_y ) ;
	APAdjustMaxAileronTitle-> setDefaultValue ( "MaxAileron" ) ;
	APAdjustMaxAileronTitle-> getDefaultValue ( &s ) ;
	APAdjustMaxAileronTitle-> setLabel ( s ) ;
	APAdjustMaxAileronText = new puText ( slider_value_x, slider_y ) ;
	APAdjustMaxAileronText-> setLabel ( SliderText[ 3 ] );

	APAdjustOkButton = new puOneShot ( 10, 10, 60, 50 );
	APAdjustOkButton-> setLegend ( gui_msg_OK );
	APAdjustOkButton-> makeReturnDefault ( TRUE );
	APAdjustOkButton-> setCallback ( goAwayAPAdjust );

	APAdjustCancelButton = new puOneShot ( 70, 10, 150, 50 );
	APAdjustCancelButton-> setLegend ( gui_msg_CANCEL );
	APAdjustCancelButton-> setCallback ( cancelAPAdjust );

	APAdjustResetButton = new puOneShot ( 160, 10, 220, 50 );
	APAdjustResetButton-> setLegend ( gui_msg_RESET );
	APAdjustResetButton-> setCallback ( resetAPAdjust );
    }
    FG_FINALIZE_PUI_DIALOG( APAdjustDialog );

#undef HORIZONTAL
}

// Simple Dialog to input Target Airport
void TgtAptDialog_Cancel(puObject *)
{
    FG_POP_PUI_DIALOG( TgtAptDialog );
}

void TgtAptDialog_OK (puObject *)
{
    string TgtAptId;
    
    //    FGTime *t = FGTime::cur_time_params;
    //    int PauseMode = t->getPause();
    //    if(!PauseMode)
    //        t->togglePauseMode();
    
    char *s;
    TgtAptDialogInput->getValue(&s);

    string tmp = s;
    double alt = 0.0;
    unsigned int pos = tmp.find( "@" );
    if ( pos != string::npos ) {
	TgtAptId = tmp.substr( 0, pos );
	string alt_str = tmp.substr( pos + 1 );
	alt = atof( alt_str.c_str() );
	if ( fgGetString("/sim/startup/units") == "feet" ) {
	    alt *= SG_FEET_TO_METER;
	}
    } else {
	TgtAptId = tmp;
    }

    TgtAptDialog_Cancel( NULL );
    
    FGAirport a;
    FGFix f;
    double t1, t2;
    if ( fgFindAirportID( TgtAptId, &a ) ) {

	 SG_LOG( SG_GENERAL, SG_INFO,
		 "Adding waypoint (airport) = " << TgtAptId );
        
	 sprintf( NewTgtAirportId, "%s", TgtAptId.c_str() );

	 SGWayPoint wp( a.longitude, a.latitude, alt,
			SGWayPoint::WGS84, TgtAptId );
	 globals->get_route()->add_waypoint( wp );

         /* and turn on the autopilot */
         current_autopilot->set_HeadingEnabled( true );
         current_autopilot->set_HeadingMode( FGAutopilot::FG_HEADING_WAYPOINT );

    } else if ( current_fixlist->query( TgtAptId, 0.0, 0.0, 0.0,
					&f, &t1, &t2 ) )
    {
	 SG_LOG( SG_GENERAL, SG_INFO,
		 "Adding waypoint (fix) = " << TgtAptId );
        
	 sprintf( NewTgtAirportId, "%s", TgtAptId.c_str() );

	 SGWayPoint wp( f.get_lon(), f.get_lat(), alt,
			SGWayPoint::WGS84, TgtAptId );
	 globals->get_route()->add_waypoint( wp );

         /* and turn on the autopilot */
         current_autopilot->set_HeadingEnabled( true );
         current_autopilot->set_HeadingMode( FGAutopilot::FG_HEADING_WAYPOINT );
    } else {
	TgtAptId  += " not in database.";
	mkDialog(TgtAptId.c_str());
    }
}

void TgtAptDialog_Reset(puObject *)
{
    sprintf( NewTgtAirportId, "%s", fgGetString("/sim/startup/airport-id").c_str() );
    TgtAptDialogInput->setValue ( NewTgtAirportId );
    TgtAptDialogInput->setCursor( 0 ) ;
}

void TgtAptDialog_HandleSlider ( puObject * slider )
{
  float val ;
  slider -> getValue ( &val ) ;
  val = 1.0f - val ;

  int index = int ( TgtAptDialogWPList -> getNumItems () * val ) ;
  TgtAptDialogWPList -> setTopItem ( index ) ;
}

void TgtAptDialog_HandleArrow( puObject *arrow )
{
    int type = ((puArrowButton *)arrow)->getArrowType() ;
    int inc = ( type == PUARROW_DOWN     ) ?   1 :
            ( type == PUARROW_UP       ) ?  -1 :
            ( type == PUARROW_FASTDOWN ) ?  10 :
            ( type == PUARROW_FASTUP   ) ? -10 : 0 ;

    float val ;
    TgtAptDialogSlider -> getValue ( &val ) ;
    val = 1.0f - val ;
    int num_items = TgtAptDialogWPList->getNumItems () - 1 ;
    if ( num_items > 0 )
    {
      int index = int ( num_items * val + 0.5 ) + inc ;
      if ( index > num_items ) index = num_items ;
      if ( index < 0 ) index = 0 ;

      TgtAptDialogSlider -> setValue ( 1.0f - (float)index / num_items ) ;
      TgtAptDialogWPList -> setTopItem ( index ) ;
  }

}

void AddWayPoint(puObject *cb)
{
    sprintf( NewTgtAirportId, "%s", fgGetString("/sim/startup/airport-id").c_str() );
    TgtAptDialogInput->setValue( NewTgtAirportId );
    
    /* refresh waypoint list */
    char WPString[100];

    int i;
    if ( WPList != NULL ) {
        for (i = 0; i < WPListsize; i++ ) {
          delete WPList[i];
        }
        delete [] WPList[i];
    }
    if ( globals->get_route()->size() > 0 ) { 
        WPListsize = globals->get_route()->size();
        WPList = new char* [ WPListsize + 1 ];
        for (i = 0; i < globals->get_route()->size(); i++ ) {
           sprintf(WPString, "%5s %3.2flon %3.2flat", globals->get_route()->get_waypoint(i).get_id().c_str(), globals->get_route()->get_waypoint(i).get_target_lon(), globals->get_route()->get_waypoint(i).get_target_lat());
           WPList [i] = new char[ strlen(WPString) ];
           strcpy ( WPList [i], WPString );
        }
    } else {
        WPListsize = 1;
        WPList = new char* [ 2 ];
        WPList [0] = new char[18];
        strcpy ( WPList [0], "** List Empty **");
    }    
    WPList [ WPListsize ] = NULL;
    TgtAptDialogWPList->newList( WPList );

   // if non-empty list, adjust the size of the slider...
   TgtAptDialogSlider->setSliderFraction (0.9999f) ;
   TgtAptDialogSlider->hide();
   TgtAptDialogUPArrow->hide();
   TgtAptDialogDNArrow->hide();
   if (WPListsize > 10) {
      TgtAptDialogSlider->setSliderFraction (10.0f/(WPListsize-1)) ;
      TgtAptDialogSlider->reveal();
      TgtAptDialogUPArrow->reveal();
      TgtAptDialogDNArrow->reveal();
    }

    FG_PUSH_PUI_DIALOG( TgtAptDialog );
}

void PopWayPoint(puObject *cb)
{
    globals->get_route()->delete_first();

    // see if there are more waypoints on the list
    if ( globals->get_route()->size() ) {
	// more waypoints
	current_autopilot->set_HeadingMode( FGAutopilot::FG_HEADING_WAYPOINT );
    } else {
	// end of the line
	current_autopilot->set_HeadingMode( FGAutopilot::FG_TC_HEADING_LOCK );

	// use current heading
	current_autopilot
            ->set_TargetHeading(fgGetDouble("/orientation/heading-deg"));
    }
}

void ClearRoute(puObject *cb)
{
    globals->get_route()->clear();
}

void NewTgtAirportInit()
{
    SG_LOG( SG_AUTOPILOT, SG_INFO, " enter NewTgtAirportInit()" );
    sprintf( NewTgtAirportId, "%s",
             fgGetString("/sim/startup/airport-id").c_str() );
    SG_LOG( SG_AUTOPILOT, SG_INFO, " NewTgtAirportId " << NewTgtAirportId );
    int len = 150
        - puGetDefaultLabelFont().getStringWidth( NewTgtAirportLabel ) / 2;
    
    TgtAptDialog = new puDialogBox (150, 350);
    {
        TgtAptDialogFrame   = new puFrame           (0,0,350, 350);
        
        TgtAptDialogWPList = new puListBox ( 50, 130, 300, 320 ) ;
        TgtAptDialogWPList -> setLabel ( "Flight Plan" );
        TgtAptDialogWPList -> setLabelPlace ( PUPLACE_ABOVE ) ;
        TgtAptDialogWPList -> setStyle ( -PUSTYLE_SMALL_SHADED ) ;
        TgtAptDialogWPList -> setValue ( 0 ) ;

        TgtAptDialogSlider = new puSlider (300, 150, 150 ,TRUE,20);
        TgtAptDialogSlider->setValue(1.0f);
        TgtAptDialogSlider->setSliderFraction (0.2f) ;
        TgtAptDialogSlider->setDelta(0.1f);
        TgtAptDialogSlider->setCBMode( PUSLIDER_DELTA );
        TgtAptDialogSlider->setCallback( TgtAptDialog_HandleSlider );

        TgtAptDialogUPArrow = new puArrowButton ( 300, 300, 320, 320, PUARROW_UP ) ;
        TgtAptDialogUPArrow->setCallback ( TgtAptDialog_HandleArrow ) ;

        TgtAptDialogDNArrow = new puArrowButton ( 300, 130, 320, 150, PUARROW_DOWN ) ;
        TgtAptDialogDNArrow->setCallback ( TgtAptDialog_HandleArrow ) ;


        TgtAptDialogInput   = new puInput           (50, 70, 300, 100);
        TgtAptDialogInput -> setLabel ( NewTgtAirportLabel );
        TgtAptDialogInput -> setLabelPlace ( PUPLACE_ABOVE ) ;
        TgtAptDialogInput   ->    setValue          (NewTgtAirportId);
        TgtAptDialogInput   ->    acceptInput();
        
        TgtAptDialogOkButton     =  new puOneShot   (50, 10, 110, 50);
        TgtAptDialogOkButton     ->     setLegend   (gui_msg_OK);
        TgtAptDialogOkButton     ->     setCallback (TgtAptDialog_OK);
        TgtAptDialogOkButton     ->     makeReturnDefault(TRUE);
        
        TgtAptDialogCancelButton =  new puOneShot   (140, 10, 210, 50);
        TgtAptDialogCancelButton ->     setLegend   (gui_msg_CANCEL);
        TgtAptDialogCancelButton ->     setCallback (TgtAptDialog_Cancel);
        
        TgtAptDialogResetButton  =  new puOneShot   (240, 10, 300, 50);
        TgtAptDialogResetButton  ->     setLegend   (gui_msg_RESET);
        TgtAptDialogResetButton  ->     setCallback (TgtAptDialog_Reset);

    }

    FG_FINALIZE_PUI_DIALOG( TgtAptDialog );
    printf("leave NewTgtAirportInit()");
}



