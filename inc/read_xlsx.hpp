#pragma once

#include <OpenXLSX.hpp>
#include "phc.hpp"

enum class s_xlsx {
    Mutató,
    IP_ID,
    Típus,
    Titulus,
    Titulus_nélküli_név,
    Adóazonosító_jel,
    Adószám,
    SZLTörölt_adószám,
    Külföldi_adóazonosító,
    Cím,
    KSH_szám,
    Anyja_neve,
    Sz_hely,
    Sz_idő,
    Születési_név,
    Cégjegyzékszám,
    Civil_szervezet_nyilvántartási_száma,
    Törölt,
    Elektronikus,
    KAÜ_ID,
    Főtevékenység_kód,
    Törlés_oka,
    Törlésre_jelölés_dátuma,
    Aktuális_adósminősítés,
    GFO_Kód,
    Van_e_partner_azonosítója,
    Külföldi_adózó,
    Utolsó_módosító,
    Utolsó_módosítás
};

std::optional<std::vector<std::array<std::string, 29>>> read_xlsx(std::string file_name);
