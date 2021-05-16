/**
 * Single Buffer Command Language (Shell/Bash/DOS) Script.
 * 
 * Aim to be very LightWeight. Only use single buffer <code>SHELL_BUFFER</code>, should always copy the result!!!.
 * 
 * - Support white space in option without string quote
 * - Support option wihout value
 * 
 * Compatible
 * - Arduino,
 * - AVR PGM Space
 * 
 * Command
 * - format: <command prefix><command name>
 * - e.g   : #cmdName
 * 
 * Argument
 * - format: <arg prefix><arg name><arg name value separator><arg value>
 * - e.g   : ~arg1=the arg1 value.
 * 
 *
 **/
#ifndef SHELL_H
#define SHELL_H

#include "ShellContext.h"

//only this buffer use. 
//define the size that fit your need
#define SHELL_BUFFER_SIZE 50

struct Shell{
	
	static char SHELL_BUFFER[SHELL_BUFFER_SIZE];
	
	static const char* cmdPrefix();
	static int         cmdPrefixLength();
	
	static const char* argPrefix();
	static int         argPrefixLength();
	
	static const char* cmdArgSeparator();
	static int         cmdArgSeparatorLength();
	
	static const char* argKeyValSeparator();
	static int         argKeyValSeparatorLength();
	
	static bool isCmd(const char* cmd, const char* shellstr);
	
	static const char* argVal(const char* searchKey, const char* shellstr);
	
	//@param argSegment (const char*) 
	//@param segmenLength (const char*) 
	//@return arg key name
	static const char* argKey(const char*, size_t);
		
	//@param shellstr (const char*) shell string pointer
	//@return next argument pointer position
    static int nextArgPosition(const char* shellstr);
		
	static void shellContext(ShellContext*);
	
	protected:
		
		static ShellContext* shellContext();
		static ShellContext* _shell_context_;
		
};

#endif