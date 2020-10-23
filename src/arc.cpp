#include <cartesian.h>
#include <celestial.h>
#include <datetime.h>
#include <vectors.h>
#include <force_model.h>
#include <gravity.h>
#include <rungekutta4.h>
#include <ephemeris.h>
#include <data_files.h>
#include <iostream>

int main() {
  DateTime test {"2020-01-01T00:00:00"};
  test.print();
  test.tai().print();
  test.tt().print();
  test.tdb().print();
  return 0;
}