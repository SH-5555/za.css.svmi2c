#include "stdafx.h"
#include "SettingDataManager.h"
#include "SVMSettingInfo.h"
#include "IniFileControl.h"

CSettingDataManager::CSettingDataManager(void)
{
	// Initialize
	int i;
	for(i=0; i<sizeof(m_data); i++){
		m_data[i] = 0;
	}
}

CSettingDataManager::~CSettingDataManager(void)
{

}

void CSettingDataManager::SetToDefault(void)
{
	int i;
	for(i=0; i<sizeof(m_data); i++){
		m_data[i] = 0;
	}
	int idx = 0;

	// first 32 bytes
	/*
	m_data[idx++] = (SVMSettingInfoID::CKIN);
	m_data[idx++] = m_conventionalData.ckin;
	m_data[idx++] = (SVMSettingInfoID::CKINDiv);
	m_data[idx++] = m_conventionalData.ckinDiv;
	m_data[idx++] = (SVMSettingInfoID::ColorSpace);
	m_data[idx++] = m_conventionalData.color;
	m_data[idx++] = (SVMSettingInfoID::BT656Mode);
	m_data[idx++] = m_conventionalData.bt656;
	m_data[idx++] = (SVMSettingInfoID::PolartyDE);
	m_data[idx++] = m_conventionalData.de;
	m_data[idx++] = (SVMSettingInfoID::PolartyDCKEdge);
	m_data[idx++] = m_conventionalData.edge;
	m_data[idx++] = (SVMSettingInfoID::PolartyHSync);
	m_data[idx++] = m_conventionalData.hsync;
	m_data[idx++] = (SVMSettingInfoID::PolartyVSync);
	m_data[idx++] = m_conventionalData.vsync;
	m_data[idx++] = (SVMSettingInfoID::CSSwapMode);
	m_data[idx++] = m_conventionalData.csSwap;
	m_data[idx++] = (SVMSettingInfoID::EndianMode);
	m_data[idx++] = m_conventionalData.csEndian;
	*/
	m_conventionalData.ckin = 0;
	m_conventionalData.ckinDiv = 0;
	m_conventionalData.color = 0;
	m_conventionalData.bt656 = 0;
	m_conventionalData.edge = 0;
	m_conventionalData.hsync = 0;
	m_conventionalData.vsync = 0;
	m_conventionalData.csSwap = 0;
	m_conventionalData.csEndian = 3;
	m_conventionalData.deMode = 0;
	m_conventionalData.deEnabled = 0;
	m_conventionalData.decimation = 0;
	m_conventionalData.hdmiRange = 0;

	// next 32 bytes
	idx = 32;
	m_data[idx++] = 0x55;
	m_data[idx++] = 0x55;


}

int CSettingDataManager::ReadFromSPIBuf(const UCHAR* pData, int dataSize)
{
	int i;
	int idx = 0;
	if(dataSize < 32) return -1;

	// first 32 bytes
	for(i=0; i<16; i++){
		switch(pData[i*2]){
		case (UCHAR)(SVMSettingInfoID::CKIN):
			m_conventionalData.ckin = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::CKINDiv):
			m_conventionalData.ckinDiv = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::ColorSpace):
			m_conventionalData.color = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::BT656Mode):
			m_conventionalData.bt656 = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::PolartyDE):
			m_conventionalData.deMode = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::PolartyDCKEdge):
			m_conventionalData.edge = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::PolartyHSync):
			m_conventionalData.hsync = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::PolartyVSync):
			m_conventionalData.vsync = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::CSSwapMode):
			m_conventionalData.csSwap = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::EndianMode):
			m_conventionalData.csEndian = pData[i*2+1];
			break; 
		case (UCHAR)(SVMSettingInfoID::DEEnabled):
			m_conventionalData.deEnabled = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::Decimation):
			m_conventionalData.decimation = pData[i*2+1];
			break;
		case (UCHAR)(SVMSettingInfoID::HDMIRange):
			m_conventionalData.hdmiRange = pData[i*2+1];
			break;
		}
	}

	// next xx bytes
	for(idx = 32; idx<sizeof(m_data); idx++){
		if(idx >= dataSize) break;
		m_data[idx] = pData[idx];
	}

	// uvc data
	{
		const int offs = 128;
		if(m_data[offs+0] == 0x55 && m_data[offs+1] == 0x55){
			// valid
			int width  = m_data[offs+4] | (((int)m_data[offs+5]) << 8);
			int height = m_data[offs+6] | (((int)m_data[offs+7]) << 8);
			int fps    = m_data[offs+8] | (((int)m_data[offs+9]) << 8);
			int deviceID = m_data[offs+10] | (((int)m_data[offs+11]) << 8);
			int color  = m_data[offs+14] | (((int)m_data[offs+15]) << 8);

			CString fpsString;
			if(fps > 120){
				fpsString.Format("%.3f", fps * 0.001);
			}else{
				fpsString.Format("%d", fps);
			}

			m_uvcData.width		 = width;
			m_uvcData.height	 = height;
			m_uvcData.fps		 = fpsString;
			m_uvcData.colorid	 = color;
			m_uvcData.deviceid	 = deviceID;
		}else{
			// error
			/*
			char buf[256];
			sprintf(buf, "No SPI setting: %02X, %02X", m_data[0], m_data[offs]);
			MessageBoxA(NULL, buf, "", MB_OK);
			*/
		}
	}

	// clipping
	{
		const int offs = 128 + 32;
		if( (m_data[offs+0] == 0x55 && m_data[offs+1] == 0x55) ||  (m_data[offs+0] == 0x11 && m_data[offs+1] == 0x11) ){
			// valid
			if( (m_data[offs+0] == 0x55 && m_data[offs+1] == 0x55) ){
				m_clippingData.enable = 1;
			}else{
				m_clippingData.enable = 0;
			}
			int x0     = m_data[offs+2] | (((int)m_data[offs+3]) << 8);
			int y0     = m_data[offs+4] | (((int)m_data[offs+5]) << 8);
			int width  = m_data[offs+6] | (((int)m_data[offs+7]) << 8);
			int height = m_data[offs+8] | (((int)m_data[offs+9]) << 8);
			

			// do not forget
			m_clippingData.x0 = x0;
			m_clippingData.y0 = y0;
			m_clippingData.width = width;
			m_clippingData.height = height;

//			char buf[64];
//			sprintf(buf, "width = %d", m_clippingData.width);
//			MessageBox(NULL, buf, "", MB_OK);
		}
	}

	// SVO data
	for(idx=0; idx<256; idx++){
		if(256+idx >= dataSize) break;
		m_svoData[idx] = m_data[256+idx];
	}

	return 0;
}
int CSettingDataManager::SetToSPIBuf(UCHAR* pData, int dataSize)
{
	int idx = 0;

	if(dataSize < 32) return -1;

	// first 32 bytes
	pData[idx++] = (SVMSettingInfoID::CKIN); // 1
	pData[idx++] = m_conventionalData.ckin;
	pData[idx++] = (SVMSettingInfoID::CKINDiv);
	pData[idx++] = m_conventionalData.ckinDiv;
	pData[idx++] = (SVMSettingInfoID::ColorSpace);
	pData[idx++] = m_conventionalData.color;
	pData[idx++] = (SVMSettingInfoID::BT656Mode);
	pData[idx++] = m_conventionalData.bt656;
	pData[idx++] = (SVMSettingInfoID::PolartyDE);
	pData[idx++] = m_conventionalData.deMode;
	pData[idx++] = (SVMSettingInfoID::PolartyDCKEdge); // 11
	pData[idx++] = m_conventionalData.edge;
	pData[idx++] = (SVMSettingInfoID::PolartyHSync);
	pData[idx++] = m_conventionalData.hsync;
	pData[idx++] = (SVMSettingInfoID::PolartyVSync);
	pData[idx++] = m_conventionalData.vsync;
	pData[idx++] = (SVMSettingInfoID::CSSwapMode);
	pData[idx++] = m_conventionalData.csSwap;
	pData[idx++] = (SVMSettingInfoID::EndianMode);
	pData[idx++] = m_conventionalData.csEndian;
	pData[idx++] = (SVMSettingInfoID::DEEnabled); // 21
	pData[idx++] = m_conventionalData.deEnabled;
	pData[idx++] = (SVMSettingInfoID::Decimation);
	pData[idx++] = m_conventionalData.decimation;
	pData[idx++] = (SVMSettingInfoID::HDMIRange);
	pData[idx++] = m_conventionalData.hdmiRange;


	// uvc data
	{
		const int offs = 128;
		int i;
		m_data[offs+0] = 0x55; m_data[offs+1] = 0x55;
		

		int height = m_uvcData.height;
		int width  = m_uvcData.width;
		const CString fpsString = m_uvcData.fps;
		int color    = m_uvcData.colorid;
		int deviceID = m_uvcData.deviceid;

		unsigned char guidBuf[64];
		char buf[128];
		int guidRet = GetColorGUID(color, guidBuf, buf, sizeof(buf)-1);

		int fps = 30;
		if(strstr(fpsString, ".")){
			fps = (int)(atof(fpsString) * 1000);
		}else{
			fps = atoi(fpsString);
		}

		m_data[offs+4] = width  & 0xFF;
		m_data[offs+5] = width  >> 8;
		m_data[offs+6] = height & 0xFF;
		m_data[offs+7] = height >> 8;
		m_data[offs+8] = fps & 0xFF;
		m_data[offs+9] = fps >> 8;
		m_data[offs+10] = deviceID & 0xFF;
		m_data[offs+11] = deviceID >> 8;

		m_data[offs+14] = color & 0xFF;
		m_data[offs+15] = color >> 8;
		

		if(guidRet == 0){
			for(i=0; i<16; i++){
				m_data[offs+16+i] = guidBuf[i];	
			}
		}else{
			// 無効なGUID
			const unsigned char defaultGUID[] = {
				0x55,0x59,0x56,0x59,0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71
			};
			for(i=0; i<16; i++){
				m_data[offs+16+i] = defaultGUID[i];
			}
		}

		unsigned short sum = 0;
		for(i=4; i<32; i++){
			sum += m_data[offs+i];
		}

		sum = ~sum;
		m_data[offs+2] = sum & 0xFF;
		m_data[offs+3] = sum >> 8;
	}

	// clipping data
	{
		const int offs = 128 + 32;
		if(m_clippingData.enable){
			m_data[offs+0] = 0x55; m_data[offs+1] = 0x55;
		}else{
			m_data[offs+0] = 0x11; m_data[offs+1] = 0x11;
		}
		m_data[offs+2] = m_clippingData.x0;
		m_data[offs+3] = m_clippingData.x0 >> 8;
		m_data[offs+4] = m_clippingData.y0;
		m_data[offs+5] = m_clippingData.y0 >> 8;
		m_data[offs+6] = m_clippingData.width;
		m_data[offs+7] = m_clippingData.width >> 8;
		m_data[offs+8] = m_clippingData.height;
		m_data[offs+9] = m_clippingData.height >> 8;

//		char buf[64];
//		sprintf(buf, "width = %d", m_clippingData.width);
//		MessageBox(NULL, buf, "", MB_OK);
	}

	// next xx bytes
	for(idx = 32; idx<256; idx++){
		if(idx >= dataSize) break;
		pData[idx] = m_data[idx];
	}

	// SVO data
	for(idx=0; idx<256; idx++){
		if(256+idx >= dataSize) break;
		pData[256+idx] = m_svoData[idx];
//		pData[256+idx] = idx; // test
	}

	return 0;
}

int CSettingDataManager::GetColorGUID(int idx, unsigned char* pGuid, char* name, int nameSize)
{
	if(idx < 0) return -1;

	// Iniファイル名取得
	CString AppName = AfxGetAppName();
	CString IniFileName = "\\" + AppName + ".ini";
	TCHAR Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,Path);
	IniFileName =  Path + IniFileName;
	CIniFileControl iniFile(AppName, IniFileName);

	CString guidString, nameString;

	char buf[128];
	sprintf(buf, "ColorName%d", idx);
	nameString = iniFile.getString(buf, "");
	sprintf(buf, "ColorGUID%d", idx);
	guidString = iniFile.getString(buf, "");

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
