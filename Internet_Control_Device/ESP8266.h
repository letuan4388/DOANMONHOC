#ifndef ESP8266_H_
#define ESP8266_H_

static char ReceivedData[100];

extern void InitESP8266(void);
extern void SendATCommand(char *cmd);
extern void ReceiveResponse(char *target, char *data, unsigned long timeout, bool check);
extern void SendRecvATCommand(char *ATcmd, char *target, unsigned long timeout, bool check);
extern void SendHtml(char *response);
extern void ESPWrite(char *str);

#endif /* ESP8266_H_ */
