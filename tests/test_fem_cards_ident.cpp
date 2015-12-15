/**
   \file tests/test_fem_cards_ident.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Testing input and output for Sesam FEM `IDENT` cards.

   Detailed description
*/

// ID:
namespace {
   const char  cID[]
#ifdef __GNUC__
   __attribute__ ((__unused__))
#endif
      = "@(#) $Id$";
}

#define NOMINMAX // To avoid problems with "numeric_limits"

#include <limits>

#include <catch.hpp>

#ifndef _MSC_VER
#include <config.h>
#endif
#include "fem/cards.h"

using namespace ::std;
using namespace ::dnvgl::extfem::fem;
using namespace ::dnvgl::extfem::fem::cards;

CATCH_TRANSLATE_EXCEPTION( errors::error& ex ) {
   return ex();
}

CATCH_TRANSLATE_EXCEPTION( ::std::string& ex ) {
   return ex;
}

TEST_CASE("FEM IDENT definitions.", "[fem_ident]" ) {

   ::std::deque<string> lines;
   
   SECTION("IDENT (1)") {
      ::std::deque<string> data;
      data.push_back(
         "IDENT    1.00000000e+000 1.00000000e+000 3.00000000e+000 0.00000000e+000\n");
      card::card_split(data, lines);
      ident probe(lines);

      CHECK(probe.SLEVEL == 1);
      CHECK(probe.SELTYP == 1);
      CHECK(probe.SELMOD == 3);
   }

   SECTION("IDENT (2)") {
      ::std::deque<string> data;
      data.push_back(
         "IDENT   +1.00000000e+000+1.00000000e+000+3.00000000e+000+0.00000000e+000\n");
      card::card_split(data, lines);
      ident probe(lines);

      CHECK(probe.SLEVEL == 1);
      CHECK(probe.SELTYP == 1);
      CHECK(probe.SELMOD == 3);
   }

   SECTION("IDENT (3)") {
      ::std::deque<string> data;
      data.push_back(
         "IDENT    1.00000000e+00  1.00000000e+00  3.00000000e+00  0.00000000e+00 \n");
      card::card_split(data, lines);
      ident probe(lines);

      CHECK(probe.SLEVEL == 1);
      CHECK(probe.SELTYP == 1);
      CHECK(probe.SELMOD == 3);
   }
}

TEST_CASE("FEM IDENT types output.", "[fem_ident,out]" ) {

   std::ostringstream test;

   SECTION("simple") {
      long SLEVEL(1), SELTYP(2), SELMOD(3);
      ident probe(SLEVEL, SELTYP, SELMOD);
      test << probe;
      CHECK(test.str() ==
            "IDENT   +1.00000000e+00 +2.00000000e+00 +3.00000000e+00  0.00000000e+00 \n");
   }
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. check -j8"
// End:
