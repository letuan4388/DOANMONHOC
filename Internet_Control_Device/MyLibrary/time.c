#include "include.h"

static unsigned long MicroSecond = 0;

/* CHUONG TRINH NGAT TIMER0 */
void Timer0IntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MicroSecond++;
}

/******************************************************************************************************/


/* HAM TRA VE THOI GIAN CHAY CHUONG TRINH */
unsigned long millis(void)
{
    return MicroSecond;
}

/******************************************************************************************************/


/* HAM DELAY MILIS GIAY */
void DelayMS(int time)
{
    SysCtlDelay(80000 * time / 3);
}
