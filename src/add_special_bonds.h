/* ---------------------------------------------------------------------
AddSpecialBonds: stands for Adder for Special Bonds.
See: https://lammps.sandia.gov/doc/special_bonds.html

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef ADD_SPECIAL_BONDS_H
#define ADD_SPECIAL_BONDS_H

#include "adder.h"

class AddSpecialBonds : public Adder {
  Dict<int,List<List<int>>> mol_type_to_sbonds_list_in_mol;
 protected:
  virtual void compute_impl(Json &, Set<Str> &) override;
 public:
  AddSpecialBonds(ShPtr<GenElement>, const List<List<int>> &);
  AddSpecialBonds(ShPtr<GenElement>, const Dict<int,List<List<int>>> &);
  virtual ~AddSpecialBonds() = default;
};

/* ------------------------------------------------------------------ */
// for pybind11

static void pybind_add_special_bonds(py::module &m)
{
  // DO NOT BREAK LINE until `.def()` for setup.py's parsing
  py::class_<AddSpecialBonds,PyUpdater<AddSpecialBonds>,Adder,Updater,ShPtr<AddSpecialBonds>>(m, "AddSpecialBonds")
    .def(py::init<ShPtr<GenElement>,const List<List<int>> &>())
    .def(py::init<ShPtr<GenElement>,const Dict<int,List<List<int>>> &>());
}

#endif