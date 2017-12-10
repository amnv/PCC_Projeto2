#ifndef FILEREADER
#define FILEREADER

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

    bool peek(char&);

    bool getLine(std::string& line);

    bool getChar(char&);

    int getInt();

    void reloadFile();

    void setFile(std::string path);

    static bool exist(std::string file);

};
#endif