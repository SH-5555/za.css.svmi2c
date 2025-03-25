// SviStatus.cpp: CSviStatus クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SviStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

//デフォルトコンストラクタ
CSviStatus::CSviStatus()
{

}

//SVIハードウエアステータスを引数にとるコンストラクタ
CSviStatus::CSviStatus(GET_STATUS &status)
{
	setStatus(status);
}


CSviStatus::~CSviStatus()
{

}

//SVIハードウエアステータスを設定します
void CSviStatus::setStatus(GET_STATUS &status)
{
	//引数をメンバ変数にコピー
	memcpy(&SviStatus, &status, sizeof(GET_STATUS));
}

//SVIハードウエアステータスのうち基本ステータスのみを設定します
void CSviStatus::setBaseStatus(ULONG status)
{
	SviStatus.ulBasicStatus = status;
}

//基本ステータスが正常終了かどうか
bool CSviStatus::IsSuccess(void)
{
	switch(SviStatus.ulBasicStatus)
	{
	case SVI_STS_SUCCESS:
	case SVI_STS_FRAMEPENDING:
	case SVI_STS_CAPCANCELED:
		return true;
	default:
		break;
	}
	return false;
}
//基本ステータス情報を文字列化します。
CString getBasicStatusString(ULONG basicStatus)
{
	CString outputString;
	switch(basicStatus)
	{
	case SVI_STS_SUCCESS:  
		outputString = " 正常終了";
		break;
	case SVI_STS_FRAMEPENDING:  
		outputString = " 正常終了 (保留フレーム/データあり)";
		break;
	case SVI_STS_CAPCANCELED    :  
		outputString = " 正常終了 (キャプチャが中止された)";
		break;
	case SVI_STS_BUSY           :  
		outputString = " ビジーでコマンドが実行できません";
		break;
	case SVI_STS_RECOVERYMODE   :  
		outputString = " リカバリーモードのためコマンドが実行できません";
		break;
	case SVI_STS_I2CACTIVE      :  
		outputString = " I2Cコントローラアクティブ";
		break;
	case SVI_STS_CMD_INVALID    :  
		outputString = " コマンドが不正です";
		break;
	case SVI_STS_PRM_INVALID    :  
		outputString = " パラメータが不正です";
		break;
	case SVI_STS_SEQ_INVALID    :  
		outputString = " パケットの発行シーケンスが不正です";
		break;
	case SVI_STS_I2C_ACKTIMEOUT :  
		outputString = " I2CでスレーブからのACKを受信できずタイムアウトが発生しました";
		break;
	case SVI_STS_I2C_PRETIMEOUT :  
		outputString = " I2Cでプリタイムアウトが発生しました";
		break;
	case SVI_STS_I2C_POSTTIMEOUT: 
		outputString = " I2Cでポストタイムアウトが発生しました";
		break;
	case SVI_STS_USB_ERROR      :  
		outputString = " USB通信時にエラーが発生しました";
		break;
	case SVI_STS_UPDATE_INVALID :  
		outputString = " モジュールデータが不正です";
		break;
	case SVI_STS_FROMERS_ERROR  :  
		outputString = " フラッシュメモリーの消去に失敗しました";
		break;
	case SVI_STS_FROMWT_ERROR   :  
		outputString = " フラッシュメモリーの書き込みに失敗しました";
		break;
	case SVI_STS_INTERNAL_ERROR :  
		outputString = " 内部エラーが発生しました";
		break;
	case SVI_STS_RESOURCE_ERROR :  
		outputString = " 内部リソースが不足して処理が実行できません";
		break;
	default:
		outputString = "エラーが特定できません";
		break;
	}
	return outputString;
}
