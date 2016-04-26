//--------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 26
// Version: 1.0
// Brief: SWSFramePackager packages and unpackage the websocket frame, so we can send and recieve data easily.
//--------------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSFRAMEPACKAGER_H_
#define SWS_SIMPLEWS_SWSFRAMEPACKAGER_H_

#include <stdint.h>

#include "swsdefine.h"

namespace simplews {

class SWSFramePackager{
public:
	SWSFramePackager();
	virtual ~SWSFramePackager();

	//----------------------------------------------------------------------
	// @brief: This method will package the user data into websocket frame buffer.
	// @param: user_data The user data.
	// @param: user_data_size The size of the user data.
	// @param: ws_frame The websocket frame.If you pass NULL, you can get the size of the final websocket frame.
	// @param: ws_frame_size The size of the final websocket frame.
	// @return: If the user data is valid, return true.
	//----------------------------------------------------------------------
	bool PackageUserData(char* user_data, int32_t user_data_size, char* ws_frame, int32_t& ws_frame_size);

	//----------------------------------------------------------------------
	// @brief: This method will unpackage the websocket frame into user data.
	// @param: ws_frame The websocket frame.
	// @param: ws_frame_size The size of the websocket frame.
	// @param: user_data The user data. If you pass NULL, you can get the size of the final user data.
	// @param: user_data_size The size of the final user data.
	// @return: If the websocket frame is valid, return true.
	//----------------------------------------------------------------------
	bool UnPackageWebSocketFrame(char* ws_frame, int32_t ws_frame_size, char* user_data, int32_t& user_data_size);

protected:
	
	// Define the websocket frame according the Websocket protocol v13.
	// More information: http://www.faqs.org/rfcs/rfc6455.html
	struct SWSWebSocketFrame{
		int8_t fin:1;
		int8_t reserve:3;
		int8_t opcode:4;
		int8_t mask:1;
		int8_t len:7;
		int64_t extend_len;
		char mask_key[4];
		char* data;
	};

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSFramePackager);
};

}; // namespace simplews
#endif // SWS_SIMPLEWS_SWSFRAMEPACKAGER_H_