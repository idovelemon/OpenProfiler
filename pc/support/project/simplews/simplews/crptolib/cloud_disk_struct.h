#ifndef CLOUD_DISK_STRUCT_H
#define CLOUD_DISK_STRUCT_H

#include <map>
#include <list>
#include <vector>
using namespace std;

typedef long  MyInt64;
typedef int   MyInt32;

typedef unsigned int   MyUInt32;
typedef unsigned long  MyUInt64;


typedef struct _Account_Info     //用户账号信息
{
	MyInt64   user_id;
	char      user_name[256];
	char      password_md5[40];
	MyInt64   parent_id;
	double    assign_size;
	double    remain_size;
	char      email[128];
	char      phone_number[16];
	MyInt32   user_disable;    //0---enable; 1---disable
}Account_Info, *PAccount_Info;


typedef map<MyInt64, PAccount_Info>    Account_Map;       //账号ID到账号信息的map

typedef vector<PAccount_Info>            Account_Array;      //账号队列
typedef map<MyInt64, Account_Array*>    Parent_Child_Account_Map;   //父账号到子账号队列的map

typedef struct _Bucket_Info   //空间bucket信息
{
	MyInt64   bucket_id;
	char      bucket_name[64];
	MyInt64   owner_user_id;
	MyInt32   bucket_limit;    //0---public;  1---private

}Bucket_Info, *PBucket_Info;

typedef map<MyInt64, PBucket_Info>    Bucket_Map;       //bucket ID到bucket信息的map

typedef vector<PBucket_Info>            Bucket_Array;      //bucket队列
typedef map<MyInt64, Bucket_Array>     Owner_Buckets_Map;    //owner_user_id到拥有的bucket队列的map


typedef struct _Block_Progress     //block上传进度信息
{
	MyInt64   block_id;
	MyInt32   laster_chunk_index;    //最后上传的chunk在block内的位置
	MyInt32   next_chunk_pos;        //下一个待上传chunk在block内的文件位置
	MyUInt32  laster_chunk_crc32;    //最后上传的chunk在block内的CRC32校验
}Block_Progress, *PBlock_Progress;

typedef map<MyInt32, PBlock_Progress>     Block_Idx_Map;    //block index到block上传进度信息的map

#endif