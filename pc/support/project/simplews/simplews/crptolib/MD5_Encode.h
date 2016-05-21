#pragma once
//#pragma warning(disable:4786)

#include <string>

using namespace std;

/*!
 * Manage MD5.
 */
class MD5_Encode
{
private:
    #define uint8  unsigned char
    #define uint32 unsigned long int

    struct md5_context
    {
        uint32 total[2];
        uint32 state[4];
        uint8 buffer[64];
    };

    void md5_starts( struct md5_context *ctx );
    void md5_process( struct md5_context *ctx, uint8 data[64] );
    void md5_update( struct md5_context *ctx, uint8 *input, uint32 length );
    void md5_finish( struct md5_context *ctx, uint8 digest[16] );

public:
    //! construct a MD5 from any buffer
    void GenerateMD5(unsigned char* buffer,int bufferlen);

    //! construct a MD5
    MD5_Encode();

    //! construct a md5src from char *
    MD5_Encode(const char * md5src);

    //! construct a MD5 from a 16 bytes md5
    MD5_Encode(unsigned long* md5src);

    //! add a other md5
    MD5_Encode operator +(MD5_Encode adder);

    //! just if equal
    bool operator ==(MD5_Encode cmper);

    //! give the value from equer
    // void operator =(MD5 equer);

    //! to a string
    string ToString();

    unsigned long m_data[4];
};
