#include "swscommunicationimp.h"

#include "swsframepackager.h"

using namespace simplews;

SWSCommunicationImp::SWSCommunicationImp()
	:communicate_sock_(INVALID_SOCKET) {
}

SWSCommunicationImp::~SWSCommunicationImp() {
	closesocket(INVALID_SOCKET);
}

void SWSCommunicationImp::AttachSocket(SOCKET communicate_sock) {
	if(communicate_sock_ != INVALID_SOCKET) {
		closesocket(communicate_sock_);
		communicate_sock_ = INVALID_SOCKET;
	}

	communicate_sock_ = communicate_sock;
}

void SWSCommunicationImp::DetachSocket() {
	closesocket(communicate_sock_);
	communicate_sock_ = NULL;
}

int32_t SWSCommunicationImp::SendBuffer(char* buffer, int32_t buffer_size) {
	
	int32_t len = -1;

	SWS_SAFE_ASSERT(buffer != NULL && buffer_size > 0);
	if(buffer != NULL
		&& buffer_size > 0 ) {
			SWSFramePackager packager;
			int32_t ws_frame_size = 0;

			// Get the final websocket frame buffer's size
			packager.PackageUserData(buffer, buffer_size, NULL, ws_frame_size);

			// Package the user data into websocket frame
			char* ws_frame = new char[ws_frame_size];
			memset(ws_frame, 0, ws_frame_size);

			if(packager.PackageUserData(buffer, buffer_size, ws_frame, ws_frame_size)) {
				// Send the websocket frame
				len = send(communicate_sock_, ws_frame, ws_frame_size, 0);
			
				delete[] ws_frame;
				ws_frame = NULL;
			}
	}

	return len;
}

int32_t SWSCommunicationImp::RecvBuffer(int32_t buffer_size, char* buffer) {
	int32_t len = -1;

	SWS_SAFE_ASSERT(buffer_size > 0 && buffer != NULL);
	if(buffer_size > 0
		&& buffer != NULL) {
			// Recieve websocket frame
			char ws_frame_buffer[1024];
			memset(ws_frame_buffer, 0, sizeof(ws_frame_buffer));
			int32_t real_size_ws_frame = recv(communicate_sock_, ws_frame_buffer, sizeof(ws_frame_buffer), 0);

			// Get user data's size
			SWSFramePackager packager;
			packager.UnPackageWebSocketFrame(ws_frame_buffer, real_size_ws_frame, len, NULL);
				
			// Allocate memory
			char* user_data = new char[len];
			if(packager.UnPackageWebSocketFrame(ws_frame_buffer, real_size_ws_frame, len, user_data)) {
					
				// Copy to output buffer
				int32_t copy_len = 0;
				if(buffer_size < len) {
					copy_len = buffer_size;
				} else {
					copy_len = len;
				}
				memcpy(buffer, user_data, copy_len);

				delete[] user_data;
				user_data = NULL;

				len = copy_len;
			}
	}
	
	return len;
}