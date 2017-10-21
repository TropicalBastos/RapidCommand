#include<Windows.h>
#include<iostream>
#include<vector>
#include "../headers/keys.h"
#include "../headers/commandops.h"

#define IS_DOWN 0x0001


int main(){


  int key = MAIN_KEY;
  HWND windowHandler;
  SetConsoleTitle("CommandHotkey");
  windowHandler = FindWindowA(NULL,"CommandHotkey");
  //MSDN suggests calling showwindow twice to guarantee hiding the window
  ShowWindow(windowHandler,SW_HIDE);
  ShowWindow(windowHandler, SW_HIDE);

  //window details
  WINDOWPLACEMENT windowStatusStruct;
  memset(&windowStatusStruct, 0, sizeof(windowStatusStruct));

  while(true){
	//always sheck to see if window really is hidden
	GetWindowPlacement(windowHandler, &windowStatusStruct);
	uint32_t windowStatus = windowStatusStruct.showCmd;
	if (windowStatus != SW_HIDE) {
		ShowWindow(windowHandler, SW_HIDE);
    ShowWindow(windowHandler, SW_HIDE);
	}

    uint16_t keyStatus = GetAsyncKeyState(key);
    if(keyStatus & IS_DOWN){
      Sleep(1000);
	  BOOL cSuccess = executeCommandPrompt(getPath());
	  if (!cSuccess) {
		  MessageBox(
			  NULL,
			  "Unknown error command prompt failed to run",
			  "Error Message",
			  MB_OK
		  );
	  }
    }
  }

  return 0;
}
