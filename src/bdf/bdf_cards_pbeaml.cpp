/**
   \file
   \author Berthold Höllmann <berthold.hoellmann@dnvgl.com>
   \copyright Copyright © 2015 by DNV GL SE
   \brief Definitions for Nastran BDF PBEAML cards.

   Detailed description
   */
#include "extfemio_stdafx.h"

#include "extfem_misc.h"

// ID:
namespace {
    // ReSharper disable once CppDeclaratorNeverUsed
    const char _EXTFEMIO_UNUSED(cID_bdf_cards_pbeaml[]) =
        "@(#) $Id$";
}

#include <memory>

#include "bdf/cards.h"
#include "bdf/errors.h"

#if defined(_DEBUG) && defined(DEBUG_NEW)
#define new DEBUG_NEW
#ifdef THIS_FILE
#undef THIS_FILE
#endif // THIS_FILE
namespace {
    char const THIS_FILE[] = __FILE__;
}
#endif

#ifdef max
#undef max
#endif

using namespace std;

using namespace dnvgl::extfem;
using namespace bdf;
using namespace cards;

using bdf::types::entry_type;
using bdf::types::entry_value;
using bdf::type_bounds::bound;

namespace {
    auto const cd0 = make_shared<double>(0.);
    auto const cd1 = make_shared<double>(1.);
}

bdf::types::card pbeaml::head = bdf::types::card("PBEAML");

namespace {
    auto const name = make_shared<std::string>("MSCBML0");
    auto const bound_GROUP = make_shared<bound<std::string>>(
        nullptr, nullptr, name);
}
entry_type<std::string> pbeaml::form_GROUP("GROUP", bound_GROUP);
namespace {
    set<std::string> const allowed({"T", "TW", "I", "L", "ROD",
                "TUBE", "CHAN", "BOX", "BAR", "CROSS", "H", "T1",
                "I1", "CHAN1", "Z", "CHAN2", "T2", "BOX1", "HEXA",
                "HAT", "HAT1", "DBOX"});
    auto const bound_TYPE = make_shared<bound<std::string>>(allowed);
}
entry_type<std::string> pbeaml::form_TYPE("TYPE", bound_TYPE);
namespace {
    auto const bound_DIM = make_shared<bound<double>>(cd0);
}
entry_type<double> pbeaml::form_DIM("DIM", bound_DIM);
namespace {
    auto const bound_NSM = make_shared<bound<double>>(nullptr, nullptr, cd0);
}
entry_type<double> pbeaml::form_NSM("NSM", bound_NSM);
namespace {
    set<std::string> const SO_set({"YES", "NO"});
    auto const bound_SO = make_shared<bound<std::string>>(SO_set);
}
entry_type<std::string> pbeaml::form_SO("SO", bound_SO);
namespace {
    auto const bound_X_XB = make_shared<bound<double>>(cd0, nullptr, cd1);
}
entry_type<double> pbeaml::form_X_XB("X/XB", bound_X_XB);

pbeaml::pbeaml(const list<std::string> &inp) :
beam_prop(inp) {
    this->pbeaml::read(inp);
}

pbeaml::pbeaml(long const *PID, long const *MID,
               std::string const *GROUP,
               std::string const *TYPE,
               vector<vector<double>> const *DIM,
               vector<double> const *NSM/*=nullptr*/,
               vector<std::string> const *SO/*=nullptr*/,
               vector<double> const *X_XB/*=nullptr*/) :
        beam_prop(PID, MID), GROUP(*GROUP), TYPE(*TYPE) {
    size_t const base_size{max(DIM->size(), size_t(2))};
    this->DIM.resize(base_size);
    for (size_t i = 0; i < DIM->size(); i++) {
        this->DIM[i].resize((*DIM)[i].size(), entry_value<double>(nullptr));
        for (size_t j = 0; j < (*DIM)[i].size(); j++)
            this->DIM[i][j]((*DIM)[i][j]);
    }
    if (DIM->size() == 1) {
        this->DIM[1].resize((*DIM)[0].size(), entry_value<double>(nullptr));
        for (size_t j = 0; j < (*DIM)[0].size(); j++)
            this->DIM[1][j]((*DIM)[0][j]);
    }

    if (NSM != nullptr && NSM->size() > 0) {
        this->NSM.resize(NSM->size(), entry_value<double>(nullptr));
        for (size_t i = 0; i < NSM->size(); i++)
            this->NSM[i]((*NSM)[i]);
    } else
        this->NSM.clear();

    this->SO.resize(base_size - 1, entry_value<std::string>(nullptr));
    if (SO != nullptr && SO->size() > 0) {
        for (size_t i = 0; i < SO->size(); i++)
            this->SO[i]((*SO)[i]);
    } else {
        this->SO.assign(base_size - 1, entry_value<std::string>("YES"));
    }

    this->X_XB.resize(base_size - 1, entry_value<double>(nullptr));
    if (X_XB != nullptr && X_XB->size()>1) {
        for (size_t i = 0; i < X_XB->size(); i++)
            this->X_XB[i]((*X_XB)[i]);
    } else {
        this->X_XB.assign(base_size - 1, entry_value<double>(1.));
    }
    this->pbeaml::check_data();
}

void pbeaml::read(list<std::string> const & inp) {

    size_t i, j{0};
    // GCC does not allow jumping over declarations.
    // ReSharper disable once CppJoinDeclarationAndAssignment
    size_t dim_num;

    auto pos = inp.begin();

    if (pos == inp.end()) goto invalid;
    ++pos;
    if (pos == inp.end()) goto invalid;
    form_PID.set_value(PID, *(pos++));
    if (pos == inp.end()) goto invalid;
    form_MID.set_value(MID, *(pos++));
    if (pos == inp.end()) goto invalid;
    form_GROUP.set_value(GROUP, *(pos++));
    if (GROUP.value != "MSCBML0")
        throw errors::parse_error(
        "PBEAML", "Currently only GROUP==MSCBML0 is supported.");
    if (pos == inp.end()) goto invalid;
    form_TYPE.set_value(TYPE, *(pos++));
    if (pos == inp.end()) goto invalid;
    // ReSharper disable once CppJoinDeclarationAndAssignment
    dim_num = this->l_geom::get_dim(TYPE.value);
    if (dim_num < 1)
        throw errors::parse_error(
            "PBEAML", "Unknown beam type " + TYPE.value + ".");

    ++pos;
    for (i = 1; i < 4; i++) {
        if (pos == inp.end()) goto invalid;
        ++pos;
    }

    // DIM.push_back(new vector<dnvgl::extfem::bdf::double> >);
    DIM.push_back(vector<bdf::types::entry_value<double>>());
    for (i = 0; i < dim_num; i++) {
        if (pos == inp.end()) goto invalid;
        DIM.front().push_back(form_DIM(*(pos++)));
    }
    if (pos == inp.end()) goto end;
    NSM.push_back(form_NSM(*(pos++)));

    // Read further cross section definitions for tapered beams. The
    // 'goto's are used because SO, and X/XB have default values. This
    // code is required because it is valid to have only one cross
    // section description defined with attached empty cells. Then the
    // code first assumes that more definitions are defined, using
    // default values for SO and X/XB, only to determine that no DIMs
    // are defined, so no further cross sections are available and
    // cleaning up SO and X/XB afterwards. This should raise an error
    // when SO and/or X/XB are given, but no DIM's, but it does not.
    while (pos != inp.end()) {
        if (pos == inp.end()) goto end;
        j++;
        // DIM.push_back(new vector<dnvgl::extfem::bdf::types::entry_value<double> >);
        DIM.push_back(vector<bdf::types::entry_value<double >> ());
        try {
            SO.push_back(form_SO(*(pos++)));
        } catch (errors::error&) {

            goto end;
        };
        if (pos == inp.end()) goto end;
        try {
            X_XB.push_back(form_X_XB(*(pos++)));
        } catch (errors::error&) {
            goto end;
        }
        if (pos == inp.end()) goto end;
        try {
            DIM.back().push_back(form_DIM(*(pos++)));
        } catch (errors::error&) {
            goto end;
        }
        for (i = 1; i < dim_num; i++) {
            if (pos == inp.end()) goto invalid;
            DIM.back().push_back(form_DIM(*(pos++)));
        }
        if (pos == inp.end()) goto end;
        NSM.push_back(form_NSM(*(pos++)));
    }

end:;
    if (DIM.back().empty()) {
        auto &ref = DIM.front();
        for (auto &p : ref)
            DIM.back().push_back(bdf::types::entry_value<double>(p.value));
    }
    if (NSM.size() == 1)
        NSM.push_back(bdf::types::entry_value<double>(NSM[0].value));
    return;
invalid:
    throw errors::parse_error("PBEAML", "Illegal number of entries.");
}

cards::types pbeaml::card_type() const {
    return cards::types::PBEAML;
};

void pbeaml::collect_outdata(
    list<unique_ptr<format_entry> > &res) const {
    if (!PID) return;

    auto pos_DIM(DIM.begin());
    auto pos_NSM(NSM.begin());
    auto pos_SO(SO.begin());
    auto pos_X_XB(X_XB.begin());

    res.push_back(unique_ptr<format_entry>(format(head)));

    res.push_back(unique_ptr<format_entry>(format<long>(form_PID, PID)));
    res.push_back(unique_ptr<format_entry>(format<long>(form_MID, MID)));

    res.push_back(unique_ptr<format_entry>(
                      bool(GROUP) ?
                      format<std::string>(form_GROUP, GROUP) :
                      format(empty)));
    res.push_back(unique_ptr<format_entry>(format<std::string>(form_TYPE, TYPE)));
    for (auto i = 0; i < 4; i++ )
        res.push_back(unique_ptr<format_entry>(format(empty)));

    for (size_t i{0}; i < pos_DIM->size(); i++)
        res.push_back(unique_ptr<format_entry>(
                          format<double>(form_DIM, (*pos_DIM)[i])));
    ++pos_DIM;
    res.push_back(unique_ptr<format_entry>(
                      pos_NSM != NSM.end() ?
                      format<double>(form_NSM, (*(pos_NSM++))) :
                      format(empty)));
    int cnt{0};
    while (cnt < 13 && pos_DIM != DIM.end()) {
        cnt++;
        if (pos_SO != SO.end()) {
            res.push_back(unique_ptr<format_entry>(
                              pos_SO != SO.end() ?
                              format<std::string>(form_SO, (*(pos_SO++))) :
                              format(empty)));
        }
        bool const last{pos_SO == SO.end()};
        if (pos_X_XB != X_XB.end()) {
            res.push_back(unique_ptr<format_entry>(
                              pos_X_XB != X_XB.end() ?
                              format<double>(form_X_XB, (*(pos_X_XB++))) :
                              format(empty)));
        }
        for (size_t i{0}; i < pos_DIM->size(); i++)
            res.push_back(unique_ptr<format_entry>(
                              (last && (*pos_DIM)[i] == DIM[0][i]) ?
                              format(empty) :
                              format<double>(form_DIM, (*pos_DIM)[i])));
        ++pos_DIM;
        if (pos_NSM != NSM.end() && !(last && *pos_NSM == NSM[0]))
            res.push_back(unique_ptr<format_entry>(
                              format<double>(form_NSM, (*(pos_NSM++)))));
    }
}

void pbeaml::check_data() {
    size_t const base_size{DIM.size()};
    size_t const dim_num{this->l_geom::get_dim(TYPE.value)};

    if (base_size < 2)
        throw errors::form_error("PBEAML", "requires at least two stations");
    if (NSM.size() != 0 && NSM.size() > base_size)
        throw errors::form_error("PBEAML", "wrong size for NSM");
    if (SO.empty() || SO.size() != base_size-1)
        throw errors::form_error("PBEAML", "wrong size for SO");
    if (X_XB.empty() || X_XB.size() != base_size - 1)
        throw errors::form_error("PBEAML", "wrong size for X/XB");
    if (GROUP) pbeaml::form_GROUP.check(GROUP);
    if (TYPE) pbeaml::form_TYPE.check(TYPE);
    for (auto pos : DIM) {
        if (pos.size() != dim_num)
            throw errors::form_error("PBEAML", "wrong number of dimension in DIM");
        for (auto ppos : pos)
            pbeaml::form_DIM.check(ppos);
    }
    for (auto pos : NSM)
        pbeaml::form_NSM.check(pos);
    for (auto pos : SO)
        pbeaml::form_SO.check(pos);
    for (auto pos : X_XB)
        pbeaml::form_X_XB.check(pos);
 }

cards::__base::card const &pbeaml::operator() (list<std::string> const &inp) {
    this->pbeaml::read(inp);
    return *this;
}

cards::__base::card const &pbeaml::operator() (
    long const *PID, long const *MID,
    std::string const *GROUP,
    std::string const *TYPE,
    vector<vector<double>> const *DIM,
    vector<double> const *NSM/*=nullptr*/,
    vector<std::string> const *SO/*=nullptr*/,
    vector<double> const *X_XB/*=nullptr*/) {
    this->beam_prop::operator() (PID, MID);
    this->GROUP(GROUP);
    this->TYPE(TYPE);
    size_t const base_size{max(DIM->size(), size_t(2))};
    this->DIM.resize(base_size);
    for (size_t i = 0; i < DIM->size(); i++) {
        this->DIM[i].resize((*DIM)[i].size(), entry_value<double>(nullptr));
        for (size_t j = 0; j < (*DIM)[i].size(); j++) {
            this->DIM[i][j]((*DIM)[i][j]);
        }
    }
    if (DIM->size() == 1) {
        this->DIM[1].resize((*DIM)[0].size(), entry_value<double>(nullptr));
        for (size_t j = 0; j < (*DIM)[0].size(); j++)
            this->DIM[1][j]((*DIM)[0][j]);
    }

    if (NSM != nullptr && NSM->size() > 0) {
        this->NSM.resize(NSM->size(), entry_value<double>(nullptr));
        for (size_t i = 0; i < NSM->size(); i++)
            this->NSM[i]((*NSM)[i]);
    } else
        this->NSM.clear();
    this->SO.resize(base_size - 1, entry_value<std::string>(nullptr));
    if (SO != nullptr&& SO->size() > 0) {
        for (size_t i = 0; i < SO->size(); i++)
            this->SO[i]((*SO)[i]);
    } else {
        this->SO.assign(base_size - 1, entry_value<std::string>("YES"));
    }

    this->X_XB.resize(base_size - 1, entry_value<double>(nullptr));
    if (X_XB != nullptr && X_XB->size()>1) {
        for (size_t i = 0; i < X_XB->size(); i++)
            this->X_XB[i]((*X_XB)[i]);
    } else {
        this->X_XB.assign(base_size - 1, entry_value<double>(1.));
    }
    this->pbeaml::check_data();
    return *this;
}

// Local Variables:
// mode: c++
// coding: utf-8
// c-file-style: "dnvgl"
// indent-tabs-mode: nil
// compile-command: "make -C ../../cbuild -j7 &&
// (make -C ../../cbuild test;
//    ../../cbuild/tests/test_bdf_cards --use-colour no)"
// End:
