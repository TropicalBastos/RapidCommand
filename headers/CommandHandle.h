#ifndef CH_H
#define CH_H

#include<Windows.h>
#include<string>
#include<iostream>

#define ROOT "/"
#define CMD std::getenv("comspec")
#define KEEP_ALIVE "/k"


//Class definition header
class CommandHandle{
public:
  CommandHandle(const PROCESS_INFORMATION &pi) : process(pi){}
  static CommandHandle createCommandPrompt(std::string);
  PROCESS_INFORMATION getProcessStruct();
private:
  const PROCESS_INFORMATION &process;
};

#endif
