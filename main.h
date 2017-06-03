#ifndef MAIN_H_
#define MAIN_H_

#include "MyLibrary/include.h"
#include "MyLibrary/init.h"
#include "MyLibrary/strings.h"
#include "MyLibrary/time.h"
#include "MyLibrary/web.h"
#include "ESP8266.h"

extern void InitProgram(void);
extern void ProcessCommand(char *CommandText);
extern void ResponseXML(void);
extern void SetGPIO(void);
extern void InitButtonISR(void);

#endif /* MAIN_H_ */
