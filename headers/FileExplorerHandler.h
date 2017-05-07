#ifndef FXHANDLER
#define FXHANDLER

#include<Windows.h>
#include<vector>
#include <shobjidl.h>
#include <shlobj.h>
#include <system_error>
#include <memory>
#include <shlwapi.h>
#include <strsafe.h>
#include <propvarutil.h>
#include<exdisp.h>
#include<atlbase.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "propsys.lib")


namespace FileExplorer{

// Throw a std::system_error if the HRESULT indicates failure.
template< typename T >
void ThrowIfFailed( HRESULT hr, T&& msg )
  {
      if( FAILED( hr ) )
          throw std::system_error{ hr, std::system_category(), std::forward<T>( msg ) };
  }


// Deleter for a PIDL allocated by the shell.
struct CoTaskMemDeleter
  {
      void operator()( ITEMIDLIST* pidl ) const { ::CoTaskMemFree( pidl ); }
    };
  // A smart pointer for PIDLs.
using UniquePidlPtr = std::unique_ptr< ITEMIDLIST, CoTaskMemDeleter >;



  // Return value of GetCurrentExplorerFolders()
struct ExplorerFolderInfo
{
    HWND hwnd = nullptr;  // window handle of explorer
    UniquePidlPtr pidl;   // PIDL that points to current folder
};

std::vector<ExplorerFolderInfo> GetCurrentExplorerFolders();

//check if the active window is file explorer
BOOL isActiveWindow(HWND hwnd);

}

#endif
