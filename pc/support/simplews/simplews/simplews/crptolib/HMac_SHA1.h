#pragma once
#include "SHA1_Code.h"

typedef unsigned char BYTE ;

class HMAC_SHA1 : public SHA1_Code
{
private:
	BYTE m_ipad[64];
	BYTE m_opad[64];

	char * szReport ;
	char * SHA1_Key ;
	char * AppendBuf1 ;
	char * AppendBuf2 ;


public:

	enum {
		SHA1_DIGEST_LENGTH    = 20,
		SHA1_BLOCK_SIZE        = 64,
		HMAC_BUF_LEN        = 4096
	} ;

	HMAC_SHA1()
		:szReport(new char[HMAC_BUF_LEN]),
		AppendBuf1(new char[HMAC_BUF_LEN]),
		AppendBuf2(new char[HMAC_BUF_LEN]),
		SHA1_Key(new char[HMAC_BUF_LEN])
	{}

	~HMAC_SHA1()
	{
		delete[] szReport ;
		delete[] AppendBuf1 ;
		delete[] AppendBuf2 ;
		delete[] SHA1_Key ;
	}

	void HMAC_SHA1_Encode(BYTE *text, int text_len, BYTE *key, int key_len, BYTE *digest);
};
