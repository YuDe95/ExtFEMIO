// Copyright © 2015 by DNV GL SE

// Purpose: Defintions for Patran CBAR cards.

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

#include <sstream>

#include "bdf/cards.h"
#include "bdf/types.h"
#include "bdf/errors.h"

using namespace std;
using namespace bdf::cards;
using bdf::types::entry_type;

const entry_type<long> cbar::_EID(
  "EID",
  bdf::type_bounds::bound<long>(make_unique<long>(1).get()));
const entry_type<long> cbar::_PID("PID");
const entry_type<long> cbar::_GA("GA");
const entry_type<long> cbar::_GB("GB");
const entry_type<double> cbar::_X1("X1");
const entry_type<long> cbar::_G0(
  "G0", bdf::type_bounds::bound<long>(make_unique<long>(1).get()));
const entry_type<double> cbar::_X2(
  "X2",
  bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
const entry_type<double> cbar::_X3(
  "X3",
  bdf::type_bounds::bound<double>(nullptr, nullptr, nullptr, true));
namespace {
  const char* initVals[8] = {
    "GGG", "BGG", "GGO", "BGO", "GOG", "BOG", "GOO", "BOO" };
  const set<std::string> OFFT_set(initVals, initVals + 8);
}
const entry_type<std::string> cbar::_OFFT(
  "OFFT", bdf::type_bounds::bound<std::string>(OFFT_set, "GGG"));

const entry_type<deque<int>> cbar::_PA("PA");
const entry_type<deque<int>> cbar::_PB("PB");
const entry_type<double> cbar::_W1A(
  "W1A",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));
const entry_type<double> cbar::_W2A(
  "W2A",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));
const entry_type<double> cbar::_W3A(
  "W3A",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));
const entry_type<double> cbar::_W1B(
  "W1B",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));
const entry_type<double> cbar::_W2B(
  "W2B",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));
const entry_type<double> cbar::_W3B(
  "W3B",
  bdf::type_bounds::bound<double>(
    nullptr, nullptr, make_unique<double>(0.).get()));

cbar::cbar(const deque<std::string> &inp) :
  card(inp) {

  auto pos = inp.rbegin();

  W1A = nullptr;
  W3B = nullptr;
  W2B = nullptr;
  W1B = nullptr;
  W3A = nullptr;
  W2A = nullptr;
  W1A = nullptr;
  PB = nullptr;
  PA = nullptr;
  OFFT = nullptr;

  switch (inp.size()-1) {
  case 16:
    W3B = bdf::types::get_val<double>(_W3B, *(pos++));
  case 15:
    W2B = bdf::types::get_val<double>(_W2B, *(pos++));
  case 14:
    W1B = bdf::types::get_val<double>(_W1B, *(pos++));
  case 13:
    W3A = bdf::types::get_val<double>(_W3A, *(pos++));
  case 12:
    W2A = bdf::types::get_val<double>(_W2A, *(pos++));
  case 11:
    W1A = bdf::types::get_val<double>(_W1A, *(pos++));
  case 10:
    PB = bdf::types::get_val<deque<int>>(_PB, *(pos++));
  case 9:
    PA = bdf::types::get_val<deque<int>>(_PA, *(pos++));
  case 8:
    OFFT = bdf::types::get_val<std::string>(_OFFT, *(pos++));
  case 7:
    X3 = bdf::types::get_val<double>(_X3, *(pos++));
  case 6:
    X2 = bdf::types::get_val<double>(_X2, *(pos++));
 case 5:
    try {
      X1 = bdf::types::get_val<double>(_X1, *pos);
      if (!X2 || !X3) {
        throw bdf_parse_error(
          "CBAR", "Incomplete direction vector.");
      }
      G0 = nullptr;
      choose_dir_code = has_DVEC;
    }
    catch (bdf_float_error) {
      G0 = bdf::types::get_val<long>(_G0, *pos);
      X1 = nullptr;
      choose_dir_code = has_DCODE;
    }
    ++pos;
    GB = bdf::types::get_val<long>(_GB, *(pos++));
    GA = bdf::types::get_val<long>(_GA, *(pos++));
    PID = bdf::types::get_val<long>(_PID, *(pos++));
    EID = bdf::types::get_val<long>(_EID, *(pos++));
    break;
  default:
    throw bdf_parse_error(
      "CBAR", "Illegal number of entries.");
  }

  if (!W3B) W3B = bdf::types::get_val<double>(_W3B, "");
  if (!W2B) W2B = bdf::types::get_val<double>(_W2B, "");
  if (!W1B) W1B = bdf::types::get_val<double>(_W1B, "");
  if (!W3A) W3A = bdf::types::get_val<double>(_W3A, "");
  if (!W2A) W2A = bdf::types::get_val<double>(_W2A, "");
  if (!W1A) W1A = bdf::types::get_val<double>(_W2A, "");
  if (!PB) PB = bdf::types::get_val<deque<int>>(_PB, "");
  if (!PA) PA = bdf::types::get_val<deque<int>>(_PA, "");
  if (!OFFT) OFFT = bdf::types::get_val<std::string>(_OFFT, "");
};

const std::ostream& cbar::operator<<(std::ostream& os) const {
  return os;
}

namespace bdf {
  namespace cards {

    std::ostream& operator<<(std::ostream &os, const cbar &card) {
      os << bdf::types::format::card("CBAR")
         << card._EID.format(*card.EID) << card._PID.format(*card.PID)
         << card._GA.format(*card.GA) << card._GB.format(*card.GB);
      if (card.choose_dir_code == card.has_DCODE) {
        os << card._G0.format(*card.G0);
        if (card.OFFT || card.PA || card.PB || card.W1A || card.W2A ||
            card.W3A || card.W1B || card.W2B || card.W3B)
          os << bdf::types::format::empty()
             << bdf::types::format::empty();
      } else
        os << card._X1.format(*card.X1) << card._X2.format(*card.X2)
           << card._X3.format(*card.X3);
      if (card.OFFT || card.PA || card.PB || card.W1A || card.W2A ||
          card.W3A || card.W1B || card.W2B || card.W3B)
        if (card.OFFT)
          os << card._OFFT.format(*card.OFFT);
        else
          os << std::endl << bdf::types::format::card("");
      else goto cont;
      if (card.PA || card.PB || card.W1A || card.W2A || card.W3A ||
          card.W1B || card.W2B || card.W3B)
        os << (card.PA ? card._PA.format(*card.PA) :
               bdf::types::format::empty());
      else goto cont;
      if (card.PB || card.W1A || card.W2A || card.W3A || card.W1B ||
          card.W2B || card.W3B)
        os << (card.PB ? card._PB.format(*card.PB) :
               bdf::types::format::empty());
      else goto cont;
      if (card.W1A || card.W2A || card.W3A || card.W1B || card.W2B ||
          card.W3B)
        os << (card.W1A ? card._W1A.format(*card.W1A) :
               bdf::types::format::empty());
      else goto cont;
      if (card.W2A || card.W3A || card.W1B || card.W2B || card.W3B)
        os << (card.W2A ? card._W2A.format(*card.W2A) :
               bdf::types::format::empty());
      else goto cont;
      if (card.W3A || card.W1B || card.W2B || card.W3B)
        os << (card.W3A ? card._W3A.format(*card.W3A) :
               bdf::types::format::empty());
      else goto cont;
      if (card.W1B || card.W2B || card.W3B)
        os << (card.W1B ? card._W1B.format(*card.W1B) :
               bdf::types::format::empty());
      else goto cont;
      if (card.W2B || card.W3B)
        os << (card.W2B ? card._W2B.format(*card.W2B) :
               bdf::types::format::empty());
      os << (card.W3B ? card._W3B.format(* card.W3B) : "");

    cont:

      os << std::endl;

      return os;
    }
  }
}

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../.. check -j 8"
// End: