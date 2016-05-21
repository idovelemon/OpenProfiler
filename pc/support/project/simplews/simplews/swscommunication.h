//-----------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 28
// Version: 1.0
// Brief: The SWSCommunication is the pipe between the server and client, you can use this to send and recieve data.
//-----------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSCOMMUNICATION_H_
#define SWS_SIMPLEWS_SWSCOMMUNICATION_H_

#include <stdint.h>

#include "swsdefine.h"

namespace simplews {

class SWSCommunicationImp;

class SWSCommunication {
public:
	SWSCommunication(SWSCommunicationImp* imp);
	virtual ~SWSCommunication();

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
	SWSCommunicationImp*					imp_;

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSCommunication);
};

}; // namespace simplews

#endif // SWS_SIMPLEWS_SWSCOMMUNICATIONIMP_H_