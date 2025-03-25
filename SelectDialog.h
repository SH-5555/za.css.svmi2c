#pragma once
#include "afxwin.h"

#include <vector>
using namespace std;

// CSelectDialog ダイアログ

class CSelectDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectDialog)

public:
	CSelectDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSelectDialog();

// ダイアログ データ
	enum { IDD = IDD_SELECT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list1;
	vector<CString> m_boardList;

	afx_msg void OnBnClickedOk();
	int m_boardID;
	virtual BOOL OnInitDialog();
};
