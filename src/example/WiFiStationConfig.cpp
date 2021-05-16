#include <iostream>
#include <cstddef>
#include <cstring>
#include "WiFiStationConfig.h"

#ifdef __PGMSPACE_H_
const char WifiSTAConfig::KEY_SSID[]        PROGMEM = WIFI_STA_SSID;
const char WifiSTAConfig::KEY_PWD[]         PROGMEM = WIFI_STA_PWD;
const char WifiSTAConfig::SHELL_CMD[]       PROGMEM = WIFI_STA_SHELL_CMD;
const char WifiSTAConfig::SHELL_ARG_SSID[]  PROGMEM = WIFI_STA_SHELL_ARG_SSID;
const char WifiSTAConfig::SHELL_ARG_PWD[]   PROGMEM = WIFI_STA_SHELL_ARG_PWD;
#else
const char* WifiSTAConfig::KEY_SSID 		= WIFI_STA_SSID;
const char* WifiSTAConfig::KEY_PWD 			= WIFI_STA_PWD;
const char* WifiSTAConfig::SHELL_CMD 		= WIFI_STA_SHELL_CMD;
const char* WifiSTAConfig::SHELL_ARG_SSID 	= WIFI_STA_SHELL_ARG_SSID;
const char* WifiSTAConfig::SHELL_ARG_PWD 	= WIFI_STA_SHELL_ARG_PWD;
#endif

WifiSTAConfig::WifiSTAConfig() : Config(2)
{
}

WifiSTAConfig::WifiSTAConfig(size_t keySize) : Config(keySize)
{
    VALUES = new char*[keySize];
	for(int i=0; i<keySize; i++){
		VALUES[i] = NULL;
	}
}

const char* WifiSTAConfig::key(int i){
#ifdef __PGMSPACE_H_
    if (i == 0) return Config::copy_P(KEY_SSID);
    if (i == 1) return Config::copy_P(KEY_PWD);
#else
    if (i == 0) return KEY_SSID;
    if (i == 1) return KEY_PWD;
#endif
    return NULL;
}

int WifiSTAConfig::hasKey(const char* name){
#ifdef __PGMSPACE_H_
    if (strcmp_P(name, KEY_SSID) == 0) return 0;
    if (strcmp_P(name, KEY_PWD) == 0) return 1;
#else
    if (strcmp(name, KEY_SSID) == 0) return 0;
    if (strcmp(name, KEY_PWD) == 0) return 1;
#endif
    return -1;
}

const char* WifiSTAConfig::shellCmd(){
#ifdef __PGMSPACE_H_
    return Config::copy_P(SHELL_CMD);
#else
    return SHELL_CMD;
#endif
}

const char* WifiSTAConfig::shellArg(int index){
#ifdef __PGMSPACE_H_
    if (index == 0) return Config::copy_P(SHELL_ARG_SSID);
    if (index == 1) return Config::copy_P(SHELL_ARG_PWD);
#else
    if (index == 0) return KEY_SSID;
    if (index == 1) return KEY_PWD;
#endif
}

const char* WifiSTAConfig::shellArg(const char* configKeyName){
#ifdef __PGMSPACE_H_
    if (strcmp_P(configKeyName, SHELL_ARG_SSID) == 0) return Config::copy_P(SHELL_ARG_SSID);
    if (strcmp_P(configKeyName, SHELL_ARG_PWD) == 0) return Config::copy_P(SHELL_ARG_PWD);
#else
    if (strcmp(configKeyName, SHELL_ARG_SSID) == 0) return SHELL_ARG_SSID;
    if (strcmp(configKeyName, SHELL_ARG_PWD) == 0) return SHELL_ARG_PWD;
#endif
    return NULL;
}