#include <iostream>
#include <cstddef>
#include <cstring>
#include "Config.h"

Config::Config(size_t keySize) : KEY_COUNT(keySize)
{
    VALUES = new char*[keySize];
	for(int i=0; i<keySize; i++){
		VALUES[i] = NULL;
	}
}

int Config::keyCount(){
    return KEY_COUNT;
}

void Config::set(const char* name, const char* val){
    int idx = hasKey(name);
    if (idx < 0) return;
    
    //copy the string, to avoid delete[] accident
    int cpyl = strlen(val);
    char* cpy = new char[cpyl + 1];
    memset(cpy, 0, cpyl);
    strcpy(cpy, val);
    VALUES[idx] = cpy;
}

const char* Config::get(const char* name){
    int idx = hasKey(name);
    if (idx < 0) return NULL;
	if (!VALUES[idx]) return NULL;
    return VALUES[idx];
}