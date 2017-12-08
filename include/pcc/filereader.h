#include <string>
#include <fstream>

class FileReader {
private:
    std::ifstream file;
    std::string path;

public:

    FileReader(std::string path);

    ~FileReader();

    bool eof();

    char peek();

    bool getLine(std::string& line);

    char getChar();

    int getInt();

    void reloadFile();

    void setFile(std::string path);

};