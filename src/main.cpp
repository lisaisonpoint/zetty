#include <iostream>
#include <string>

#include <zettystream.hpp>
#include <gzstream.hpp>

int main()
{
    std::cout << "Hello World!" << '\n';

    {
        ogzstream gz("/home/ugi/asdf.gz");
        ozettystream zetty("/home/ugi/asdf.zty");

        gz << "Hello World!" << '\n';
        zetty << "Hello World!" << '\n';
    }

    {
        igzstream gz("/home/ugi/asdf.gz");
        izettystream zetty("/home/ugi/asdf.zty");

        std::string linegz;
        std::string linezty;
        std::getline(gz, linegz);
        std::getline(zetty, linezty);

        std::cout << linegz << '\n';
        std::cout << linezty << '\n';
    }
}
