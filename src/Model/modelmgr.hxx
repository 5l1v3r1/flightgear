// model-mgr.hxx - manage user-specified 3D models.
// Written by David Megginson, started 2002.
//
// This file is in the Public Domain, and comes with no warranty.

#ifndef __MODELMGR_HXX
#define __MODELMGR_HXX 1

#ifndef __cplusplus
# error This library requires C++
#endif

#include <vector>

#include <simgear/compiler.h>	// for SG_USING_STD

#include <Main/fgfs.hxx>	// for FGSubsystem

SG_USING_STD(vector);

// Don't pull in headers, since we don't need them here.
class ssgSelector;
class SGPropertyNode;
class SGModelPlacement;


/**
 * Manage a list of user-specified models.
 */
class FGModelMgr : public FGSubsystem
{
public:

  /**
   * A dynamically-placed model using properties.
   *
   * The model manager uses the property nodes to update the model's
   * position and orientation; any of the property node pointers may
   * be set to zero to avoid update.  Normally, a caller should
   * load the model by instantiating SGModelPlacement with the path
   * to the model or its XML wrapper, then assign any relevant
   * property node pointers.
   *
   * @see SGModelPlacement
   * @see FGModelMgr#add_instance
   */
  struct Instance
  {
    Instance ();
    virtual ~Instance ();
    SGModelPlacement * model;
    SGPropertyNode * lon_deg_node;
    SGPropertyNode * lat_deg_node;
    SGPropertyNode * elev_ft_node;
    SGPropertyNode * roll_deg_node;
    SGPropertyNode * pitch_deg_node;
    SGPropertyNode * heading_deg_node;
  };

  FGModelMgr ();
  virtual ~FGModelMgr ();

  virtual void init ();
  virtual void bind ();
  virtual void unbind ();
  virtual void update (double dt);

  /**
   * Add an instance of a dynamic model to the manager.
   *
   * NOTE: pointer ownership is transferred to the model manager!
   *
   * The caller is responsible for setting up the Instance structure
   * as required.  The model manager will continuously update the
   * location and orientation of the model based on the current
   * values of the properties.
   */
  virtual void add_instance (Instance * instance);


  /**
   * Remove an instance of a dynamic model from the manager.
   *
   * NOTE: the manager will delete the instance as well.
   */
  virtual void remove_instance (Instance * instance);

  virtual void draw ();

private:

  vector<Instance *> _instances;

  ssgSelector * _selector;

};

#endif // __MODELMGR_HXX
