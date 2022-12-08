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
    
    std::string generateRandomName(){
        // TODO
        return "miao";
    }

    int generateRandomChar(){
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

    void generateRandomAttributes(){
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

    void assignAttributeOnPivot(bool &done,unsigned int &attr, int chunk){
        if(!done){
            done = true;
            attr = chunk;
        }
    }

    void cycleThroughPivot(int pool, unsigned int &attrPow, unsigned int &attrFin, unsigned int &attrRes){
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

    void assignRandomPhysicalAttr(int pool){
        cycleThroughPivot(pool, charSheet.pAtt_.strength, charSheet.pAtt_.dexterity, charSheet.pAtt_.stamina);
    }

    void assignRandomSocialAttr(int pool){
        cycleThroughPivot(pool, charSheet.sAtt_.presence, charSheet.sAtt_.manipulation, charSheet.sAtt_.composure);
    }

    void assignRandomMentalAttr(int pool){
        cycleThroughPivot(pool, charSheet.mAtt_.intelligence, charSheet.mAtt_.wits, charSheet.mAtt_.resolve);
    }

    void generateRandomMerits(){

    }

    void generateRandomSkills(){
        
    }
};

int main(){
    
}
