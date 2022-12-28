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