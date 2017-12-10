#ifndef LZ78_
#define LZ78_

#include <string> 
#include <pcc/filewriter.h>
#include <pcc/filereader.h>

class LZ78 {
public:
    static void encode(std::string text, FileWriter*);
    static std::string decode(FileReader*);
};

#endif