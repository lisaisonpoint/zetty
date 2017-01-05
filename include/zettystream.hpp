#ifndef ZETTYSTREAMBUF_HPP
#define ZETTYSTREAMBUF_HPP

#include <fstream>
#include <iostream>

class zettystreambuf
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
    zettystreambuf()
        : opened(0)
    {
        setp(buffer, buffer + (bufferSize-1));
        setg(buffer,buffer,buffer);
    }
    ~zettystreambuf()
    {
        close();
    }

    int is_open() { return opened; }

    zettystreambuf* open( const char* name, int open_mode );
    zettystreambuf* close();

    virtual int underflow();
    virtual int overflow(int c = EOF);
    virtual int sync();
};

class ozettystream
    : public std::ostream
    , virtual std::ios
{
private:
    zettystreambuf buf;

public:
    ozettystream()
        : std::ostream(&buf)
    {}
    ozettystream
    (
        const char* name,
        int open_mode = std::ios::out
    );
    ~ozettystream();

    void open(const char* name, int open_mode);
    void close();

    zettystreambuf* rdbuf()
    {
        return &buf;
    }
};

class izettystream
    : public std::istream
    , virtual std::ios
{
private:
    zettystreambuf buf;

public:
    izettystream()
        : std::istream(&buf)
    {}
    izettystream
    (
        const char* name,
        int open_mode = std::ios::in
    );
    ~izettystream();

    void open(const char* name, int open_mode);
    void close();

    zettystreambuf* rdbuf()
    {
        return &buf;
    }
};

#endif /* end of include guard: ZETTYSTREAMBUF_HPP */
