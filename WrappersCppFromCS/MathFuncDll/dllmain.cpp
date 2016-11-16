//https://drthitirat.wordpress.com/2013/05/30/combine-gui-of-c-with-c-codes/
//https://drthitirat.wordpress.com/2013/06/03/use-c-codes-in-a-c-project-wrapping-native-c-with-a-managed-clr-wrapper/

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

