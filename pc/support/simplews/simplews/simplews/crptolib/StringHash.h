#pragma once

#include <string>

using namespace std;


#define MAXTABLELEN 1024 // Ĭ�Ϲ�ϣ�������С 
////////////////////////////////////////////////////////////////////////// 
// ��ϣ�������� 
typedef struct _HASHTABLE
{ 
	long nHashA; 
	long nHashB; 
	bool bExists; 
}HASHTABLE, *PHASHTABLE ;

class StringHash
{
public:
	StringHash(const long nTableLength = MAXTABLELEN);
	~StringHash(void);
private: 
	static bool g_initedCryptTable;
	static unsigned long g_cryptTable[0x500]; 

	unsigned long m_tablelength; // ��ϣ�������� 
	HASHTABLE *m_HashIndexTable; 
private:
	static unsigned long HashString(const string& lpszString, unsigned long dwHashType); // ��ȡ��ϣֵ 
public:
	static void InitCryptTable(); // �Թ�ϣ������Ԥ���� 
	static bool GetTwoHashValue(const string& lpszString, long long& hashVal);   

	bool Hash(string url);
	unsigned long Hashed(string url); // ���url�Ƿ�hash��
};

