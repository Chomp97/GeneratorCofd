#include <string>

struct Merit{
    std::string name;
    unsigned int rating;
    std::string description;
    std::string prerequisites;

    Merit() : name(""), rating(0), description(""), prerequisites(""){};
    Merit(std::string n, unsigned int r) : name(std::move(n)), rating(r){};
};