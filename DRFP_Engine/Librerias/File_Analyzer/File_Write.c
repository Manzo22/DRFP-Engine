#include "File_Write.h"

void Open_File(){
    FinalCheck = fopen("Check Sum FMR DL.txt", "w");
    fprintf(FinalCheck, "       -- Programa de análisis de DL para sistema FMR --\n");
    fprintf(FinalCheck, "SIAG - Servicio de Análisis Operativo Armas y Guerra Electrónica\n\n");
}

void Write_File(char *line){
    fprintf(FinalCheck, "%s", line);
    return;
}
