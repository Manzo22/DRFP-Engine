#include "Librerias/DRFP_Engine.h"

int main (){
    uint8_t FC, GUN, scn, NumDL=7, i;
    float TiempoTotal;
    uint16_t meko, inttime;
    char identificador[6];
    InfoAppend InfoRet[20]={};
    Status_Return ret;

    ret = DRFP_Engine_Init("COPYCASS", &NumDL, InfoRet);
    printf("Ret: %d\n", ret);
    printf("Num DL: %d\n", NumDL);
    for(i=0;i<NumDL;i++)
        printf("DL-%d\tIDENT: %s\tDuracion: %f\n", i+1, InfoRet[i].Ident, InfoRet[i].TotalTime);
    //return 0;

    DE_Get_IDENT(identificador);
    FC = DE_Get_FC();
    GUN = DE_Get_GUN();
    scn = DE_Get_SCN();
    TiempoTotal = DE_Get_Total_Run_Time();
    inttime = DE_Get_INTERV_TIME();
    NumDL = DE_Get_NumDL();
    meko = DE_Get_Meko_Type();

    printf("FC: %d\nGUN: %d\nEscenario: %d\nInt Time: %d\nIdentificador: %s\nUnidad Meko-%d\nTiempo Total: %f\nNumero de DL: %d",
           FC, GUN, scn, inttime, identificador, meko, TiempoTotal, NumDL);

    return 0;
}
