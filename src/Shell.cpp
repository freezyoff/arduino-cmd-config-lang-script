#include <iostream>
#include <cstddef>
#include <cstring>
#include "Shell.h"

char Shell::SHELL_BUFFER[SHELL_BUFFER_SIZE];

ShellContext* Shell::_shell_context_;

ShellContext* Shell::shellContext(){
    return _shell_context_;
}

void Shell::shellContext(ShellContext* ptr){
    _shell_context_ = ptr;
}

const char* Shell::cmdPrefix(){
    return shellContext()->cmdPrefix(SHELL_BUFFER, SHELL_BUFFER_SIZE);
}

int  Shell::cmdPrefixLength(){
    return shellContext()->cmdPrefixLength();
}
	
const char* Shell::argPrefix(){
    return shellContext()->argPrefix(SHELL_BUFFER, SHELL_BUFFER_SIZE);
}

int  Shell::argPrefixLength(){
    return shellContext()->argPrefixLength();
}

const char* Shell::cmdArgSeparator(){
    return shellContext()->cmdArgSeparator(SHELL_BUFFER, SHELL_BUFFER_SIZE);
}

int  Shell::cmdArgSeparatorLength(){
    return shellContext()->cmdArgSeparatorLength();
}

const char* Shell::argKeyValSeparator(){
    return shellContext()->argKeyValSeparator(SHELL_BUFFER, SHELL_BUFFER_SIZE);
}

int  Shell::argKeyValSeparatorLength(){
    return shellContext()->argKeyValSeparatorLength();
}

bool Shell::isCmd(const char* cmd, const char* shellstr){
    const char* ptr = shellstr;
	if (strncmp(ptr, cmdPrefix(), cmdPrefixLength()) != 0) {
	    return false;
	}
    ptr += cmdPrefixLength();
	
	if (ptr && strncmp(ptr, cmd, strlen(cmd)) == 0){
		return true;
	}
	return false;
}

int Shell::nextArgPosition(const char* shellstr){
    //1. search argument forward
    const char* nptr = strchr(shellstr, argPrefix()[0]);
    if (!nptr){
        return strlen(shellstr);
    }
    
    //2. check if equal argPrefix()
    if (strncmp(nptr, argPrefix(), argPrefixLength()) == 0){
        int length = (nptr - shellstr);
        return length + argPrefixLength();
    }
    
    return strlen(shellstr);
}

const char* Shell::argKey(const char* segmentPtr, size_t segmentLen){
    //find key val separator ('=') or next argument segment ('~')
    int pos;
    for(int i=0; i<segmentLen; i++){
        bool match = false;
        if (segmentPtr[i] == argKeyValSeparator()[0]){
            match = strncmp(segmentPtr+i, argKeyValSeparator(), argKeyValSeparatorLength()) == 0;
        }
        else if (segmentPtr[i] == cmdArgSeparator()[0]){
            match = strncmp(segmentPtr+i, cmdArgSeparator()   , cmdArgSeparatorLength()   ) == 0;
        }
        
        if (match){
            pos = i;
            break;
        }
    }
    
    memset(SHELL_BUFFER, 0, SHELL_BUFFER_SIZE);
    strncat(SHELL_BUFFER, segmentPtr, pos);
    return SHELL_BUFFER;
}

const char* Shell::argVal(const char* searchKey, const char* shellstr){
	int maxpos = strlen(shellstr);
	int pos = nextArgPosition(shellstr);
	const char* strptr = shellstr + pos;
	
	while (pos < maxpos){
		
		int nextPos = nextArgPosition(strptr);
		 
		//calculate arg segment length and remove trailing whitespace
		int segLen = nextPos;
		segLen *= segLen<0 ? -1 : 1;
		if (strncmp(strptr + (segLen-argPrefixLength()), argPrefix(), argPrefixLength()) == 0){
		    segLen -= argPrefixLength();
		}
		if (strncmp(strptr + (segLen-cmdArgSeparatorLength()), cmdArgSeparator(), cmdArgSeparatorLength()) == 0){
		    segLen -= cmdArgSeparatorLength();
		}
		 
		//capture key
		const char* capturedKey = argKey(strptr, segLen);
		const int capturedKeyLen = strlen(capturedKey);
		
		//capture value
		if (strncmp(searchKey, capturedKey, capturedKeyLen)  == 0){
			//return argVal(strptr + capturedKeyLen + 1, segLen - capturedKeyLen - 1);
			
			memset(SHELL_BUFFER, 0, SHELL_BUFFER_SIZE);
			strncpy(SHELL_BUFFER, strptr + capturedKeyLen + 1, segLen - capturedKeyLen - 1);
			return SHELL_BUFFER;
		}
		
		//shift next argument 
		strptr += nextPos;
		pos += nextPos;
	}
	
	return "";
	
}