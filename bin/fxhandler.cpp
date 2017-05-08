#include "../headers/fxhandler.h"


BOOL FileExplorer::isActiveWindow(HWND explorer){
  HWND foreground = GetForegroundWindow();
  BOOL isActive = (explorer==foreground) ? TRUE: FALSE;
  return isActive;
}

// Get information about all currently open explorer windows.
// Throws std::system_error exception to report errors.
std::vector< FileExplorer::ExplorerFolderInfo > FileExplorer::GetCurrentExplorerFolders()
{
    CComPtr< IShellWindows > pshWindows;
    HRESULT hResult = pshWindows.CoCreateInstance( CLSID_ShellWindows );

    if(hResult!=S_OK) return std::vector<FileExplorer::ExplorerFolderInfo>();

    long count = 0;
    ThrowIfFailed(
        pshWindows->get_Count( &count ),
        "Could not get number of shell windows" );

    std::vector< ExplorerFolderInfo > result;
    result.reserve( count );

    for( long i = 0; i < count; ++i )
    {
        ExplorerFolderInfo info;

        CComVariant vi{ i };
        CComPtr< IDispatch > pDisp;
        ThrowIfFailed(
            pshWindows->Item( vi, &pDisp ),
            "Could not get item from IShellWindows" );

        if( ! pDisp )
            // Skip - this shell window was registered with a NULL IDispatch
            continue;

        CComQIPtr< IWebBrowserApp > pApp{ pDisp };
        if( ! pApp )
            // This window doesn't implement IWebBrowserApp
            continue;

        // Get the window handle.
        pApp->get_HWND( reinterpret_cast<SHANDLE_PTR*>( &info.hwnd ) );

        CComQIPtr< IServiceProvider > psp{ pApp };
        if( ! psp )
            // This window doesn't implement IServiceProvider
            continue;

        CComPtr< IShellBrowser > pBrowser;
        if( FAILED( psp->QueryService( SID_STopLevelBrowser, &pBrowser ) ) )
            // This window doesn't provide IShellBrowser
            continue;

        CComPtr< IShellView > pShellView;
        if( FAILED( pBrowser->QueryActiveShellView( &pShellView ) ) )
            // For some reason there is no active shell view
            continue;

        CComQIPtr< IFolderView > pFolderView{ pShellView };
        if( ! pFolderView )
            // The shell view doesn't implement IFolderView
            continue;

        // Get the interface from which we can finally query the PIDL of
        // the current folder.
        CComPtr< IPersistFolder2 > pFolder;
        if( FAILED( pFolderView->GetFolder( IID_IPersistFolder2, (void**) &pFolder ) ) )
            continue;

        LPITEMIDLIST pidl = nullptr;
        if( SUCCEEDED( pFolder->GetCurFolder( &pidl ) ) )
        {
            // Take ownership of the PIDL via std::unique_ptr.
            info.pidl = UniquePidlPtr{ pidl };
            if(FileExplorer::isActiveWindow(info.hwnd))
              result.push_back( std::move( info ) );

        }
    }

    return result;
}
