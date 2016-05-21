#include "swsframepackager.h"

#include <memory>

using namespace simplews;

const int32_t SWS_WEBSOCKET_FRAME_HEADER_SIZE = 2;
const int32_t SWS_WEBSOCKET_FRAME_MAX_LEN = 125;

SWSFramePackager::SWSFramePackager() {
}

SWSFramePackager::~SWSFramePackager() {
}

bool SWSFramePackager::PackageUserData(char* user_data, int32_t user_data_size, char* ws_frame, int32_t& ws_frame_size) {
	bool result = false;

	if(user_data != NULL
		&& user_data_size > 0) {
			int32_t real_len = SWS_WEBSOCKET_FRAME_HEADER_SIZE + user_data_size; // The websocket frame's header is 6 bytes.
			ws_frame_size = real_len;

			if(ws_frame_size <= SWS_WEBSOCKET_FRAME_MAX_LEN) {
				result = true;

				if(ws_frame != NULL) {
					char* frame = new char[ws_frame_size];
					memset(frame, 0, ws_frame_size);

					frame[0] = static_cast<char>(0x81);
					frame[1] = user_data_size;
					memcpy(frame+2, user_data, user_data_size);

					int32_t real_copy_len = 0;
					if(ws_frame_size > SWS_WEBSOCKET_FRAME_MAX_LEN) {
						real_copy_len = SWS_WEBSOCKET_FRAME_MAX_LEN;
					} else {
						real_copy_len = ws_frame_size;
					}

					memcpy(ws_frame, frame, real_copy_len);
					delete[] frame;
					frame = NULL;

					ws_frame_size = real_copy_len;
				}
			}
	}

	return result;
}

bool SWSFramePackager::UnPackageWebSocketFrame(char* ws_frame, int32_t ws_frame_size
																						,int32_t& user_data_size, char* user_data) {
	bool result = false;

	if(ws_frame != NULL
		&& ws_frame_size > 0) {

		// Copy the websocket frame header
		SWSWebSocketFrame frame;
		memset(&frame, 0, sizeof(frame));
		frame.fin = ((uint8_t)ws_frame[0]) >> 7;
		frame.reserve = 0;
		frame.opcode = ws_frame[0] & 0x0f;
		frame.mask = ((uint8_t)ws_frame[1]) >> 7;
		frame.len = ws_frame[1] & 0x7f;
		memcpy(frame.mask_key, ws_frame+2, sizeof(frame.mask_key));

		// Save the length of the user data
		user_data_size = frame.len;

		// Read the data
		if(user_data == NULL) {
			result = false;
		} else {
			
			int32_t copy_len = 0;
			if(frame.len < user_data_size) {
				copy_len = frame.len;
			} else {
				copy_len = user_data_size;
			}
			memcpy(user_data, ws_frame + 6, copy_len);
			
			// Unmasking the data
			for(int32_t i = 0; i < copy_len; i++) {
				user_data[i] = user_data[i] ^ ((uint8_t)frame.mask_key[i % 4]);
			}

			result = true;
			user_data_size = copy_len;
		}
	}

	return result;
}