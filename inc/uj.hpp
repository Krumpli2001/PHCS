#pragma once

#include <phc.hpp>

// NEV,C,129	VAROS,C,30	UTCA,C,30	ADOSZ,C,13	IRSZ,C,4	KDAT,D	VDAT,D	UJ,L	RDAT,D	MDAT,D	CSODTIP,C,2	HSZAM,C,16	RKOD,C,6	RIDO,C,10	MODOSIT,L	JEGYZ,C,10	BIRHAT,C,25	BIRSZLSZ,C,24	BIRDAT,D	BIRO,C,60	FNEV,C,60	FIRSZ,C,4	FVAROS,C,30	FCIM,C,30	REKORD,N,10,0

struct s_uj
{
    std::string NEV; // Cegnev
    std::string VAROS;
    std::string UTCA;
    std::string ADOSZ;
    std::string IRSZ;
    std::string KDAT;
    std::string VDAT;
    std::string UJ;
    std::string RDAT;
    std::string MDAT;
    std::string CSODTIP;
    std::string HSZAM;
    std::string RKOD;
    std::string RIDO;
    std::string MODOSIT;
    std::string JEGYZ;
    std::string BIRHAT;
    std::string BIRSZLSZ;
    std::string BIRDAT;
    std::string BIRO;
    std::string FNEV;
    std::string FIRSZ;
    std::string FVAROS;
    std::string FCIM;
    std::string REKORD;
};
