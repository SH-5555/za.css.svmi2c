#if !defined(AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_)
#define AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMsgDialog ダイアログ

class CMsgDialog : public CDialog
{
// コンストラクション
public:
	CMsgDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMsgDialog)
	enum { IDD = IDD_MSG_DIALOG };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMsgDialog)
	public:
	virtual int DoModal(UINT UID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	CString strMsg;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMsgDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL SetMessge(UINT UID);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_)
