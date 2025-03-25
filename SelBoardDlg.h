#pragma once
#include "afxwin.h"


// CSelBoardDlg �_�C�A���O

class CSelBoardDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelBoardDlg)

public:
	CSelBoardDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSelBoardDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SELBOARD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
