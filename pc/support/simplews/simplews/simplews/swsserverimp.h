//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 24
// Version: 1.0
// Brief: The SWSServer is an object that you can use it as a websocket server.
// Update: 2016 / 04 / 28 Use interface to hide the implemention detail.
//-----------------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSSERVERIMP_H_
#define SWS_SIMPLEWS_SWSSERVERIMP_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunication;

class SWSServerImp{
public:
	//----------------------------------------------------------------------------
	// @param:port The port that you want to listen to the connection from client.
	//----------------------------------------------------------------------------
	SWSServerImp(int16_t port);
	virtual ~SWSServerImp();

	//-----------------------------------------------------------------------------
	// @brief: After you create a server, you can call waitConnection to accpet the connection from client.
	// This method will block the thread time ms. Once the connection is comming, it will return immediately.
	// @param: time The largest block time. If you want to wait forever, set the time as 0.
	// @return: SWSCommnunication
	//-----------------------------------------------------------------------------
	virtual SWSCommunication* WaitConnection(int32_t time);

	//-----------------------------------------------------------------------------
	// @brief: At anytime, if you want to shutdown the server, you can call this method.
	//-----------------------------------------------------------------------------
	virtual void Close();

protected:
	SOCKET											listen_sock_; // The listen socket. Listen to the client's connection.
	int16_t												listen_port_; // The port that the server will use to listen to client's connection.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSServerImp);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSERVERIMP_H_