#pragma once

#include "phc.hpp"
#include <shapefil.h>
#include <tm.hpp>
#include <uj.hpp>
#include <tszem.hpp>

enum dbf_tipus{
    TM = 21,
    UJ = 24,
    TSZEM = 35
};

std::optional<std::variant<std::vector<std::array<std::string, dbf_tipus::TM>>, std::vector<std::array<std::string, dbf_tipus::UJ>>, std::vector<std::array<std::string, dbf_tipus::TSZEM>>>> read_dbf(std::string file_name, dbf_tipus tipus);