#if !defined(AFX_DUMPDIALOG_H__784F39E2_38C9_4252_AA67_9D31A1CB3934__INCLUDED_)
#define AFX_DUMPDIALOG_H__784F39E2_38C9_4252_AA67_9D31A1CB3934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog ダイアログ

class CDumpDialog : public CDialog
{
// コンストラクション
public:
	CDumpDialog(int *len,CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDumpDialog)
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDumpDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDumpDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int *m_len;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DUMPDIALOG_H__784F39E2_38C9_4252_AA67_9D31A1CB3934__INCLUDED_)
