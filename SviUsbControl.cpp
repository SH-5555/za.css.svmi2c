// SviUsbControl.cpp: CSviUsbControl クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SviUsbControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CSviUsbControl::CSviUsbControl()
{
	// メンバ変数初期化
	RC=0;
	m_deviceIndex = 0;

	// SVIライブラリー初期化
	SVI05API_Init();
	// 接続SVI-03ボード情報取得
//	ScanBoard();
}

CSviUsbControl::~CSviUsbControl()
{
	//SVIドライバ・クローズ処理
	SVI05API_Close(SVI05API_APP_WHO_CTL);
	//SVIライブラリー終了処理
	SVI05API_End();
}
//発生したエラーコードを取得します。（エラーコードは初期化されます。)
DWORD CSviUsbControl::getLastError(void)
{
	DWORD outputRC = RC;
	RC = 0;
	return outputRC;
}

//エラーコードを文字列に変換します。
CString CSviUsbControl::getLastErrorString(DWORD errorcode)
{
	CString outputString;
	switch(errorcode)
	{
	case SVI05API_RET_NORMAL:
		outputString = "正常終了";
		break;
	case SVI05API_RET_ERROR_DEVOPEN:
		outputString = "SVI専用USB2.0ドライバをオープンできません";
		break;
	case SVI05API_RET_ERROR_MULTIOPEN:
		outputString = "同じアプリケーションからは二重にオープンできません";
		break;
	case SVI05API_RET_ERROR_PARAMETER:
		outputString = "引数に間違いがあります";
		break;
	case SVI05API_RET_ERROR_NOOPEN:
		outputString = "ドライバがオープンされていません。";
		break;
	case SVI05API_RET_ERROR_COM:
		outputString = "SVIUSB20_RET_ERROR_COM";
		break;
	case SVI05API_RET_ERROR_NOIDLE:
		outputString = "SVIUSB20_RET_ERROR_NOIDLE";
		break;
	case SVI05API_RET_ERROR_FMUPDATE_T:
		outputString = "SVIUSB20_RET_ERROR_FMUPDATE_T";
		break;
	case SVI05API_RET_ERROR_FPUPDATE_T:
		outputString = "SVIUSB20_RET_ERROR_FPUPDATE_T";
		break;
	case SVI05API_RET_ERROR_GSTS2_T:
		outputString = "SVIUSB20_RET_ERROR_GSTS2_T";
		break;
	case SVI05API_RET_ERROR_MDATA_T:
		outputString = "SVIUSB20_RET_ERROR_MDATA_T";
		break;
	case SVI05API_RET_ERROR_SVI:
		outputString = "SVIUSB20_RET_ERROR_SVI";
		break;

	default:
		outputString.Format("Win32APIエラー：%x",errorcode);
		break;
	}

	return outputString;
}

//エラーチェック単純化（private)
bool CSviUsbControl::checkLastError(void)
{
	if(RC != SVI05API_RET_NORMAL)
	{
		TRACE(getLastErrorString(RC));
		return false;
	}
	return true;
}

//SVIドライバをオープンします
bool CSviUsbControl::open()
{
	// コントロールモードでオープン
	// (SVI05API_OpenEx: SVO-03 にも対応 / SVI05API_Open: SVO-03 非対応)
	RC = SVI05API_OpenEx(SVI05API_APP_WHO_CTL, m_deviceIndex, m_boardType);
	return checkLastError();
}

// カメラのレジスタへ設定
bool CSviUsbControl::SetValue(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord)
{
	bool rf = false;
	// デバイスドライバオープン
	if(!open()){
		goto svi_close;
	}

	if(/*IS_SVM03() && */ulSlaveAdr == 0x08){
		RC = SVI05API_SPIFpgaWrite(0x08, 0x99, ulSubAdr, ulLen, pRcvBuff);
	}else if(ulSlaveAdr == 0x00){ // [17/05/29] FX3 Register
		RC = SVI05API_SPIFpgaWrite(0x0A, 0x99, ulSubAdr, ulLen, pRcvBuff);
	}else{
		if(!I2CBlockWrite(ulSlaveAdr, ulSubAdr, ulLen, pRcvBuff, bWord))
			goto svi_close;
	}

	rf = true;

svi_close:
	// デバイスドライバクローズ
	RC = SVI05API_Close(SVI05API_APP_WHO_CTL);
	checkLastError();
	return rf;
}

// カメラのレジスタへ設定
bool CSviUsbControl::SetValue2(ULONG ulSlaveAdr,ULONG ulSubAdr,PUCHAR pRcvBuff,ULONG ulLen, BOOL bWord)
{
	if(/*IS_SVM03() && */ulSlaveAdr == 0x08){
		RC = SVI05API_SPIFpgaWrite(0x08, 0x99, ulSubAdr, ulLen, pRcvBuff);
	}else{
		if(I2CBlockWrite(ulSlaveAdr, ulSubAdr, ulLen, pRcvBuff, bWord) != SVI05API_RET_NORMAL) return false;
	}

	return true;
}

bool CSviUsbControl::OneBlockRead(ULONG ulSlaveAdr, PUCHAR pRcvBuff, ULONG ulLen)
{
	if(SVI05API_I2COneBlockRead( ulSlaveAdr, ulLen, 0, pRcvBuff) != SVI05API_RET_NORMAL) return false;

	return true;
}
// [17/02/15] restartCondition
bool CSviUsbControl::GetValue(ULONG ulSlaveAdr, ULONG ulSubAdr, PUCHAR pRcvBuff, ULONG ulLen, BOOL bWord, BOOL bRestart)
{

	bool rf = false;
	// デバイスドライバオープン
	if(!open()){
		goto svi_close;
	}

	if(/*IS_SVM03() && */ulSlaveAdr == 0x08){
		RC = SVI05API_SPIFpgaRead(0x07,0x99,ulSubAdr,ulLen,pRcvBuff);
	}else if(ulSlaveAdr == 0x00){ // [17/05/29] FX3 Register
		RC = SVI05API_SPIFpgaRead(0x09,0x99,ulSubAdr,ulLen,pRcvBuff);
	}else{
		if(bRestart){
			if((RC = I2CBlockRead(ulSlaveAdr, ulSubAdr, ulLen, pRcvBuff, bWord)) != SVI05API_RET_NORMAL){
				goto svi_close;
			}
		}else{
			// Write -> Read
			unsigned char buf[4];
			if(bWord){
				buf[0] = ulSubAdr >> 8;
				buf[1] = ulSubAdr;
				if((RC = SVI05API_I2COneBlockWrite(ulSlaveAdr, 2, 0, buf)) != SVI05API_RET_NORMAL){
					goto svi_close;
				}
			}
			else{
				buf[0] = ulSubAdr;
				if((RC = SVI05API_I2COneBlockWrite(ulSlaveAdr, 1, 0, buf)) != SVI05API_RET_NORMAL){
					goto svi_close;
				}
			}
			if((RC = SVI05API_I2COneBlockRead( ulSlaveAdr, ulLen, 0, pRcvBuff)) != SVI05API_RET_NORMAL){
				goto svi_close;
			}
		}
	}

	rf = true;
svi_close:
	// デバイスドライバクローズ
	RC = SVI05API_Close(SVI05API_APP_WHO_CTL);
	checkLastError();
	return rf;
}

bool CSviUsbControl::GetValue2(ULONG ulSlaveAdr, ULONG ulSubAdr, PUCHAR pRcvBuff, ULONG ulLen, BOOL bWord, BOOL bRestart)
{

	if(/*IS_SVM03() && */ulSlaveAdr == 0x08){
		RC = SVI05API_SPIFpgaRead(0x07,0x99,ulSubAdr,ulLen,pRcvBuff);
	}else if(ulSlaveAdr == 0x00){ // [17/05/29] FX3 Register
		RC = SVI05API_SPIFpgaRead(0x09,0x99,ulSubAdr,ulLen,pRcvBuff);
	}else{
		if(bRestart){
			if((RC = I2CBlockRead(ulSlaveAdr, ulSubAdr, ulLen, pRcvBuff, bWord)) != SVI05API_RET_NORMAL){
				return false;
			}
		}else{
			// Write -> Read
			unsigned char buf[4];
			if(bWord){
				buf[0] = ulSubAdr >> 8;
				buf[1] = ulSubAdr;
				if((RC = SVI05API_I2COneBlockWrite(ulSlaveAdr, 2, 0, buf)) != SVI05API_RET_NORMAL){
					return false;
				}
			}
			else{
				buf[0] = ulSubAdr;
				if((RC = SVI05API_I2COneBlockWrite(ulSlaveAdr, 1, 0, buf)) != SVI05API_RET_NORMAL){
					return false;
				}
			}
			if((RC = SVI05API_I2COneBlockRead( ulSlaveAdr, ulLen, 0, pRcvBuff)) != SVI05API_RET_NORMAL){
				return false;
			}
		}
	}

	return true;
}
bool CSviUsbControl::I2CBlockWrite(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucSendBuf, BOOL bWord)
{
	// debug
	/*
	FILE* fp = fopen("c:\\project\\test.txt", "at+");
	if(fp){
		if(ulLen == 2) fprintf(fp, "%02X, %02X, %02X, %02X\n", ulSlaveAdr, ulSubAdr, pucSendBuf[0], pucSendBuf[1]);
		else if(ulLen == 1) fprintf(fp, "%02X, %02X, %02X\n", ulSlaveAdr, ulSubAdr, pucSendBuf[0]);
		fclose(fp);
	}*/
	

	RC = SVI05API_I2CBlockWrite( ulSlaveAdr, ulSubAdr, ulLen, pucSendBuf, bWord);
	if(0){
		char buf[64]; sprintf(buf, "Ret = %08X", RC); MessageBox(NULL, buf, "", MB_OK);
	}
	return checkLastError();
}

bool CSviUsbControl::I2CBlockRead(ULONG ulSlaveAdr, ULONG ulSubAdr, ULONG ulLen, PUCHAR pucRcvBuf, BOOL bWord)
{
	RC = SVI05API_I2CBlockRead( ulSlaveAdr, ulSubAdr, ulLen, pucRcvBuf, bWord);
	return checkLastError();
}
/*
DWORD CSviUsbControl::ScanBoard()
{
	// 接続SVI-03ボード情報取得
	ulBoardNum = 0;
	return SVI05API_RET_NORMAL;
}


ULONG CSviUsbControl::GetBoardNum()
{
	return ulBoardNum;
}

ULONG CSviUsbControl::GetDeviceID(int no)
{
	return ulBoardInfo[no];
}

void CSviUsbControl::SetSelBoardNo(int no)
{
	ulSelBoardNo = ulBoardInfo[no];
}
*/

bool CSviUsbControl::close()
{
	//コントロールモードでクローズ
	RC = SVI05API_Close(SVI05API_APP_WHO_CTL);
	return checkLastError();
}

// SPIROMへ値を設定する
bool CSviUsbControl::SetSVMSettingValue(ULONG ulLen, PUCHAR pRcvBuff)
{
	bool rf = false;
	// デバイスドライバオープン
	if(!open())
		goto svi_close;
	if(!SVMSettingWrite(ulLen, pRcvBuff))
		goto svi_close;

	rf = true;

svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

// SPIROMから値を取得する
bool CSviUsbControl::GetSVMSettingValue(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	if(!SVMSettingRead(ulLen, pRcvBuff))
		goto svi_close;

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

// After v1.3.2
#define ENABLE_UB3_01 1

// [17/05/18] Write I2C Initialization Data
bool CSviUsbControl::WriteInitI2C(ULONG ulLen, PUCHAR pucSendBuf)
{
	if(IS_UB3_01() && ENABLE_UB3_01){ // [15/08/04]
//		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x060000, ulLen, pucSendBuf);
		RC = SVI05API_SVMSPIBootMemUpdate(0x060000, ulLen, pucSendBuf);
	}
	else if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x80}; // MSB First
		buf[3] = 0x01; // Enable SPI-ROM Write
		SetValue2(0x08, 0x48000FFC, buf, 4, TRUE);

//		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0xFE0000, ulLen, pucSendBuf);
		RC = SVI05API_SVMSPIBootMemUpdate(0xFE0000, ulLen, pucSendBuf);
		
		buf[3] = 0x00; // Disable SPI-ROM Write
		SetValue2(0x08, 0x48000FFC, buf, 4, TRUE);
	}
	else if(IS_SVM03U()){ 
//		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x1E0000, ulLen, pucSendBuf);
		RC = SVI05API_SVMSPIBootMemUpdate(0x1E0000, ulLen, pucSendBuf);
	}
	else{
//		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x1E0000, ulLen, pucSendBuf);
		RC = SVI05API_SVMSPIBootMemUpdate(0x1E0000, ulLen, pucSendBuf);
	}
	return checkLastError();
}

// [17/05/19] Check whether there's I2c initialization data
bool CSviUsbControl::CheckInitI2C()
{
	UCHAR buf[256];
	if(IS_UB3_01() && ENABLE_UB3_01){ // [15/08/04]
		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x060000, 16, buf);
	}
	else if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0xFE0000, 16, buf);
	}
	else if(IS_SVM03U()){ 
		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x1E0000, 16, buf);
	}else{
		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x1E0000, 16, buf);
	}
	return (buf[0] == 0x55);
}

// [17/05/18] Write I2C Initialization Data
// -> Obsoleted
bool CSviUsbControl::ReadInitI2C(ULONG ulLen, PUCHAR pucRcvBuf)
{
	if(IS_UB3_01() && ENABLE_UB3_01){
//		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x060000, ulLen, pucRcvBuf);
		RC = SVI05API_SVMSPIBootMemRead(0x060000, ulLen, pucRcvBuf);
	}
	else if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
//		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0xFE0000, ulLen, pucRcvBuf);
		RC = SVI05API_SVMSPIBootMemRead(0xFE0000, ulLen, pucRcvBuf);
	}
	else if(IS_SVM03U()){ 
//		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x1E0000, ulLen, pucRcvBuf);
		RC = SVI05API_SVMSPIBootMemRead(0x1E0000, ulLen, pucRcvBuf);
	}else{
//		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x1E0000, ulLen, pucRcvBuf);
		RC = SVI05API_SVMSPIBootMemRead(0x1E0000, ulLen, pucRcvBuf);
	} 
	return checkLastError();
}

// SPIWriteコマンド送信
bool CSviUsbControl::SVMSettingWrite(ULONG ulLen, PUCHAR pucSendBuf)
{
	/*
	if(IS_UB3_01()){ // [15/08/04]
		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x70000, ulLen, pucSendBuf);
	}
	else if(IS_SVM03U()){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		RC = SVI05API_SVM03USettingWrite( ulLen, pucSendBuf);
	}
	else{
		RC = SVI05API_SVMSettingWrite( ulLen, pucSendBuf);
	}
	*/
	if(IS_UB3_01() && ENABLE_UB3_01){ // [15/08/04]
		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x070000, ulLen, pucSendBuf);
	}
	else if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){ // [18/09/25] add condition
		unsigned char buf[4] = {0x00, 0x00, 0x00, 0x80}; // MSB First
		buf[3] = 0x01; // Enable SPI-ROM Write
		SetValue2(0x08, 0x48000FFC, buf, 4, TRUE);

		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0xFF0000, ulLen, pucSendBuf);

		buf[3] = 0x00; // Disable SPI-ROM Write
		SetValue2(0x08, 0x48000FFC, buf, 4, TRUE);
	}
	else if(IS_SVM03U()){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x1F0000, ulLen, pucSendBuf);
	}
	else{
		RC = SVI05API_SPIWrite(SVM_FX3CMD_SPIWRITE, SVM_SSID_SPI, 0x1F0000, ulLen, pucSendBuf);
	}
	return checkLastError();
}
// SPIReadコマンド送信
// [18/10/19] Fixed for USB2.0 compatibility
bool CSviUsbControl::SVMSettingRead(ULONG ulLen, PUCHAR pucRcvBuf)
{
	unsigned long baseAddr = 0x1F0000;
	if(IS_UB3_01() && ENABLE_UB3_01){ // [15/08/04]
		baseAddr = 0x070000;
	}
	else if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){ // [18/09/25] add condition
		baseAddr = 0xFF0000;
	}
	else if(IS_SVM03U()){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		baseAddr = 0x1F0000;
//		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, 0x1F0000, ulLen, pucRcvBuf);
	}else{
		baseAddr = 0x1F0000;
		
		//char buf[64]; sprintf(buf, "Err = %X", RC); MessageBoxA(NULL, buf, "", MB_OK);
	} // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応


	PUCHAR p = pucRcvBuf;
	while(ulLen){
		ULONG sz = 256;
		if(sz > ulLen) sz = ulLen;

		RC = SVI05API_SPIRead(SVM_FX3CMD_SPIREAD, SVM_SSID_SPI, baseAddr, sz, p);

		baseAddr += sz;
		p += sz;
		ulLen -= sz;
	};

	return checkLastError();
}

// Fx3Updateを行います
bool CSviUsbControl::SVMFx3Update(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;

	if(IS_UB3_01()){ // [15/08/04]
		MessageBox(NULL, "Not inplemented yet.", "Error", MB_OK);
		return false;
	}
	
	if(0){
		char buf[128];
		sprintf(buf, "FX3: %d", ulLen);
		MessageBox(NULL, buf, "", MB_OK);
		return false;
	
		if(ulLen > FX3_SINGLE_AREA_SIZE) return false;
	}

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	if(0){ // [16/05/20] Test Mode (update primary FX3)
		MessageBox(NULL, "これはデバッグモードです。Primary 領域の FX3 をアップデートします。", "", MB_OK);
		if(!SVI05API_SVMFX3Update(ulLen, pRcvBuff))
			goto svi_close;
	}else{

		if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){ // [16/07/08]
			// (Update Main FX3)
			//if(!SVI05API_Update(0x300000, ulLen, pRcvBuff))
			//	goto svi_close;

			// [18/07/26] Update Sub FX3
			if(!SVI05API_Update(0x2C0000, ulLen, pRcvBuff))
				goto svi_close;
		}else if(IS_SVM03U() && strcmp(g_boardName, "SVO-03 (HDMI-UVC)") != 0){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
			if(!SVI05API_SVM03UFX3Update(ulLen, pRcvBuff))
				goto svi_close;
		}else{
			if(!SVI05API_SVMFX3Update(ulLen, pRcvBuff))
				goto svi_close;
		}
	}


	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

// SPIロム内にあるFX3のブート用データを取得します。
bool CSviUsbControl::SVMFX3BootMemRead(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){ // [16/07/08]
		// (Update Main FX3)
		//if(!SVI05API_SVMSPIBootMemRead(0x300000, ulLen, pRcvBuff))
		//	goto svi_close;
		// [18/07/26] Update Sub FX3
		if(!SVI05API_SVMSPIBootMemRead(0x2C0000, ulLen, pRcvBuff))
			goto svi_close;
	}
	else if(IS_SVM03U() && strcmp(g_boardName, "SVO-03 (HDMI-UVC)") != 0){// 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		if(!SVI05API_SVM03UFX3BootMemRead(ulLen, pRcvBuff))
			goto svi_close;
	}else{
		if(!SVI05API_SVMFX3BootMemRead(ulLen, pRcvBuff))
			goto svi_close;
	}


	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

// FPGAのUpdateを行います
bool CSviUsbControl::SVMFPGAUpdate(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;
	
	if(IS_UB3_01()){ // [15/08/04]
		MessageBox(NULL, "Not inplemented yet.", "Error", MB_OK);
		return false;
	}

	if(0){
		char buf[128];
		sprintf(buf, "FPGA: %d", ulLen);
		MessageBox(NULL, buf, "", MB_OK);
		return false;
	}

	if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
		if(ulLen > 5*FPGA_SINGLE_AREA_SIZE) {
			MessageBox(NULL, "Too large size!", "Error", MB_OK);
			return false;
		}
	}else{
		if(ulLen > FPGA_SINGLE_AREA_SIZE) {
			MessageBox(NULL, "Too large size!", "Error", MB_OK);
			return false;
		}
	}

	// デバイスドライバオープン
	if(!open())
		goto svi_close;
	
	if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
		if(!SVI05API_SVMSPIBootMemUpdate(0x340000, ulLen, pRcvBuff)){
			goto svi_close;
		}
	}
	else if(IS_SVM03U() && strcmp(g_boardName, "SVM-03W") != 0 && strcmp(g_boardName, "SVM-03W-MIPI") != 0){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		if(!SVI05API_SVM03UFPGAUpdate(ulLen, pRcvBuff)) // latter
			goto svi_close;
	}else{
		if(!SVI05API_SVMFPGAUpdate(ulLen, pRcvBuff)) // former
			goto svi_close;
	}

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}


// SPIロム内にあるFPGAのブート用データを取得します。
bool CSviUsbControl::SVMFPGABootMemRead(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;


	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	
	if(IS_ARTIX_UPDATER() || IS_SVI09() || IS_SVO_MIPI_HDMI()){
		if(!SVI05API_SVMSPIBootMemRead(0x340000, ulLen, pRcvBuff)){
			goto svi_close;
		}
	}
	else if(IS_SVM03U() && strcmp(g_boardName, "SVM-03W") != 0 && strcmp(g_boardName, "SVM-03W-MIPI") != 0){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		if(!SVI05API_SVM03UFPGABootMemRead(ulLen, pRcvBuff)) // latter
			goto svi_close;
	}else{
		if(!SVI05API_SVMFPGABootMemRead(ulLen, pRcvBuff))
			goto svi_close;
	}

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

// FPGAのUpdateを行います
bool CSviUsbControl::SVMMultiUpdate(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;
	
	if(IS_UB3_01()){ // [15/08/04]
		MessageBox(NULL, "Not inplemented yet.", "Error", MB_OK);
		return false;
	}

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	/*
	if(IS_SVM03U()){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		if(!SVI05API_SVM03UFPGAUpdate(ulLen, pRcvBuff))
			goto svi_close;
	}else{
		if(!SVI05API_SVMFPGAUpdate(ulLen, pRcvBuff))
			goto svi_close;
	}
	*/
	// [15/05/26] Multi-boot
	if(!SVI05API_SVMFPGAUpdate(ulLen, pRcvBuff))
		goto svi_close;

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}
// SPIロム内にあるFPGAのブート用データを取得します。
bool CSviUsbControl::SVMMultiBootMemRead(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	/*
	if(IS_SVM03U()){ // 2015.04.16 V1.0.1.0 SVM-03,SVM-03U混在対応
		if(!SVI05API_SVM03UFPGABootMemRead(ulLen, pRcvBuff))
			goto svi_close;
	}else{
		if(!SVI05API_SVMFPGABootMemRead(ulLen, pRcvBuff))
			goto svi_close;
	}
	*/
	// [15/05/26] Multi-boot
	if(!SVI05API_SVMFPGABootMemRead(ulLen, pRcvBuff))
		goto svi_close;

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}


// Fx3VersionInfoを取得します。
// [18/10/19] This function failed when SDK version = 1.3.4
bool CSviUsbControl::SVMVersionInfo(ULONG ulLen ,PUCHAR pRcvBuff)
{
	bool rf = false;

	// デバイスドライバオープン
	if(!open())
		goto svi_close;

	if(!SVI05API_SVMVersionInfo(ulLen, pRcvBuff))
		goto svi_close;

	rf = true;
svi_close:
	// デバイスドライバクローズ
	close();
	return rf;
}

bool CSviUsbControl::WriteFPGARegister(ULONG addr, ULONG value)
{
	BYTE buf[4];
	buf[0] = value >> 24;
	buf[1] = value >> 16;
	buf[2] = value >> 8;
	buf[3] = value;
	return SetValue(0x08, addr, buf, 4, FALSE);
}

bool CSviUsbControl::ReadFPGARegister(ULONG addr, PULONG pValue)
{
	BYTE buf[4] = {0};
	bool ret = GetValue(0x08, addr, buf, 4, FALSE, FALSE);
	*pValue = ((ULONG)buf[0] << 24) | ((ULONG)buf[1] << 16) | ((ULONG)buf[2] << 8) | ((ULONG)buf[3]);

	return ret;
}
