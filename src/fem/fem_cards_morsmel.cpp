/**
   \file fem_cards_morsmel.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2016 by DNV GL SE
   \brief Processing Sesam FEM `MORSMEL` cards.

   Detailed description
*/

#include "StdAfx.h"

// ID:
namespace {
   const char  cID[]
#ifdef __GNUC__
   __attribute__ ((__unused__))
#endif
      = "@(#) $Id$";
}

#include <memory>
#include <algorithm>

#include "fem/cards.h"
#include "fem/types.h"

#if defined(__AFX_H__) && defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace dnvgl::extfem;
using namespace fem;
using namespace types;

namespace dnvgl {
   namespace extfem {
      namespace fem {
         namespace cards {

            fem::types::card const morsmel::head("MORSMEL");

            // entry_type<long> const morsmel::_form_MATNO("MATNO");
            entry_type<double> const morsmel::_form_Q1("Q1");
            entry_type<double> const morsmel::_form_Q2("Q2");
            entry_type<double> const morsmel::_form_Q3("Q3");
            entry_type<double> const morsmel::_form_RHO("RHO");
            entry_type<double> const morsmel::_form_D11("D11");
            entry_type<double> const morsmel::_form_D21("D21");
            entry_type<double> const morsmel::_form_D22("D22");
            entry_type<double> const morsmel::_form_D31("D31");
            entry_type<double> const morsmel::_form_D32("D32");
            entry_type<double> const morsmel::_form_D33("D33");
            entry_type<double> const morsmel::_form_PS1("PS1");
            entry_type<double> const morsmel::_form_PS2("PS2");
            entry_type<double> const morsmel::_form_DAMP1("DAMP1");
            entry_type<double> const morsmel::_form_DAMP2("DAMP2");
            entry_type<double> const morsmel::_form_ALPHA1("ALPHA1");
            entry_type<double> const morsmel::_form_ALPHA2("ALPHA2");

            morsmel::morsmel(std::deque<std::string> const &inp) :
               base_material(inp) {

               if (inp.size() < 7)
                  throw errors::parse_error(
                     "MORSMEL", "Illegal number of entries.");

               auto pos = inp.begin();

               ++pos;
               MATNO = _form_MATNO(*(pos++));
               Q1 = _form_Q1(*(pos++));
               Q2 = _form_Q2(*(pos++));
               Q3 = _form_Q3(*(pos++));
               RHO = _form_RHO(*(pos++));
               D11 = _form_D11(*(pos++));
               D21 = _form_D21(*(pos++));
               D22 = _form_D22(*(pos++));
               D31 = _form_D31(*(pos++));
               D32 = _form_D32(*(pos++));
               D33 = _form_D33(*(pos++));
               PS1 = _form_PS1(*(pos++));
               PS2 = _form_PS2(*(pos++));
               DAMP1 = _form_DAMP1(*(pos++));
               DAMP2 = _form_DAMP2(*(pos++));
               ALPHA1 = _form_ALPHA1(*(pos++));
               ALPHA2 = _form_ALPHA2(*pos);
            }

            morsmel::morsmel(void) :
               morsmel(-1, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
                       0., 0., 0., 0., 0.) {}

            morsmel::morsmel(long const &MATNO,
                       double const &Q1,
                       double const &Q2,
                       double const &Q3,
                       double const &RHO,
                       double const &D11,
                       double const &D21,
                       double const &D22,
                       double const &D31,
                       double const &D32,
                       double const &D33,
                       double const &PS1,
                       double const &PS2,
                       double const &DAMP1,
                       double const &DAMP2,
                       double const &ALPHA1,
                       double const &ALPHA2) :
               base_material(MATNO), Q1(Q1), Q2(Q2), Q3(Q3),
               RHO(RHO),
               D11(D11), D21(D21), D22(D22), D31(D31), D32(D32),
               D33(D33),
               PS1(PS1), PS2(PS2),
               DAMP1(DAMP1), DAMP2(DAMP2),
               ALPHA1(ALPHA1), ALPHA2(ALPHA2) {}

            const dnvgl::extfem::fem::cards::types
            morsmel::card_type(void) const {return MORSMEL;}

            const std::ostream&
            morsmel::operator<< (std::ostream& os) const {
               os << this;
               return os;
            }

            std::ostream&
            operator<< (std::ostream &os, morsmel const &card) {
               if (card.MATNO == -1) return os;
               os << morsmel::head.format()
                  << card._form_MATNO.format(card.MATNO)
                  << card._form_Q1.format(card.Q1)
                  << card._form_Q2.format(card.Q2)
                  << card._form_Q3.format(card.Q3)
                  << std::endl
                  << dnvgl::extfem::fem::types::card().format()
                  << card._form_RHO.format(card.RHO)
                  << card._form_D11.format(card.D11)
                  << card._form_D21.format(card.D21)
                  << card._form_D22.format(card.D22)
                  << std::endl
                  << dnvgl::extfem::fem::types::card().format()
                  << card._form_D31.format(card.D31)
                  << card._form_D32.format(card.D32)
                  << card._form_D33.format(card.D33)
                  << card._form_PS1.format(card.PS1)
                  << std::endl
                  << dnvgl::extfem::fem::types::card().format()
                  << card._form_PS2.format(card.PS2)
                  << card._form_DAMP1.format(card.DAMP1)
                  << card._form_DAMP2.format(card.DAMP2)
                  << card._form_ALPHA1.format(card.ALPHA1)
                  << std::endl
                  << dnvgl::extfem::fem::types::card().format()
                  << card._form_ALPHA2.format(card.ALPHA2)
                  << std::endl;
               return os;
            }
         }
      }
   }
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../.. check -j 8"
// End: