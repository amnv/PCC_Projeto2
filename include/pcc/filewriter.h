#ifndef FILEWRITER
#define FILEWRITER

#include <string>
#include <fstream>

class FileWriter {
private:
    std::ofstream file;
    std::string path;
    bool append; //indica se modo escrita esta com append

public:

    FileWriter(std::string path, bool append = true);

    ~FileWriter();

    void write(std::string);

    void write(int);

    void write(char);

    void flush();

    void setFile(std::string path, bool append);
};
#endif