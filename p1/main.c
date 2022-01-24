/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#include <stdio.h>
#include <string.h>
#include "types.h"
#define CODE_LENGTH 2

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif


void new(tPartyName param, tList *L) {                          //Esta función se encarga de crear nuevos partidos
    tItemL newItem;
    tPosL pos;

    pos=findItem(param, *L);
    if (pos==LNULL) {                                           //Si el partido no existía anteriormente se procede a su creación
        newItem.numVotes = 0;
        strcpy(newItem.partyName, param);

        if (insertItem(newItem, pos, L)){                       //Si la lista no está llena el partido se guarda en ella
        printf("* New: party %s\n", newItem.partyName);}
        else printf("+ Error: New not possible\n");             //Si la lista está llena el partido no se guarda

    }
    else printf("+ Error: New not possible\n");                 //Si el partido ya existía, solamente se devuelve un mensaje de error
}


void  vote(tPartyName param, tList *L, int *nullvotes, int *validvotes){                //La función se encarga de votar
    tPosL pos;

    pos=findItem(param, *L);                                                            //Buscamos si existe el partido
    if (pos == LNULL){                                                                  //En caso de no existir no es posible votarlo
    *nullvotes+=1;                                                                      //El voto se cuenta como nulo
    printf("+ Error: Vote not possible. Party %s not found. NULLVOTE\n",param);
    }
    else{                                                                               //Si el partido existe se incrementa su número de votos en 1
        int votos=getItem(pos, *L).numVotes+1;
        updateVotes(votos, pos, L);
        *validvotes+=1;                                                                 //Se incrementa también la variable de votos válidos
        printf("* Vote: party %s numvotes %d\n", param, getItem(pos, *L).numVotes );
    }
}


void stats(int itotalvoters, tList *L, int *nullvotes, int *validvotes){              //Esta función realiza las estadísitcas de los votos y partidos
    tPosL pos;
    tItemL item;
    float percent=0;

if (!isEmptyList(*L)) {                                                               //Si la lista de partidos está vacía se omiten las estadísticas de los partidos
    for (pos = first(*L); pos != LNULL; pos = next(pos, *L)) {                        //Se recorre la lista de partidos uno a uno imprimiéndose sus estadísticas
        item = getItem(pos, *L);

        if (*validvotes == 0) printf("Party %s numvotes %d (0.00%s)\n", item.partyName, item.numVotes, "%");    //Si el número de votos válidos es 0 el porcentaje se imprime...
                                                                                                                //...como 0.00 para evitar la división de votos totales entre 0
        else {
            percent = ((float) (item.numVotes) / (float) *validvotes) * 100;                                    //Si el número de votos válidos no es 0, el porcentaje será la...
            printf("Party %s numvotes %d (%.2f%s)\n", item.partyName, item.numVotes, percent, "%");             //...división de los votos del partido entre los votos válidos
        }
    }
}
    percent = ((float) (*nullvotes + *validvotes) / (float) itotalvoters) * 100;      //El porcentaje de participación es la suma de votos válidos y nulos entre los votantes totales
    printf("Null Votes %d\n", *nullvotes);
    printf("Participation: %d votes from %d voters (%.2f%s)\n", (*nullvotes + *validvotes), itotalvoters, percent, "%");
}


void illegalize(tPartyName param, tList *L, int *nullvotes, int *validvotes){         //Con esta función se ilagalizan los partidos
    tPosL pos;
    tItemL item;

    pos=findItem(param, *L);                                        //Se busca el partido en la lista
    if(pos==LNULL) printf("+ Error: Illegalize not possible\n");    //Si no existe se emite el mensaje de error
    else {                                                          //Si existe se procede a su ilegalización:
        item = getItem(pos, *L);
        *nullvotes+=item.numVotes;                                  //Se convierten los votos que tenía a nulos
        *validvotes-=item.numVotes;                                 //A los votos válidos se les resta los que tenía este partido

        deleteAtPosition(pos, L);                                   //Se elimina completamente el partido

        printf("* Illegalize: party %s\n", param);
    }
}


void processCommand(char command_number[CODE_LENGTH+1], char command, char param[NAME_LENGTH_LIMIT+1], tList *L, int *nullvotes, int *validvotes) {

    switch(command) {
        case 'N': {
            printf("********************\n");
            printf("%s %c: party %s\n", command_number, command, param);
            new(param, L);
        }
            break;
        case 'V': {
            printf("********************\n");
            printf("%s %c: party %s\n", command_number, command, param);
            vote(param, L, nullvotes, validvotes);
        }
            break;
        case 'S': {
            printf("********************\n");
            printf("%s %c: totalvoters %s\n", command_number, command, param);
            int itotalvoters=0;
            sscanf(param, "%d", &itotalvoters);                 //Convertimos al valor de param (un array) a un entero y se lo asignamos a la nueva variable
            stats(itotalvoters, L, nullvotes, validvotes);
        }
            break;
        case 'I': {
            printf("********************\n");
            printf("%s %c: party %s\n", command_number, command, param);
            illegalize(param, L, nullvotes, validvotes);
        }
            break;
        default: {
            break;
    }
    }
}

void readTasks(char *filename) {

    tList L;                            //Creamos la lista de partidos
    createEmptyList(&L);

    int nullvotes=0, validvotes=0;      //Se crean las variables para contabilizar votos nulos y válidos

    FILE *df;
    char command_number[CODE_LENGTH+1], command, param[NAME_LENGTH_LIMIT+1];
    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c %%%is", CODE_LENGTH, NAME_LENGTH_LIMIT);
            fscanf(df,format, command_number, &command, param);
            processCommand(command_number, command, param, &L, &nullvotes, &validvotes);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *file_name = "vote.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}