#pragma once

#include "phc.hpp"

// TM_UNEV,C,255	TM_TIPUS,C,2	TM_ISZAM,C,4	TM_HNEV,C,255	TM_CIM,C,255	ADOSZAM,C,13	TM_KEZDATE,D	TM_HATIDO,D	TM_HIVHELY,C,40	ELSO,C,1	TM_TIPUSRC,N,5,0	SORBAN,N,1,0	TM_JEGYZ,C,10	TM_BIRHAT,C,25	TM_BIRSZLS,C,24	TM_BIRDAT,D	TM_BIRO,C,255	TM_FNEV,C,255	TM_FIRSZ,C,4	TM_FVAROS,C,255	TM_FCIM,C,255

struct tm
{
    std::string TM_UNEV;   // cegnév
    std::string TM_UTIPUS; //?
    int TM_ISZAM;          // IRSZ
    std::string TM_HNEV;   // Város
    std::string TM_CIM;    // utca
    uint32_t ADOSZAM;
    std::string TM_KEZDATE;  // datum
    std::string TM_HATARIDO; // datum
    std::string TM_HIVHELY;
    std::string ELSO;
    std::string TM_TIPUSRC;
    std::string SORBAN;
    uint32_t TM_JEGYZ;
    std::string TM_BIRHAT;
    std::string TM_BIRSZLS;
    std::string TM_BIRDAT; // datum
    std::string TM_BIRO;
    std::string TM_FNEV;
    std::string TM_FIRSZ;
    std::string TM_FVAROS;
    std::string TM_FCIM;
};
