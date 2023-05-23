#include "CharsheetCofd.h"
#include <fstream>
#include <sstream>
#include <random>
#include "name-generator/dasmig/namegen.hpp"
#ifndef JSON
#define JSON
#include "nlohmann/single_include/nlohmann/json.hpp"
#endif

#define PATH_MENTALMERITS "./jsons/mentalMerits.json"
#define PATH_PHYSICALMERITS "./jsons/physicalMerits.json"
#define PATH_SOCIALMERITS "./jsons/socialMerits.json"

void mapTheVirtues(){
    mapVirtues[Virtue::Ambitious] = "Ambitious";
    mapVirtues[Virtue::Courageous] = "Courageous";
    mapVirtues[Virtue::Generous] = "Generous";
    mapVirtues[Virtue::Honest] = "Honest";
    mapVirtues[Virtue::Hopeful] = "Hopeful";
    mapVirtues[Virtue::Humble] = "Humble";
    mapVirtues[Virtue::Just] = "Just";
    mapVirtues[Virtue::Loving] = "Loving";
    mapVirtues[Virtue::Loyal] = "Loyal";
    mapVirtues[Virtue::Patient] = "Patient";
    mapVirtues[Virtue::Peaceful] = "Peaceful";
    mapVirtues[Virtue::Righteous] = "Righteous";
    mapVirtues[Virtue::Trustworthy] = "Trustworthy";
}

void mapTheVices(){
    mapVices[Vice::Ambitious] = "Ambitious";
    mapVices[Vice::Arrogant] = "Arrogant";
    mapVices[Vice::Competitive] = "Competitive";
    mapVices[Vice::Greedy] = "Greedy";
    mapVices[Vice::Addictive] = "Addictive";
    mapVices[Vice::Corrupt] = "Corrupt";
    mapVices[Vice::Cruel] = "Cruel";
    mapVices[Vice::Deceitful] = "Deceitful";
    mapVices[Vice::Dogmatic] = "Dogmatic";
    mapVices[Vice::Hasty] = "Hasty";
    mapVices[Vice::Hateful] = "Hateful";
    mapVices[Vice::Pessimistic] = "Pessimistic";
}

class randomSheetGenerator{
    std::default_random_engine gen;
    CharSheetCofd charSheet;
    
    std::wstring generateRandomName();
    void generateRandomAttributes();
    void generateRandomSkills();
    void generateRandomMerits();
    void assignAttributeOnPivot(bool &done,unsigned int &attr, int &chunk);
    void cycleAttributeThroughPivot(int pool, unsigned int &attrPow, unsigned int &attrFin, unsigned int &attrRes);
    void cycleSkillThroughPivot(int pool, skillSet &skills);
    void assignRandomPhysicalAttr(int pool);
    void assignRandomPhysicalSkill(int pool);
    void assignRandomSocialAttr(int pool);
    void assignRandomSocialSkill(int pool);
    void assignRandomMentalAttr(int pool);
    void assignRandomMentalSkill(int pool);
    void setDerivatedAttributes();

    public:
    randomSheetGenerator() : gen(std::default_random_engine(std::random_device{}())), charSheet(CharSheetCofd()) {};
    int generateRandomChar();
    CharSheetCofd sheet() const { return charSheet;}
};

std::wstring randomSheetGenerator::generateRandomName(){
    dasmig::ng::instance().load("./name-generator/resources");
    return dasmig::ng::instance().get_name().append_surname();;
}

int randomSheetGenerator::generateRandomChar(){
    std::uniform_int_distribution<int> ageDistribution(8,80);
    std::uniform_int_distribution<int> virtueDistribution(0,int(Virtue::LastVirtue));
    std::uniform_int_distribution<int> viceDistribution(0,int(Vice::LastVice));
    mapTheVices();
    mapTheVirtues();
    charSheet.name(generateRandomName());
    charSheet.age(ageDistribution(gen));
    charSheet.virtue(static_cast<Virtue>(virtueDistribution(gen)));
    charSheet.vice(static_cast<Vice>(viceDistribution(gen)));
    generateRandomAttributes();
    generateRandomSkills();
    generateRandomMerits();
    setDerivatedAttributes();

    return 1;
}

void randomSheetGenerator::setDerivatedAttributes(){
    charSheet.size_ = 5;
    charSheet.health_ = charSheet.size_ + charSheet.pAtt_.stamina;
    charSheet.defense_ = std::min(charSheet.mAtt_.wits,charSheet.pAtt_.dexterity) + charSheet.pSkills_.points[0];
    charSheet.willpower_ = charSheet.mAtt_.resolve + charSheet.sAtt_.composure;
    charSheet.initiative_ = charSheet.pAtt_.dexterity + charSheet.sAtt_.composure;
    charSheet.speed_ = charSheet.pAtt_.strength + charSheet.pAtt_.dexterity + 5;
    charSheet.integrity_ = 7;
}

void extractMeritsIntoVector(std::vector<nlohmann::json>& jsons, std::ifstream& input_json){
    if(!input_json.is_open())        printf("I can't find the file");
    nlohmann::json json = nlohmann::json::parse(input_json);

    for(auto element = json.begin(); element != json.end(); ++element){
        if(json.is_array()) jsons.push_back(element.value());
        else jsons.push_back({element.key(), element.value()});
    }
}

void randomSheetGenerator::generateRandomMerits(){
    std::vector<Merit> merits;
    std::vector<nlohmann::json> jsons;
    std::ifstream input_json(PATH_MENTALMERITS);
    extractMeritsIntoVector(jsons, input_json);
    std::ifstream input_jsonPhys(PATH_PHYSICALMERITS);
    extractMeritsIntoVector(jsons, input_jsonPhys);
    std::ifstream input_jsonSoc(PATH_SOCIALMERITS);
    extractMeritsIntoVector(jsons, input_jsonSoc);

    for(nlohmann::json element : jsons){
        Merit merit;
        merit.deserialize(element);
        merits.push_back(merit);
    }

    merits.erase(std::remove_if(merits.begin(), merits.end(),
                [](const Merit& m1) {return !m1.prerequisites.empty();}), merits.end());

    int i = 0;
    while(i < maxMeritDots){
        std::uniform_int_distribution<int> meritArrayDistribution(0,merits.size()-1);
        int offset = meritArrayDistribution(gen);
        Merit& merit = merits.at(offset);
        int meritRating = std::stoi(merit.rating.substr(0,1));
        if((std::find(charSheet.merits.begin(),charSheet.merits.end(),merit) != charSheet.merits.end()) or meritRating > (maxMeritDots - i)) continue;
        if(merit.rating.size() > 1){
            int max = std::min(int(merit.rating.back() - '0'),maxMeritDots - i);
            std::uniform_int_distribution<int> meritRatingDistribution(meritRating,max);
            meritRating = meritRatingDistribution(gen);
        }
        charSheet.merits.push_back(Merit(merit.name,std::to_string(meritRating),merit.description));
        i += meritRating;
    }
}

void randomSheetGenerator::generateRandomSkills(){
    int distributions [] = {11,7,4};
    bool doneMental,donePhysical,doneSocial;
    doneMental = donePhysical = doneSocial = false;
    std::uniform_int_distribution<int> skillDistribution(1,3);
    for(int i = 0; i < 3; i++){
        int pool = distributions[i];
        bool goOn = false;
        int pivot = 0;
        while (!goOn){
            pivot = skillDistribution(gen);
            switch (pivot){
            case 1:
                if(!donePhysical){
                    donePhysical = goOn = true;
                    assignRandomPhysicalSkill(pool);
                }
                break;
            
            case 2:
                if(!doneMental){
                    doneMental = goOn = true;
                    assignRandomMentalSkill(pool);
                }
                break;
            
            case 3:
                if(!doneSocial){
                    doneSocial = goOn = true;
                    assignRandomSocialSkill(pool);
                }
                break;
            }
        }
    }
}

void randomSheetGenerator::generateRandomAttributes(){
    int distributions [] = {3,4,5};
    bool doneMental,donePhysical,doneSocial;
    doneMental = donePhysical = doneSocial = false;
    std::uniform_int_distribution<int> attributeDistribution(1,3);
    for(int i = 0; i < 3; i++){
        int pool = distributions[i];
        int pivot = 0;
        while (i == doneMental + doneSocial + donePhysical){
            pivot = attributeDistribution(gen);
            switch (pivot){
                case 1:
                    if (!doneMental){
                        doneMental = true;
                        assignRandomMentalAttr(pool);
                    }
                    break;
        
                case 2:
                    if (!donePhysical){
                        donePhysical = true;
                        assignRandomPhysicalAttr(pool);
                    }
                    break;

                case 3:
                    if (!doneSocial){
                        doneSocial = true;
                        assignRandomSocialAttr(pool);
                    }
                    break;
            }
        }
    }
}

void randomSheetGenerator::assignAttributeOnPivot(bool &done,unsigned int &attr, int& chunk){
    if(!done){
        done = true;
        attr += chunk;
        chunk = 0;
    }
}

void randomSheetGenerator::cycleAttributeThroughPivot(int pool, unsigned int& attrPow, unsigned int& attrFin, unsigned int& attrRes){
    bool donePow,doneFin,doneRes;
    donePow = doneFin = doneRes = false;
    while(pool > 0){
        std::uniform_int_distribution<int> assignDistribution(1,std::min(pool,4));
        int chunk = assignDistribution(gen);
        pool -= chunk;
        std::uniform_int_distribution<int> assignAttribute(1,3);
        while(chunk){
            int pivot = assignAttribute(gen);
            if (donePow && doneFin && doneRes) donePow = doneFin = doneRes = false;
            switch (pivot){
            case 1:
                assignAttributeOnPivot(donePow, attrPow, chunk);
                break;

            case 2:
                assignAttributeOnPivot(doneFin, attrFin, chunk);
                break;

            case 3:
                assignAttributeOnPivot(doneRes, attrRes, chunk);
                break;
            }
        }
    }
}

void randomSheetGenerator::cycleSkillThroughPivot(int pool, skillSet &skills){
    while(pool > 0){
        std::uniform_int_distribution<int> assignDistribution(1,std::min(pool,5)); // distribute from 1 to 5 points
        int chunk = assignDistribution(gen); // points to assign
        pool -= chunk;
        std::uniform_int_distribution<int> assignSkill(0,7); // randomize the skill we assign the points to
        int pivot = assignSkill(gen); // index of skill
        while (skills.points[pivot] + chunk > 5){
            pivot = assignSkill(gen);
        }
        skills.points[pivot] += chunk;
    }
}

void randomSheetGenerator::assignRandomPhysicalAttr(int pool){
    cycleAttributeThroughPivot(pool, charSheet.pAtt_.strength, charSheet.pAtt_.dexterity, charSheet.pAtt_.stamina);
}

void randomSheetGenerator::assignRandomPhysicalSkill(int pool){
    cycleSkillThroughPivot(pool, charSheet.mSkills_);
}

void randomSheetGenerator::assignRandomSocialAttr(int pool){
    cycleAttributeThroughPivot(pool, charSheet.sAtt_.presence, charSheet.sAtt_.manipulation, charSheet.sAtt_.composure);
}

void randomSheetGenerator::assignRandomSocialSkill(int pool){
    cycleSkillThroughPivot(pool, charSheet.pSkills_);
}

void randomSheetGenerator::assignRandomMentalAttr(int pool){
    cycleAttributeThroughPivot(pool, charSheet.mAtt_.intelligence, charSheet.mAtt_.wits, charSheet.mAtt_.resolve);
}

void randomSheetGenerator::assignRandomMentalSkill(int pool){
    cycleSkillThroughPivot(pool, charSheet.sSkills_);
}

int main(){
    for(int i = 0; i < 100; i++){
        randomSheetGenerator r = randomSheetGenerator();
        r.generateRandomChar();
        r.sheet().prettyPrint();
    }
}
