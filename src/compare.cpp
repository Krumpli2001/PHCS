#include "compare.hpp"

void adoszam_alakitas(std::string &adoszam)
{
    std::string adoszam2 = "";

    for (auto c : adoszam)
    {
        if (c != '-')
        {
            adoszam2 += c;
        }
    }

    adoszam = adoszam2;
}

void compare_records(std::optional<std::variant<std::vector<std::array<std::string, dbf_tipus::TM>>, std::vector<std::array<std::string, dbf_tipus::UJ>>, std::vector<std::array<std::string, dbf_tipus::TSZEM>>>> dbf, dbf_tipus tipus, std::optional<std::vector<std::array<std::string, 29UL>>> xlsx, std::string *output)
{
    if (tipus == dbf_tipus::TM)
    {
        // std::println("Összehasonlítás TM rekordokkal");
        *output += "Összehasonlítás TM rekordokkal\n";
        *output += "Adószám;Név;Irsz;Utca;Tipus;Irsz;Név;Cím;Kezdet;Határidő;Hivhely;Első;Tipr.;Sorban;Jegyz.;B.hat.;B.szls;B.dat;Bíró;Fnév;Irsz;Város;Cím\n";

        for (std::size_t i = 0; i < std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value()).size(); i++)
        {
            for (std::size_t j = 0; j < (*xlsx).size(); j++)
            {
                std::string xadoszam = (*xlsx)[j][static_cast<int>(s_xlsx::Adószám)];
                adoszam_alakitas(xadoszam);
                auto dbfadoszam = std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::ADOSZAM)];
                // auto dbf = std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i];
                if (xadoszam.substr(0, 8) == dbfadoszam.substr(0, 8))
                {
                    // *output += (*xlsx)[j][static_cast<int>(s_xlsx::Titulus_nélküli_név)] + ';' + xadoszam + ";\n";
                    *output += xadoszam + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_UNEV)] + ';' + std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_ISZAM)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_CIM)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_UTIPUS)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_ISZAM)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_HNEV)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_CIM)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_KEZDATE)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_HATARIDO)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_HIVHELY)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::ELSO)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_TIPUSRC)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::SORBAN)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_JEGYZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_BIRHAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_BIRSZLS)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_BIRDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_BIRO)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_FNEV)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_FIRSZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_FVAROS)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_FCIM)] + '\n';
                }
            }
        }
    }

    if (tipus == dbf_tipus::UJ)
    {
        // std::println("Összehasonlítás UJ rekordokkal");
        *output += "Összehasonlítás UJ rekordokkal\n";
        *output += "Adószám;Név;Irsz;Utca;Város;Utca;Irsz;Kdat;Vdat;Rdat;Mdat;Csodtip;Hszam.;Rkod;Rido;Jegyzet;Bhat;Bszlsz;Bdat;Bíró;Fnév;Irsz;Város;Cím\n";
        for (std::size_t i = 0; i < std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value()).size(); i++)
        {
            for (std::size_t j = 0; j < (*xlsx).size(); j++)
            {
                std::string xadoszam = (*xlsx)[j][static_cast<int>(s_xlsx::Adószám)];
                adoszam_alakitas(xadoszam);
                auto dbfadoszam = std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::ADOSZ)];

                if (xadoszam.substr(0, 8) == dbfadoszam.substr(0, 8))
                {
                    // *output += (*xlsx)[j][static_cast<int>(s_xlsx::Titulus_nélküli_név)] + ';' + xadoszam + ";\n";
                    *output += xadoszam + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::NEV)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::IRSZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::UTCA)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::VAROS)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::UTCA)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::IRSZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::KDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::VDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::RDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::MDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::CSODTIP)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::HSZAM)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::RKOD)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::RIDO)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::JEGYZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::BIRHAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::BIRSZLSZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::BIRDAT)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::BIRO)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::FNEV)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::FIRSZ)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::FVAROS)] + ';' +
                               std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::FCIM)] + '\n';
                }
            }
        }
    }
}
