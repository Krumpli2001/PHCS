#include "read_xlsx.hpp"
#include "read_dbf.hpp"

auto main(int argc, char **argv) -> int
{
    std::print("Szia világ!");

    // read_xlsx("/home/sarvaria/source/PHCS/assets/Adózók adatai_sopron_20260923.xlsx");
    read_dbf(argv[1]);
}