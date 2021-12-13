#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "ipc.h"

int sClose(int tfd) {
    return close(tfd);
}

int sInit() {
    return socket(PF_UNIX, SOCK_DGRAM, 0);
}

int sConn(int sock_fd, struct sockaddr_un addr) {
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_SOCK_FILE);
    return connect(sock_fd, (struct sockaddr *) &addr, sizeof(addr));
}

int sWrite(int sock_fd, void *buffer) {
    return send(sock_fd, buffer, strlen(buffer), 0);
}

int sRead(int sock_fd, void *buffer, size_t buf_len) {
    return recv(sock_fd, buffer, buf_len, 0);
}

int main() {
    int fd;
    struct sockaddr_un addr;
    int ret;
    const size_t kBufLen = 8192;
    char buff[kBufLen];
    struct sockaddr_un from;
    int ok = 1;
    int len;

    if ((fd = sInit()) < 0) {
        perror("socket");
        ok = 0;
    }

    if (ok) {
        if (sConn(fd, addr) == -1) {
            perror("connect");
            ok = 0;
        }
    }

    if (ok) {
        strcpy(buff, "iccExchangeAPDU");
        if (sWrite(fd, buff) == -1) {
            perror("send");
            ok = 0;
        }
//		if (send(fd, buff, strlen(buff)+1, 0) == -1) {
//			perror("send");
//			ok = 0;
//		}
        printf("sent iccExchangeAPDU\n");
    }

    if (ok) {
        len = sRead(fd, buff, kBufLen);
        if (len < 0) {
            perror("recv");
            ok = 0;
        }
        printf("receive %d %s\n", len, buff);
    }

    sClose(fd);

    return 0;
}
