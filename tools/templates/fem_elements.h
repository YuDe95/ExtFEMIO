/*
   #####     #    #     # #######   ###   ####### #     #   ###
  #     #   # #   #     #    #       #    #     # ##    #   ###
  #        #   #  #     #    #       #    #     # # #   #   ###
  #       #     # #     #    #       #    #     # #  #  #    #
  #       ####### #     #    #       #    #     # #   # #
  #     # #     # #     #    #       #    #     # #    ##   ###
   #####  #     #  #####     #      ###   ####### #     #   ###

   Automatically generated source file. Contact author if changes are
   required.
 */

/**
   \file fem/elements.h
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015, 2016 by DNV GL SE
   \brief Element card representation for Sesam FEM.

   Detailed description
*/

// ID: $Id$

#include "fem/cards.h"

#ifndef _FEM_ELEMENTS_H_
#define _FEM_ELEMENTS_H_

#include <my_c++14.h>

#include <set>

{% line %}

namespace dnvgl {
   namespace extfem {
      namespace fem {
         namespace elements {

            enum class el_types {
               {% for name, val in enums %}{{ name }} = {{ val }},
               {% endfor %}INVALID=-1, UNDEFINED=-2};
{% line %}
            enum class el_processor {
               general, Preframe, Prefem, Sestra, ADVANCE,
               Framework, Launch, Platework, Pretube,
               Splice, Wadam, Wajac,
               Poseidon};

            namespace __base {
            /** Base class for FEM element representation.
             */
               class elem {

               private:

                  static cards::gelmnt1 d_gelmnt1;
                  static cards::gelref1 d_gelref1;

               protected:
                  el_types static const type;
                  elem(void);
                  elem(long const elno,
                       long const elident,
                       long const el_add,
                       std::vector<long> const nodes,
                       long const matref,
                       long const add_no,
                       long const intno,
                       long const mass_intno,
                       long const i_strain_ref,
                       long const i_stressef,
                       long const strpoint_ref,
                       std::vector<long> const sections,
                       std::vector<long> const fixations,
                       std::vector<long> const eccentrities,
                       std::vector<long> const csys);
                  __base::elem const &operator() (
                     long const elno,
                     long const elident,
                     long const el_add,
                     std::vector<long> const nodes,
                     long const matref,
                     long const add_no,
                     long const intno,
                     long const mass_intno,
                     long const i_strain_ref,
                     long const i_stressef,
                     long const strpoint_ref,
                     std::vector<long> const sections,
                     std::vector<long> const fixations,
                     std::vector<long> const eccentrities,
                     std::vector<long> const csys);

               public:
                  elem(dnvgl::extfem::fem::cards::gelmnt1 const*);
                  elem(dnvgl::extfem::fem::cards::gelref1 const*);
                  elem(elem const*);

                  cards::__base::card const &gelmnt1(void) const;
                  cards::__base::card const &gelref1(void) const;


                  /** Element number ->
                      dnvgl::extfem::fem::cards::gelmnt1::ELNOX
                  */
                  long eleno;
                  /** internal element identifier ->
                      dnvgl::extfem::fem::cards::gelmnt1::ELNO, ->
                      dnvgl::extfem::fem::cards::gelref1::ELNO
                  */
                  long elident;
                  /** Additional element information ->
                      dnvgl::extfem::fem::cards::gelmnt1::ELTYAD
                  */
                  long el_add;
                  /** node references for element ->
                      dnvgl::extfem::fem::cards::gelmnt1::NODIN
                  */
                  std::vector<long> nodes;
                  /** Material reference ->
                      dnvgl::extfem::fem::cards::gelref1::MATNO
                  */
                  long matref;
                  /** additional data type number ->
                      dnvgl::extfem::fem::cards::gelref1::ADDNO
                  */
                  long add_no;
                  /** Integration station reference for stiffness
                      matrix-> dnvgl::extfem::fem::cards::gelref1::INTNO
                  */
                  long intno;
                  /** Integration station reference for mass and damping
                      matrices->
                      dnvgl::extfem::fem::cards::gelref1::INTNO
                  */
                  long mass_intno;
                  /** Reference to initial strain information (unused).
                      -> dnvgl::extfem::fem::cards::gelref1::STRANO
                  */
                  long i_strain_ref;
                  /** Reference to initial stress information (unused).
                      -> dnvgl::extfem::fem::cards::gelref1::STRENO
                  */
                  long i_stress_ref;
                  /** Reference to stresspoint definition ->
                      dnvgl::extfem::fem::cards::gelref1::STREPONO
                  */
                  long strpoint_ref;
                  /** Geometry information reference for element. ->
                      dnvgl::extfem::fem::cards::gelref1::GEONO_OPT /
                      dnvgl::extfem::fem::cards::gelref1::GEONO
                  */
                  std::vector<long> section;
                  /** Fixation information reference for element. ->
                      dnvgl::extfem::fem::cards::gelref1::FIXNO_OPT /
                      dnvgl::extfem::fem::cards::gelref1::FIXNO
                  */
                  std::vector<long> fixations;
                  /** Eccentricity information reference for element. ->
                      dnvgl::extfem::fem::cards::gelref1::ECCNO_OPT /
                      dnvgl::extfem::fem::cards::gelref1::ECCNO
                  */
                  std::vector<long> eccentrities;
                  /** Local coordinate system information reference for
                      element. ->
                      dnvgl::extfem::fem::cards::gelref1::TRANSNO_OPT /
                      dnvgl::extfem::fem::cards::gelref1::TRANSNO
                  */
                  std::vector<long> csys;

                  virtual void add(dnvgl::extfem::fem::cards::gelref1 const*);
                  virtual void add(dnvgl::extfem::fem::cards::gelmnt1 const*);

                  virtual long nnodes(void) const = 0;

                  virtual el_types get_type(void) const = 0;

                  friend std::ostream &operator<<(std::ostream&, elem const &);
               };

               /** Base thin shell element definitions
                */
               class fem_thin_shell : public __base::elem {
               public:
                  fem_thin_shell(void);
                  fem_thin_shell(
                     long const elno,
                     long const elident,
                     long const el_add,
                     std::vector<long> const nodes,
                     long const matref,
                     long const add_no,
                     long const intno,
                     long const mass_intno,
                     long const i_strain_ref,
                     long const i_stressef,
                     long const strpoint_ref,
                     std::vector<long> const sections,
                     std::vector<long> const fixations,
                     std::vector<long> const eccentrities,
                     std::vector<long> const csys);
                  fem_thin_shell(dnvgl::extfem::fem::cards::gelmnt1 const*);
                  fem_thin_shell(dnvgl::extfem::fem::cards::gelref1 const*);
                  fem_thin_shell(__base::elem const*);
                  using elem::operator();
               };
            }

            class undef : public __base::elem {
            public:
               undef (void);
               undef(dnvgl::extfem::fem::cards::gelref1 const*);
               virtual long nnodes(void) const;
               el_types get_type(void) const;
            };

{% for elem, vals in elements %}
{% line %}
            /** {{ vals.doc }}
             */
            class {{ elem }} : public __base::{{ vals.base }} {
            public:
               {{ elem }}(void);
               {{ elem }}(long const elno,
                       long const elident,
                       long const el_add,
                       std::vector<long> const nodes,
                       long const matref,
                       long const add_no,
                       long const intno,
                       long const mass_intno,
                       long const i_strain_ref,
                       long const i_stressef,
                       long const strpoint_ref,
                       std::vector<long> const sections,
                       std::vector<long> const fixations,
                       std::vector<long> const eccentrities,
                       std::vector<long> const csys);
               using {{ vals.base }}::operator();
               {{ elem }}(dnvgl::extfem::fem::cards::gelmnt1 const*);
               {{ elem }}(dnvgl::extfem::fem::cards::gelref1 const*);
               {{ elem }}( __base::elem const*);
               virtual long nnodes(void) const;
               el_types get_type(void) const;
               std::set<el_processor> static const processors;
            };
{% endfor %}
{% line %}
            /** Dispatch element class instance for `id`
             */
            void dispatch(std::unique_ptr<__base::elem>&,
               cards::gelmnt1 const *data);

            /** Match element type id to element type name.
             */
            std::string name_elem(dnvgl::extfem::fem::elements::el_types const &);
         }
      }
   }
}

#endif // _FEM_ELEMENTS_H_

// Local Variables:
// mode: c++
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../../cbuild -j8&&make -C ../../cbuild test"
// End:
