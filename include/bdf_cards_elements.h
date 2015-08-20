// Copyright © 2015 by DNV GL SE

// Purpose: Definitions for BDF element type cards.

// Author Berthold Höllmann <berthold.hoellmann@dnvgl.com>

// ID: $Id$

#if !defined _BERHOL20150714_BDF_CARDS_ELEMENTS
#define _BERHOL20150714_BDF_CARDS_ELEMENTS

#include <memory>

namespace bdf {

  using namespace types;

  namespace cards {

    // Base class for `ctria3' and `cquad4'.
    class bdf_shell : public bdf_card {

    protected:

      static bdf_int _EID;
      static bdf_int _PID;
      static bdf_int _G1;
      static bdf_int _G2;
      static bdf_int _G3;
      static bdf_int _G4;
      static bdf_int _MCID;
      static bdf_float _THETA;
      static bdf_float _ZOFFS;
      static bdf_int _TFLAG;
      static bdf_float _T1;
      static bdf_float _T2;
      static bdf_float _T3;
      static bdf_float _T4;

      DllExport bdf_shell(const ::std::deque<::std::string> &inp) :
        bdf_card(inp) {};

    public:

      typedef enum {has_MCID, has_THETA} CHOOSE_MCID_THETA;

      CHOOSE_MCID_THETA choose_mcid_theta;

      ::std::unique_ptr<long> EID;
      ::std::unique_ptr<long> PID;
      ::std::unique_ptr<long> G1;
      ::std::unique_ptr<long> G2;
      ::std::unique_ptr<long> G3;
      ::std::unique_ptr<long> G4;
      ::std::unique_ptr<long> MCID;
      ::std::unique_ptr<double> THETA;
      ::std::unique_ptr<double> ZOFFS;
      ::std::unique_ptr<long> TFLAG;
      ::std::unique_ptr<double> T1;
      ::std::unique_ptr<double> T2;
      ::std::unique_ptr<double> T3;
      ::std::unique_ptr<double> T4;
    };

/*
Handle Nastran Bulk CTRIA3 entries.

Format:
.......

+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
| 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10 |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
| CTRIA3| EID   | PID   | G1    | G2    | G3    | THETA | ZOFFS |       |    |
|       |       |       |       |       |       | or    |       |       |    |
|       |       |       |       |       |       | MCID  |       |       |    |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
|       |       | TFLAG | T1    | T2    | T3    |       |       |       |    |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+

Description:
............

``EID``
  Element identification number. (Integer > 0)
``PID``
  Property identification number of a ``PSHELL``, ``PCOMP`` or
  ``PLPLANE`` entry. (Integer > 0; Default = ``EID``)
``Gi``
  Grid point identification numbers of connection points. (Integers > 0,
  all unique)

``THETA``
  Material property orientation angle in degrees. ``THETA`` is ignored
  for hyperelastic elements. (Real; Default = 0.0)
``MCID``
  Material coordinate system identification number. The x-axis of the
  material coordinate system is determined by projecting the x-axis of
  the ``MCID`` coordinate system (defined by the ``CORDij`` entry or
  zero for the basic coordinate system) onto the surface of the
  element. ``MCID`` is ignored for hyperelastic elements. (Integer >
  0; if blank, then ``THETA`` = 0.0 is assumed.)
``ZOFFS``
  Offset from the surface of grid points to the element reference
  plane. ``ZOFFS`` is ignored for hyperelastic elements. (Real)
``TFLAG``
  An integer flag, signifying the meaning of the ``Ti``
  values. (Integer 0, 1, or blank)
``Ti``
  Membrane thickness of element at grid points G1 through G4. If
  ``TFLAG`` zero or blank, then ``Ti`` are actual user specified
  thickness. (Real > 0.0 or blank, not all zero.) If ``TFLAG`` one,
  then the ``Ti`` are fraction relative to the ``T`` value of the
  ``PSHELL``. (Real > 0.0 or blank; not all zero. Default = 1.0)
  ``Ti`` are ignored for hyperelastic elements.
 */

    class ctria3 : public bdf_shell {
      // NASTRAN ``BDF`` ``CTRIA3`` representation.

    public:

      DllExport ctria3(const ::std::deque<::std::string> &);

      DllExport ::bdf::cards::types card(void) { return CTRIA3; };

    };

/*
Handle Nastran Bulk CQUAD4 entries.

Format:
.......

+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
| 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 10 |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
|CQUAD4 | EID   | PID   | G1    | G2    | G3    | G4    | THETA | ZOFFS |    |
|       |       |       |       |       |       |       | or    |       |    |
|       |       |       |       |       |       |       | MCID  |       |    |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+
|       |TFLAG  | T1    | T2    | T3    | T4    |       |       |       |    |
+-------+-------+-------+-------+-------+-------+-------+-------+-------+----+

Description:
............

``EID``
  Element identification number. (Integer > 0)
``PID``
  Property identification number of a ``PSHELL``, ``PCOMP``, or
  ``PLPLANE`` entry. (Integer > 0; Default = ``EID``)
``Gi``
  Grid point identification numbers of connection points. (Integers
  > 0, all unique.)
``THETA``
  Material property orientation angle in degrees. ``THETA`` is
  ignored for hyperelastic elements. (Real; Default = 0.0)
``MCID``
  Material coordinate system identification number. The x-axis of
  the material coordinate system is determined by projecting the
  x-axis of the ``MCID`` coordinate system (defined by the
  ``CORDij`` entry or zero for the basic coordinate system) onto the
  surface of the element. ``MCID`` is ignored for hyperelastic
  elements. (Integer > 0; If blank, then ``THETA`` = 0.0 is
  assumed.)
``ZOFFS``
  Offset from the surface of grid points to the element reference
  plane.  ``ZOFFS`` is ignored for hyperelastic elements. (Real)
``TFLAG``
  An integer flag, signifying the meaning of the Ti values. (Integer
  0, 1, or blank)
``Ti``
  Membrane thickness of element at grid points ``G1`` through
  ``G4``. If ``TFLAG`` is zero or blank, then ``Ti`` are actual user
  specified thicknesses.  (Real > 0.0 or blank, not all zero.) If
  ''TFLAG`` is one, then the ``Ti`` are fractions relative to the
  ``T`` value of the ``PSHELL``.  (Real > 0.0 or blank, not all
  zero. Default = 1.0) ``Ti`` are ignored for hyperelastic elements.
 */

    class cquad4 : public bdf_shell {
      // NASTRAN ``BDF`` ``CQUAD4`` representation.

    public:

      DllExport cquad4(const ::std::deque<::std::string> &);

      DllExport ::bdf::cards::types card(void) { return CQUAD4; };

    };

    /*
Handle Nastran Bulk CBEAM entries.

Format:
.......

+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
| 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9      | 10 |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
| CBEAM | EID   | PID   | GA    | GB    | X1    | X2    | X3    |OFFT/BIT|    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
|       |PA     | PB    | W1A   | W2A   | W3A   | W1B   | W2B   | W3B    |    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
|       |SA     | SB    |       |       |       |       |       |        |    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+

Alternate Format:
.................

+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
| 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9      | 10 |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
| CBEAM | EID   | PID   | GA    | GB    | G0    |       |       |OFFT/BIT|    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
|       |PA     | PB    | W1A   | W2A   | W3A   | W1B   | W2B   | W3B    |    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+
|       |SA     | SB    |       |       |       |       |       |        |    |
+-------+-------+-------+-------+-------+-------+-------+-------+--------+----+

Description:
............

``EID``
  Unique element identification number. (0 < Integer < 100,000,000)
``PID``
  Property identification number of ``PBEAM``, ``PBCOMP`` or
  ``PBEAML`` entry. (Integer > 0; Default = ``EID``)
``GA``, ``GB``
  Grid point identification numbers of connection points. (Integer > 0)
``X1``, ``X2``, ``X3``
  Components of orientation vector , from ``GA``, in the displacement
  coordinate system at ``GA`` (default), or in the basic coordinate
  system. (Real)
``G0``
  Alternate method to supply the orientation vector using grid point
  ``G0``. Direction of is from ``GA`` to G0. is then transferred to
  End ``A``. (Integer > 0; or ``GB``)
``OFFT``
  Offset vector interpretation flag. (Character or blank)
``BIT``
  Built-in twist of the cross-sectional axes about the beam axis at
  end ``B`` relative to end ``A``. For beam p-elements only. (Real;
  Default = 0.0)
``PA``, ``PB``
  Pin flags for beam ends ``A`` and ``B``, respectively; used to
  remove connections between the grid point and selected
  degrees-offreedom of the beam. The degrees-of-freedom are defined in
  the element’s coordinate system and the pin flags are applied at the
  offset ends of the beam. The beam must have stiffness associated
  with the ``PA`` and ``PB`` degrees-of-freedom to be released by the
  pin flags. For example, if ``PA`` = 4, the ``PBEAM`` entry must have
  a nonzero value for ``J``, the torsional stiffness. (Up to five of
  the unique Integers 1 through 6 with no embedded blanks.)  Pin flags
  are not allowed for beam p-elements.
``W1A``, ``W2A``, ``W3A``, ``W1B``, ``W2B``, ``W3B``
  Components of offset vectors from the grid points to the end points
  of the axis of the shear center. (Real; Default = 0.0)
``SA``, ``SB``
  Scalar or grid point identification numbers for the ends ``A`` and
  ``B``, respectively. The degrees-of-freedom at these points are the
  warping variables . ``SA`` and ``SB`` cannot be specified for beam
  p-elements. (Integers > 0 or blank)
*/

    class cbeam : public bdf_card {

    private:

      static bdf_int _EID;
      static bdf_int _PID;
      static bdf_int _GA;
      static bdf_int _GB;
      static bdf_float _X1;
      static bdf_int _G0;
      static bdf_float _X2;
      static bdf_float _X3;
      static bdf_float _BIT;
      static bdf_str _OFFT;
      static bdf_list<int> _PA;
      static bdf_list<int> _PB;
      static bdf_float _W1A;
      static bdf_float _W2A;
      static bdf_float _W3A;
      static bdf_float _W1B;
      static bdf_float _W2B;
      static bdf_float _W3B;
      static bdf_int _SA;
      static bdf_int _SB;

    public:

      DllExport cbeam(const ::std::deque<::std::string> &inp);

      DllExport ::bdf::cards::types card(void) { return CBEAM; };

      typedef enum {has_DVEC, has_DCODE} CHOOSE_DIR_CODE;
      CHOOSE_DIR_CODE choose_dir_code;

      typedef enum {has_OFFT, has_BIT} CHOOSE_OFFT_BIT;
      CHOOSE_OFFT_BIT choose_offt_bit;

      ::std::unique_ptr<long> EID;
      ::std::unique_ptr<long> PID;
      ::std::unique_ptr<long> GA;
      ::std::unique_ptr<long> GB;
      ::std::unique_ptr<double> X1;
      ::std::unique_ptr<long> G0;
      ::std::unique_ptr<double> X2;
      ::std::unique_ptr<double> X3;
      ::std::unique_ptr<double> BIT;
      ::std::unique_ptr<::std::string> OFFT;
      ::std::unique_ptr<::std::deque<int>> PA;
      ::std::unique_ptr<::std::deque<int>> PB;
      ::std::unique_ptr<double> W1A;
      ::std::unique_ptr<double> W2A;
      ::std::unique_ptr<double> W3A;
      ::std::unique_ptr<double> W1B;
      ::std::unique_ptr<double> W2B;
      ::std::unique_ptr<double> W3B;
      ::std::unique_ptr<long> SA;
      ::std::unique_ptr<long> SB;

    };

  }
}

#endif // _BERHOL20150714_BDF_CARDS_ELEMENTS

// Local Variables:
// mode: c++
// ispell-local-dictionary: "english"
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C .. check -j 8"
// coding: utf-8
// End:
