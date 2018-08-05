#ifndef LECTURA_BLOQUES_H

#define LECTURA_BLOQUES_H

#include "../Variables_Globales.h"



typedef enum {
    VolumenHeader   = 0,    //44XXXX
    FileHeader      = 1,    //422020
    Mark            = 2,    //FFFF
    PresetBlock     = 3,    //000054
    DataBlock       = 4,    //000054
    LastBlock       = 5,    //800000
    FileTrailer     = 6,    //2F2F2F
    DeviceTrailer   = 7,    //2F2E20
    LastDataBlock   = 8,
    BlockError      = 10
} BlockType;

struct Grupo {
    uint8_t id;
    uint16_t time;
    uint32_t recFlag;
};

struct Grupo GruposGrabados[15];

uint8_t numGruposGrabados;

Status_Return ReadVolumenHeader(FILE *Archivo);
Status_Return ReadFileHeader(FILE *Archivo);
Status_Return ReadPresetBlock (FILE *Archivo);
uint8_t ReadDataBlock (FILE *Archivo, uint8_t resto, uint8_t *grupoActual, uint8_t Save_Flag);
Status_Return ReadLastBlock (FILE *Archivo);
Status_Return ReadFileTrailer (FILE *Archivo);
Status_Return ReadDeviceTrailer (FILE *Archivo);
Status_Return ReadMark (FILE *Archivo);
void FinalizarLectura(uint8_t resto, FILE *Archivo);




#endif // LECTURA_BLOQUES_H
