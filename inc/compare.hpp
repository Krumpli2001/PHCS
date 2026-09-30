#pragma once

#include "phc.hpp"
#include "read_dbf.hpp"
#include "read_xlsx.hpp"
#include "tm.hpp"
#include "uj.hpp"
#include "tszem.hpp"

void compare_records(std::optional<std::variant<std::vector<std::array<std::string, dbf_tipus::TM>>, std::vector<std::array<std::string, dbf_tipus::UJ>>, std::vector<std::array<std::string, dbf_tipus::TSZEM>>>> dbf, dbf_tipus tipus, std::optional<std::vector<std::array<std::string, 29UL>>> xlsx);