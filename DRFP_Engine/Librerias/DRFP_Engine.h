#ifndef DRFP_Engine
#define DRFP_Engine

#include "Variables_Globales.h"

Status_Return DRFP_Engine_Init(char *dir_Copycass, uint8_t *AppendNum, InfoAppend InfoRet[20]);

void DE_Get_IDENT(char* temp);
uint8_t DE_Get_FC();
uint8_t DE_Get_GUN();
Scenario_Type DE_Get_SCN();
float DE_Get_Total_Run_Time();
uint16_t DE_Get_INTERV_TIME();
uint8_t DE_Get_NumDL();
uint16_t DE_Get_Meko_Type();

#endif // DRFP_Engine
