#include "swscommunication.h"

#include "swsframepackager.h"

using namespace simplews;

SWSCommunication::SWSCommunication()
	:communicate_sock_(INVALID_SOCKET) {
}

SWSCommunication::~SWSCommunication() {
	closesocket(INVALID_SOCKET);
}

void SWSCommunication::AttachSocket(SOCKET communicate_sock) {
	if(communicate_sock_ != INVALID_SOCKET) {
		closesocket(communicate_sock_);
		communicate_sock_ = INVALID_SOCKET;
	}

	communicate_sock_ = communicate_sock;
}

void SWSCommunication::DetachSocket() {
	closesocket(communicate_sock_);
	communicate_sock_ = NULL;
}

void SWSCommunication::SendBuffer(char* buffer, int32_t buffer_size) {
	SWS_SAFE_ASSERT(buffer != NULL && buffer_size > 0);
	if(buffer != NULL
		&& buffer_size > 0 ) {
			SWSFramePackager packager;
			int32_t ws_frame_size = 0;

			// Get the final websocket frame buffer's size
			packager.PackageUserData(buffer, buffer_size, NULL, ws_frame_size);

			// Package the user data into websocket frame
			char* ws_frame = new char[ws_frame_size];
			packager.PackageUserData(buffer, buffer_size, ws_frame, ws_frame_size);

			// Send the websocket frame
			send(communicate_sock_, ws_frame, ws_frame_size, 0);
			
			delete[] ws_frame;
			ws_frame = NULL;
	}
}

int32_t SWSCommunication::RecvBuffer(int32_t buffer_size, char* buffer) {
	int32_t len = 0;

	SWS_SAFE_ASSERT(buffer_size > 0 && buffer != NULL);
	if(buffer_size > 0
		&& buffer != NULL) {
			// Recieve websocket frame
			char ws_frame_buffer[1024];
			int32_t real_size_ws_frame = recv(communicate_sock_, ws_frame_buffer, sizeof(ws_frame_buffer), 0);

			// Get user data's size
			SWSFramePackager packager;
			packager.UnPackageWebSocketFrame(ws_frame_buffer, real_size_ws_frame, NULL, len);

			// TODO:
	}
	
	return len;
}