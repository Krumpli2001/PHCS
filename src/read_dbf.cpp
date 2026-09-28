#include <read_dbf.hpp>

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

std::optional<std::variant<std::vector<s_tm>, std::vector<s_uj>, std::vector<s_tszem>>> read_dbf(std::string file_name, dbf_tipus tipus)
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
        DBFFieldType type = DBFGetFieldInfo(dbf, field, fieldName.data(), &width, &decimals);
        // std::string output = convertToUtf8(fieldName.data(), "CP850");
    }

    if (tipus == TM)
    {
        std::vector<s_tm> tm_records;
        tm_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            for (int field = 0; field < numFields; field++)
            {
                s_tm record;
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                switch (field)
                {
                case 0:
                    record.TM_UNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 1:
                    record.TM_UTIPUS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 2:
                    record.TM_ISZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 3:
                    record.TM_HNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 4:
                    record.TM_CIM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 5:
                    record.ADOSZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 6:
                    record.TM_KEZDATE = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 7:
                    record.TM_HATARIDO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 8:
                    record.TM_HIVHELY = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 9:
                    record.ELSO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 10:
                    record.TM_TIPUSRC = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 11:
                    record.SORBAN = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 12:
                    record.TM_JEGYZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 13:
                    record.TM_BIRHAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 14:
                    record.TM_BIRSZLS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 15:
                    record.TM_BIRDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 16:
                    record.TM_BIRO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 17:
                    record.TM_FNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 18:
                    record.TM_FIRSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 19:
                    record.TM_FVAROS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 20:
                    record.TM_FCIM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                default:
                    break;
                }
                tm_records.push_back(record);
            }
        }
        return tm_records;
    }
    else if (tipus == UJ)
    {
        std::vector<s_uj> uj_records;
        uj_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            for (int field = 0; field < numFields; field++)
            {
                // std::println("{}", convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850"));
                s_uj record;
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                switch (field)
                {
                case 0:
                    record.NEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 1:
                    record.VAROS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 2:
                    record.UTCA = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 3:
                    record.ADOSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 4:
                    record.IRSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 5:
                    record.KDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 6:
                    record.VDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 7:
                    record.UJ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 8:
                    record.RDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 9:
                    record.MDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 10:
                    record.CSODTIP = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 11:
                    record.HSZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 12:
                    record.RKOD = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 13:
                    record.RIDO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 14:
                    record.MODOSIT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 15:
                    record.JEGYZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 16:
                    record.BIRHAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 17:
                    record.BIRSZLSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 18:
                    record.BIRDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 19:
                    record.BIRO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 20:
                    record.FNEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 21:
                    record.FIRSZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 22:
                    record.FVAROS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 23:
                    record.FCIM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 24:
                    record.REKORD = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                default:
                    break;
                }
                uj_records.push_back(record);
            }
        }

        std::println("4. UJ rekord: {}", uj_records[3].NEV);
        return uj_records;
    }
    else if (tipus == TSZEM)
    {
        std::vector<s_tszem> tszem_records;
        tszem_records.reserve(numRecords);

        for (int rec = 0; rec < numRecords; rec++)
        {
            for (int field = 0; field < numFields; field++)
            {
                s_tszem record;
                if (DBFIsAttributeNULL(dbf, rec, field))
                    continue;
                switch (field)
                {
                case 0:
                    record.MUTATO = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 1:
                    record.SZEMSZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 2:
                    record.NEV = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 3:
                    record.ORSZAG = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 4:
                    record.IR_SZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 5:
                    record.UT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 6:
                    record.MEGJ_JELZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 7:
                    record.MEGJ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 8:
                    record.MOD_DAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 9:
                    record.TIPUS_JELZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 10:
                    record.TULTIP = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 11:
                    record.KONYVVEZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 12:
                    record.TARSASAG = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 13:
                    record.ERV_ATIPUS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 14:
                    record.AKT_ATIPUS = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 15:
                    record.AGAZAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 16:
                    record.ERTKOD = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 17:
                    record.SZULDAT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 18:
                    record.K_AZON = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 19:
                    record.JEL1 = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 20:
                    record.JEL2 = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 21:
                    record.JEL3 = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 22:
                    record.JEL4 = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 23:
                    record.ALLKOD = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 24:
                    record.CSOPMEGJEL = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 25:
                    record.TORLOKA = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 26:
                    record.KOVTRANZ = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 27:
                    record.HELYSEG = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 28:
                    record.LEVORSZAG = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 29:
                    record.LEVIR_SZAM = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 30:
                    record.LEVUT = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 31:
                    record.NEV_PTR = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 32:
                    record.CIM_PTR = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 33:
                    record.LEVCIM_PTR = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                case 34:
                    record.ELUGY = convertToUtf8(DBFReadStringAttribute(dbf, rec, field), "CP850");
                    break;
                default:
                    break;
                }
                tszem_records.push_back(record);
            }
        }
        return tszem_records;
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

    return std::nullopt;

    DBFClose(dbf);
}
