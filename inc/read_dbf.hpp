#pragma once

#include "phc.hpp"
#include <shapefil.h>
#include <tm.hpp>
#include <uj.hpp>
#include <tszem.hpp>

enum dbf_tipus{
    TM,
    UJ,
    TSZEM,
};

std::optional<std::variant<std::vector<s_tm>, std::vector<s_uj>, std::vector<s_tszem>>> read_dbf(std::string file_name, dbf_tipus tipus);
