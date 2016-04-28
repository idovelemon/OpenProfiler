//--------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 04 / 26
// Version: 1.0
// Brief: SWSFramePackager packages and unpackage the websocket frame, so we can send and recieve data easily.
// TODO: Support the Message Fragmentation.
// TODO: Support morn than 125bytes user data.
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
	// @param: user_data
	// @param: user_data_size
	// @param: ws_frame The websocket frame.If you pass NULL, you can get the size of the final websocket frame.
	// @param: ws_frame_size
	// @return: If the user data is valid and successfully package the data, then return true.
	// @note: If the ws_frame_size is smaller than the real websocket frame's size, this method will return false.
	// And do nothing with the ws_frame. 
	// @note: This method only support the 125 bytes user data at most.
	//----------------------------------------------------------------------
	bool PackageUserData(char* user_data, int32_t user_data_size, char* ws_frame, int32_t& ws_frame_size);

	//----------------------------------------------------------------------
	// @brief: This method will unpackage the websocket frame into user data.
	// @param: ws_frame The websocket frame.
	// @param: ws_frame_size The size of the websocket frame.
	// @param: user_data_size If you want to get the final user data's size, you can pass NULL to user_data, and then the result will store in user_data_size.
	// @param: user_data The user data. If you pass NULL, you can get the size of the final user data.
	// @return: If the websocket frame is valid and successfully unpackage the websocket frame, than return true.
	// @note: If the user_data_size is smaller than the real user data's size, this method will return false.
	// And do nothing with the user_data.
	// @note: This method doesn't support fragmentation. It can only deal with one complete websocket frame.
	//----------------------------------------------------------------------
	bool UnPackageWebSocketFrame(char* ws_frame, int32_t ws_frame_size, int32_t& user_data_size, char* user_data);

protected:
	
	// Define the websocket frame according the Websocket protocol v13.
	// More information: http://www.faqs.org/rfcs/rfc6455.html
	struct SWSWebSocketFrame{
		uint8_t fin;
		uint8_t reserve;
		uint8_t opcode;
		uint8_t mask;
		uint8_t len;
		char mask_key[4];
		char* data;
	};

private:
	SWS_DISALLOW_COPY_AND_ASSIGN(SWSFramePackager);
};

}; // namespace simplews
#endif // SWS_SIMPLEWS_SWSFRAMEPACKAGER_H_