#include <Vices.h>
#include <Virtues.h>
#include <Attributes.h>
#include <Skills.h>
#include <Merits.h>
#include <vector>

class CharSheetCofd{
    private:
    std::string name_;
    unsigned int age_;
    Virtue virtue_;
    Vice vice_;
    std::vector<Merit> merits;

    public:
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

    std::string name() const { return name_; }
    void name(std::string n) { name_ = std::move(n);}

    unsigned int age() const { return age_; }
    void age(unsigned int age) { age_ = std::move(age);}

    Virtue virtue() const { return virtue_; }
    void virtue(Virtue virtue) { virtue_ = std::move(virtue);}

    Vice vice() const { return vice_; }
    void vice(Vice vice) { vice_ = std::move(vice);}
    };