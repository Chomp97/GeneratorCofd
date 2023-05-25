#include "headers\Randomsheetgenerator.hpp"

int main(){
    randomSheetGenerator r = randomSheetGenerator();
    r.generateRandomChar();
    r.sheet().prettyPrint();
}