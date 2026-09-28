#include "read_xlsx.hpp"
#include "read_dbf.hpp"

auto main(int argc, char **argv) -> int
{
    std::println("Szia világ!");

    // read_xlsx("/home/sarvaria/source/PHCS/assets/Adózók adatai_sopron_20260923.xlsx");
    auto tm_records = read_dbf(argv[1], TM);
    auto uj_records = read_dbf(argv[2], UJ);
    auto tszem_records = read_dbf(argv[3], TSZEM);

    if (tm_records.has_value()) {
        std::println("4. TM rekord: {}", std::get<std::vector<s_tm>>(tm_records.value())[3].TM_UNEV);
    }

    if (uj_records.has_value()) {
        std::println("4. UJ rekord: {}", std::get<std::vector<s_uj>>(uj_records.value())[3].NEV);
    }

    if (tszem_records.has_value()) {
        std::println("4. TSZEM rekord: {}", std::get<std::vector<s_tszem>>(tszem_records.value())[3].NEV);
    }

    // std::cin>> std::ws;
}