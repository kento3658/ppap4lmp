/* ---------------------------------------------------------------------
ProRadialDistributionFunction: stands for Processor which computes
Radial Distribution Function (RDF) from wrapped positions.

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include "processor.h"

class ProRadialDistributionFunction : public Processor {
  int n_bins = 1;
  double bin_width = 1.0;
  bool bin_from_r_to_r_plus_dr = false;
  ArrayXd rdf;
  List<ArrayXd> rdf_traj;
  List<double> density_traj;
  List<ArrayXd> number_distribution_traj;
 protected:
  virtual void run_impl(int) override;
 public:
  ProRadialDistributionFunction(ShPtr<GenElement>, ShPtr<GenElement>);
  ProRadialDistributionFunction(
    List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>>);
  virtual ~ProRadialDistributionFunction() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_bin(double, int);
  void set_bin_from_r_to_r_plus_dr(bool);
  const ArrayXd get_r_axis();
  const ArrayXd &get_rdf();
  const List<ArrayXd> &get_rdf_traj();
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_pro_radial_distribution_function(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<ProRadialDistributionFunction,PyProcessor<ProRadialDistributionFunction>,Processor,ShPtr<ProRadialDistributionFunction>>(m, "ProRadialDistributionFunction")
    .def(py::init<ShPtr<GenElement>,ShPtr<GenElement>>())
    .def(py::init<List<std::pair<ShPtr<GenElement>,ShPtr<GenElement>>>>())
    .def("set_bin", &ProRadialDistributionFunction::set_bin)
    .def("set_bin_from_r_to_r_plus_dr", &ProRadialDistributionFunction::set_bin_from_r_to_r_plus_dr)
    .def("get_r_axis", &ProRadialDistributionFunction::get_r_axis)
    .def(
      "get_rdf", &ProRadialDistributionFunction::get_rdf,
      py::return_value_policy::reference_internal)
    .def(
      "get_rdf_traj", &ProRadialDistributionFunction::get_rdf_traj,
      py::return_value_policy::reference_internal);
}

#endif