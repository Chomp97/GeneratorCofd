#include <CharsheetCofd.h>
#include <fstream>
#include <random>

void mapTheVirtues(){
    mapVirtues[Virtue::Ambitious] = "Ambitious";
    mapVirtues[Courageous] = "Courageous";
    mapVirtues[Generous] = "Generous";
    mapVirtues[Honest] = "Honest";
    mapVirtues[Hopeful] = "Hopeful";
    mapVirtues[Humble] = "Humble";
    mapVirtues[Just] = "Just";
    mapVirtues[Loving] = "Loving";
    mapVirtues[Loyal] = "Loyal";
    mapVirtues[Patient] = "Patient";
    mapVirtues[Peaceful] = "Peaceful";
    mapVirtues[Righteous] = "Righteous";
    mapVirtues[Trustworthy] = "Trustworthy";
}

void mapTheVices(){
    mapVices[Vice::Ambitious] = "Ambitious";
    mapVices[Arrogant] = "Arrogant";
    mapVices[Competitive] = "Competitive";
    mapVices[Greedy] = "Greedy";
    mapVices[Addictive] = "Addictive";
    mapVices[Corrupt] = "Corrupt";
    mapVices[Cruel] = "Cruel";
    mapVices[Deceitful] = "Deceitful";
    mapVices[Dogmatic] = "Dogmatic";
    mapVices[Hasty] = "Hasty";
    mapVices[Hateful] = "Hateful";
    mapVices[Pessimistic] = "Pessimistic";
}

class randomSheetGenerator{
    std::default_random_engine gen;
    CharSheetCofd charSheet;
    
    std::string generateRandomName();
    int generateRandomChar();
    void generateRandomAttributes();
    void generateRandomSkills();
    void generateRandomMerits();
    void assignAttributeOnPivot(bool &done,unsigned int &attr, int chunk);
    void cycleAttributeThroughPivot(int pool, unsigned int &attrPow, unsigned int &attrFin, unsigned int &attrRes);
    void cycleSkillThroughPivot(int pool, skillSet &skills);
    void assignRandomPhysicalAttr(int pool);
    void assignRandomPhysicalSkill(int pool);
    void assignRandomSocialAttr(int pool);
    void assignRandomSocialSkill(int pool);
    void assignRandomMentalAttr(int pool);
    void assignRandomMentalSkill(int pool);    
};

std::string randomSheetGenerator::generateRandomName(){
    // TODO
    return "miao";
    }

int randomSheetGenerator::generateRandomChar(){
    std::uniform_int_distribution<int> ageDistribution(8,80);
    std::uniform_int_distribution<int> virtueDistribution(0,LastVirtue);
    std::uniform_int_distribution<int> viceDistribution(0,LastVice);
    charSheet.name(generateRandomName());
    charSheet.age(ageDistribution(gen));
    charSheet.virtue(static_cast<Virtue>(virtueDistribution(gen)));
    charSheet.vice(static_cast<Vice>(viceDistribution(gen)));
    generateRandomAttributes();
    generateRandomSkills();
    // randomize merits TODO after serialization of tables
    generateRandomMerits();
}

void randomSheetGenerator::generateRandomSkills(){
    int distributions [] = {11,7,4};
    bool doneMental,donePhysical,doneSocial = false;
    std::uniform_int_distribution<int> skillDistribution(1,3);
    for(int i = 0; i < 3; i++){
        int pool = distributions[i];
        bool goOn = true;
        int pivot = 0;
        while (goOn){
            pivot = skillDistribution(gen);
            switch (pivot)
            {
            case 1:
                if(!donePhysical){
                    donePhysical = true;
                    assignRandomPhysicalSkill(pool);
                }
                break;
            
            case 2:
                if(!doneMental){
                    doneMental = true;
                    assignRandomMentalSkill(pool);
                }
                break;
            
            case 3:
                if(!doneSocial){
                    doneSocial = true;
                    assignRandomSocialSkill(pool);
                }
                break;
            
            default:
                break;
            }
        }
    }
}

void randomSheetGenerator::generateRandomAttributes(){
    int distributions [] = {3,4,5};
    bool doneMental,donePhysical,doneSocial = false;
    std::uniform_int_distribution<int> attributeDistribution(1,3);
    for(int i = 0; i < 3; i++){
        int pool = distributions[i];
        bool goOn = true;
        int pivot = 0;
        while (goOn){
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
                    break;                case 3:
                    if (!doneSocial){
                        doneSocial = true;
                        assignRandomSocialAttr(pool);
                    }
                    break;
            }
        }
    }
}

void randomSheetGenerator::assignAttributeOnPivot(bool &done,unsigned int &attr, int chunk){
    if(!done){
        done = true;
        attr = chunk;
    }
}

void randomSheetGenerator::cycleAttributeThroughPivot(int pool, unsigned int &attrPow, unsigned int &attrFin, unsigned int &attrRes){
    bool donePow,doneFin,doneRes = false;
    while(pool > 0){
        std::uniform_int_distribution<int> assignDistribution(1,pool);
        int chunk = assignDistribution(gen);
        pool -= chunk;
        std::uniform_int_distribution<int> assignAttribute(1,3);
        int pivot = assignAttribute(gen);
        bool goOn = true;
        while (goOn){
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
            pivot = assignAttribute(gen);
            goOn = donePow && doneFin && doneRes;
        }
    }
}

void randomSheetGenerator::cycleSkillThroughPivot(int pool, skillSet &skills){
    while(pool > 0){
        std::uniform_int_distribution<int> assignDistribution(1,std::min(pool,5)); // distribute from 1 to 5 points
        int chunk = assignDistribution(gen); // points to assign
        pool -= chunk;
        std::uniform_int_distribution<int> assignSkill(1,8); // randomize the skill we assign the points to
        int pivot = assignSkill(gen); // index of skill
        while (skills.points[pivot] > 0)
        {
            pivot = assignSkill(gen);
        }
        skills.points[pivot] = chunk;
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
    
}
