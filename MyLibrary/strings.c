#include "include.h"

/* CHUONG TRINH TIM CHUOI "STR" TRONG CHUOI "SRC" */
int FindString(char src[], char str[])
{
    int i = 0, j = 0, location;
    while (src[i] != '\0')
    {
        while (src[i] != str[0] && src[i] != '\0')
            i++;
        if (src[i] == '\0')
            return (-1);
        location = i;
        while (src[i] == str[j] && src[i] != '\0' && str[j] != '\0')
        {
            i++;
            j++;
        }
        if (str[j] == '\0')
            return (location);
        if (src[i] == '\0')
            return (-1);
        i = location + 1;
        j = 0;
    }
    return (-1);
}

/******************************************************************************************************/


/* CHUONG TRINH GUI CHUOI "data" RA HERCULES */
void SendString(char *data)
{
    while (UARTBusy(UART0_BASE));
    while (*data != '\0')
    {
        UARTCharPut(UART0_BASE, *data);
        *data++;
    }
    UARTCharPut(UART0_BASE, '\r');
    UARTCharPut(UART0_BASE, '\n');
}

/******************************************************************************************************/


/* CHUONG TRINH DOI SO THANH CHUOI */
char* itoa(int i, char strnum[])
{
    char digit[] = "0123456789";
    char *p = strnum;
    int j = i;
    while (j)
    {
        *p++;
        j /= 10;
    }
    *p = '\0';
    while (i)
    {
        *--p = digit[i%10];
        i /= 10;
    }
    return (strnum);
}

/******************************************************************************************************/
