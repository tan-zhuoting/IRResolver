#include <iostream>
#include <fstream>

#include "IRResolver.hpp"

int main(int argc, char** argv)
{
    IRResolver irr;
    std::ifstream ifs(argv[1]);
    std::string line;
    while (std::getline(ifs, line)) {
        irr.add_record(line);
    }
    ifs.close();
    while (true) {
        std::cout << "Please input frequency (0 to quit)\n";
        unsigned n;
        std::cin >> n;
        if (n == 0) {
            break;
        }
        auto recs = irr.find_records(n);
        for (auto& r : recs) {
            std::cout << *r << std::endl;
        }
    }

    return 0;
}
