#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "ipc.h"




int main() {
	int fd;
	struct sockaddr_un addr;
	int ret;
    const size_t kBufLen = 8192;
	char buff[kBufLen];
	struct sockaddr_un from;
	int ok = 1;
    size_t len;
	socklen_t fromlen = sizeof(from);

	if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}

    if (ok) {
        ok = listen(fd, kBufLen);
    }

    if (ok) {
        accept(fd, &addr, sizeof(addr));
    }

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, SERVER_SOCK_FILE);
		unlink(SERVER_SOCK_FILE);
		if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			ok = 0;
		}
	}

    while (1) {
        len = recvfrom(fd, buff, kBufLen, 0, (struct sockaddr *)&from, &fromlen);
        if (len == 0) {
            continue;
        }
        if (len == -1) {
            perror("recvfrom()");
            break;
        }
        printf("buf: %s\n", buff);
		len = sendto(fd, buff, len, 0, (struct sockaddr *)&from, fromlen);
		if (len == -1) {
			perror("sendto");
//			break;
		}
	}


	if (fd >= 0) {
		close(fd);
	}

	return 0;
}
