// Copyright © 2015 by DNV GL SE

// Purpose: Testing the BDF ENDDATA card class.

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
#include "bdf/errors.h"

using namespace ::std;
using namespace ::dnvgl::extfem::bdf;
using namespace ::dnvgl::extfem::bdf::cards;

CATCH_TRANSLATE_EXCEPTION( errors::error& ex ) {
  return Catch::toString( ex() );
}

TEST_CASE("BDF ENDDATA definitions. (Small Field Format)",
          "[bdf_ENDDATA]" ) {

  SECTION("enddata read") {
    ::std::deque<string> data;
    data.push_back(
      "ENDDAT                                                                  \n");

    ::std::deque<string> lines = card::card_split(data);
    enddata probe(lines);
  }
}

TEST_CASE("BDF ENDDATA types output.", "[bdf_enddata,out]" ) {

  std::ostringstream test;
  // enddata probe();
  // test << probe;
  test << enddata();

  SECTION("output") {
    CHECK(test.str() == "ENDDATA \n");
  }
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. doxyfile.stamp check -j 8"
// End: