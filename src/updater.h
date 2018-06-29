/* ---------------------------------------------------------------------
Updater: is an abstract class to update data held by Generator.

create: 2018/06/29 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef UPDATER_H
#define UPDATER_H

#include "generator.h"

class Updater {
 public:
  Updater() = default;
  virtual ~Updater() = default;
  virtual void compute(nlohmann::json &) = 0;
  void add_generator(std::shared_ptr<Generator>);
 protected:
  std::unordered_map<std::string,std::shared_ptr<Generator>> generators;
  virtual void compute_impl(nlohmann::json &) = 0;
};

/* ------------------------------------------------------------------ */
// for pubind11

namespace py = pybind11;

// trampoline class to bind Python
template <class UPD = Updater>
class PyUpdater : public UPD {
 public:
  using UPD::UPD;
  void compute(nlohmann::json &data) override
  {
    PYBIND11_OVERLOAD_PURE(void, UPD, compute, data);
  }
 protected:
  void compute_impl(nlohmann::json &data) override
  {
    PYBIND11_OVERLOAD_PURE(void, UPD, compute_impl, data);
  }
};

static void pybind_updater(py::module &m)
{
  py::class_<Updater,PyUpdater<>,std::shared_ptr<Updater>>(m, "Updater")
    .def(py::init<>())
    .def("add_generator", &Updater::add_generator);
}

#endif