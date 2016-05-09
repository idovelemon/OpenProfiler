#include "swslistenner.h"

#include "swscommunication.h"
#include "swslistennerimp.h"

using namespace simplews;

SWSListenner::SWSListenner(int16_t port)
	:imp_(new SWSListennerImp(port)) {
}

SWSListenner::~SWSListenner() {
	SWS_SAFE_DELETE(imp_);
}

SWSCommunication* SWSListenner::WaitConnection(int32_t time) {
	SWSCommunication* communication = NULL;
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		communication = imp_->WaitConnection(time);
	}

	return communication;
}

void SWSListenner::Close() {
	SWS_SAFE_ASSERT(imp_ != NULL);
	if(imp_ != NULL) {
		imp_->Close();
	}
}