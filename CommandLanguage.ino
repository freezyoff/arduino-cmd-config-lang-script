#include "src/example/WiFiStationConfig.h"

#define LOG(m) Serial.println(m)
#define LOGA(m) Serial.print(m)
#define LOGF(f,m) Serial.print(f,m)
#define LOGVAR(k,v) Serial.print((String) k);Serial.println(v)

WifiSTAConfig wstaConf;
const char* testStr = "#wsta ~gbr1=sadasjd sdkkasdlk ~gbr2=asdja asdjajiof ndadjhusjn ~gbr3=76726 8789921387 921 ~gbr4=nids9382mdlkvm j3u29dslkc lk3432u0kslalkd ~ssid=my ssid ~pwd=my secret pwd";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  LOG("");
  LOG("Test Shell with Garbage string: ");
  LOG(F("#wsta"));
  LOG(F("  ~gbr1=sadasjd sdkkasdlk"));
  LOG(F("  ~gbr2=asdja asdjajiof ndadjhusjn"));
  LOG(F("  ~gbr3=76726 8789921387 921"));
  LOG(F("  ~gbr4=nids9382mdlkvm j3u29dslkc lk3432u0kslalkd"));
  LOG(F("  ~ssid=my ssid"));
  LOG(F("  ~pwd=my secret pwd")); 
   
  LOG("");
  LOG("WifiSTAConfig keys:");
  for (int i=0; i<wstaConf.keyCount(); i++){
    LOGVAR(F("key ") + String(i) + F(": "), wstaConf.key(i));
  }

  LOG("");
  LOG("Initial config value:");
  for (int i=0; i<wstaConf.keyCount(); i++){
    const char* val = wstaConf.get(wstaConf.key(i));
    LOGVAR(F("Config key ") + String(wstaConf.key(i)) + F(": "), val? val : "NULL");
  }

  LOG("");
  LOG("Set config value with Shell:");
  int startm = millis();
  for (int i=0; i<wstaConf.keyCount(); i++){
    const char* val = Shell::argVal(wstaConf.key(i), testStr);
    wstaConf.set(wstaConf.key(i), val);
    LOGVAR(F("Shell key ") + String(wstaConf.key(i)) + F(": "), val? val : "NULL");
  }
  
  LOGA("Elapse Reading Shell & Set Config: ");
  LOGF(((float) millis()-startm)/1000, 5);
  LOG(" ms");

  LOG("");
  LOG("Final config value:");
  for (int i=0; i<wstaConf.keyCount(); i++){
    const char* val = wstaConf.get(wstaConf.key(i));
    LOGVAR(F("Config key ") + String(wstaConf.key(i)) + F(": "), val? val : "NULL");
  }

  int keys[] = {1000, 10000};
  const char* dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int keylen = random(1, strlen(dict));
  char key[keylen];
  for (int x=0; x<sizeof(keys)/sizeof(keys[0]); x++){
    LOG("");
    LOGVAR("Test search: ", String(keys[x]) + String(" total"));
    int startm = millis();
    
    LOGVAR("Shell String length: ", strlen(testStr));
    LOGVAR("Random Key length  : ", keylen);
    for (int i=0; i<keys[x]; i++){
      
      //build key
      for(int k=0; k<keylen; k++){
        int idx = random(1, strlen(dict));
        key[k] = dict[idx];
      }
  
      const char* val = Shell::argVal(key, testStr);
    }
    LOGA("Elapse Generate Keys & Reading Shell: ");
    LOGF(((float) millis()-startm)/1000, 5);
    LOG(" ms");
    yield();
  }
}

void loop() {

}
