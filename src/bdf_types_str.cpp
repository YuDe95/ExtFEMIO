// Copyright © 2015 by DNV GL SE

// Purpose: Processing of string entries from Nastran BDF files.

// Author Berthold Höllmann <berthold.hoellmann@dnvgl.com>

// ID:
namespace {
  const char  cID[]
#ifdef __GNUC__
  __attribute__ ((__unused__))
#endif
    = "@(#) $Id$";
}

#include "bdf_types.h"

using namespace std;
using namespace bdf::types;
using namespace bdf::type_bounds;
using namespace bdf::string;

entry_type<::std::string>::entry_type(::std::string name) :
  ::bdf::types::base(name), bounds(::bdf::type_bounds::bound<::std::string>()) {}

entry_type<::std::string>::entry_type(::std::string name, ::bdf::type_bounds::bound<::std::string> bounds) :
  ::bdf::types::base(name), bounds(bounds) {}

::std::string
*entry_type<::std::string>::operator() (const ::std::string &inp) const {
  std::string sval = bdf::string::string(inp).trim();

  if (sval.length() == 0)
    sval = bounds.get_default();

  if (!bounds.is_allowed(sval))
    throw bdf_str_error(name, "!" + sval + "! Value not in list of allowed values.");

  return new ::std::string(sval);
}


// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. check -j 8"
// End: