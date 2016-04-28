#include "swsserver.h"

#include "swscommunication.h"
#include "swsserverimp.h"

using namespace simplews;

SWSServer::SWSServer(int16_t port)
	:imp_(new SWSServerImp(port)) {
}

SWSServer::~SWSServer() {
	SWS_SAFE_DELETE(imp_);
}

SWSCommunication* SWSServer::WaitConnection(int32_t time) {
	SWSCommunication* communication = NULL;
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		communication = imp_->WaitConnection(time);
	}

	return communication;
}

void SWSServer::Close() {
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		imp_->Close();
	}
}