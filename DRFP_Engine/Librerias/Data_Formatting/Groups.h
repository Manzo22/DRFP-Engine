#ifndef GROUPS
#define GROUPS

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

FILE *Group_1;
FILE *Group_2;
FILE *Group_3;
FILE *Group_4;
FILE *Group_5;
FILE *Group_6;
FILE *Group_7;
FILE *Group_8;
FILE *Group_9;
FILE *Group_10;
FILE *Group_11;
FILE *Group_12;
FILE *Group_13;
FILE *Group_14;
FILE *Group_15;
FILE *Group_16;
FILE *Group_17;
FILE *Group_18;
FILE *Group_19;
FILE *Group_20;
FILE *Group_21;
FILE *Group_22;
FILE *Group_23;
FILE *Group_24;
FILE *Group_25;
FILE *Group_26;
FILE *Group_27;
FILE *Group_28;
FILE *Group_29;
FILE *Group_30;
FILE *Group_31;
FILE *Group_32;
FILE *Group_33;
FILE *Group_34;
FILE *Group_80;
FILE *Group_81;
FILE *Group_82;
FILE *Group_84;
FILE *Group_85;
FILE *Group_86;

FILE *GroupsFiles[87];

void GroupsInit();
uint8_t writeGroupInfo (uint8_t GroupID, uint8_t word1, uint8_t word2, uint8_t word3);
uint8_t createGroupFile (uint8_t GroupID);
void EndGroupInfo(uint8_t GroupID);
void closeGroupFile(uint8_t GroupID);
void openGroupFile(uint8_t GroupID);
uint8_t readGroupInfo(uint8_t GroupID, uint8_t *word1, uint8_t *word2, uint8_t *word3);

#endif // GROUPS
