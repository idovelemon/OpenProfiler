//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 28
// Version: 1.0
// Brief: The SWSServer is an object that you can use it as a websocket server.
// First you create the server, then you call the WaitConnection() method to accept the client's connection.
// When the connection is comming, the WaitConnection() method will return a SWSCommunication object,
// you can use SWSCommunication object to communicate with the client.
// At last, you can call Close() method to close the server if you do not want to accept more connections.
//-----------------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSSERVER_H_
#define SWS_SIMPLEWS_SWSSERVER_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunication;
class SWSServerImp;

class SWSServer{
public:
	//----------------------------------------------------------------------------
	// @param:port The port that you want to listen to the connection from client.
	//----------------------------------------------------------------------------
	SWSServer(int16_t port);
	virtual ~SWSServer();

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
	SWSServerImp*					imp_; // The implementation of the SWSServer interface.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSServer);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSERVER_H_