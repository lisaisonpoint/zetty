#ifndef IZTYSTREAM_HPP
#define IZTYSTREAM_HPP

#include <fstream>
#include <iostream>

#include <ztystreambuf.hpp>

class iztystream
    : public std::istream
    , virtual std::ios
{
private:
    ztystreambuf buf;

public:
    iztystream();
    iztystream(const char* name, int open_mode = std::ios::in);

    ~iztystream();

    void open(const char* name, int open_mode);
    void close();

    ztystreambuf* rdbuf();
};


#endif /* end of include guard: IZTYSTREAM_HPP */
