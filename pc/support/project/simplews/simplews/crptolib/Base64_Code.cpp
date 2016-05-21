#include "Base64_Code.h"


static const char BASE_CODE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

Base64Code::Base64Code(void)
{
}

Base64Code::~Base64Code(void)
{
}

//���룬������Ҫ������ַ���ָ�룬������ŵ�λ�ã������ִ����ȵ�4/3����Ҫ������ַ������� ->���ؽ������
int Base64Code::Base64Encode(char *lpString, char *lpBuffer, int sLen) 
{	
	register int vLen = 0;	//�Ĵ����ֲ�����������
	while(sLen > 0)		//���������ַ���
	{	
		*lpBuffer++ = BASE_CODE[(lpString[0] >> 2 ) & 0x3F];	//������λ����00111111�Ƿ�ֹ������Լ�
		if(sLen > 2)	//��3���ַ�
		{	
			*lpBuffer++ = BASE_CODE[((lpString[0] & 3) << 4) | (lpString[1] >> 4)];
			*lpBuffer++ = BASE_CODE[((lpString[1] & 0xF) << 2) | (lpString[2] >> 6)];
			*lpBuffer++ = BASE_CODE[lpString[2] & 0x3F];
		}
		else
		{	
			switch(sLen)	//׷�ӡ�=��
			{	
			case 1:
				*lpBuffer ++ = BASE_CODE[(lpString[0] & 3) << 4 ];
				*lpBuffer ++ = '=';
				*lpBuffer ++ = '=';
				break;
			case 2:
				*lpBuffer ++ = BASE_CODE[((lpString[0] & 3) << 4) | (lpString[1] >> 4)];
				*lpBuffer ++ = BASE_CODE[((lpString[1] & 0x0F) << 2) | (lpString[2] >> 6)];
				*lpBuffer ++ = '=';
				break;
			}
		}
		lpString += 3;
		sLen -= 3;
		vLen +=4;
	}
	*lpBuffer = 0;
	return vLen;
}

//���룬��������������ģ����ĳ���
int Base64Code::Base64Decode(char *lpString, char *lpSrc, int sLen)   //���뺯��
{	
	static char lpCode[4];
	register int vLen = 0;
	if(sLen % 4)		//Base64���볤�ȱض���4�ı���������'='
	{	
		lpString[0] = '\0';
		return -1;
	}
	while(sLen > 2)		//���������ַ�������
	{	
		lpCode[0] = GetCharIndex(lpSrc[0]);
		lpCode[1] = GetCharIndex(lpSrc[1]);
		lpCode[2] = GetCharIndex(lpSrc[2]);
		lpCode[3] = GetCharIndex(lpSrc[3]);

		*lpString++ = (lpCode[0] << 2) | (lpCode[1] >> 4);
		*lpString++ = (lpCode[1] << 4) | (lpCode[2] >> 2);
		*lpString++ = (lpCode[2] << 6) | (lpCode[3]);

		lpSrc += 4;
		sLen -= 4;
		vLen += 3;
	}
	return vLen;
}

