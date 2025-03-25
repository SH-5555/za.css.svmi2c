#include "stdafx.h"
#include "SVMSettingInfo.h"
#include "IniFileControl.h"


SVMSettingInfo::SVMSettingInfo(void)
{
	// 変数初期化
	ckin = 0;			
	ckinDiv = 0;		
	color = 0;			
	bt656 = 0;			
	de = 0;				
	edge = 0;			
	hsync = 0;			
	vsync = 0;		
	csSwap = 0;		
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
	csEndian = 0;		
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
	AppName = "";
	IniFileFullPath = "";

	width = 1280;
	height = 720;
	colorid = 0;
	fps = "30";
	deviceid = 0;
}

SVMSettingInfo::~SVMSettingInfo(void)
{
}

// コピーコンストラクタ
SVMSettingInfo::SVMSettingInfo(const SVMSettingInfo &obj)
{
	ckin = obj.ckin;			
	ckinDiv = obj.ckinDiv;		
	color = obj.color;			
	bt656 = obj.bt656;			
	de = obj.de;				
	edge = obj.edge;			
	hsync = obj.hsync;			
	vsync = obj.vsync;		
	csSwap = obj.csSwap;		
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
	csEndian = obj.csEndian;		
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加

	width = obj.width;
	height = obj.height;
	colorid = obj.colorid;
	fps = obj.fps;
	deviceid = obj.deviceid;

	AppName = obj.AppName;
	IniFileFullPath = obj.IniFileFullPath;
}
/**
	@brief	CKIN Out Select取得
	@return	BYTE;CKIN Out Select設定値
*/
BYTE SVMSettingInfo::GetCkinOutSelect(void)
{
	return ckin;
}
/**
	@brief	CKIN Out Select設定
	@param[in] CKIN Out Select設定値
	@return	なし
*/
void SVMSettingInfo::SetCkinOutSelect(BYTE val)
{
	ckin = val;
}

/**
	@brief	CKIN Out Divide取得
	@return	BYTE;CKIN Out Divide設定値
*/
BYTE SVMSettingInfo::GetCkinOutDivide(void)
{
	return ckinDiv;
}
/**
	@brief	CKIN Out Divide設定
	@param[in] CKIN Out Divide設定値
	@return	なし
*/
void SVMSettingInfo::SetCkinOutDivide(BYTE val)
{
	ckinDiv = val;
}

/**
	@brief	Color Space Select取得
	@return	BYTE;Color Space Select設定値
*/
BYTE SVMSettingInfo::GetColorSpaceSelect(void)
{
	return color;
}
/**
	@brief	Color Space Select設定
	@param[in] Color Space Select設定値
	@return	なし
*/
void SVMSettingInfo::SetColorSpaceSelect(BYTE val)
{
	color = val;
}


/**
	@brief	ITU BT.656 Mode(SAV/EAV)取得
	@return	BYTE;ITU BT.656 Mode(SAV/EAV)設定値
*/
BYTE SVMSettingInfo::GetBT686Mode(void)
{
	return bt656;
}
/**
	@brief	ITU BT.656 Mode(SAV/EAV)設定
	@param[in] ITU BT.656 Mode(SAV/EAV)設定値
	@return	なし
*/
void SVMSettingInfo::SetBT686Mode(BYTE val)
{
	bt656 = val;
}

/**
	@brief	DE Signal Setting取得
	@return	BYTE;DE Signal Setting設定値
*/
BYTE SVMSettingInfo::GetDeSignalSetting(void)
{
	return de;
}
/**
	@brief		DE Signal Setting設定
	@param[in] 	DE Signal Setting設定値
	@return	なし
*/
void SVMSettingInfo::SetDeSignalSetting(BYTE val)
{
	de = val;
}


/**
	@brief	Polarity of Pixel Clock Edge取得
	@return	BYTE;Polarity of Pixel Clock Edge設定値
*/
BYTE SVMSettingInfo::GetPolarityClockEdge(void)
{
	return edge;
}
/**
	@brief	Polarity of Pixel Clock Edge設定
	@param[in] Polarity of Pixel Clock Edge設定値
	@return	なし
*/
void SVMSettingInfo::SetPolarityClockEdge(BYTE val)
{
	edge = val;
}

/**
	@brief	Polarity of H-Sync and DE取得
	@return	BYTE;Polarity of H-Sync and DE設定値
*/
BYTE SVMSettingInfo::GetPolarityHsync(void)
{
	return hsync;
}
/**
	@brief	Polarity of H-Sync and DE設定
	@param[in] Polarity of H-Sync and DE設定値
	@return	なし
*/
void SVMSettingInfo::SetPolarityHsync(BYTE val)
{
	hsync = val;
}

/**
	@brief	Polarity of V-Sync取得
	@return	BYTE;Polarity of V-Sync設定値
*/
BYTE SVMSettingInfo::GetPolarityVsync(void)
{
	return vsync;
}
/**
	@brief	Polarity of V-Sync設定
	@param[in] Polarity of V-Sync設定値
	@return	なし
*/
void SVMSettingInfo::SetPolarityVsync(BYTE val)
{
	vsync = val;
}

/**
	@brief	CS Swap Mode取得
	@return	BYTE;CS Swap Mode設定値
*/
BYTE SVMSettingInfo::GetCSSwapMode(void)
{
	return csSwap;
}
/**
	@brief	CS Swap Mode設定
	@param[in] CS Swap Mode設定値
	@return	なし
*/
void SVMSettingInfo::SetCSSwapMode(BYTE val)
{
	csSwap = val;
}

#if 1 // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加
/**
	@brief	Endian Mode取得
	@return	BYTE;Endian Mode設定値
*/
BYTE SVMSettingInfo::GetEndianMode(void)
{
	return csEndian;
}
/**
	@brief	Endian Mode設定
	@param[in] Endian Mode設定値
	@return	なし
*/
void SVMSettingInfo::SetEndianMode(BYTE val)
{
	csEndian = val;
}
#endif // 2015.04.17 V1.0.1.0 SVM-03U用に1項目追加


int SVMSettingInfo::GetColorGUID(int idx, unsigned char* pGuid, char* name, int nameSize)
{
	if(idx < 0) return -1;

	// Iniファイル名取得
	AppName = AfxGetAppName();
	CString IniFileName = "\\" + AppName + ".ini";
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,Path);
	IniFileName =  Path + IniFileName;
	CIniFileControl iniFile(AppName, IniFileName);

	CString guidString, nameString;

	char buf[128];
	sprintf(buf, "ColorName%d", idx);
	nameString = iniFile.GetString(buf, "");
	sprintf(buf, "ColorGUID%d", idx);
	guidString = iniFile.GetString(buf, "");

	if(nameString == "" || guidString == "") return -2;

	// カンマ区切り -> char
	buf[0] = '\0';
	int bufPos = 0;
	unsigned char guidBuf[64];
	int guidPos = 0;
	for(int i=0; i<strlen(guidString) + 1; i++){
		char a = guidString[i];
		if(a == ',' || a == '\0'){
//			guidBuf[guidPos++] = (unsigned char) atoi(buf); // dec
			if(buf[0] == '0' && buf[1] == 'x'){
				guidBuf[guidPos++] = (unsigned char) strtol(buf+2, NULL, 16); // hex
			}else{
				guidBuf[guidPos++] = (unsigned char) strtol(buf, NULL, 16); // hex
			}
			bufPos = 0;
		}else{
			buf[bufPos++] = a;
			buf[bufPos]   = '\0';
		}
	}

	if(guidPos != 16) return -3;

	int i;
	for(i=0; i<16; i++) {
		pGuid[i] = guidBuf[i];
	}
	strncpy(name, nameString, nameSize);

	return 0;
}

/**
	@brief	iniファイルのフルパス取得
	@retval TRUE 成功
	@retval FALSE 失敗
*/
BOOL SVMSettingInfo::GetIniFilePath(void)
{
	//.svmファイル内容を適用する
	AppName = AfxGetAppName();
	IniFileFullPath = "\\" + AppName + ".svm";

	GetCurrentDirectory(MAX_PATH,AppPath);

	IniFileFullPath =  AppPath + IniFileFullPath;

	return TRUE;

}
/**
	@brief	Iniファイルの値をクラス変数に設定
	@retval TRUE 成功
	@retval FALSE 失敗
*/
BOOL SVMSettingInfo::GetIniFileData(void)
{
	// Iniファイル名取得
	GetIniFilePath();

	// Iniファイルクラス作成
	CIniFileControl iniFile(AppName, IniFileFullPath);

	// Iniファイルから値取得
	//	CKIN Out Select
	ckin = iniFile.GetInt(INI_KEY_CKIN,DEFAULT_CKIN);
	//	CKIN Out Divide
	ckinDiv = iniFile.GetInt(INI_KEY_CKINDIV,DEFAULT_CKINDIV);
	//	Color Space Select
	color = iniFile.GetInt(INI_KEY_COLOR,DEFAULT_COLOR);
	//	ITU BT.656 Mode(SAV/EAV)
	bt656 = iniFile.GetInt(INI_KEY_BT656,DEFAULT_BT656);
	//	Polarity of Pixel Clock Edge 
	edge = iniFile.GetInt(INI_KEY_EDGE,DEFAULT_EDGE);
	//	Polarity of H-Sync and DE
	hsync = iniFile.GetInt(INI_KEY_HSYNC,DEFAULT_HSYNC);
	//	Polarity of V-Sync
	vsync = iniFile.GetInt(INI_KEY_VSYNC,DEFAULT_VSYNC);
	//	CS Swap Mode
	csSwap = iniFile.GetInt(INI_KEY_CSSWAP,DEFAULT_CSSWAP);
#if 1 // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え
	csEndian = iniFile.GetInt(INI_KEY_ENDIAN,DEFAULT_ENDIAN);
#endif // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え

	width	 = iniFile.GetInt(INI_KEY_WIDTH, DEFAULT_WIDTH);
	height	 = iniFile.GetInt(INI_KEY_HEIGHT, DEFAULT_HEIGHT);
	fps		 = iniFile.GetString(INI_KEY_FPS, DEFAULT_FPS);
	colorid	 = iniFile.GetInt(INI_KEY_COLORGUID, DEFAULT_COLORGUID);

	return TRUE;
}

/**
	@brief	クラス変数をIniファイルに保存
	@retval TRUE 成功
	@retval FALSE 失敗
*/
BOOL SVMSettingInfo::SetIniFileData(void)
{
	// Iniファイル名取得
	GetIniFilePath();

	// Iniファイルクラス作成
	CIniFileControl iniFile(AppName,IniFileFullPath);

	// Iniファイル値設定
	//	CKIN Out Select
	iniFile.SetInt(INI_KEY_CKIN,ckin);
	//	CKIN Out Divide
	iniFile.SetInt(INI_KEY_CKINDIV,ckinDiv);
	//	Color Space Select
	iniFile.SetInt(INI_KEY_COLOR,color);
	//	ITU BT.656 Mode(SAV/EAV)
	iniFile.SetInt(INI_KEY_BT656,bt656);
	//	Polarity of Pixel Clock Edge 
	iniFile.SetInt(INI_KEY_EDGE,edge);
	//	Polarity of H-Sync and DE
	iniFile.SetInt(INI_KEY_HSYNC,hsync);
	//	Polarity of V-Sync
	iniFile.SetInt(INI_KEY_VSYNC,vsync);
	//	CS Swap Mode
	iniFile.SetInt(INI_KEY_CSSWAP,csSwap);
#if 1 // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え
	//	Endian Mode
	iniFile.SetInt(INI_KEY_ENDIAN,csEndian);
#endif // 2015.04.17 V1.0.1.0 SVM-03/03U切り替え

	iniFile.SetInt(INI_KEY_WIDTH, width);
	iniFile.SetInt(INI_KEY_HEIGHT, height);
	iniFile.SetString(INI_KEY_FPS, fps);
	iniFile.SetInt(INI_KEY_COLORGUID, colorid);

	return TRUE;
}