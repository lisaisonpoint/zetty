#ifndef ZTYSTREAMBUF_HPP
#define ZTYSTREAMBUF_HPP

#include <fstream>
#include <iostream>

class ztystreambuf
    : public std::streambuf
{
private:
    static const int bufferSize = 300;

    FILE* file;
    char buffer[bufferSize];
    int opened;
    int mode;

    int flush_buffer();

public:
    ztystreambuf();

    ~ztystreambuf();

    int is_open();

    ztystreambuf* open( const char* name, int open_mode );
    ztystreambuf* close();

    virtual int underflow();
    virtual int overflow(int c = EOF);
    virtual int sync();
};



#endif /* end of include guard: ZTYSTREAMBUF_HPP */
