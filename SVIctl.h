// SVIctl.h : SVICTL アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_)
#define AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp:
// このクラスの動作の定義に関しては SVIctl.cpp ファイルを参照してください。
//

class CSVIctlApp : public CWinApp
{
public:
	CSVIctlApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSVIctlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSVIctlApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_)
