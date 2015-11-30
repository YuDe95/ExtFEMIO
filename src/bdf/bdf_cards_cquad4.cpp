/**
   \file bdf/bdf_cards_cquad4.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Definitions for Nastran BDF CQUAD4 cards.

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

#include "bdf/cards.h"
#include "bdf/errors.h"

#include <memory>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace ::std;
using namespace ::dnvgl::extfem;
using namespace bdf::cards;
using bdf::types::entry_type;

cquad4::cquad4(const deque<std::string> &inp) : base_shell(inp) {

   auto pos = inp.rbegin();

   THETA = nullptr;
   MCID = nullptr;
   ZOFFS = nullptr;
   TFLAG = nullptr;
   T1 = nullptr;
   T2 = nullptr;
   T3 = nullptr;
   T4 = nullptr;

   switch (inp.size()-1) {
   case 16:
      ++pos;
   case 15:
      ++pos;
   case 14:
      form_T4.set_value(T4, *(pos++));
   case 13:
      form_T3.set_value(T3, *(pos++));
   case 12:
      form_T2.set_value(T2, *(pos++));
   case 11:
      form_T1.set_value(T1, *(pos++));
   case 10:
      form_TFLAG.set_value(TFLAG, *(pos++));
   case 9:
      ++pos;
   case 8:
      form_ZOFFS.set_value(ZOFFS, *(pos++));
   case 7:
      try {
         form_THETA.set_value(THETA, *pos);
         MCID = nullptr;
         choose_mcid_theta = has_THETA;
      }
      catch (errors::float_error) {
         try {
            form_MCID.set_value(MCID, *pos);
            THETA = nullptr;
            choose_mcid_theta = has_MCID;
         }
         catch (errors::int_error) {
            THETA.is_value = true;
            THETA.value = 0.;
            MCID = nullptr;
            choose_mcid_theta = has_THETA;
         }
      }
      ++pos;
   case 6:
      form_G4.set_value(G4, *(pos++));
      form_G3.set_value(G3, *(pos++));
      form_G2.set_value(G2, *(pos++));
      form_G1.set_value(G1, *(pos++));
      form_PID.set_value(PID, *(pos++));
      form_EID.set_value(EID, *pos);
      break;
   default:
      throw errors::parse_error(
         "CQUAD4", "Illegal number of entries.");
   }

   if (!THETA.is_value && !MCID.is_value)
      form_THETA.set_value(THETA, "");
   if (TFLAG.is_value) {
      if (!T1.is_value) form_T1.set_value(T1, "");
      if (!T2.is_value) form_T2.set_value(T2, "");
      if (!T3.is_value) form_T3.set_value(T3, "");
      if (!T4.is_value) form_T4.set_value(T4, "");
   }
}

const std::ostream& cquad4::operator << (std::ostream& os) const {
   throw errors::error("can't write CQUAD4.");
   return os;
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../.. check -j 8"
// End:
