# Simple & Lightweight Command Language Script
Single Line String Script untuk tukar-menukar (*exchange*) data dari Hardware (e.g Arduino) ke Server dan sebaliknya.  
Menggunakan Buffer Tunggal (*Singgle Buffer*) dalam parsing Script untuk memperkecil RAM Heap.

Tersedia Support PGMSpace (PROGMEM) untuk Arduino.

## Unit Test
- CPP    : compile dan run [Main.cpp](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/Main.cpp)  
- Arduino: compile dan upload [CommandLanguage.cpp](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/CommandLanguage.ino)  

## Anatomi Script:
```
//Command format: <prefix><cmd signature>
const char* cmd = "#cmd-name";

//Argument format: <prefix><argument><separator><value>
const char* cmd = "#cmd-name ~arg-name-1=arg value 1 ~arg-name-2=arg value 2 ...";
```
  
## Parsing Script:
- Gunakan class [Shell](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/src/Shell.h) untuk parsing.  
- Penting untuk diingat, Class [Shell](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/src/Shell.h) didesain menggunakan Buffer Tunggal (*Single Buffer*) untuk menghemat RAM. Karena itu hasil parsing perlu dicopy.
```
//contoh kasus:
//Server mengirim data untuk ubah konfigurasi WiFi Station berikut:
const char* shellStr = "#wsta ~ssid=my ssid ~pwd=my secret pwd\n#restart";

//ada 2 command script,
//1: #wsta ~ssid=my ssid ~pwd=my secret pwd --> perintah ubah konfigurasi WiFi Station
//2: #restart                               --> perintah restart hardware

//perlu kita pecah per baris
//ambil baris pertama
const char* firstLine = split(shellStr, '\n');  //<<---- method *split()* hanya contoh

const char* ptr;

//ambil nilai ssid
ptr = Shell::argVal("ssid", singleLineStr);
char ssid_val[strlen(ptr)];
strcpy(ssid_val, ptr);      //<<------ copy nilai ssid

//ambil nilai pwd
ptr = Shell::argVal("pwd", shellStr);
char pwd_val[strlen(ptr)];
strcpy(pwd_val, ptr);      //<<------ copy nilai pwd

delete[] firstLine;
```

## Implementasi Class Config:
- Tersedia Class [Config.h](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/src/Config.h) untuk digunakan.
- Contoh implementasi class bisa dilihat pada [WiFiStationConfig.h](https://github.com/freezyoff/arduino-shell-cmd-config-script/blob/main/src/example/WiFiStationConfig.h)
```
//Definisikan class turunan
struct WifiSTAConfig : Config, ShellDescriptor{

  ...

}
```
- Dengan contoh kasus diatas:
```
//pada contoh kasus diatas:
//Server mengirim data untuk ubah konfigurasi WiFi Station berikut:
const char* shellStr = "#wsta ~ssid=my ssid ~pwd=my secret pwd\n#restart";

//perlu kita pecah per baris
//ambil baris pertama
const char* firstLine = split(shellStr, '\n');

WifiSTAConfig wstaConf;

//check apakah betul "#wsta" == wstaConf.shellCmd()
if (Shell::isCmd(wstaConf.shellCmd(), firstLine)){
  
  //set konfigurasi wstaConf
  const char* val;
  
  val = Shell::argVal(wstaConf.KEY_SSID, firstLine);
  wstaConf.set(wstaConf.KEY_SSID, val);
  
  val = Shell::argVal(wstaConf.KEY_PWD, firstLine);
  wstaConf.set(wstaConf.KEY_PWD, val);
  
}

... 

```
