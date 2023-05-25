#include <stdio.h>

struct mentalAttributes{
    unsigned int intelligence;
    unsigned int wits;
    unsigned int resolve;

    mentalAttributes() : intelligence(1), wits(1), resolve(1) {};
    mentalAttributes(unsigned int i, unsigned int w, unsigned int r) : intelligence(i), wits(w), resolve(r) {};
};

struct physicalAttributes{
    unsigned int strength;
    unsigned int dexterity;
    unsigned int stamina;

    physicalAttributes() : strength(1), dexterity(1), stamina(1) {};
    physicalAttributes(unsigned int s, unsigned int d, unsigned int st) : strength(s), dexterity(d), stamina(st) {};
};

struct socialAttributes{
    unsigned int presence;
    unsigned int manipulation;
    unsigned int composure;

    socialAttributes() : presence(1), manipulation(1), composure(1) {};
    socialAttributes(unsigned int p, unsigned int m, unsigned int c) : presence(p), manipulation(m), composure(c) {};
};