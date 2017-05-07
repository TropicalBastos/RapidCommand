#include<Windows.h>
#include<iostream>
#include<vector>
#include "headers/keys.h"
#include "headers/CommandHandle.h"
#include "headers/FileExplorerHandler.h"

#define IS_DOWN 0x0001

std::string getPath(){
  ::CoInitialize( nullptr );
  wchar_t wch_path[ 32767 ];
  BOOL isOpen = TRUE;
    try
    {
        std::vector<FileExplorer::ExplorerFolderInfo> ex
        = FileExplorer::GetCurrentExplorerFolders();
        if(ex.size()==NULL) isOpen = FALSE;
        std::wcout << L"Currently open explorer windows:\n";
        for( const auto& info : ex )
        {
            if(!isOpen) break;
            if( ::SHGetPathFromIDListEx( info.pidl.get(), wch_path, ARRAYSIZE(wch_path), 0 ) )
                std::wcout << L"hwnd: 0x" << std::hex << info.hwnd << L", path: " << wch_path << L"\n";
        }
    }
    catch( std::system_error& e )
    {
        std::cout << "ERROR: " << e.what() << "\nError code: " << e.code() << "\n";
    }

    ::CoUninitialize();

    if(isOpen){
      std::wstring wpath(wch_path);
      std::string path(wpath.begin(),wpath.end());
      return path;
    }else{
      return "";
    }
}

int main(){


  int key = MAIN_KEY;
  std::vector<CommandHandle> CHANDLE_vec; //store each command process in array
  HWND windowHandler;
  SetConsoleTitle("CommandHotkey");
  windowHandler = FindWindowA(NULL,"CommandHotkey");
  ShowWindow(windowHandler,SW_HIDE);

  while(true){
    uint16_t keyStatus = GetAsyncKeyState(key);
    if(keyStatus & IS_DOWN){
      Sleep(1000);
      CommandHandle CHANDLE = CommandHandle::createCommandPrompt(getPath());
      CHANDLE_vec.push_back(CHANDLE);

      for(int i = 0;i < CHANDLE_vec.size(); i++){
        std::cout << &CHANDLE << std::endl;
      }
    }
  }

  return 0;
}
