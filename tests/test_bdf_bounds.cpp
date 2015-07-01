// Copyright © 2015 by DNV GL SE

// Task      Testing the BDF boundary classes.

// Author    Berthold Höllmann <berthold.hoellmann@dnvgl.com>

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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp fil
#define CATCH_CONFIG_COLOUR_NONE    // completely disables all text colouring

#include <catch.hpp>

#ifndef _MSC_VER
#include <config.h>
#endif
#include "bdf_types.h"

using namespace bdf::type_bounds;

TEST_CASE("BDF boundary definitions (long).", "[bdf_bounds]" ) {

  num<long> *probe = new num<long>();
  num<long> *probe_min = new num<long>(new long(-12), NULL, NULL);
  num<long> *probe_max = new num<long>(NULL, new long(12), NULL);
  num<long> *probe_mm = new num<long>(new long(-12), new long(12), NULL);
  num<long> *probe_mmd = new num<long>(new long(-12), new long(12), new long(6));
  num<long> *probe_def = new num<long>(NULL, NULL, new long(1));

  SECTION("<nothing>") {
    CHECK_FALSE(probe->has_default());
    CHECK(probe->in_bounds(std::numeric_limits<long>::min()));
    CHECK(probe->in_bounds(0));
    CHECK(probe->in_bounds(std::numeric_limits<long>::max()));
  }

  SECTION("min") {
    CHECK_FALSE(probe_min->has_default());
    CHECK_FALSE(probe_min->in_bounds(std::numeric_limits<long>::min()));
    CHECK(probe_min->in_bounds(-12));
    CHECK(probe_min->in_bounds(0));
    CHECK(probe_min->in_bounds(std::numeric_limits<long>::max()));
  }

  SECTION("min class") {
    CHECK_FALSE(probe_min->has_default());
    CHECK_FALSE(probe_min->in_bounds(std::numeric_limits<long>::min()));
    CHECK(probe_min->in_bounds(-12));
    CHECK(probe_min->in_bounds(0));
    CHECK(probe_min->in_bounds(std::numeric_limits<long>::max()));
  }

  SECTION("max") {
    CHECK_FALSE(probe_max->has_default());
    CHECK_FALSE(probe_max->in_bounds(std::numeric_limits<long>::max()));
    CHECK(probe_max->in_bounds(12));
    CHECK(probe_max->in_bounds(0));
    CHECK(probe_max->in_bounds(std::numeric_limits<long>::min()));
  }

  SECTION("max class") {
    CHECK_FALSE(probe_max->has_default());
    CHECK_FALSE(probe_max->in_bounds(std::numeric_limits<long>::max()));
    CHECK(probe_max->in_bounds(12));
    CHECK(probe_max->in_bounds(0));
    CHECK(probe_max->in_bounds(std::numeric_limits<long>::min()));
  }

  SECTION("min_max") {
    CHECK_FALSE(probe_mm->has_default());
    CHECK_FALSE(probe_mm->in_bounds(std::numeric_limits<long>::min()));
    CHECK(probe_mm->in_bounds(-12));
    CHECK(probe_mm->in_bounds(0));
    CHECK(probe_mm->in_bounds(12));
    CHECK_FALSE(probe_mm->in_bounds(std::numeric_limits<long>::max()));
  }

  SECTION("min_max") {
    CHECK(probe_mmd->has_default());
        CHECK(probe_mmd->get_default() == 6);
    CHECK_FALSE(probe_mmd->in_bounds(std::numeric_limits<long>::min()));
    CHECK(probe_mm->in_bounds(-12));
    CHECK(probe_mmd->in_bounds(0));
    CHECK(probe_mm->in_bounds(12));
    CHECK_FALSE(probe_mmd->in_bounds(std::numeric_limits<long>::max()));
  }

  SECTION("<nothing> (with default)") {
    CHECK(probe_def->has_default());
    CHECK(probe_def->get_default() == 1);
  }
}

TEST_CASE("BDF boundary definitions (double).", "[bdf_bounds]" ) {

  num<double> *probe = new num<double>();
  num<double> *probe_def = new num<double>(NULL, NULL, new double(1.));

  SECTION("<nothing>") {
    CHECK_FALSE(probe->has_default());
  }

  SECTION("<nothing> (with default)") {
    CHECK(probe_def->has_default());
    CHECK(probe_def->get_default() == 1.);
  }
}

/*
  Local Variables:
  mode: c++
  ispell-local-dictionary: "english"
  c-file-style: "gl"
  indent-tabs-mode: nil
  compile-command: "make -C .. check -j 7"
  coding: utf-8
  End:
*/
