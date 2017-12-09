#ifndef LZ77_
#define LZ77_

#include <string>
#include <pcc/filewriter.h>
#include <pcc/filereader.h>

class LZ77 {
public:
    static void encode(std::string text, FileWriter*);
    static std::string decode(FileReader*);
};

#endif