// SVIctlDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SVIctl.h"
#include "SVIctlDlg.h"
#include "DumpDialog.h"
//#include "SVMInfoDlg.h"
#if USE_USB_VERSION
#include "GetUSBVersion.h"
#endif
#include "SelBoardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 基板名
char g_boardName[64];
int SVM_03_REVISION;

/////////////////////////////////////////////////////////////////////////////
// CSVIctlDlg ダイアログ

CSVIctlDlg::CSVIctlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSVIctlDlg::IDD, pParent)
	, m_boardPower(TRUE)
{
	//{{AFX_DATA_INIT(CSVIctlDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pReadFileThread = NULL;

	AppName = "svmi2c";
}

void CSVIctlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSVIctlDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SVMSETTING, m_cButtonSetting);
	DDX_Control(pDX, ID_INIT, m_cButtonSFR);
	DDX_Control(pDX, ID_WRITE, m_cButtonWrite);
	DDX_Control(pDX, ID_READ, m_cButtonRead);
	DDX_Check(pDX, ID_BOARD_POWER, m_boardPower);
	DDX_Control(pDX, ID_RESTART_SVM, m_cButtonRestart);
}

BEGIN_MESSAGE_MAP(CSVIctlDlg, CDialog)
	//{{AFX_MSG_MAP(CSVIctlDlg)
	ON_BN_CLICKED(ID_WRITE, OnWrite)
	ON_BN_CLICKED(ID_READ, OnRead)
	ON_BN_CLICKED(ID_INIT, OnSettingFileWrite)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_WORD_ADDRESS, &CSVIctlDlg::OnBnClickedWordAddress)
	ON_BN_CLICKED(ID_BOARD_POWER, &CSVIctlDlg::OnBnClickedBoardPower)
	ON_BN_CLICKED(ID_Debug, &CSVIctlDlg::OnBnClickedDebug)
	ON_BN_CLICKED(ID_Debug2, &CSVIctlDlg::OnBnClickedDebug2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSVIctlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(ID_RESTART_SVM, &CSVIctlDlg::OnBnClickedRestartSvm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVIctlDlg メッセージ ハンドラ

int CSVIctlDlg::GetBoardNameFromCC(char* boardName, const UCHAR* customCode, const UCHAR* versionInfo, int i)
{
	int fwVersion = versionInfo[0];
	int fpgaVersion = versionInfo[1];
	int fpgaVersion2 = versionInfo[2];

	// Device ID
	int deviceID = 0;
	if(customCode[0] == 'K'){
		SVM_03_REVISION = 10; // temporary set
	}else{
		SVM_03_REVISION = 0;
	}
	if(customCode[0] == 'K')
	{ // Valid only SVM
		unsigned char receiveBuf[512];
		const int offs = 128;
		// SVMSetting情報の取得
		if(m_sviUsbControl.GetSVMSettingValue(sizeof(receiveBuf), receiveBuf )){
			deviceID = receiveBuf[offs+10] | (((int)receiveBuf[offs+11]) << 8);
		}else{
			//MessageBox("");
		}
	}

	if(customCode[0] == 'K'){
		if(customCode[1] == 'R'){
			sprintf(boardName, "%d: SVI-09 (LAN)", i);
		}else{
			sprintf(boardName, "%d: SVI-09 (UVC)", i);
		}
	}else if(customCode[0] == 'D'){ // SVP-01
		if(customCode[1] == 'u'){ // UVC
			sprintf(boardName, "%d: SVP-01 (UVC)", i);
		}else{ // DP
			sprintf(boardName, "%d: SVP-01 (DP_Source?)", i);
		}
	}else if(customCode[0] == 'w'){ // SVP-01-W
		if(customCode[1] == 'W'){ // UVC
			sprintf(boardName, "%d: SVP-01W (UVC)", i);
		}else{ // Other
			sprintf(boardName, "%d: SVP-01W (Unknown)", i);
		}
	}
	else if(customCode[0] == 'U'){
		if(customCode[1] == 'b'){ // [19/06/26]
			sprintf(boardName, "%d: SVM-06 Updater", i);
		}else{
			sprintf(boardName, "%d: SVM-06", i);
		}
	}
	else if(customCode[0] == 'S' || customCode[0] == 'R' || customCode[0] == 'T'){
		if(customCode[1] == 'U' || customCode[1] == 'u'){
			sprintf(boardName, "%d: SVM-03U-MIPI (UVC)", i);
		}
		else if(customCode[1] == 'b'){ // [19/06/26]
			sprintf(boardName, "%d: SVO Updater", i);
		}
		else if(customCode[1] == 'O' || customCode[1] == 'H' || customCode[1] == 'b'){
			sprintf(boardName, "%d: SVO-MIPI", i);
			// Device ID (DIP SW 6-4)
			{
				UCHAR buf[4];
				m_sviUsbControl.GetValue(0x08, 0x08000000, buf, 4, FALSE, FALSE);
				deviceID = (buf[3] >> 3) & 0x07;
			}
		}
		else {
			sprintf(boardName, "%d: SVM-03-MIPI (HDMI)", i);
		}
		/*
		// 32bit or 16bit?
		if(fpgaVersion >= 3){
			SVM_MIPI_32B = 1;
		}else{
			SVM_MIPI_32B = 0;
		}*/
	}
	else if(customCode[0] == 'X'){
		sprintf(boardName, "%d: SVM-03W-MIPI", i);
	}
	else if(customCode[1] == 'W'){
		sprintf(boardName, "%d: SVM-03W", i);
	}
	else if(customCode[1] == 'U' || customCode[1] == 'u'){
		sprintf(boardName, "%d: SVM-03U (UVC)", i);
	}
	else if(customCode[0] == 'O' && customCode[1] == 'V'){
		sprintf(boardName, "%d: SVO-03 (HDMI-UVC)", i);
	}
	else if(customCode[0] == 'O'){
		sprintf(boardName, "%d: SVO-03", i);
		// Device ID (DIP SW 6-4)
		{
			UCHAR buf[4];
			m_sviUsbControl.GetValue(0x08, 0x08000000, buf, 4, FALSE, FALSE);
			deviceID = (buf[3] >> 3) & 0x07;
		}
	}
	else if(customCode[1] == 'M'){
		sprintf(boardName, "%d: SVM-03 (HDMI)", i);
	}
	else if(fpgaVersion <= 1 && fpgaVersion2 == 0){
		sprintf(boardName, "%d: UB3-01 (?)", i);
		// debug message
		MessageBoxA("Warning: unknown board detected");
	}else if(fwVersion < 90 || fwVersion >= 200){ // SVM-03U
		sprintf(boardName, "%d: SVM-03U (?)", i);
	}else if(fwVersion < 100){ // SVI-05U
		sprintf(boardName, "%d: SVI-05U (?)", i);
	}else{ // SVM-03
		sprintf(boardName, "%d: SVM-03 (?)", i);
	}
	

	if(deviceID && deviceID < 100){
		char buf[128];
		sprintf(buf, " [ID=%d]", deviceID);
		strcat(boardName, buf);
	}
	return 0;
}
int CSVIctlDlg::UpdateBoardInfoFromCC(const UCHAR* customCode, const UCHAR* versionInfo)
{
	int fwVersion = versionInfo[0];
	int fpgaVersion = versionInfo[1];
	int fpgaVersion2 = versionInfo[2];

	if(customCode[0] == 'K'){
		if(customCode[1] == 'R'){ // LAN
			SVM_03_REVISION = 11;
			strcpy(g_boardName, "SVI-09(LAN)");
		}else if(customCode[1] == 'b'){ // [19/06/26]
			SVM_03_REVISION = 24;
			strcpy(g_boardName, "SVI Updater");
		}else{
			SVM_03_REVISION = 10;
			strcpy(g_boardName, "SVI-09");
		}
	}
	else if(customCode[0] == 'S' || customCode[0] == 'R' || customCode[0] == 'T'){
		if(customCode[1] == 'U' || customCode[1] == 'u'){
			SVM_03_REVISION = 1;
			strcpy(g_boardName, "SVM-03U-MIPI");
		}
		else if((customCode[1] == 'O')){ // [18/09/25]
			SVM_03_REVISION = 21;
			strcpy(g_boardName, "SVO-MIPI");
		}
		else if((customCode[1] == 'H')){ // [18/09/25]
			SVM_03_REVISION = 23;
			strcpy(g_boardName, "SVO-MIPI (HDMI)");
		}
		else if(customCode[1] == 'b'){ // [19/06/26]
			SVM_03_REVISION = 23;
			strcpy(g_boardName, "SVO Updater");
		}
		else {
			SVM_03_REVISION = 0;
			strcpy(g_boardName, "SVM-03-MIPI");
		}
	}
	else if(customCode[0] == 'D'){
		if(customCode[1] == 'U' || customCode[1] == 'u'){
			SVM_03_REVISION = 31;
			strcpy(g_boardName, "SVP-01 (UVC)");
		}else{
			SVM_03_REVISION = 32;
			strcpy(g_boardName, "SVP-01 (DP)");
		}
	}
	else if(customCode[0] == 'w'){
		SVM_03_REVISION = 39;
		strcpy(g_boardName, "SVP-01W (UVC)");
	}
	else if(customCode[0] == 'U'){
		if(customCode[1] == 'b'){ // [19/06/26]
			SVM_03_REVISION = 24;
			strcpy(g_boardName, "SVM-06 Updater");
		}else{
			SVM_03_REVISION = 15;
			strcpy(g_boardName, "SVM-06");
		}
	}
	else if(customCode[0] == 'X'){
		SVM_03_REVISION = 1; // FX3 ROM in later area
		strcpy(g_boardName, "SVM-03W-MIPI");
	}
	else if(customCode[1] == 'W'){
		SVM_03_REVISION = 4; // FX3 ROM in former area
		strcpy(g_boardName, "SVM-03W");
	}
	else if(customCode[1] == 'U' || customCode[1] == 'u'){
		SVM_03_REVISION = 1;
		strcpy(g_boardName, "SVM-03U");
	}
	else if(customCode[0] == 'O' && customCode[1] == 'V'){
		SVM_03_REVISION = 1;
		strcpy(g_boardName, "SVO-03 (HDMI-UVC)");
	}
	else if(customCode[0] == 'O'){
		SVM_03_REVISION = 20;
		//SVM_03_REVISION = 0;
		strcpy(g_boardName, "SVO-03");
	}
	else if(customCode[1] == 'M'){
		SVM_03_REVISION = 0;
		strcpy(g_boardName, "SVM-03");
	}
	else if(fpgaVersion <= 1 && fpgaVersion2 == 0){
		SVM_03_REVISION = 3;
		{
			CWnd* pWindow;
			pWindow = GetDlgItem(IDC_SVMINFO);
			if(pWindow) pWindow->EnableWindow(FALSE);
			pWindow = GetDlgItem(ID_BOARD_POWER);
			if(pWindow) pWindow->EnableWindow(FALSE);
			strcpy(g_boardName, "UB3-01");
		}
	}else if(fwVersion < 90 || fwVersion >= 200){ // SVM-03U
		SVM_03_REVISION = 1;
		strcpy(g_boardName, "SVM-03U");
	//	m_cButtonSetting.SetWindowTextA("SVM-03U Setting");
	}else if(fwVersion < 100){ // SVI-05U
		SVM_03_REVISION = 2;
		strcpy(g_boardName, "SVI-05U");
	}else{ // SVM-03
		SVM_03_REVISION = 0;
		strcpy(g_boardName, "SVM-03");
	//	m_cButtonSetting.SetWindowTextA("SVM-03 Setting");
	}
	return 0;
}

INT_PTR CSVIctlDlg::DoModal()
{

//	MessageBox(NULL , "2024: SVMCtl_I2C.dll api call test." , MB_OK);
	return CDialog::DoModal();
}

BOOL CSVIctlDlg::OpenCaptureBoard()
{
	//iniファイル内容を適用する
	IniFileName = "\\" + AppName + ".ini";
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Path);
	IniFileName = Path + IniFileName;
	CIniFileControl iniFile(AppName, IniFileName);

	//	ID_SLAVE_ADDRESS
	CString slaveAddress = iniFile.GetString(INI_KEY_SLAVE_ADDRESS, DEFAULT_SLAVE_ADDRESS);
	if (slaveAddress == "") slaveAddress = "1a";

	// ID_SUB_ADDRESS
	CString subAddress = iniFile.GetString(INI_KEY_SUB_ADDRESS, DEFAULT_SUB_ADDRESS);

	// ID_VALUE
	CString value = iniFile.GetString(INI_KEY_VALUE, DEFAULT_VALUE);

	// ID_READ_COUNTS
	CString readCounts = iniFile.GetString(INI_KEY_READ_COUNTS, DEFAULT_READ_COUNTS);

	// ID_WORD_ADDRESS
	int wordAddress = iniFile.GetInt(INI_KEY_WORD_ADDRESS, DEFAULT_WORD_ADDRESS);

	// [15/05/25] Get FW Version
	{
		//strcpy(g_boardName, "(Unknown Device)");
		//if (IsBoardSelected() == false) {
		//	windowTitleText += " -[No Device]";
		//	this->SetWindowTextA(windowTitleText);
		//	m_cButtonSetting.EnableWindow(FALSE); //
		//}
		UCHAR buf[10];
		UCHAR versionInfo[4];

#define VIDEO_ID_MAX 8
		// 複数台の SVM を検出
		if (1) {
			int maxIndex = 1;
			int curIndex = 0;
			int i;
			int boardType = 0, boardIdx = 0;
			int boardIdxList[VIDEO_ID_MAX] = { 0 };
			char boardName[VIDEO_ID_MAX][128];
			//int boardCnt = m_sviUsbControl.ScanBoard();
			for (i = 0; i < VIDEO_ID_MAX; i++) {
				m_sviUsbControl.SetDeviceIndex(boardIdx);
				if (m_sviUsbControl.open() == false) {
					// [18/07/31]
					if (boardType == 0) {
						// Switch SVM -> SVO
						boardType = 1;
						boardIdx = 0;
						m_sviUsbControl.SetBoardType(boardType);
						m_sviUsbControl.SetDeviceIndex(boardIdx);
						if (m_sviUsbControl.open() == false) {
							break;
						}
					}
					else {
						break;
					}
				}
				m_sviUsbControl.close();
				boardIdxList[i] = (boardType << 8) | boardIdx;
				boardIdx++;

				if (m_sviUsbControl.SVMVersionInfo(sizeof(versionInfo), versionInfo) == true) {

					// Custom Code
					UCHAR customCode[4] = { 0,0,0,0 }; // first -> fourth
					{
						UCHAR buf[4];
						if (!(versionInfo[1] <= 1 && versionInfo[2] == 0))// not v1.00
						{
							m_sviUsbControl.GetValue(0x08, 0x080000D0, buf, 4, FALSE, FALSE);
							customCode[0] = buf[3];
							m_sviUsbControl.GetValue(0x08, 0x080000D4, buf, 4, FALSE, FALSE);
							customCode[1] = buf[3];
						}
					}
					GetBoardNameFromCC(boardName[i], customCode, versionInfo, i);

				}
				else {
					sprintf(boardName[i], "%d: Unknown board", i);
				}
				maxIndex = i + 1;

			}

			// 選択
			//if (maxIndex > 1) {
			//	CSelBoardDlg dlg;
			//	for (i = 0; i < maxIndex; i++) {
			//		dlg.AppendBoardName(boardName[i]);
			//	}
			//	if (dlg.DoModal() == IDOK) {
			//		curIndex = dlg.m_curBoardIdx;
			//	}
			//}

			// [18/07/31] Modified
			if (curIndex > VIDEO_ID_MAX) curIndex = 0;
			m_sviUsbControl.SetBoardType(boardIdxList[curIndex] >> 8);
			m_sviUsbControl.SetDeviceIndex(boardIdxList[curIndex] & 0xFF);
		}

		Sleep(100);

		if (m_sviUsbControl.SVMVersionInfo(sizeof(versionInfo), versionInfo) == true)
		{
			char titleText[512];
			int fwVersion = versionInfo[0];
			int fpgaVersion = versionInfo[1];
			int fpgaVersion2 = versionInfo[2];

			// Custom Code
			UCHAR customCode[4] = { 0,0,0,0 }; // first -> fourth
			{
				UCHAR buf[4];
				if (!(fpgaVersion <= 1 && fpgaVersion2 == 0)) { // not v1.00
					m_sviUsbControl.GetValue(0x08, 0x080000D0, buf, 4, FALSE, FALSE);
					customCode[0] = buf[3];
					m_sviUsbControl.GetValue(0x08, 0x080000D4, buf, 4, FALSE, FALSE);
					customCode[1] = buf[3];
				}
			}
			UpdateBoardInfoFromCC(customCode, versionInfo);

			//sprintf(titleText, "%s [%s]", windowTitleText, g_boardName);

			// USB version
#if (USE_USB_VERSION)
			CGetUSBVersion usbVersion;
			// VID/PID [18/03/01] Currently not supported for VID 0x2FA3
			int bcdUsb = usbVersion.GetUSBVersion(SVM_PID, SVM_VID);
			if (bcdUsb > 100) {
				char buf2[64];
				sprintf(buf2, "(USB%d.%d)", bcdUsb >> 8, bcdUsb & 0xFF);
				strcat(titleText, buf2);
			}
			else {
				strcat(titleText, "(USB?.?)");
				// Error
				MessageBoxA("Warning: Software can't get USB Version.");
			}
#endif
			//this->SetWindowTextA(titleText);

			if (IS_SVO09() || IS_SVO_MIPI())
			{
				//m_cButtonSetting.EnableWindow(FALSE); //

				//CWnd* pWindow;
				//pWindow = GetDlgItem(ID_BOARD_POWER);
				//if (pWindow) pWindow->EnableWindow(FALSE);
			}
		}
		else {
			//char titleText[512];
			//sprintf(titleText, "%s +[No Device]", windowTitleText);
			//this->SetWindowTextA(titleText);
			//m_cButtonSetting.EnableWindow(FALSE); //

			//m_cButtonSFR.EnableWindow(FALSE);
			//m_cButtonRead.EnableWindow(FALSE);
			//m_cButtonWrite.EnableWindow(FALSE);
			//m_cButtonRestart.EnableWindow(FALSE);

			//{
			//	CWnd* pWindow;
			//	pWindow = GetDlgItem(IDC_SVMINFO);
			//	if (pWindow) pWindow->EnableWindow(FALSE);

			//	pWindow = GetDlgItem(ID_BOARD_POWER);
			//	if (pWindow) pWindow->EnableWindow(FALSE);
			//}
			return FALSE;
		}

	}

	/// S.H Test
	//m_cButtonSFR.EnableWindow(TRUE);


	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

BOOL CSVIctlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	//iniファイル内容を適用する
//	AppName = AfxGetAppName();
	IniFileName = "\\" + AppName + ".ini";
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,Path);
	IniFileName =  Path + IniFileName;
	CIniFileControl iniFile(AppName, IniFileName);

	CString windowTitleText = "SVMCtl";

	//	ID_SLAVE_ADDRESS
	CString slaveAddress = iniFile.GetString(INI_KEY_SLAVE_ADDRESS,DEFAULT_SLAVE_ADDRESS);
	this->SetDlgItemText(ID_SLAVE_ADDRESS,slaveAddress);

	// ID_SUB_ADDRESS
	CString subAddress = iniFile.GetString(INI_KEY_SUB_ADDRESS,DEFAULT_SUB_ADDRESS);
	this->SetDlgItemText(ID_SUB_ADDRESS,subAddress);

	// ID_VALUE
	CString value = iniFile.GetString(INI_KEY_VALUE,DEFAULT_VALUE);
	this->SetDlgItemText(ID_VALUE,value);

	// ID_READ_COUNTS
	CString readCounts = iniFile.GetString(INI_KEY_READ_COUNTS,DEFAULT_READ_COUNTS);
	this->SetDlgItemText(ID_READ_COUNTS,readCounts);

	// ID_WORD_ADDRESS
	int wordAddress = iniFile.GetInt(INI_KEY_WORD_ADDRESS,DEFAULT_WORD_ADDRESS);
	((CButton*)this->GetDlgItem(ID_WORD_ADDRESS))->SetCheck(wordAddress);

	// [15/05/25] Get FW Version
	{
		strcpy(g_boardName, "(Unknown Device)");
		if(IsBoardSelected() == false) {
			windowTitleText += " -[No Device]";
			this->SetWindowTextA(windowTitleText);
			m_cButtonSetting.EnableWindow(FALSE); //
		}
		UCHAR buf[10];
		UCHAR versionInfo[4];

#define VIDEO_ID_MAX 8
		// 複数台の SVM を検出
		if(1){
			int maxIndex = 1;
			int curIndex = 0;
			int i;
			int boardType = 0, boardIdx = 0;
			int boardIdxList[VIDEO_ID_MAX] = {0};
			char boardName[VIDEO_ID_MAX][128];
			//int boardCnt = m_sviUsbControl.ScanBoard();
			for(i=0; i<VIDEO_ID_MAX; i++){
				m_sviUsbControl.SetDeviceIndex(boardIdx);
				if(m_sviUsbControl.open() == false){
					// [18/07/31]
					if(boardType == 0){
						// Switch SVM -> SVO
						boardType = 1;
						boardIdx = 0;
						m_sviUsbControl.SetBoardType(boardType);
						m_sviUsbControl.SetDeviceIndex(boardIdx);
						if(m_sviUsbControl.open() == false){
							break;
						}
					}else{
						break;
					}
				}
				m_sviUsbControl.close();
				boardIdxList[i] = (boardType << 8) | boardIdx;
				boardIdx ++;

				if(m_sviUsbControl.SVMVersionInfo(sizeof(versionInfo), versionInfo) == true){

					// Custom Code
					UCHAR customCode[4] = {0,0,0,0}; // first -> fourth
					{
						UCHAR buf[4];
						if(!(versionInfo[1] <= 1 && versionInfo[2] == 0))// not v1.00
						{
							m_sviUsbControl.GetValue(0x08, 0x080000D0, buf, 4, FALSE, FALSE);
							customCode[0] = buf[3];
							m_sviUsbControl.GetValue(0x08, 0x080000D4, buf, 4, FALSE, FALSE);
							customCode[1] = buf[3];
						}
					}
					GetBoardNameFromCC(boardName[i], customCode, versionInfo, i);

				}else{
					sprintf(boardName[i], "%d: Unknown board", i);
				}
				maxIndex = i+1;

			}

			// 選択
			if(maxIndex > 1){
				CSelBoardDlg dlg;
				for(i=0; i<maxIndex; i++){
					dlg.AppendBoardName(boardName[i]);
				}
				if(dlg.DoModal() == IDOK){
					curIndex = dlg.m_curBoardIdx;
				}
			}
			
			// [18/07/31] Modified
			if(curIndex > VIDEO_ID_MAX) curIndex = 0;
			m_sviUsbControl.SetBoardType(boardIdxList[curIndex] >> 8);
			m_sviUsbControl.SetDeviceIndex(boardIdxList[curIndex] & 0xFF);
		}

		Sleep(100);

		if(m_sviUsbControl.SVMVersionInfo(sizeof(versionInfo), versionInfo) == true)
		{
			char titleText[512];
			int fwVersion = versionInfo[0];
			int fpgaVersion = versionInfo[1];
			int fpgaVersion2 = versionInfo[2];

			// Custom Code
			UCHAR customCode[4] = {0,0,0,0}; // first -> fourth
			{
				UCHAR buf[4];
				if(!(fpgaVersion <= 1 && fpgaVersion2 == 0)){ // not v1.00
					m_sviUsbControl.GetValue(0x08, 0x080000D0, buf, 4, FALSE, FALSE);
					customCode[0] = buf[3];
					m_sviUsbControl.GetValue(0x08, 0x080000D4, buf, 4, FALSE, FALSE);
					customCode[1] = buf[3];
				}
			}
			UpdateBoardInfoFromCC(customCode, versionInfo);

			sprintf(titleText, "%s [%s]", windowTitleText, g_boardName);

			// USB version
#if (USE_USB_VERSION)
			CGetUSBVersion usbVersion;
			// VID/PID [18/03/01] Currently not supported for VID 0x2FA3
			int bcdUsb = usbVersion.GetUSBVersion(SVM_PID, SVM_VID);
			if(bcdUsb > 100){
				char buf2[64];
				sprintf(buf2, "(USB%d.%d)", bcdUsb>>8, bcdUsb&0xFF);
				strcat(titleText, buf2);
			}else{
				strcat(titleText, "(USB?.?)");
				// Error
				MessageBoxA("Warning: Software can't get USB Version.");
			}
#endif
			this->SetWindowTextA(titleText);

			if(IS_SVO09() || IS_SVO_MIPI() ) 
			{
				m_cButtonSetting.EnableWindow(FALSE); //

				CWnd* pWindow;
				pWindow = GetDlgItem(ID_BOARD_POWER);
				if(pWindow) pWindow->EnableWindow(FALSE);
			}
		}else{
			char titleText[512];
			sprintf(titleText, "%s +[No Device]", windowTitleText);
			this->SetWindowTextA(titleText);
			m_cButtonSetting.EnableWindow(FALSE); //

			m_cButtonSFR.EnableWindow(FALSE);
			m_cButtonRead.EnableWindow(FALSE);
			m_cButtonWrite.EnableWindow(FALSE);
			m_cButtonRestart.EnableWindow(FALSE);

			{
				CWnd* pWindow;
				pWindow = GetDlgItem(IDC_SVMINFO);
				if(pWindow) pWindow->EnableWindow(FALSE);

				pWindow = GetDlgItem(ID_BOARD_POWER);
				if(pWindow) pWindow->EnableWindow(FALSE);
			}
		}

	}

	/// S.H Test
	m_cButtonSFR.EnableWindow(TRUE);


	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// CSV形式文字列のパース
int CSVIctlDlg::ParseCsv(CString strData, UCHAR* workBuf, ULONG bufSize/*vector<UCHAR> &work*/)
{
	if(strData.GetLength()==0) return 0;

	PTCHAR pStopstring;
	CString strWork;
	int pos = 0;
	int count = 0;
	PTCHAR string = strData.GetBuffer(strData.GetLength());
	PTCHAR spesLine = "\r\n";		//行単位の分解
	PTCHAR spes = " ,\t\r\n";	//行内の分解
	PTCHAR tokenLine,token;
	strWork = "";
	// 行単位に分解
	tokenLine = _tcstok(string,spesLine);
	while(tokenLine != NULL)
	{
		TRACE("tokenLine = %s\n",tokenLine);
		if(tokenLine[0] =='#')
		{
			tokenLine = _tcstok(NULL,spes);
			continue;
		}
		strWork += tokenLine;
		strWork += ",";
		tokenLine = _tcstok(NULL,spesLine);
	}

	tokenLine = strWork.GetBuffer(strWork.GetLength());
	// 行内の分解
	token = _tcstok(tokenLine,spes);
	while(token != NULL)
	{
		// ファイル終端の制御文字対応
		if(_tcslen(token) > 2 )
		{
			for(int i = 0 ; i < _tcslen(token);i++){
				if(!_istalnum(token[i]))
				{
					token[i] = '\0';
					break;
				}
			}
			if(_tcslen(token) < 2 )
				break;
		}
		int d = _tcstoul(token, &pStopstring, 16);

		if( count >= bufSize-1 )
			return 0;
	//	if(work.size() <= count)
	//		work.resize(count);
		workBuf[count] = d;
		count++;
		token = _tcstok(NULL, spes);
	}

	return count;
}

/*
 *  レジスタ値の書込み
 */
int CSVIctlDlg::WriteReg(ULONG devAddr, ULONG regAddr, UCHAR regVal)
{
	UCHAR rcvBuf[1024];
	CString strText;
	char* temp;

	// 選択されているSVI-03ボードを設定します
	if (IsBoardSelected() == false)
	{
		return -5;
	}


	if (devAddr == 0x08) {
		ULONG ulVal;
		sscanf_s(strText, "%x", &ulVal);
		BYTE bVal[16];
		bVal[0] = (BYTE)((ulVal >> 24) & 0xff);
		bVal[1] = (BYTE)((ulVal >> 16) & 0xff);
		bVal[2] = (BYTE)((ulVal >> 8) & 0xff);
		bVal[3] = (BYTE)((ulVal >> 0) & 0xff);
		// カメラレジスタの設定
		if (!m_sviUsbControl.SetValue(devAddr, regAddr, bVal, 4, false))
		{
			return -1;
		}
	}
	else {
		if (!m_sviUsbControl.SetValue(devAddr, regAddr, &regVal, 1, true))
		{
			return -1;
		}
	}

	return 0;
}

void CSVIctlDlg::OnWrite()
{
	CButton *pCheck = (CButton *)GetDlgItem(ID_WORD_ADDRESS);
	UCHAR rcvBuf[1024];
	ULONG deviceAddr, regAddr;
	CString strText;
	char* temp;

	// 選択されているSVI-03ボードを設定します
	if(IsBoardSelected() == false) return;

	// 設定値の取得
	// Slave Addressの取得
	GetDlgItemText(ID_SLAVE_ADDRESS, strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSLAVE);
		return;
	}
	if(!CSVIctlDlg::Checkalnum((LPCTSTR)strText))
	{
		AfxMessageBox(ID_MSG_ERR_DATASLAVE);
		return;
	}

	deviceAddr = _tcstoul(strText, &temp, 16);

	// SubAddressの取得
	GetDlgItemText(ID_SUB_ADDRESS,strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSUB);
		return;
	}
	if(!Checkalnum((LPCTSTR)strText))
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSUB);
		return;
	}
	regAddr = _tcstoul(strText, &temp, 16);

	// Valueの取得
	GetDlgItemText(ID_VALUE,strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTVALUE);
		return;
	}
	if(!Checkalnum((LPCTSTR)strText,true))
	{
		AfxMessageBox(ID_MSG_ERR_DATAVALUE);
		return;
	}

	if(deviceAddr == 0x08){
		ULONG ulVal;
		sscanf_s(strText, "%x", &ulVal);
		BYTE bVal[16];
		bVal[0] = (BYTE)((ulVal >> 24)&0xff);
		bVal[1] = (BYTE)((ulVal >> 16)&0xff);
		bVal[2] = (BYTE)((ulVal >>  8)&0xff);
		bVal[3] = (BYTE)((ulVal >>  0)&0xff);
		// カメラレジスタの設定
		if(!m_sviUsbControl.SetValue(deviceAddr, regAddr, bVal, 4, false))
		{
			AfxMessageBox(ID_MSG_ERR_WRITE);
			return;
		}
	}else{
		// カンマをパースし、rcvBufに設定
		int dataSize = ParseCsv(strText, rcvBuf, sizeof(rcvBuf));
		if(dataSize == 0) return;

		// カメラレジスタの設定
		if(!m_sviUsbControl.SetValue(deviceAddr, regAddr, rcvBuf, dataSize, pCheck->GetCheck()))
		{
			AfxMessageBox(ID_MSG_ERR_WRITE);
			return;
		}
	}

}

void CSVIctlDlg::OnRead()
{
	CButton *pCheck = (CButton *)GetDlgItem(ID_WORD_ADDRESS);
	UCHAR rcvBuf[2048];
	ULONG deviceAddr, regAddr;
	ULONG cnt;

	CString strText;
	CString strRcv, strWork;
	char* temp;
	int i;

	// 選択されているSVI-03ボードを設定します
	if(IsBoardSelected() == false) return;

	// Slave Addressの取得
	GetDlgItemText(ID_SLAVE_ADDRESS,strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSLAVE);
		return;
	}
	if(!Checkalnum((LPCTSTR)strText))
	{
		AfxMessageBox(ID_MSG_ERR_DATASLAVE);
		return;
	}
	deviceAddr = _tcstoul(strText, &temp, 16);

	// SubAddressの取得
	GetDlgItemText(ID_SUB_ADDRESS,strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSUB);
		return;
	}
	if(!Checkalnum((LPCTSTR)strText))
	{
		AfxMessageBox(ID_MSG_ERR_DATASUB);
		return;
	}
	regAddr = _tcstoul(strText,&temp,16);

	BOOL Trans;
	cnt = GetDlgItemInt(ID_READ_COUNTS, &Trans, TRUE);
	if(!Trans)
	{
		AfxMessageBox(ID_MSG_ERR_DATAREADCOUNTS);
		return;
	}
	if(cnt <= 0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTREADCOUNTS);
		return;
	}

	if(cnt >= sizeof(rcvBuf)) {
		MessageBoxA("Size Over.", "Error", MB_ICONERROR);
		return;
	}

	// カメラレジスタの取得
	if(!m_sviUsbControl.GetValue(deviceAddr, regAddr, rcvBuf, cnt, pCheck->GetCheck(), TRUE)) // I2C Read
	{
		AfxMessageBox(ID_MSG_ERR_READ);
		return;
	}

	// 取得値をカンマ区切り形式へ編集
	if(cnt == 0){
		strRcv = "(No Data)";
	}else{
		for(i=0;i<cnt;i++)
		{
			strWork.Format("%02X", rcvBuf[i]);
			if(i==0)
				strWork = strWork;
			else if((i%16)==0) 
				strWork = ",\r\n" + strWork;
			else 
				strWork = "," + strWork;
			strRcv = strRcv + strWork;
		}
	}

	// Read Valueへ表示
	GetDlgItemText(ID_DUMP_VALUE,strWork);
	strWork = strWork + strRcv;
	strWork = strWork + "\r\n";
	SetDlgItemText(ID_DUMP_VALUE,strWork);

	// 最終行を常に表示
	CEdit* pEdit = (CEdit*)GetDlgItem(ID_DUMP_VALUE);
	pEdit->LineScroll(pEdit->GetLineCount());
}

/*
 *  設定ファイルの書込み（UIなし版）
 */
int CSVIctlDlg::SettingFileWriteNoUI(char* fileName)
{
	int result = 0;

	strRecDataFileName = fileName;
	pReadFileThread = AfxBeginThread(XferFileThread, this, THREAD_PRIORITY_NORMAL, 256 * 1024, CREATE_SUSPENDED);
	if (pReadFileThread != NULL)
	{
		pReadFileThread->m_pMainWnd = this;
		pReadFileThread->m_bAutoDelete = FALSE;
		pReadFileThread->ResumeThread();
		DWORD res = WaitForSingleObject(pReadFileThread->m_hThread, 10000);
		if (res == WAIT_TIMEOUT)
		{
			result = -3;
		}
		delete pReadFileThread;
		pReadFileThread = NULL;
		result = m_ThreadReturn;
	}
	else result = -2;

	return result;
}

/*
 *  設定ファイルの書込み（UI制御版）
 */
int CSVIctlDlg::SettingFileWrite(char* fileName)
{
	int result = 0;

	strRecDataFileName = fileName;
	pReadFileThread = AfxBeginThread(ReadFileThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	if (pReadFileThread != NULL)
	{
		pReadFileThread->m_pMainWnd = this;
		pReadFileThread->m_bAutoDelete = FALSE;
		pReadFileThread->ResumeThread();
		MsgDialog.DoModal(ID_MSG_UPDATE_DATAWRITE);
		DWORD res = WaitForSingleObject(pReadFileThread->m_hThread, 10000);
		if (res == WAIT_TIMEOUT)
		{
			result = -3;
		}
		delete pReadFileThread;
		pReadFileThread = NULL;
		result = m_ThreadReturn;
	}
	else result = -2;

	return result;
}

void CSVIctlDlg::OnSettingFileWrite()
{
	if(IsBoardSelected() == false) return;

	// バッファクリア
	//rcvBuf.clear();

//	CString AppName = "SVMCtl_I2C"; // AfxGetAppName();
	CString IniFileName = "\\" + AppName + ".ini";
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Path);
	IniFileName =  Path + IniFileName;
	CIniFileControl iniFile(AppName, IniFileName);

	CString lastFileName = iniFile.GetString("SettingFileName", "");

	// ファイルの読込処理
	char szFilter[sizeof(STR_FILE_INIFILTER)+2] = STR_FILE_INIFILTER;
	// ファイルの指定を行う
	CFileDialog dlg(TRUE, NULL, lastFileName,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR,
						szFilter, NULL );
	dlg.m_ofn.lpstrTitle = "Open File";

	// ＯＫボタンが押されたかチェックする
	if( dlg.DoModal() == IDOK )
		strRecDataFileName = dlg.GetPathName();	// ファイル名を取得する
	else
		return;

	iniFile.SetString("SettingFileName", dlg.GetPathName());

	// ファイルの取得と更新メッセージ出力
	// ファイル読み込み、カメラへの設定のスレッド立ち上げる
	pReadFileThread = AfxBeginThread(ReadFileThread, this);
	// スレッド立ち上げ中は表示しつづける。
	MsgDialog.DoModal(ID_MSG_UPDATE_DATAWRITE);

}

void CSVIctlDlg::OnOK()
{
	// リターンによって画面が閉じないようにする。
	//	CDialog::OnOK();
}

void CSVIctlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// 読み込み処理 (使用しない)
	if(nIDEvent == READTIMER)
			OnRead();
	CDialog::OnTimer(nIDEvent);
}

UINT CSVIctlDlg::ReadFileThread(LPVOID pMain)
{
	CSVIctlDlg* pMainWnd = (CSVIctlDlg*)pMain;
	CButton *pCheck = (CButton *)pMainWnd->GetDlgItem(ID_WORD_ADDRESS);
	int wordMode = pCheck->GetCheck();

	ULONG			deviceAddr;
	ULONG			regAddr;
	UCHAR*			rcvWorkBuff = NULL;
	UCHAR			lineBuf[16*1024];
	CString			strText;
	CString			strValue;

	char* temp;
	ULONG lwork;
	PTCHAR pStopstring;
	CString strWork, readValueText;
	// Flags
	int unit_f = 0;
	int wt_f = 0;
	int slave_f = 0;
	int read_f = 0;
	int unit = 16;
	int wt = 0;

	int fpos = 0;
	int bpos = 0;
	int i,j;
	
	char itemBuf[2560];
	vector<ULONG> ulItem;
	//ULONG ulItem[200];
	unsigned long ulFileLen;
	CFile file;

	pMainWnd->m_ThreadReturn = 0;

	pMainWnd->GetDlgItemText(ID_DUMP_VALUE, readValueText);

	if((pMainWnd->m_sviUsbControl).open() == false){
		AfxMessageBox(ID_MSG_ERR_NO_SVI03);
		pMainWnd->m_ThreadReturn = 1;
		goto readfile_end;
	}

	// 設定値の取得
	// Slave Addressの取得
	pMainWnd->GetDlgItemText(ID_SLAVE_ADDRESS, strText);
	strText.TrimLeft();
	strText.TrimRight();
	if(strText.GetLength()==0)
	{
		AfxMessageBox(ID_MSG_ERR_NOINPUTSLAVE);
		pMainWnd->m_ThreadReturn = 2;
		goto readfile_end;
	}
	if(!pMainWnd->Checkalnum((LPCTSTR)strText))
	{
		AfxMessageBox(ID_MSG_ERR_DATASLAVE);
		pMainWnd->m_ThreadReturn = 3;
		goto readfile_end;
	}

	deviceAddr = _tcstoul(strText, &temp, 16);

	if(!file.Open(pMainWnd->strRecDataFileName ,
							CFile::modeRead |
							CFile::shareExclusive |
							CFile::typeBinary))
	{
		AfxMessageBox(ID_MSG_ERR_FILEOPEN);
		pMainWnd->m_ThreadReturn = 4;
		goto readfile_end;
	}

	// ファイル読み込み(カンマ区切り形式)
	ulFileLen = file.GetLength();
	rcvWorkBuff = new UCHAR [ulFileLen + 2];
	file.Read(rcvWorkBuff, ulFileLen);
	rcvWorkBuff[ulFileLen++] = '\0';// [21/04/06] avoid fail for reading last line
	strValue = rcvWorkBuff;
	file.Close();

	// 正常に読み込めなかったらエラー
	if(strValue.GetLength()==0){
		AfxMessageBox(ID_MSG_ERR_FILEREAD);
		pMainWnd->m_ThreadReturn = 5;
		goto readfile_end;
	}

	int lineCnt = 0;
	// ファイル解析＆I2C送信
	while(fpos < ulFileLen)
	{
		// 1行を取得
		for(bpos=0; fpos < ulFileLen; fpos++)
		{
			if(rcvWorkBuff[fpos] == '\r' && rcvWorkBuff[fpos+1] == '\n')
			{
				lineBuf[bpos++] = '\0';
				lineCnt ++;
				fpos+=2;
				break;
			}
			else if (rcvWorkBuff[fpos] == '\r' || rcvWorkBuff[fpos] == '\n' || rcvWorkBuff[fpos] == '\0') // [21/04/06] avoid fail for reading last line
			{
				lineBuf[bpos++] = '\0';
				lineCnt++;
				fpos += 1;
				break;
			}
			lineBuf[bpos++] = rcvWorkBuff[fpos];
		}
		// コメント行（先頭カラムが'#'か';'）だったらスキップ
		if(lineBuf[0] == '#' || lineBuf[0] == ';' || lineBuf[0] == '\0' || lineBuf[0] == '/') continue;
		// 1行を解析
		ulItem.clear();
		for(i=j=0;i<bpos;i++)
		{
			// 行中のアイテム抽出
			if( lineBuf[i] == ','  ||
					lineBuf[i] == ' '  || 
					lineBuf[i] == '\t' ||
					lineBuf[i] == ';'  ||
					lineBuf[i] == '#'  ||
					lineBuf[i] == '\0')
			{

				char* temp;
				// 制御文（"UNIT","WT","SLAVE"）だったら制御処理を行う
				itemBuf[j++] = '\0';

				if(_tcsncmp(itemBuf, "UNIT", 4) == 0) unit_f = 1;
				else if(_tcsncmp(itemBuf, "BYTE", 4) == 0) wordMode = 0;
				else if(_tcsncmp(itemBuf, "WORD", 4) == 0) wordMode = 1;
				else if(_tcsncmp(itemBuf, "wt", 2) == 0) wt_f = 1;
				else if(_tcsncmp(itemBuf, "WT", 2) == 0) wt_f = 1;
				else if(_tcsncmp(itemBuf, "SLAVE", 5) == 0) slave_f = 1;
				else if(_tcsncmp(itemBuf, "READ", 4) == 0) read_f = 1;
				else{
					if(unit_f != 0){
						unit = strtol(itemBuf, &temp, 10);
						unit_f = 0;
					}else if(wt_f != 0){
						wt = strtol(itemBuf, &temp, unit); // [17/12/06] unit should be 10 but this inherites old version...
						Sleep(wt);
						wt_f = 0;
					}else if(slave_f != 0){
						deviceAddr = strtol(itemBuf, &temp, unit);
						slave_f = 0;
					}else if(read_f != 0){
						if(ulItem.size() == 1){ // 2nd content
							ulItem.push_back(strtoul(itemBuf, &temp, 10));
						}else{
							ulItem.push_back(strtoul(itemBuf, &temp, unit));
						}
					}else{
						if(itemBuf[0] != '\0' )
						{
							ulItem.push_back(strtoul(itemBuf, &temp, unit));
						}
					}
				}
				j = 0;
				if( lineBuf[i] == ';' || lineBuf[i] == '#' || lineBuf[i] == '\0') break;
			}else{
				itemBuf[j++] = lineBuf[i];
			}
		}
		
		if(read_f) // READ コマンド実行
		{
			read_f = 0;
			if(ulItem.size() != 2) // READ コマンドが不完全
			{
				{
					// debug msg
					char text[512];
					sprintf(text, "Line %d: %s", lineCnt, lineBuf);
					::MessageBoxA(NULL, text, "Error (incomplete READ command)", MB_OK);
				}
				AfxMessageBox(ID_MSG_ERR_INIT);
				pMainWnd->m_ThreadReturn = 6;
				goto readfile_end;
			}
			else
			{
				regAddr = ulItem[0];
				ULONG readSize = ulItem[1];
				
				if(readSize == 0)
				{
					char text[512];
					sprintf(text, "Line %d: %s", lineCnt, lineBuf);
					::MessageBoxA(NULL, text, "Error (Read count is 0)", MB_OK);
					AfxMessageBox(ID_MSG_ERR_INIT);
					pMainWnd->m_ThreadReturn = 6;
					goto readfile_end;
				}
				else
				{
					BYTE* readBuf = new BYTE[readSize];
					
					bool result = (pMainWnd->m_sviUsbControl).GetValue2(deviceAddr, regAddr, readBuf, readSize, wordMode, TRUE); // 0x08 判定はこの中で行われる

					if(!result) 
					{
						{
							// debug msg
							char text[512];
							sprintf(text, "Line %d: %s", lineCnt, lineBuf);
							::MessageBoxA(NULL, text, "I2C Read Error", MB_OK);
						}
						AfxMessageBox(ID_MSG_ERR_INIT);
						pMainWnd->m_ThreadReturn = 6;
						delete [] readBuf;
						goto readfile_end;
					}

					delete [] readBuf;
				}
			}
		}
		else
		{
			// I2C送信
			if(ulItem.size() != 0)
			{
				regAddr = ulItem[0];
				if(ulItem.size() > 1)
				{
					BYTE* sendBuf = new BYTE[ulItem.size()-1];
					for(i=1;i<ulItem.size();i++){
						sendBuf[i-1] = (UCHAR)ulItem[i];
					}

					if(!(pMainWnd->m_sviUsbControl).SetValue2(deviceAddr, regAddr, sendBuf, ulItem.size()-1, wordMode)) // 0x08 判定はこの中で行われる
					{
						{
							// debug msg
							char text[512];
							sprintf(text, "Line %d: %s", lineCnt, lineBuf);
							::MessageBoxA(NULL, text, "I2C Write Error", MB_OK);
						}
						AfxMessageBox(ID_MSG_ERR_INIT);
						pMainWnd->m_ThreadReturn = 6;
						delete [] sendBuf;
						goto readfile_end;
					}
					delete [] sendBuf;
				}
			}
		}
	}
	
	/*
	pMainWnd->SetDlgItemText(ID_DUMP_VALUE, readValueText);
	// 最終行を常に表示
	CEdit* pEdit = (CEdit*)(pMainWnd->GetDlgItem(ID_DUMP_VALUE));
	pEdit->LineScroll(pEdit->GetLineCount());
	*/
	

readfile_end:
	::PostMessage(pMainWnd->MsgDialog.m_hWnd,WM_CLOSE,0,0);
	if(rcvWorkBuff) delete [] rcvWorkBuff;

	if((pMainWnd->m_sviUsbControl).close() == false){
		AfxMessageBox(ID_MSG_ERR_NO_SVI03);
		goto readfile_end;
	}

	pMainWnd->EndDialog(0);
	return 0;
}

/*
 *  設定ファイル書込み処理スレッド（UIなし版）
 */
UINT CSVIctlDlg::XferFileThread(LPVOID pMain)
{
	CSVIctlDlg* pMainWnd = (CSVIctlDlg*)pMain;
	int wordMode = 0; //pCheck->GetCheck();

	ULONG			deviceAddr;
	ULONG			regAddr;
	UCHAR* rcvWorkBuff = NULL;
	UCHAR			lineBuf[16 * 1024];
	CString			strText;
	CString			strValue;

	char* temp;
	ULONG lwork;
	PTCHAR pStopstring;
	CString strWork, readValueText;
	// Flags
	int unit_f = 0;
	int wt_f = 0;
	int slave_f = 0;
	int read_f = 0;
	int unit = 16;
	int wt = 0;

	int fpos = 0;
	int bpos = 0;
	int i, j;

	char itemBuf[2560];
	vector<ULONG> ulItem;
	unsigned long ulFileLen;
	CFile file;

	pMainWnd->m_ThreadReturn = 0;

	if ((pMainWnd->m_sviUsbControl).open() == false) {
		pMainWnd->m_ThreadReturn = 1;
		goto readfile_end_xfer;
	}

	deviceAddr = _tcstoul("1a", &temp, 16);

	if (!file.Open(pMainWnd->strRecDataFileName,
		CFile::modeRead |
		CFile::shareExclusive |
		CFile::typeBinary))
	{
		pMainWnd->m_ThreadReturn = 4;
		goto readfile_end_xfer;
	}

	// ファイル読み込み(カンマ区切り形式)
	ulFileLen = file.GetLength();
	rcvWorkBuff = new UCHAR[ulFileLen + 2];
	file.Read(rcvWorkBuff, ulFileLen);
	rcvWorkBuff[ulFileLen++] = '\0';
	strValue = rcvWorkBuff;
	file.Close();

	// 正常に読み込めなかったらエラー
	if (strValue.GetLength() == 0) {
		pMainWnd->m_ThreadReturn = 5;
		goto readfile_end_xfer;
	}

	int lineCnt = 0;
	// ファイル解析＆I2C送信
	while (fpos < ulFileLen)
	{
		// 1行を取得
		for (bpos = 0; fpos < ulFileLen; fpos++)
		{
			if (rcvWorkBuff[fpos] == '\r' && rcvWorkBuff[fpos + 1] == '\n')
			{
				lineBuf[bpos++] = '\0';
				lineCnt++;
				fpos += 2;
				break;
			}
			else if (rcvWorkBuff[fpos] == '\r' || rcvWorkBuff[fpos] == '\n' || rcvWorkBuff[fpos] == '\0')
			{
				lineBuf[bpos++] = '\0';
				lineCnt++;
				fpos += 1;
				break;
			}
			lineBuf[bpos++] = rcvWorkBuff[fpos];
		}
		// コメント行（先頭カラムが'#'か';'）だったらスキップ
		if (lineBuf[0] == '#' || lineBuf[0] == ';' || lineBuf[0] == '\0' || lineBuf[0] == '/') continue;
		// 1行を解析
		ulItem.clear();
		for (i = j = 0;i < bpos;i++)
		{
			// 行中のアイテム抽出
			if (lineBuf[i] == ',' ||
				lineBuf[i] == ' ' ||
				lineBuf[i] == '\t' ||
				lineBuf[i] == ';' ||
				lineBuf[i] == '#' ||
				lineBuf[i] == '\0')
			{

				char* temp;
				// 制御文（"UNIT","WT","SLAVE"）だったら制御処理を行う
				itemBuf[j++] = '\0';

				if (_tcsncmp(itemBuf, "UNIT", 4) == 0) unit_f = 1;
				else if (_tcsncmp(itemBuf, "BYTE", 4) == 0) wordMode = 0;
				else if (_tcsncmp(itemBuf, "WORD", 4) == 0) wordMode = 1;
				else if (_tcsncmp(itemBuf, "wt", 2) == 0) wt_f = 1;
				else if (_tcsncmp(itemBuf, "WT", 2) == 0) wt_f = 1;
				else if (_tcsncmp(itemBuf, "SLAVE", 5) == 0) slave_f = 1;
				else if (_tcsncmp(itemBuf, "READ", 4) == 0) read_f = 1;
				else {
					if (unit_f != 0) {
						unit = strtol(itemBuf, &temp, 10);
						unit_f = 0;
					}
					else if (wt_f != 0) {
						wt = strtol(itemBuf, &temp, unit);
						Sleep(wt);
						wt_f = 0;
					}
					else if (slave_f != 0) {
						deviceAddr = strtol(itemBuf, &temp, unit);
						slave_f = 0;
					}
					else if (read_f != 0) {
						if (ulItem.size() == 1) { // 2nd content
							ulItem.push_back(strtoul(itemBuf, &temp, 10));
						}
						else {
							ulItem.push_back(strtoul(itemBuf, &temp, unit));
						}
					}
					else {
						if (itemBuf[0] != '\0')
						{
							ulItem.push_back(strtoul(itemBuf, &temp, unit));
						}
					}
				}
				j = 0;
				if (lineBuf[i] == ';' || lineBuf[i] == '#' || lineBuf[i] == '\0') break;
			}
			else {
				itemBuf[j++] = lineBuf[i];
			}
		}

		if (read_f) // READ コマンド実行
		{
			read_f = 0;
			if (ulItem.size() != 2) // READ コマンドが不完全
			{
				pMainWnd->m_ThreadReturn = 6;
				goto readfile_end_xfer;
			}
			else
			{
				regAddr = ulItem[0];
				ULONG readSize = ulItem[1];

				if (readSize == 0)
				{
					pMainWnd->m_ThreadReturn = 6;
					goto readfile_end_xfer;
				}
				else
				{
					BYTE* readBuf = new BYTE[readSize];

					bool result = (pMainWnd->m_sviUsbControl).GetValue2(deviceAddr, regAddr, readBuf, readSize, wordMode, TRUE); // 0x08 判定はこの中で行われる

					if (!result)
					{
						pMainWnd->m_ThreadReturn = 6;
						delete[] readBuf;
						goto readfile_end_xfer;
					}

					delete[] readBuf;
				}
			}
		}
		else
		{
			// I2C送信
			if (ulItem.size() != 0)
			{
				regAddr = ulItem[0];
				if (ulItem.size() > 1)
				{
					BYTE* sendBuf = new BYTE[ulItem.size()];
					for (i = 1;i < ulItem.size(); i++) {
						sendBuf[i - 1] = (UCHAR)ulItem[i];
					}

					if (!(pMainWnd->m_sviUsbControl).SetValue2(deviceAddr, regAddr, sendBuf, ulItem.size() - 1, wordMode)) // 0x08 判定はこの中で行われる
					{
						pMainWnd->m_ThreadReturn = 6;
						delete[] sendBuf;
						goto readfile_end_xfer;
					}
					delete[] sendBuf;
				}
			}
		}
	}

readfile_end_xfer:
	if (rcvWorkBuff) delete[] rcvWorkBuff;

	if ((pMainWnd->m_sviUsbControl).close() == false) {
		AfxMessageBox(ID_MSG_ERR_NO_SVI03);
		goto readfile_end_xfer;
	}

	return 0;
}


bool CSVIctlDlg::Checkalnum(LPCTSTR strText,bool cammaflg)
{
	bool rf = false;
	int len = _tcslen(strText);
	for(int i = 0;i<len;i++)
	{
		if(!_istalnum(strText[i]))
		{
			if(!cammaflg)
				return false;
			if(strText[i] != ',' )
				return false;
		}
	}
	return true;
}

void CSVIctlDlg::OnClose()
{
	//アプリ終了時iniファイルに現状を保存

	CIniFileControl iniFile(AppName,IniFileName);

	//	ID_SLAVE_ADDRESS
	CString slaveAddress;
	this->GetDlgItemText(ID_SLAVE_ADDRESS,slaveAddress);
	iniFile.SetString(INI_KEY_SLAVE_ADDRESS,slaveAddress);

	// ID_SUB_ADDRESS
	CString subAddress;
	this->GetDlgItemText(ID_SUB_ADDRESS,subAddress);
	iniFile.SetString(INI_KEY_SUB_ADDRESS,subAddress);

	// ID_VALUE
	CString value;
	this->GetDlgItemText(ID_VALUE,value);
	iniFile.SetString(INI_KEY_VALUE,value);

	// ID_READ_COUNTS
	CString readCounts;
	this->GetDlgItemText(ID_READ_COUNTS,readCounts);
	iniFile.SetString(INI_KEY_READ_COUNTS,readCounts);

	// ID_WORD_ADDRESS
	int wordAddress = ((CButton*)this->GetDlgItem(ID_WORD_ADDRESS))->GetCheck();
	iniFile.SetInt(INI_KEY_WORD_ADDRESS,wordAddress);

	CDialog::OnClose();
}

bool CSVIctlDlg::IsBoardSelected()
{
	return true;
}



// SVIUSBControlのポインタを取得します
CSviUsbControl* CSVIctlDlg::GetSviUsbControl(void)
{
	 return &m_sviUsbControl;
}
void CSVIctlDlg::OnBnClickedWordAddress()
{
	return;
	// debug
	CButton *pCheck = (CButton *)GetDlgItem(ID_WORD_ADDRESS);

	if( pCheck->GetCheck()){
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x01}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0x08000018UL, buf, 4, TRUE);
		m_sviUsbControl.SetValue2(0x08, 0x0800001CUL, buf, 4, TRUE);
	}else{
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0x08000018UL, buf, 4, TRUE);
		m_sviUsbControl.SetValue2(0x08, 0x0800001CUL, buf, 4, TRUE);
	}
}

void CSVIctlDlg::OnBnClickedBoardPower()
{
	UpdateData();
	// 選択されているSVI-03ボードを設定します
	if(IsBoardSelected() == false) return;

	if(m_boardPower){
		unsigned char buf[4] = {0x00, 0x00, 0x01, 0x00}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0x10000000UL, buf, 4, TRUE);
	}else{
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00};
		m_sviUsbControl.SetValue2(0x08, 0x10000000UL, buf, 4, TRUE);
	}
}

void CSVIctlDlg::OnBnClickedDebug()
{
	CButton *pCheck = (CButton *)GetDlgItem(ID_Debug);

	if( pCheck->GetCheck()){
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0xB0000000UL, buf, 4, TRUE);
	}else{
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x01}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0xB0000000UL, buf, 4, TRUE);
	}
}

void CSVIctlDlg::OnBnClickedDebug2()
{
	CButton *pCheck = (CButton *)GetDlgItem(ID_Debug2);

	if( pCheck->GetCheck()){
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x80}; // MSB First
		m_sviUsbControl.SetValue2(0x08, 0x08000084UL, buf, 4, TRUE);
	}else{
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00};
		m_sviUsbControl.SetValue2(0x08, 0x08000084UL, buf, 4, TRUE);
	}

	EndDialog(0);
}
void CSVIctlDlg::OnBnClickedRestartSvm()
{
	unsigned char buf[4] = {0x00, 0x00, 0x00, 0x80}; // MSB First
	m_sviUsbControl.SetValue2(0x08, 0x08000084UL, buf, 4, TRUE);

	EndDialog(0);
}


void CSVIctlDlg::OnBnClickedButton1()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(ID_DUMP_VALUE);
	pEdit->SetWindowTextA("");
}