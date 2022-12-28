#include <Vices.h>
#include <Virtues.h>
#include <Attributes.h>
#include <Skills.h>
#include <Merits.h>
#include <vector>

class CharSheetCofd{
    private:
    std::wstring name_;
    unsigned int age_;
    Virtue virtue_;
    Vice vice_;
    std::vector<Merit> merits;
    std::string mSkillsNames[8] = {"academics","computer","crafts","investigation","medicine","occult","politics","science"};
    std::string pSkillsNames[8] = {"athletics","brawl","drive","firearms","larceny","stealth","survival","weaponry"};
    std::string sSkillsNames[8] = {"animal_ken","empathy","expression","intimidation","persuasion","socialize","streetwise","subterfuge"};

    public:
    mentalAttributes mAtt_ {1};
    physicalAttributes pAtt_ {1};
    socialAttributes sAtt_ {1};
    skillSet mSkills_ = skillSet(mSkillsNames);
    skillSet pSkills_ = skillSet(pSkillsNames);
    skillSet sSkills_ = skillSet(sSkillsNames);
    unsigned int size_ = 5;
    unsigned int speed_;
    unsigned int defense_;
    unsigned int initiative_;
    unsigned int health_;
    unsigned int willpower_;
    unsigned int integrity_;

    std::wstring name() const { return name_; }
    void name(std::wstring n) { name_ = std::move(n);}

    unsigned int age() const { return age_; }
    void age(unsigned int age) { age_ = std::move(age);}

    Virtue virtue() const { return virtue_; }
    void virtue(Virtue virtue) { virtue_ = std::move(virtue);}

    Vice vice() const { return vice_; }
    void vice(Vice vice) { vice_ = std::move(vice);}
    };