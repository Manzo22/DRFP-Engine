#include "Groups.h"

void GroupsInit(){
    GroupsFiles[1] = Group_1;
    GroupsFiles[2] = Group_2;
    GroupsFiles[3] = Group_3;
    GroupsFiles[4] = Group_4;
    GroupsFiles[5] = Group_5;
    GroupsFiles[6] = Group_6;
    GroupsFiles[7] = Group_7;
    GroupsFiles[8] = Group_8;
    GroupsFiles[9] = Group_9;
    GroupsFiles[10] = Group_10;
    GroupsFiles[11] = Group_11;
    GroupsFiles[12] = Group_12;
    GroupsFiles[13] = Group_13;
    GroupsFiles[14] = Group_14;
    GroupsFiles[15] = Group_15;
    GroupsFiles[16] = Group_16;
    GroupsFiles[17] = Group_17;
    GroupsFiles[18] = Group_18;
    GroupsFiles[19] = Group_19;
    GroupsFiles[20] = Group_20;
    GroupsFiles[21] = Group_21;
    GroupsFiles[22] = Group_22;
    GroupsFiles[23] = Group_23;
    GroupsFiles[24] = Group_24;
    GroupsFiles[25] = Group_25;
    GroupsFiles[26] = Group_26;
    GroupsFiles[27] = Group_27;
    GroupsFiles[28] = Group_28;
    GroupsFiles[29] = Group_29;
    GroupsFiles[30] = Group_30;
    GroupsFiles[31] = Group_31;
    GroupsFiles[32] = Group_32;
    GroupsFiles[33] = Group_33;
    GroupsFiles[34] = Group_34;
    GroupsFiles[80] = Group_80;
    GroupsFiles[81] = Group_81;
    GroupsFiles[82] = Group_82;
    GroupsFiles[84] = Group_84;
    GroupsFiles[85] = Group_85;
    GroupsFiles[86] = Group_86;

}

uint8_t createGroupFile(uint8_t GroupID){
    char FileName[20];
    char Temp[3];
    itoa(GroupID, Temp, 10);
    strcpy(FileName, "Grupos/Grupo_");
    strcat(FileName, Temp);
    strcat(FileName, ".txt");
    GroupsFiles[GroupID] = fopen(FileName, "wb");
    if(GroupsFiles[GroupID]!=NULL)
        return 1;
    return 0;
}

uint8_t writeGroupInfo(uint8_t GroupID, uint8_t word1, uint8_t word2, uint8_t word3){
    fwrite(&word1, 1, 1, GroupsFiles[GroupID]);
    fwrite(&word2, 1, 1, GroupsFiles[GroupID]);
    fwrite(&word3, 1, 1, GroupsFiles[GroupID]);
    return 0;
}

void EndGroupInfo(uint8_t GroupID){
    //char Temp[2];
    //strcpy(Temp, "\n");
    //fwrite(Temp, 2, 1, GroupsFiles[GroupID]);
}

void closeGroupFile(uint8_t GroupID){
    fclose(GroupsFiles[GroupID]);
}

void openGroupFile(uint8_t GroupID){
    char FileName[20];
    char Temp[3];
    itoa(GroupID, Temp, 10);
    strcpy(FileName, "Grupos/Grupo_");
    strcat(FileName, Temp);
    strcat(FileName, ".txt");
    GroupsFiles[GroupID] = fopen(FileName, "rb");
}

uint8_t readGroupInfo(uint8_t GroupID, uint8_t *word1, uint8_t *word2, uint8_t *word3){
    fread(word1, 1, 1, GroupsFiles[GroupID]);
    fread(word2, 1, 1, GroupsFiles[GroupID]);
    fread(word3, 1, 1, GroupsFiles[GroupID]);
    return 0;
}
