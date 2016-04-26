#include "swsserver.h"

#include <stdio.h>

#include "crptolib\base64.h"
#include "crptolib\SHA1_Code.h"

#include "swscommunication.h"
#include "swsdefine.h"
#include "libsocket\libsocket.h"

using namespace simplews;

SWSServer::SWSServer(int16_t port)
	:listen_sock_(INVALID_SOCKET)
	,listen_port_(port){

	if(libsocket::LSInitWinSocket() != true) {
		SWS_SAFE_ASSERT(false); // Init the win32 socket error.
		return;
	}
	
	if(port < 0) {
		SWS_SAFE_ASSERT(false); // Invalid port.
		return;
	}

	listen_sock_ = libsocket::LSCreateTCPSocket(static_cast<uint16_t>(port));
	if(listen_sock_ == INVALID_SOCKET) {
		SWS_SAFE_ASSERT(false); // Create TCP socket error.
		return;
	}
}

SWSServer::~SWSServer() {
	Close();
}

SWSCommunication* SWSServer::WaitConnection(int32_t time) {
	bool result = false;
	
	// Wait to connection from client
	SOCKET communicate_sock = libsocket::LSWaitConnection(listen_sock_, time, NULL, NULL);
	
	// Recieve the handshake message
	char buffer[256];
	int32_t real_buffer_length = 0;
	char hand_shake_key[29];

	if(communicate_sock != INVALID_SOCKET) {
		memset(buffer, 0, sizeof(buffer));

		// Recieve the origin header, we just ignore this.
		real_buffer_length  = libsocket::LSRecvBuffer(communicate_sock, sizeof(buffer), buffer);

		// Recieve the handshake from client
		real_buffer_length  = libsocket::LSRecvBuffer(communicate_sock, sizeof(buffer), buffer);
	
		// Extract the Sec-websocket-key from the handshake buffer
		char sec_key[60]; // The Sec-WebSocket-Key:24 bytes GUID:36 bytes
		char* addr = strstr(buffer, "Sec-WebSocket-Key:");

		if(addr != NULL
			&& real_buffer_length - (addr - buffer) >= 24) {
				memcpy(sec_key, addr + 19, 24);
	
				// Append the 258EAFA5-E914-47DA-95CA-C5AB0DC85B11 GID to the sec_key
				memcpy(sec_key + 24, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 36);

				// Sha1 the sec_key
				SHA1_Code sha1;
				char sha1_result[20];
				sha1.Update(reinterpret_cast<unsigned char*>(sec_key), sizeof(sec_key));
				sha1.Final();
				sha1.GetHash(reinterpret_cast<unsigned char*>(sha1_result));

				// Base64 the sec_key
				int32_t base_len = sizeof(hand_shake_key);
				base64_encode(reinterpret_cast<const unsigned char*>(sha1_result), sizeof(sha1_result), 
					reinterpret_cast<unsigned char*>(hand_shake_key), &base_len);
				
				SWS_SAFE_ASSERT(base_len == 28);
				if (base_len == 28) {
					
					// Build the response handshake message
					char response_hand_shake_key[] = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ";
					int32_t response_hand_shake_len = sizeof(response_hand_shake_key) - 1 + base_len + 4;
					char* response_hand_shake = new char[response_hand_shake_len];
					
					SWS_SAFE_ASSERT(response_hand_shake != NULL); // Allocate memory failed
					if(response_hand_shake != NULL) {
						memset(response_hand_shake, 0, response_hand_shake_len);
						
						memcpy(response_hand_shake, response_hand_shake_key, sizeof(response_hand_shake_key) - 1);
						memcpy(response_hand_shake + sizeof(response_hand_shake_key) - 1, hand_shake_key, 28);
					
						response_hand_shake[response_hand_shake_len - 4] = '\r';
						response_hand_shake[response_hand_shake_len - 3] = '\n';
						response_hand_shake[response_hand_shake_len - 2] = '\r';
						response_hand_shake[response_hand_shake_len - 1] = '\n';

						libsocket::LSSendBuffer(communicate_sock, response_hand_shake, response_hand_shake_len);

						delete[] response_hand_shake;
						response_hand_shake = NULL;

						result = true;
					}
				}
		}
	}

	// Create the communication
	SWSCommunication* comm = new SWSCommunication();
	comm->AttachSocket(communicate_sock);
	return comm;
}

void SWSServer::Close() {
	libsocket::LSCloseSocket(listen_sock_);
	libsocket::LSCleanupWinSocket();
}