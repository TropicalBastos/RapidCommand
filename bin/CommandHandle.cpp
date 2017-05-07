#include "../headers/CommandHandle.h"

CommandHandle CommandHandle::createCommandPrompt(std::string path){

  if(path.size()==0)
    path = ROOT;

  TCHAR* program = new TCHAR[sizeof(CMD)];
  program = TEXT(CMD);
  TCHAR* directory = (TCHAR*) path.c_str();
  TCHAR command[] = TEXT(KEEP_ALIVE);

  STARTUPINFO info;
  PROCESS_INFORMATION processInfo;
  ZeroMemory(&info,sizeof(STARTUPINFO));
  ZeroMemory(&processInfo,sizeof(PROCESS_INFORMATION));

  BOOL processResult =
  CreateProcess(program,
                command, NULL, NULL,
                TRUE, CREATE_NEW_CONSOLE,
                NULL, directory,
                &info,
                &processInfo);

  if(!processResult){
    std::cerr << "CreateProcess() failed to start program \""
    << program << "\"\n";
    exit(1);
  }

  std::cout << "Started program \""
  << program << "\" successfully\n";
  CommandHandle CHANDLE(processInfo);
  return CHANDLE;
}

PROCESS_INFORMATION CommandHandle::getProcessStruct(){
  return this->process;
}
