#ifndef COMPRESS
#define COMPRESS

#include <string>

class Compress {

public:

    static void create(std::string file, std::string& text);

    static std::string extract(std::string file);


};

#endif