#pragma once

#include "phc.hpp"

// MUTATO,C,6	SZEMSZAM,C,11	NEV,C,30	ORSZAG,C,3	IR_SZAM,C,5	UT,C,30	MEGJ_JELZ,L	MEGJ,M	MOD_DAT	TIPUS_JELZ,L	TULTIP,N,1,0	KONYVVEZ,N,1,0	TARSASAG,N,2,0	ERV_ATIPUS,C,2	AKT_ATIPUS,C,2	AGAZAT,C,2	ERTKOD,C,3	SZULDAT,D	K_AZON,C,2	JEL1,C,2	JEL2,C,2	JEL3,C,2	JEL4,C,2	ALLKOD,C,3	CSOPMEGJEL,L	TORLOKA,C,3	KOVTRANZ,N,5,0	HELYSEG,C,25	LEVORSZAG,C,3	LEVIR_SZAM,C,5	LEVUT,C,30	NEV_PTR,C,25	CIM_PTR,C,25	LEVCIM_PTR,C,25	ELUGY,L
// 	JEL2,C,2	JEL3,C,2	JEL4,C,2	ALLKOD,C,3	CSOPMEGJEL,L	TORLOKA,C,3	KOVTRANZ,N,5,0	HELYSEG,C,25	LEVORSZAG,C,3	LEVIR_SZAM,C,5	LEVUT,C,30	NEV_PTR,C,25	CIM_PTR,C,25	LEVCIM_PTR,C,25	ELUGY,L

struct s_tszem
{
    std::string MUTATO;   // cegnév
    std::string SZEMSZAM; //?
    std::string NEV;          // IRSZ
    std::string ORSZAG;   // Város
    std::string IR_SZAM;    // utca
    std::string UT;
    std::string MEGJ_JELZ;  // datum
    std::string MEGJ; // datum
    std::string MOD_DAT;
    std::string TIPUS_JELZ;
    std::string TULTIP;
    std::string KONYVVEZ;
    std::string TARSASAG;
    std::string ERV_ATIPUS;
    std::string AKT_ATIPUS;
    std::string AGAZAT; // datum
    std::string ERTKOD;
    std::string SZULDAT;
    std::string K_AZON;
    std::string JEL1;
    std::string JEL2;
    std::string JEL3;
    std::string JEL4;
    std::string ALLKOD;
    std::string CSOPMEGJEL;
    std::string TORLOKA;
    std::string KOVTRANZ;
    std::string HELYSEG;
    std::string LEVORSZAG;
    std::string LEVIR_SZAM;
    std::string LEVUT;
    std::string NEV_PTR;
    std::string CIM_PTR;
    std::string LEVCIM_PTR;
    std::string ELUGY;
};
