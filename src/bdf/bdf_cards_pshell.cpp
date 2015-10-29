// Copyright © 2015 by DNV GL SE

// Purpose: Definitions for Nastran BDF PSHELL cards.

// Author Berthold Höllmann <berthold.hoellmann@dnvgl.com>

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

#include <memory>

using namespace std;
using namespace ::bdf;
using namespace bdf::cards;
using bdf::types::entry_type;

const entry_type<long> pshell::_PID("PID", bdf::type_bounds::bound<long>(make_unique<long>(1).get()));
const entry_type<long> pshell::_MID1(
  "MID1",
  bdf::type_bounds::bound<long>(make_unique<long>(1).get(), nullptr, nullptr, true));
const entry_type<double> pshell::_T(
  "T", bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
const entry_type<long> pshell::_MID2(
  "MID2",
  bdf::type_bounds::bound<long>(make_unique<long>(-1).get(), nullptr, nullptr, true));
const entry_type<double> pshell::_12I_T__3(
  "12I/T**3",
  bdf::type_bounds::bound<double>(make_unique<double>(0.).get(), nullptr,
              make_unique<double>(1.).get()));
const entry_type<long> pshell::_MID3(
  "MID3",
  bdf::type_bounds::bound<long>(make_unique<long>(1).get(), nullptr, nullptr, true));
const entry_type<double> pshell::_TS_T(
  "TS/T", bdf::type_bounds::bound<double>(make_unique<double>(0.).get(), nullptr,
                      make_unique<double>(.833333).get()));
const entry_type<double> pshell::_NSM(
  "NSM", bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
const entry_type<double> pshell::_Z1(
  "Z1", bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
const entry_type<double> pshell::_Z2(
  "Z2", bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
const entry_type<long> pshell::_MID4(
  "MID4", bdf::type_bounds::bound<long>(make_unique<long>(1).get(),
                                        nullptr, nullptr, true));

pshell::pshell(const deque<std::string> &inp) : card(inp) {

  auto pos = inp.rbegin();

  MID4 = nullptr;
  Z2 = nullptr;
  Z1 = nullptr;
  NSM = nullptr;
  TS_T = nullptr;
  MID3 = nullptr;

  switch (inp.size()-1) {
  case 16:
    ++pos;
  case 15:
    ++pos;
  case 14:
    ++pos;
  case 13:
    ++pos;
  case 12:
    ++pos;
  case 11:
    MID4 = bdf::types::get_val<long>(_MID4, *(pos++));
  case 10:
    Z2 = bdf::types::get_val<double>(_Z2, *(pos++));
  case 9:
    Z1 = bdf::types::get_val<double>(_Z1, *(pos++));
  case 8:
    NSM = bdf::types::get_val<double>(_NSM, *(pos++));
  case 7:
    TS_T = bdf::types::get_val<double>(_TS_T, *(pos++));
  case 6:
    MID3 = bdf::types::get_val<long>(_MID3, *(pos++));
  case 5:
    x12I_T__3 = bdf::types::get_val<double>(_12I_T__3, *(pos++));
    MID2 = bdf::types::get_val<long>(_MID2, *(pos++));
    T = bdf::types::get_val<double>(_T, *(pos++));
    MID1 = bdf::types::get_val<long>(_MID1, *(pos++));
    PID = bdf::types::get_val<long>(_PID, *pos);
    break;
  default:
    throw bdf_parse_error("PSHELL", "Illegal number of entries.");
  }

  TS_T = bdf::types::get_val<double>(_TS_T, "");
}

const std::ostream& pshell::operator << (std::ostream& os) const {
  throw bdf_error("can't write cbeam.");
  return os;
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. check -j 8"
// End: