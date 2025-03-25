#include "stdafx.h"
#include "SVMSettingInfo.h"
#include "IniFileControl.h"


SVMSettingInfo::SVMSettingInfo(void)
{
	// �ϐ�������
	ckin = 0;			
	ckinDiv = 0;		
	color = 0;			
	bt656 = 0;			
	de = 0;				
	edge = 0;			
	hsync = 0;			
	vsync = 0;		
	csSwap = 0;		
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�
	csEndian = 0;		
#endif // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�
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

// �R�s�[�R���X�g���N�^
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
#if 1 // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�
	csEndian = obj.csEndian;		
#endif // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�

	width = obj.width;
	height = obj.height;
	colorid = obj.colorid;
	fps = obj.fps;
	deviceid = obj.deviceid;

	AppName = obj.AppName;
	IniFileFullPath = obj.IniFileFullPath;
}
/**
	@brief	CKIN Out Select�擾
	@return	BYTE;CKIN Out Select�ݒ�l
*/
BYTE SVMSettingInfo::GetCkinOutSelect(void)
{
	return ckin;
}
/**
	@brief	CKIN Out Select�ݒ�
	@param[in] CKIN Out Select�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetCkinOutSelect(BYTE val)
{
	ckin = val;
}

/**
	@brief	CKIN Out Divide�擾
	@return	BYTE;CKIN Out Divide�ݒ�l
*/
BYTE SVMSettingInfo::GetCkinOutDivide(void)
{
	return ckinDiv;
}
/**
	@brief	CKIN Out Divide�ݒ�
	@param[in] CKIN Out Divide�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetCkinOutDivide(BYTE val)
{
	ckinDiv = val;
}

/**
	@brief	Color Space Select�擾
	@return	BYTE;Color Space Select�ݒ�l
*/
BYTE SVMSettingInfo::GetColorSpaceSelect(void)
{
	return color;
}
/**
	@brief	Color Space Select�ݒ�
	@param[in] Color Space Select�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetColorSpaceSelect(BYTE val)
{
	color = val;
}


/**
	@brief	ITU BT.656 Mode(SAV/EAV)�擾
	@return	BYTE;ITU BT.656 Mode(SAV/EAV)�ݒ�l
*/
BYTE SVMSettingInfo::GetBT686Mode(void)
{
	return bt656;
}
/**
	@brief	ITU BT.656 Mode(SAV/EAV)�ݒ�
	@param[in] ITU BT.656 Mode(SAV/EAV)�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetBT686Mode(BYTE val)
{
	bt656 = val;
}

/**
	@brief	DE Signal Setting�擾
	@return	BYTE;DE Signal Setting�ݒ�l
*/
BYTE SVMSettingInfo::GetDeSignalSetting(void)
{
	return de;
}
/**
	@brief		DE Signal Setting�ݒ�
	@param[in] 	DE Signal Setting�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetDeSignalSetting(BYTE val)
{
	de = val;
}


/**
	@brief	Polarity of Pixel Clock Edge�擾
	@return	BYTE;Polarity of Pixel Clock Edge�ݒ�l
*/
BYTE SVMSettingInfo::GetPolarityClockEdge(void)
{
	return edge;
}
/**
	@brief	Polarity of Pixel Clock Edge�ݒ�
	@param[in] Polarity of Pixel Clock Edge�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetPolarityClockEdge(BYTE val)
{
	edge = val;
}

/**
	@brief	Polarity of H-Sync and DE�擾
	@return	BYTE;Polarity of H-Sync and DE�ݒ�l
*/
BYTE SVMSettingInfo::GetPolarityHsync(void)
{
	return hsync;
}
/**
	@brief	Polarity of H-Sync and DE�ݒ�
	@param[in] Polarity of H-Sync and DE�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetPolarityHsync(BYTE val)
{
	hsync = val;
}

/**
	@brief	Polarity of V-Sync�擾
	@return	BYTE;Polarity of V-Sync�ݒ�l
*/
BYTE SVMSettingInfo::GetPolarityVsync(void)
{
	return vsync;
}
/**
	@brief	Polarity of V-Sync�ݒ�
	@param[in] Polarity of V-Sync�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetPolarityVsync(BYTE val)
{
	vsync = val;
}

/**
	@brief	CS Swap Mode�擾
	@return	BYTE;CS Swap Mode�ݒ�l
*/
BYTE SVMSettingInfo::GetCSSwapMode(void)
{
	return csSwap;
}
/**
	@brief	CS Swap Mode�ݒ�
	@param[in] CS Swap Mode�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetCSSwapMode(BYTE val)
{
	csSwap = val;
}

#if 1 // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�
/**
	@brief	Endian Mode�擾
	@return	BYTE;Endian Mode�ݒ�l
*/
BYTE SVMSettingInfo::GetEndianMode(void)
{
	return csEndian;
}
/**
	@brief	Endian Mode�ݒ�
	@param[in] Endian Mode�ݒ�l
	@return	�Ȃ�
*/
void SVMSettingInfo::SetEndianMode(BYTE val)
{
	csEndian = val;
}
#endif // 2015.04.17 V1.0.1.0 SVM-03U�p��1���ڒǉ�


int SVMSettingInfo::GetColorGUID(int idx, unsigned char* pGuid, char* name, int nameSize)
{
	if(idx < 0) return -1;

	// Ini�t�@�C�����擾
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

	// �J���}��؂� -> char
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
	@brief	ini�t�@�C���̃t���p�X�擾
	@retval TRUE ����
	@retval FALSE ���s
*/
BOOL SVMSettingInfo::GetIniFilePath(void)
{
	//.svm�t�@�C�����e��K�p����
	AppName = AfxGetAppName();
	IniFileFullPath = "\\" + AppName + ".svm";

	GetCurrentDirectory(MAX_PATH,AppPath);

	IniFileFullPath =  AppPath + IniFileFullPath;

	return TRUE;

}
/**
	@brief	Ini�t�@�C���̒l���N���X�ϐ��ɐݒ�
	@retval TRUE ����
	@retval FALSE ���s
*/
BOOL SVMSettingInfo::GetIniFileData(void)
{
	// Ini�t�@�C�����擾
	GetIniFilePath();

	// Ini�t�@�C���N���X�쐬
	CIniFileControl iniFile(AppName, IniFileFullPath);

	// Ini�t�@�C������l�擾
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
#if 1 // 2015.04.17 V1.0.1.0 SVM-03/03U�؂�ւ�
	csEndian = iniFile.GetInt(INI_KEY_ENDIAN,DEFAULT_ENDIAN);
#endif // 2015.04.17 V1.0.1.0 SVM-03/03U�؂�ւ�

	width	 = iniFile.GetInt(INI_KEY_WIDTH, DEFAULT_WIDTH);
	height	 = iniFile.GetInt(INI_KEY_HEIGHT, DEFAULT_HEIGHT);
	fps		 = iniFile.GetString(INI_KEY_FPS, DEFAULT_FPS);
	colorid	 = iniFile.GetInt(INI_KEY_COLORGUID, DEFAULT_COLORGUID);

	return TRUE;
}

/**
	@brief	�N���X�ϐ���Ini�t�@�C���ɕۑ�
	@retval TRUE ����
	@retval FALSE ���s
*/
BOOL SVMSettingInfo::SetIniFileData(void)
{
	// Ini�t�@�C�����擾
	GetIniFilePath();

	// Ini�t�@�C���N���X�쐬
	CIniFileControl iniFile(AppName,IniFileFullPath);

	// Ini�t�@�C���l�ݒ�
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
#if 1 // 2015.04.17 V1.0.1.0 SVM-03/03U�؂�ւ�
	//	Endian Mode
	iniFile.SetInt(INI_KEY_ENDIAN,csEndian);
#endif // 2015.04.17 V1.0.1.0 SVM-03/03U�؂�ւ�

	iniFile.SetInt(INI_KEY_WIDTH, width);
	iniFile.SetInt(INI_KEY_HEIGHT, height);
	iniFile.SetString(INI_KEY_FPS, fps);
	iniFile.SetInt(INI_KEY_COLORGUID, colorid);

	return TRUE;
}