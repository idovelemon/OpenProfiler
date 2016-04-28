//-----------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 26
// Version: 1.0
// Brief: The SWSCommunication is the pipe between the server and client, you can use this to send and recieve data.
// Update: 2016 / 04 / 28 - Use interface to hide the implementation detail.
//-----------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSCOMMUNICATIONIMP_H_
#define SWS_SIMPLEWS_SWSCOMMUNICATIONIMP_H_

#include <stdint.h>
#include <WinSock2.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunicationImp {
public:
	SWSCommunicationImp();
	virtual ~SWSCommunicationImp();

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
	// @return: The length of the real buffer that has been sent.If this method failed, return 01.
	//--------------------------------------------------------------------------------
	virtual int32_t SendBuffer(char* buffer, int32_t buffer_size);

	//--------------------------------------------------------------------------------
	// @brief: Recieve the buffer from the client through the communication.
	// @param: buffer_size The size of the buffer.
	// @param: buffer The buffer that stores the data from the communication.
	// @return: The real length of data that stored in the buffer.If the method failed, return -1.
	// @note: This method will block the thread if it hasn't recieved data.
	//--------------------------------------------------------------------------------
	virtual int32_t RecvBuffer(int32_t buffer_size, char* buffer);

protected:
	SOCKET									communicate_sock_;	// The communicate socket between the server and client.

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSCommunicationImp);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSCOMMUNICATIONIMP_H_