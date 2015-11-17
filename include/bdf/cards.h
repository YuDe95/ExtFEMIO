// Copyright © 2015 by DNV GL SE

// Classes for the different Nastran BDF cards.

// Author Berthold Höllmann <berthold.hoellmann@dnvgl.com>

// ID: $Id$

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined _BERHOL20150630_BDF_CARDS
#define _BERHOL20150630_BDF_CARDS

#include <deque>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <memory>

#include "extfem_misc.h"

#include <my_c++14.h>

#ifndef _MSC_VER
#include <config.h>
#endif
#include "bdf/types.h"

namespace dnvgl {
  namespace extfem {
    namespace bdf {
      namespace cards {

        typedef enum {
          /// undknown card
          UNKNOWN,
          /// Grid Point
          GRID,
          /// Isotropic Material Property Definition
          MAT1,
          /// Triangular Plate Element Connection
          CTRIA3,
          /// Fully Nonlinear Axisymmetric Element
          CQUAD4,
          /// Shell Element Property
          PSHELL,
          /// Beam Element Connection
          CBEAM,
          /// Beam Property
          PBEAM,
          /// Beam Cross-Section Property
          PBEAML,
          /// Simple Beam Element Connection
          CBAR,
          /// Simple Beam Property
          PBAR,
          /// Simple Beam Cross-Section Property
          PBARL,
          /// Rod Element Connection
          CROD,
          /// Rod Property
          PROD,
          /// Element Force Output or Particle Velocity Request
          FORCE,
          /// Static Moment
          MOMENT,
          /// External Static Load Set Selection
          LOAD,
          /// Bulk Data Delimiter
          ENDDATA,
          /// base class for beam/bar property description
          BEAM_BASE,
          /// base class for bar property description
          BAR_PROP,
          /// base class for beam property description
          BEAM_PROP,
        } types;

        typedef ::std::pair<::dnvgl::extfem::bdf::types::base*, void*> format_entry;

        class card {

        private:

          // two character strings for continuation lines in Free Form
          // Format cards.
          static const ::std::set<char> free_form_cont;

          static const ::std::map<::std::string, types> cardtype_map;

        protected:

          static ::dnvgl::extfem::bdf::types::empty empty;

          static ::dnvgl::extfem::bdf::types::card head;

          ::std::string format_outlist(
            const ::std::deque<::std::unique_ptr<format_entry>>&) const;

        public:

          friend
          ::std::unique_ptr<format_entry>
          format(const ::std::unique_ptr<::dnvgl::extfem::bdf::types::card> &formatter);

          friend
          ::std::unique_ptr<format_entry>
          format(const ::std::unique_ptr<::dnvgl::extfem::bdf::types::empty> &formatter);

          template <class T> friend
          ::std::unique_ptr<format_entry>
          format(const ::dnvgl::extfem::bdf::types::entry_type<T> &formatter,
                 const ::std::unique_ptr<T> &val);

          DllExport static ::std::deque<::std::string>
          card_split(::std::deque<::std::string> const &);

          DllExport card (const ::std::deque<::std::string> &);
          DllExport card ();

          virtual const ::dnvgl::extfem::bdf::cards::types card_type(void) const = 0;
          virtual const ::std::ostream& operator<<(::std::ostream&) const = 0;
        };

        inline ::std::unique_ptr<format_entry>
        format(const ::dnvgl::extfem::bdf::types::card &formatter) {
          return ::std::make_unique<format_entry>(
            (::dnvgl::extfem::bdf::types::card*)&formatter, (void*)NULL);
        };

        inline ::std::unique_ptr<format_entry>
        format(const ::dnvgl::extfem::bdf::types::empty &formatter) {
          return ::std::make_unique<format_entry>(
            (::dnvgl::extfem::bdf::types::base*)&formatter, (void*)NULL);
        };

        template <class T>
        inline ::std::unique_ptr<format_entry>
        format(const ::dnvgl::extfem::bdf::types::entry_type<T> &formatter,
               const ::std::unique_ptr<T> &val) {
          return ::std::make_unique<format_entry>(
            (::dnvgl::extfem::bdf::types::base*)&formatter,
            (void*)val.get());
        };

        class unknown : public card {

        public:

          DllExport unknown(const ::std::deque<::std::string> &inp) :
            card(inp), content(inp) {};

          DllExport const ::dnvgl::extfem::bdf::cards::types card_type(void) const { return UNKNOWN; }

          ::std::deque<::std::string> content;

          DllExport const ::std::ostream& operator << (::std::ostream& os) const {
            throw errors::error("can't write UNKNOWN.");
            return os;
          };
        };

        /// # Handle Nastran Bulk `ENDDATA` entries.
/**
Bulk Data Delimiter

Designates the end of the Bulk Data Section.

## Format

| 1        | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| -------- | - | - | - | - | - | - | - | - | -- |
| ENDDATA  |   |   |   |   |   |   |   |   |    |
*/
        class enddata : public card {

        private:

          static ::dnvgl::extfem::bdf::types::card head;

        public:

          DllExport enddata(const ::std::deque<::std::string> &inp) :
            card(inp) {};

          DllExport enddata() : card() {};

          DllExport const ::dnvgl::extfem::bdf::cards::types card_type(void) const { return ENDDATA; };

          DllExport const ::std::ostream& operator<< (::std::ostream& os) const {
            os << this;
            return os;
          };
          DllExport friend ::std::ostream& operator<<(::std::ostream &os, const enddata &card) {

            std::deque<std::unique_ptr<format_entry>> entries;

            entries.push_back(format(enddata::head));

            os << card.format_outlist(entries) << std::endl;

            return os;
          }
        };

        /// # Handle Nastran Bulk `GRID` entries.
/**
Grid Point

Defines the location of a geometric grid point, the directions of its
displacement, and its permanent single-point constraints.

## Format

| 1     | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9    | 10 |
| ----- | -- | -- | -- | -- | -- | -- | -- | ---- | -- |
| GRID  | ID | CP | X1 | X2 | X3 | CD | PS | SEID |    |

## Description

- `ID` : Grid point identification number. (0 < Integer < 100000000)

- `CP` : Identification number of coordinate system in which the
  location of the grid point is defined. (Integer > 0 or blank)

- `X1`, `X2`, `X3` : Location of the grid point in coordinate system
  CP. (Real; Default = 0.0)

- `CD` : Identification number of coordinate system in which the
  displacements, degrees-of-freedom, constraints, and solution deques
  are defined at the grid point. (Integer > -1 or blank)

- `PS` : Permanent single-point constraints associated with the grid
  point. (Any of the Integers 1 through 6 with no embedded blanks, or
  blank.)

- `SEID` : Superelement identification number. (Integer > 0; Default =
  0)
*/
        class grid : public card {

        private:

          static ::std::unique_ptr<::dnvgl::extfem::bdf::types::base> head(void);

          static const ::dnvgl::extfem::bdf::types::entry_type<long> _ID;
          static const ::dnvgl::extfem::bdf::types::entry_type<long> _CP;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _X1;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _X2;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _X3;
          static const ::dnvgl::extfem::bdf::types::entry_type<long> _CD;
          static const ::dnvgl::extfem::bdf::types::entry_type<::std::deque<int>> _PS;
          static const ::dnvgl::extfem::bdf::types::entry_type<long> _SEID;

        public:

          ::std::unique_ptr<long> ID;
          ::std::unique_ptr<long> CP;
          ::std::unique_ptr<double> X1;
          ::std::unique_ptr<double> X2;
          ::std::unique_ptr<double> X3;
          ::std::unique_ptr<long> CD;
          ::std::unique_ptr<::std::deque<int>> PS;
          ::std::unique_ptr<long> SEID;

          DllExport grid(const ::std::deque<::std::string> &);
          DllExport grid(long &ID, long &CP, double &X1, double &X2, double &X3);

          DllExport const ::dnvgl::extfem::bdf::cards::types card_type(void) const { return GRID; };

          DllExport const ::std::ostream& operator << (::std::ostream& os) const;
        };

        /// # Handle Nastran Bulk `MAT1` entries.
/**
Isotropic Material Property Definition

Defines the material properties for linear isotropic materials.

## Format

| 1    | 2   | 3  | 4  | 5     | 6   | 7 | 8    | 9  | 10 |
| ---- | --- | -- | -- | ----- | --- | - | ---- | -- | -- |
| MAT1 | MID | E  | G  | NU    | RHO | A | TREF | GE |    |
|      | ST  | SC | SS | MCSID |     |   |      |    |    |

## Description

- `MID` : Material identification number. (Integer > 0)

- `E` : Young’s modulus. (Real > 0.0 or blank)

- `G` : Shear modulus. (Real > 0.0 or blank)

- `NU` : Poisson’s ratio. (-1.0 < Real < 0.5 or blank)

- `RHO` : Mass density. See Remark 5. (Real)

- `A` : Thermal expansion coefficient. (Real)

- `TREF` : Reference temperature for the calculation of thermal loads,
  or a temperature-dependent thermal expansion coefficient. (Real;
  Default = 0.0 if A is specified.)

- `GE` : Structural element damping coefficient. (Real)

- `ST`, `SC`, `SS` : Stress limits for tension, compression, and shear
  are optionally supplied, used only to compute margins of safety in
  certain elements; and have no effect on the computational
  procedures. (Real > 0.0 or blank)

- `MCSID` : Material coordinate system identification number. Used
  only for `PARAM,CURV` processing. (Integer > 0 or blank)
*/

        class mat1 : public card {
          // NASTRAN `BDF` `MAT1` representation.

        private:

          static ::std::unique_ptr<::dnvgl::extfem::bdf::types::base> head(void);

          static const ::dnvgl::extfem::bdf::types::entry_type<long> _MID;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _E;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _G;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _NU;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _RHO;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _A;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _TREF;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _GE;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _ST;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _SC;
          static const ::dnvgl::extfem::bdf::types::entry_type<double> _SS;
          static const ::dnvgl::extfem::bdf::types::entry_type<long> _MCSID;

        public:

          ::std::unique_ptr<long> MID;
          ::std::unique_ptr<double> E;
          ::std::unique_ptr<double> G;
          ::std::unique_ptr<double> NU;
          ::std::unique_ptr<double> RHO;
          ::std::unique_ptr<double> A;
          ::std::unique_ptr<double> TREF;
          ::std::unique_ptr<double> GE;
          ::std::unique_ptr<double> ST;
          ::std::unique_ptr<double> SC;
          ::std::unique_ptr<double> SS;
          ::std::unique_ptr<long> MCSID;

          DllExport mat1(const ::std::deque<::std::string> &);

          DllExport const ::dnvgl::extfem::bdf::cards::types card_type(void) const { return MAT1; };

          DllExport const ::std::ostream& operator << (::std::ostream& os) const;
        };
      }
    }
  }
}

#include "bdf/cards_elements.h"
#include "bdf/cards_properties.h"
#include "bdf/cards_loads.h"

namespace dnvgl {
  namespace extfem {
    namespace bdf {
      namespace cards {
        DllExport ::std::unique_ptr<card> dispatch(const ::std::deque<::std::string> &);
      }
    }
  }
}

#endif // _BERHOL20150630_BDF_CARDS

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../.. doxyfile.stamp check -j 8"
// coding: utf-8
// End:
