#ifndef COMPRESS
#define COMPRESS

#include <string>

class Compress {

public:

    static void create(std::string file, std::string& text, std::string indexType, std::string algCompress = "lz78" );

    static std::string extract(std::string file, std::string& suffix);


};

#endif