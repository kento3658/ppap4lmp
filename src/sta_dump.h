/* ---------------------------------------------------------------------
StaDump: stands for Starter reading lammps' Dump file.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef STA_DUMP_H
#define STA_DUMP_H

#include "starter.h"

class StaDump : public Starter {
 protected:
  int timestep;
  std::string filepath;
 public:
  StaDump(const std::string &, int);
  virtual ~StaDump() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_sta_dump(py::module &m)
{
  py::class_<StaDump,PyUpdater<StaDump>,Starter,Updater,std::shared_ptr<StaDump>>(m, "StaDump")
    .def(py::init<const std::string &, int>());
}

#endif