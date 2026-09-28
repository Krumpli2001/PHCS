#pragma once

#include "phc.hpp"
#include <shapefil.h>

enum dbf_tipus{
    TM,
    UJ,
    TSZEM,
};

void read_dbf(std::string file_name, dbf_tipus tipus);
