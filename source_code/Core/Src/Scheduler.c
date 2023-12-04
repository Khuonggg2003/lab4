
#include "Scheduler.h"

uint32_t current_task_index;
sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(){
	current_task_index = 0;
}

void SCH_Update(void){
	if(SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0 && SCH_tasks_G[0].Delay-- == 0){
		SCH_tasks_G[0].RunMe = 1;
	}
}


void SCH_Dispatch_Tasks(void){
	if(SCH_tasks_G[0].RunMe > 0){
		// Run the task
		(*SCH_tasks_G[0].pTask)();

		// Store function and period of this task
		void(*pFunction)() = SCH_tasks_G[0].pTask;
		uint32_t period = SCH_tasks_G[0].Period;

		// Rearrange the task in the queue
		SCH_Delete_Task(0);
		SCH_Add_Task(pFunction, period, period);
	}
}
void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    if (current_task_index >= SCH_MAX_TASKS || PERIOD == 0) {
        return; // Do not accept one-shot tasks
    }

    uint32_t i = 0;
    while (DELAY >= SCH_tasks_G[i].Delay && i < current_task_index) {
        DELAY -= SCH_tasks_G[i].Delay;
        i++;
    }

    if (i != current_task_index) {
        for (uint32_t idx = current_task_index; idx > i; idx--) {
            SCH_tasks_G[idx] = SCH_tasks_G[idx - 1]; // Shift tasks to make space for the new task
            SCH_tasks_G[idx].TaskID = idx;
        }
        SCH_tasks_G[i + 1].Delay -= DELAY; // Update delay time of the next task
    }

    SCH_tasks_G[i].pTask = pFunction;
    SCH_tasks_G[i].Delay = DELAY;
    SCH_tasks_G[i].Period = PERIOD;
    SCH_tasks_G[i].RunMe = 0;
    SCH_tasks_G[i].TaskID = i;
    current_task_index++;
}

void SCH_Delete_Task(uint32_t taskID) {
    for (uint32_t i = taskID; i < current_task_index - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1]; // Shift tasks to fill the deleted task's position
        SCH_tasks_G[i].TaskID = i;
    }
    current_task_index--;
}

