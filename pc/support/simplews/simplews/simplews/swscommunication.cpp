#include "swscommunication.h"

#include "swscommunicationimp.h"

using namespace simplews;

SWSCommunication::SWSCommunication(SWSCommunicationImp* imp)
	:imp_(imp) {
}

SWSCommunication::~SWSCommunication() {
	SWS_SAFE_DELETE(imp_);
}

int32_t SWSCommunication::SendBuffer(char* buffer, int32_t buffer_size) {
	int32_t result = -1;
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		result = imp_->SendBuffer(buffer, buffer_size);
	}

	return result;
}

int32_t SWSCommunication::RecvBuffer(int32_t buffer_size, char* buffer) {
	int32_t result = -1;
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		result = imp_->RecvBuffer(buffer_size, buffer);
	}

	return result;
}