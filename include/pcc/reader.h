#include <string>
#include <fstream>

class Reader {
private:
    std::ifstream file;
    std::string path;

public:

    Reader(std::string path);

    ~Reader();

    bool getLine(std::string& line);

    void reloadFile();

    void setFile(std::string path);

};