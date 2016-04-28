#include <stdio.h>

#include "simplews.h"

int main() {
	simplews::SWSServer server(4567);
	simplews::SWSCommunication* com = server.WaitConnection(0);
	char buffer[1204];
	int32_t len = com->RecvBuffer(sizeof(buffer), buffer);
	buffer[len] = 0;
	printf(buffer);

	com->SendBuffer(buffer, len+1);

	printf("Exit");
	system("pause");
	return 0;
}