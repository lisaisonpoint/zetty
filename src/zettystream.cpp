#include <iostream>

#include <zettystream.hpp>

zettystreambuf* zettystreambuf::open(const char* name, int open_mode)
{
    if (opened)
        return 0;

    mode = open_mode;
    if
    (
        (mode & std::ios::ate)
     || (mode & std::ios::app)
     || ((mode & std::ios::in) && (mode & std::ios::out))
    )
        return 0;

    char  fmode[10];
    char* fmodeptr = fmode;
    if ( mode & std::ios::in)
        *fmodeptr++ = 'r';
    else if ( mode & std::ios::out)
        *fmodeptr++ = 'w';
    *fmodeptr++ = 'b';
    *fmodeptr = '\0';
    file = fopen(name, fmode);

    if (file == 0)
        return 0;
    opened = 1;

    return this;
}

zettystreambuf* zettystreambuf::close()
{
    if (opened)
    {
        sync();
        opened = 0;
        if (fclose(file) == 0)
            return this;
    }
    return 0;
}

int zettystreambuf::flush_buffer()
{
    int w = pptr() - pbase();
    /*
    Here we put the algorithm for compressing the data, we have to
    determine whether we flush it by the width and/or its content.

    Before writing the algorithm, we are going to test it with just simple
    file writing. It will just write the character it gets.
    */

    if (fwrite(pbase(), 1, w, file) == EOF)
        return EOF;
    pbump(-w);

    return w;
}

// ouput to a file
int zettystreambuf::overflow(int c)
{
    std::cout << "overflow" << '\n';
    if (!( mode & std::ios::out) || !opened)
        return EOF;
    if (c != EOF)
    {
        *pptr() = c;
        pbump(1);
    }
    if (flush_buffer() == EOF)
        return EOF;
    return c;
}

// input to a file
int zettystreambuf::underflow()
{
    std::cout << "underflow zetty" << '\n';
    if ( ! (mode & std::ios::in) || ! opened)
        return EOF;

    int num = fread(buffer, 1, bufferSize, file);

    if (num <= 0)
        return EOF;

    setg(buffer, buffer, buffer+num);

    return *reinterpret_cast<unsigned char*>(gptr());
}

int zettystreambuf::sync()
{
    std::cout << "sync" << '\n';
    if ( pptr() && pptr() > pbase()) {
        if ( flush_buffer() == EOF)
            return -1;
    }
    return 0;
}

ozettystream::ozettystream
(
    const char* name,
    int open_mode
)
    : std::ostream(&buf)
{
    init(&buf);
    open(name, open_mode);
}

ozettystream::~ozettystream()
{
    buf.close();
}

void ozettystream::open(const char* name, int open_mode)
{
    if (!buf.open(name, open_mode))
        setstate(std::ios::badbit);
}

void ozettystream::close()
{
    if ( buf.is_open())
        if ( ! buf.close())
            setstate(std::ios::badbit);
}

izettystream::izettystream
(
    const char* name,
    int open_mode
)
    : std::istream(&buf)
{
    init(&buf);
    open(name, open_mode);
}

izettystream::~izettystream()
{
    buf.close();
}

void izettystream::open(const char* name, int open_mode)
{
    if (!buf.open(name, open_mode))
        setstate(std::ios::badbit);
}

void izettystream::close()
{
    if ( buf.is_open())
        if ( ! buf.close())
            setstate(std::ios::badbit);
}
