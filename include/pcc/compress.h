#ifndef COMPRESS
#define COMPRESS

#include <string>

class Compress {

public:

    void create(std::string file, std::string& text);

    std::string extract(std::string file);


};

#endif