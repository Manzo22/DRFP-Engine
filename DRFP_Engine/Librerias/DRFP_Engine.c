
#include "DRFP_Engine.h"


#include "Data_Formatting/DRFP.h"
#include "File_Analyzer/Copycass_Check.h"
#include "File_Analyzer/Control_Unit.h"

Status_Return Extraer_FC_GUN();
Status_Return Extraer_FC_SAM();
Status_Return Extraer_GUN();
Status_Return Extraer_FC();
Status_Return Extraer_Exocet();


Status_Return DRFP_Engine_Init(char *dir_Copycass, uint8_t *AppendNum, InfoAppend InfoRet[20]){
    Scenario_Type temp_scn;
    Status_Return ret;

    ret = CC_Formatting_DL(dir_Copycass, AppendNum, InfoRet);
    if(ret != Ret_OK)
        return ret;

    temp_scn = CU_Get_SCN();

    switch (temp_scn){

    case 1:
        ret = Extraer_FC_GUN();
        return ret;

    case 2:
        ret = Extraer_FC_SAM();
        return ret;

    case 3:
        ret = Extraer_GUN();
        return ret;

    case 4:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 5:
        ret = Extraer_FC();
        return ret;

    case 6:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 7:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 8:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 9:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 10:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 11:
        ret = Ret_Scn_Incompatible;
        return ret;

    case 12:
        ret = Extraer_Exocet();
        return ret;

    case 13:
        ret = Ret_Scn_Unknown;
        return ret;

    default:
        ret = Ret_Err;
        return ret;
    }

    return Ret_Err;

}

Status_Return Extraer_FC_GUN(){
    Status_Return ret;

    ret = GrupoPRE();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoNGS();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoOSD();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoSEN();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoGEN();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoGUN();
    if (ret!=Ret_OK)
        return ret;

    return Ret_OK;
}

Status_Return Extraer_FC_SAM(){
    Status_Return ret;

    ret = GrupoNGS();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoOSD();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoSEN();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoGEN();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoSMI();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoSMC();
    if (ret!=Ret_OK)
        return ret;

    return Ret_OK;
}

Status_Return Extraer_GUN(){
    Status_Return ret;

    ret = GrupoPRE();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoNGS();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoGUN();
    if (ret!=Ret_OK)
        return ret;

    return Ret_OK;
}

Status_Return Extraer_FC(){
    Status_Return ret;

    ret = GrupoPRE();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoNGS();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoOSD();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoSEN();
    if (ret!=Ret_OK)
        return ret;

    ret = GrupoGEN();
    if (ret!=Ret_OK)
        return ret;

    return Ret_OK;
}

Status_Return Extraer_Exocet(){
    Status_Return ret;

    ret = GrupoSSM();
    if (ret!=Ret_OK)
        return ret;

    return Ret_OK;
}

void DE_Get_IDENT( char* temp){
    CU_Get_IDENT(temp);
    return;
}

uint8_t DE_Get_FC(){
    return CU_Get_FC();
}

uint8_t DE_Get_GUN(){
    return CU_Get_GUN();
}

Scenario_Type DE_Get_SCN(){
    return CU_Get_SCN();
}

float DE_Get_Total_Run_Time(){
    return CU_Get_Total_Run_Time();
}

uint16_t DE_Get_INTERV_TIME(){
    return CU_Get_INTERV_TIME();
}

uint8_t DE_Get_NumDL(){
    return CU_Get_NumDL();
}

uint16_t DE_Get_Meko_Type(){
    return CU_Get_Meko_Type();
}
