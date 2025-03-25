#pragma once

#if (USE_USB_VERSION)

#undef _MP // avoid type/def conflict

#define ALLOC malloc
#define FREE free
#define OOPS() ;

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

// DDKのヘッダファイル
#include <devioctl.h>
#include <ntdddisk.h> 


// may be better to include "C:\Program Files (x86)\Windows Kits\8.1\Include\shared";"C:\Program Files (x86)\Windows Kits\8.1\Include\um"

#include <INITGUID.H>

#include <usbiodef.h>
#include <usbioctl.h>

#include <devguid.h>
#include <regstr.h>
#include <setupapi.h>
#pragma	comment(lib,"setupapi.lib")

class CGetUSBVersion
{
public:
	CGetUSBVersion(){
		m_detectedCnt = 0;
		m_lastDeviceName[0] = '\0';
	};
	virtual ~CGetUSBVersion(){
	};
	int GetUSBVersion(int pid, int vid);

private:
	int CheckUSBRoot(void);
	int CheckUSBHub(const char* rootHubName);

	const char* GetLastDeviceName(){
		return m_lastDeviceName;
	}

private:
	int m_pid, m_vid, m_detectedCnt, m_lastBcdUsb;
	char m_lastDeviceName[512];

private:
	static PCHAR GetHCDDriverKeyName(HANDLE HCD);
	static PCHAR GetRootHubName(HANDLE HostController);
	static PCHAR GetExternalHubName (HANDLE Hub, ULONG ConnectionIndex);
	static PCHAR GetDriverKeyName (HANDLE Hub, ULONG ConnectionIndex);
	static TCHAR* GetDeviceDescription(HDEVINFO hDevInfo, SP_DEVINFO_DATA* pDevInfo, DWORD propertyNumber);

	static PCHAR WideStrToMultiStr (PWCHAR WideStr, size_t cbWideStr);
};

#endif