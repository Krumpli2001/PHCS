#include "read_xlsx.hpp"
#include "read_dbf.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int
{
    std::println("Szia világ!");

    auto xlsx_records = read_xlsx(argv[1]);

    auto tm_records = read_dbf(argv[1], TM);
    // auto uj_records = read_dbf(argv[2], UJ);
    // auto tszem_records = read_dbf(argv[3], TSZEM);

    // if (tm_records.has_value())
    // {
    //     std::println("4. TM rekord: {}", std::get<std::vector<s_tm>>(tm_records.value())[3].TM_UNEV);
    // }

    // if (uj_records.has_value())
    // {
    //     std::println("4. UJ rekord: {}", std::get<std::vector<s_uj>>(uj_records.value())[3].NEV);
    // }

    // if (tszem_records.has_value())
    // {
    //     std::println("4. TSZEM rekord: {}", std::get<std::vector<s_tszem>>(tszem_records.value())[3].NEV);
    // }

    // if (xlsx_records.has_value())
    // {
    //     // std::println("4. XLSX rekord: {}", std::get<std::vector<std::array<std::string, 29>>>(xlsx_records.value())[3][s_xlsx::Titulus_nélküli_név]);
    //     auto record = (*xlsx_records)[3][s_xlsx::Mutató];
    //     std::println("4. XLSX rekord: {}", record);
    // }

    // std::cin>> std::ws;
}