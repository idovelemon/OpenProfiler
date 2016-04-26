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


typedef struct _Account_Info     //�û��˺���Ϣ
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


typedef map<MyInt64, PAccount_Info>    Account_Map;       //�˺�ID���˺���Ϣ��map

typedef vector<PAccount_Info>            Account_Array;      //�˺Ŷ���
typedef map<MyInt64, Account_Array*>    Parent_Child_Account_Map;   //���˺ŵ����˺Ŷ��е�map

typedef struct _Bucket_Info   //�ռ�bucket��Ϣ
{
	MyInt64   bucket_id;
	char      bucket_name[64];
	MyInt64   owner_user_id;
	MyInt32   bucket_limit;    //0---public;  1---private

}Bucket_Info, *PBucket_Info;

typedef map<MyInt64, PBucket_Info>    Bucket_Map;       //bucket ID��bucket��Ϣ��map

typedef vector<PBucket_Info>            Bucket_Array;      //bucket����
typedef map<MyInt64, Bucket_Array>     Owner_Buckets_Map;    //owner_user_id��ӵ�е�bucket���е�map


typedef struct _Block_Progress     //block�ϴ�������Ϣ
{
	MyInt64   block_id;
	MyInt32   laster_chunk_index;    //����ϴ���chunk��block�ڵ�λ��
	MyInt32   next_chunk_pos;        //��һ�����ϴ�chunk��block�ڵ��ļ�λ��
	MyUInt32  laster_chunk_crc32;    //����ϴ���chunk��block�ڵ�CRC32У��
}Block_Progress, *PBlock_Progress;

typedef map<MyInt32, PBlock_Progress>     Block_Idx_Map;    //block index��block�ϴ�������Ϣ��map

#endif