#include "Vices.h"
#include "Virtues.h"
#include "Attributes.h"
#include "Skills.h"
#include "Merits.h"
#include <vector>
#define maxMeritDots 7
#ifndef JSON
#define JSON
#include "../nlohmann/single_include/nlohmann/json.hpp"
#endif

class CharSheetCofd{
    private:
    std::wstring name_;
    unsigned int age_;
    Virtue virtue_;
    Vice vice_;
    std::string mSkillsNames[8] = {"academics","computer","crafts","investigation","medicine","occult","politics","science"};
    std::string pSkillsNames[8] = {"athletics","brawl","drive","firearms","larceny","stealth","survival","weaponry"};
    std::string sSkillsNames[8] = {"animal_ken","empathy","expression","intimidation","persuasion","socialize","streetwise","subterfuge"};

    public:
    std::vector<Merit> merits;
    mentalAttributes mAtt_ = mentalAttributes();
    physicalAttributes pAtt_ = physicalAttributes();
    socialAttributes sAtt_ = socialAttributes();
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

    nlohmann::json toJson(){
        nlohmann::json sheet;
        sheet["name"] = name_;
        sheet["age"] = age_;
        sheet["virtue"] = virtue_;
        sheet["vice"] = vice_;
        sheet["mental_attributes"] = {
            {"intelligence",mAtt_.intelligence},
            {"wits",mAtt_.wits},
            {"resolve",mAtt_.resolve}
        };
        sheet["phisycal_attributes"] = {
            {"strength",pAtt_.strength},
            {"dexterity",pAtt_.dexterity},
            {"stamina",pAtt_.stamina}
        };
        sheet["social_attributes"] = {
            {"presence",sAtt_.presence},
            {"manipulation",sAtt_.manipulation},
            {"composure",sAtt_.composure}
        };
        sheet["mental_skills_names"] = mSkills_.names;
        sheet["mental_skills_points"] = mSkills_.points; 
        sheet["physical_skills_names"] = pSkills_.names;
        sheet["physical_skills_points"] = pSkills_.points; 
        sheet["social_skills_names"] = sSkills_.names;
        sheet["social_skills_points"] = sSkills_.points;
        sheet["merits"] = merits;
        sheet["size"] = size_;
        sheet["speed"] = speed_;
        sheet["defense"] = defense_;
        sheet["initiative"] = initiative_;
        sheet["health"] = health_;
        sheet["willpower"] = willpower_;
        sheet["integrity"] = integrity_;
        return sheet;
    }

    void prettyPrint(){
        std::wcout << name_ << std::endl;
        std::cout <<  "Age: " + std::to_string(age_) + ", Virtue: " + mapVirtues[virtue_] + ", Vice: " + mapVices[vice_] << std::endl;
        std::cout << "Intelligence: " + std::to_string(mAtt_.intelligence) + " Strength: " + std::to_string(pAtt_.strength) + " Presence: " + std::to_string(sAtt_.presence)
         << std::endl;
        std::cout << "Wits: " + std::to_string(mAtt_.wits) + " Dexterity: " + std::to_string(pAtt_.dexterity) + " Manipulation: " + std::to_string(sAtt_.manipulation)
         << std::endl;
        std::cout << "Resolve: " + std::to_string(mAtt_.resolve) + " Stamina: " + std::to_string(pAtt_.stamina) + " Composure: " + std::to_string(sAtt_.composure)
         << std::endl;
        for(int i = 0; i < sizeof(mSkills_.names)/sizeof(mSkills_.names[0]); i++){
            std::cout << mSkills_.names[i] + ": " + std::to_string(mSkills_.points[i]) + " ";
        }
        std::cout << std::endl;
        for(int i = 0; i < sizeof(pSkills_.names)/sizeof(pSkills_.names[0]); i++){
            std::cout << pSkills_.names[i] + ": " + std::to_string(pSkills_.points[i]) + " ";
        }
        std::cout << std::endl;
        for(int i = 0; i < sizeof(sSkills_.names)/sizeof(sSkills_.names[0]); i++){
            std::cout << sSkills_.names[i] + ": " + std::to_string(sSkills_.points[i]) + " ";
        }
        std::cout << std::endl;
        std::cout << "Merits:" << std::endl;
        for(Merit& m : merits){
            std::cout << m.name + " " + m.rating + ": " + m.description << std::endl;
        }
        std::cout << "Other Traits: " << std::endl;
        std::cout << "Health: " + std::to_string(health_) + " Willpower: " + std::to_string(willpower_) + " Defense: " + std::to_string(defense_) << std::endl;
        std::cout << "Size: " + std::to_string(size_) + " Speed: " + std::to_string(speed_) + " Initiative: " + std::to_string(initiative_) << std::endl;
        std::cout << "Integrity: " + std::to_string(integrity_) << std::endl;
    }
};