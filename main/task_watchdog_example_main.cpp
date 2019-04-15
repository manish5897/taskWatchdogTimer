#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include <esp_task_wdt.h>
#include <stdio.h>
#include <stdint.h>

extern "C"
{
	void app_main(void);
}

#define WATCHDOG_TIMEOUT_S 5

/*As we know this task takes max 5sec to execute
* If it takes more than 5sec, that means
* Task is stuck somewhere in infinte loop
* So, we define the TASK WATCHDOG TIMEOUT as 5sec
* The system will restart, after the timeout
* as enable the panic of watchdog timer
*/
void myTask(void *myData)
{

	printf("# Registering our new task with the task watchdog.\n");
	esp_task_wdt_add(NULL);

	while (1)
	{

		for (int i = 0; i < 5; i++)
		{
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			printf("Tick :%d\n", i);
		}

		printf("# Our current task priority is %d.\n", uxTaskPriorityGet(NULL));
		esp_task_wdt_reset();

		printf("# Removing our watchdog registration before we end the task.\n");
		esp_task_wdt_delete(NULL);
	}
	vTaskDelete(NULL);
}

void app_main(void)
{

	printf("App starting\n");
	printf("Initializing the task watchdog subsystem with an interval of 4 seconds.\n");

	// task watchdog timer timeout of 5sec
	esp_task_wdt_init(WATCHDOG_TIMEOUT_S, true);

	printf("Creatign a new task.\n");

	xTaskCreate(myTask,	// Task code
				"My Task", // Name of task
				2048,	  // Stack size
				NULL,	  // Task data
				1,		   // Priority
				NULL	   // task handle
	);
}
