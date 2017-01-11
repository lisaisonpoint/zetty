#include <iostream>

#include <fstream>
#include <iostream>
#include <iztystream.hpp>

iztystream::iztystream()
    : std::istream(&buf)
{
}

iztystream::iztystream
(
    const char* name,
    int open_mode
)
{
    init(&buf);
    open(name, open_mode);
}

iztystream::~iztystream()
{
    close();
}

void iztystream::open(const char* name, int open_mode)
{
    if (!buf.open(name, open_mode))
        setstate(std::ios::badbit);
}

void iztystream::close()
{
    if ( buf.is_open())
        if ( ! buf.close())
            setstate(std::ios::badbit);
}

ztystreambuf* iztystream::rdbuf()
{
    return &buf;
}
