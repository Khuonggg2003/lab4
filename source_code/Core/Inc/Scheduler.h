
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#define SCH_MAX_TASKS	40

typedef struct {
	// void pointer to the task
	void (* pTask)(void);
	// Delay until the function will be run
	uint32_t Delay;
	// Period
	uint32_t Period;
	// determine task is execute or not
	uint8_t RunMe;
	// task id
	uint32_t TaskID;
} sTask;
void SCH_Init();

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Add_Task(void(*pFunction)(),
		uint32_t DELAY, uint32_t PERIOD);

void SCH_Delete_Task(uint32_t taskID);

#endif /* INC_SCHEDULER_H_ */
