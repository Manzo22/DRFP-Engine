#include "DRFP.h"

#include "Arithmetic_Unit.h"
#include "../File_Analyzer/Control_Unit.h"

//char Ident[6];
//uint8_t FC, GUN;
//uint16_t IntervalTime;
//uint16_t TotalRunTime;
/*
void setDuracion(uint16_t var){
    TotalRunTime = var;
}
void setInter(uint16_t interv){
    IntervalTime = interv;
}
*/

Status_Return GrupoPRE(){
    FILE *PRE_File, *Grupo81;
    float BAR=0, MV1=0, MV2=0, MV3=0, MV6=0, MV7=0, VWA=0, VWS=0, BWNA=0, BWNS=0, TEMPA=0, TEMPS=0, CC=0, LA81=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;

    PRE_File = fopen("DRFP_generated/Grupo_PRE.csv", "w");
    //fprintf(PRE_File, "Grupo PRE\n");
    //fprintf(PRE_File, "IDENT:;%c%c%c%c%c%c\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5]);
    fprintf(PRE_File, "BAR;MV1;MV2;MV3;MV6;MV7;VWA;VWS;BWNA;BWNS;TEMPA;TEMPS;CC;LA81\n");
    //fprintf(PRE_File, "MBAR;M/S;M/S;M/S;M/S;M/S;KTS;KTS;DEG;DEG;DEGC;DEGC;%%;DEG\n");
    Grupo81 = fopen("Grupos/Grupo_81.txt", "rb");
    if(Grupo81==NULL){
        fclose(PRE_File);
        return Ret_ErrGrupoPRE;
    }

    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    BAR = (float)temp/MBAR;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    MV1 = (float)temp/MpS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    MV2 = (float)temp/MpS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    MV3 = (float)temp/MpS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    MV6 = (float)temp/MpS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    MV7 = (float)temp/MpS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    VWA = (float)temp/KTS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    VWS = (float)temp/KTS;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=temp3|(temp2<<8)|(temp1<<16);
    BWNA = (float)temp/DEG;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=temp3|(temp2<<8)|(temp1<<16);
    BWNS = (float)temp/DEG;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    TEMPA = (float)temp/DEGC;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    TEMPS = (float)temp/DEGC;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    CC = (float)temp/Porc;
    fread(&temp1, 1, 1, Grupo81);
    fread(&temp2, 1, 1, Grupo81);
    fread(&temp3, 1, 1, Grupo81);
    temp=temp3|(temp2<<8)|(temp1<<16);
    LA81 = (float)temp/RAD;

    fprintf(PRE_File, "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\n", BAR, MV1, MV2, MV3, MV6, MV7, VWA, VWS, BWNA, BWNS, TEMPA, TEMPS, CC, LA81);

    fclose(PRE_File);
    fclose(Grupo81);

    remove("Grupos/Grupo_81.txt");

    return Ret_OK;
}

Status_Return GrupoNGS(){
    FILE *NGS_File, *Grupo86;
    float BD=0, RD=0, RDZ=0, KS=0, VS=0, OTL=0, OSB=0, OSR=0, TROF=0;
    char CBOTL[6], CROTL[6], valor[5];

    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;

    NGS_File = fopen("DRFP_generated/Grupo NGS.csv", "w");
    //fprintf(NGS_File, "Grupo NGS\n");
    //fprintf(NGS_File, "IDENT:;%c%c%c%c%c%c\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5]);
    fprintf(NGS_File, "BD;RD;RDZ;KS;VS;OTL;OSB;OSR;CBOTL;CROTL;TROF\n");
    //fprintf(NGS_File, "DEG;Y;FT;DEG;Y/S;DEG;DEG;Y;Y;Y;DEG\n");
    Grupo86 = fopen("Grupos/Grupo_86.txt", "rb");
    if(Grupo86==NULL){
        fclose(NGS_File);
        return Ret_ErrGrupoNGS;
    }
    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=temp3|(temp2<<8)|(temp1<<16);
    BD = (float)temp/DEG;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    RD = (float)temp/Y;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    RDZ = (float)temp/FT;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=temp3|(temp2<<8)|(temp1<<16);
    KS = (float)temp/DEG;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    VS = (float)temp/YpS;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=temp3|(temp2<<8)|(temp1<<16);
    OSB = (float)temp/DEG;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    OSR = (float)temp/Y;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=temp3|(temp2<<8)|(temp1<<16);
    OTL = (float)temp/DEG;

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    if (temp<0){
        temp = temp/(-Y);
        temp = (int)temp;
        if(temp>9999)
            strcpy(valor, "****");
        else
            itoa(temp, valor, 10);
        strcpy(CBOTL, "L");
        strcat(CBOTL, valor);
    }
    else{
        temp = temp/Y;
        temp = (int)temp;
        if(temp>9999)
            strcpy(valor, "****");
        else
            itoa(temp, valor, 10);
        strcpy(CBOTL, "R");
        strcat(CBOTL, valor);

    }
    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    if (temp<0){
        temp = temp/(-Y);
        temp = (int)temp;
        if(temp>9999)
            strcpy(valor, "****");
        else
            itoa(temp, valor, 10);
        strcpy(CROTL, "D");
        strcat(CROTL, valor);
    }
    else{

        temp = temp/Y;
        temp = (int)temp;
        if(temp>9999)
            strcpy(valor, "****");
        else
            itoa(temp, valor, 10);

        strcpy(CROTL, "A");

        strcat(CROTL, valor);


    }

    fread(&temp1, 1, 1, Grupo86);
    fread(&temp2, 1, 1, Grupo86);
    fread(&temp3, 1, 1, Grupo86);
    temp=convertir_a_negativo(temp1, temp2, temp3);
    TROF = (float)(temp/DEG);


    fprintf(NGS_File, "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%s;%s;%.1f\n", BD, RD, RDZ, KS, VS, OTL, OSB, OSR, CBOTL, CROTL, TROF);

    fclose(NGS_File);
    fclose(Grupo86);

    remove("Grupos/Grupo_86.txt");

    return Ret_OK;
}

Status_Return GrupoOSD(){
    FILE *OSD_File, *Grupo8;
    float TM=0, VE=0, KE=0, QE=0, EE=0, FQE=0, FEE=0, VQE=0, VEE=0;
    float correccion=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;
    int count=0, i=0;
    float t=0;
    uint32_t tiempoInt=0;


    OSD_File = fopen("DRFP_generated/Grupo OSD.csv", "w");
    //fprintf(OSD_File, "Grupo OSD\n");
    //fprintf(OSD_File, "IDENT:;%c%c%c%c%c%c\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5]);
    fprintf(OSD_File, "TIME;TM;VE;KE;QE;EE;FQE;FEE;VQE;VEE\n");
    //fprintf(OSD_File, "SEC;SEC;Y/S;DEG;DEG;DEG;DEG;DEG;DEG/S;DEG/S\n");
    Grupo8 = fopen("Grupos/Grupo_8.txt", "rb");
    if(Grupo8==NULL){
        fclose(OSD_File);
        return Ret_ErrGrupoOSD;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TM = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        VE = (float)temp/YpS;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=temp3|(temp2<<8)|(temp1<<16);
        KE = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        QE = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        EE = (float)temp/DEG;

        for(i=0; i<3; i++){
            fread(&temp1, 1, 1, Grupo8);
        }

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        VQE = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        VEE = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        FQE = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo8);
        fread(&temp2, 1, 1, Grupo8);
        fread(&temp3, 1, 1, Grupo8);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        FEE = (float)temp/DEG;

        t = (float)tiempoInt/100;
        correccion = (float)count*(0.000132);
        t-=correccion;

        fprintf(OSD_File, "%.2f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\n", t, TM, VE, KE, QE, EE, FQE, FEE, VQE, VEE);

        tiempoInt +=IntervalTime;

    }

    fclose(OSD_File);
    fclose(Grupo8);

    remove("Grupos/Grupo_8.txt");

    return Ret_OK;
}

Status_Return GrupoSEN(){
    FILE *SEN_File, *Grupo3;
    float TM=0, RD=0, BDN=0, ED=0, FRR=0, FBR=0, FER=0, SDR=0, SDB=0, SDE=0;
    float correccion=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;
    int count=0, i=0;
    float t=0;
    uint32_t tiempoInt=0;

    SEN_File = fopen("DRFP_generated/Grupo SEN.csv", "w");
    //fprintf(SEN_File, "Grupo SEN\n");
    //fprintf(SEN_File, "IDENT:;%c%c%c%c%c%c;INT:;%d MS;FC%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10), FC);
    fprintf(SEN_File, "TIME;TM;RD;BDN;ED;FRR;FBR;FER;SDR;SDB;SDE\n");
    fprintf(SEN_File, "SEC;SEC;Y;DEG;DEG;Y;DEG;DEG;Y;DEG;DEG\n");
    Grupo3 = fopen("Grupos/Grupo_3.txt", "rb");
    if(Grupo3==NULL){
        fclose(SEN_File);
        return Ret_ErrGrupoSEN;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TM = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        RD = (float)temp/Y;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp=temp3|(temp2<<8)|(temp1<<16);
        BDN = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        ED = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        FRR = (float)temp/Y;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        FBR = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        FER = (float)temp/DEG;

        for (i=0; i<3; i++){
            fread(&temp1, 1, 1, Grupo3);
        }

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        SDR = (float)temp/Y;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp=temp3|(temp2<<8)|(temp1<<16);
        SDB = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo3);
        fread(&temp2, 1, 1, Grupo3);
        fread(&temp3, 1, 1, Grupo3);
        temp=temp3|(temp2<<8)|(temp1<<16);
        SDE = (float)temp/DEG;

        t = (float)tiempoInt/100;
        correccion = (float)count*(0.000132);
        t-=correccion;

        fprintf(SEN_File, "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\n", t, TM, RD, BDN, ED, FRR, FBR, FER, SDR, SDB, SDE);

        tiempoInt += IntervalTime;
    }

    fclose(SEN_File);
    fclose(Grupo3);

    remove("Grupos/Grupo_3.txt");

    return Ret_OK;
}

Status_Return GrupoGUN(){
    FILE *GUN_File, *Grupo13, *Grupo10;
    float TM=0, BS=0, ES=0, RT=0, BTN=0, ET=0, TS=0, CRS=0, CBS=0, CES=0;
    float paramX=0, paramY=0, paramZ=0;
    float correccion=0;
    uint8_t Flag_A=0, Flag_B=0, Flag_C=0, Flag_D=0, Flag_E=0, Flag_F=0, Flag_G=0, Flag_H=0, Flag_I=0, Flag_J=0, Flag_K=0, Flag_L=0, Flag_M=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t RSX=0, RSY=0, RSZ=0, RTX=0, RTY=0, RTZ=0;
    int32_t temp=0;
    uint8_t wicStatus_1=0, wicStatus_2=0, wicStatus_3=0;
    int count=0, i=0;
    float t=0;
    uint32_t tiempoInt=0;

    GUN_File = fopen("DRFP_generated/Grupo GUN.csv", "w");
    //fprintf(GUN_File, "Grupo GUN\n");
    //fprintf(GUN_File, "IDENT:;%c%c%c%c%c%c;INT:;%d MS;FC%d/GUN%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10), FC, GUN);
    fprintf(GUN_File, "TIME;TM;BS;ES;RT;BTN;ET;TS;CRS;CBS;CES;A;B;C;D;E;F;G;H;I;J;K;L;M\n");
    fprintf(GUN_File, "SEC;SEC;DEG;DEG;Y;DEG;DEG;SEC;Y;mil;mil\n");
    Grupo13 = fopen("Grupos/Grupo_13.txt", "rb");
    if(Grupo13==NULL){
        fclose(GUN_File);
        return Ret_ErrGrupoGUN;
    }
    Grupo10 = fopen("Grupos/Grupo_10.txt", "rb");
    if(Grupo10==NULL){
        fclose(GUN_File);
        return Ret_ErrGrupoGUN;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        fread(&wicStatus_1, 1, 1, Grupo10);
        fread(&wicStatus_2, 1, 1, Grupo10);
        fread(&wicStatus_3, 1, 1, Grupo10);
        if((wicStatus_1&0x80)!=0)
            Flag_A=1;
        else
            Flag_A=0;
        if((wicStatus_1&0x40)!=0)
            Flag_B=1;
        else
            Flag_B=0;
        if((wicStatus_1&0x20)!=0)
            Flag_C=1;
        else
            Flag_C=0;
        if((wicStatus_1&0x10)!=0)
            Flag_D=1;
        else
            Flag_D=0;
        if((wicStatus_1&0x08)!=0)
            Flag_E=1;
        else
            Flag_E=0;
        if((wicStatus_1&0x04)!=0)
            Flag_F=1;
        else
            Flag_F=0;
        if((wicStatus_1&0x02)!=0)
            Flag_G=1;
        else
            Flag_G=0;
        if((wicStatus_1&0x01)!=0)
            Flag_H=1;
        else
            Flag_H=0;
        if((wicStatus_2&0x80)!=0)
            Flag_I=1;
        else
            Flag_I=0;
        if((wicStatus_2&0x40)!=0)
            Flag_J=1;
        else
            Flag_J=0;
        if((wicStatus_2&0x20)!=0)
            Flag_K=1;
        else
            Flag_K=0;
        if((wicStatus_2&0x10)!=0)
            Flag_L=1;
        else
            Flag_L=0;
        if((wicStatus_2&0x08)!=0)
            Flag_M=1;
        else
            Flag_M=0;

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TM = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RSX = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RSY = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RSZ = convertir_a_negativo(temp1, temp2, temp3);

        for(i=0; i<9; i++)
            fread(&temp1, 1, 1, Grupo13);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RTX = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RTY = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        RTZ = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TS = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        CRS = (float)temp/Y;

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        CBS = (float)temp/mil;

        fread(&temp1, 1, 1, Grupo13);
        fread(&temp2, 1, 1, Grupo13);
        fread(&temp3, 1, 1, Grupo13);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        CES = (float)temp/mil;

        BS = arctan_2(RSX, RSY);
        if (BS<0)
            BS+=360;
        BTN = arctan_2(RTX, RTY);
        if(BTN<0)
            BTN+=360;
        ES = arctan_3(RSX, RSY, RSZ);
        ET = arctan_3(RTX, RTY, RTZ);
        paramX = (float) RTX / Y;
        paramY = (float) RTY / Y;
        paramZ = (float) RTZ / Y;
        RT = raiz_3(paramX, paramY, paramZ);

        t = (float)tiempoInt/100;
        correccion = (float)count*(0.000132);
        t-=correccion;

        fprintf(GUN_File, "%.1f;****;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.0f;%.2f;%.0f;", t, BS, ES, RT, BTN, ET, TS, CRS, CBS, CES);
        fprintf(GUN_File, "%d;%d;%d;%d;%d;%d;%d;", Flag_A, Flag_B, Flag_C, Flag_D, Flag_E, Flag_F, Flag_G);
        fprintf(GUN_File, "%d;%d;%d;%d;%d;%d\n", Flag_H, Flag_I, Flag_J, Flag_K, Flag_L, Flag_M);

        tiempoInt += IntervalTime;

    }

    fclose(GUN_File);
    fclose(Grupo10);
    fclose(Grupo13);

    remove("Grupos/Grupo_13.txt");
    remove("Grupos/Grupo_10.txt");

    return Ret_OK;
}

Status_Return GrupoGEN(){
    FILE *GEN_File, *Grupo5, *Grupo1;
    float TM, RM, BMN, EM, KM, VM, VMZ_2;
    float correccion=0;
    uint8_t Flag_A=0, Flag_C=0, Flag_D=0, Flag_E=0, Flag_F=0, Flag_G=0, Flag_H=0, Flag_I=0, Flag_J=0, Flag_K=0, Flag_L=0, Flag_M=0, Flag_N=0, Flag_O=0, Flag_P=0, Flag_Q=0, Flag_R=0, Flag_S=0, Flag_T=0, Flag_U=0, Flag_V=0, Flag_W=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t RMX=0, RMY=0, RMZ=0, VMX=0, VMY=0, VMZ=0;
    int32_t temp=0;
    uint8_t FcStatus_1=0, FcStatus_2=0, FcStatus_3=0;
    float paramX=0, paramY=0, paramZ=0;
    int count=0;     //verificar que ande el count para mas de 6h de DL!!!!
    float t=0;
    uint32_t tiempoInt=0;

    GEN_File = fopen("DRFP_generated/Grupo GEN.csv", "w");
    //fprintf(GEN_File, "Grupo GEN\n");
    //fprintf(GEN_File, "IDENT:;%c%c%c%c%c%c;INT:;%d MS;FC%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10), FC);
    fprintf(GEN_File, "TIME;TM;RM;BMN;EM;KM;VM;VMZ;A;C;D;E;F;G;H;I;J;K;L;M;N;O;P;Q;R;S;T;U;V;W\n");
    fprintf(GEN_File, "SEC;SEC;Y;DEG;DEG;DEG;Y/S;Y/S\n");
    Grupo5 = fopen("Grupos/Grupo_5.txt", "rb");
    if(Grupo5==NULL){
        fclose(GEN_File);
        return Ret_ErrGrupoGEN;
    }
    Grupo1 = fopen("Grupos/Grupo_1.txt", "rb");
    if(Grupo1==NULL){
        fclose(GEN_File);
        return Ret_ErrGrupoGEN;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        fread(&FcStatus_1, 1, 1, Grupo1);
        fread(&FcStatus_2, 1, 1, Grupo1);
        fread(&FcStatus_3, 1, 1, Grupo1);
        if((FcStatus_1&0x80)!=0)
            Flag_A=1;
        else
            Flag_A=0;
        if((FcStatus_1&0x20)!=0)
            Flag_C=1;
        else
            Flag_C=0;
        if((FcStatus_1&0x10)!=0)
            Flag_D=1;
        else
            Flag_D=0;
        if((FcStatus_1&0x08)!=0)
            Flag_E=1;
        else
            Flag_E=0;
        if((FcStatus_1&0x04)!=0)
            Flag_F=1;
        else
            Flag_F=0;
        if((FcStatus_1&0x02)!=0)
            Flag_G=1;
        else
            Flag_G=0;
        if((FcStatus_1&0x01)!=0)
            Flag_H=1;
        else
            Flag_H=0;
        if((FcStatus_2&0x80)!=0)
            Flag_I=1;
        else
            Flag_I=0;
        if((FcStatus_2&0x40)!=0)
            Flag_J=1;
        else
            Flag_J=0;
        if((FcStatus_2&0x20)!=0)
            Flag_K=1;
        else
            Flag_K=0;
        if((FcStatus_2&0x10)!=0)
            Flag_L=1;
        else
            Flag_L=0;
        if((FcStatus_2&0x08)!=0)
            Flag_M=1;
        else
            Flag_M=0;
        if((FcStatus_2&0x04)!=0)
            Flag_N=1;
        else
            Flag_N=0;
        if((FcStatus_2&0x02)!=0)
            Flag_O=1;
        else
            Flag_O=0;
        if((FcStatus_2&0x01)!=0)
            Flag_P=1;
        else
            Flag_P=0;
        if((FcStatus_3&0x80)!=0)
            Flag_Q=1;
        else
            Flag_Q=0;
        if((FcStatus_3&0x40)!=0)
            Flag_R=1;
        else
            Flag_R=0;
        if((FcStatus_3&0x20)!=0)
            Flag_S=1;
        else
            Flag_S=0;
        if((FcStatus_3&0x10)!=0)
            Flag_T=1;
        else
            Flag_T=0;
        if((FcStatus_3&0x08)!=0)
            Flag_U=1;
        else
            Flag_U=0;
        if((FcStatus_3&0x04)!=0)
            Flag_V=1;
        else
            Flag_V=0;
        if((FcStatus_3&0x02)!=0)
            Flag_W=1;
        else
            Flag_W=0;

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TM = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        RMX = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        RMY = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        RMZ = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        VMX = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        VMY = convertir_a_negativo(temp1, temp2, temp3);

        fread(&temp1, 1, 1, Grupo5);
        fread(&temp2, 1, 1, Grupo5);
        fread(&temp3, 1, 1, Grupo5);
        VMZ = convertir_a_negativo(temp1, temp2, temp3);
        VMZ_2 = (float)VMZ/YpS;

        paramX = (float) RMX / Y;
        paramY = (float) RMY / Y;
        paramZ = (float) RMZ / Y;
        RM = raiz_3(paramX, paramY, paramZ);
        BMN = arctan_2(RMX, RMY);
        if(BMN<0)
            BMN+=360;
        EM = arctan_3(RMX, RMY, RMZ);
        KM = arctan_2(VMX, VMY);
        if(KM < 0)
            KM+=360;
        VM = (float)raiz_3(VMX, VMY, VMZ);
        VM = (float)VM/YpS;

        t = (float)tiempoInt/100;
        correccion = (float)count*(0.000132);
        t-=correccion;

        fprintf(GEN_File, "%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;", t, TM, RM, BMN, EM, KM, VM, VMZ_2);
        fprintf(GEN_File, "%d;%d;%d;%d;%d;%d;%d;", Flag_A, Flag_C, Flag_D, Flag_E, Flag_F, Flag_G, Flag_H);
        fprintf(GEN_File, "%d;%d;%d;%d;%d;%d;%d;", Flag_I, Flag_J, Flag_K, Flag_L, Flag_M, Flag_N, Flag_O);
        fprintf(GEN_File, "%d;%d;%d;%d;%d;%d;%d;%d\n", Flag_P, Flag_Q, Flag_R, Flag_S, Flag_T, Flag_U, Flag_V, Flag_W);

        tiempoInt += IntervalTime;
    }

    fclose(GEN_File);
    fclose(Grupo1);
    fclose(Grupo5);

    remove("Grupos/Grupo_5.txt");
    remove("Grupos/Grupo_1.txt");

    return Ret_OK;
}

Status_Return GrupoSMI(){
    FILE *SMI_File, *Grupo19;
    uint8_t w2_A=0, w2_B=0, w2_C=0, w2_D=0, w2_E=0, w2_F=0, w2_G=0, w2_H=0, w2_I=0, w2_J=0, w2_K=0, w2_L=0, w2_M=0, w2_N=0, w2_O=0, w2_P=0;
    uint8_t w1_A=0, w1_B=0, w1_C=0, w1_D=0, w1_E=0, w1_F=0, w1_G=0, w1_H=0, w1_I=0, w1_J=0, w1_K=0, w1_L=0, w1_M=0, w1_N=0, w1_O=0, w1_P=0;
    uint8_t FcStatus_1=0, FcStatus_2=0, FcStatus_3=0;
    uint8_t TTEZ=0, TOF=0, TTIZ=0, TTI=0;
    float IPX=0, IPY=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;
    int count=0, i;
    float t=0;
    uint32_t tiempoInt=0;

    SMI_File = fopen("DRFP_generated/Grupo SMI.csv", "w");
    //fprintf(SMI_File, "Grupo SMI\n");
    //fprintf(SMI_File, "IDENT:;%c%c%c%c%c%c;INT:;%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10));
    fprintf(SMI_File, "TIME;TTIZ;TTI;TTEZ;TOF;IPX;IPY;A;B;C;D;E;F;G;H;I;J;K;L;M;N;O;P;A;B;C;D;E;F;G;H;I;J;K;L;M;N;O;P\n");
    fprintf(SMI_File, "SEC;SEC;SEC;SEC;SEC;Y;Y\n");
    Grupo19 = fopen("Grupos/Grupo_19.txt", "rb");
    if(Grupo19==NULL){
        fclose(SMI_File);
        return Ret_ErrGrupoSMI;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        for(i=0; i<3; i++)
            fread(&temp1, 1, 1, Grupo19);

        //LEER TTEZ
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TTEZ = convertir_a_par((temp/SMI_TTEZ)%SMI_TTEZ);
        TTIZ = convertir_a_par(truncar((float)temp/SMI_TTI));


        //LEER TOF
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TOF = convertir_a_par((temp/SMI_TTEZ)%SMI_TTEZ);
        TTI = convertir_a_par(truncar((float)temp/SMI_TTI));

        fread(&FcStatus_1, 1, 1, Grupo19);
        fread(&FcStatus_2, 1, 1, Grupo19);
        fread(&FcStatus_3, 1, 1, Grupo19);
        if((FcStatus_1&0x80)!=0)
            w1_A=1;
        else
            w1_A=0;
        if((FcStatus_1&0x40)!=0)
            w1_B=1;
        else
            w1_B=0;
        if((FcStatus_1&0x20)!=0)
            w1_C=1;
        else
            w1_C=0;
        if((FcStatus_1&0x10)!=0)
            w1_D=1;
        else
            w1_D=0;
        if((FcStatus_1&0x08)!=0)
            w1_E=1;
        else
            w1_E=0;
        if((FcStatus_1&0x04)!=0)
            w1_F=1;
        else
            w1_F=0;
        if((FcStatus_1&0x02)!=0)
            w1_G=1;
        else
            w1_G=0;
        if((FcStatus_1&0x01)!=0)
            w1_H=1;
        else
            w1_H=0;
        if((FcStatus_2&0x80)!=0)
            w1_I=1;
        else
            w1_I=0;
        if((FcStatus_2&0x40)!=0)
            w1_J=1;
        else
            w1_J=0;
        if((FcStatus_2&0x20)!=0)
            w1_K=1;
        else
            w1_K=0;
        if((FcStatus_2&0x10)!=0)
            w1_L=1;
        else
            w1_L=0;
        if((FcStatus_2&0x08)!=0)
            w1_M=1;
        else
            w1_M=0;
        if((FcStatus_2&0x04)!=0)
            w1_N=1;
        else
            w1_N=0;
        if((FcStatus_2&0x02)!=0)
            w1_O=1;
        else
            w1_O=0;
        if((FcStatus_2&0x01)!=0)
            w1_P=1;
        else
            w1_P=0;

        fread(&FcStatus_1, 1, 1, Grupo19);
        fread(&FcStatus_2, 1, 1, Grupo19);
        fread(&FcStatus_3, 1, 1, Grupo19);
        if((FcStatus_1&0x80)!=0)
            w2_A=1;
        else
            w2_A=0;
        if((FcStatus_1&0x40)!=0)
            w2_B=1;
        else
            w2_B=0;
        if((FcStatus_1&0x20)!=0)
            w2_C=1;
        else
            w2_C=0;
        if((FcStatus_1&0x10)!=0)
            w2_D=1;
        else
            w2_D=0;
        if((FcStatus_1&0x08)!=0)
            w2_E=1;
        else
            w2_E=0;
        if((FcStatus_1&0x04)!=0)
            w2_F=1;
        else
            w2_F=0;
        if((FcStatus_1&0x02)!=0)
            w2_G=1;
        else
            w2_G=0;
        if((FcStatus_1&0x01)!=0)
            w2_H=1;
        else
            w2_H=0;
        if((FcStatus_2&0x80)!=0)
            w2_I=1;
        else
            w2_I=0;
        if((FcStatus_2&0x40)!=0)
            w2_J=1;
        else
            w2_J=0;
        if((FcStatus_2&0x20)!=0)
            w2_K=1;
        else
            w2_K=0;
        if((FcStatus_2&0x10)!=0)
            w2_L=1;
        else
            w2_L=0;
        if((FcStatus_2&0x08)!=0)
            w2_M=1;
        else
            w2_M=0;
        if((FcStatus_2&0x04)!=0)
            w2_N=1;
        else
            w2_N=0;
        if((FcStatus_2&0x02)!=0)
            w2_O=1;
        else
            w2_O=0;
        if((FcStatus_2&0x01)!=0)
            w2_P=1;
        else
            w2_P=0;

        for(i=0; i<6; i++)
            fread(&temp1, 1, 1, Grupo19);

        //LEER TTIZ ******************************** Otra posicion!!!!
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        //temp=temp3|(temp2<<8)|(temp1<<16);
        //TTIZ = convertir_a_par(truncar((float)temp/SMI_TTI));

        //LEER TTI  ******************************** Otra posicion!!!!
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        //temp=temp3|(temp2<<8)|(temp1<<16);
        //TTI = convertir_a_par(truncar((float)temp/SMI_TTI));

        for(i=0; i<3; i++)
            fread(&temp1, 1, 1, Grupo19);

        //LEER IPX
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        IPX = (float)truncar((float)temp/SMI_IPXY)*SMI_IPconv;

        //LEER IPY
        fread(&temp1, 1, 1, Grupo19);
        fread(&temp2, 1, 1, Grupo19);
        fread(&temp3, 1, 1, Grupo19);
        temp=convertir_a_negativo(temp1, temp2, temp3);
        IPY = (float)(truncar((float)temp/SMI_IPXY))*SMI_IPconv;

        for(i=0; i<15; i++)
            fread(&temp1, 1, 1, Grupo19);

        t = (float)tiempoInt/100;

        fprintf(SMI_File, "%.2f;%d;%d;%d;%d;%.0f;%.0f;%d;", t, TTIZ, TTI, TTEZ, TOF, IPX, IPY, w1_A);
        fprintf(SMI_File, "%d;%d;%d;%d;%d;%d;%d;", w1_B, w1_C, w1_D, w1_E, w1_F, w1_G, w1_H);
        fprintf(SMI_File, "%d;%d;%d;%d;%d;%d;%d;%d;", w1_I, w1_J, w1_K, w1_L, w1_M, w1_N, w1_O, w1_P);
        fprintf(SMI_File, "%d;%d;%d;%d;%d;%d;%d;%d;", w2_A, w2_B, w2_C, w2_D, w2_E, w2_F, w2_G, w2_H);
        fprintf(SMI_File, "%d;%d;%d;%d;%d;%d;%d;%d\n", w2_I, w2_J, w2_K, w2_L, w2_M, w2_N, w2_O, w2_P);


        tiempoInt += IntervalTime;

    }
    fclose(SMI_File);
    fclose(Grupo19);

    remove("Grupos/Grupo_19.txt");

    return Ret_OK;
}

Status_Return GrupoSMC(){
    FILE *SMC_File, *Grupo20;
    float TMO=0, RD=0, BD=0, ED=0, TMI=0, BS=0, ES=0;
    uint32_t temp1=0, temp2=0, temp3=0;
    int32_t temp=0;
    int count=0;
    float t=0;
    uint32_t tiempoInt=0;

    SMC_File = fopen("DRFP_generated/Grupo SMC.csv", "w");
    //fprintf(SMC_File, "Grupo SMC\n");
    //fprintf(SMC_File, "IDENT:;%c%c%c%c%c%c;INT:;%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10));
    fprintf(SMC_File, "TIME;TMO;RD;BD;ED;TMI;BS;ES\n");
    //fprintf(SMC_File, "SEC;SEC;Y;DEG;DEG;SEC;DEG;DEG\n");
    Grupo20 = fopen("Grupos/Grupo_20.txt", "rb");
    if(Grupo20==NULL){
        fclose(SMC_File);
        return Ret_ErrGrupoSMC;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TMO = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        RD = (float)temp/Y;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp=temp3|(temp2<<8)|(temp1<<16);
        BD = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        ED = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp=temp3|(temp2<<8)|(temp1<<16);
        TMI = (float)temp/SEG;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp=temp3|(temp2<<8)|(temp1<<16);
        BS = (float)temp/DEG;

        fread(&temp1, 1, 1, Grupo20);
        fread(&temp2, 1, 1, Grupo20);
        fread(&temp3, 1, 1, Grupo20);
        temp = convertir_a_negativo(temp1, temp2, temp3);
        ES = (float)temp/DEG;

        t = (float)tiempoInt/100;

        fprintf(SMC_File, "%.2f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f\n", t, TMO, RD, BD, ED, TMI, BS, ES);

        tiempoInt += IntervalTime;

    }

    fclose(SMC_File);
    fclose(Grupo20);

    remove("Grupos/Grupo_20.txt");

    return Ret_OK;
}

Status_Return GrupoSSM(){
    FILE *SSM_File, *Grupo30;
    float BDN=0, RD=0, t=0, paramX=0, paramY=0;
    int32_t RDX=0, RDY=0;
    char R_RTG, R_DEP, R_WDT, A_RTG, A_DEP, A_WDT, MOD[4];
    uint32_t temp1=0, temp2=0, temp3=0;
    int count=0, i;
    uint32_t tiempoInt=0;

    SSM_File = fopen("DRFP_generated/Grupo SSM.csv", "w");
    //fprintf(SSM_File, "Grupo SSM\n");
    //fprintf(SSM_File, "IDENT:;%c%c%c%c%c%c;INT:;%d\n", Ident[0], Ident[1], Ident[2], Ident[3], Ident[4], Ident[5], (IntervalTime*10));
    //fprintf(SSM_File, ";OUTPUT;OUTPUT;OUTPUT;RECOM.;RECOM.;RECOM.;ACTUAL;ACTUAL;ACTUAL\n");
    fprintf(SSM_File, "TIME;RD;BDN;MOD;RTG;DEP;WDT;RTG;DEP;WDT\n");
    //fprintf(SSM_File, "SEC;Y;DEG;;SML;SML;SML;SML;SML;SML\n");
    Grupo30 = fopen("Grupos/Grupo_30.txt", "rb");
    if(Grupo30==NULL){
        fclose(SSM_File);
        return Ret_ErrGrupoSSM;
    }

    uint16_t TotalRunTime, IntervalTime;
    TotalRunTime = CU_Get_Num_Samples();
    IntervalTime = CU_Get_INTERV_TIME();

    for(count=0; count<TotalRunTime; count++){

        for(i=0;i<27;i++)
            fread(&temp1, 1, 1, Grupo30);

        fread(&temp1, 1, 1, Grupo30);
        fread(&temp2, 1, 1, Grupo30);
        fread(&temp3, 1, 1, Grupo30);
        RDX = convertir_a_negativo(temp1, temp2, temp3);
        fread(&temp1, 1, 1, Grupo30);
        fread(&temp2, 1, 1, Grupo30);
        fread(&temp3, 1, 1, Grupo30);
        RDY = convertir_a_negativo(temp1, temp2, temp3);

        for(i=0;i<14;i++)
            fread(&temp1, 1, 1, Grupo30);

        fread(&R_DEP, 1, 1, Grupo30);
        fread(&R_RTG, 1, 1, Grupo30);

        fread(&temp1, 1, 1, Grupo30);
        fread(&temp1, 1, 1, Grupo30);

        fread(&R_WDT, 1, 1, Grupo30);

        fread(&temp1, 1, 1, Grupo30);
        if(temp1 == 1)
            strcpy(MOD, "RBL");
        else if (temp1 == 2)
            strcpy(MOD, "BOL");
        else
            strcpy(MOD, "***");

        fread(&temp1, 1, 1, Grupo30);
        fread(&temp1, 1, 1, Grupo30);

        fread(&A_WDT, 1, 1, Grupo30);
        fread(&A_DEP, 1, 1, Grupo30);
        fread(&A_RTG, 1, 1, Grupo30);

        fread(&temp1, 1, 1, Grupo30);
        fread(&temp1, 1, 1, Grupo30);

        paramX = (float)RDX / Y_DHC;
        paramY = (float)RDY / Y_DHC;
        RD = raiz_2(paramX, paramY);
        BDN = arctan_2(RDX, RDY);

        if((R_RTG!='S')&&(R_RTG!='M')&&(R_RTG!='L')&&(R_RTG!='-'))
            R_RTG = '*';
        if((R_DEP!='S')&&(R_DEP!='M')&&(R_DEP!='L')&&(R_DEP!='-'))
            R_DEP = '*';
        if((R_WDT!='S')&&(R_WDT!='M')&&(R_WDT!='L')&&(R_WDT!='-'))
            R_WDT = '*';
        if((A_RTG!='S')&&(A_RTG!='M')&&(A_RTG!='L')&&(A_RTG!='-'))
            A_RTG = '*';
        if((A_DEP!='S')&&(A_DEP!='M')&&(A_DEP!='L')&&(A_DEP!='-'))
            A_DEP = '*';
        if((A_WDT!='S')&&(A_WDT!='M')&&(A_WDT!='L')&&(A_WDT!='-'))
            A_WDT = '*';
        /*R_RTG = R_RTG&0x7F;
        R_DEP = R_DEP&0x7F;
        R_WDT = R_WDT&0x7F;
        A_RTG = A_RTG&0x7F;
        A_DEP = A_DEP&0x7F;
        A_WDT = A_WDT&0x7F;*/

        t = (float)tiempoInt/100;

        fprintf(SSM_File, "%.1f;%.0f;%.0f;%s;%c;%c;%c;%c;%c;%c\n", t, RD, BDN, MOD, R_RTG, R_DEP, R_WDT, A_RTG, A_DEP, A_WDT);

        tiempoInt += IntervalTime;
    }
    fclose(SSM_File);
    fclose(Grupo30);

    remove("Grupos/Grupo_30.txt");

    return Ret_OK;
}

void GrupoACO(){
printf("\nGrupo ACO\n");
}

void GrupoDEP(){
printf("\nGrupo DEP\n");
}

void GrupoSTA(){
printf("\nGrupo STA\n");
}

void GrupoCPA(){
printf("\nGrupo CPA\n");
}

void GrupoVTD(){
printf("\nGrupo VTD\n");
}

void GrupoTRK(){
printf("\nGrupo TRK\n");
}

void GrupoTOR(){
printf("\nGrupo TOR\n");
}

void GrupoACP(){
printf("\nGrupo ACP\n");
}

void GrupoVPD(){
printf("\nGrupo VPD\n");
}
