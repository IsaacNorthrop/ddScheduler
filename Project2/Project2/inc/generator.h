#include ../inc/testBench.h
#include ../inc/FreeRTOSConfig.h
#include userDefined.h


void Gen1(void *taskParameters);
void Gen2(void *taskParameters);
void Gen3(void *taskParameters);

void createDDTask (void *task);
