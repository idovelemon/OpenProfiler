#pragma once

#include <string>

using namespace std;


#define MAXTABLELEN 1024 // 默认哈希索引表大小 
////////////////////////////////////////////////////////////////////////// 
// 哈希索引表定义 
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

	unsigned long m_tablelength; // 哈希索引表长度 
	HASHTABLE *m_HashIndexTable; 
private:
	static unsigned long HashString(const string& lpszString, unsigned long dwHashType); // 求取哈希值 
public:
	static void InitCryptTable(); // 对哈希索引表预处理 
	static bool GetTwoHashValue(const string& lpszString, long long& hashVal);   

	bool Hash(string url);
	unsigned long Hashed(string url); // 检测url是否被hash过
};

