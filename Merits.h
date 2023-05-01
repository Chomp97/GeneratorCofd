#include <string>
#include <iostream>
#ifndef JSON
#define JSON
#include "nlohmann/single_include/nlohmann/json.hpp"
#endif

struct Prerequisite{
    std::string name;
    int value;

    Prerequisite(std::string n, int v) : name(std::move(n)), value(v){};
};

void to_json(nlohmann::json& j, const Prerequisite& p){
        j = nlohmann::json{{"name", p.name},{"value", p.value}};
};

void from_json(const nlohmann::json& j, Prerequisite& p){
    j.at("name").get_to(p.name);
    j.at("value").get_to(p.value);
}

struct Merit{
    std::string name;
    std::string rating;
    std::string description;
    std::vector<Prerequisite> prerequisites;

    Merit() : name(""), rating("0"), description(""){};
    Merit(std::string n, std::string r) : name(std::move(n)), rating(r){};
    Merit(std::string n, std::string r, std::string d) : name(std::move(n)), rating(r), description(d){};

    void deserialize(const nlohmann::json& json){
        name = json.at("merit_name");
        rating = json.at("merit_rating");
        description = json.at("effect");
        for(auto& element : json.at("prerequisites")){
            Prerequisite pr(element.at("noun"), element.at("rating"));
            prerequisites.push_back(pr);
        }
    }

    bool operator==(const Merit& m2){
        return this->name == m2.name;
    }
};

void to_json(nlohmann::json& j, const Merit& m){
        j = nlohmann::json{{"name", m.name},{"rating", m.rating},{"description", m.description},{"prerequisites", m.prerequisites}};
};

void from_json(const nlohmann::json& j, Merit& m){
    j.at("merit_name").get_to(m.name);
    j.at("merit_rating").get_to(m.rating);
    j.at("effect").get_to(m.description);
    // j.at("prerequisites").get_to(m.prerequisites);
}