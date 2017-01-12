#include <iostream>
#include <string>

#include <iztystream.hpp>
#include <oztystream.hpp>
#include <gzstream.hpp>
#include <fstream>

int main()
{
    std::cout << "Hello World!" << '\n';

    auto file = fopen("resources/alpha.water", "r");

    {
        //ogzstream gz("resources/comp.gz");
        std::ifstream file("resources/alpha.water");
        std::noskipws(file);
        oztystream zty("resources/comp.zty");

        //std::cout << "writing for gzip..." << '\n';
        //gz << "Hello World!" << '\n';

        uint8_t x;
        while (file >> x)
            zty << x;

        //std::cout << "writing for zetty..." << '\n';
        //zty << "Hello World!" << '\n';
    }

    {
        //igzstream gz("resources/comp.gz");
        iztystream zty("resources/comp.zty");

        std::string linegz;
        std::string linezty;

        //std::cout << "reading for gzip..." << '\n';
        //std::getline(gz, linegz);
        //std::cout << "reading for zetty..." << '\n';
        //std::getline(zty, linezty);

        //std::cout << linegz << '\n';
        //std::cout << linezty << '\n';
    }
}
