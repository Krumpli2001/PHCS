#pragma once

#include <OpenXLSX.hpp>
#include "phc.hpp"

struct s_xlsx {
    std::string Mutató;
    std::string IP_ID;
    std::string Típus;
    std::string Titulus;
    std::string Titulus_nélküli_név;
    std::string Adóazonosító_jel;
    std::string Adószám;
    std::string SZLTörölt_adószám;
    std::string Külföldi_adóazonosító;
    std::string Cím;
    std::string KSH_szám;
    std::string Anyja_neve;
    std::string Sz_hely;
    std::string Sz_idő;
    std::string Születési_név;
    std::string Cégjegyzékszám;
    std::string Civil_szervezet_nyilvántartási_száma;
    std::string Törölt;
    std::string Elektronikus;
    std::string KAÜ_ID;
    std::string Főtevékenység_kód;
    std::string Törlés_oka;
    std::string Törlésre_jelölés_dátuma;
    std::string Aktuális_adósminősítés;
    std::string GFO_Kód;
    std::string Van_e_partner_azonosítója;
    std::string Külföldi_adózó;
    std::string Utolsó_módosító;
    std::string Utolsó_módosítás;
};

std::optional<std::vector<s_xlsx>> read_xlsx(std::string file_name);
