#include "swslistennerimp.h"

#include <stdio.h>

#include "crptolib\base64.h"
#include "crptolib\SHA1_Code.h"

#include "swscommunication.h"
#include "swscommunicationimp.h"
#include "swsdefine.h"
#include "libsocket\libsocket.h"

using namespace simplews;

SWSListennerImp::SWSListennerImp(int16_t port)
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

SWSListennerImp::~SWSListennerImp() {
	Close();
}

SWSCommunication* SWSListennerImp::WaitConnection(int32_t time) {
	bool result = false;
	
	// Wait to connection from client
	SOCKET communicate_sock = libsocket::LSWaitConnection(listen_sock_, time, NULL, NULL);
	
	// Recieve the handshake message from client
	char handshake_msg[256];
	int32_t real_handshake_msg_length = 0;
	memset(handshake_msg, 0, sizeof(handshake_msg));
	if(communicate_sock != INVALID_SOCKET) {
		real_handshake_msg_length = RecieveHandshakeMsg(communicate_sock, handshake_msg, sizeof(handshake_msg));
		if(real_handshake_msg_length > 0) {

			// Extract the Sec-websocket-key from the handshake buffer
			char sec_websocket_key[24]; // The size of the Sec-websocket-key is 24bytes
			if(ExtractSecWebsocketKey(handshake_msg, real_handshake_msg_length, sec_websocket_key)) {
		
				// Append the GUID to the sec_websocket_key to build the response handshake key string
				char response_handshake_key_plaintext[60]; // The size of the GUID string is 36bytes
				if(AppendGUID(sec_websocket_key, sizeof(sec_websocket_key), response_handshake_key_plaintext)) {

					// Encrypt the plaintext to get ciphertext
					char response_handshake_key_ciphertext[29]; // The size of the ciphertext is 29bytes
					if(Encrypt(response_handshake_key_plaintext, sizeof(response_handshake_key_plaintext),
						response_handshake_key_ciphertext, sizeof(response_handshake_key_ciphertext))) {

						// Build the response handshake message
						char response_handshake_msg[129]; // The size of the response_handshake_msg is 129bytes
						if(BuildResponseHandshakeMsg(response_handshake_key_ciphertext, sizeof(response_handshake_key_ciphertext),
							response_handshake_msg, sizeof(response_handshake_msg))) {

							// Send the response handshake message
							libsocket::LSSendBuffer(communicate_sock, response_handshake_msg, sizeof(response_handshake_msg));

							result = true;
						}
					}
				}
			}			
		}
	}

	SWSCommunication* comm = NULL;
	if(result) {
		// Create the communication
		SWSCommunicationImp* comm_imp = new SWSCommunicationImp();
		comm_imp->AttachSocket(communicate_sock);
		comm = new SWSCommunication(comm_imp);
	} else {
		SWS_SAFE_ASSERT(false); // There is something wrong
	}

	return comm;
}

void SWSListennerImp::Close() {
	libsocket::LSCloseSocket(listen_sock_);
	libsocket::LSCleanupWinSocket();
}

int32_t SWSListennerImp::RecieveHandshakeMsg(SOCKET sock, char* handshake_msg, int32_t len) {
	int32_t real_buffer_length = -1;
	if(sock != INVALID_SOCKET
		&& handshake_msg != NULL) {
		memset(handshake_msg, 0, len);

		// Recieve the origin header, we just ignore this.
		real_buffer_length  = libsocket::LSRecvBuffer(sock, len, handshake_msg);

		// Recieve the handshake from client
		real_buffer_length  = libsocket::LSRecvBuffer(sock, len, handshake_msg);
	}

	return real_buffer_length;
}

bool SWSListennerImp::ExtractSecWebsocketKey(char* handshake_msg, int32_t len, char* sec_websocket_key) {
	bool result = false;
	
	if(handshake_msg != NULL
		&& sec_websocket_key != NULL) {
		char* addr = strstr(handshake_msg, "Sec-WebSocket-Key:");

		if(addr != NULL
			&& len - (addr - handshake_msg) >= 24) {
				memcpy(sec_websocket_key, addr + 19, 24);
				result = true;
		}
	}

	return result;
}

bool SWSListennerImp::AppendGUID(char* sec_websocket_key, int32_t len, char* response_handshake_key_plaintext) {
	bool result = false;

	if(sec_websocket_key != NULL
		&& response_handshake_key_plaintext != NULL) {
			// Copy the Sec-Websocket-Key to the plaintext
			memcpy(response_handshake_key_plaintext, sec_websocket_key, len);
			
			// Append the 258EAFA5-E914-47DA-95CA-C5AB0DC85B11 GUID to the plaintext
			memcpy(response_handshake_key_plaintext + len, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 36);

			result = true;
	}

	return result;
}

bool SWSListennerImp::Encrypt(char* response_handshake_key_plaintext, int32_t plaintext_len,
							  char* response_handshake_key_ciphertext, int32_t ciphertext_len) {
	bool result = false;

	if(response_handshake_key_plaintext != NULL
		&& response_handshake_key_ciphertext != NULL) {
		// Sha1 the sec_key
		SHA1_Code sha1;
		char sha1_result[20];
		sha1.Update(reinterpret_cast<unsigned char*>(response_handshake_key_plaintext), plaintext_len);
		sha1.Final();
		sha1.GetHash(reinterpret_cast<unsigned char*>(sha1_result));

		// Base64 the sec_key
		base64_encode(reinterpret_cast<const unsigned char*>(sha1_result), sizeof(sha1_result), 
			reinterpret_cast<unsigned char*>(response_handshake_key_ciphertext), &ciphertext_len);

		result = true;
	}

	return result;
}

bool SWSListennerImp::BuildResponseHandshakeMsg(char* response_handshake_key_ciphertext, int32_t ciphertext_len,
												char* response_handshake_msg, int32_t handshake_msg_len) {
	bool result = false;

	if(response_handshake_key_ciphertext != NULL
		&& response_handshake_msg != NULL) {
		// Build the response handshake message
		char response_hand_shake_msg_header[] = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ";

		memset(response_handshake_msg, 0, handshake_msg_len);
						
		memcpy(response_handshake_msg, response_hand_shake_msg_header, sizeof(response_hand_shake_msg_header) - 1);
		memcpy(response_handshake_msg + sizeof(response_hand_shake_msg_header) - 1, response_handshake_key_ciphertext, 28);
					
		response_handshake_msg[handshake_msg_len - 4] = '\r';
		response_handshake_msg[handshake_msg_len - 3] = '\n';
		response_handshake_msg[handshake_msg_len - 2] = '\r';
		response_handshake_msg[handshake_msg_len - 1] = '\n';

		result = true;
	}

	return result;
}