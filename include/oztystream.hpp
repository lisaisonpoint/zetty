#ifndef OZTYSTREAM_HPP
#define OZTYSTREAM_HPP

#include <fstream>
#include <iostream>

#include <ztystreambuf.hpp>

class oztystream
    : public std::ostream
    , virtual std::ios
{
private:
    ztystreambuf buf;

public:
    oztystream();
    oztystream(const char* name, int open_mode = std::ios::out);

    ~oztystream();

    void open(const char* name, int open_mode);
    void close();

    ztystreambuf* rdbuf();
};


#endif /* end of include guard: OZTYSTREAM_HPP */
