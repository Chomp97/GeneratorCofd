#include <Vices.h>
#include <Virtues.h>
#include <Attributes.h>
#include <Skills.h>

class CharSheetCofd{
    private:
    std::string name_;
    unsigned int age_;
    Virtue virtue_;
    Vice vice_;
    mentalAttributes mAtt_ {1};
    physicalAttributes pAtt_ {1};
    socialAttributes sAtt_ {1};
    mentalSkills mSkills_ {0};
    physicalSkills pSkills_ {0};
    socialSkills sSkills_ {0};
    unsigned int size_ = 5;
    unsigned int speed_;
    unsigned int defense_;
    unsigned int initiative_;
    unsigned int health_;
    unsigned int willpower_;
    unsigned int integrity_;

    public:
        std::string name() const { return name_; }
        void name(std::string n) { name_ = std::move(n);}

        unsigned int age() const { return age_; }
        void name(unsigned int age) { age_ = std::move(age);}
    };