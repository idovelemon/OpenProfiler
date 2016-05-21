//-----------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[132600812@qq.com]
// Date: 2016 / 04 / 24
// Version: 1.0
// Brief: Define some marco and method.
//-----------------------------------------------------------------------------------------
#ifndef SWS_SIMPLEWS_SWSDEFINE_H_
#define SWS_SIMPLEWS_SWSDEFINE_H_

#include <assert.h>

#define SWS_SAFE_DELETE(Pointer) \
	do{ \
		if(Pointer != NULL) { \
			delete Pointer; \
			Pointer = NULL; \
		} \
	}while(false)

#define SWS_SAFE_ASSERT(Expression) \
	do{ \
		bool result = Expression; \
		assert(result); \
	}while(false)

#define SWS_DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)

#endif // SWS_SIMPLEWS_SWSDEFINE_H_