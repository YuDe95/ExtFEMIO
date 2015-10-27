// Copyright © 2015 by DNV GL SE

// Definitions for Nastran Bulk data entry types.

// Author    Berthold Höllmann <berthold.hoellmann@dnvgl.com>

#include "stdafx.h"

// ID:
namespace {
  const char  cID[]
#ifdef __GNUC__
  __attribute__ ((__unused__))
#endif
    = "@(#) $Id$";
}

#include <sstream>

#ifdef __GNUC__
#include <boost/regex.hpp>
using boost::regex;
using boost::smatch;
using boost::regex_constants::ECMAScript;
#else
#include <regex>
using std::regex;
using std::smatch;
using std::regex_constants::ECMAScript;
#endif

#include "bdf/types.h"

using namespace std;

using namespace bdf::types;

entry_type<double>::entry_type(std::string name) :
  bdf::types::base(name), bounds(bdf::type_bounds::bound<double>()) {};

entry_type<double>::entry_type(std::string name, bdf::type_bounds::bound<double> bounds) :
  bdf::types::base(name), bounds(bounds) {};

const regex entry_type<double>::float_exp_re(
  "([\\+-]?[.[:digit:]]+)([+-][[:digit:]]+)");

const regex entry_type<double>::float_re(
  "([\\+-]?((0|([1-9][[:digit:]]*))?[.][[:digit:]]*)|"
  "[.][[:digit:]]+)(((E[+-]?)|[+-])[[:digit:]]+)?",
  ECMAScript);

const regex entry_type<double>::float_lead_dot(
  "^[\\+-]?[.][[:digit:]]+", ECMAScript);

// Convert string to float
double *entry_type<double>::operator() (const std::string &inp) const {
  auto *value = new double();
  auto sval = bdf::string::string(inp).trim().upper();

  if (sval.length() == 0) {
    if (this->bounds.does_allow_empty())
      return nullptr;
    if (!this->bounds.has_default())
      throw bdf_float_error(name, "empty entry without default");
    *value = this->bounds.get_default();
  } else {
    if (! regex_match(sval, float_re)) {
      std::string msg("illegal input, no float");
      throw bdf_float_error(name, msg + "; !" + sval + "!");
    }

    smatch m;

    if (regex_search(sval, m, float_exp_re))
      sval = m[1].str() + "E" + m[2].str();

    if (regex_match(sval, float_lead_dot)) {
        auto pos = sval.find('.');
        sval.insert(pos, 1, '0');
    }

    istringstream conv(sval);
    conv.imbue(locale("C"));
    conv >> *value;
  }
  if (!this->bounds.in_bounds(value))
    throw bdf_float_error(name, "boundary condition violated");
  return value;
}

/*
  Local Variables:
  mode: c++
  ispell-local-dictionary: "english"
  c-file-style: "gl"
  indent-tabs-mode: nil
  compile-command: "make -C .. check -j 8"
  coding: utf-8
  End:
*/