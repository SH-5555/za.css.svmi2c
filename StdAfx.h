// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__EF02CB33_F816_4457_8365_94833852C065__INCLUDED_)
#define AFX_STDAFX_H__EF02CB33_F816_4457_8365_94833852C065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// <devioctl.h>と<winioctl.h>内で定義が被るため<winioctl.h>は
// インクルードしないようにする
#define _WINIOCTL_

#pragma warning(disable:4996)


#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

// VID/PID
#define SVM_VID 0x0525
#define SVM_PID 0xA115

// Firmware Revision
extern int SVM_03_REVISION; // 0: SVM-03 / 1: SVM-03U / 2: SVI-05U / 3: UB3-01

#define IS_SVM03()  (SVM_03_REVISION == 0)
#define IS_SVM03U() (SVM_03_REVISION == 1)
#define IS_SVI05U() (SVM_03_REVISION == 2)
#define IS_UB3_01() (SVM_03_REVISION == 3)
#define IS_SVM03W() (SVM_03_REVISION == 4)
#define IS_SVM06() (SVM_03_REVISION == 15 || SVM_03_REVISION == 16)
#define IS_SVM06_HDMI() (SVM_03_REVISION == 16)
//#define IS_SVO03() (SVM_03_REVISION == 5)
#define IS_SVI09() ((SVM_03_REVISION == 10) || (SVM_03_REVISION == 11) || (SVM_03_REVISION == 15) ||(SVM_03_REVISION == 24))
#define IS_SVI09_LAN() (SVM_03_REVISION == 11)
#define IS_SVO03() ((SVM_03_REVISION == 20) || (SVM_03_REVISION == 21)) // SVO-03 or SVO-MIPI
#define IS_SVO_MIPI() (SVM_03_REVISION == 21) // SPI not supported
#define IS_SVO09() (SVM_03_REVISION == 22) // SPI not supported
#define IS_SVO_MIPI_HDMI() (SVM_03_REVISION == 23) // NOT confused to SVO_MIPI which is non-accessible SPI!
#define IS_ARTIX_UPDATER() ((SVM_03_REVISION == 23) || (SVM_03_REVISION == 24))
#define IS_SVO06() (SVM_03_REVISION == 25) // SPI supported

#define IS_SVP01() ((SVM_03_REVISION == 31) || (SVM_03_REVISION == 32) || (SVM_03_REVISION == 33) || (SVM_03_REVISION == 39))

#define IS_MIPI_BOARD() (IS_SVO_MIPI() || SVM_MIPI_BOARD || IS_SVO06())
#define IS_ARTIX_BOARD() (IS_SVO_MIPI() || IS_SVO06() || IS_SVO09() || IS_SVO_MIPI_HDMI() || IS_SVM06_HDMI() || IS_SVM06() || IS_ARTIX_UPDATER() || IS_SVP01())

// [21/07/30] Whether display USB Version of board? (Windows DDK required for this option)
#define USE_USB_VERSION 0

extern char g_boardName[64];

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#include <windows.h>

#endif // !defined(AFX_STDAFX_H__EF02CB33_F816_4457_8365_94833852C065__INCLUDED_)
