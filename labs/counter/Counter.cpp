#include "Counter.h"
#include "List.h"

// Counter Member Functions

//The default constructor creates an empty Counter.
Counter::Counter(){}

// The destructor cleans up any allocated memory.
Counter::~Counter(){}

// count() returns the number of keys stored in the counter.
size_t Counter::count() const{
    int sum = 0;
    for(auto itr = begin(); itr != end(); ++itr) {
        sum ++;
    }
    return sum;
}

// total() returns the sum of all counts in the counter.
int Counter::total() const{
    int sum = 0;
    for(auto itr = begin(); itr != end(); ++itr) {
        sum += itr.value();
    }
    return sum;
}

// inc(k, d) increments a count by a given value (default one).
void Counter::inc(const std::string& key, int by){
    list.find_add(key)->value += by;
}

// dec(k, d) decrements a count by a given value (default one).
void Counter::dec(const std::string& key, int by){
    list.find_add(key)->value -= by;
}

// del(k) removes a key from the counter, setting its count to (implicit) zero.
void Counter::del(const std::string& key){
    list.remove(key);
}

// get(k) looks up a count by key. If the key isn't present, it returns zero.
int  Counter::get(const std::string& key) const{
    if(list.find(key) == nullptr){
        return 0;
    }
    else{
        return list.find(key)->value;
    }
}

// set(k, v) sets a count by key.
void Counter::set(const std::string& key, int count){
    list.find_add(key)->value = count;
}

// begin() returns an iterator to the first-inserted item in the counter.
Counter::Iterator Counter::begin() const{
    Iterator retIter(list.head);
    return retIter;
}

// end() returns an invalid "end" iterator.
Counter::Iterator Counter::end() const{
    return nullptr;
}

const std::string& Counter::Iterator::key() const{
    return curr->key;
}


