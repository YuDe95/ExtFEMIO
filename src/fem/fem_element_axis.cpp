/**
   \file fem/fem_element_axis.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2016 by DNV GL SE
   \brief FEM element definition for axis.

   Axial Spring
*/

// ID:
namespace {
   const char  cID[]
#ifdef __GNUC__
   __attribute__ ((__unused__))
#endif
      = "@(#) $Id$";
}

#include "fem/elements.h"

using namespace ::dnvgl::extfem::fem::elements;

const long axis::nnodes = 2;

el_types axis::get_type() const {return AXIS;}

namespace {
   const size_t procs_len = 7;
   el_processor procs[
      procs_len] = {general, Preframe, Prefem, Sestra, ADVANCE,
                    Framework, Poseidon};
}
const ::std::set<el_processor> axis::processors(procs, procs+procs_len);

axis::axis(const ::dnvgl::extfem::fem::cards::gelmnt1 &data) :
   ::dnvgl::extfem::fem::elements::__base(data) {}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../.. check -j8"
// End: