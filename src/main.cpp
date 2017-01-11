#include <iostream>
#include <string>

#include <iztystream.hpp>
#include <oztystream.hpp>
#include <gzstream.hpp>

int main()
{
    std::cout << "Hello World!" << '\n';

    {
        ogzstream gz("asdf.gz");
        oztystream zty("asdf.zty");

        gz << "Hello World!" << '\n';
        zty << "Hello World!" << '\n';
    }

    {
        igzstream gz("asdf.gz");
        iztystream zty("asdf.zty");

        std::string linegz;
        std::string linezty;
        std::getline(gz, linegz);
        std::getline(zty, linezty);

        std::cout << linegz << '\n';
        std::cout << linezty << '\n';
    }
}
