/*
 * Do an mon hoc nganh dien tu (EE3151)
 * De tai: DIEU KHIEN THIET BI QUA INTERNET
 */

#include "main.h"

int main(void)
{
    InitProgram();
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
    char c;
    int i = 0;
    memset(ReceivedData, 0, sizeof(ReceivedData));
    while (true)
    {
        while (true)
        {
            if (UARTCharsAvail(UART1_BASE))
            {
                c = UARTCharGet(UART1_BASE);
                if (c == '\0') continue;
                UARTCharPut(UART0_BASE, c);
                ReceivedData[i] = c;
                if (i < 100)
                    i++;
                else i = 0;
            }
            if (FindString(ReceivedData, "HTTP") != -1)
            {
                if (FindString(ReceivedData, "GET / HTTP") != -1)
                    SendHtml(website);
                else
                {
                    ProcessCommand(ReceivedData);
                    SetGPIO();
                    ResponseXML();
                }
                break;
            }
        }
        i = 0;
        memset(ReceivedData, 0, sizeof(ReceivedData));
        DelayMS(100);
    }
}
/********************************************************************************/


/* CHUONG TRINH XU LY DU LIEU TU WEB */
void ProcessCommand(char *CommandText)
{
    if (FindString(CommandText, "GPIO1") != -1)
    {
        GPIO1_STATE = 1 - GPIO1_STATE;
    }
    if (FindString(CommandText, "GPIO2") != -1)
    {
        GPIO2_STATE = 1 - GPIO2_STATE;
    }
}

/* CHUONG TRINH GUI PHAN HOI LAI YEU CAU TU CLIENT */
void ResponseXML(void)
{
    SendATCommand("AT+CIPSEND=0,119");
    DelayMS(50);
    ESPWrite("<?xml version='1.0' encoding='utf-8'?>");   //38 ky tu
    ESPWrite("<inputs>");             //8
    if (GPIO1_STATE)
        ESPWrite("<GPIO>THIET BI 1 DANG BAT</GPIO>");    //32
    else
        ESPWrite("<GPIO>THIET BI 1 DANG TAT</GPIO>");
    if (GPIO2_STATE)
        ESPWrite("<GPIO>THIET BI 2 DANG BAT</GPIO>");    //32
    else
        ESPWrite("<GPIO>THIET BI 2 DANG TAT</GPIO>");
    //ESPWrite("<GPIO>NHIET DO HIEN TAI LA 20 DO</GPIO>");       //39
    ESPWrite("</inputs>");            //9
    memset(ReceivedData, 0, sizeof(ReceivedData));
    ReceiveResponse("SEND OK", ReceivedData, 1000, true);
    SendString("\r\n");             // Kiem tra
    SendRecvATCommand("AT+CIPCLOSE=0", "OK", 1000, true);
}

/*
 * CHUONG TRINH BAT TAT ROLE
 * Neu STATE = 1 thi ROLE duoc BAT
 * Neu STATE = 0 thi ROLE TAT
 */
void SetGPIO(void)
{
    if (GPIO1_STATE)
    {
        //GPIOPinWrite(GPIO_PORT, GPIO1, GPIO1);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO1, GPIO1);
    }
    else
    {
        //GPIOPinWrite(GPIO_PORT, GPIO1, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO1, 0);
    }
    //
    if (GPIO2_STATE)
    {
        //GPIOPinWrite(GPIO_PORT, GPIO2, GPIO2);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO2, GPIO2);
    }
    else
    {
        //GPIOPinWrite(GPIO_PORT, GPIO2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO2, 0);
    }
}

/*
 * HAM KHOI TAO CHUONG TRINH
 */
void InitProgram(void)
{
    // Khoi tao clock he thong
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    // Khoi tao he thong
    InitUART0();        // Khoi tao UART0
    InitUART1();        // Khoi tao UART1
    InitTimer0();       // Khoi tao ngat TIMER0
    InitESP8266();      // Khoi tao ESP8266 V1
    InitLED();          // Khoi tao LED
    InitButton();       // Khoi tao nut nhan
    InitButtonISR();    // Khoi tao ngat nut nhan
    // Thong bao ket noi thanh cong
    SendString("Connected \r\n");/*
    GPIOPinWrite(GPIO_PORT, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 14);
    DelayMS(1000);
    GPIOPinWrite(GPIO_PORT, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);*/
}

void ButtonISR(void)
{
    GPIOIntClear(GPIO_PORT, SW1 | SW2);
    uint32_t value = GPIOPinRead(GPIO_PORT, SW1 | SW2);
    if ((value & SW1) == 0)
    {
        GPIO1_STATE = 1 - GPIO1_STATE;
    }
    if ((value & SW2) == 0)
    {
        GPIO2_STATE = 1 - GPIO2_STATE;
    }
    SetGPIO();
}

void ButtonDISR(void)
{
    GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    uint32_t value = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    if ((value & GPIO_PIN_6) == 0)
    {
        GPIO1_STATE = 1 - GPIO1_STATE;
    }
    if ((value & GPIO_PIN_7) == 0)
    {
        GPIO2_STATE = 1 - GPIO2_STATE;
    }
    SetGPIO();
    DelayMS(50);
}

void InitButtonISR(void)
{/*
    GPIOIntTypeSet(GPIO_PORT, SW1 | SW2, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORT, &ButtonISR);
    GPIOIntEnable(GPIO_PORT, SW1 | SW2);
    IntEnable(INT_GPIOF);
    IntMasterEnable();*/
        /////
    GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTD_BASE, &ButtonDISR);
    GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    IntEnable(INT_GPIOD);
    IntMasterEnable();
}

