#include "read_xlsx.hpp"

std::string cellToString(const OpenXLSX::XLCellValue& value) {
    switch (value.type()) {
        case OpenXLSX::XLValueType::Empty:   return "";
        case OpenXLSX::XLValueType::Boolean: return std::to_string(value.get<bool>());
        case OpenXLSX::XLValueType::Integer: return std::to_string(value.get<int64_t>());
        case OpenXLSX::XLValueType::Float:   return std::to_string(value.get<double>());
        case OpenXLSX::XLValueType::String:  return value.get<std::string>();
        case OpenXLSX::XLValueType::Error:   return "[error]";
        default:                             return "";
    }
}

void read_xlsx(std::string file_name){
    OpenXLSX::XLDocument doc;
    doc.open(file_name);
    auto wks = doc.workbook().worksheet("Adózók adatai");

    auto range = wks.range(); // full used range
    for (const auto& row : wks.rows()) {
        auto values = std::vector<OpenXLSX::XLCellValue>(row.values());
        for (const auto& value : values) {
            std::cout << cellToString(value) << "\t";
        }
        std::cout << "\n";
    }

    doc.close();
}