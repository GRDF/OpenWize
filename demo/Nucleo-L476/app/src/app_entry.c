
#ifdef __cplusplus
extern "C" {
#endif

#include "app_entry.h"

extern void Sys_Init(void);
extern void Sys_Start(void);

void App_Init(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
void app_entry(void)
{
  	Sys_Init();
  	App_Init();
  	Sys_Start();
}

/******************************************************************************/
void* hTask;
static void Main_Task(void const * argument);
#define APP_TASK_NAME main
#define APP_TASK_FCT Main_Task
#define APP_STACK_SIZE 300
#define APP_PRIORITY (UBaseType_t)(tskIDLE_PRIORITY+1)
SYS_TASK_CREATE_DEF(main, APP_STACK_SIZE, APP_PRIORITY);

void App_Init(void)
{
	hTask = SYS_TASK_CREATE_CALL(main, APP_TASK_FCT, NULL);
}

static void Main_Task(void const * argument)
{
	(void)argument;

	uint8_t i;
	uint8_t pData[50];
	uint8_t u8Size;

	// Set the L6App
	pData[0] = 0x05;
	// Set the rest of the message
	strncpy(&pData[1], "Hello World!", 50);
	u8Size = strlen( (char*)pData) ;

	i = 0;
	while(1)
	{
		LOG_INF("---------- \n");
		switch(i)
		{
			case 0:
				LOG_INF("Main Install\n");
				WizeApi_ExecPing();
				break;
			default :
				LOG_INF("Main Data %d\n", i);
				WizeApi_SendEx(pData, u8Size, APP_DATA);
				break;
		}
		i++;
		if(i > 9) {i = 0;}
		msleep(2000);
	}
}
/******************************************************************************/

#ifdef __cplusplus
}
#endif
