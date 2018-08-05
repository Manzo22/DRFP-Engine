#ifndef VAR_GLOB
#define VAR_GLOB

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

typedef enum {
    Ret_OK                  = 0,
    Ret_Scn_Incompatible    = 1,    //Cuando se quiere extraer un DL que no sea GUN, SAM o Exocet
    Ret_Scn_Unknown         = 2,    //Cuando se quiere extraer un DL que no posee un formato de grupos documentado
    Ret_CopyCassDirErr      = 3,    //Cuando no se puede abrir el archivo de Copycass
    Ret_VolHeaderErr        = 4,    //Cuando no se puede leer el Volumen Header
    Ret_FirstMarkErr        = 5,    //Cuando no se puede leer la primer marca del copycass
    Ret_FileHeaderErr       = 6,    //Cuando no se puede leer el File Header (gun y fc invalidos)
    Ret_MarkErr             = 7,    //Cuando no se puede leer una marca
    Ret_PrestBlockErr       = 8,    //Cuando no se puede leer el Preset Block
    Ret_DataBlockErr        = 9,    //Error al leer un Data Block
    Ret_UnknownBlock        = 10,   //Cuando no se puede identificar un tipo de bloque
    Ret_FileTrailerErr      = 11,   //Cuando no se puede leer el File Trailer
    Ret_DeviceTrailerErr    = 12,   //Cuando no se puede leer el Device Trailer
    Ret_ErrGrupoPRE         = 13,   //Cuando no se pudo encontrar los datos del grupo 81 (PRE)
    Ret_ErrGrupoNGS         = 14,   //Cuando no se pudo encontrar los datos del grupo 86 (NGS)
    Ret_ErrGrupoOSD         = 15,   //Cuando no se pudo encontrar los datos del grupo 8 (OSD)
    Ret_ErrGrupoSEN         = 16,   //Cuando no se pudo encontrar los datos del grupo 3 (SEN)
    Ret_ErrGrupoGUN         = 17,   //Cuando no se pudo encontrar los datos del grupo 10 0 13 (GUN)
    Ret_ErrGrupoGEN         = 18,   //Cuando no se pudo encontrar los datos del grupo 1 0 5 (GEN)
    Ret_ErrGrupoSMI         = 19,   //Cuando no se pudo encontrar los datos del grupo 19 (SMI)
    Ret_ErrGrupoSMC         = 20,   //Cuando no se pudo encontrar los datos del grupo 20 (SMC)
    Ret_ErrGrupoSSM         = 21,   //Cuando no se pudo encontrar los datos del grupo 30 (SSM)



    Ret_Err                 = 255    //Error General
} Status_Return;

typedef enum {
    Scn_FCGUN       = 1,
    Scn_FCSAM       = 2,
    Scn_GUN         = 3,
    Scn_AIRCO       = 4,
    Scn_FC          = 5,
    Scn_TRACK       = 6,
    Scn_VECTAC      = 7,
    Scn_STATIONING  = 8,
    Scn_CPA         = 9,
    Scn_DEPCHARGE   = 10,
    Scn_TORPEDO     = 11,
    Scn_EXOCET      = 12,
    Scn_UNKNOWN     = 13
} Scenario_Type;

typedef struct {
    char            Ident_1;
    char            Ident_2;
    char            Ident_3;
    char            Ident_4;
    char            Ident_5;
    char            Ident_6;
    uint8_t         GUN;
    uint8_t         FC;
    uint16_t        Int_Time;   //segundos * 100
    uint8_t         Num_DL;
    float           Total_Time; //segundos
    Scenario_Type   SCEN;
    uint16_t        Meko_Type;
    uint16_t        Num_Samples;
} EstadosDL;

typedef struct {
    char            Ident[6];
    float           TotalTime; //segundos
} InfoAppend;

#endif // VAR_GLOB
