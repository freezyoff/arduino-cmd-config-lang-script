#ifndef CONFIG_H
#define CONFIG_H

#if defined(__PGMSPACE_H_) || defined(Arduino_h)
#pragma message "Config.h use Program Space Utilities (PGM)"
#endif

//replace with your own value
#define PGM_CONVERT_BUFFER_SIZE 10
	
struct Config{
	
	Config(size_t);
	
    //number of config keys
    virtual int         keyCount();
    virtual const char* key(int i) = 0;
    virtual int 		hasKey(const char* name) = 0;
    
    virtual void        set(const char* name, const char* val);
	virtual const char* get(const char* name);
	
#ifdef __PGMSPACE_H_
    
    static char* PGM_CONVERT_BUFFER[PGM_CONVERT_BUFFER_SIZE];
    const char* copy_P(PGM_P& key){
        memset(PGM_CONVERT_BUFFER, 0, PGM_CONVERT_BUFFER_SIZE);
        strcpy_P(PGM_CONVERT_BUFFER, key);
		Serial.println(PGM_CONVERT_BUFFER);
        return PGM_CONVERT_BUFFER;
    }
    
#endif
	
	protected:
		const int KEY_COUNT;
		char**    VALUES;
};

#endif