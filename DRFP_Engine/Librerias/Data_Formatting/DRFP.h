#ifndef DRFP
#define DRFP

#include "../Variables_Globales.h"


//Tabla de Conversiones
#define Y               59.9261184
#define MBAR            4194.304
#define DEG             46603.37778
#define RAD             2670170.614
#define SEG             65536
#define YpS             3835.9261184
#define MpS             4194.304
#define mil             2621.44
#define DEGC            41943.04
#define Porc            41943.04
#define KTS             2157.736334
#define FT              19.9753728
#define SMI_IPXY        32768
#define SMI_IPconv      139.983
#define SMI_TTEZ        128
#define SMI_TTI         131072
#define Y_DHC           14.9815296

//void setIdent(char str[6]);
void setInter(uint16_t interv);
//void setFC(uint8_t FC_temp);
//void setGUN(uint8_t GUN_temp);
void setDuracion(uint16_t var);

Status_Return GrupoPRE();
Status_Return GrupoNGS();
Status_Return GrupoOSD();
Status_Return GrupoSEN();
Status_Return GrupoGUN();
Status_Return GrupoGEN();
Status_Return GrupoSMI();
Status_Return GrupoSMC();
Status_Return GrupoSSM();

void GrupoTOR();
void GrupoACP();
void GrupoVPD();
void GrupoACO();
void GrupoDEP();
void GrupoSTA();
void GrupoCPA();
void GrupoVTD();
void GrupoTRK();

#endif // DRFP
