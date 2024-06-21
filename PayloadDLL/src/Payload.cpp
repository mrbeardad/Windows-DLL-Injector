#include "Payload.h"
#include "string"

void LogMessage(const char* message) {

	 //printf("%s\n", message);

	// exit with native api
	//pNtTerminateProcess pFuncNtTerminateProcess = (pNtTerminateProcess)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtTerminateProcess");
    STARTUPINFO si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    auto s = std::string("cmd.exe /k echo ") + message;
    CreateProcessA(NULL, (LPSTR)s.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,
                   NULL, &si, &pi);
    CloseHandle(pi.hProcess); 
    CloseHandle(pi.hThread); 

	//pFuncNtTerminateProcess((NTSTATUS)0);

}

extern "C" __declspec(dllexport) void HookProcedure() {

	printf("Injected via SetWindowsHookEx");
	//MessageBox(0, "Hello I'm DLL injected inside you !!!", "SetWindowsHookEx", MB_ICONINFORMATION);

}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
) {
	

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			//MessageBox(0, "Hello I'm DLL injected inside you !!!", "DLL_PROCESS_ATTACH", MB_ICONINFORMATION);
			LogMessage("Hello I'm DLL injected inside you in DLL_PROCESS_ATTACH mode!!!");
			//exit(1);
			break;

		case DLL_THREAD_ATTACH:
			//MessageBox(0, "Hello I'm DLL injected inside you GOOGLE CHROME !!!", "DLL_THREAD_ATTACH", MB_ICONINFORMATION);
			//LogMessage("Hello I'm DLL injected inside you in DLL_THREAD_ATTACH mode!!!");
			//exit(1);
			break;

		case DLL_THREAD_DETACH:
			//MessageBox(0, "Hello I'm DLL injected inside you GOOGLE CHROME !!!", "DLL_THREAD_DETACH", MB_ICONINFORMATION);
			//LogMessage("Hello I'm DLL injected inside you in DLL_THRED_DETACH mode!!!");
			//exit(1);
			break;

		case DLL_PROCESS_DETACH:
			//MessageBox(0, "Hello I'm DLL injected inside you !!!", "DLL_PROCESS_DETACH", MB_ICONINFORMATION);
			LogMessage("Hello I'm DLL injected inside you in DLL_PROCESS_DETACH mode!!!");
			//exit(1);
			break;
	}

	return TRUE;
}