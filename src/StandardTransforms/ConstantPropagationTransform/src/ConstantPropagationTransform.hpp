// BSD 3-Clause License

// Copyright (c) 2019, SCALE Lab, Brown University
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <OpenPhySyn/Database/DatabaseHandler.hpp>
#include <OpenPhySyn/Database/Types.hpp>
#include <OpenPhySyn/Psn/Psn.hpp>
#include <OpenPhySyn/SteinerTree/SteinerTree.hpp>
#include <OpenPhySyn/Transform/PsnTransform.hpp>
#include <cstring>
#include <memory>
#include <unordered_set>

class ConstantPropagationTransform : public psn::PsnTransform
{
private:
    bool isNumber(const std::string& s);
    int  prop_count_;

    int  propagateConstants(psn::Psn* psn_inst, std::string tiehi_cell_name,
                            std::string tielo_cell_name,
                            std::string inverter_cell_name, int max_depth,
                            bool invereter_replace);
    void propagateTieHiLoCell(
        psn::Psn* psn_inst, bool is_tiehi, psn::InstanceTerm* constant_term,
        int max_depth, bool invereter_replace, psn::Instance* tiehi_cell,
        psn::Instance* tielo_cell, psn::LibraryCell* inverter_lib_cell,
        std::unordered_set<psn::Instance*>&     visited,
        std::unordered_set<psn::Instance*>&     deleted_inst,
        std::unordered_set<psn::InstanceTerm*>& deleted_pins);
    int isTiedToConstant(psn::Psn* psn_inst, psn::InstanceTerm* constant_term,
                         bool constant_val);
    int isTiedToInput(psn::Psn* psn_inst, psn::InstanceTerm* input_term,
                      psn::InstanceTerm* constant_term, bool constant_val);

public:
    ConstantPropagationTransform();

    int run(psn::Psn* psn_inst, std::vector<std::string> args) override;
};

DEFINE_TRANSFORM(
    ConstantPropagationTransform, "constant_propagation", "1.0.0",
    "Performs design optimization through constant propagation",
    "Usage: transform constant_propagation [enable-inverter-replacement] "
    "[max-depth] [tie-hi cell] [tie-lo]"
    "cell] [inverter_cell]")
