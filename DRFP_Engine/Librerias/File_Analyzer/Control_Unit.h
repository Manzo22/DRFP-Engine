#ifndef CONTROL_UNIT
#define CONTROL_UNIT

#include "../Variables_Globales.h"

void VerificarGrupos();
Scenario_Type IdentificarEscenario();
void CU_Set_IDENT(char temp[6]);
void CU_Set_GUN(uint8_t temp);
void CU_Set_FC(uint8_t temp);
void CU_Set_NumDL(uint8_t temp);
void CU_Set_INT_TIME(uint16_t temp);
void CU_Set_T_TIME(float temp);
void CU_Set_Meko_Type(uint16_t temp);
void CU_Set_Scenario(Scenario_Type temp);
void CU_Get_IDENT(char* temp);
void CU_Set_Num_Samples(uint16_t temp);
uint8_t CU_Get_FC();
uint8_t CU_Get_GUN();
Scenario_Type CU_Get_SCN();
float CU_Get_Total_Run_Time();
uint16_t CU_Get_INTERV_TIME();
uint8_t CU_Get_NumDL();
uint16_t CU_Get_Meko_Type();
uint16_t CU_Get_Num_Samples();

#endif // CONTROL_UNIT
