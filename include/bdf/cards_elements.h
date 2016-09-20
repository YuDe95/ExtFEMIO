/**
   \file bdf/cards_elements.h
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Definitions for BDF element type cards.

   Detailed description
*/

// ID: $Id$

#if !defined _BDF_CARDS_ELEMENTS_H_
#define _BDF_CARDS_ELEMENTS_H_

#include <memory>

namespace dnvgl {
   namespace extfem {
      namespace bdf {

         using types::entry_value;
         using types::entry_type;

         namespace cards {
            namespace __base {

               /// Base class for `ctria3` and `cquad4`.
               class shell : public card {

               protected:

                  static const entry_type<long> form_EID;
                  static const entry_type<long> form_PID;
                  static const entry_type<long> form_G1;
                  static const entry_type<long> form_G2;
                  static const entry_type<long> form_G3;
                  static const entry_type<long> form_G4;
                  static const entry_type<long> form_MCID;
                  static const entry_type<double> form_THETA;
                  static const entry_type<double> form_ZOFFS;
                  static const entry_type<long> form_TFLAG;
                  static const entry_type<double> form_T1;
                  static const entry_type<double> form_T2;
                  static const entry_type<double> form_T3;
                  static const entry_type<double> form_T4;

                  shell(const std::list<std::string> &);

               public:

                  typedef enum {has_MCID, has_THETA} CHOOSE_MCID_THETA;

                  CHOOSE_MCID_THETA choose_mcid_theta;

                  /** Element identification number. (Integer > 0)
                   */
                  entry_value<long> EID;
                  /** Property identification number of a `PSHELL`,
                      `PCOMP` or `PLPLANE` entry. (Integer > 0; Default =
                      `EID`)
                  */
                  entry_value<long> PID;
                  /** Grid point identification numbers of first
                      connection point. (Integers > 0, all unique)
                  */
                  entry_value<long> G1;
                  /** Grid point identification numbers of second
                      connection point. (Integers > 0, all unique)
                  */
                  entry_value<long> G2;
                  /** Grid point identification numbers of third
                      connection point. (Integers > 0, all unique)
                  */
                  entry_value<long> G3;
                  /** Grid point identification numbers of fourth
                      connection point. (Integers > 0, all unique)
                  */
                  entry_value<long> G4;
                  /** Material property orientation angle in degrees.
                      `THETA` is ignored for hyperelastic elements.
                      (Real; Default = 0.0)
                  */
                  entry_value<double> THETA;
                  /** Material coordinate system identification number.
                      The x-axis of the material coordinate system is
                      determined by projecting the x-axis of the `MCID`
                      coordinate system (defined by the `CORDij` entry or
                      zero for the basic coordinate system) onto the
                      surface of the element. `MCID` is ignored for
                      hyperelastic elements. (Integer > 0; if blank, then
                      `THETA` = 0.0 is assumed.)
                  */
                  entry_value<long> MCID;
                  /** Offset from the surface of grid points to the
                      element reference plane. `ZOFFS` is ignored for
                      hyperelastic elements. (Real)
                  */
                  entry_value<double> ZOFFS;
                  /** An integer flag, signifying the meaning of the `Ti`
                      values. (Integer 0, 1, or blank)
                  */
                  entry_value<long> TFLAG;
                  /** Membrane thickness of element at grid point G1. If
                      `TFLAG` zero or blank, then `T1` is actual user
                      specified thickness. (Real > 0.0 or blank, not all
                      zero.) If `TFLAG` one, then the `T1` is fraction
                      relative to the `T` value of the `PSHELL`. (Real >
                      0.0 or blank; not all zero. Default = 1.0) `T1` is
                      ignored for hyperelastic elements.
                  */
                  entry_value<double> T1;
                  /** Membrane thickness of element at grid point G2. If
                      `TFLAG` zero or blank, then `T2` is actual user
                      specified thickness. (Real > 0.0 or blank, not all
                      zero.) If `TFLAG` one, then the `T2` is fraction
                      relative to the `T` value of the `PSHELL`. (Real >
                      0.0 or blank; not all zero. Default = 1.0) `T2` is
                      ignored for hyperelastic elements.
                  */
                  entry_value<double> T2;
                  /** Membrane thickness of element at grid point G3. If
                      `TFLAG` zero or blank, then `T3` is actual user
                      specified thickness. (Real > 0.0 or blank, not all
                      zero.) If `TFLAG` one, then the `T3` is fraction
                      relative to the `T` value of the `PSHELL`. (Real >
                      0.0 or blank; not all zero. Default = 1.0) `T3` is
                      ignored for hyperelastic elements.
                  */
                  entry_value<double> T3;
                  /** Membrane thickness of element at grid point G4. If
                      `TFLAG` zero or blank, then `T4` is actual user
                      specified thickness. (Real > 0.0 or blank, not all
                      zero.) If `TFLAG` one, then the `T4` is fraction
                      relative to the `T` value of the `PSHELL`. (Real >
                      0.0 or blank; not all zero. Default = 1.0) `T4` is
                      ignored for hyperelastic elements.
                  */
                  entry_value<double> T4;

               protected:

                  const card *operator() (
                     long const *EID, long const *PID,
                     long const *G1, long const *G2,
                     long const *G3, long const *G4,
                     double const *THETA,
                     double const *ZOFFS,
                     long const *TFLAG,
                     double const *T1, double const *T2,
                     double const *T3, double const *T4);

                  const card *operator() (
                     long const *EID, long const *PID,
                     long const *G1, long const *G2,
                     long const *G3, long const *G4,
                     long const *MCID,
                     double const *ZOFFS, long const *TFLAG,
                     double const *T1, double const *T2,
                     double const *T3, double const *T4);

                  using card::put;
                  using card::read;
               };
            }
/// Handle Nastran Bulk `CTRIA3` entries.
/** # Triangular Plate Element Connection

    Defines an isoparametric membrane-bending or plane strain triangular
    plate element.

    # Format

    | 1        | 2     | 3       | 4    | 5    | 6    | 7                 | 8       | 9 | 10 |
    | -------- | ----- | ------- | ---- | ---- | ---- | ----------------- | ------- | - | -- |
    | `CTRIA3` | `EID` | `PID`   | `G1` | `G2` | `G3` | `THETA` or `MCID` | `ZOFFS` |   |    |
    |          |       | `TFLAG` | `T1` | `T2` | `T3` |                   |         |   |    |
*/
            class ctria3 : public __base::shell {

            private:

               static bdf::types::card head;

            public:

               ctria3(const std::list<std::string> &);

               const dnvgl::extfem::bdf::cards::types
               card_type(void) const;

               virtual void read(const std::list<std::string> &);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *G1, long const *G2, long const *G3,
                  double const *THETA=nullptr,
                  double const *ZOFFS=nullptr,
                  long const *TFLAG=nullptr,
                  double const *T1=nullptr, double const *T2=nullptr,
                  double const *T3=nullptr, double const *T4=nullptr);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *G1, long const *G2, long const *G3,
                  long const *MCID,
                  double const *ZOFFS=nullptr,
                  long const *TFLAG=nullptr,
                  double const *T1=nullptr, double const *T2=nullptr,
                  double const *T3=nullptr, double const *T4=nullptr);

            private:

               using __base::shell::put;

               virtual void collect_outdata(
                  std::list<std::unique_ptr<format_entry> >&) const;
            };

/// Handle Nastran Bulk `CQUAD4` entries.
/** # Quadrilateral Plate Element Connection

    Defines an isoparametric membrane-bending or plane strain
    quadrilateral plate element.

    # Format

    | 1        | 2       | 3     | 4    | 5    | 6   | 7     | 8                 | 9       | 10 |
    | -------- | ------- | ----- | ---- | ---- | ---- | ---- | ----------------- | ------- | -- |
    | `CQUAD4` | `EID`   | `PID` | `G1` | `G2` | `G3` | `G4` | `THETA` or `MCID` | `ZOFFS` |    |
    |          | `TFLAG` | `T1`  | `T2` | `T3` | `T4` |      |                   |         |    |
*/
            class cquad4 : public __base::shell {

            private:

               static bdf::types::card head;

            public:

               cquad4(const std::list<std::string> &);

               const dnvgl::extfem::bdf::cards::types
               card_type(void) const;

               virtual void read(const std::list<std::string> &);

               const card *operator() (
                  long const *EID, long const *PID,
                  long const *G1, long const *G2,
                  long const *G3, long const *G4,
                  double const *THETA=nullptr,
                  double const *ZOFFS=nullptr,
                  long const *TFLAG=nullptr,
                  double const *T1=nullptr, double const *T2=nullptr,
                  double const *T3=nullptr, double const *T4=nullptr);

               const card *operator() (
                  long const *EID, long const *PID,
                  long const *G1, long const *G2,
                  long const *G3, long const *G4,
                  long const *MCID,
                  double const *ZOFFS=nullptr,
                  long const *TFLAG=nullptr,
                  double const *T1=nullptr, double const *T2=nullptr,
                  double const *T3=nullptr, double const *T4=nullptr);

            private:

               using __base::shell::put;

               virtual void collect_outdata(
                  std::list<std::unique_ptr<format_entry> >&) const;
            };

/// Handle Nastran Bulk `CBEAM` entries.
/** # Beam Element Connection

    Defines a beam element.

    # Format

    | 1       | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9             | 10 |
    | ------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------------- | -- |
    | `CBEAM` | `EID` | `PID` | `GA`  | `GB`  | `X1`  | `X2`  | `X3`  | `OFFT` / `BIT`|    |
    |         | `PA`  | `PB`  | `W1A` | `W2A` | `W3A` | `W1B` | `W2B` | `W3B`         |    |
    |         | `SA`  | `SB`  |       |       |       |       |       |               |    |

    # Alternate Format

    | 1       | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9             | 10 |
    | ------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------------- | -- |
    | `CBEAM` | `EID` | `PID` | `GA`  | `GB`  | `G0`  |       |       | `OFFT` / `BIT`|    |
    |         | `PA`  | `PB`  | `W1A` | `W2A` | `W3A` | `W1B` | `W2B` | `W3B`         |    |
    |         | `SA`  | `SB`  |       |       |       |       |       |               |    |
*/
            class cbeam : public __base::card {

            private:

               static bdf::types::card head;

               static const entry_type<long> form_EID;
               static const entry_type<long> form_PID;
               static const entry_type<long> form_GA;
               static const entry_type<long> form_GB;
               static const entry_type<double> form_X1;
               static const entry_type<long> form_G0;
               static const entry_type<double> form_X2;
               static const entry_type<double> form_X3;
               static const entry_type<double> form_BIT;
               static const entry_type<std::string> form_OFFT;
               static const entry_type<std::list<int> > form_PA;
               static const entry_type<std::list<int> > form_PB;
               static const entry_type<double> form_W1A;
               static const entry_type<double> form_W2A;
               static const entry_type<double> form_W3A;
               static const entry_type<double> form_W1B;
               static const entry_type<double> form_W2B;
               static const entry_type<double> form_W3B;
               static const entry_type<long> form_SA;
               static const entry_type<long> form_SB;

            public:

               /** Flag to store whether direction node or direction
                   vector was std::set for cross section direction.
               */
               typedef enum {
                  /// Element has direction vector entry
                  has_DVEC,
                  /// Element direction defined by direction code
                  has_DCODE} CHOOSE_DIR_CODE;
               CHOOSE_DIR_CODE choose_dir_code;
               /** Flag to store whether 'OFFT' or 'BIT' was std::set.
                */
               typedef enum {
                  /// `OFFT` is std::set for element
                  has_OFFT,
                  /// `BIT` is std::set for element
                  has_BIT} CHOOSE_OFFT_BIT;
               CHOOSE_OFFT_BIT choose_offt_bit;

               /** Unique element identification number. (0 <
                   Integer < 100,000,000)
               */
               entry_value<long> EID;
               /** Property identification number of `PBEAM`, `PBCOMP`
                   or `PBEAML` entry. (Integer > 0; Default = `EID`)
               */
               entry_value<long> PID;
               /** First grid point identification numbers of
                   connection points. (Integer > 0)
               */
               entry_value<long> GA;
               /** Second grid point identification numbers of
                   connection points. (Integer > 0)
               */
               entry_value<long> GB;
               /** First components of orientation vector , from `GA`,
                   in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system.
                   (Real)
               */
               entry_value<double> X1;
               /** Alternate method to supply the orientation vector
                   using grid point `G0`. Direction of is from `GA` to
                   G0. is then transferred to End `A`. (Integer > 0;
                   or `GB`)
               */
               entry_value<long> G0;
               /** Second components of orientation vector , from
                   `GA`, in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system.
                   (Real)
               */
               entry_value<double> X2;
               /** Third components of orientation vector , from `GA`,
                   in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system.
                   (Real)
               */
               entry_value<double> X3;
               /** Built-in twist of the cross-sectional axes about
                   the beam axis at end `B` relative to end `A`. For
                   beam p-elements only. (Real; Default = 0.0)
               */
               entry_value<double> BIT;
               /** Offset vector interpretation flag. (Character or
                   blank)
               */
               entry_value<std::string> OFFT;
               /** Pin flags for beam end `A`, respectively; used to
                   remove connections between the grid point and
                   selected degrees-offreedom of the beam. The
                   degrees-of-freedom are defined in the element’s
                   coordinate system and the pin flags are applied at
                   the offset ends of the beam. The beam must have
                   stiffness associated with the `PA` and `PB`
                   degrees-of-freedom to be released by the pin flags.
                   For example, if `PA` = 4, the `PBEAM` entry must
                   have a nonzero value for `J`, the torsional
                   stiffness. (Up to five of the unique Integers 1
                   through 6 with no embedded blanks.) Pin flags are
                   not allowed for beam p-elements.
               */
               entry_value<std::list<int> > PA;
               /** Pin flags for beam end `B`, respectively; used to
                   remove connections between the grid point and
                   selected degrees-offreedom of the beam. The
                   degrees-of-freedom are defined in the element’s
                   coordinate system and the pin flags are applied at
                   the offset ends of the beam. The beam must have
                   stiffness associated with the `PA` and `PB`
                   degrees-of-freedom to be released by the pin flags.
                   For example, if `PA` = 4, the `PBEAM` entry must
                   have a nonzero value for `J`, the torsional
                   stiffness. (Up to five of the unique Integers 1
                   through 6 with no embedded blanks.) Pin flags are
                   not allowed for beam p-elements.
               */
               entry_value<std::list<int> > PB;
               /** *x* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `A`. (Real; Default = 0.0)
               */
               entry_value<double> W1A;
               /** *y* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `A`. (Real; Default = 0.0)
               */
               entry_value<double> W2A;
               /** *z* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `A`. (Real; Default = 0.0)
               */
               entry_value<double> W3A;
               /** *x* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `B`. (Real; Default = 0.0)
               */
               entry_value<double> W1B;
               /** *y* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `B`. (Real; Default = 0.0)
               */
               entry_value<double> W2B;
               /** *z* Components of offset vectors from the grid
                   points to the end points of the axis of the shear
                   center at beam end `B`. (Real; Default = 0.0)
               */
               entry_value<double> W3B;
               /** Scalar or grid point identification numbers for the
                   end `A`. The degrees-of-freedom at these points are
                   the warping variables . `SA` and `SB` cannot be
                   specified for beam p-elements. (Integers > 0 or
                   blank)
               */
               entry_value<long> SA;
               /** Scalar or grid point identification numbers for the
                   end `B`. The degrees-of-freedom at these points are
                   the warping variables . `SA` and `SB` cannot be
                   specified for beam p-elements. (Integers > 0 or
                   blank)
               */
               entry_value<long> SB;

               cbeam(std::list<std::string> const &inp);

               const dnvgl::extfem::bdf::cards::types
               card_type(void) const { return CBEAM; };

               virtual void read(const std::list<std::string> &);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  double const *X1,
                  double const *X2,
                  double const *X3,
                  std::string const *OFFT=nullptr,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr,
                  long const *SA=nullptr, long const *SB=nullptr);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  double const *X1,
                  double const *X2,
                  double const *X3,
                  double const *BIT,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr,
                  long const *SA=nullptr, long const *SB=nullptr);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  long const *G0,
                  std::string const *OFFT=nullptr,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr,
                  long const *SA=nullptr, long const *SB=nullptr);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  long const *G0,
                  double const *BIT,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr,
                  long const *SA=nullptr, long const *SB=nullptr);

            private:

               using __base::card::put;

               virtual void collect_outdata(
                  std::list<std::unique_ptr<format_entry> >&) const;
            };

/// Handle Nastran Bulk `CBAR` entries.
/** # Simple Beam Element Connection

    Defines a simple beam element.

    # Format

    | 1       | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9      | 10 |
    | ------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------ | -- |
    | `CBAR`  | `EID` | `PID` | `GA`  | `GB`  | `X1`  | `X2`  | `X3`  | `OFFT` |    |
    |         | `PA`  | `PB`  | `W1A` | `W2A` | `W3A` | `W1B` | `W2B` | `W3B`  |    |

    # Alternate Format

    | 1       | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9      | 10 |
    | ------- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------ | -- |
    | `CBAR`  | `EID` | `PID` | `GA`  | `GB`  | `G0`  |       |       | `OFFT` |    |
    |         | `PA`  | `PB`  | `W1A` | `W2A` | `W3A` | `W1B` | `W2B` | `W3B`  |    |
*/
            class cbar : public __base::card {

            private:

               static bdf::types::card head;

               static const entry_type<long> form_EID;
               static const entry_type<long> form_PID;
               static const entry_type<long> form_GA;
               static const entry_type<long> form_GB;
               static const entry_type<double> form_X1;
               static const entry_type<long> form_G0;
               static const entry_type<double> form_X2;
               static const entry_type<double> form_X3;
               static const entry_type<std::string> form_OFFT;
               static const entry_type<std::list<int> > form_PA;
               static const entry_type<std::list<int> > form_PB;
               static const entry_type<double> form_W1A;
               static const entry_type<double> form_W2A;
               static const entry_type<double> form_W3A;
               static const entry_type<double> form_W1B;
               static const entry_type<double> form_W2B;
               static const entry_type<double> form_W3B;

            public:

               const dnvgl::extfem::bdf::cards::types card_type(void) const {
                  return CBAR;
               };

               /** Flag to store whether direction node or direction
                   vector was std::set for cross section direction.
               */
               typedef enum {
                  /// Element has direction vector entry
                  has_DVEC,
                  /// Element direction defined by direction code
                  has_DCODE} CHOOSE_DIR_CODE;
               CHOOSE_DIR_CODE choose_dir_code;

               /** Unique element identification number. (0 <
                   Integer < 100,000,000)
               */
               entry_value<long> EID;
               /** Property identification number of a `PBAR` or
                   `PBARL` entry. (Integer > 0 or blank*; Default =
                   `EID` unless `BAROR` entry has nonzero entry in
                   field 3.)
               */
               entry_value<long> PID;
               /** Grid point identification numbers of connection
                   point at `A` side of beam. (Integer > 0; `GA` ≠
                   `GB` )
               */
               entry_value<long> GA;
               /** Grid point identification numbers of connection
                   point at `B` side of beam. (Integer > 0; `GA` ≠
                   `GB` )
               */
               entry_value<long> GB;
               /** *x* components of orientation vector *v* , from
                   `GA`, in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system. See
                   Remark 8. (Real)
               */
               entry_value<double> X1;
               /** Alternate method to supply the orientation
                   vector *v* using grid point `G0`. The direction of
                   *v* is from `GA` to `G0`. 'v* is then translated to
                   End `A`. (Integer > 0; `G0` ≠ `GA` or `GB`)
               */
               entry_value<long> G0;
               /** *y* components of orientation vector *v* , from
                   `GA`, in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system. See
                   Remark 8. (Real)
               */
               entry_value<double> X2;
               /** *z* components of orientation vector *v* , from
                   `GA`, in the displacement coordinate system at `GA`
                   (default), or in the basic coordinate system. See
                   Remark 8. (Real)
               */
               entry_value<double> X3;
               /** Offset vector interpretation flag. (character or
                   blank) See Remark 8.
               */
               entry_value<std::string> OFFT;
               /** Pin flags for bar ends `A`. Used to remove
                   connections between the grid point and selected
                   degrees-of-freedom of the bar. The
                   degrees-of-freedom are defined in the element’s
                   coordinate system (see Figure 8-8). The bar must
                   have stiffness associated with the `PA`
                   degrees-of-freedom to be released by the pin flags.
                   For example, if `PA` = 4 is specified, the `PBAR`
                   entry must have a value for `J`, the torsional
                   stiffness. (Up to 5 of the unique Integers 1
                   through 6 anywhere in the field with no embedded
                   blanks; Integer > 0.)
               */
               entry_value<std::list<int> > PA;
               /** Pin flags for bar ends `B`. Used to remove
                   connections between the grid point and selected
                   degrees-of-freedom of the bar. The
                   degrees-of-freedom are defined in the element’s
                   coordinate system (see Figure 8-8). The bar must
                   have stiffness associated with the `PB`
                   degrees-of-freedom to be released by the pin flags.
                   For example, if `PB` = 4 is specified, the `PBAR`
                   entry must have a value for `J`, the torsional
                   stiffness. (Up to 5 of the unique Integers 1
                   through 6 anywhere in the field with no embedded
                   blanks; Integer > 0.)
               */
               entry_value<std::list<int> > PB;
               /** *x* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GA`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W1A;
               /** *y* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GA`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W2A;
               /** *z* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GA`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W3A;
               /** *x* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GB`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W1B;
               /** *y* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GB`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W2B;
               /** *z* components of offset vectors \f$w_a\f$ and
                   \f$w_b\f$, respectively (see Figure 8-8) in
                   displacement coordinate systems (or in element
                   system depending upon the content of the `OFFT`
                   field), at point `GB`. See Remark 7. and 8. (Real;
                   Default = 0.0)
               */
               entry_value<double> W3B;

               cbar(const std::list<std::string> &inp);

               cbar(
                  const long *EID, const long *PID,
                  const long *GA, const long *GB,
                  const double *X1, const double *X2, const double *X3,
                  const std::string *OFFT = nullptr,
                  const std::list<int> *PA = nullptr,
                  const std::list<int> *PB = nullptr,
                  const double *W1A = nullptr, const double *W2A = nullptr,
                  const double *W3A = nullptr, const double *W1B = nullptr,
                  const double *W2B = nullptr, const double *W3B = nullptr);

               cbar(
                  const long *EID, const long *PID,
                  const long *GA, const long *GB, const long *G0,
                  const std::string *OFFT = nullptr,
                  const std::list<int> *PA = nullptr, const std::list<int> *PB = nullptr,
                  const double *W1A = nullptr, const double *W2A = nullptr,
                  const double *W3A = nullptr, const double *W1B = nullptr,
                  const double *W2B = nullptr, const double *W3B = nullptr);

               virtual void read(const std::list<std::string> &);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  long const *G0,
                  std::string const *OFFT=nullptr,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr);

               card const *operator() (
                  long const *EID, long const *PID,
                  long const *GA, long const *GB,
                  double const *X1, double const *X2,double const *X3,
                  std::string const *OFFT=nullptr,
                  std::list<int> const *PA=nullptr, std::list<int> const *PB=nullptr,
                  double const *W1A=nullptr, double const *W2A=nullptr,
                  double const *W3A=nullptr, double const *W1B=nullptr,
                  double const *W2B=nullptr, double const *W3B=nullptr);

            private:

               virtual void collect_outdata(
                  std::list<std::unique_ptr<format_entry> >&) const;
            };

/// Handle Nastran Bulk `CROD` entries.
/** # Rod Element Connection

    Defines a tension-compression-torsion element.

    # Format

    | 1       | 2     | 3     | 4    | 5    | 6 | 7 | 8 | 9 | 10 |
    | ------- | ----- | ----- | ---- | ---- | - | - | - | - | -- |
    | `CROD`  | `EID` | `PID` | `G1` | `G2` |   |   |   |   |    |
*/
            class crod : public __base::card {

            private:

               static bdf::types::card head;

               static const entry_type<long> form_EID;
               static const entry_type<long> form_PID;
               static const entry_type<long> form_G1;
               static const entry_type<long> form_G2;

            public:

               /** Element identification number. (Integer > 0)
                */
               entry_value<long> EID;
               /** Property identification number of a `PROD` entry.
                   (Integer > 0; Default = `EID`)
               */
               entry_value<long> PID;
               /** Grid point identification number of first connection
                   point. (Integer > 0; `G1` ≠ `G2`)
               */
               entry_value<long> G1;
               /** Grid point identification number of second connection
                   point. (Integer > 0; `G1` ≠ `G2`)
               */
               entry_value<long> G2;

               crod(const std::list<std::string> &inp);

               const dnvgl::extfem::bdf::cards::types
               card_type(void) const { return CROD; };

               virtual void read(const std::list<std::string> &);

               const card *operator() (long const *EID, long const *PID,
                                       long const *G1, long const *G2);

            private:

               virtual void collect_outdata(
                  std::list<std::unique_ptr<format_entry> >&) const;
            };
            // celas
         }
      }
   }
}

#endif // _BDF_CARDS_ELEMENTS_H_

// Local Variables:
// mode: c++
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../../cbuild -j8&&make -C ../../cbuild test"
// coding: utf-8
// End:
