/**
   \file tests/test_bdf_cards_cbeam.cpp
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Testing the BDF `CBEAM` card class.

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
#include "bdf/cards.h"

using namespace ::std;
using namespace ::dnvgl::extfem::bdf;
using namespace ::dnvgl::extfem::bdf::cards;

CATCH_TRANSLATE_EXCEPTION( errors::error& ex ) {
   return ex();
}

CATCH_TRANSLATE_EXCEPTION( ::std::string& ex ) {
   return ex;
}

using namespace ::std;
using namespace ::dnvgl::extfem::bdf::cards;

TEST_CASE("BDF CBEAM definitions. (Small Field Format)", "[bdf_cbeam]" ) {

   ::std::deque<string> data;
   data.push_back(
      "CBEAM   7869    104010  76      153     0.0     66.5206 997.785  2.\n");
   data.push_back(
      "                        0.0     -22.617 -339.25 0.0     -22.617 \n");
   ::std::deque<string> lines;
   card::card_split(data, lines);
   cbeam probe(lines);

   SECTION("first cbeam") {
      CHECK(probe.EID.value == 7869);
      CHECK(probe.PID.value == 104010);
      CHECK(probe.GA.value == 76);
      CHECK(probe.GB.value == 153);
      CHECK((double)probe.X1 == 0.);
      CHECK((double)probe.X2 == 66.5206);
      CHECK((double)probe.X3 == 997.785);
      CHECK_FALSE(probe.G0);
      CHECK(probe.choose_dir_code == cbeam::has_DVEC);
      CHECK((double)probe.BIT == 2.);
      CHECK_FALSE(probe.OFFT);
      CHECK(probe.choose_offt_bit == cbeam::has_BIT);
      deque<int> p_ref;
      CHECK(probe.PA == p_ref);
      CHECK(probe.PB == p_ref);
      CHECK((double)probe.W1A == 0.);
      CHECK((double)probe.W2A == -22.617);
      CHECK((double)probe.W3A == -339.25);
      CHECK((double)probe.W1B == 0.);
      CHECK((double)probe.W2B == -22.617);
      CHECK((double)probe.W3B == 0.);
      CHECK_FALSE(probe.SA);
      CHECK_FALSE(probe.SB);
   }
}

TEST_CASE("BDF CBEAM definitions. (Small Field Format), dircode",
          "[bdf_cbeam,dcode]" ) {

   ::std::deque<string> data;
   data.push_back(
      "CBEAM   7869    104010  76      153      13                     GOO     \n");
   data.push_back(
      "                        0.0     -22.617 -339.25 0.0     22.617 ");
   ::std::deque<string> lines;
   card::card_split(data, lines);
   cbeam probe(lines);

   SECTION("dir code cbeam") {
      CHECK((long)probe.EID == 7869);
      CHECK((long)probe.PID == 104010);
      CHECK((long)probe.GA == 76);
      CHECK((long)probe.GB == 153);
      CHECK((long)probe.G0 == 13);
      CHECK_FALSE(probe.X1);
      CHECK_FALSE(probe.X2);
      CHECK_FALSE(probe.X3);
      CHECK(probe.choose_dir_code == cbeam::has_DCODE);
      CHECK(probe.OFFT == "GOO");
      CHECK_FALSE(probe.BIT);
      CHECK(probe.choose_offt_bit == cbeam::has_OFFT);
      deque<int> p_ref;
      CHECK(probe.PA == p_ref);
      CHECK(probe.PB == p_ref);
      CHECK((double)probe.W1A == 0.);
      CHECK((double)probe.W2A == -22.617);
      CHECK((double)probe.W3A == -339.25);
      CHECK((double)probe.W1B == 0.);
      CHECK((double)probe.W2B == 22.617);
      CHECK((double)probe.W3B == 0.);
      CHECK_FALSE(probe.SA);
      CHECK_FALSE(probe.SB);
   }
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. check -j 8"
// End:
