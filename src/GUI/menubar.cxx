#include <string.h>
#include <iostream>
#include <plib/pu.h>
#include <simgear/debug/logstream.hxx>

#include <Main/globals.hxx>
#include <Main/fg_props.hxx>

#include <Input/input.hxx>

#include "new_gui.hxx"
#include "menubar.hxx"



////////////////////////////////////////////////////////////////////////
// FIXME!!
//
// Deprecated wrappers for old menu commands.
//
// DO NOT ADD TO THESE.  THEY WILL BE DELETED SOON!
//
// These are defined in gui_funcs.cxx.  They should be replaced with
// user-configured dialogs and new commands where necessary.
////////////////////////////////////////////////////////////////////////

extern void saveFlight (puObject *);
static bool
do_save_dialog (const SGPropertyNode * arg)
{
    saveFlight(0);
    return true;
}

extern void loadFlight (puObject *);
static bool
do_load_dialog (const SGPropertyNode * arg)
{
    loadFlight(0);
    return true;
}

extern void reInit (puObject *);
static bool
do_reinit_dialog (const SGPropertyNode * arg)
{
    reInit(0);
    return true;
}

#if defined(TR_HIRES_SNAP)
extern void dumpHiResSnapShot (puObject *);
static bool
do_hires_snapshot_dialog (const SGPropertyNode * arg)
{
    dumpHiResSnapShot(0);
    return true;
}
#endif // TR_HIRES_SNAP

extern void dumpSnapShot (puObject *);
static bool
do_snapshot_dialog (const SGPropertyNode * arg)
{
    dumpSnapShot(0);
    return true;
}


#if defined( WIN32 ) && !defined( __CYGWIN__) && !defined(__MINGW32__)
extern void printScreen (puObject *);
static bool
do_print_dialog (const SGPropertyNode * arg)
{
    printScreen(0);
    return true;
}
#endif

extern void PilotOffsetAdjust (puObject *);
static bool
do_pilot_offset_dialog (const SGPropertyNode * arg)
{
    PilotOffsetAdjust(0);
    return true;
}

extern void fgHUDalphaAdjust (puObject *);
static bool
do_hud_alpha_dialog (const SGPropertyNode * arg)
{
    fgHUDalphaAdjust(0);
    return true;
}

extern void prop_pickerView (puObject *);
static bool
do_properties_dialog (const SGPropertyNode * arg)
{
    prop_pickerView(0);
    return true;
}

extern void fgPresetAirport (puObject *);
static bool
do_preset_airport_dialog (const SGPropertyNode * arg)
{
    fgPresetAirport(0);
    return true;
}

extern void fgPresetRunway (puObject *);
static bool
do_preset_runway_dialog (const SGPropertyNode * arg)
{
    fgPresetRunway(0);
    return true;
}

extern void fgPresetOffsetDistance (puObject *);
static bool
do_preset_offset_distance_dialog (const SGPropertyNode * arg)
{
    fgPresetOffsetDistance(0);
    return true;
}

extern void fgPresetAltitude (puObject *);
static bool
do_preset_altitude_dialog (const SGPropertyNode * arg)
{
    fgPresetAltitude(0);
    return true;
}

extern void fgPresetGlideslope (puObject *);
static bool
do_preset_glideslope_dialog (const SGPropertyNode * arg)
{
    fgPresetGlideslope(0);
    return true;
}

extern void fgPresetAirspeed (puObject *);
static bool
do_preset_airspeed_dialog (const SGPropertyNode * arg)
{
    fgPresetAirspeed(0);
    return true;
}

extern void fgPresetCommit (puObject *);
static bool
do_preset_commit_dialog (const SGPropertyNode * arg)
{
    fgPresetCommit(0);
    return true;
}

extern void AddWayPoint (puObject *);
static bool
do_ap_add_waypoint_dialog (const SGPropertyNode * arg)
{
    AddWayPoint(0);
    return true;
}

extern void PopWayPoint (puObject *);
static bool
do_ap_pop_waypoint_dialog (const SGPropertyNode * arg)
{
    PopWayPoint(0);
    return true;
}

extern void ClearRoute (puObject *);
static bool
do_ap_clear_route_dialog (const SGPropertyNode * arg)
{
    ClearRoute(0);
    return true;
}

extern void fgAPAdjust (puObject *);
static bool
do_ap_adjust_dialog (const SGPropertyNode * arg)
{
    fgAPAdjust(0);
    return true;
}

extern void fgLatLonFormatToggle (puObject *);
static bool
do_lat_lon_format_dialog (const SGPropertyNode * arg)
{
    fgLatLonFormatToggle(0);
    return true;
}

extern void helpCb (puObject *);
static bool
do_help_dialog (const SGPropertyNode * arg)
{
    helpCb(0);
    return true;
}

static struct {
    const char * name;
    SGCommandMgr::command_t command;
} deprecated_dialogs [] = {
    { "old-save-dialog", do_save_dialog },
    { "old-load-dialog", do_load_dialog },
    { "old-reinit_dialog", do_reinit_dialog },
#if defined(TR_HIRES_SNAP)
    { "old-hires-snapshot-dialog", do_hires_snapshot_dialog },
#endif
    { "old-snapshot-dialog", do_snapshot_dialog },
#if defined( WIN32 ) && !defined( __CYGWIN__) && !defined(__MINGW32__)
    { "old-print-dialog", do_print_dialog },
#endif
    { "old-pilot-offset-dialog", do_pilot_offset_dialog },
    { "old-hud-alpha-dialog", do_hud_alpha_dialog },
    { "old-properties-dialog", do_properties_dialog },
    { "old-preset-airport-dialog", do_preset_airport_dialog },
    { "old-preset-runway-dialog", do_preset_runway_dialog },
    { "old-preset-offset-distance-dialog", do_preset_offset_distance_dialog },
    { "old-preset-altitude-dialog", do_preset_altitude_dialog },
    { "old-preset-glideslope-dialog", do_preset_glideslope_dialog },
    { "old-preset-airspeed-dialog", do_preset_airspeed_dialog },
    { "old-preset-commit-dialog", do_preset_commit_dialog },
    { "old-ap-add-waypoint-dialog", do_ap_add_waypoint_dialog },
    { "old-ap-pop-waypoint-dialog", do_ap_pop_waypoint_dialog },
    { "old-ap-clear-route-dialog", do_ap_clear_route_dialog },
    { "old-ap-adjust-dialog", do_ap_adjust_dialog },
    { "old-lat-lon-format-dialog", do_lat_lon_format_dialog },
    { "old-help-dialog", do_help_dialog },
    { 0, 0 }
};

static void
add_deprecated_dialogs ()
{
  SG_LOG(SG_GENERAL, SG_INFO, "Initializing old dialog commands:");
  for (int i = 0; deprecated_dialogs[i].name != 0; i++) {
    SG_LOG(SG_GENERAL, SG_INFO, "  " << deprecated_dialogs[i].name);
    globals->get_commands()->addCommand(deprecated_dialogs[i].name,
					deprecated_dialogs[i].command);
  }
}



////////////////////////////////////////////////////////////////////////
// Static functions.
////////////////////////////////////////////////////////////////////////


static void
menu_callback (puObject * object)
{
    NewGUI * gui = (NewGUI *)globals->get_subsystem("gui");
    gui->getMenuBar()->fireItem(object);
}



////////////////////////////////////////////////////////////////////////
// Implementation of FGMenuBar.
////////////////////////////////////////////////////////////////////////


FGMenuBar::FGMenuBar ()
    : _visible(false),
      _menuBar(0)
{
}

FGMenuBar::~FGMenuBar ()
{
    hide();
    puDeleteObject(_menuBar);

    int i;

                                // Delete all the character arrays
                                // we were forced to keep around for
                                // plib.
    for (i = 0; i < _char_arrays.size(); i++) {
        for (int j = 0; _char_arrays[i][j] != 0; j++)
            free(_char_arrays[i][j]); // added with strdup
        delete _char_arrays[i];
    }

                                // Delete all the callback arrays
                                // we were forced to keep around for
                                // plib.
    for (i = 0; i < _callback_arrays.size(); i++)
        delete _callback_arrays[i];

                                // Delete all those bindings
    map<string,vector<FGBinding *> >::iterator it;
    it = _bindings.begin();
    while (it != _bindings.end()) {
        for (int i = 0; i < it->second.size(); i++)
            delete it->second[i];
    }
}

void
FGMenuBar::init ()
{
    if (_menuBar != 0)          // FIXME: check if PUI owns the pointer
        delete _menuBar;
    make_menubar();

                                // FIXME: temporary commands to get at
                                // old, hard-coded dialogs.
    add_deprecated_dialogs();
}

void
FGMenuBar::show ()
{
    if (_menuBar != 0)
        _menuBar->reveal();
    _visible = true;
}

void
FGMenuBar::hide ()
{
    if (_menuBar != 0)
        _menuBar->hide();
    _visible = false;
}

bool
FGMenuBar::isVisible () const
{
    return _visible;
}

void
FGMenuBar::fireItem (puObject * item)
{
    const char * name = item->getLegend();
    vector<FGBinding *> &bindings = _bindings[name];

    for (int i = 0; i < bindings.size(); i++)
        bindings[i]->fire();
}

void
FGMenuBar::make_menu (SGPropertyNode_ptr node)
{
    const char * name = strdup(node->getStringValue("label"));
    vector<SGPropertyNode_ptr> item_nodes = node->getChildren("item");

    int array_size = item_nodes.size();

    char ** items = make_char_array(array_size);
    puCallback * callbacks = make_callback_array(array_size);

    for (int i = 0, j = item_nodes.size() - 1;
         i < item_nodes.size();
         i++, j--) {
        
                                // Set up the PUI entries for this item
        items[j] = strdup((char *)item_nodes[i]->getStringValue("label"));
        callbacks[j] = menu_callback;

                                // Load all the bindings for this item
        vector<SGPropertyNode_ptr> binding_nodes =
            item_nodes[i]->getChildren("binding");

        for (int k = 0; k < binding_nodes.size(); k++)
            _bindings[items[j]].push_back(new FGBinding(binding_nodes[k]));
    }

    _menuBar->add_submenu(name, items, callbacks);
}

void
FGMenuBar::make_menubar ()
{
    _menuBar = new puMenuBar;
    SGPropertyNode props;

    fgLoadProps("gui/menubar.xml", &props);
    vector<SGPropertyNode_ptr> menu_nodes = props.getChildren("menu");
    for (int i = 0; i < menu_nodes.size(); i++)
        make_menu(menu_nodes[i]);

    _menuBar->close();
    if (_visible)
        _menuBar->reveal();
    else
        _menuBar->hide();
}

char **
FGMenuBar::make_char_array (int size)
{
    char ** list = new char*[size+1];
    for (int i = 0; i <= size; i++)
        list[i] = 0;
    _char_arrays.push_back(list);
    return list;
}

puCallback *
FGMenuBar::make_callback_array (int size)
{
    puCallback * list = new puCallback[size+1];
    for (int i = 0; i <= size; i++)
        list[i] = 0;
    _callback_arrays.push_back(list);
    return list;
}

// end of menubar.cxx
