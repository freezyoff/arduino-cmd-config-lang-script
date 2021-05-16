/**
 * Class ShellContextContext 
 * 
 * Describe Command Language prefix & symbol
 *
 **/

#ifndef SHELL_CONTEXT_H
#define SHELL_CONTEXT_H

#if defined(__PGMSPACE_H_) || defined(Arduino_h)
#pragma message "Shell.h use Program Space Utilities (PGM)"
#endif

//define Command prefix, 
//eg: #trigger
#define SHELL_CMD_PREFIX_CHAR "#"

//define Argument prefix 
//eg: ~option1
#define SHELL_ARG_PREFIX_CHAR "~"

//define Command & Argmument separator 
//eg: #trigger ~option1 ~option2
#define SHELL_CMD_ARG_SEPARATOR_CHAR " "

//define Argument key & value separator
//eg: ~option1=option_1_value
#define SHELL_ARG_KEY_VAL_SEPARATOR_CHAR "="

struct ShellContext{
    
#ifdef __PGMSPACE_H_
	static const char SHELL_CMD_PREFIX[] PROGMEM;
	static const char SHELL_ARG_PREFIX[] PROGMEM;
	static const char SHELL_CMD_ARG_SEPARATOR[] PROGMEM;
	static const char SHELL_ARG_KEY_VAL_SEPARATOR[] PROGMEM;
#else
    static const char* SHELL_CMD_PREFIX;
	static const char* SHELL_ARG_PREFIX;
	static const char* SHELL_CMD_ARG_SEPARATOR;
	static const char* SHELL_ARG_KEY_VAL_SEPARATOR;
#endif

	const char* cmdPrefix(char* buffer, size_t size);
	int         cmdPrefixLength();
	
	const char* argPrefix(char* buffer, size_t size);
	int         argPrefixLength();
	
	const char* cmdArgSeparator(char* buffer, size_t size);
	int         cmdArgSeparatorLength();
	
	const char* argKeyValSeparator(char* buffer, size_t size);
	int         argKeyValSeparatorLength();
	
	private:
    static void cleanBuffer(char* buffer, size_t size);
};

#endif