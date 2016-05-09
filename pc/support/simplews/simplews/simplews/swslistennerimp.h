//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 24
// Version: 1.0
// Brief: The SWSListenner is an object that you can use it as a websocket server.
// Update: 2016 / 04 / 28 Use interface to hide the implemention detail.
//-----------------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSLISTENNERIMP_H_
#define SWS_SIMPLEWS_SWSLISTENNERIMP_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunication;

class SWSListennerImp{
public:
	//----------------------------------------------------------------------------
	// @param:port The port that you want to listen to the connection from client.
	//----------------------------------------------------------------------------
	SWSListennerImp(int16_t port);
	virtual ~SWSListennerImp();

	//-----------------------------------------------------------------------------
	// @brief: After you create a listenner, you can call waitConnection to accpet the connection from client.
	// This method will block the thread time ms. Once the connection is comming, it will return immediately.
	// @param: time The largest block time. If you want to wait forever, set the time as 0.
	// @return: SWSCommnunication
	//-----------------------------------------------------------------------------
	virtual SWSCommunication* WaitConnection(int32_t time);

	//-----------------------------------------------------------------------------
	// @brief: At anytime, if you want to shutdown the listenner, you can call this method.
	//-----------------------------------------------------------------------------
	virtual void Close();

protected:

	//-----------------------------------------------------------------------------
	// @brief: Recieve the handshake message from the client and store it in the handshakemsg
	//-----------------------------------------------------------------------------
	int32_t RecieveHandshakeMsg(SOCKET sock, char* handshake_msg, int32_t len);

	//-----------------------------------------------------------------------------
	// @brief: Extract the Sec-WebSocket-Key from the handshake mesage and store in in the sec_websocket_key
	//-----------------------------------------------------------------------------
	bool ExtractSecWebsocketKey(char* handshake_msg, int32_t len,  char* sec_websocket_key);

	//-----------------------------------------------------------------------------
	// @brief: Append the GUID to the Sec-Websocket-Key to build the response handshake key plaintext
	//-----------------------------------------------------------------------------	
	bool AppendGUID(char* sec_websocket_key, int32_t len,  char* response_handshake_key_plaintext);

	//-----------------------------------------------------------------------------
	// @brief: Encrypt the response handshake key plaintext into the ciphertext
	//-----------------------------------------------------------------------------	
	bool Encrypt(char* response_handshake_key_plaintext, int32_t plaintext_len,
							  char* response_handshake_key_ciphertext, int32_t ciphertext_len);

	//-----------------------------------------------------------------------------
	// @brief: Build the response handshake message base on the response handshake key ciphertext
	//-----------------------------------------------------------------------------	
	bool BuildResponseHandshakeMsg(char* response_handshake_key_ciphertext, int32_t ciphertext_len,
												char* response_handshake_msg, int32_t handshake_msg_len);

	SOCKET											listen_sock_; // The listen socket. Listen to the client's connection.
	int16_t												listen_port_; // The port that the listenner will use to listen to client's connection.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSListennerImp);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSLISTENNERIMP_H_