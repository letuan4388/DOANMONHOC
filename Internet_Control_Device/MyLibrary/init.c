	/*
 *  Chuong trinh chua cac ham khoi tao he thong
 */

#include "include.h"

/* CHUONG TRINH KHOI TAO UART 0
 * HIEN THI KIEM TRA LEN MAN HINH TERMINAL
 */
void InitUART0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, LED | GPIO1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

/******************************************************************************************************/


/* CHUONG TRINH KHOI TAO UART 1
 * UART 1 KET NOI VOI MODULE WIFI ESP8266
 */
void InitUART1(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, LED | GPIO1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    UARTConfigSetExpClk(UART1_BASE, 16000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    UARTEnable(UART1_BASE);
}

/******************************************************************************************************/


/* CHUONG TRINH KHOI TAO NGAT TIMER 0
 * NGAT TIMER DUNG DE DEM THOI GIAN CHAY CUA CHUONG TRINH
 */
void InitTimer0(void)
{
    int value;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    value = (SysCtlClockGet() / 1000) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, value - 1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);
}

/******************************************************************************************************/


/* CHUONG TRINH KHOI TAO LED
 * LED DUNG DE KIEM TRA XEM CAC ROLE CO DUOC BAT HAY KHONG TU WEB
 */
void InitLED(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, LED | GPIO1 | GPIO2);
    GPIOPinWrite(GPIO_PORTD_BASE, LED | GPIO1 | GPIO2, 0);
}

/******************************************************************************************************/


/* CHUONG TRINH KHOI TAO NUT NHAN
 * NUT NHAN DUNG DE BAT TAT CAC ROLE
 */
void InitButton(void)
{
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = SW2;
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, SW1 | SW2);
    GPIOPadConfigSet(GPIO_PORTD_BASE, SW1 | SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
