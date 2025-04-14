// SVIctlDlg.h : ヘッダー ファイル
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SviUsbControl.h"
#include "MsgDialog.h"
//#include "SVMSettingDlg.h"
#include "SVMSettingInfo.h"
#include <afxmt.h>
#include <vector>
#include <mmsystem.h>	// timeGetTime()
#pragma comment( lib, "winmm.lib" )

using namespace std;

#if !defined(AFX_SVICTLDLG_H__D38F6FBD_CC9E_4A99_B432_A50F6213B516__INCLUDED_)
#define AFX_SVICTLDLG_H__D38F6FBD_CC9E_4A99_B432_A50F6213B516__INCLUDED_

#include "IniFileControl.h"

// ファイルフィルタ
#define STR_FILE_DATFILTER		"Record File (*.dat)|*.dat|"			// Datファイルフィルタ
#define STR_FILE_BMPFILTER		"Bitmap File (*.bmp)|*.bmp|"			// Bmpファイルフィルタ
#define STR_FILE_FWFILTER		"Update File (fw*.bin)|fw*.bin|"		// firmwareファイルフィルタ
//#define STR_FILE_FPGAFILTER		"Update File (fpga*.bin)|fpga*.bin|"	// fpgaファイルフィルタ
#define STR_FILE_DATBMPFILTER	"Record File (*.dat)|*.dat|Bitmap File (*.bmp)|*.bmp|"	// Dat or Bmpファイルフィルタ
#define STR_FILE_INIFILTER		"Text and Initialize File (*.txt,*.ini)|*.txt;*.ini|CSV File (*.csv)|*.csv|ALL File (*.*)|*.*|"
																		// Datファイルフィルタ 2006/1/16 txt 拡張子追加
//const CString STR_FILE_FWFILTER = "Update File (so*fw*.bin)|so*fw*.bin|";		///< @brief firmwareファイルフィルタ
#define STR_FILE_FX3FILTER  "Update File (*.img)|*.img|";		///< @brief firmwareファイルフィルタ
#define STR_FILE_FPGAFILTER  "Update File (*.bin)|*.bin|";		///< @brief firmwareファイルフィルタ

//	タイマー
#define READTIMER			100		// タイマーID
#define	TIMER_SPEED			1000	// 初期タイマー速度


#define INI_KEY_SLAVE_ADDRESS "SlaveAddress"
#define DEFAULT_SLAVE_ADDRESS ""

#define INI_KEY_SUB_ADDRESS "SubAddress"
#define DEFAULT_SUB_ADDRESS ""

#define INI_KEY_VALUE "Value"
#define DEFAULT_VALUE ""

#define INI_KEY_READ_COUNTS "ReadCounts"
#define DEFAULT_READ_COUNTS ""

#define INI_KEY_REALTIME "RealTime"
#define DEFAULT_REALTIME 0

#define INI_KEY_WORD_ADDRESS "WordAddress"
#define DEFAULT_WORD_ADDRESS 0

#if 1 // 2012.07.24 V3.2.2.0
#define INI_KEY_RESTART_ENABLE "RestartConditionEnable"
#define DEFAULT_RESTART_ENABLE 0
#endif // 2012.07.24 V3.2.2.0


/////////////////////////////////////////////////////////////////////////////
// CSVIctlDlg ダイアログ

#include "IniFileControl.h"	// ClassView によって追加されました。
#include "afxwin.h"
class CSVIctlDlg : public CDialog
{
// 構築
public:
	bool IsBoardSelected();
	CSVIctlDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	CString strRecDataFileName;

// ダイアログ データ
	//{{AFX_DATA(CSVIctlDlg)
	enum { IDD = IDD_SVICTL_DIALOG };
	//}}AFX_DATA

protected:
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSVIctlDlg)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// SVIコントロール
	CSviUsbControl m_sviUsbControl;

	// 格納用バッファ
	//vector<UCHAR> RcvBuff;

	// メッセージ表示用ダイアログ
	CMsgDialog MsgDialog;

	// CSV形式文字列のパース
	int ParseCsv(CString strData, UCHAR* workBuf, ULONG bufSize);

	// CSV形式文字列のパース 2006.1.13 update
//	bool ParseCsv(CString strData, UCHAR* workBuf, ULONG bufSize, BOOL bWord);

	// 英数文字チェック
	static bool Checkalnum(LPCTSTR strText,bool cammaflg = false);

	//スレッド関数
	CWinThread *pReadFileThread;
	static UINT CSVIctlDlg::ReadFileThread(LPVOID pMain);
	static UINT CSVIctlDlg::XferFileThread(LPVOID pMain);

	//iniファイルで使用
	CString AppName;//アプリケーション名
	CString IniFileName;//iniファイル名

//	SVMSettingInfo SVMSettingInfo; // SVM設定値格納クラス
//	CSettingDataManager m_settingData;

//	BOOL SVMSettingSPIRead();
//	BOOL SVMSettingSPIWrite();


	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSVIctlDlg)
	virtual BOOL OnInitDialog();
//	virtual INT_PTR DoModal();
	afx_msg void OnWrite();
	afx_msg void OnRead();
	afx_msg void OnOK();
	afx_msg void OnSettingFileWrite();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int UpdateBoardInfoFromCC(const UCHAR* customCode, const UCHAR* versionInfo);
	int GetBoardNameFromCC(char* boardName, const UCHAR* customCode, const UCHAR* versionInfo, int i);
public:
	CSviUsbControl* GetSviUsbControl();

	CButton m_cButtonSetting;
	CButton m_cButtonSFR;
	CButton m_cButtonWrite;
	CButton m_cButtonRead;
	afx_msg void OnBnClickedWordAddress();
	afx_msg void OnBnClickedBoardPower();
	BOOL m_boardPower;
	afx_msg void OnBnClickedDebug();
	afx_msg void OnBnClickedDebug2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRestartSvm();
	CButton m_cButtonRestart;

	BOOL OpenCaptureBoard();
	int SettingFileWriteNoUI(char* fileNama);
	int SettingFileWrite(char *fileNama);
	int WriteReg(ULONG devAddr, ULONG regAddr, UCHAR regVal);

	virtual INT_PTR DoModal();

	int m_ThreadReturn;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SVICTLDLG_H__D38F6FBD_CC9E_4A99_B432_A50F6213B516__INCLUDED_)
