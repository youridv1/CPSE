#include <iostream>
#include <fstream>

#include "compressor.hpp"
#include "decompressor.hpp"

int main(void) {
    // compressor based on template with 4096 byte buffer.
    lz_compressor<4096> compressor;
    //open input
    std::ifstream f1;
    f1.open("wilhelmus.txt");
    if (!f1.is_open()) {
        std::cerr << "input file not opened";
        return -1;
    }
    // open output
    std::ofstream f2;
    f2.open("compressed.txt");
    if (!f2.is_open()) {
        std::cerr << "output file not opened";
        return -1;
    }
    //call compressor's method compress based on two lambda's
    compressor.compress(
        [&f1]() -> int { auto c = f1.get(); return f1.eof() ? '\0' : c; }, //lambda for reading
        [&f2](char c) { f2.put(c); }); //lambda for writing

    //close in- and output
    f1.close();
    f2.close();

    // open compressed version as input
    f1.open("compressed.txt");
    if (!f1.is_open()) {
        std::cerr << "compressed file not opened";
        return -1;
    }

    //decompress using decompressors method decompress based on two lambda's
    lz_decompressor decompressor;
    decompressor.decompress(
        [&f1]() -> int { auto c = f1.get(); return f1.eof() ? '\0' : c; }, // lambda for read
        [&f2](char c) { std::cout << c; }); //lambda for cout
}
