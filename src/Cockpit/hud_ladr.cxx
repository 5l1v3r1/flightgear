
#include "hud.hxx"
#include "panel.hxx"

#define DO_PANEL_HACK

//====================== Top of HudLadder Class =======================
HudLadder ::   HudLadder(  string name,
			   int       x,
			   int       y,
			   UINT      width,
			   UINT      height,
			   float	 factr,
			   FLTFNPTR  ptch_source,
			   FLTFNPTR  roll_source,
			   float     span_units,
			   float     major_div,
			   float     minor_div,
			   UINT      screen_hole,
			   UINT      lbl_pos,
			   bool      frl_spot,
			   bool		 target,
			   bool		 vel_vec,
			   bool		 drift,
			   bool		 alpha,
			   bool      energy,
			   bool      climb,
			   bool      glide,
			   float     glide_slope_val,
			   bool      worm_energy,
			   bool      waypoint,
			   bool      working) :
    dual_instr_item( x, y, width, height,
		     ptch_source,
		     roll_source,
		     working,
		     HUDS_RIGHT),
    width_units			( (int)(span_units)   ),
    div_units			( (int)(major_div < 0? -major_div: major_div) ),
    minor_div			( (int)(minor_div)    ),
    label_pos			( lbl_pos      ),
    scr_hole			( screen_hole  ),
    vmax				( span_units/2 ),
    vmin				( -vmax        ),
    factor				( factr		  ),
    hudladder_type		( name		  ),
    frl					( frl_spot		),
    velocity_vector		( vel_vec		),
    drift_marker		( drift			),
    alpha_bracket		( alpha			),
    energy_marker		( energy		),
    climb_dive_marker	( climb		),
    target_spot			( target		),
    glide_slope_marker	( glide			),
    glide_slope			( glide_slope_val),
    energy_worm			( worm_energy),
    waypoint_marker		( waypoint)


{
    if( !width_units ) {
	width_units = 45;
    }
}
   
HudLadder ::  ~HudLadder()
{
}
           
HudLadder ::
HudLadder( const HudLadder & image ) :
    dual_instr_item		( (dual_instr_item &) image),
    width_units			( image.width_units   ),
    div_units			( image.div_units     ),
    label_pos			( image.label_pos     ),
    scr_hole			( image.scr_hole      ),
    vmax				( image.vmax ),
    vmin				( image.vmin ),
    factor				( image.factor        ),
    hudladder_type		( image.hudladder_type),
    frl					( image.frl),
    velocity_vector		( image.velocity_vector),
    drift_marker		( image.drift_marker),
    alpha_bracket		( image.alpha_bracket),
    energy_marker		( image.energy_marker),
    climb_dive_marker	( image.climb_dive_marker),
    target_spot			( image.target_spot),
    glide_slope_marker	( image.glide_slope_marker),
    glide_slope			( image.glide_slope),
    energy_worm			( image.energy_worm),
    waypoint_marker		( image.waypoint_marker)
{
}
HudLadder & HudLadder ::  operator = ( const HudLadder & rhs )
{
    if( !(this == &rhs)) {
	(dual_instr_item &)(*this) = (dual_instr_item &)rhs;
	width_units			= rhs.width_units;
	div_units			= rhs.div_units;
	label_pos			= rhs.label_pos;
	scr_hole			= rhs.scr_hole;
	vmax				= rhs.vmax;
	vmin				= rhs.vmin;
	factor				= rhs.factor;
	hudladder_type		= rhs.hudladder_type;
	frl					= rhs.frl;
	velocity_vector		= rhs.velocity_vector;
	drift_marker		= rhs.drift_marker;
	alpha_bracket		= rhs.alpha_bracket;
	energy_marker		= rhs.energy_marker;
	climb_dive_marker	= rhs.climb_dive_marker;
	target_spot			= rhs.target_spot;
	glide_slope_marker	= rhs.glide_slope_marker;
	glide_slope			= rhs.glide_slope;
	energy_worm			= rhs.energy_worm;
	waypoint_marker		= rhs.waypoint_marker;
    }
    return *this;
}
                           
//
//  Draws a climb ladder in the center of the HUD
//

void HudLadder :: draw( void )
{

    float  x_ini,x_ini2;
    float  x_end,x_end2;
    float  y;
    int count;
    float cosine, sine,xvvr,yvvr,Vxx,Vyy,Vzz,up_vel,ground_vel,actslope;
    float Axx,Ayy,Azz,total_vel,pot_slope,t1,t2,psi,alpha,pla;
    float vel_x,vel_y,drift;
    char     Textaux[8] ;
    bool  pitch_ladder;
    bool  climb_dive_ladder;
    bool  clip_plane;

    GLdouble eqn_top[4] = {0.0,-1.0,0.0,0.0};
    GLdouble eqn_left[4] = {-1.0,0.0,0.0,100.0};
    GLdouble eqn_right[4] = {1.0,0.0,0.0,100.0};

    POINT  centroid    = get_centroid();
    RECT   box         = get_location();

    float   half_span  = box.right / 2.0;
    float   roll_value = current_ch2();
    alpha = get_aoa();
    pla = get_throttleval();

    int lgear,wown,wowm,ilcanclaw,ihook;
    ilcanclaw = get_iaux1();
    lgear = get_iaux2();
    wown = get_iaux3();
    wowm = get_iaux4();
    ihook = get_iaux5();
    
    float pitch_value = current_ch1() * SGD_RADIANS_TO_DEGREES;
	
    if(hudladder_type=="Climb/Dive Ladder") {
	pitch_ladder = false;
	climb_dive_ladder = true;
	clip_plane = true;
    }
    else
	if(hudladder_type=="Pitch Ladder") {
	    pitch_ladder = true;
	    climb_dive_ladder = false;
	    clip_plane = false;
	}
	
    //**************************************************************
    glPushMatrix();
    // define (0,0) as center of screen
    glTranslatef( centroid.x, centroid.y, 0);

    // OBJECT STATIC RETICLE
    // TYPE FRL
    // ATTRIB - ALWAYS
    // Draw the FRL spot and line
    if(frl)	{
#define FRL_DIAMOND_SIZE 2.0
	glBegin(GL_LINE_LOOP);
	glVertex2f( -FRL_DIAMOND_SIZE, 0.0);
	glVertex2f(0.0, FRL_DIAMOND_SIZE);
	glVertex2f( FRL_DIAMOND_SIZE, 0.0);
	glVertex2f(0.0, -FRL_DIAMOND_SIZE);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, FRL_DIAMOND_SIZE);
	glVertex2f(0, 8.0 );
	glEnd();
#undef FRL_DIAMOND_SIZE
    }
    // TYPE WATERLINE_MARK (W shaped _    _ )
    //		  			              \/\/

    //****************************************************************    
    // TYPE TARGET_SPOT
    // Draw the target spot.
    if (target_spot)	{
#define CENTER_DIAMOND_SIZE 6.0
	glBegin(GL_LINE_LOOP);
	glVertex2f( -CENTER_DIAMOND_SIZE, 0.0);
	glVertex2f(0.0, CENTER_DIAMOND_SIZE);
	glVertex2f( CENTER_DIAMOND_SIZE, 0.0);
	glVertex2f(0.0, -CENTER_DIAMOND_SIZE);
	glEnd();
#undef CENTER_DIAMOND_SIZE
    }

    //****************************************************************    
    //velocity vector reticle - computations
    if(velocity_vector)	{
	Vxx = get_Vx();
	Vyy = get_Vy();
	Vzz = get_Vz();
	Axx = get_Ax();
	Ayy = get_Ay();
	Azz = get_Az();
	psi = get_heading();

	if (psi > 180.0) psi = psi - 360;

	total_vel = sqrt(Vxx*Vxx + Vyy*Vyy + Vzz*Vzz);
	ground_vel = sqrt(Vxx*Vxx + Vyy*Vyy);
	up_vel = Vzz;

	if (ground_vel < 2.0) {
	    if (fabs(up_vel) < 2.0) {
		actslope = 0.0;
	    } else {
		actslope = (up_vel/fabs(up_vel))*90.0;
	    }
	} else {
	    actslope = atan(up_vel/ground_vel)*SGD_RADIANS_TO_DEGREES;
	}

	xvvr = (((atan2(Vyy,Vxx)*SGD_RADIANS_TO_DEGREES)-psi)*(640.0/45.0));
	drift = ((atan2(Vyy,Vxx)*SGD_RADIANS_TO_DEGREES)-psi);
	yvvr = ((actslope - pitch_value)*factor);
	vel_y = ((actslope -pitch_value) * cos(roll_value) + drift*sin(roll_value))*factor;
	vel_x = (-(actslope -pitch_value)*sin(roll_value) + drift*cos(roll_value))*(640/45.0);
	//  printf("%f %f %f %f\n",vel_x,vel_y,drift,psi);
	//****************************************************************    
	// OBJECT MOVING RETICLE
	// TYPE - DRIFT MARKER
	// ATTRIB - ALWAYS
	// drift marker
	if(drift_marker)	{
	    glBegin(GL_LINE_STRIP);
	    glVertex2f((xvvr*25/120)-6, -4);
	    glVertex2f(xvvr*25/120, 8);
	    glVertex2f((xvvr*25/120)+6, -4);
	    glEnd();
	}

	//****************************************************************    
	// Clipping coordinates for ladder to be input from xml file
	// Clip hud ladder
	if (clip_plane)	{
	    glClipPlane(GL_CLIP_PLANE0,eqn_top);
	    glEnable(GL_CLIP_PLANE0);
	    glClipPlane(GL_CLIP_PLANE1,eqn_left);
	    glEnable(GL_CLIP_PLANE1);
	    glClipPlane(GL_CLIP_PLANE2,eqn_right);
	    glEnable(GL_CLIP_PLANE2);
	    //      glScissor(-100,-240,200,240);
	    //      glEnable(GL_SCISSOR_TEST);
	}
	//****************************************************************    
	// OBJECT MOVING RETICLE
	// TYPE VELOCITY VECTOR
	// ATTRIB - ALWAYS
	//  velocity vector
	glBegin(GL_LINE_LOOP);  // Use polygon to approximate a circle 
        for(count=0; count<50; count++) {             
	    cosine = 6 * cos(count * 2 * SGD_PI/50.0); 
            sine =   6 * sin(count * 2 * SGD_PI/50.0); 
            glVertex2f(cosine+vel_x, sine+vel_y);
	}     
	glEnd(); 
	//velocity vector reticle orientation lines
	glBegin(GL_LINE_STRIP);
	glVertex2f(vel_x-12, vel_y);
	glVertex2f(vel_x-6, vel_y);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(vel_x+12, vel_y);
	glVertex2f(vel_x+6, vel_y);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(vel_x, vel_y+12);
	glVertex2f(vel_x, vel_y+6);
	glEnd();

	// OBJECT MOVING RETICLE
	// TYPE LINE
	// ATTRIB - ON CONDITION
	if (lgear == 1) {
	    // undercarriage status
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x+8, vel_y);
	    glVertex2f(vel_x+8, vel_y-4);
	    glEnd();
	    // OBJECT MOVING RETICLE
	    // TYPE LINE
	    // ATTRIB - ON CONDITION
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x-8, vel_y);
	    glVertex2f(vel_x-8, vel_y-4);
	    glEnd();
	    // OBJECT MOVING RETICLE
	    // TYPE LINE
	    // ATTRIB - ON CONDITION
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x, vel_y-6);
	    glVertex2f(vel_x, vel_y-10);
	    glEnd();
	}

	// OBJECT MOVING RETICLE
	// TYPE V
	// ATTRIB - ON CONDITION
	if (ihook == 1) {
	    // arrestor hook status
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x-4, vel_y-8);
	    glVertex2f(vel_x, vel_y-10);
	    glVertex2f(vel_x+4, vel_y-8);
	    glEnd();
	}
    }//if velocity_vector

    //***************************************************************
    // OBJECT MOVING RETICLE
    // TYPE - SQUARE_BRACKET
    // ATTRIB - ON CONDITION
    // alpha bracket
    if (alpha_bracket)	{
	if (ihook == 1) {
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x-20 , vel_y-(16-alpha)*factor);
	    glVertex2f(vel_x-17, vel_y-(16-alpha)*factor);
	    glVertex2f(vel_x-17, vel_y-(14-alpha)*factor);
	    glVertex2f(vel_x-20, vel_y-(14-alpha)*factor);
	    glEnd();
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x+20 , vel_y-(16-alpha)*factor);
	    glVertex2f(vel_x+17, vel_y-(16-alpha)*factor);
	    glVertex2f(vel_x+17, vel_y-(14-alpha)*factor);
	    glVertex2f(vel_x+20, vel_y-(14-alpha)*factor);
	    glEnd();
	}
    }
    //printf("xvr=%f,yvr=%f,Vx=%f,Vy=%f,Vz=%f\n",xvvr,yvvr,Vx,Vy,Vz);
    //printf("Ax=%f,Ay=%f,Az=%f\n",Ax,Ay,Az);
    //****************************************************************	
    // OBJECT MOVING RETICLE
    // TYPE ENERGY_MARKERS
    // ATTRIB - ALWAYS
    //energy markers - compute potential slope
    if(energy_marker)	{
	if (total_vel < 5.0) {
	    t1 = 0;
	    t2 = 0;
	} else {
	    t1 = up_vel/total_vel;
	    t2 = asin((Vxx*Axx + Vyy*Ayy + Vzz*Azz)/(9.81*total_vel));
	}
	pot_slope = ((t2/3)*SGD_RADIANS_TO_DEGREES)*factor + vel_y;
	//    if (pot_slope < (vel_y - 45)) pot_slope = vel_y-45;
	//    if (pot_slope > (vel_y + 45)) pot_slope = vel_y+45;

	//energy markers
	glBegin(GL_LINE_STRIP);
	glVertex2f(vel_x-20, pot_slope-5);
	glVertex2f(vel_x-15, pot_slope);
	glVertex2f(vel_x-20, pot_slope+5);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(vel_x+20, pot_slope-5);
	glVertex2f(vel_x+15, pot_slope);
	glVertex2f(vel_x+20, pot_slope+5);
	glEnd();
	if (pla > (105.0/131.0)) {
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x-24, pot_slope-5);
	    glVertex2f(vel_x-19, pot_slope);
	    glVertex2f(vel_x-24, pot_slope+5);
	    glEnd();
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(vel_x+24, pot_slope-5);
	    glVertex2f(vel_x+19, pot_slope);
	    glVertex2f(vel_x+24, pot_slope+5);
	    glEnd();
	}
    }
    //********************************************************** 
    // ramp reticle
    // OBJECT STATIC RETICLE
    // TYPE LINE
    // ATTRIB - ON CONDITION
    if (energy_worm)	{
	if (ilcanclaw == 1) {
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(-15, -134);
	    glVertex2f(15, -134);
	    glEnd();
	    // OBJECT MOVING RETICLE
	    // TYPE BOX
	    // ATTRIB - ON CONDITION
	    glBegin(GL_LINE_STRIP);
	    glVertex2f(-6, -134);
	    glVertex2f(-6, t2*SGD_RADIANS_TO_DEGREES*4.0 - 134);
	    glVertex2f(+6, t2*SGD_RADIANS_TO_DEGREES*4.0 - 134);
	    glVertex2f(6, -134);
	    glEnd();
	    // OBJECT MOVING RETICLE
	    // TYPE DIAMOND
	    // ATTRIB - ON CONDITION
	    glBegin(GL_LINE_LOOP);
	    glVertex2f(-6, actslope*4.0 - 134);
	    glVertex2f(0, actslope*4.0 -134 +3);
	    glVertex2f(6, actslope*4.0 - 134);
	    glVertex2f(0, actslope*4.0 -134 -3);
	    glEnd();
	}
    }
    //*************************************************************
    // OBJECT MOVING RETICLE
    // TYPE DIAMOND
    // ATTRIB - ALWAYS
    // Draw the locked velocity vector.
    if(climb_dive_marker)	{
	glBegin(GL_LINE_LOOP);
        glVertex2f( -3.0, 0.0+vel_y);
        glVertex2f(0.0, 6.0+vel_y);
        glVertex2f( 3.0, 0.0+vel_y);
        glVertex2f(0.0, -6.0+vel_y);
	glEnd();
    }

    //****************************************************************    

    if(climb_dive_ladder) {// CONFORMAL_HUD

	vmin              = pitch_value - (float)width_units;
	vmax              = pitch_value + (float)width_units; 

	glTranslatef( vel_x, vel_y, 0);

    }
    else 
	if (pitch_ladder) {//Default Hud

	    vmin              = pitch_value - (float)width_units * 0.5f;
	    vmax              = pitch_value + (float)width_units * 0.5f;

	}

    glRotatef(roll_value * SGD_RADIANS_TO_DEGREES, 0.0, 0.0, 1.0);
    // FRL marker not rotated - this line shifted below

    if( div_units ) {
  
        char     TextLadder[8] ;
        float    label_length ;
        float    label_height ;
        float    left ;
        float    right ;
        float    bot ;
        float    top ;
        float    text_offset = 4.0f ;
	float    zero_offset;
		
	if(climb_dive_ladder)
	    zero_offset = 50.0f ;
	else
	    if(pitch_ladder)
		zero_offset = 10.0f ;
		
	fntFont *font      = HUDtext->getFont();
	float    pointsize = HUDtext->getPointSize();
	float    italic    = HUDtext->getSlant();

        TextList.setFont( HUDtext );
        TextList.erase();
        LineList.erase();
        StippleLineList.erase();

        int last = FloatToInt(vmax)+1;
        int i    = FloatToInt(vmin);

        if( !scr_hole ) {
	    x_end =  half_span;
            for( ; i<last ; i++ ) {
                
                y =  (((float)(i - pitch_value) * factor) + .5f);
                if( !(i % div_units ))    {        //  At integral multiple of div
                
                    sprintf( TextLadder, "%d", i );
                    font->getBBox ( TextLadder, pointsize, italic,
                                    &left, &right, &bot, &top ) ;
                    label_length  = right - left;
                    label_length += text_offset;
                    label_height  = (top - bot)/2.0f;
                
                    x_ini = -half_span;
                    
                    if( i >= 0 ) {
                        // Make zero point wider on left
                        if( i == 0 )
                            x_ini -= zero_offset;
                        // Zero or above draw solid lines
                        Line(x_ini, y, x_end, y);
                    } else {
                        // Below zero draw dashed lines.
                        StippleLine(x_ini, y, x_end, y);
                    }
                    
                    // Calculate the position of the left text and write it.
                    Text( x_ini-label_length, y-label_height, TextLadder );
                    Text( x_end+text_offset,  y-label_height, TextLadder );
                }
            }
        }
        else // if(scr_hole )
	    {    // Draw ladder with space in the middle of the lines
		float hole = (float)((scr_hole)/2.0f);

		x_end = -half_span + hole;
		x_ini2= half_span  - hole;
		for( ; i<last ; i++ )      {

		    if(hudladder_type=="Pitch Ladder")
			y = (((float)(i - pitch_value) * factor) + .5);
		    else
			if(hudladder_type=="Climb/Dive Ladder")
			    y = (((float)(i - actslope) * factor) + .5);

		    if( !(i % div_units ))    {        //  At integral multiple of div

			sprintf( TextLadder, "%d", i );
			font->getBBox ( TextLadder, pointsize, italic,
					&left, &right, &bot, &top ) ;
			label_length  = right - left;
			label_length += text_offset;
			label_height  = (top - bot)/2.0f;
			//                  printf("l %f r %f b %f t %f\n",left, right, bot, top );
                
			// Start by calculating the points and drawing the
			// left side lines.
			x_ini = -half_span;
			x_end2= half_span;
                    
			if( i >= 0 ) { 
			    // Make zero point wider on left
			    if( i == 0 ) {
				x_ini -= zero_offset;
				x_end2 +=zero_offset;
			    } else {
				if(climb_dive_ladder){
				    // Zero or above draw solid lines
				    Line(x_end, y-5.0, x_end, y);
				    Line(x_ini2, y-5.0, x_ini2, y);
				}
			    }

			    Line(x_ini, y, x_end, y);
			    Line(x_ini2, y, x_end2, y);

			} else {
			    // Below zero draw dashed lines.
			    if(climb_dive_ladder) {
				Line(x_end, y+5.0, x_end, y);
				Line(x_ini2, y+5.0, x_ini2, y);
			    }
			    StippleLine(x_ini, y, x_end, y);
			    StippleLine(x_ini2, y, x_end2, y);
			}
                    
			// Now calculate the location of the left side label using
			Text( x_ini-label_length, y-label_height, TextLadder );
			Text (x_end2+text_offset, y-label_height, TextLadder );

		    }
		}

		// OBJECT LADDER MARK
		// TYPE LINE
		// ATTRIB - ON CONDITION
		// draw appraoch glide slope marker
		if (glide_slope_marker)	{
		    if (ihook) {
			Line(-half_span+15, (glide_slope-actslope)*factor, -half_span + hole, (glide_slope-actslope)*factor);
			Line(half_span-15, (glide_slope-actslope)*factor, half_span - hole, (glide_slope-actslope)*factor);
		    }
		}// if glide_slope_marker
	    }
        TextList.draw();

        glLineWidth(0.2);
        
        LineList.draw();
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple( 1, 0x00FF );
        StippleLineList.draw( );
        glDisable(GL_LINE_STIPPLE);
    }
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    //      glDisable(GL_SCISSOR_TEST);
    glPopMatrix();
    //*************************************************************
    //*************************************************************
    if(waypoint_marker) {
	//waypoint marker computation
	float fromwp_lat,towp_lat,fromwp_lon,towp_lon,dist,delx,dely,hyp,theta,brg;

	fromwp_lon = get_longitude()*SGD_DEGREES_TO_RADIANS;
	fromwp_lat = get_latitude()*SGD_DEGREES_TO_RADIANS;
	towp_lon = get_aux5()*SGD_DEGREES_TO_RADIANS;
	towp_lat = get_aux6()*SGD_DEGREES_TO_RADIANS;

	dist = acos(sin(fromwp_lat)*sin(towp_lat)+cos(fromwp_lat)*cos(towp_lat)*cos(fabs(fromwp_lon-towp_lon)));
	delx= towp_lat - fromwp_lat;
	dely = towp_lon - fromwp_lon;
	hyp = sqrt(pow(delx,2)+pow(dely,2));
	if (hyp != 0) {
	    theta = asin(dely/hyp);
	} else {
	    theta = 0.0;
	}
	brg = theta*SGD_RADIANS_TO_DEGREES;
	if (brg > 360.0) brg = 0.0;
	if (delx < 0) brg = 180 - brg;

	//        {Brg  = asin(cos(towp_lat)*sin(fabs(fromwp_lon-towp_lon))/ sin(dist));
	//        Brg = Brg * SGD_RADIANS_TO_DEGREES; }
	dist = dist*SGD_RADIANS_TO_DEGREES * 60.0*1852.0; //rad->deg->nm->m
	// end waypoint marker computation
	//*********************************************************
	// OBJECT MOVING RETICLE
	// TYPE ARROW
	// waypoint marker
	if (fabs(brg-psi) > 10.0) {
	    glPushMatrix();
	    glTranslatef( centroid.x, centroid.y, 0);
	    glTranslatef( vel_x, vel_y, 0);
	    glRotatef(brg - psi,0.0,0.0,-1.0);
	    glBegin(GL_LINE_LOOP);
	    glVertex2f(-2.5,20.0);
	    glVertex2f(-2.5,30.0);
	    glVertex2f(-5.0,30.0);
	    glVertex2f(0.0,35.0);
	    glVertex2f(5.0,30.0);
	    glVertex2f(2.5,30.0);
	    glVertex2f(2.5,20.0);
	    glEnd();
	    glPopMatrix();
	}
	// waypoint marker on heading scale
	if (fabs(brg-psi) < 12.0) {
	    glBegin(GL_LINE_LOOP);
	    glVertex2f(((brg-psi)*60/25)+320,240.0);
	    glVertex2f(((brg-psi)*60/25)+326,240.0-4);
	    glVertex2f(((brg-psi)*60/25)+323,240.0-4);
	    glVertex2f(((brg-psi)*60/25)+323,240.0-8);
	    glVertex2f(((brg-psi)*60/25)+317,240.0-8);
	    glVertex2f(((brg-psi)*60/25)+317,240.0-4);
	    glVertex2f(((brg-psi)*60/25)+314,240.0-4);
	    glEnd();
	}
	//*************************************************************
    }// if waypoint_marker
}//draw
