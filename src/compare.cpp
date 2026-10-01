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

void compare_records(std::optional<std::variant<std::vector<std::array<std::string, dbf_tipus::TM>>, std::vector<std::array<std::string, dbf_tipus::UJ>>, std::vector<std::array<std::string, dbf_tipus::TSZEM>>>> dbf, dbf_tipus tipus, std::optional<std::vector<std::array<std::string, 29UL>>> xlsx)
{
    if (tipus == dbf_tipus::TM)
    {
        std::println("Összehasonlítás TM rekordokkal");

        for (std::size_t i = 0; i < std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value()).size(); i++)
        {
            for (std::size_t j = 0; j < (*xlsx).size(); j++)
            {
                std::string xadoszam = (*xlsx)[j][static_cast<int>(s_xlsx::Adószám)];
                adoszam_alakitas(xadoszam);

                if (std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::ADOSZAM)] == xadoszam)
                {
                    std::println("Cégnév: {}", std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(dbf.value())[i][static_cast<int>(s_tm::TM_UNEV)]);
                }
            }
        }
    }

    if (tipus == dbf_tipus::UJ)
    {
        std::println("Összehasonlítás UJ rekordokkal");
        for (std::size_t i = 0; i < std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value()).size(); i++)
        {
            for (std::size_t j = 0; j < (*xlsx).size(); j++)
            {
                std::string xadoszam = (*xlsx)[j][static_cast<int>(s_xlsx::Adószám)];
                adoszam_alakitas(xadoszam);

                if (std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::ADOSZ)] == xadoszam)
                {
                    std::println("Cégnév: {}", std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(dbf.value())[i][static_cast<int>(s_uj::NEV)]);
                }
            }
        }
    }
}
