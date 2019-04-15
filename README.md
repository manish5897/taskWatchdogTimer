# taskWatchdogTimer
The ESP-IDF has support for two types of watchdogs: The Interrupt Watchdog Timer and the Task Watchdog Timer (TWDT). The Interrupt Watchdog Timer and the TWDT can both be enabled using make menuconfig, however the TWDT can also be enabled during runtime. The Interrupt Watchdog is responsible for detecting instances where FreeRTOS task switching is blocked for a prolonged period of time. The TWDT is responsible for detecting instances of tasks running without yielding for a prolonged period.


# Test:
change "#define WATCHDOG_TIMEOUT_S 5" to "#define WATCHDOG_TIMEOUT_S 4"
changing the timeout of 5sec to 4sec
As Task takes 5sec, if watchdog timeout is 4sec, then system will restart aftertimeout
