#include <simgear/misc/sg_path.hxx>

#include "fixlist.hxx"
#include "ilslist.hxx"
#include "navlist.hxx"
#include "mkrbeacons.hxx"

// change this!
const string FG_DATA_DIR("/usr/local/lib/FlightGear");

int main() {
    double heading, dist;

    current_navlist = new FGNavList;
    SGPath p_nav( FG_DATA_DIR + "/Navaids/default.nav" );

    current_navlist->init( p_nav );
	
    FGNav *n;
    if ( (n = current_navlist->findByFreq( -93.2 * SG_DEGREES_TO_RADIANS,
                                           45.14 * SG_DEGREES_TO_RADIANS,
                                           3000, 117.30)) != NULL )
    {
	cout << "Found a vor station in range" << endl;
	cout << " id = " << n->get_ident() << endl;
    } else {
	cout << "not picking up vor. :-(" << endl;
    }

    FGNav *dcs;
    if ( (dcs = current_navlist->findByIdent( "DCS",
                                              -3.3 * SG_DEGREES_TO_RADIANS,
                                              55.9 * SG_DEGREES_TO_RADIANS))
         != NULL ) {
						
        cout << "Found DCS by ident" << endl;
        if (dcs->get_freq() != 11520)
            cout << "Frequency for DCS VOR is wrong (should be 115.20), it's " 
                 << dcs->get_freq() << endl;
    } else {
        cout << "couldn't locate DCS (Dean-Cross) VOR" << endl;
    }
	
    // we have to init the marker beacon storage before we parse the ILS file
    current_beacons = new FGMarkerBeacons;
    current_beacons->init();
	
    current_ilslist = new FGILSList;
    SGPath p_ils( FG_DATA_DIR + "/Navaids/default.ils" );
    current_ilslist->init( p_ils );
    FGILS i;
    if ( current_ilslist->query( -93.1 * SG_DEGREES_TO_RADIANS,
                                 45.24 * SG_DEGREES_TO_RADIANS,
                                 3000, 110.30, &i) )
    {
	cout << "Found an ils station in range" << endl;
	cout << " apt = " << i.get_aptcode() << endl;
	cout << " rwy = " << i.get_rwyno() << endl;
    } else {
	cout << "not picking up ils. :-(" << endl;
    }

    current_fixlist = new FGFixList;
    SGPath p_fix( FG_DATA_DIR + "/Navaids/default.fix" );
    current_fixlist->init( p_fix );
    FGFix fix;
	
    // attempting to get the position relative to the OTR VOR; heading
    // should be 108 degrees, distance 74nm (according to my SimCharts
    // v1.5)
    if ( current_fixlist->query_and_offset( "DOGGA",
                                            -0.103 * SG_DEGREES_TO_RADIANS,
                                            53.698 * SG_DEGREES_TO_RADIANS,
                                            3000, &fix, &heading, &dist) )
    {
	cout << "Found a matching fix" << endl;
	cout << " id = " << fix.get_ident() << endl;
	cout << " heading = " << heading << " dist = " << dist * SG_METER_TO_NM
             << endl;
    } else {
	cout << "did not find fix. :-(" << endl;
    }
}
