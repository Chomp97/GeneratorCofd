#include <string>

struct Merit{
    std::string name;
    unsigned int dots;

    Merit(std::string n, unsigned int d) : name(std::move(n)), dots(d){};
};