#include "../headers/commandops.h"
#include "../headers/fxhandler.h"

BOOL executeCommandPrompt(std::string path) {
	
	if (path.size() == 0) path = ROOT;

	TCHAR* directory = (TCHAR*)path.c_str();
	
	HINSTANCE hInstance = ShellExecute(
		NULL, "open", CMD,
		KEEP_ALIVE, directory,
		SW_SHOW
	);

	if (hInstance > (HINSTANCE) SHELL_SUCCESS) 
		return TRUE;

	return FALSE;

}

std::string getPath() {
	::CoInitialize(nullptr);
	wchar_t wch_path[32767];
	BOOL isOpen = TRUE;
	try
	{
		std::vector<FileExplorer::ExplorerFolderInfo> ex
			= FileExplorer::GetCurrentExplorerFolders();
		if (ex.size() == NULL) isOpen = FALSE;
		std::wcout << L"Currently open explorer windows:\n";
		for (const auto& info : ex)
		{
			if (!isOpen) break;
			if (::SHGetPathFromIDListEx(info.pidl.get(), wch_path, ARRAYSIZE(wch_path), 0))
				std::wcout << L"hwnd: 0x" << std::hex << info.hwnd << L", path: " << wch_path << L"\n";
		}
	}
	catch (std::system_error& e)
	{
		std::cout << "ERROR: " << e.what() << "\nError code: " << e.code() << "\n";
	}

	::CoUninitialize();

	if (isOpen) {
		std::wstring wpath(wch_path);
		std::string path(wpath.begin(), wpath.end());
		return path;
	}
	else {
		return "";
	}
}
