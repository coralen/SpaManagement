#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ManicurePedicore.h"

int initMadicurePedicore(MedicurePedicore* MediPedi){
    char color[MAX_STRING];
    MediPedi->Manicure=False;
    MediPedi->Pedicore=False;
    MediPedi->NailArtType=eNoType;

    setMedicoreAndPedicore( MediPedi);
    setPolishColor(MediPedi, color);
    setNailArtType( MediPedi);
}

void setMedicoreAndPedicore(MedicurePedicore* MediPedi){
    printf("Do you want to get medicure? \n0- no\n1-yes\n ");
    int choise;
    scanf("%d", &choise);
    if (choise==1) MediPedi->Manicure=True;

    printf("Do you want to get pedicore? \n0- no\n1-yes\n ");
    scanf("%d", &choise);
    if (choise==1) MediPedi->Pedicore=True;
}

void setPolishColor(MedicurePedicore* MediPedi, char* color){
    printf("Enter the color that you want: \n");
    if (scanf("%s", color) != 1) {
        printf("Invalid input for color\n");
        return;
    }
    MediPedi->color = strdup(color);
    if (MediPedi->color == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
}
void setNailArtType(MedicurePedicore* MediPedi){
    printf("Enter the type of your nail art, the options are: \n0- ChromePowder\n1- Sticker\n2- French\n");
    int numType;
    scanf("%d", &numType);
    if (numType >= 0 && numType < eNoType) {
        MediPedi->NailArtType = numType;
        printf("Role set to: %s\n", NailType[MediPedi->NailArtType]);
    } else {
        printf("Invalid type number\n");
    }
}
