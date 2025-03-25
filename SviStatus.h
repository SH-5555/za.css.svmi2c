// SviStatus.h: CSviStatus クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_)
#define AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SVI05API.h"

//SVIハードウエアステータスを保持するクラス
class CSviStatus  
{
public:
	CSviStatus();
	CSviStatus(GET_STATUS &status);
	virtual ~CSviStatus();

	//GET_STATUSにキャスト
	operator GET_STATUS(){return getStatus();};

	//SVIハードウエアステータスを設定します
	void setStatus(GET_STATUS &status);

	//SVIハードウエアステータスを返します
	GET_STATUS getStatus(void){return SviStatus;};

	//SVIハードウエアステータスのうち基本ステータスのみを設定します
	void setBaseStatus(ULONG status);

	//SVIハードウエアステータスのうち基本ステータスのみを返します
	ULONG getBasicStatus(void){return SviStatus.ulBasicStatus;};

	//基本ステータスが正常終了かどうか
	bool IsSuccess(void);

	//基本ステータス情報を文字列化します。
	CString getBasicStatusString(ULONG basicStatus);

	//アイドル状態か確認
	bool IsIdle(void){return (SviStatus.ulOPStatus==0);};

	//モニタリング状態か確認
	bool IsMonitring(void){return (SviStatus.ulOPStatus==1);};

	//レコーディング状態か確認
	bool IsRecording(void){return (SviStatus.ulOPStatus==2);};

	//アップデート中か確認
	bool IsUpdating(void){return (SviStatus.ulOPStatus==8);};

	//保留フレーム・データがあるか確認
	bool IsFramePending(void){return (SviStatus.ulBasicStatus==SVI_STS_FRAMEPENDING);};



private:
	//SVIハードウエアステータス
	GET_STATUS SviStatus;
};

#endif // !defined(AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_)
