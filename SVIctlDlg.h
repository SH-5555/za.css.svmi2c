// SVIctlDlg.h : �w�b�_�[ �t�@�C��
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

// �t�@�C���t�B���^
#define STR_FILE_DATFILTER		"Record File (*.dat)|*.dat|"			// Dat�t�@�C���t�B���^
#define STR_FILE_BMPFILTER		"Bitmap File (*.bmp)|*.bmp|"			// Bmp�t�@�C���t�B���^
#define STR_FILE_FWFILTER		"Update File (fw*.bin)|fw*.bin|"		// firmware�t�@�C���t�B���^
//#define STR_FILE_FPGAFILTER		"Update File (fpga*.bin)|fpga*.bin|"	// fpga�t�@�C���t�B���^
#define STR_FILE_DATBMPFILTER	"Record File (*.dat)|*.dat|Bitmap File (*.bmp)|*.bmp|"	// Dat or Bmp�t�@�C���t�B���^
#define STR_FILE_INIFILTER		"Text and Initialize File (*.txt,*.ini)|*.txt;*.ini|CSV File (*.csv)|*.csv|ALL File (*.*)|*.*|"
																		// Dat�t�@�C���t�B���^ 2006/1/16 txt �g���q�ǉ�
//const CString STR_FILE_FWFILTER = "Update File (so*fw*.bin)|so*fw*.bin|";		///< @brief firmware�t�@�C���t�B���^
#define STR_FILE_FX3FILTER  "Update File (*.img)|*.img|";		///< @brief firmware�t�@�C���t�B���^
#define STR_FILE_FPGAFILTER  "Update File (*.bin)|*.bin|";		///< @brief firmware�t�@�C���t�B���^

//	�^�C�}�[
#define READTIMER			100		// �^�C�}�[ID
#define	TIMER_SPEED			1000	// �����^�C�}�[���x


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
// CSVIctlDlg �_�C�A���O

#include "IniFileControl.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "afxwin.h"
class CSVIctlDlg : public CDialog
{
// �\�z
public:
	bool IsBoardSelected();
	CSVIctlDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
	CString strRecDataFileName;

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSVIctlDlg)
	enum { IDD = IDD_SVICTL_DIALOG };
	//}}AFX_DATA

protected:
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSVIctlDlg)
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// SVI�R���g���[��
	CSviUsbControl m_sviUsbControl;

	// �i�[�p�o�b�t�@
	//vector<UCHAR> RcvBuff;

	// ���b�Z�[�W�\���p�_�C�A���O
	CMsgDialog MsgDialog;

	// CSV�`��������̃p�[�X
	int ParseCsv(CString strData, UCHAR* workBuf, ULONG bufSize);

	// CSV�`��������̃p�[�X 2006.1.13 update
//	bool ParseCsv(CString strData, UCHAR* workBuf, ULONG bufSize, BOOL bWord);

	// �p�������`�F�b�N
	static bool Checkalnum(LPCTSTR strText,bool cammaflg = false);

	//�X���b�h�֐�
	CWinThread *pReadFileThread;
	static UINT CSVIctlDlg::ReadFileThread(LPVOID pMain);
	static UINT CSVIctlDlg::XferFileThread(LPVOID pMain);

	//ini�t�@�C���Ŏg�p
	CString AppName;//�A�v���P�[�V������
	CString IniFileName;//ini�t�@�C����

//	SVMSettingInfo SVMSettingInfo; // SVM�ݒ�l�i�[�N���X
//	CSettingDataManager m_settingData;

//	BOOL SVMSettingSPIRead();
//	BOOL SVMSettingSPIWrite();


	// �������ꂽ���b�Z�[�W �}�b�v�֐�
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
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SVICTLDLG_H__D38F6FBD_CC9E_4A99_B432_A50F6213B516__INCLUDED_)
