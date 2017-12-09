#include <iostream>
#include <map>
#include <pcc/filewriter.h>
#include <pcc/filereader.h>
#include <pcc/compress.h>
#include <pcc/lz78.h>
#include <pcc/lz77.h>


using namespace std;

void Compress::create(string file, string& text, string alg) {
    /** Comprime um texto e o salva em um arquivo */
    FileWriter* w = new FileWriter(file, false);
    //
    // FileReader* r = new FileReader("/tmp/test");
    // string line;
    // text = "";
    // while (r->getLine(line)) {
    //     text += line + "\n";
    // }
    //

    if (alg == "lz77") {
        LZ77::encode(text, w);
    } else {
        LZ78::encode(text, w);
    }

    w->flush();
}

string Compress::extract(string file) {
    /** Recebe um arquivo e o extrai*/
    FileReader* reader = new FileReader(file);
    string r = ""; 
    r = LZ78::decode(reader);
    return r;
}