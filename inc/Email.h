#include <winsock2.h>

class Email {
private:
    char sendBuf[BUFSIZ], recBuf[BUFSIZ], recMail[BUFSIZ], subject[BUFSIZ], content[BUFSIZ],
    sendMail[BUFSIZ], pass[BUFSIZ];
    char *pstr = NULL;
    const char *host = "smtp.163.com";
    int port = 25;
    SOCKET sock;
    char dppsw[20];
public:
    void disconnect(SOCKET sock);
    void sendMsg(SOCKET sock, char *msg);
    void recMsg(SOCKET sock);
    void setDppsw(int code);
    int getDppsw();
    char* base64_encode(const char* data, int len);
    SOCKET connectServer(const char *host, int port);
    void sendTo();
    Email(char *);
};