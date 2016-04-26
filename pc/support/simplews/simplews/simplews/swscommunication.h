//-----------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 26
// Version: 1.0
// Brief: The SWSCommunication is the pipe between the server and client, you can use this to send and recieve data.
//-----------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSCOMMUNICATION_H_
#define SWS_SIMPLEWS_SWSCOMMUNICATION_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunication {
public:
	SWSCommunication();
	virtual ~SWSCommunication();

	//-------------------------------------------------------------------------------
	// @brief: Attach a socket to this communication, all the communications between server and client will go through the socket.
	// @param: communicate_sock The socket between server and client.
	//-------------------------------------------------------------------------------
	virtual void AttachSocket(SOCKET communicate_sock);
	
	//--------------------------------------------------------------------------------
	// @brief: Detach the socket from the communication.
	//--------------------------------------------------------------------------------
	virtual void DetachSocket();

	//--------------------------------------------------------------------------------
	// @brief: Send the buffer to the client through the communication.
	// @param: buffer The buffer that need to be sent.
	// @param: buffer_size The size of the buffer.
	//--------------------------------------------------------------------------------
	virtual void SendBuffer(char* buffer, int32_t buffer_size);

	//--------------------------------------------------------------------------------
	// @brief: Recieve the buffer from the client through the communication.
	// @param: buffer_size The size of the buffer.
	// @param: buffer The buffer that stores the data from the communication.
	// @return: The real length of the recieved data.
	//--------------------------------------------------------------------------------
	virtual int32_t RecvBuffer(int32_t buffer_size, char* buffer);

protected:
	SOCKET									communicate_sock_;	// The communicate socket between the server and client.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSCommunication);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSCOMMUNICATION_H_