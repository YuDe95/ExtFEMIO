// Copyright © 2015 by DNV GL SE

// Purpose: Testing the BDF CBAR card class.

// Author Berthold Höllmann <berthold.hoellmann@dnvgl.com>

// ID:
namespace {
  const char  cID[]
#ifdef __GNUC__
  __attribute__ ((__unused__))
#endif
    = "@(#) $Id$";
}

#define NOMINMAX // To avoid problems with "numdric_limits"

#include <limits>

#include <catch.hpp>

#ifndef _MSC_VER
#include <config.h>
#endif
#include "bdf/cards.h"

CATCH_TRANSLATE_EXCEPTION( bdf_error& ex ) {
  return ex();
}

CATCH_TRANSLATE_EXCEPTION( ::std::string& ex ) {
  return ex;
}

using namespace std;
using namespace bdf::cards;

TEST_CASE("BDF CBAR definitions. (Small Field Format)", "[bdf_cbar]" ) {

  ::std::deque<string> data;
  data.push_back("CBAR    7869    104010  76      153     0.0     66.5206 997.785 \n");
  data.push_back("                        0.0     -22.617 -339.25 0.0     -22.617 \n");
  ::std::deque<string> lines = card::card_split(data);
  cbar probe(lines);

  SECTION("first cbar") {
    CHECK(*probe.EID == 7869);
    CHECK(*probe.PID == 104010);
    CHECK(*probe.GA == 76);
    CHECK(*probe.GB == 153);
    CHECK(*probe.X1 == 0.);
    CHECK(*probe.X2 == 66.5206);
    CHECK(*probe.X3 == 997.785);
    CHECK_FALSE(probe.G0);
    CHECK(probe.choose_dir_code == cbar::has_DVEC);
    CHECK(*probe.OFFT == "GGG");
    deque<int> p_ref;
    CHECK(*probe.PA == p_ref);
    CHECK(*probe.PB == p_ref);
    CHECK(*probe.W1A == 0.);
    CHECK(*probe.W2A == -22.617);
    CHECK(*probe.W3A == -339.25);
    CHECK(*probe.W1B == 0.);
    CHECK(*probe.W2B == -22.617);
    CHECK(*probe.W3B == 0.);
  }
}

TEST_CASE("BDF CBAR definitions. (Small Field Format), dircode",
          "[bdf_cbar,dcode]" ) {

  ::std::deque<string> data;
  data.push_back("CBAR    7869    104010  76      153      13      "
                 "               GOO     \n");
  data.push_back("                        0.0     -22.617 -339.25 "
                 "0.0     -22.617 ");
  ::std::deque<string> lines = card::card_split(data);
  cbar probe(lines);

  SECTION("dir code cbar") {
    CHECK(*probe.EID == 7869);
    CHECK(*probe.PID == 104010);
    CHECK(*probe.GA == 76);
    CHECK(*probe.GB == 153);
    CHECK(*probe.G0 == 13);
    CHECK_FALSE(probe.X1);
    CHECK_FALSE(probe.X2);
    CHECK_FALSE(probe.X3);
    CHECK(probe.choose_dir_code == cbar::has_DCODE);
    CHECK(*probe.OFFT == "GOO");
    deque<int> p_ref;
    CHECK(*probe.PA == p_ref);
    CHECK(*probe.PB == p_ref);
    CHECK(*probe.W1A == 0.);
    CHECK(*probe.W2A == -22.617);
    CHECK(*probe.W3A == -339.25);
    CHECK(*probe.W1B == 0.);
    CHECK(*probe.W2B == -22.617);
    CHECK(*probe.W3B == 0.);
  }
}

TEST_CASE("BDF CBAR types output.", "[bdf_cbar,out]" ) {

  std::ostringstream test;

  SECTION("dir code") {
    long EID(1), PID(2), GA(3), GB(4), G0(5);

    cbar probe(&EID, &PID, &GA, &GB, &G0);
    test << probe;
    CHECK(test.str() == "CBAR           1       2       3       4       5\n");
  }

  SECTION("dir code large") {
    long EID(1), PID(2), GA(3), GB(4), G0(5);

    cbar probe(&EID, &PID, &GA, &GB, &G0);
    probe.W3B = std::make_unique<double>(2.);
    test << probe;
    CHECK(test.str() ==
          "CBAR           1       2       3       4       5                \n"
          "                                                                2.000+00\n");
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