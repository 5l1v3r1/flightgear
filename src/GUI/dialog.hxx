// dialog.hxx - XML-configured dialog box.

#ifndef __DIALOG_HXX
#define __DIALOG_HXX 1

#ifndef __cplusplus
# error This library requires C++
#endif

#include <plib/pu.h>

#include <simgear/compiler.h>	// for SG_USING_STD
#include <simgear/misc/props.hxx>

#include <vector>
SG_USING_STD(vector);

class FGDialog;
class FGBinding;


/**
 * An XML-configured dialog box.
 *
 * The GUI manager stores only the property tree for the dialog
 * boxes.  This class creates a PUI dialog box on demand from
 * the properties in that tree.  The manager recreates the dialog
 * every time it needs to show it.
 */
class FGDialog
{
public:

    /**
     * Construct a new GUI widget configured by a property tree.
     *
     * The configuration properties are not part of the main
     * FlightGear property tree; the GUI manager reads them
     * from individual configuration files.
     *
     * @param props A property tree describing the dialog.
     */
    FGDialog (SGPropertyNode * props);


    /**
     * Destructor.
     */
    virtual ~FGDialog ();


    /**
     * Update the values of all GUI objects with a specific name.
     *
     * This method copies values from the FlightGear property tree to
     * the GUI object(s).
     *
     * @param objectName The name of the GUI object(s) to update.
     *        Use the empty name for all unnamed objects.
     */
    virtual void updateValue (const char * objectName);


    /**
     * Apply the values of all GUI objects with a specific name.
     *
     * This method copies values from the GUI object(s) to the
     * FlightGear property tree.
     *
     * @param objectName The name of the GUI object(s) to update.
     *        Use the empty name for all unnamed objects.
     */
    virtual void applyValue (const char * objectName);


    /**
     * Update the values of all GUI objects.
     *
     * This method copies values from the FlightGear property tree to
     * the GUI objects.
     */
    virtual void updateValues ();


    /**
     * Apply the values of all GUI objects.
     *
     * This method copies from the GUI objects to the FlightGear
     * property tree properties.
     */
    virtual void applyValues ();


private:

    // Private copy constructor to avoid unpleasant surprises.
    FGDialog (const FGDialog &);

    // Show the dialog.
    void display (SGPropertyNode * props);

    // Build the dialog or a subobject of it.
    puObject * makeObject (SGPropertyNode * props,
                           int parentWidth, int parentHeight);

    // Common configuration for all GUI objects.
    void setupObject (puObject * object, SGPropertyNode * props);

    // Common configuration for all GUI group objects.
    void setupGroup (puGroup * group, SGPropertyNode * props,
                     int width, int height, bool makeFrame = false);

    // The top-level PUI object.
    puObject * _object;

    // PUI provides no way for userdata to be deleted automatically
    // with a GUI object, so we have to keep track of all the special
    // data we allocated and then free it manually when the dialog
    // closes.
    vector<void *> _info;
    struct PropertyObject {
        PropertyObject (const char * name,
                        puObject * object,
                        SGPropertyNode_ptr node);
        string name;
        puObject * object;
        SGPropertyNode_ptr node;
    };
    vector<PropertyObject *> _propertyObjects;

    // PUI doesn't copy arrays, so we have to allocate string arrays
    // and then keep pointers so that we can delete them when the
    // dialog closes.
    char ** make_char_array (int size);
    vector<char **> _char_arrays;
};

#endif // __DIALOG_HXX
