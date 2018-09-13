/*!
  @file src/adders/add_child_ids.h
  @brief This file has a definition of the AddChildIDs class, which is
  a subclass of the Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_CHILD_IDS_H
#define ADD_CHILD_IDS_H

#include <adders/adder.h>

/*!
  @brief \e AddChildIDs stands for Adder for Child IDs (such as
  \c atom-ids for molecules).
  @details This class inherits Adder class and overrides
  Adder::compute_impl. An instance of this class is supposed to own a
  \e children instance (such as atoms) as the #ext_generator and be
  appended to \e parent instance (such as molecules). \c id property of
  a \e child is appended to an array belonging to its \e parent. About
  usage in Python, please see src/pybind/adders/add_child_ids.h.
  <p>
  Name (key) of property to be added:
    - <c>[child_name]-ids</c> (array of integer)
  </p>
  <p>
  Name (key) of property to be required:
    - \c id (integer)
  </p>
  <p>
  Name (key) of property in #ext_generator to be required:
    - \c id (integer)
    - <c>[key_for_parent_id]</c>  (integer)
  </p>
*/
class AddChildIDs : public Adder {
  /*!
    @brief Name of \e children instance stored as #ext_generator.
    @details The name (key) of property added by this class is named
    as <c>[child_name]-ids</c>.
  */
  Str child_name;
  /*!
    @brief Key in #ext_generator corresponding to \c id of \e parent
    instance.
    @details The \e parent instance is an Element instance where this
    instance is appended to.
  */
  Str key_for_parent_id;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildIDs class.
    @param elem : Shared pointer to \e children instance.
    @param child_name_ : A string for name of the \e children instance.
    @param key_for_parent_id_ : A string for key in the \e children
    instance corresponding to \c id of \e parent instance.
    @return Instance of this class.
    @details The \c elem, \c child_name_ and \c key_for_parent_id_ are
    assigned to the #ext_generator, #child_name and #key_for_parent_id,
    respectively.
  */
  AddChildIDs(
    const ElPtr &elem,
    const Str &child_name_,
    const Str &key_for_parent_id_);
  virtual ~AddChildIDs() = default;
};

#endif