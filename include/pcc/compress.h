#ifndef COMPRESS
#define COMPRESS

#include <string>
#include <pcc/filewriter.h>

class Compress {
private:
    FileWriter* w;

public:
    Compress(std::string file);

    void compress(std::string&);

    std::string extract(std::string);


};

#endif