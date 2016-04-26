#include "simplews.h"

int main() {
	simplews::SWSServer server(4567);
	simplews::SWSCommunication* com = server.WaitConnection(0);
	return 0;
}