#pragma once
class Base64Code
{
public:
	Base64Code(void);
	~Base64Code(void);

public:
	int Base64Encode(char *lpString, char *lpBuffer, int sLen);

	int Base64Decode(char *lpString, char *lpSrc, int sLen);

protected:
	inline char GetCharIndex(char c);

};

//�Ӻ��� - ȡ���ĵ�����
inline char Base64Code::GetCharIndex(char c) //������������ʡȥ�������ù��̣�����
{	
	if((c >= 'A') && (c <= 'Z'))
	{	return c - 'A';
	}else if((c >= 'a') && (c <= 'z'))
	{	return c - 'a' + 26;
	}else if((c >= '0') && (c <= '9'))
	{	return c - '0' + 52;
	}else if(c == '+')
	{	return 62;
	}else if(c == '/')
	{	return 63;
	}else if(c == '=')
	{	return 0;
	}
	return 0;
}
