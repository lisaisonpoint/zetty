#include <iostream>

#include <fstream>
#include <iostream>
#include <oztystream.hpp>

oztystream::oztystream()
    : std::ostream(&buf)
{
}

oztystream::oztystream
(
    const char* name,
    int open_mode
)
{
    init(&buf);
    open(name, open_mode);
}

oztystream::~oztystream()
{
    close();
}

void oztystream::open(const char* name, int open_mode)
{
    if (!buf.open(name, open_mode))
        setstate(std::ios::badbit);
}

void oztystream::close()
{
    if ( buf.is_open())
        if ( ! buf.close())
            setstate(std::ios::badbit);
}

ztystreambuf* oztystream::rdbuf()
{
    return &buf;
}
