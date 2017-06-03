/*
 *  Chuong trinh chua cac ham de khoi tao module ESP8266
 *  Cac ham xu ly du lieu nhan duoc tu ESP
 *  Cac ham gui du lieu thong qua ESP
 */

#include "MyLibrary/include.h"
#include "main.h"

/* CHUONG TRINH KHOI TAO MODULE WIFI ESP8266 */
void InitESP8266(void)
{	
    SendRecvATCommand("AT", "OK", 1000, true);
    SendRecvATCommand("AT+RST", "invalid", 5000, true);
    SendRecvATCommand("AT+CWMODE=1", "OK", 1000, true);
    //SendRecvATCommand("AT+CWJAP=\"BMDT\",\"PTN@203B3\"", "OK", 10000, true);
    //SendRecvATCommand("AT+CWJAP=\"Red Tea House\",\"khongcowifi\"", "OK", 10000, true);
    //SendRecvATCommand("AT+CWSAP=\"ESP8266\",\"11000011\",1,0", "OK", 10000, true);
    //SendRecvATCommand("AT+CWJAP=\"Miracle\",\"01203284600\"", "OK", 10000, true);
    SendRecvATCommand("AT+CWJAP=\"GALAXY\",\"11223344\"", "OK", 10000, true);
    SendRecvATCommand("AT+CIPSTA=\"192.168.1.167\"", "OK", 10000, true);
    SendRecvATCommand("AT+CIPMUX=1", "OK", 1000, true);
    SendRecvATCommand("AT+CIPSERVER=1,80", "OK", 1000, true);
    SendRecvATCommand("AT+CIPSTO=1", "OK", 1000, true);
    SendRecvATCommand("AT+CIFSR", "OK", 1000, true);
}

/******************************************************************************************************/


/* CHUONG TRINH GUI LENH AT COMMAND VA NHAN PHAN HOI TU MODULE WIFI */
void SendATCommand(char *cmd)
{
    while (UARTBusy(UART1_BASE));
    while (*cmd != '\0')
    {
        UARTCharPut(UART1_BASE, *cmd++);
    }
    UARTCharPut(UART1_BASE, '\r'); //<CR>
    UARTCharPut(UART1_BASE, '\n'); //<LF>
}

/******************************************************************************************************/


/* CHUONG TRINH NHAN PHAN HOI TU MODULE ESP8266 SAU KHI GUI LENH AT COMMAND */
void ReceiveResponse(char *target, char *data, unsigned long timeout, bool check)
{
    unsigned long start = millis();
    char a;
    int i = 0;
    while (start + timeout > millis())
    {
        while (UARTCharsAvail(UART1_BASE))
        {
            a = UARTCharGet(UART1_BASE);
            UARTCharPut(UART0_BASE, a);			/* Kiem tra */
            if (a == '\0')  continue;
            data[i] = a;
            i++;
        }
        if (check)
        {
            if (FindString(data, target) != -1)
                break;
        }
    }
}

/******************************************************************************************************/


/* CHUONG TRINH GUI LENH AT COMMAND VA NHAN PHAN HOI KIEM TRA */
void SendRecvATCommand(char *ATcmd, char *target, unsigned long timeout, bool check)
{
    memset(ReceivedData, 0, sizeof(ReceivedData));
    SendATCommand(ATcmd);
    unsigned long start = millis();
    while (start + 20000 > millis())
    //while (1)
    {
        ReceiveResponse(target, ReceivedData, timeout, check);
        if (check == false)
            break;
        if (FindString(ReceivedData, target) != -1)
            break;
    }
    SendString("\r\n");
}

/******************************************************************************************************/


/* GUI THIET LAP TRANG WEB */
void SendHtml(char *response)
{
    /* Thiet lap lenh CIPSEND */
    char cipsend[] = "AT+CIPSEND=0,";
    char lengthstr[4];
    int length = strlen(response);
    itoa(length, lengthstr);
    strcat(cipsend, lengthstr);
    /**********************************************/
    SendATCommand(cipsend); //Gui AT+CIPSEND
    DelayMS(50);
    while (UARTBusy(UART1_BASE));
    while (*response != '\0')
    {
        UARTCharPut(UART1_BASE, *response);
        *response++;
    }
    memset(ReceivedData, 0, sizeof(ReceivedData));
    ReceiveResponse("SEND OK", ReceivedData, 1000, true);
    SendString("\r\n");
    SendRecvATCommand("AT+CIPCLOSE=0", "OK", 1000, true);
}

/******************************************************************************************************/


/* GUI DU LIEU QUA UART 1 */
void ESPWrite(char *str)
{
    while (UARTBusy(UART1_BASE));
    while (*str != '\0')
    {
        UARTCharPut(UART1_BASE, *str);
        *str++;
    }
}

/******************************************************************************************************/
