
#include "stdafx.h"
#include "GetUSBVersion.h"

#if (USE_USB_VERSION)


//*****************************************************************************
//
// GetDeviceDescription()
//
//*****************************************************************************

TCHAR* CGetUSBVersion::GetDeviceDescription(HDEVINFO hDevInfo, SP_DEVINFO_DATA* pDevInfo, DWORD propertyNumber)
{
	DWORD			dwRegType;
	TCHAR* pszName;

	DWORD dwSize = 0;
	BOOL bRet = ::SetupDiGetDeviceRegistryProperty(hDevInfo,pDevInfo,propertyNumber,&dwRegType,NULL,0,&dwSize);
	pszName = new TCHAR[dwSize];
	if(pszName == NULL)
		return NULL;

	bRet = ::SetupDiGetDeviceRegistryProperty(hDevInfo,pDevInfo,propertyNumber,&dwRegType,(BYTE*)pszName,dwSize,&dwSize);
	if(bRet == FALSE)
	{
		delete	pszName;
		return NULL;
	}
	return pszName;
}

//*****************************************************************************
//
// WideStrToMultiStr()
//
//*****************************************************************************

PCHAR CGetUSBVersion::WideStrToMultiStr ( PWCHAR WideStr, size_t cbWideStr)
{
    ULONG  nBytes = 0;
    PCHAR  MultiStr = NULL;
    PWCHAR pWideStr = NULL;

    // Use local string to guarantee zero termination
    pWideStr = (PWCHAR) malloc((DWORD) cbWideStr + 1);
    if (NULL == pWideStr)
    {
        return NULL;
    }
    memset(pWideStr, 0, cbWideStr + 1);
    memcpy(pWideStr, WideStr, cbWideStr);

    // Get the length of the converted string
    //
    nBytes = WideCharToMultiByte(
                 CP_ACP,
                 WC_NO_BEST_FIT_CHARS,
                 pWideStr,
                 -1,
                 NULL,
                 0,
                 NULL,
                 NULL);

    if (nBytes == 0)
    {
        free(pWideStr);
        return NULL;
    }

    // Allocate space to hold the converted string
    //
    MultiStr = (PCHAR)malloc(nBytes);
    if (MultiStr == NULL)
    {
        free(pWideStr);
        return NULL;
    }

    // Convert the string
    //
    nBytes = WideCharToMultiByte(
                 CP_ACP,
                 WC_NO_BEST_FIT_CHARS,
                 pWideStr,
                 -1,
                 MultiStr,
                 nBytes,
                 NULL,
                 NULL);

    if (nBytes == 0)
    {
        free(MultiStr);
        free(pWideStr);
        return NULL;
    }

    free(pWideStr);
    return MultiStr;
}

//*****************************************************************************
//
// GetDriverKeyName()
//
//*****************************************************************************

PCHAR CGetUSBVersion::GetDriverKeyName (HANDLE Hub, ULONG ConnectionIndex)
{
    BOOL                                success = 0;
    ULONG                               nBytes = 0;
    USB_NODE_CONNECTION_DRIVERKEY_NAME  driverKeyName;
    PUSB_NODE_CONNECTION_DRIVERKEY_NAME driverKeyNameW = NULL;
    PCHAR                               driverKeyNameA = NULL;

    // Get the length of the name of the driver key of the device attached to
    // the specified port.
    //
    driverKeyName.ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Allocate space to hold the driver key name
    //
    nBytes = driverKeyName.ActualLength;

    if (nBytes <= sizeof(driverKeyName))
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    driverKeyNameW = (PUSB_NODE_CONNECTION_DRIVERKEY_NAME)ALLOC(nBytes);
    if (driverKeyNameW == NULL)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Get the name of the driver key of the device attached to
    // the specified port.
    //
    driverKeyNameW->ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
                              driverKeyNameW,
                              nBytes,
                              driverKeyNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Convert the driver key name
    //
    driverKeyNameA = WideStrToMultiStr(driverKeyNameW->DriverKeyName, nBytes);

    // All done, free the uncoverted driver key name and return the
    // converted driver key name
    //
    FREE(driverKeyNameW);

    return driverKeyNameA;


GetDriverKeyNameError:
    // There was an error, free anything that was allocated
    //
    if (driverKeyNameW != NULL)
    {
        FREE(driverKeyNameW);
        driverKeyNameW = NULL;
    }

    return NULL;
}

//*********************************************
//
// GetExternalHubName()
//
//*****************************************************************************

PCHAR CGetUSBVersion::GetExternalHubName (HANDLE Hub, ULONG ConnectionIndex)
{
    BOOL                        success = 0;
    ULONG                       nBytes = 0;
    USB_NODE_CONNECTION_NAME    extHubName;
    PUSB_NODE_CONNECTION_NAME   extHubNameW = NULL;
    PCHAR                       extHubNameA = NULL;

    // Get the length of the name of the external hub attached to the
    // specified port.
    //
    extHubName.ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_NAME,
                              &extHubName,
                              sizeof(extHubName),
                              &extHubName,
                              sizeof(extHubName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Allocate space to hold the external hub name
    //
    nBytes = extHubName.ActualLength;

    if (nBytes <= sizeof(extHubName))
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    extHubNameW = (PUSB_NODE_CONNECTION_NAME)ALLOC(nBytes);

    if (extHubNameW == NULL)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Get the name of the external hub attached to the specified port
    //
    extHubNameW->ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_NAME,
                              extHubNameW,
                              nBytes,
                              extHubNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Convert the External Hub name
    //
    extHubNameA = WideStrToMultiStr(extHubNameW->NodeName, nBytes);

    // All done, free the uncoverted external hub name and return the
    // converted external hub name
    //
    FREE(extHubNameW);

    return extHubNameA;


GetExternalHubNameError:
    // There was an error, free anything that was allocated
    //
    if (extHubNameW != NULL)
    {
        FREE(extHubNameW);
        extHubNameW = NULL;
    }

    return NULL;
}

//*****************************************************************************
//
// GetRootHubName()
//
//*****************************************************************************

PCHAR CGetUSBVersion::GetRootHubName(HANDLE HostController)
{
    BOOL                success = 0;
    ULONG               nBytes = 0;
    USB_ROOT_HUB_NAME   rootHubName;
    PUSB_ROOT_HUB_NAME  rootHubNameW = NULL;
    PCHAR               rootHubNameA = NULL;

    // Get the length of the name of the Root Hub attached to the
    // Host Controller
    //
    success = DeviceIoControl(HostController,
                              IOCTL_USB_GET_ROOT_HUB_NAME,
                              0,
                              0,
                              &rootHubName,
                              sizeof(rootHubName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Allocate space to hold the Root Hub name
    //
    nBytes = rootHubName.ActualLength;

    rootHubNameW = (PUSB_ROOT_HUB_NAME)ALLOC(nBytes);
    if (rootHubNameW == NULL)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Get the name of the Root Hub attached to the Host Controller
    //
    success = DeviceIoControl(HostController,
                              IOCTL_USB_GET_ROOT_HUB_NAME,
                              NULL,
                              0,
                              rootHubNameW,
                              nBytes,
                              &nBytes,
                              NULL);
    if (!success)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Convert the Root Hub name
    //
    rootHubNameA = WideStrToMultiStr(rootHubNameW->RootHubName, nBytes);

    // All done, free the uncoverted Root Hub name and return the
    // converted Root Hub name
    //
    FREE(rootHubNameW);

    return rootHubNameA;

GetRootHubNameError:
    // There was an error, free anything that was allocated
    //
    if (rootHubNameW != NULL)
    {
        FREE(rootHubNameW);
        rootHubNameW = NULL;
    }
    return NULL;
}

//*****************************************************************************
//
// GetHCDDriverKeyName()
//
//*****************************************************************************

PCHAR CGetUSBVersion::GetHCDDriverKeyName(HANDLE HCD)
{
    BOOL                    success = 0;
    ULONG                   nBytes = 0;
    USB_HCD_DRIVERKEY_NAME  driverKeyName = {0};
    PUSB_HCD_DRIVERKEY_NAME driverKeyNameW = NULL;
    PCHAR                   driverKeyNameA = NULL;

    ZeroMemory(&driverKeyName, sizeof(driverKeyName));

    // Get the length of the name of the driver key of the HCD
    //
    success = DeviceIoControl(HCD,
                              IOCTL_GET_HCD_DRIVERKEY_NAME,
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        goto GetHCDDriverKeyNameError;
    }

    // Allocate space to hold the driver key name
    //
    nBytes = driverKeyName.ActualLength;
    if (nBytes <= sizeof(driverKeyName))
    {
        goto GetHCDDriverKeyNameError;
    }

    // Allocate size of name plus 1 for terminal zero
    driverKeyNameW = (PUSB_HCD_DRIVERKEY_NAME)malloc(nBytes + 1);
    if (driverKeyNameW == NULL)
    {
        goto GetHCDDriverKeyNameError;
    }

    // Get the name of the driver key of the device attached to
    // the specified port.
    //

    success = DeviceIoControl(HCD,
                              IOCTL_GET_HCD_DRIVERKEY_NAME,
                              driverKeyNameW,
                              nBytes,
                              driverKeyNameW,
                              nBytes,
                              &nBytes,
                              NULL);
    if (!success)
    {
        goto GetHCDDriverKeyNameError;
    }

    // Convert the driver key name
    //
    driverKeyNameA = WideStrToMultiStr(driverKeyNameW->DriverKeyName, nBytes);

    // All done, free the uncoverted driver key name and return the
    // converted driver key name
    //
    free(driverKeyNameW);

    return driverKeyNameA;

GetHCDDriverKeyNameError:
    // There was an error, free anything that was allocated
    //
    if (driverKeyNameW != NULL)
    {
        free(driverKeyNameW);
        driverKeyNameW = NULL;
    }

    return NULL;
}

int CGetUSBVersion::CheckUSBHub(const char* rootHubName){

    char deviceName[512];
	strcpy(deviceName, "\\\\.\\");
	strcat(deviceName, rootHubName);


	HANDLE hHubDevice = CreateFile(deviceName,
				GENERIC_WRITE,
				FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

	if(hHubDevice){
		USB_NODE_INFORMATION    hubInfo;
		ULONG		nBytes = 0;
		
		DeviceIoControl(hHubDevice,
                  IOCTL_USB_GET_NODE_INFORMATION,
                  &hubInfo,
                  sizeof(USB_NODE_INFORMATION),
                  &hubInfo,
                  sizeof(USB_NODE_INFORMATION),
                  &nBytes,
                  NULL);



		int portCnt = hubInfo.u.HubInformation.HubDescriptor.bNumberOfPorts;
		//printf("NumHub = %d\n", portCnt);

		int port;
		for(port=1; port<=portCnt; port++) // number is 1-based
		{
			// 以下、EnumerateHubPorts に相当

			ULONG	nBytesEx = sizeof(USB_NODE_CONNECTION_INFORMATION_EX) +
					 (sizeof(USB_PIPE_INFO) * 30);

			PUSB_NODE_CONNECTION_INFORMATION_EX pConnectionInfoEx = (PUSB_NODE_CONNECTION_INFORMATION_EX)ALLOC(nBytesEx);

			pConnectionInfoEx->ConnectionIndex = port;

			BOOL success = DeviceIoControl(hHubDevice,
					IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX,
					pConnectionInfoEx,
					nBytesEx,
					pConnectionInfoEx,
					nBytesEx,
					&nBytesEx,
					NULL);
			if(success){
				int vid = pConnectionInfoEx->DeviceDescriptor.idVendor;
				int pid = pConnectionInfoEx->DeviceDescriptor.idProduct;
				//printf("%d: VID = %04X, PID = %04X\n", 
				//	port, vid, pid);

				if(vid == m_vid && pid == m_pid)
				{
					m_detectedCnt ++;
					m_lastBcdUsb = pConnectionInfoEx->DeviceDescriptor.bcdUSB;

				}

				if(pConnectionInfoEx->DeviceIsHub){
					// ハブだった場合、再帰的に呼び出す
					PCHAR extHubName;

					extHubName = GetExternalHubName(hHubDevice, port);
					if (extHubName != NULL)
					{
						//printf("Is USB Hub: %s\n", extHubName);
						CheckUSBHub(extHubName);
						
						FREE(extHubName);
					}

				}

			}else{
				// 失敗した場合、IOCTL_USB_GET_NODE_CONNECTION_INFORMATION を使って情報取得するべき
				// 今回はしてない
				// USB3.0 だとうまくいくのかな？
				//printf("%d: VID = unknown\n", port);
			}
			FREE(pConnectionInfoEx);
		}


		CloseHandle(hHubDevice);
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int CGetUSBVersion::CheckUSBRoot(void)
{
	HDEVINFO hDevInfo;
	ULONG index = 0;
	DWORD error = 0;
	BOOL ret;
	TCHAR*			pszName;

	// Enumerate Host Controllers

	hDevInfo = ::SetupDiGetClassDevs((LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER,
		0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if(hDevInfo == INVALID_HANDLE_VALUE)
		return -1;
	while(1)
	{

		ULONG requiredLength = 0;
		SP_DEVINFO_DATA  deviceInfoData;
		SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
		SP_DEVICE_INTERFACE_DETAIL_DATA* pDeviceDetailData;

		memset(&deviceInfoData, 0, sizeof(deviceInfoData));

		deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

		ret = ::SetupDiEnumDeviceInfo(hDevInfo, index, &deviceInfoData);
		if(ret == FALSE) break;


		pszName = GetDeviceDescription(hDevInfo, &deviceInfoData, SPDRP_DEVICEDESC);
		if(pszName == NULL) continue;
		//printf("DeviceName: %s\n", pszName);
		delete	pszName;


		ret = SetupDiEnumDeviceInterfaces(hDevInfo, 0,
			(LPGUID)&GUID_CLASS_USB_HOST_CONTROLLER, index, &deviceInterfaceData);
		if(ret == FALSE) {
			index ++;
			continue;
		}

		// get size
		ret = SetupDiGetDeviceInterfaceDetail(hDevInfo, &deviceInterfaceData, 
			NULL, 0, &requiredLength, NULL);
		if(ret == FALSE && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
			break;
		}

		pDeviceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA*)malloc(requiredLength);
		pDeviceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		ret = SetupDiGetDeviceInterfaceDetail(hDevInfo, &deviceInterfaceData, 
			pDeviceDetailData, requiredLength, &requiredLength, NULL);
		if(ret == FALSE) break;

		// とりあえず print
		//printf("%d: %s\n", index, pDeviceDetailData->DevicePath);

		// CreateFile
		HANDLE hHostController = CreateFile(pDeviceDetailData->DevicePath,
			GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if(hHostController){
			// 以下、EnumerateHostController に相当
			
			// DriverKey の取得
			char* driverKeyName = GetHCDDriverKeyName(hHostController);
			char* rootHubName = GetRootHubName(hHostController);

			//printf("\t %d: %s / %s\n", index, driverKeyName, rootHubName);


			if(rootHubName && driverKeyName){
				// 以下、EnumerateHub に相当
				// driverKeyName は使わない

				CheckUSBHub(rootHubName);

				free(rootHubName);
				free(driverKeyName);
			}

			CloseHandle(hHostController);
		}

		free(pDeviceDetailData);
		index ++;
	}

	// Enumerate Hubs

	// Enumerate Downstream Ports

	return 0;
}

// Return -2: Error / -1: Not found
int CGetUSBVersion::GetUSBVersion(int pid, int vid)
{
	m_pid = pid;
	m_vid = vid;
	m_detectedCnt = 0;
	m_lastBcdUsb = 0;

	if(CheckUSBRoot()) return -2;
	if(m_detectedCnt == 0) return -1;
	
	return m_lastBcdUsb;
}

#endif