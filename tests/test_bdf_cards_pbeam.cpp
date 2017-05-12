/**
   \file
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Testing the BDF `PBEAM` card class.

   Detailed description
*/
#include "extfem_misc.h"

// ID:
namespace {
    const char cID[] _EXTFEMIO_UNUSED =
        "@(#) $Id$";
}

#define NOMINMAX // To avoid problems with "numeric_limits"

#include <catch.hpp>

#ifdef __GNUC__
#include "config.h"
#endif

#include "bdf/cards.h"

#if defined(__AFX_H__) && defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

using namespace dnvgl::extfem::bdf;
using namespace dnvgl::extfem::bdf::cards;

TEST_CASE("BDF PBEAM definitions (Small Field Format).", "[bdf_pbeam]") {

    std::list<std::string> data({
            //       PID     MID     A       I1      I2      I12     J
            // 34567A1234567B1234567C1234567D1234567E1234567F1234567G1234567H1234567I
            "PBEAM    4000001       3 1.046+4 9.369+7 1.694+6 6.856+6 1.316+6        \n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);
    pbeam probe(lines);

    CAPTURE( data.front() );

    CHECK(long(probe.PID) == 4000001);
    CHECK(long(probe.MID) == 3);
    CHECK(probe.A == vector<double>({10460.}));
    CHECK(probe.I1 == vector<double>({93690000.}));
    CHECK(probe.I2 == vector<double>({1694000.}));
    CHECK(probe.I12 == vector<double>({6.856e6}));
    CHECK(probe.J == vector<double>({1.316e6}));
}

TEST_CASE("BDF PBEAM definitions (Small Field Format 2).", "[bdf_pbeam]") {

    std::list<std::string> data({
            //       PID     MID     A       I1      I2      I12     J
            // 34567A1234567B1234567C1234567D1234567E1234567F1234567G1234567H1234567I
            "PBEAM   4000001 3       1.046+4 9.369+7 1.694+6 6.856+6 1.316+6\n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);
    pbeam probe(lines);

    CAPTURE( data.front() );

    CHECK(long(probe.PID) == 4000001);
    CHECK(long(probe.MID) == 3);
    CHECK(probe.A == vector<double>({10460.}));
    CHECK(probe.I1 == vector<double>({93690000.}));
    CHECK(probe.I2 == vector<double>({1694000.}));
    CHECK(probe.I12 == vector<double>({6.856e6}));
    CHECK(probe.J == vector<double>({1.316e6}));
}

TEST_CASE("BDF PBEAM definitions (Free Field Format 1).", "[bdf_pbeam]") {

    std::list<std::string> data({
            "PBEAM,1,2,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.\n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);
    pbeam probe(lines);

    CAPTURE( data.front() );

    CHECK(long(probe.PID) == 1);
    CHECK(long(probe.MID) == 2);
    CHECK(probe.A == vector<double>({3.}));
    CHECK(probe.I1 == vector<double>({4.}));
    CHECK(probe.I2 == vector<double>({5.}));
    CHECK(probe.I12 == vector<double>({6.}));
    CHECK(probe.J == vector<double>({7.}));
    CHECK(probe.NSM == vector<double>({8.}));
    CHECK(probe.C1 == vector<double>({9.}));
    CHECK(probe.C2 == vector<double>({10.}));
    CHECK(probe.D1 == vector<double>({11.}));
    CHECK(probe.D2 == vector<double>({12.}));
    CHECK(probe.E1 == vector<double>({13.}));
    CHECK(probe.E2 == vector<double>({14.}));
    CHECK(probe.F1 == vector<double>({15.}));
    CHECK(probe.F2 == vector<double>({16.}));
}

TEST_CASE("BDF PBEAM definitions (Free Field Format 2).", "[bdf_pbeam]") {

    std::list<std::string> data({
            "PBEAM,1,2,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,\n",
            ",YES,18.,19.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30.,31.,32.,\n",
            ",NO,34.,35.,36.,37.,38.,39.,40.,41.,42.,43.,44.,45.,46.,47.,48.,\n",
            ",49.,50.,51.,52.,53.,54.,55.,56.,57.,58.,59.,60.,61.,62.,63.,64.\n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);

    CHECK(lines.size() == 65);
    pbeam probe(lines);

    CAPTURE( data.front() );

    CHECK(long(probe.PID) == 1);
    CHECK(long(probe.MID) == 2);
    vector<std::string> ref({"YES", "NO"});
    for (auto p : probe.SO) {
        CHECK(p == ref.front());
        ref.erase(ref.begin());
    }
    CHECK(probe.X_XB == vector<double>({18., 34.}));
    CHECK(probe.A == vector<double>({3., 19., 35.}));
    CHECK(probe.I1 == vector<double>({4., 20., 36.}));
    CHECK(probe.I2 == vector<double>({5., 21., 37.}));
    CHECK(probe.I12 == vector<double>({6., 22., 38.}));
    CHECK(probe.J == vector<double>({7., 23., 39.}));
    CHECK(probe.NSM == vector<double>({8., 24., 40.}));
    CHECK(probe.C1 == vector<double>({9., 25., 41.}));
    CHECK(probe.C2 == vector<double>({10., 26., 42.}));
    CHECK(probe.D1 == vector<double>({11., 27., 43.}));
    CHECK(probe.D2 == vector<double>({12., 28., 44.}));
    CHECK(probe.E1 == vector<double>({13., 29., 45.}));
    CHECK(probe.E2 == vector<double>({14., 30., 46.}));
    CHECK(probe.F1 == vector<double>({15., 31., 47.}));
    CHECK(probe.F2 == vector<double>({16., 32., 48.}));
    CHECK(double(probe.K1) == 49);
    CHECK(double(probe.K2) == 50);
    CHECK(double(probe.S1) == 51);
    CHECK(double(probe.S2) == 52);
    CHECK(double(probe.NSI_A) == 53);
    CHECK(double(probe.NSI_B) == 54);
    CHECK(double(probe.CW_A) == 55);
    CHECK(double(probe.CW_B) == 56);
    CHECK(double(probe.M1_A) == 57);
    CHECK(double(probe.M2_A) == 58);
    CHECK(double(probe.M1_B) == 59);
    CHECK(double(probe.M2_B) == 60);
    CHECK(double(probe.N1_A) == 61);
    CHECK(double(probe.N2_A) == 62);
    CHECK(double(probe.N1_B) == 63);
    CHECK(double(probe.N2_B) == 64);
}


TEST_CASE("BDF PBEAM definitions (Free Field Format 3).", "[bdf_pbeam]") {

    std::list<std::string> data({
            "PBEAM,1,2,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,"
            "YES,18.,19.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30.,31.,32.,"
            "NO,34.,35.,36.,37.,38.,39.,40.,41.,42.,43.,44.,45.,46.,47.,48.,"
            "49.,50.,51.,52.,53.,54.,55.,56.,57.,58.,59.,60.,61.,62.,63.,64."
            ",65.\n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);

    CAPTURE(data.front());
    CHECK(lines.size() == 66);
    CHECK_THROWS(pbeam(lines));
}

TEST_CASE("BDF PBEAM definitions (Tapered Beam).", "[bdf_pbeam]") {

    std::list<std::string> data({
            // 34567A1234567B1234567C1234567D1234567E1234567F1234567G1234567H1234567I
            "PBEAM         39       6     2.9     3.5    5.97                        \n",
            "                             2.0    -4.0                                \n",
            "             YES     1.0     5.3    56.2    78.6                        \n",
            "                             2.5    -5.0                                \n",
            "                             1.1             2.1            0.21        \n",
            "                                             0.5             0.0        \n"});
    std::list<std::string> lines;
    __base::card::card_split(data, lines);
    pbeam probe(lines);

    CAPTURE( data.front() );

    CHECK(long(probe.PID) == 39);
    CHECK(long(probe.MID) == 6);
    CHECK(probe.A == vector<double>({2.9, 5.3}));
    CHECK(probe.I1 == vector<double>({3.5, 56.2}));
    CHECK(probe.I2 == vector<double>({5.97, 78.6}));
    CHECK(probe.I12 == vector<double>({0., 0.}));
    CHECK(probe.J == vector<double>({0., 0.}));
    CHECK(probe.NSM == vector<double>({0., 0.}));
    CHECK(probe.C1 == vector<double>({0., 0.}));
    CHECK(probe.C2 == vector<double>({0., 0.}));
    CHECK(probe.D1 == vector<double>({2., 2.5}));
    CHECK(probe.D2 == vector<double>({-4., -5.}));
    CHECK(probe.E1 == vector<double>({0., 0.}));
    CHECK(probe.E2 == vector<double>({0., 0.}));
    CHECK(probe.F1 == vector<double>({0., 0.}));
    CHECK(probe.F2 == vector<double>({0., 0.}));
    vector<dnvgl::extfem::bdf::types::entry_value<std::string> > ref(1);
    dnvgl::extfem::bdf::types::entry_type<std::string> tmp("tmp");
    tmp.set_value(ref.front(), "YES");
    CHECK(probe.SO == ref);
    CHECK(probe.X_XB == vector<double>({1.}));

    CHECK(double(probe.K1) == 1.);
    CHECK(double(probe.K2) == 1.);
    CHECK(double(probe.S1) == 1.1);
    CHECK(double(probe.S2) == 0.);
    CHECK(double(probe.NSI_A) == 2.1);
    CHECK_FALSE(probe.NSI_B);
    CHECK(double(probe.CW_A) == 0.21);
    CHECK_FALSE(probe.CW_B);
    CHECK(double(probe.M1_A) == 0.);
    CHECK(double(probe.M2_A) == 0.);
    CHECK_FALSE(probe.M1_B);
    CHECK_FALSE(probe.M2_B);
    CHECK(double(probe.N1_A) == 0.5);
    CHECK(double(probe.N2_A) == 0.);
    CHECK(double(probe.N1_B) == 0.0);
    CHECK_FALSE(probe.N2_B);
}

TEST_CASE("BDF PBEAM roundtrip test", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1., 2.};
    std::vector<double> I1{2., 3.};
    std::vector<double> I2{3., 4.};
    std::vector<double> I12{4., 5.};
    std::vector<double> J{5., 6.};
    std::vector<double> NSM{6., 7.};
    std::vector<double> C1{7., 8.};
    std::vector<double> C2{8., 9.};
    std::vector<double> D1{9., 10.};
    std::vector<double> D2{10., 11.};
    std::vector<double> E1{11., 12.};
    std::vector<double> E2{12., 13.};
    std::vector<double> F1{13., 14.};
    std::vector<double> F2{14., 15.};
    std::vector<std::string> SO{"YESA"};
    std::vector<double> X_XB{16.};
    double K1{17.};
    double K2{18.};
    double S1{19.};
    double S2{20.};
    double NSI_A{21.};
    double NSI_B{22.};
    double CW_A{23.};
    double CW_B{24.};
    double M1_A{25.};
    double M2_A{26.};
    double M1_B{27.};
    double M2_B{28.};
    double N1_A{29.};
    double N2_A{30.};
    double N1_B{31.};
    double N2_B{32.};

    pbeam probe(&EID, &PID, &A, &I1, &I2, &I12, &J, &NSM,
                &C1, &C2, &D1, &D2, &E1, &E2, &F1, &F2,
                &SO, &X_XB,
                &K1, &K2, &S1, &S2, &NSI_A, &NSI_B, &CW_A, &CW_B,
                &M1_A, &M2_A, &M1_B, &M2_B, &N1_A, &N2_A, &N1_B, &N2_B);
    test << probe;

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+004.000+005.000+006.000+00\n"
              "        7.000+008.000+009.000+001.000+011.100+011.200+011.300+011.400+01\n"
              "        YESA    1.600+012.000+003.000+004.000+005.000+006.000+007.000+00\n"
              "        8.000+009.000+001.000+011.100+011.200+011.300+011.400+011.500+01\n"
              "        1.700+011.800+011.900+012.000+012.100+012.200+012.300+012.400+01\n"
              "        2.500+012.600+012.700+012.800+012.900+013.000+013.100+013.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1., 2.}));
        CHECK(probe.I1 == std::vector<double>({2., 3.}));
        CHECK(probe.I2 == std::vector<double>({3., 4.}));
        CHECK(probe.I12 == std::vector<double>({4., 5.}));
        CHECK(probe.J == std::vector<double>({5., 6.}));
        CHECK(probe.NSM == std::vector<double>({6., 7.}));
        CHECK(probe.C1 == std::vector<double>({7., 8.}));
        CHECK(probe.C2 == std::vector<double>({8., 9.}));
        CHECK(probe.D1 == std::vector<double>({9., 10.}));
        CHECK(probe.D2 == std::vector<double>({10., 11.}));
        CHECK(probe.E1 == std::vector<double>({11., 12.}));
        CHECK(probe.E2 == std::vector<double>({12., 13.}));
        CHECK(probe.F1 == std::vector<double>({13., 14.}));
        CHECK(probe.F2 == std::vector<double>({14., 15.}));
        for (auto pos : probe.SO) {
            CHECK(pos.value == "YESA");
        }
        CHECK(probe.X_XB == std::vector<double> {16.});
        CHECK(double(probe.K1) == 17.);
        CHECK(double(probe.K2) == 18.);
        CHECK(double(probe.S1) == 19.);
        CHECK(double(probe.S2) == 20.);
        CHECK(double(probe.NSI_A) == 21.);
        CHECK(double(probe.NSI_B) == 22.);
        CHECK(double(probe.CW_A) == 23.);
        CHECK(double(probe.CW_B) == 24.);
        CHECK(double(probe.M1_A) == 25.);
        CHECK(double(probe.M2_A) == 26.);
        CHECK(double(probe.M1_B) == 27.);
        CHECK(double(probe.M2_B) == 28.);
        CHECK(double(probe.N1_A) == 29.);
        CHECK(double(probe.N2_A) == 30.);
        CHECK(double(probe.N1_B) == 31.);
        CHECK(double(probe.N2_B) == 32.);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (reuse)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1., 2.};
    std::vector<double> I1{2., 3.};
    std::vector<double> I2{3., 4.};
    std::vector<double> I12{4., 5.};
    std::vector<double> J{5., 6.};
    std::vector<double> NSM{6., 7.};
    std::vector<double> C1{7., 8.};
    std::vector<double> C2{8., 9.};
    std::vector<double> D1{9., 10.};
    std::vector<double> D2{10., 11.};
    std::vector<double> E1{11., 12.};
    std::vector<double> E2{12., 13.};
    std::vector<double> F1{13., 14.};
    std::vector<double> F2{14., 15.};
    std::vector<std::string> SO{"YESA"};
    std::vector<double> X_XB{16.};
    double K1{17.};
    double K2{18.};
    double S1{19.};
    double S2{20.};
    double NSI_A{21.};
    double NSI_B{22.};
    double CW_A{23.};
    double CW_B{24.};
    double M1_A{25.};
    double M2_A{26.};
    double M1_B{27.};
    double M2_B{28.};
    double N1_A{29.};
    double N2_A{30.};
    double N1_B{31.};
    double N2_B{32.};

    pbeam probe;
    test << probe;
    test << probe(&EID, &PID, &A, &I1, &I2, &I12, &J, &NSM,
                  &C1, &C2, &D1, &D2, &E1, &E2, &F1, &F2,
                  &SO, &X_XB,
                  &K1, &K2, &S1, &S2, &NSI_A, &NSI_B, &CW_A, &CW_B,
                  &M1_A, &M2_A, &M1_B, &M2_B, &N1_A, &N2_A, &N1_B, &N2_B);

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+004.000+005.000+006.000+00\n"
              "        7.000+008.000+009.000+001.000+011.100+011.200+011.300+011.400+01\n"
              "        YESA    1.600+012.000+003.000+004.000+005.000+006.000+007.000+00\n"
              "        8.000+009.000+001.000+011.100+011.200+011.300+011.400+011.500+01\n"
              "        1.700+011.800+011.900+012.000+012.100+012.200+012.300+012.400+01\n"
              "        2.500+012.600+012.700+012.800+012.900+013.000+013.100+013.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l;
        probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1., 2.}));
        CHECK(probe.I1 == std::vector<double>({2., 3.}));
        CHECK(probe.I2 == std::vector<double>({3., 4.}));
        CHECK(probe.I12 == std::vector<double>({4., 5.}));
        CHECK(probe.J == std::vector<double>({5., 6.}));
        CHECK(probe.NSM == std::vector<double>({6., 7.}));
        CHECK(probe.C1 == std::vector<double>({7., 8.}));
        CHECK(probe.C2 == std::vector<double>({8., 9.}));
        CHECK(probe.D1 == std::vector<double>({9., 10.}));
        CHECK(probe.D2 == std::vector<double>({10., 11.}));
        CHECK(probe.E1 == std::vector<double>({11., 12.}));
        CHECK(probe.E2 == std::vector<double>({12., 13.}));
        CHECK(probe.F1 == std::vector<double>({13., 14.}));
        CHECK(probe.F2 == std::vector<double>({14., 15.}));
        for (auto pos : probe.SO) {
            CHECK(pos == "YESA");
        }
        CHECK(probe.X_XB == std::vector<double> {16.});
        CHECK(double(probe.K1) == 17.);
        CHECK(double(probe.K2) == 18.);
        CHECK(double(probe.S1) == 19.);
        CHECK(double(probe.S2) == 20.);
        CHECK(double(probe.NSI_A) == 21.);
        CHECK(double(probe.NSI_B) == 22.);
        CHECK(double(probe.CW_A) == 23.);
        CHECK(double(probe.CW_B) == 24.);
        CHECK(double(probe.M1_A) == 25.);
        CHECK(double(probe.M2_A) == 26.);
        CHECK(double(probe.M1_B) == 27.);
        CHECK(double(probe.M2_B) == 28.);
        CHECK(double(probe.N1_A) == 29.);
        CHECK(double(probe.N2_A) == 30.);
        CHECK(double(probe.N1_B) == 31.);
        CHECK(double(probe.N2_B) == 32.);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (no taper)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    std::vector<double> I12{4.};
    std::vector<double> J{5.};
    std::vector<double> NSM{6.};
    std::vector<double> C1{7.};
    std::vector<double> C2{8.};
    std::vector<double> D1{9.};
    std::vector<double> D2{10.};
    std::vector<double> E1{11.};
    std::vector<double> E2{12.};
    std::vector<double> F1{13.};
    std::vector<double> F2{14.};
    double K1{17.};
    double K2{18.};
    double S1{19.};
    double S2{20.};
    double NSI_A{21.};
    double NSI_B{22.};
    double CW_A{23.};
    double CW_B{24.};
    double M1_A{25.};
    double M2_A{26.};
    double M1_B{27.};
    double M2_B{28.};
    double N1_A{29.};
    double N2_A{30.};
    double N1_B{31.};
    double N2_B{32.};

    pbeam probe(&EID, &PID, &A, &I1, &I2, &I12, &J, &NSM,
                &C1, &C2, &D1, &D2, &E1, &E2, &F1, &F2,
                nullptr, nullptr,
                &K1, &K2, &S1, &S2, &NSI_A, &NSI_B, &CW_A, &CW_B,
                &M1_A, &M2_A, &M1_B, &M2_B, &N1_A, &N2_A, &N1_B, &N2_B);
    test << probe;

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+004.000+005.000+006.000+00\n"
              "        7.000+008.000+009.000+001.000+011.100+011.200+011.300+011.400+01\n"
              "        1.700+011.800+011.900+012.000+012.100+012.200+012.300+012.400+01\n"
              "        2.500+012.600+012.700+012.800+012.900+013.000+013.100+013.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12 == std::vector<double>({4.}));
        CHECK(probe.J == std::vector<double>({5.}));
        CHECK(probe.NSM == std::vector<double>({6.}));
        CHECK(probe.C1 == std::vector<double>({7.}));
        CHECK(probe.C2 == std::vector<double>({8.}));
        CHECK(probe.D1 == std::vector<double>({9.}));
        CHECK(probe.D2 == std::vector<double>({10.}));
        CHECK(probe.E1 == std::vector<double>({11.}));
        CHECK(probe.E2 == std::vector<double>({12.}));
        CHECK(probe.F1 == std::vector<double>({13.}));
        CHECK(probe.F2 == std::vector<double>({14.}));
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK(double(probe.K1) == 17.);
        CHECK(double(probe.K2) == 18.);
        CHECK(double(probe.S1) == 19.);
        CHECK(double(probe.S2) == 20.);
        CHECK(double(probe.NSI_A) == 21.);
        CHECK(double(probe.NSI_B) == 22.);
        CHECK(double(probe.CW_A) == 23.);
        CHECK(double(probe.CW_B) == 24.);
        CHECK(double(probe.M1_A) == 25.);
        CHECK(double(probe.M2_A) == 26.);
        CHECK(double(probe.M1_B) == 27.);
        CHECK(double(probe.M2_B) == 28.);
        CHECK(double(probe.N1_A) == 29.);
        CHECK(double(probe.N2_A) == 30.);
        CHECK(double(probe.N1_B) == 31.);
        CHECK(double(probe.N2_B) == 32.);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (no taper) (reuse)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    std::vector<double> I12{4.};
    std::vector<double> J{5.};
    std::vector<double> NSM{6.};
    std::vector<double> C1{7.};
    std::vector<double> C2{8.};
    std::vector<double> D1{9.};
    std::vector<double> D2{10.};
    std::vector<double> E1{11.};
    std::vector<double> E2{12.};
    std::vector<double> F1{13.};
    std::vector<double> F2{14.};
    double K1{17.};
    double K2{18.};
    double S1{19.};
    double S2{20.};
    double NSI_A{21.};
    double NSI_B{22.};
    double CW_A{23.};
    double CW_B{24.};
    double M1_A{25.};
    double M2_A{26.};
    double M1_B{27.};
    double M2_B{28.};
    double N1_A{29.};
    double N2_A{30.};
    double N1_B{31.};
    double N2_B{32.};

    pbeam probe;
    test << probe;
    test << probe(&EID, &PID, &A, &I1, &I2, &I12, &J, &NSM,
                  &C1, &C2, &D1, &D2, &E1, &E2, &F1, &F2,
                  nullptr, nullptr,
                  &K1, &K2, &S1, &S2, &NSI_A, &NSI_B, &CW_A, &CW_B,
                  &M1_A, &M2_A, &M1_B, &M2_B, &N1_A, &N2_A, &N1_B, &N2_B);

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+004.000+005.000+006.000+00\n"
              "        7.000+008.000+009.000+001.000+011.100+011.200+011.300+011.400+01\n"
              "        1.700+011.800+011.900+012.000+012.100+012.200+012.300+012.400+01\n"
              "        2.500+012.600+012.700+012.800+012.900+013.000+013.100+013.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l;
        probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12 == std::vector<double>({4.}));
        CHECK(probe.J == std::vector<double>({5.}));
        CHECK(probe.NSM == std::vector<double>({6.}));
        CHECK(probe.C1 == std::vector<double>({7.}));
        CHECK(probe.C2 == std::vector<double>({8.}));
        CHECK(probe.D1 == std::vector<double>({9.}));
        CHECK(probe.D2 == std::vector<double>({10.}));
        CHECK(probe.E1 == std::vector<double>({11.}));
        CHECK(probe.E2 == std::vector<double>({12.}));
        CHECK(probe.F1 == std::vector<double>({13.}));
        CHECK(probe.F2 == std::vector<double>({14.}));
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK(double(probe.K1) == 17.);
        CHECK(double(probe.K2) == 18.);
        CHECK(double(probe.S1) == 19.);
        CHECK(double(probe.S2) == 20.);
        CHECK(double(probe.NSI_A) == 21.);
        CHECK(double(probe.NSI_B) == 22.);
        CHECK(double(probe.CW_A) == 23.);
        CHECK(double(probe.CW_B) == 24.);
        CHECK(double(probe.M1_A) == 25.);
        CHECK(double(probe.M2_A) == 26.);
        CHECK(double(probe.M1_B) == 27.);
        CHECK(double(probe.M2_B) == 28.);
        CHECK(double(probe.N1_A) == 29.);
        CHECK(double(probe.N2_A) == 30.);
        CHECK(double(probe.N1_B) == 31.);
        CHECK(double(probe.N2_B) == 32.);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (minimal)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    std::vector<double> I12{4.};

    pbeam probe(&EID, &PID, &A, &I1, &I2);
    test << probe;

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+00\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12.size() == 0);
        CHECK(probe.J.size() == 0);
        CHECK(probe.NSM.size() == 0);
        CHECK(probe.C1.size() == 0);
        CHECK(probe.C2.size() == 0);
        CHECK(probe.D1.size() == 0);
        CHECK(probe.D2.size() == 0);
        CHECK(probe.E1.size() == 0);
        CHECK(probe.E2.size() == 0);
        CHECK(probe.F1.size() == 0);
        CHECK(probe.F2.size() == 0);
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK_FALSE(probe.K1);
        CHECK_FALSE(probe.K2);
        CHECK_FALSE(probe.S1);
        CHECK_FALSE(probe.S2);
        CHECK_FALSE(probe.NSI_A);
        CHECK_FALSE(probe.NSI_B);
        CHECK_FALSE(probe.CW_A);
        CHECK_FALSE(probe.CW_B);
        CHECK_FALSE(probe.M1_A);
        CHECK_FALSE(probe.M2_A);
        CHECK_FALSE(probe.M1_B);
        CHECK_FALSE(probe.M2_B);
        CHECK_FALSE(probe.N1_A);
        CHECK_FALSE(probe.N2_A);
        CHECK_FALSE(probe.N1_B);
        CHECK_FALSE(probe.N2_B);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (minimal) (reuse)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    std::vector<double> I12{4.};

    pbeam probe;
    test << probe;
    test << probe(&EID, &PID, &A, &I1, &I2);

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+00\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l;
        probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12.size() == 0);
        CHECK(probe.J.size() == 0);
        CHECK(probe.NSM.size() == 0);
        CHECK(probe.C1.size() == 0);
        CHECK(probe.C2.size() == 0);
        CHECK(probe.D1.size() == 0);
        CHECK(probe.D2.size() == 0);
        CHECK(probe.E1.size() == 0);
        CHECK(probe.E2.size() == 0);
        CHECK(probe.F1.size() == 0);
        CHECK(probe.F2.size() == 0);
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK_FALSE(probe.K1);
        CHECK_FALSE(probe.K2);
        CHECK_FALSE(probe.S1);
        CHECK_FALSE(probe.S2);
        CHECK_FALSE(probe.NSI_A);
        CHECK_FALSE(probe.NSI_B);
        CHECK_FALSE(probe.CW_A);
        CHECK_FALSE(probe.CW_B);
        CHECK_FALSE(probe.M1_A);
        CHECK_FALSE(probe.M2_A);
        CHECK_FALSE(probe.M1_B);
        CHECK_FALSE(probe.M2_B);
        CHECK_FALSE(probe.N1_A);
        CHECK_FALSE(probe.N2_A);
        CHECK_FALSE(probe.N1_B);
        CHECK_FALSE(probe.N2_B);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (N2_B only)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    double N2_B{32.};

    pbeam probe(&EID, &PID, &A, &I1, &I2, nullptr, nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &N2_B);
    test << probe;

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+00                        \n"
              "                                                                        \n"
              "                                                                        \n"
              "                                                                3.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12.size() == 0);
        CHECK(probe.J.size() == 0);
        CHECK(probe.NSM.size() == 0);
        CHECK(probe.C1.size() == 0);
        CHECK(probe.C2.size() == 0);
        CHECK(probe.D1.size() == 0);
        CHECK(probe.D2.size() == 0);
        CHECK(probe.E1.size() == 0);
        CHECK(probe.E2.size() == 0);
        CHECK(probe.F1.size() == 0);
        CHECK(probe.F2.size() == 0);
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK_FALSE(bool(probe.K1));
        CHECK_FALSE(bool(probe.K2));
        CHECK_FALSE(bool(probe.S1));
        CHECK_FALSE(bool(probe.S2));
        CHECK_FALSE(bool(probe.NSI_A));
        CHECK_FALSE(bool(probe.NSI_B));
        CHECK_FALSE(bool(probe.CW_A));
        CHECK_FALSE(bool(probe.CW_B));
        CHECK_FALSE(bool(probe.M1_A));
        CHECK_FALSE(bool(probe.M2_A));
        CHECK_FALSE(bool(probe.M1_B));
        CHECK_FALSE(bool(probe.M2_B));
        CHECK_FALSE(bool(probe.N1_A));
        CHECK_FALSE(bool(probe.N2_A));
        CHECK_FALSE(bool(probe.N1_B));
        CHECK(double(probe.N2_B) == 32.);
    }
}

TEST_CASE("BDF PBEAM roundtrip test (N2_B only) (reuse)", "[bdf_pbeam]") {
    std::ostringstream test;

    long EID{7869}, PID{104010};
    std::vector<double> A{1.};
    std::vector<double> I1{2.};
    std::vector<double> I2{3.};
    double N2_B{32.};

    pbeam probe;
    test << probe;
    test << probe(
        &EID, &PID, &A, &I1, &I2, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &N2_B);

    SECTION("check output") {
        CHECK(test.str() ==
              "PBEAM       7869  1040101.000+002.000+003.000+00                        \n"
              "                                                                        \n"
              "                                                                        \n"
              "                                                                3.200+01\n");
    }

    SECTION("check reading") {
        std::list<std::string> data;
        std::list<std::string> lines;
        std::string tmp;
        std::istringstream raw(test.str());

        while (getline(raw, tmp))
            data.push_back(tmp);
        __base::card::card_split(data, lines);
        pbeam probe_l;
        probe_l(lines);

        CHECK(long(probe_l.PID) == 7869);
        CHECK(long(probe_l.MID) == 104010);
        CHECK(probe.A == std::vector<double>({1.}));
        CHECK(probe.I1 == std::vector<double>({2.}));
        CHECK(probe.I2 == std::vector<double>({3.}));
        CHECK(probe.I12.size() == 0);
        CHECK(probe.J.size() == 0);
        CHECK(probe.NSM.size() == 0);
        CHECK(probe.C1.size() == 0);
        CHECK(probe.C2.size() == 0);
        CHECK(probe.D1.size() == 0);
        CHECK(probe.D2.size() == 0);
        CHECK(probe.E1.size() == 0);
        CHECK(probe.E2.size() == 0);
        CHECK(probe.F1.size() == 0);
        CHECK(probe.F2.size() == 0);
        CHECK(probe.SO.size() == 0);
        CHECK(probe.X_XB.size() == 0);
        CHECK_FALSE(bool(probe.K1));
        CHECK_FALSE(bool(probe.K2));
        CHECK_FALSE(bool(probe.S1));
        CHECK_FALSE(bool(probe.S2));
        CHECK_FALSE(bool(probe.NSI_A));
        CHECK_FALSE(bool(probe.NSI_B));
        CHECK_FALSE(bool(probe.CW_A));
        CHECK_FALSE(bool(probe.CW_B));
        CHECK_FALSE(bool(probe.M1_A));
        CHECK_FALSE(bool(probe.M2_A));
        CHECK_FALSE(bool(probe.M1_B));
        CHECK_FALSE(bool(probe.M2_B));
        CHECK_FALSE(bool(probe.N1_A));
        CHECK_FALSE(bool(probe.N2_A));
        CHECK_FALSE(bool(probe.N1_B));
        CHECK(double(probe.N2_B) == 32.);
    }
}

// Local Variables:
// mode: c++
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../cbuild -j7 &&
//   (make -C ../cbuild test ;
//    ../cbuild/tests/test_bdf_cards --use-colour no)"
// End:
