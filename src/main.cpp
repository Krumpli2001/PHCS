#include "read_xlsx.hpp"
#include "read_dbf.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int
{
    std::println("Szia világ!");

    
    auto tm_records = read_dbf(argv[1], dbf_tipus::TM);
    auto uj_records = read_dbf(argv[2], dbf_tipus::UJ);
    auto tszem_records = read_dbf(argv[3], dbf_tipus::TSZEM);
    auto xlsx_records = read_xlsx(argv[4]);

    if (tm_records.has_value())
    {
        std::println("4. TM rekord: {}", std::get<std::vector<std::array<std::string, dbf_tipus::TM>>>(tm_records.value())[3][static_cast<int>(s_tm::TM_UNEV)]);
    }

    if (uj_records.has_value())
    {
        std::println("4. UJ rekord: {}", std::get<std::vector<std::array<std::string, dbf_tipus::UJ>>>(uj_records.value())[3][static_cast<int>(s_uj::NEV)]);
    }

    if (tszem_records.has_value())
    {
        std::println("4. TSZEM rekord: {}", std::get<std::vector<std::array<std::string, dbf_tipus::TSZEM>>>(tszem_records.value())[3][static_cast<int>(s_tszem::NEV)]);
    }

    if (xlsx_records.has_value())
    {
        // std::println("4. XLSX rekord: {}", std::get<std::vector<std::array<std::string, 29>>>(xlsx_records.value())[3][s_xlsx::Titulus_nélküli_név]);
        auto record = (*xlsx_records)[15][s_xlsx::Titulus_nélküli_név];
        std::println("16. XLSX rekord: {}", record);
    }

    // std::cin>> std::ws;
}