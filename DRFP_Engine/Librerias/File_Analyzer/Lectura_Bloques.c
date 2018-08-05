#include "Lectura_Bloques.h"

#include "../Data_Formatting/Groups.h"
#include "Control_Unit.h"

/*
    Función de lectura de bloque VOLUMEN HEADER
    Verififca el nombre de la embarcación y lo asocia a una unidad MEKO-140 o MEKO-360

    ret:
    0   OK
    255   Error
*/
Status_Return ReadVolumenHeader(FILE *Archivo){
    int i;
    char Temp;
    char MekoUnit[4];

    fread(MekoUnit, 1, 4, Archivo);

    for(i=0; i<251; i++){
        fread(&Temp, 1, 1, Archivo);
    }

    if(strcmp(MekoUnit, "DL26")==0){
        CU_Set_Meko_Type(360);
        return Ret_OK;
    }
    if(strcmp(MekoUnit, "DL55")==0){
        CU_Set_Meko_Type(140);
        return Ret_OK;
    }
    //printf("%s\n", MekoUnit);
    return Ret_Err;
}

/*
    Función de lectura de bloque FILE HEADER
    Verififca el encabezado, muestra el IDENTIFICADOR, FC y GUN

    ret:
    0   OK
    255   Error
*/
Status_Return ReadFileHeader(FILE *Archivo){
    char TempWord[4];
    char Ident[6];
    uint8_t i=0;
    int temp_FC, temp_GUN;

    fread(TempWord, 1, 2, Archivo);
    for(i=0; i<3; i++)
        fread(TempWord, 1, 3, Archivo);
    fread(Ident, 1, 6, Archivo);
    CU_Set_IDENT(Ident);
    fread(TempWord, 1, 1, Archivo);
    temp_FC = atoi(&TempWord[0]);
    if((temp_FC>6)||(temp_FC<0))
        return Ret_Err;
    fread(TempWord, 1, 1, Archivo);
    temp_GUN = atoi(&TempWord[0]);
    if((temp_GUN>7)||(temp_GUN<0))
        return Ret_Err;
    fread(TempWord, 1, 1, Archivo);
    //setFC(FC);
    //setGUN(GUN);
    CU_Set_FC(temp_FC);
    CU_Set_GUN(temp_GUN);
    for(i=0; i<20; i++)
        fread(TempWord, 1, 3, Archivo);
    return Ret_OK;
}


/*
    Función de lectura de bloque MARK
    Verififca que el bloque sea una Marca

    ret:
    0   OK
    255   Error
*/
Status_Return ReadMark (FILE *Archivo){

    uint8_t Temp[2];

    fread(&Temp[0], 1, 1, Archivo);
    fread(&Temp[1], 1, 1, Archivo);

    if(Temp[0]==0xFF)
        if(Temp[1]==0xFF)
            return Ret_OK;
    return Ret_Err;
}

/*
    Función de lectura de PRESET BLOCK
    Verififca que el bloque sea el bloque de preset de datos.
    Verifica los grupos grabados y los intervalos de tiempos.

    ret:
    Time Gap (>66 & <1000)
    1 Error

*/
Status_Return ReadPresetBlock (FILE *Archivo){
    uint8_t Temp, i;
    uint8_t blockLength;

    uint16_t Word1, Word2;
    uint16_t TimeGap;

    for(i=0; i<15; i++)
        GruposGrabados[i].recFlag=0;
    numGruposGrabados = 0;

    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    blockLength = Temp;
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    if(Temp!=0x0F){
        //printf("Error PresetBlock\n");
        return Ret_Err;
    }
    blockLength = blockLength-1;
    for(i=0; i<15; i++){
        fread(&Temp, 1, 1, Archivo);
        if(Temp!=0){
            //fprintf(FinalCheck, "Grupo Grabado:\t%d\n", Temp);
            createGroupFile(Temp);
            GruposGrabados[i].id=Temp;
            numGruposGrabados++;
        }
    }
    blockLength = blockLength-5;
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    if(Temp!=0x0F){
        //printf("Error PresetBlock\n");
        return Ret_Err;
    }
    blockLength = blockLength-1;
    for(i=0; i<15; i++){
        fread(&Temp, 1, 1, Archivo);
    }
    blockLength = blockLength-5;
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    if(Temp!=0x0F){
        return Ret_Err;
    }
    blockLength = blockLength-1;
    for(i=0; i<15; i++){
        fread(&Temp, 1, 1, Archivo);
        fread(&Word1, 1, 1, Archivo);
        fread(&Word2, 1, 1, Archivo);
        if(Word2!=0){
            Word1= Word1<<8;
            TimeGap = Word1|Word2;
            GruposGrabados[i].time=TimeGap;
        }
    }
    blockLength = blockLength-15;

    for(i=0; i<blockLength; i++){
        fread(&Temp, 1, 1, Archivo);
        fread(&Temp, 1, 1, Archivo);
        fread(&Temp, 1, 1, Archivo);
    }
    CU_Set_INT_TIME(TimeGap);
    //fprintf(FinalCheck, "Time Gap: %d mseg\n", (TimeGap*10));
    return Ret_OK;
}

/*
    Funcion que realiza la lectura de un bloque de datos
    Lee cada uno de los grupos almacenados verificando cada encabezado
    Guarda la infomracion de cada grupo por separado

    ret:
        Retorna la cantidad de palabras faltantes del ultimo Grupo
    255 No se pudieron leer mas grupos
*/

uint8_t ReadDataBlock (FILE *Archivo, uint8_t resto, uint8_t *grupoActual, uint8_t Save_Flag){
    uint8_t Temp, i;
    uint8_t blockLength;
    uint8_t palabraActual_1, palabraActual_2, palabraActual_3, groupSize;

    fread(&Temp, 1, 1, Archivo);
    fread(&Temp, 1, 1, Archivo);
    blockLength = Temp;

    for(i=0; i<6; i++)
        fread(&Temp, 1, 1, Archivo);
    blockLength = blockLength - 2;

    if(Temp!=0x03){
        for(i=0; i<resto; i++){
            fread(&palabraActual_1, 1, 1, Archivo);
            fread(&palabraActual_2, 1, 1, Archivo);
            fread(&palabraActual_3, 1, 1, Archivo);
            blockLength-=1;
            if(Save_Flag==1)
                writeGroupInfo(*grupoActual, palabraActual_1, palabraActual_2, palabraActual_3);
        }
        EndGroupInfo(*grupoActual);
    }

    while(blockLength>0){
        fread(&Temp, 1, 1, Archivo);
        *grupoActual = Temp;
        for(i=0; i<numGruposGrabados; i++){
            if(GruposGrabados[i].id == *grupoActual)
                GruposGrabados[i].recFlag++;
        }
        //printf("Grupo actual: %d\n", grupoActual);
        fread(&Temp, 1, 1, Archivo);
        groupSize = Temp;
        fread(&Temp, 1, 1, Archivo);
        blockLength= blockLength-1;
        if(*grupoActual==0x00){
            for(i=0; i<blockLength; i++){
                fread(&palabraActual_1, 1, 1, Archivo);
                fread(&palabraActual_2, 1, 1, Archivo);
                fread(&palabraActual_3, 1, 1, Archivo);
            }
            for(i=0; i<numGruposGrabados; i++)
                closeGroupFile(GruposGrabados[i].id);
            return 0xFF;//Final archivo
        }
        if(Temp!=0x01)
            return 1;
        if(*grupoActual > 35){
            createGroupFile(*grupoActual);
            GruposGrabados[numGruposGrabados].id=*grupoActual;
            GruposGrabados[numGruposGrabados].recFlag = 1;
            numGruposGrabados++;
        }
        if(groupSize==blockLength){
            for(i=0; i<groupSize; i++){
                fread(&palabraActual_1, 1, 1, Archivo);
                fread(&palabraActual_2, 1, 1, Archivo);
                fread(&palabraActual_3, 1, 1, Archivo);
                if(Save_Flag==1)
                    writeGroupInfo(*grupoActual, palabraActual_1, palabraActual_2, palabraActual_3);
            }
            EndGroupInfo(*grupoActual);
            return 0;
        }
        if(groupSize<blockLength){
            for(i=0; i<groupSize; i++){
                fread(&palabraActual_1, 1, 1, Archivo);
                fread(&palabraActual_2, 1, 1, Archivo);
                fread(&palabraActual_3, 1, 1, Archivo);
                blockLength= blockLength-1;
                if(Save_Flag==1)
                    writeGroupInfo(*grupoActual, palabraActual_1, palabraActual_2, palabraActual_3);
            }
            EndGroupInfo(*grupoActual);
        }
        else{
            for(i=0; i<blockLength; i++){
                fread(&palabraActual_1, 1, 1, Archivo);
                fread(&palabraActual_2, 1, 1, Archivo);
                fread(&palabraActual_3, 1, 1, Archivo);
                if(Save_Flag==1)
                    writeGroupInfo(*grupoActual, palabraActual_1, palabraActual_2, palabraActual_3);
            }
            return (groupSize-blockLength);
        }
    }
    return groupSize;
}


Status_Return ReadLastBlock (FILE *Archivo){
    uint8_t Temp, i;
    fread(&Temp, 1, 1, Archivo);
    if(Temp!=0x80){
        return Ret_Err;
    }
    for(i=0; i<254; i++)
        fread(&Temp, 1, 1, Archivo);
    return Ret_OK;
}


Status_Return ReadFileTrailer (FILE *Archivo){
    uint8_t Temp, i;
    for(i=0; i<3; i++){
        fread(&Temp, 1, 1, Archivo);
        if(Temp!=0x2F)
            return Ret_Err;
    }
    for(i=0; i<252; i++)
        fread(&Temp, 1, 1, Archivo);
    return Ret_OK;
}


Status_Return ReadDeviceTrailer (FILE *Archivo){
    uint8_t Temp, i;

    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x2F)
        return Ret_Err;
    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x44)
        return Ret_Err;
    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x4C)
        return Ret_Err;
    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x2F)
        return Ret_Err;
    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x44)
        return Ret_Err;
    fread(&Temp, 1, 1, Archivo);
    //printf("%d\n", Temp);
    if(Temp!=0x4C)
        return Ret_Err;

    for(i=0; i<24; i++)
        fread(&Temp, 1, 1, Archivo);

    if(fread(&Temp, 1, 1, Archivo)==EOF)
        return Ret_OK;

    return Ret_OK;
}

void FinalizarLectura(uint8_t resto, FILE *Archivo){
    uint8_t i=0, Temp;
    for(i=0; i<resto; i++)
        fread(&Temp, 1, 1, Archivo);
    return;
}

