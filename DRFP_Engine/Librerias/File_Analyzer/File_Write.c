#include "File_Write.h"

void Open_File(){
    FinalCheck = fopen("Check Sum FMR DL.txt", "w");
    fprintf(FinalCheck, "       -- Programa de an�lisis de DL para sistema FMR --\n");
    fprintf(FinalCheck, "SIAG - Servicio de An�lisis Operativo Armas y Guerra Electr�nica\n\n");
}

void Write_File(char *line){
    fprintf(FinalCheck, "%s", line);
    return;
}
