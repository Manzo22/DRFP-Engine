#include "Control_Unit.h"

//#include "../Data_Formatting/Groups.h"
#include "Lectura_Bloques.h"

EstadosDL General_Info;

uint8_t verificarFCGUN();
uint8_t verificarFCSAM();
uint8_t verificarSAM();
uint8_t verificarGUN();
uint8_t verificarFC();
uint8_t verificarTrack();
uint8_t verificarExocet();
uint8_t verificarTorpedo();
uint8_t verificarDephtCharge();
uint8_t verificarAirco();
uint8_t verificarCPA();
uint8_t verificarStationing();
uint8_t verificarVECTAC();

void VerificarGrupos(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++)
        if(GruposGrabados[i].recFlag == 0){}
            //fprintf(FinalCheck, "MISSING GROUP: %d\n", GruposGrabados[i].id);

    return;
}

void CU_Set_IDENT(char temp[6]){
    General_Info.Ident_1 = temp[0];
    General_Info.Ident_2 = temp[1];
    General_Info.Ident_3 = temp[2];
    General_Info.Ident_4 = temp[3];
    General_Info.Ident_5 = temp[4];
    General_Info.Ident_6 = temp[5];
}

void CU_Set_GUN(uint8_t temp){
    General_Info.GUN = temp;
}

void CU_Set_FC(uint8_t temp){
    General_Info.FC = temp;
}

void CU_Set_NumDL(uint8_t temp){
    General_Info.Num_DL = temp;
}

void CU_Set_INT_TIME(uint16_t temp){
    General_Info.Int_Time = temp;
}

void CU_Set_T_TIME(float temp){
    General_Info.Total_Time = temp;
}

void CU_Set_Meko_Type(uint16_t temp){
    General_Info.Meko_Type = temp;
}

void CU_Set_Scenario(Scenario_Type temp){
    General_Info.SCEN = temp;
}

void CU_Set_Num_Samples(uint16_t temp){
    General_Info.Num_Samples = temp;
}

Scenario_Type IdentificarEscenario(){
    uint8_t i;

    if(numGruposGrabados==10){  //FC+GUN
        if(verificarFCGUN()==1){
            return Scn_FCGUN;
        }
        else{//ERROR
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);

        }
    }

    if(numGruposGrabados==9){   //FC+SAM
        if(verificarFCSAM()==1){
            return Scn_FCSAM;
        }
        else{
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);
        }
    }

    if(numGruposGrabados==6){   //GUN
        if(verificarGUN()==1){
            return Scn_GUN;
        }
        else{
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);
        }
    }

    if(numGruposGrabados==5){   //FC or Track or Airco
        if(verificarAirco()==1){
            return Scn_AIRCO;
        }
        else if (verificarFC()==1){
            return Scn_FC;
        }
        else if (verificarTrack()==1){
            return Scn_TRACK;
        }
        else{
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);
        }
    }

    if(numGruposGrabados==3){   //VECTAC or STATIONING or CPA or Depth Charge or Torpedo Syst
        if(verificarVECTAC()==1){
            return Scn_VECTAC;
        }
        else if (verificarStationing()==1){
            return Scn_STATIONING;
        }
        else if (verificarCPA()==1){
            return Scn_CPA;
        }
        else if (verificarDephtCharge()==1){
            return Scn_DEPCHARGE;
        }
        else if (verificarTorpedo()==1){
            return Scn_TORPEDO;
        }
        else{
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);
        }
    }

    if(numGruposGrabados==2){   //Exocet
        if(verificarExocet()==1){
            return Scn_EXOCET;
        }
        else{
            return Scn_UNKNOWN;
            for(i=0; i<numGruposGrabados; i++){}
                //fprintf(FinalCheck, "%d\t", GruposGrabados[i].id);
        }
    }

    return Scn_UNKNOWN;
}

uint8_t verificarFCGUN(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=1)&&
           (GruposGrabados[i].id!=2)&&
           (GruposGrabados[i].id!=3)&&
           (GruposGrabados[i].id!=5)&&
           (GruposGrabados[i].id!=6)&&
           (GruposGrabados[i].id!=8)&&
           (GruposGrabados[i].id!=10)&&
           (GruposGrabados[i].id!=13)&&
           (GruposGrabados[i].id!=15)&&
           (GruposGrabados[i].id!=16)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarFCSAM(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=1)&&
           (GruposGrabados[i].id!=3)&&
           (GruposGrabados[i].id!=5)&&
           (GruposGrabados[i].id!=6)&&
           (GruposGrabados[i].id!=8)&&
           (GruposGrabados[i].id!=17)&&
           (GruposGrabados[i].id!=18)&&
           (GruposGrabados[i].id!=19)&&
           (GruposGrabados[i].id!=20)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarSAM(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=1)&&
           (GruposGrabados[i].id!=5)&&
           (GruposGrabados[i].id!=17)&&
           (GruposGrabados[i].id!=18)&&
           (GruposGrabados[i].id!=19)&&
           (GruposGrabados[i].id!=20)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarGUN(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=2)&&
           (GruposGrabados[i].id!=6)&&
           (GruposGrabados[i].id!=10)&&
           (GruposGrabados[i].id!=13)&&
           (GruposGrabados[i].id!=15)&&
           (GruposGrabados[i].id!=16)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarFC(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=1)&&
           (GruposGrabados[i].id!=3)&&
           (GruposGrabados[i].id!=5)&&
           (GruposGrabados[i].id!=6)&&
           (GruposGrabados[i].id!=8)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarTrack(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=24)&&
           (GruposGrabados[i].id!=32)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarExocet(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=30)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarTorpedo(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=33)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarDephtCharge(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=29)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarAirco(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=28)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarCPA(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=27)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarStationing(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=26)){
            return 0;
           }
    }
    return 1;
}

uint8_t verificarVECTAC(){
    uint8_t i;
    for(i=0; i<numGruposGrabados; i++){
        if((GruposGrabados[i].id!=22)&&
           (GruposGrabados[i].id!=23)&&
           (GruposGrabados[i].id!=25)){
            return 0;
           }
    }
    return 1;
}

void CU_Get_IDENT(char *temp){
    temp[0] = General_Info.Ident_1;
    temp[1] = General_Info.Ident_2;
    temp[2] = General_Info.Ident_3;
    temp[3] = General_Info.Ident_4;
    temp[4] = General_Info.Ident_5;
    temp[5] = General_Info.Ident_6;
    return;
}

uint8_t CU_Get_FC(){
    return General_Info.FC;
}

uint8_t CU_Get_GUN(){
    return General_Info.GUN;
}

Scenario_Type CU_Get_SCN(){
    return General_Info.SCEN;
}

float CU_Get_Total_Run_Time(){
    return General_Info.Total_Time;
}

uint16_t CU_Get_INTERV_TIME(){
    return General_Info.Int_Time;
}

uint8_t CU_Get_NumDL(){
    return General_Info.Num_DL;
}

uint16_t CU_Get_Meko_Type(){
    return General_Info.Meko_Type;
}

uint16_t CU_Get_Num_Samples(){
    return General_Info.Num_Samples;
}
