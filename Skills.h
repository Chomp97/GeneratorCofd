#include <stdio.h>


struct skillSet{
    public:
    unsigned int points[8] {0};
    std::string names[8];
    skillSet(std::string names_[8]){
        for (size_t i = 0; i < 8; i++){
            names[i] = names_[i];
        }
    }
};

struct mentalSkills{
    unsigned int points[8] {0};
    std::string names[8] = {"academics","computer","crafts","investigation","medicine","occult","politics","science"};
};

struct physicalSkills{
    unsigned int points[8] {0};
    std::string names[8] = {"athletics","brawl","drive","firearms","larceny","stealth","survival","weaponry"};
};

struct socialSkills{
    unsigned int points[8] {0};
    std::string names[8] = {"animal_ken","empathy","expression","intimidation","persuasion","socialize","streetwise","subterfuge"};
};