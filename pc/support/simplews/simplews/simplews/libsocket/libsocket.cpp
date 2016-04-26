#include "libsocket.h"

#include <stdint.h>

bool libsocket::LSInitWinSocket() {
	bool result = true;
	WSADATA data;
	int16_t version = static_cast<int16_t>((2 << 8) + 2); // Major version:2 Minor version:2
	
	if(WSAStartup(version, &data) != 0) {
		result = false;
	}

	return result;
}

void libsocket::LSCleanupWinSocket() {
	WSACleanup();
}

SOCKET libsocket::LSCreateTCPSocket(uint16_t port) {
	bool result = false;

	// Create the TCP socket
	SOCKET soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(soc != INVALID_SOCKET) {
		
		// Bind the socket
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		
		if(bind(soc, (const sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR) {
			
			// Listen to the connections
			if(listen(soc, 5) != SOCKET_ERROR) {
				result = true;
			}
		}
	}

	if(result == false) {
		soc = INVALID_SOCKET;
	}

	return soc;
}

void libsocket::LSCloseSocket(SOCKET sock) {
	closesocket(sock);
}

SOCKET libsocket::LSWaitConnection(SOCKET listen, int32_t time, sockaddr* remote, int* length) {
	bool result = false;
	SOCKET communication_sock = INVALID_SOCKET;

	if(listen != INVALID_SOCKET) {
		
		if(time != 0) {
			struct timeval timeout;
			timeout.tv_usec = time;
			setsockopt(listen, SOL_SOCKET, SO_RCVTIMEO,  (const char*)&timeout, sizeof(timeout));
		}

		if(remote == NULL
			|| length == NULL) {
				sockaddr_in ignore_addr;
				int ignore_length = sizeof(ignore_addr);
				communication_sock = accept(listen, (sockaddr*)&ignore_addr, &ignore_length);
		} else {
			communication_sock = accept(listen, (sockaddr*)&remote, length);
		}
		int32_t error = WSAGetLastError();

		if(communication_sock != INVALID_SOCKET) {
			result = true;
		}
	}

	if(result == false) {
		communication_sock = INVALID_SOCKET;
	}

	return communication_sock;
}

int32_t libsocket::LSRecvBuffer(SOCKET communicate_sock, int32_t buffer_size, char* buffer) {
	bool result = false;
	int32_t real_buffer_size = 0;

	if(communicate_sock != INVALID_SOCKET
		&& buffer_size != 0
		&& buffer != NULL) {
			real_buffer_size = recv(communicate_sock, buffer, buffer_size, 0);
			result = true;
	}

	if(result == false) {
		real_buffer_size = -1;
	}

	return real_buffer_size;
}

int32_t libsocket::LSSendBuffer(SOCKET communicate_sock, char* buffer, int32_t buffer_size) {
	bool result = false;

	if (communicate_sock != INVALID_SOCKET
		&& buffer != NULL
		&& buffer_size > 0) {
			send(communicate_sock, buffer, buffer_size, 0);
			result = true;
	}

	if(result == false) {
		return -1;
	} else {
		return 0;
	}
}