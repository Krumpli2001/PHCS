#include <read_dbf.hpp>
#include <tm.hpp>
#include <uj.hpp>

#ifdef _WIN64
#include <windows.h>
#else
#include <iconv.h>
#endif

// UTF-8-á
#ifdef _WIN64
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

void read_dbf(std::string file_name, dbf_tipus tipus)
{
    DBFHandle dbf = DBFOpen(file_name.c_str(), "rb");
    if (dbf == nullptr)
    {
        return;
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
        DBFFieldType type = DBFGetFieldInfo(dbf, field, fieldName.data(), &width, &decimals);
        std::string output = convertToUtf8(fieldName.data(), "CP850");
        // std::cout << fieldName.size() << ' ' << width << '\n';
        // std::println("{}", fieldName.data());
    }

    if (tipus == TM)
    {
        std::vector<s_tm> tm_records;
        tm_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            for (int field = 0; field < numFields; field++)
            {
                tm_records.emplace_back(); // Add a new s_tm object for each record
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                switch (field)
                {
                case 0:
                    tm_records[rec].TM_UNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    // std::println("{}", tm_records[rec].TM_UNEV);
                    break;
                case 1:
                    tm_records[rec].TM_UTIPUS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 2:
                    tm_records[rec].TM_ISZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 3:
                    tm_records[rec].TM_HNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 4:
                    tm_records[rec].TM_CIM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 5:
                    tm_records[rec].ADOSZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 6:
                    tm_records[rec].TM_KEZDATE = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 7:
                    tm_records[rec].TM_HATARIDO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 8:
                    tm_records[rec].TM_HIVHELY = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 9:
                    tm_records[rec].ELSO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 10:
                    tm_records[rec].TM_TIPUSRC = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 11:
                    tm_records[rec].SORBAN = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 12:
                    tm_records[rec].TM_JEGYZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 13:
                    tm_records[rec].TM_BIRHAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 14:
                    tm_records[rec].TM_BIRSZLS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 15:
                    tm_records[rec].TM_BIRDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 16:
                    tm_records[rec].TM_BIRO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 17:
                    tm_records[rec].TM_FNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 18:
                    tm_records[rec].TM_FIRSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 19:
                    tm_records[rec].TM_FVAROS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 20:
                    tm_records[rec].TM_FCIM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                default:
                    break;
                }
            }
            // std::cout << "\n";
        }
        std::println("{}", tm_records[2].ADOSZAM);
    }
    else if (tipus == UJ)
    {
        std::vector<s_uj> uj_records;
        uj_records.reserve(numRecords);
    }
    else if (tipus == TSZEM)
    {
        std::cout << "TSZEM\n";
    }

    // for (int rec = 0; rec < numRecords; rec++)
    // {
    //     for (int field = 0; field < numFields; field++)
    //     {
    //         if (DBFIsAttributeNULL(dbf, rec, field))
    //             continue;
    //         std::string value = DBFReadStringAttribute(dbf, rec, field);
    //         std::print("{} ", convertToUtf8(value, "CP850"));
    //     }
    //     std::cout << "\n";
    // }

    DBFClose(dbf);
}
