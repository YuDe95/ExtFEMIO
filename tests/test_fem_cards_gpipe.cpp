/**
   \file tests/test_fem_cards_gpipe.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Testing IO for Sesam FEM `GPIPE` cards.

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

TEST_CASE("FEM GPIPE definitions.", "[fem_gpipe]" ) {

   SECTION("GPIPE (1)") {
      ::std::deque<string> data;

      data.push_back(
         "GPIPE    6.54357000e+005 0.00000000e+000 5.90218891e-002 2.95109446e-002\n");
      data.push_back(
         "         1.00000000e+000 1.00000000e+000 0.00000000e+000 0.00000000e+000\n");
      ::std::deque<string> lines = card::card_split(data);
      gpipe probe(lines);

      CHECK(probe.GEONO == 22);
      CHECK(probe.DI == 0.);
      CHECK(probe.DY == 5.90218891e-2);
      CHECK(probe.T == 2.95109446e-2);
      CHECK(probe.SFY == 1.);
      CHECK(probe.SFZ == 1.);
      CHECK(probe.NCIR == 0);
      CHECK(probe.NRAD == 0);
   }

   SECTION("GPIPE (2)") {
      ::std::deque<string> data;

      data.push_back(
         "GPIPE    6.54357000e+05  0.00000000e+00  5.90218891e-02  2.95109446e-02 \n");
      data.push_back(
         "         1.00000000e+00  1.00000000e+00  0.00000000e+00  0.00000000e+00 \n");
      ::std::deque<string> lines = card::card_split(data);
      gpipe probe(lines);

      CHECK(probe.GEONO == 22);
      CHECK(probe.DI == 0.);
      CHECK(probe.DY == 5.90218891e-2);
      CHECK(probe.T == 2.95109446e-2);
      CHECK(probe.SFY == 1.);
      CHECK(probe.SFZ == 1.);
      CHECK(probe.NCIR == 0);
      CHECK(probe.NRAD == 0);
   }
}

TEST_CASE("FEM GPIPE types output.", "[fem_gpipe,out]" ) {

   std::ostringstream test;

   SECTION("simple") {
      gpipe probe(1, 2., 3., 4., 5., 6., 7, 8);
      test << probe;
      CHECK(test.str() ==
            "GPIPE   +1.00000000e+00 +2.00000000e+00 +3.00000000e+00 +4.00000000e+00 \n"
            "        +5.00000000e+00 +6.00000000e+00 +7.00000000e+00 +8.00000000e+00 \n");
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