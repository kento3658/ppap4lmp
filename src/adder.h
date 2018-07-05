/* ---------------------------------------------------------------------
Adder: is an abstract class to add new properties to data.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADDER_H
#define ADDER_H

#include "updater.h"

class Adder : public Updater {
 protected:
  std::unordered_set<std::string> callable_datatypes;
 public:
  Adder() = default;
  virtual ~Adder() = default;
  virtual void compute(nlohmann::json &, const std::string &) override;
  virtual const bool is_callable(const std::string &) override;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_adder(py::module &m)
{
  py::class_<Adder,PyUpdater<Adder>,Updater,std::shared_ptr<Adder>>(m, "Adder")
    .def(py::init<>());
}

#endif