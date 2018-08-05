#include "Copycass_Check.h"

#include "Lectura_Bloques.h"
#include "Control_Unit.h"
#include "../Data_Formatting/Groups.h"

FILE *Copycass;
FILE *Resultado;
char BloqueActual[86][6];
uint8_t numGrupos = 0;
uint8_t ApendCount;

BlockType identificarBloque();

Status_Return CC_Formatting_DL(char *dir_Copycass, uint8_t *AppendNum, InfoAppend InfoRet[20]){
    int i;
    float Tiempo=0, TimeGap;
    uint8_t resto=0, End_Cass=0, End_File=0;
    uint16_t TempTime;
    uint32_t blockNum=0;
    uint8_t grupoActual;
    Status_Return ret;

    ApendCount=1;

    GroupsInit();

    Copycass = fopen(dir_Copycass, "rb");
    if (Copycass == NULL){
        ret = Ret_CopyCassDirErr;
        return ret;
    }
    rewind(Copycass);

    //Open_File();

    ret = ReadVolumenHeader(Copycass);
    if(ret==Ret_Err){
        ret = Ret_VolHeaderErr;
        return ret;
    }
    blockNum++;

    if(ReadMark(Copycass)==Ret_Err){
        ret = Ret_FirstMarkErr;
        return ret;
    }
    blockNum++;

    //fprintf(FinalCheck, "DL-%d:\n", ApendCount);

    if(identificarBloque()==FileHeader){
        if(ReadFileHeader(Copycass)==Ret_Err)
            return Ret_FileHeaderErr;
    }
    else{
        ret = Ret_FileHeaderErr;
        return ret;
    }
    blockNum++;

    while (End_Cass==0){

        if(ReadMark(Copycass)==1){
            ret = Ret_MarkErr;
            return ret;
        }
        blockNum++;

        ret = ReadPresetBlock(Copycass);

        if(ret==Ret_Err){
            ret = Ret_PrestBlockErr;
            return ret;
        }
        CU_Get_IDENT(InfoRet[ApendCount-1].Ident);
        blockNum++;
        TempTime = CU_Get_INTERV_TIME();
        TimeGap = (float)TempTime/100;
        //DE_Set_INT_TIME(uint16_t TimeGap);***********************************************

        CU_Set_Scenario(IdentificarEscenario()); //Hacerlo solo con el Append Requerido

        while(End_File==0){

            switch(identificarBloque()){

            case 2:
                break;

            case 4:
                if(*AppendNum==ApendCount)
                    resto=ReadDataBlock(Copycass, resto, &grupoActual, 1);
                else
                    resto=ReadDataBlock(Copycass, resto, &grupoActual, 0);
                if(resto==255){
                    if(ReadLastBlock(Copycass)==Ret_Err){
                        ret = Ret_DataBlockErr;
                        return ret;
                    }
                    blockNum++;
                    End_File = 1;
                    break;
                }
                break;

            case 5:
                FinalizarLectura(254, Copycass);
                End_File = 1;
                if(resto!=0){
                    //Write_File("Error: Ultimo grupo de datos incompleto\n");
                }
                break;

            case 10:
                ret = Ret_UnknownBlock;
                return ret;
            }
            blockNum++;

        }

        VerificarGrupos();

        Tiempo = (float)(TempTime*GruposGrabados[0].recFlag)/100;
        //setDuracion(GruposGrabados[0].recFlag);
        //fprintf(FinalCheck, "Run Time: %f\n\n", Tiempo);
        CU_Set_T_TIME(Tiempo); //Hacerlo solo con el Appnd Requerido
        InfoRet[ApendCount-1].TotalTime=Tiempo;

        if(ReadFileTrailer(Copycass)==Ret_Err){
            ret = Ret_FileTrailerErr;
            return ret;
        }
        blockNum++;

        if(ReadMark(Copycass)==Ret_Err){
            ret = Ret_MarkErr;
            return ret;
        }
        blockNum++;

        if(identificarBloque()==FileHeader){
            ApendCount++;
            //fprintf(FinalCheck, "DL-%d:\n", ApendCount);
            if(ReadFileHeader(Copycass)==Ret_Err)
                return Ret_FileHeaderErr;
            End_File = 0;
            Tiempo = 0;
            //clear Grupos Grabados Flags;
            numGruposGrabados = 0;
            for(i=0;i<15;i++){
                GruposGrabados[i].id=0;
                GruposGrabados[i].time=0;
                GruposGrabados[i].recFlag=0;

            }
        }
        else{
            if(ReadDeviceTrailer(Copycass)==Ret_Err){
                ret = Ret_DeviceTrailerErr;
                return ret;
            }
            End_Cass = 1;
            //Write_File("Cassette Tape Complete!\n");
        }
        blockNum++;

    }

    //Write_File("\nPrograma finalizado correctamente\n- Resumen:\n");
    //fprintf(FinalCheck, "\tNumero de DLs: %d\n", ApendCount);
    //fprintf(FinalCheck, "\tNumero de Bloques: %d\n", blockNum);

    CU_Set_NumDL(ApendCount);
    //CU_Set_Num_Samples(blockNum);

    *AppendNum = ApendCount;


    fclose(Copycass);
    //fclose(FinalCheck);

    //printf("Programa finalizado\n");
    return Ret_OK;
}


BlockType identificarBloque(){
    uint8_t Var;

    fread(&Var, 1, 1, Copycass);

    if(Var==0xFF){
        fread(&Var, 1, 1, Copycass);
        return Mark;
    }

    if(Var==0x42)
        return FileHeader;

    if(Var==0x00)
        return DataBlock;

    if(Var==0x80)
        return LastBlock;

    if(Var==0x2F){
        fread(&Var, 1, 1, Copycass);
        fread(&Var, 1, 1, Copycass);
        if(Var==0x2F)
            return FileTrailer;
        if(Var==0x20)
            return DeviceTrailer;
        return BlockError;
    }
    //printf("Error: %d", Var);
    return BlockError;
}

