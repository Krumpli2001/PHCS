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

void read_dbf(std::string file_name)
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
        std::cout << fieldName.size() << ' ' << width << '\n';
        std::println("{}", fieldName.data());
    }

    for (int rec = 0; rec < numRecords; rec++)
    {
        for (int field = 0; field < numFields; field++)
        {
            if (DBFIsAttributeNULL(dbf, rec, field))
                continue;
            std::string value = DBFReadStringAttribute(dbf, rec, field);
            std::print("{} ", convertToUtf8(value, "CP850"));
        }
        std::cout << "\n";
    }

    DBFClose(dbf);
}
