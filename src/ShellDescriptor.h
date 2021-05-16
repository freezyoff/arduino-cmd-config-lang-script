#ifndef SHELL_DESCRIPTOR_H
#define SHELL_DESCRIPTOR_H

#include "ShellContext.h"
#include "Shell.h"

struct ShellDescriptor{
    virtual const char* shellCmd() = 0;
	virtual const char* shellArg(int keyIndex) = 0;
    virtual const char* shellArg(const char* configKey) = 0;
};

#endif