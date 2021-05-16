#ifndef arduino_wifista_h
#define arduino_wifista_h

#include "../ShellDescriptor.h"
#include "../Config.h"

//Shell script arguments
#define WIFI_STA_SHELL_CMD "wsta"
#define WIFI_STA_SHELL_ARG_SSID "s"
#define WIFI_STA_SHELL_ARG_PWD "p"

//Config keys 
//example use different value between Config keys & Shell Script arguments
//uncomment below if you want to use same value for Config Key & Shell Arg
#define WIFI_STA_SSID "ssid"
#define WIFI_STA_PWD "pwd"
//#define WIFI_STA_SSID WIFI_STA_SHELL_ARG_SSID
//#define WIFI_STA_PWD WIFI_STA_SHELL_ARG_PWD

struct WifiSTAConfig : Config, ShellDescriptor{

#ifdef __PGMSPACE_H_
    static const char KEY_SSID[] PROGMEM;
    static const char KEY_PWD[]  PROGMEM;
    
    static const char SHELL_CMD[] PROGMEM;
    static const char SHELL_ARG_SSID[] PROGMEM;
    static const char SHELL_ARG_PWD[] PROGMEM;
#else
    static const char* KEY_SSID;
    static const char* KEY_PWD;
    
    static const char* SHELL_CMD;
    static const char* SHELL_ARG_SSID;
    static const char* SHELL_ARG_PWD;
#endif
    
    WifiSTAConfig();
    
    WifiSTAConfig(size_t keySize);
    
    //Config
    const char* key(int i);
    int         hasKey(const char* name);
	
	//ShellDescriptor
	const char* shellCmd();
	const char* shellArg(int index);
    const char* shellArg(const char* configKeyName);
    
};

#endif