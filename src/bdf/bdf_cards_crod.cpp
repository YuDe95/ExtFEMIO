/**
   \file bdf/bdf_cards_crod.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Defintions for Patran CROD cards.

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
#include "bdf/types.h"
#include "bdf/errors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace ::std;
using namespace ::dnvgl::extfem;
using namespace bdf::cards;
using bdf::types::entry_type;

const entry_type<long> crod::form_EID(
   "EID", bdf::type_bounds::bound<long>(make_unique<long>(1).get()));
const entry_type<long> crod::form_PID("PID");
const entry_type<long> crod::form_G1("G1");
const entry_type<long> crod::form_G2("G2");

crod::crod(const deque<std::string> &inp) :
   card(inp) {

   auto pos = inp.rbegin();

   switch (inp.size()-1) {
   case 8:
      ++pos;
   case 7:
      ++pos;
   case 6:
      ++pos;
   case 5:
      ++pos;
   case 4:
      form_G2.set_value(G2, *(pos++));
      form_G1.set_value(G1, *(pos++));
      form_PID.set_value(PID, *(pos++));
      form_EID.set_value(EID, *pos);
      break;
   default:
      throw errors::parse_error(
         "CROD", "Illegal number of entries for CROD");
   }
};

const std::ostream& crod::operator << (std::ostream& os) const {
   throw errors::error("can't write CROD.");
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
