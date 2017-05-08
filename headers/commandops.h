#ifndef CH_H
#define CH_H

#include<Windows.h>
#include<string>
#include<iostream>

#define ROOT "C:\\"
#define CMD std::getenv("comspec")
#define KEEP_ALIVE "/k"
#define SHELL_SUCCESS 0x20

BOOL executeCommandPrompt(std::string);
std::string getPath();

#endif
