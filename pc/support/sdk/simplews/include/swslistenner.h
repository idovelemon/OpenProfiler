//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 28
// Version: 1.0
// Brief: The SWSListenner is an object that you can use it as a websocket listenner.
// First you create the listenner, then you call the WaitConnection() method to accept the client's connection.
// When the connection is comming, the WaitConnection() method will return a SWSCommunication object,
// you can use SWSCommunication object to communicate with the client.
// At last, you can call Close() method to close the listenner if you do not want to accept more connections.
//-----------------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSLISTENNER_H_
#define SWS_SIMPLEWS_SWSLISTENNER_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunication;
class SWSListennerImp;

class SWSListenner{
public:
	//----------------------------------------------------------------------------
	// @param:port The port that you want to listen to the connection from client.
	//----------------------------------------------------------------------------
	SWSListenner(int16_t port);
	virtual ~SWSListenner();

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
	SWSListennerImp*					imp_; // The implementation of the SWSListenner interface.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSListenner);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSLISTENNER_H_