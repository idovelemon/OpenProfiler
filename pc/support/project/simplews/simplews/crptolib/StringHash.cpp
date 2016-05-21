
#include "StringHash.h"

#include <ctype.h>


static const unsigned long HASH_OFFSET = 0;
static const unsigned long HASH_A = 1;
static const unsigned long HASH_B = 2; 


bool StringHash::g_initedCryptTable = false;
unsigned long  StringHash::g_cryptTable[0x500] = {0};


StringHash::StringHash(const long nTableLength /*= MAXTABLELEN*/)
{
	if(!g_initedCryptTable)
		InitCryptTable(); 

	m_tablelength = nTableLength; 
	//初始化hash表
	m_HashIndexTable = new HASHTABLE[nTableLength]; 
	for ( int i = 0; i < nTableLength; i++ ) 
	{ 
		m_HashIndexTable[i].nHashA = -1; 
		m_HashIndexTable[i].nHashB = -1; 
		m_HashIndexTable[i].bExists = false; 
	} 
}

StringHash::~StringHash(void)
{
	//清理内存
	if ( NULL != m_HashIndexTable ) 
	{ 
		delete []m_HashIndexTable; 
		m_HashIndexTable = NULL; 
		m_tablelength = 0; 
	} 
}

/************************************************************************/
/*函数名：InitCryptTable
/*功 能：对哈希索引表预处理 
/*返回值：无
/************************************************************************/
void StringHash::InitCryptTable() 
{ 
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

	if(g_initedCryptTable)
		return;

	for( index1 = 0; index1 < 0x100; index1++ ) 
	{ 
		for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 ) 
		{ 
			unsigned long temp1, temp2; 
			seed = (seed * 125 + 3) % 0x2AAAAB; 
			temp1 = (seed & 0xFFFF) << 0x10; 
			seed = (seed * 125 + 3) % 0x2AAAAB; 
			temp2 = (seed & 0xFFFF); 
			g_cryptTable[index2] = ( temp1 | temp2 ); 
		} 
	} 
	g_initedCryptTable = true;
}

/************************************************************************/
/*函数名：HashString
/*功 能：求取哈希值 
/*返回值：返回hash值
/************************************************************************/
unsigned long StringHash::HashString(const string& lpszString, unsigned long dwHashType) 
{ 
	unsigned char *key = (unsigned char *)(const_cast<char*>(lpszString.c_str())); 
	unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE; 
	int ch;

	while(*key != 0) 
	{ 
		ch = toupper(*key++);

		seed1 = g_cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2); 
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; 
	} 
	return seed1; 
}

/************************************************************************/
/*函数名：Hashed
/*功 能：检测一个字符串是否被hash过
/*返回值：如果存在，返回位置；否则，返回-1
/************************************************************************/
unsigned long StringHash::Hashed(string lpszString)
{ 
	//不同的字符串三次hash还会碰撞的几率无限接近于不可能
	unsigned long nHash = HashString(lpszString, HASH_OFFSET); 
	unsigned long nHashA = HashString(lpszString, HASH_A); 
	unsigned long nHashB = HashString(lpszString, HASH_B); 
	unsigned long nHashStart = nHash % m_tablelength, 
	nHashPos = nHashStart;

	while ( m_HashIndexTable[nHashPos].bExists) 
	{ 
	if (m_HashIndexTable[nHashPos].nHashA == nHashA && m_HashIndexTable[nHashPos].nHashB == nHashB)
		return nHashPos; 
	else 
		nHashPos = (nHashPos + 1) % m_tablelength;

	if (nHashPos == nHashStart) 
		break; 
	}

	return -1; //没有找到 
}

/************************************************************************/
/*函数名：Hash
/*功 能：hash一个字符串 
/*返回值：成功，返回true；失败，返回false
/************************************************************************/
bool StringHash::Hash(string lpszString)
{ 
	unsigned long nHash = HashString(lpszString, HASH_OFFSET); 
	unsigned long nHashA = HashString(lpszString, HASH_A); 
	unsigned long nHashB = HashString(lpszString, HASH_B); 
	unsigned long nHashStart = nHash % m_tablelength, 
	nHashPos = nHashStart;

	while ( m_HashIndexTable[nHashPos].bExists) 
	{ 
		nHashPos = (nHashPos + 1) % m_tablelength; 
		if (nHashPos == nHashStart) //一个轮回 
		{ 
			//hash表中没有空余的位置了,无法完成hash
			return false; 
		} 
	} 
	m_HashIndexTable[nHashPos].bExists = true; 
	m_HashIndexTable[nHashPos].nHashA = nHashA; 
	m_HashIndexTable[nHashPos].nHashB = nHashB;

	return true; 
}

/************************************************************************/
/*函数名：GetTwoHashValue
/*功 能：hash一个字符串， 得到两个不同的hash值组成一个long long64位的数字 
/*返回值：成功，返回true；失败，返回false
/************************************************************************/
bool StringHash::GetTwoHashValue(const string& lpszString, long long& hashVal)
{
	hashVal = 0;
	if(!g_initedCryptTable)
		return false;

	unsigned long nHashA = HashString(lpszString, HASH_A); 
	unsigned long nHashB = HashString(lpszString, HASH_B); 

	hashVal = ((long long)nHashA) << sizeof(long);
	hashVal = hashVal | nHashB;

	return true;
}