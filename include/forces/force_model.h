#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H
#include <drag.h>
#include <gravity.h>
#include <icrf.h>
#include <vectors.h>

#include <iostream>
#include <vector>

/*
Acceleration force model

Determines physical forces acting upon a spacecraft at a given state
*/
class ForceModel {
  // Gravity sources to model
  std::vector<GravityModel> gravity_models;
  // Atmospheric drag model to utilize
  DragModel drag_model;

public:
  /*
  Default constructor

  Set gravity_models to empty vector
  */
  ForceModel();

  /*
  Minimum constructor

  Adds default of spherical central-body gravity of the given state (two-body
  only)

  @param state ICRF state from which to determine central body
  */
  ForceModel(ICRF& state);

  /*
  Direct constructor

  @param gravity_models Vector of GravityModels to include
  */
  ForceModel(std::vector<GravityModel> gravity_models, DragModel drag_model);

  /*
  Add a new GravityModel to the list

  @param model Gravity model to add (existing model with matching id will be replaced)
  */
  void add_gravity(GravityModel model);

  /*
  Change atmospheric drag model

  @param model Drag model to use
  */
  void set_drag_model(DragModel model);

  /*
  Get total acceleration force at a given state

  @param state ICRF state at which to determine acceleration force
  @returns Estimated acceleration vector at the given state in m/s^2
  */
  Vector3 acceleration(ICRF& state);

  // I/O stream operator
  friend std::ostream& operator<<(std::ostream& out, ForceModel& fm);
};

// I/O stream
std::ostream& operator<<(std::ostream& out, ForceModel& fm);

#endif