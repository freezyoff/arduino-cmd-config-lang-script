#include <iostream>
#include <cstddef>
#include <cstring>
#include "ShellContext.h"

#ifdef __PGMSPACE_H_

const char ShellContext::SHELL_CMD_PREFIX[] 		    PROGMEM = SHELL_CMD_PREFIX_CHAR;
const char ShellContext::SHELL_ARG_PREFIX[] 			PROGMEM = SHELL_ARG_PREFIX_CHAR;
const char ShellContext::SHELL_CMD_ARG_SEPARATOR[] 		PROGMEM = SHELL_CMD_ARG_SEPARATOR_CHAR;
const char ShellContext::SHELL_ARG_KEY_VAL_SEPARATOR[] 	PROGMEM = SHELL_ARG_KEY_VAL_SEPARATOR_CHAR;

#else

const char* ShellContext::SHELL_CMD_PREFIX  		    = SHELL_CMD_PREFIX_CHAR;
const char* ShellContext::SHELL_ARG_PREFIX   			= SHELL_ARG_PREFIX_CHAR;
const char* ShellContext::SHELL_CMD_ARG_SEPARATOR 		= SHELL_CMD_ARG_SEPARATOR_CHAR;
const char* ShellContext::SHELL_ARG_KEY_VAL_SEPARATOR 	= SHELL_ARG_KEY_VAL_SEPARATOR_CHAR;

#endif

const char* ShellContext::cmdPrefix(char* buffer, size_t size){
    cleanBuffer(buffer, size);
#ifdef __PGMSPACE_H_
	strcpy_P(buffer, SHELL_CMD_PREFIX);
#else
    strcpy(buffer, SHELL_CMD_PREFIX);
#endif
	return buffer;
}

int ShellContext::cmdPrefixLength(){
#ifdef __PGMSPACE_H_
	return strlen_P(SHELL_CMD_PREFIX);
#else
    return strlen(SHELL_CMD_PREFIX);
#endif
}

const char* ShellContext::argPrefix(char* buffer, size_t size){
    cleanBuffer(buffer, size);
#ifdef __PGMSPACE_H_
	strcpy_P(buffer, SHELL_ARG_PREFIX);
#else
    strcpy(buffer, SHELL_ARG_PREFIX);
#endif
	return buffer;
}

int ShellContext::argPrefixLength(){
#ifdef __PGMSPACE_H_
	return strlen_P(SHELL_ARG_PREFIX);
#else
    return strlen(SHELL_ARG_PREFIX);
#endif   
}

const char* ShellContext::cmdArgSeparator(char* buffer, size_t size){
#ifdef __PGMSPACE_H_
	strcpy_P(buffer, SHELL_CMD_ARG_SEPARATOR);
#else
    strcpy(buffer, SHELL_CMD_ARG_SEPARATOR);
#endif
	return buffer;
}

int ShellContext::cmdArgSeparatorLength(){
#ifdef __PGMSPACE_H_
	return strlen_P(SHELL_CMD_ARG_SEPARATOR);
#else
    return strlen(SHELL_CMD_ARG_SEPARATOR);
#endif
}

const char* ShellContext::argKeyValSeparator(char* buffer, size_t size){
#ifdef __PGMSPACE_H_
	strcpy_P(buffer, SHELL_ARG_KEY_VAL_SEPARATOR);
#else
    strcpy(buffer, SHELL_ARG_KEY_VAL_SEPARATOR);
#endif
	return buffer;
}

int ShellContext::argKeyValSeparatorLength(){
#ifdef __PGMSPACE_H_
	strlen_P(SHELL_ARG_KEY_VAL_SEPARATOR);
#else
    strlen(SHELL_ARG_KEY_VAL_SEPARATOR);
#endif
}

void ShellContext::cleanBuffer(char* buffer, size_t size){
	memset(buffer, 0 , size);
}