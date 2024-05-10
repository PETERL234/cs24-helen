#include "Person.h"
#include "GenePool.h"

// Person Member Functions

Person::Person(std::string name, std::string gender, Person* motherPtr, Person* fatherPtr){
    this->mem_name = name;
    this->mem_gender = gender;
    mem_mother = motherPtr;
    mem_father = fatherPtr;
    if(mem_father != nullptr){
        mem_father->mem_children.insert(this);
    }
    if(mem_mother != nullptr){
        mem_mother->mem_children.insert(this);
    }
}

Person::~Person(){}

const std::string& Person::name() const{
    return mem_name;
}
Gender  Person::gender() const{
    Gender retGender;
    if(mem_gender == "male"){
        retGender = Gender::MALE;
    }
    else if(mem_gender == "female"){
        retGender = Gender::FEMALE;
    }
    else{
        retGender = Gender::ANY;
    }
    return retGender;
}

Person* Person::mother(){
    return mem_mother;
}
Person* Person::father(){
    return mem_father;
}

std::set<Person*> Person::ancestors(PMod pmod){
    std::set<Person*> empty; //not written
    return empty;
}
std::set<Person*> Person::aunts(PMod pmod, SMod smod){
    std::set<Person*> empty; //not written
    return empty;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod){
    std::set<Person*> output;
    std::set<Person*> mem_siblings = siblings(pmod, smod);
    for (auto it = mem_siblings.begin(); it != mem_siblings.end(); ++it) {
        Person* person = *it;
        if(person->gender() == Gender::MALE){
            output.insert(person);
        }
    }
    return output;
}

std::set<Person*> Person::children(){
    return mem_children;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod){
    std::set<Person*> empty; //not written
    return empty;
}

std::set<Person*> Person::daughters(){
    std::set<Person*> output;
    for (auto it = mem_children.begin(); it != mem_children.end(); ++it) {
        if(this->gender() == Gender::FEMALE){
            output.insert(*it);
        }
    }
    return output;
}

std::set<Person*> Person::descendants(){
    std::set<Person*> empty; //not written
    return empty;
}

std::set<Person*> Person::grandchildren(){
    std::set<Person*> output;
    for(Person* person: mem_children){
        output.insert(person->mem_children.begin(), person->mem_children.end());
    }
    return output;
}

std::set<Person*> Person::granddaughters(){
    std::set<Person*> output;
    std::set<Person*> grandc = grandchildren();
    for (auto it = grandc.begin(); it != grandc.end(); ++it) {
        if(this->gender() == Gender::MALE){
            output.insert(*it);
        }
    }
    return output;
}

std::set<Person*> Person::grandfathers(PMod pmod){
    std::set<Person*> output;
    if(mem_mother != nullptr && mem_mother->mem_mother != nullptr && pmod == PMod::MATERNAL){
        output.insert(mem_mother->mem_father);
    }
    else if(mem_father != nullptr && mem_father->mem_father != nullptr && pmod == PMod::PATERNAL){
        output.insert(mem_father->mem_father);
    }
    else{
        if(mem_mother != nullptr && mem_mother->mem_mother != nullptr){
            output.insert(mem_mother->mem_father);
        }
        else if(mem_father != nullptr && mem_father->mem_father != nullptr){
            output.insert(mem_father->mem_father);
        }
    }
    return output;
}

std::set<Person*> Person::grandmothers(PMod pmod){
    std::set<Person*> output;
    if(mem_mother != nullptr && mem_mother->mem_mother != nullptr && pmod == PMod::MATERNAL){
        output.insert(mem_mother->mem_mother);
    }
    else if(mem_father != nullptr && mem_father->mem_father != nullptr && pmod == PMod::PATERNAL){
        output.insert(mem_father->mem_mother);
    }
    else{
        if(mem_mother != nullptr && mem_mother->mem_mother != nullptr){
            output.insert(mem_mother->mem_mother);
        }
        else if(mem_father != nullptr && mem_father->mem_father != nullptr){
            output.insert(mem_father->mem_mother);
        }
    }
    return output;
}

std::set<Person*> Person::grandparents(PMod pmod){
    std::set<Person*> output;
    if(pmod == PMod::MATERNAL){
        if(mem_mother != nullptr){
            return mem_mother->parents();
        }
        else{
            return output;
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mem_father != nullptr){
            return mem_father->parents();
        }
        else{
            return output;
        }
    }
    else{
        if(mem_mother != nullptr){
            output.insert(mem_mother->parents().begin(), mem_mother->parents().end());
        }
        if(mem_father != nullptr){
            output.insert(mem_father->parents().begin(), mem_father->parents().end());
        }
        return output;
    }
}

std::set<Person*> Person::grandsons(){
    std::set<Person*> empty; //not written
    return empty;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    std::set<Person*> empty; //not written
    return empty;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    std::set<Person*> empty; //not written
    return empty;
}

std::set<Person*> Person::parents(PMod pmod){
    std::set<Person*> output;
    if(mem_mother != nullptr && pmod != PMod::PATERNAL){
        output.insert(mem_mother);
    }
    if(mem_father != nullptr && pmod != PMod::MATERNAL){
        output.insert(mem_father);
    }
    return output;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod){
    std::set<Person*> output;
    if(pmod == PMod::MATERNAL){
        if(mem_mother != nullptr){
            output.insert(mem_mother->mem_children.begin(), mem_mother->mem_children.end());
        }
    }
    else if(pmod == PMod::PATERNAL){
        if(mem_father != nullptr){
            output.insert(mem_father->mem_children.begin(), mem_father->mem_children.end());
        }
    }
    else{
        if(mem_mother != nullptr){
            output.insert(mem_mother->mem_children.begin(), mem_mother->mem_children.end());
        }
        if(mem_father != nullptr){
            output.insert(mem_father->mem_children.begin(), mem_father->mem_children.end());
        }
    }
    // return output;
    if(mem_mother != nullptr || mem_father != nullptr){ //加这行以免output是空的
        if(smod == SMod::HALF){
            for (auto it = output.begin(); it != output.end(); ) {
                Person* person = *it;
                if (person->mem_father != nullptr && person->mem_mother != nullptr
                && person->mem_father == mem_father && person->mem_mother == mem_mother) {
                    it = output.erase(it);
                } else {
                    ++it;
                }
            }
        }
        else if(smod == SMod::FULL){
            for (auto it = output.begin(); it != output.end(); ) {
                Person* person = *it;
                if (person->mem_father == nullptr || person->mem_mother == nullptr
                    || person->mem_father != mem_father || person->mem_mother != mem_mother) {
                    it = output.erase(it);
                } else {
                    ++it;
                }
            }
        }
        else{
            for (auto it = output.begin(); it != output.end(); ) {
                Person* person = *it;
                if ((person->mem_father == nullptr && person->mem_mother == nullptr)
                ||
                (person->mem_father == nullptr && person->mem_mother != mem_mother)
                ||
                (person->mem_mother == nullptr && person->mem_father != mem_father)) {
                    it = output.erase(it);
                } else {
                    ++it;
                }
            }
        }
        output.erase(this);
    }
    return output;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    std::set<Person*> output;
    std::set<Person*> mem_siblings = siblings(pmod, smod);
    for (auto it = mem_siblings.begin(); it != mem_siblings.end(); ++it) {
        Person* person = *it;
        if(person->gender() == Gender::FEMALE){
            output.insert(person);
        }
    }
    return output;
}

std::set<Person*> Person::sons(){
    std::set<Person*> output;
    for (auto it = mem_children.begin(); it != mem_children.end(); ++it) {
        if(this->gender() == Gender::MALE){
            output.insert(*it);
        }
    }
    return output;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod){
    std::set<Person*> empty; //not written
    return empty;
}