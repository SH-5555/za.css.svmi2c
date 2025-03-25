#pragma once
#include "afxwin.h"


// CSelBoardDlg ダイアログ

class CSelBoardDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelBoardDlg)

public:
	CSelBoardDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSelBoardDlg();

// ダイアログ データ
	enum { IDD = IDD_SELBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo1;
	virtual BOOL OnInitDialog();

	void AppendBoardName(const char* name)
	{
		strncpy(m_boardName[m_maxBoardName], name, 127);
		m_maxBoardName ++;
	};
	int m_curBoardIdx;
private:
	int  m_maxBoardName;
	char m_boardName[16][128];
public:
	afx_msg void OnBnClickedOk();
};
