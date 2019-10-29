#include <iostream>
#include <fstream>

#include "compressor.hpp"
#include "decompressor.hpp"

int main(void) {
    lz_compressor<4096> compressor;

    // read ../week4/main.cpp for explanation
    std::ifstream f1;
    f1.open("wilhelmus.txt");
    if (!f1.is_open()) {
        std::cerr << "input file not opened";
        return -1;
    }

    // open asm file for output
    std::ofstream f2;
    f2.open("compressed.asm");
    if (!f2.is_open()) {
        std::cerr << "output file not opened";
        return -1;
    }

    // put necessary lines denoting cpu architecture, alignment, this being a global lable and the string
    f2 << ".cpu cortex-m0\n.data\n.align 2\n.global compressed\n\nstr: .asciz \"";

    // compress the string and put in asm output file
       compressor.compress(
          [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; },
          [ &f2 ]( char c ){ if(c != '\n'){ f2.put( c );}else{f2.put('_');}}
       );

       // put instructions for starting the decompress lable, including the start of the asciz string
       f2 <<  "\"\n\n.text\ncompressed:\n\tldr r0, =str\n\tbl decompress";
       // close in- and output
       f1.close();
       f2.close();
}
