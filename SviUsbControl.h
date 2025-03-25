// SviUsbControl.h: CSviUsbControl クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_)
#define AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "SVI05API.h"

// [15/06/11] Avoid unsafe updating 
#define FPGA_SINGLE_AREA_SIZE (1024*512) // Bytes
#define FX3_SINGLE_AREA_SIZE (1024*512) // Bytes

using namespace std;

//SVIUSB2.0ドライバに対する操作をラップします。
class CSviUsbControl
{
public:
	bool close();
//	void SetSelBoardNo(int no);
//	ULONG ulSelBoardNo;
//	ULONG GetDeviceID(int no);
//	ULONG GetBoardNum();
	DWORD ScanBoard();
//	ULONG ulBoardNum;
//	ULONG ulBoardInfo[4];
	//コンストラクタ
	CSviUsbControl();

	virtual ~CSviUsbControl();

	//SVIドライバをオープンします
	bool open(void);

	//発生したエラーコードを取得します。（エラーコードは初期化されます。)
	DWORD getLastError(void);

	//エラーコードを文字列に変換します。
	CString getLastErrorString(DWORD errorcode);

	//カメラレジスタの設定(サブアドレス指定有り)
	bool SetValue(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord);
	// オープンクローズは外で行う場合
	bool SetValue2(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord);

	//カメラレジスタの取得
	bool GetValue(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord, BOOL bRestart);
	// オープンクローズは外で行う場合
	bool GetValue2(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord, BOOL bRestart);
	// Read Access のみ
	bool OneBlockRead(ULONG ulSlaveAdr, PUCHAR pRcvBuff, ULONG ulLen);

	// SPIROMの値を取得
	bool SetSVMSettingValue(ULONG ulLen, PUCHAR pRcvBuff);
	// SPIROMから値を取得
	bool GetSVMSettingValue(ULONG ulLen ,PUCHAR pRcvBuff);

	// SPIROMにあるFX3データをアップデート
	bool SVMFx3Update(ULONG ulLen ,PUCHAR pRcvBuff);
	// FPGAのUpdateを行います
	bool SVMFPGAUpdate(ULONG ulLen ,PUCHAR pRcvBuff);
	
	// [15/06/11
	bool SVMMultiUpdate(ULONG ulLen ,PUCHAR pRcvBuff);

	// SPIROMにあるFX3データを取得する
	bool SVMFX3BootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);
	// SPIロム内にあるFPGAのブート用データを取得します。
	bool SVMFPGABootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);

	// [15/06/11]
	bool SVMMultiBootMemRead(ULONG ulLen ,PUCHAR pRcvBuff);

	// FX3のバージョン情報を取得
	bool SVMVersionInfo(ULONG ulLen ,PUCHAR pRcvBuff);

	// [17/05/18] Write I2C Initialization Data
	bool WriteInitI2C(ULONG ulLen, PUCHAR pucSendBuf);

	// [17/05/18] Write I2C Initialization Data
	bool ReadInitI2C(ULONG ulLen, PUCHAR pucRcvBuf);
	bool CheckInitI2C();
		
	// [22/02/18] FPGA Register RW
	bool WriteFPGARegister(ULONG addr, ULONG value);
	bool ReadFPGARegister(ULONG addr, PULONG pValue);

private:

	// １ブロック受信
	bool I2CBlockRead(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucRcvBuf, BOOL bWord);

	//エラーチェック単純化（private)
	bool CSviUsbControl::checkLastError(void);

	//リターンコード
	DWORD RC;

	// １ブロック送信
	bool I2CBlockWrite(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucSendBuf, BOOL bWord);

	// SPIWriteコマンド送信
	bool SVMSettingWrite(ULONG ulLen, PUCHAR pucSendBuf);
	// SPIReadコマンド送信
	bool SVMSettingRead(ULONG ulLen, PUCHAR pucRcvBuf);

	// [15/09/02]
	int m_deviceIndex;
	// [18/07/31]
	int m_boardType;
public:
	void SetDeviceIndex(int index){
		m_deviceIndex = index;
	};
	void SetBoardType(int type){
		m_boardType = type;
	};
};

#endif // !defined(AFX_SVIUSBCONTROL_H__19B3D7F6_CEA6_4B17_9A40_CAD728E223C3__INCLUDED_)
