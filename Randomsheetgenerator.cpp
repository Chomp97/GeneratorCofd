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
        return "miao";
    }

    int generateRandomChar(){
        std::uniform_int_distribution<int> ageDistribution(8,80);
        std::uniform_int_distribution<int> virtueDistribution(0,LastVice);
        std::uniform_int_distribution<int> viceDistribution(0,LastVice);
        charSheet.name(generateRandomName());
        charSheet.age(ageDistribution(gen));
        charSheet.virtue(static_cast<Virtue>(virtueDistribution(gen)));
        charSheet.vice(static_cast<Vice>(viceDistribution(gen)));
    }
};

int main(){
    
}
