#include <iostream>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include "src/example/WiFiStationConfig.h"

using namespace std;

int main()
{
    const int   testCount = 4;
    const char* testName[testCount];
    bool        testResult[testCount];
    
    WifiSTAConfig config;
    
    int iter = 0;
    const char* shellStr = "#wsta ~ssid=my ssid ~pwd=my secret pwd";
    const char* shellArg[2] = {config.key(0), config.key(1)};
    const char* shellArgVal[2] = {"my ssid", "my secret pwd"};
    
    //Shell::isCmd
    const char* test_iscmd = config.shellCmd();
    testName[iter] = "Shell::isCmd()";
    testResult[iter++] = Shell::isCmd(test_iscmd, shellStr);
    
    //Shell::nextArgPosition
    testName[iter] = "Shell::nextArgPosition()";
    testResult[iter++] = Shell::nextArgPosition(shellStr) == 7;
    
    //Shell::argKey
    const char* testArgKey = shellStr;
    int pos1 = Shell::nextArgPosition(testArgKey);
    const char* kptr1 = testArgKey + pos1;
    int pos2 = Shell::nextArgPosition(kptr1);
    const char* kptr2 = kptr1 + pos2;
    const char* key1 = Shell::argKey(kptr1, strlen(kptr1));
    bool testArgKeyResult = (strncmp(key1, shellArg[0], strlen(shellArg[0])) == 0);
    const char* key2 = Shell::argKey(kptr2, strlen(kptr2));
    testArgKeyResult &= (strncmp(key2, shellArg[1], strlen(shellArg[1])) == 0);
    testName[iter] = "Shell::argKey()";
    testResult[iter++] = testArgKeyResult;
    
    //Shell::argVal
    const char* value = Shell::argVal(shellArg[0], shellStr);
    bool testArgValResult = strcmp(value, shellArgVal[0]) == 0;
    value = Shell::argVal(shellArg[1], shellStr);
    testArgValResult &= strcmp(value, shellArgVal[1]) == 0;
    testName[iter] = "Shell::argVal()";
    testResult[iter++] = testArgValResult;
    
    //Shell::argVal()
    int failed = 0;
    for (int i=0; i<testCount; i++){
        cout << "Test " << testName[i] << (testResult[i]? " passed" : " failed") << "\n";
        if (!testResult[i]){   
            failed++;
        }
    }
    
    //WifiSTAConfig::set
    for(int i=0; i<config.keyCount(); i++){
		const char* val = Shell::argVal(config.shellArg(i), shellStr);
		if (val && strlen(val) > 0){
			config.set(config.key(i), val);
			cout << config.key(i) << ": " << config.get(config.key(i)) << "\n";
		}
	}
    
    
    //TEST Result
    cout << "Test Count: " << testCount << "\n";
    cout << "Test Failed: " << failed << "\n";
    return 0;
}
