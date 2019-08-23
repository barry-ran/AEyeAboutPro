/***********************************************************************************
*								Base.cpp
*
* Copyright(C):	智慧眼科技股份有限公司
*
* Author:  YCL
*
* Date: 2019-06
*
* Description: base64编解码类库
***********************************************************************************/

#include "Base64.h"
#include <string>
#include <fstream>
#include <cassert>
#include <QFile>

int Base64::encode(char * base64code, const char * src, int src_len) 
{
    Base64 b;
	if (src_len == 0)
	{
		src_len = strlen(src);
	}
	
	int len = 0;
	unsigned char* psrc = (unsigned char*)src;
	char * p64 = base64code;
	int i;
	for (i = 0; i < src_len - 3; i += 3) 
	{
		unsigned long ulTmp = *(unsigned long*)psrc;
        register int b0 = b.getB64Char((B0(ulTmp) >> 2) & 0x3F); 
        register int b1 = b.getB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
        register int b2 = b.getB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F); 
        register int b3 = b.getB64Char((B2(ulTmp) << 2 >> 2) & 0x3F); 
		*((unsigned long*)p64) = b0 | b1 << 8 | b2 << 16 | b3 << 24;
		len += 4;
		p64  += 4; 
		psrc += 3;
	}
	
	// 处理最后余下的不足3字节的饿数据
	if (i < src_len) 
	{
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j) 
		{
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		}
		
		p64[0] = b.getB64Char((B0(ulTmp) >> 2) & 0x3F); 
		p64[1] = b.getB64Char((B0(ulTmp) << 6 >> 2 | B1(ulTmp) >> 4) & 0x3F); 
		p64[2] = rest > 1 ? b.getB64Char((B1(ulTmp) << 4 >> 2 | B2(ulTmp) >> 6) & 0x3F) : '='; 
		p64[3] = rest > 2 ? b.getB64Char((B2(ulTmp) << 2 >> 2) & 0x3F) : '='; 
		p64 += 4; 
		len += 4;
	}
	
	*p64 = '\0'; 

	return len;
}

int Base64::encodeFile(std::string& strRet, std::string strPath) 
{
    int iRet = -1;
    Base64 b;
    
    if(!QFile::exists(strPath.c_str())) 
	{
        return 1;
    }

    std::ifstream  inFile(strPath.c_str(), std::ios::binary);  
    inFile.exceptions (std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);  

    std::istream::pos_type posBegin = inFile.tellg();
    inFile.seekg(0, std::ios_base::end);
    std::istream::pos_type posEnd = inFile.tellg();
    inFile.seekg(posBegin);

    char* szBuf = new char[posEnd];  
    memset(szBuf, 0, posEnd);  

    inFile.read(reinterpret_cast<char*>(szBuf), posEnd * sizeof(char));  
    inFile.close();  

    char* szRet = new char[3*posEnd];
    iRet = Base64::encode(szRet, szBuf, posEnd);
    strRet = szRet;

    delete[] szBuf;
    delete[] szRet;

    return iRet;
}

int Base64::decode(char * buf, const char * base64code, int src_len/* = 0*/) 
{   
    Base64 b;
	if (src_len == 0) {
		src_len = strlen(base64code);
    }

	int len = 0;
	unsigned char* psrc = (unsigned char*)base64code;
	char * pbuf = buf;
	int i;
	for (i = 0; i < src_len - 4; i += 4) {
		unsigned long ulTmp = *(unsigned long*)psrc;
		
		register int b0 = (b.getB64Index((char)B0(ulTmp)) << 2 | b.getB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		register int b1 = (b.getB64Index((char)B1(ulTmp)) << 4 | b.getB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
		register int b2 = (b.getB64Index((char)B2(ulTmp)) << 6 | b.getB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
		
		*((unsigned long*)pbuf) = b0 | b1 << 8 | b2 << 16;
		psrc  += 4; 
		pbuf += 3;
		len += 3;
	}

	// 处理最后余下的不足4字节的饿数据
	if (i < src_len) {
		int rest = src_len - i;
		unsigned long ulTmp = 0;
		for (int j = 0; j < rest; ++j) {
			*(((unsigned char*)&ulTmp) + j) = *psrc++;
		}
		
		register int b0 = (b.getB64Index((char)B0(ulTmp)) << 2 | b.getB64Index((char)B1(ulTmp)) << 2 >> 6) & 0xFF;
		*pbuf++ = b0;
		len  ++;

		if ('=' != B1(ulTmp) && '=' != B2(ulTmp)) {
			register int b1 = (b.getB64Index((char)B1(ulTmp)) << 4 | b.getB64Index((char)B2(ulTmp)) << 2 >> 4) & 0xFF;
			*pbuf++ = b1;
			len  ++;
		}
		
		if ('=' != B2(ulTmp) && '=' != B3(ulTmp)) {
			register int b2 = (b.getB64Index((char)B2(ulTmp)) << 6 | b.getB64Index((char)B3(ulTmp)) << 2 >> 2) & 0xFF;
			*pbuf++ = b2;
			len  ++;
		}
	}
		
	*pbuf = '\0'; 

	return len;
} 

char Base64::getB64Char(int index)
{
    const char szBase64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (index >= 0 && index < 64) {
        return szBase64Table[index];
    }

    return '=';
}

int Base64::getB64Index(char ch) 
{
    int index = -1;
    if (ch >= 'A' && ch <= 'Z') {
        index = ch - 'A';
    } else if (ch >= 'a' && ch <= 'z') {
        index = ch - 'a' + 26;
    } else if (ch >= '0' && ch <= '9') {
        index = ch - '0' + 52;
    } else if (ch == '+') {
        index = 62;
    } else if (ch == '/') {
        index = 63;
    }

    return index;
}
