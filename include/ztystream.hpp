#ifndef ztystreambuf_HPP
#define ztystreambuf_HPP

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
    ztystreambuf()
        : opened(0)
    {
        setp(buffer, buffer + (bufferSize-1));
        setg(buffer,buffer,buffer);
    }
    ~ztystreambuf()
    {
        close();
    }

    int is_open() { return opened; }

    ztystreambuf* open( const char* name, int open_mode );
    ztystreambuf* close();

    virtual int underflow();
    virtual int overflow(int c = EOF);
    virtual int sync();
};

class oztystream
    : public std::ostream
    , virtual std::ios
{
private:
    ztystreambuf buf;

public:
    oztystream()
        : std::ostream(&buf)
    {}

    oztystream
    (
        const char* name,
        int open_mode = std::ios::out
    )
        : std::ostream(&buf)
    {
        init(&buf);
        open(name, open_mode);
    }

    ~oztystream()
    {
        buf.close();
    }

    void open(const char* name, int open_mode)
    {
        if (!buf.open(name, open_mode))
            setstate(std::ios::badbit);
    }

    void close()
    {
        if ( buf.is_open())
            if ( ! buf.close())
                setstate(std::ios::badbit);
    }

    ztystreambuf* rdbuf()
    {
        return &buf;
    }
};

class iztystream
    : public std::istream
    , virtual std::ios
{
private:
    ztystreambuf buf;

public:
    iztystream()
        : std::istream(&buf)
    {}
    iztystream
    (
        const char* name,
        int open_mode = std::ios::in
    )
        : std::istream(&buf)
    {
        init(&buf);
        open(name, open_mode);
    }
    ~iztystream()
    {
        buf.close();
    }

    void open(const char* name, int open_mode)
    {
        if (!buf.open(name, open_mode))
            setstate(std::ios::badbit);
    }

    void close()
    {
        if ( buf.is_open())
            if ( ! buf.close())
                setstate(std::ios::badbit);
    }

    ztystreambuf* rdbuf()
    {
        return &buf;
    }
};

#endif /* end of include guard: ztystreambuf_HPP */
