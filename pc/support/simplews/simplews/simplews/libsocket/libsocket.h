//-----------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 24
// Version: 1.0
// Brief: The libsocket contains some easy-to-use methods to operate with win32 socket.
// The purpose to design this library is to make our life easier when we build something base on win32 socket.
//-----------------------------------------------------------------------------------------
#ifndef LS_LIBSOCKET_LIBSOCKET_H_ // LS -- libsocket
#define LS_LIBSOCKET_LIBSOCKET_H_

#include <stdint.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

namespace libsocket {

	//----------------------------------------------------------------------------------------
	// @brief: Call this method to startup the win32 socket library.
	// @return: Return true if startup successfully.
	//----------------------------------------------------------------------------------------
	bool LSInitWinSocket();

	//----------------------------------------------------------------------------------------
	// @brief: If you do not want to use win32 socket library, please shutdown it with this method.
	//----------------------------------------------------------------------------------------
	void LSCleanupWinSocket();

	//----------------------------------------------------------------------------------------
	// @brief: This method will create a tcp socket, bind it to localhost and listen to connections.
	// @param: port The port that the server will use to accpet the client's connection.
	//----------------------------------------------------------------------------------------
	SOCKET LSCreateTCPSocket(uint16_t port);

	//----------------------------------------------------------------------------------------
	// @brief: When you do not want to use socket, please close it.
	// @param: sock The socket that you want to close.
	//----------------------------------------------------------------------------------------
	void LSCloseSocket(SOCKET sock);

	//----------------------------------------------------------------------------------------
	// @brief: Wait for connection during specific time.
	// @param: listen The listen socket that listen to client's connections.
	// @param: time The wait connection time in ms. If you want to wait forever, set time as 0.
	// @param: remote The client's address information. If you do not want to get it, just pass NULL.
	// @param: length The size of the remote structure. If you do not want to get it, just pass NULL.
	// @return: When connection has happened, return the communication socket.Otherwise return INVALID_SOCKET.
	//----------------------------------------------------------------------------------------
	SOCKET LSWaitConnection(SOCKET listen, int32_t time, sockaddr* remote, int* length);

	//----------------------------------------------------------------------------------------
	// @brief: Recieve the buffer from the communicate socket.
	// @param: communicate_sock The socket that contains the buffer
	// @param: buffer_size The parameter buffer's size
	// @param: buffer The buffer used to recieve the data.
	// @return: The real size of the recieved buffer. If the method failed, return -1.
	//----------------------------------------------------------------------------------------
	int32_t LSRecvBuffer(SOCKET communicate_sock, int32_t buffer_size, char* buffer);

	//---------------------------------------------------------------------------------------------
	// @brief: Send the buffer to the communicate socket.
	// @param: communicate_sock The socket that recieve the buffer
	// @param: buffer The data that needed to be sent
	// @param: buffer_size The data buffer's size
	// @return: If this method successfully, return 0.
	//---------------------------------------------------------------------------------------------
	int32_t LSSendBuffer(SOCKET communicate_sock, char* buffer, int32_t buffer_size);
}; // namespace libsocket

#endif // LS_LIBSOCKET_LIBSOCKET_H_