#include <read_dbf.hpp>

#ifdef _WIN64
#include <windows.h>
#else
#include <iconv.h>
#endif

// UTF-8-á
#ifdef _WIN64
#define CP850 CP_ACP
std::string convertToUtf8(const std::string &input, UINT codePage)
{
    int wideLen = MultiByteToWideChar(codePage, 0, input.c_str(), -1, nullptr, 0);
    std::wstring wide(wideLen, 0);
    MultiByteToWideChar(codePage, 0, input.c_str(), -1, &wide[0], wideLen);

    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string utf8(utf8Len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, &utf8[0], utf8Len, nullptr, nullptr);

    utf8.resize(utf8Len - 1); // drop null terminator
    return utf8;
}
#else
#define CP850 "CP850"
std::string convertToUtf8(const std::string &input, const std::string &fromEncoding)
{
    iconv_t cd = iconv_open("UTF-8", fromEncoding.c_str());
    if (cd == (iconv_t)-1)
        throw std::runtime_error("iconv_open failed");

    size_t inBytesLeft = input.size();
    size_t outBytesLeft = input.size() * 4; // worst case UTF-8 expansion
    std::string output(outBytesLeft, '\0');

    char *inPtr = const_cast<char *>(input.data());
    char *outPtr = &output[0];
    char *outStart = outPtr;

    if (iconv(cd, &inPtr, &inBytesLeft, &outPtr, &outBytesLeft) == (size_t)-1)
    {
        iconv_close(cd);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(cd);
    output.resize(outPtr - outStart);
    return output;
}
#endif

std::optional<std::variant<std::vector<std::array<std::string, dbf_tipus::TM>>, std::vector<std::array<std::string, dbf_tipus::UJ>>, std::vector<std::array<std::string, dbf_tipus::TSZEM>>>> read_dbf(std::string file_name, dbf_tipus tipus)
{
    DBFHandle dbf = DBFOpen(file_name.c_str(), "rb");
    if (dbf == nullptr)
    {
        return std::nullopt;
    }

    int numRecords = DBFGetRecordCount(dbf);
    int numFields = DBFGetFieldCount(dbf);

    for (int field = 0; field < numFields; field++)
    {
        // MEGLESNI
        // std::string fieldName(15, '\0');
        // file_name.resize(12);
        // char fieldName[15];

        std::array<char, 12> fieldName;
        int width, decimals;
        [[maybe_unused]] DBFFieldType type = DBFGetFieldInfo(dbf, field, fieldName.data(), &width, &decimals);
        // std::string output = convertToUtf8(fieldName.data(), "CP850");
    }

    if (tipus == dbf_tipus::TM)
    {
        std::vector<std::array<std::string, dbf_tipus::TM>> tm_records;
        tm_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            std::array<std::string, dbf_tipus::TM> record;
            for (int field = 0; field < numFields; field++)
            {
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                record[field] = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), CP850);
            }
            tm_records.push_back(record);
        }
        DBFClose(dbf);
        return tm_records;
    }
    else if (tipus == dbf_tipus::UJ)
    {
        std::vector<std::array<std::string, dbf_tipus::UJ>> uj_records;
        uj_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            std::array<std::string, dbf_tipus::UJ> record;
            for (int field = 0; field < numFields; field++)
            {
                // std::println("{}", convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850"));
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                record[field] = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), CP850);
            }
            uj_records.push_back(record);
        }
        DBFClose(dbf);
        return uj_records;
    }
    else if (tipus == dbf_tipus::TSZEM)
    {
        std::vector<std::array<std::string, dbf_tipus::TSZEM>> tszem_records;
        tszem_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            std::array<std::string, dbf_tipus::TSZEM> record;
            for (int field = 0; field < numFields; field++)
            {
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                record[field] = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), CP850);
            }
            tszem_records.push_back(record);
        }
        DBFClose(dbf);
        return tszem_records;
    }

    return std::nullopt;

    DBFClose(dbf);
}
