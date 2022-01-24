/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
 * AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
 * GROUP: 1.2
 * DATE: 04 / 04 / 2020
 */

#include <stdio.h>
#include "types.h"
#include "center_list.h"

#define CODE_LENGTH 2

void create (tListC *C, tCenterName param1, tNumVotes iparam2){             //Esta función se encarga de crear los centros
    tPosC p;
    tItemC newItemC;

    p = findItemC(param1, *C);                                              //Buscamos si el centro ya existe
    if (p==NULLC){                                                          //Si el centro no existía se procede a su creación


        strcpy(newItemC.centerName, param1);
        newItemC.totalVoters=iparam2;
        newItemC.validVotes=0;
        newItemC.nullVotes=0;
        createEmptyList(&newItemC.partyList);

        if (insertItemC(newItemC, C) == true) printf("* Create: center %s totalvoters %d\n", param1, iparam2);      //Si la lista de centros no esta llena, el nuevo centro...
        else printf("+ Error: Create not possible\n");                                                              //...se inserta en ella, de lo contrario se devuelve error

    }
    else{                                                                   //Si el centro ya existía se emite el mensaje de error
        printf("+ Error: Create not possible\n");
    }
}

void new (tListC *C, tCenterName param1, tPartyName param2){                //Esta función crea los partidos
    tPosC p;
    tPosL q;
    tItemC center;

    p=findItemC(param1, *C);                                                //Primero se comprueba que el centro donde queremos insertar el partido existe

    if (p==NULLC) {                                                         //Si el centro no existe se emite el mensaje de error
        printf("+ Error: New not possible\n");
    }
    else{                                                                   //Si existe:
        center=getItemC(p, *C);
        q=findItem(param2, center.partyList);                               //Se busca si el partido ya existía en ese centro
        if (q==LNULL){                                                      //Si no existía se procede a su creación

            tItemL newparty;

            strcpy(newparty.partyName, param2);
            newparty.numVotes=0;

            if (insertItem(newparty, &center.partyList)){
                updateListC(center.partyList, p, C);
                printf("* New: center %s party %s\n", param1, param2);
            }
            else printf("+ Error: New not possible\n");                      //Si surge algún problema para insertar el partido, se emite el mensaje de error
        }
        else{
        printf("+ Error: New not possible\n");                               //Si el partido ya existía en el centro, se emite el error
        }

    }
}

void vote (tListC *C, tCenterName param1, tPartyName param2){                //Esta función se encarga de votar a los partidos
    tPosC p;
    tPosL q;
    tItemC center;

    p=findItemC(param1, *C);                                                 //Se comprueba que el centro existe
    if (p==NULLC){                                                           //Si el centro no existe se emite error
        printf("+ Error: Vote not possible\n");
    }
    else{                                                                    //Si el centro existe:
        center=getItemC(p, *C);
        q=findItem(param2, center.partyList);                                //Se busca el partido:
        if (q==LNULL){                                                       //Si no existe el voto cuenta como nulo
            updateNullVotesC(1, p, C);
            printf("+ Error: Vote not possible. Party %s not found in center %s. NULLVOTE\n", param2, param1);
        }
        else{                                                                //Si el partido existe:
            tItemL votedparty;

            updateValidVotesC(1, p, C);                                      //Se aumentan los votos válidos del centro

            votedparty=getItem(q, center.partyList);
            updateVotes(votedparty.numVotes+=1, q, &center.partyList);       //Se incrementan en 1 los votos del partido

            printf("* Vote: center %s party %s numvotes %d\n", param1, param2, votedparty.numVotes);

            updateListC(center.partyList, p, C);
        }
    }
}

void removeCenter (tListC *C){                                              //Esta función es la encargada de eliminar los centros con 0 votos válidos
    tPosC p;
    tItemC center;
    int q=0;

    for (p = lastC(*C); p != NULLC; p = previousC(p, *C)) {                 //Se revisa la lista de centros desde la posición 0 hasta la última posición ocupada
        center=getItemC(p, *C);

        if (center.validVotes==0){                                          //Si el centro de la posición no tiene votos válidos, este se elimina
            printf("* Remove: center %s\n", center.centerName);
            deleteAtPositionC(p, C);
            q++;
        }
    }
    if(q==0) printf("* Remove: no centers removed\n");                      //Si no se elimino ningún centro, se emite un mensaje que lo avisa
}

void stats (tListC *C){                                                     //Esta función imprime las estadísticas de los centros
    tPosC p;
    tItemC center;

    if(!isEmptyListC(*C)) {                                                 //Si la lista de centros no está vacía se procede a realizar las estadísticas:
        for (p = firstC(*C); p != NULLC; p = nextC(p, *C)) {                //Se entra en un bucle desde la primera posición de la lista hasta la última ocupada...
            center=getItemC(p, *C);
            tPosL q;                                                        //...para imrpimir las estadísiticas de todos los partidos de la lista
            float porcentaje;

            printf("Center %s\n", center.centerName);                       //Para cada centro se imprime lo siguiente:

            for (q = first(center.partyList); q != LNULL; q = next(q, center.partyList)) {                     //Se recorre toda su lista de partidos y se...
                tItemL party;                                                                                  //...imprimen los votos de cada partido con...
                party=getItem(q, center.partyList);                                                            //...su porcentaje

                if (party.numVotes==0){                                                                             //Si el partido tiene 0 votos, su porcentaje...
                    printf("Party %s numvotes %d (0.00%s)\n", party.partyName, party.numVotes, "%");                //...0% directamente para evitar la división entre 0
                }
                else {
                    porcentaje = ((float) party.numVotes / (float) center.validVotes) * 100;                        //Si el partido tiene más de 0 votos, su porcentaje...
                    printf("Party %s numvotes %d (%.2f%s)\n", party.partyName, party.numVotes, porcentaje, "%");    //...se calcula dividiendo sus votos entre el total...
                }                                                                                                   //de votos válidos del centro
            }

            printf("Null votes %d\n", center.nullVotes);                                                                                    //Se imprime el número de votos nulos
            if ((center.nullVotes+center.validVotes)==0) {                                                                                  //Se imprime el número de votos válidos y se calcula...
                printf("Participation: %d votes from %d voters (0.00%s)\n", center.nullVotes+center.validVotes, center.totalVoters, "%");   //...el porcentaje de participación evitando también...
            }                                                                                                                               //...la división entre 0
            else{
            porcentaje=((float)(center.nullVotes+center.validVotes)/(float)center.totalVoters)*100;
            printf("Participation: %d votes from %d voters (%.2f%s)\n", center.nullVotes+center.validVotes, center.totalVoters, porcentaje, "%");
            }
        }
    }
}


void processCommand(char commandNumber[CODE_LENGTH+1], char command,
        char param1[NAME_LENGTH_LIMIT+1], char param2[NAME_LENGTH_LIMIT+1], tListC *C) {

    //printf("Read from input file: %s %c %s %s\n", commandNumber, command, param1, param2);

    switch(command) {
        case 'C': {
            printf("********************\n");
            printf("%s %c: center %s totalvoters %s\n", commandNumber, command, param1, param2);
            printf("\n");
            int iparam2=0;
            sscanf(param2, "%d", &iparam2);                 //Convertimos el valor de param (un array) a un entero y se lo asignamos a la nueva variable
            create(C, param1, iparam2);
        }
            break;

        case 'N': {
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            new(C, param1, param2);
        }
            break;

        case 'V': {
            printf("********************\n");
            printf("%s %c: center %s party %s\n", commandNumber, command, param1, param2);
            printf("\n");
            vote(C, param1, param2);
        }
            break;

        case 'R': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            removeCenter (C);
        }
            break;

        case 'S': {
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            printf("\n");
            stats (C);
        }
            break;

        default: {
            break;
        }
    }
}

void readTasks(char *filename) {

    tListC C;                            //Creamos la lista de centros
    createEmptyListC(&C);

    FILE *df;
    char commandNumber[CODE_LENGTH+1], command, param1[NAME_LENGTH_LIMIT+1], param2[NAME_LENGTH_LIMIT+1];

    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c ", CODE_LENGTH);
            fscanf(df, format, commandNumber, &command);
            if (command == 'S' || command == 'R') {
                param1[0] = '\0';
                param2[0] = '\0';
            } else {
                sprintf(format, "%%%is %%%is", NAME_LENGTH_LIMIT, NAME_LENGTH_LIMIT);
                fscanf(df, format, param1, param2);
            }
            processCommand(commandNumber, command, param1, param2, &C);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *filename = "new.txt";

    if (nargs > 1) {
        filename = args[1];
    } else {
        #ifdef INPUT_FILE
        filename = INPUT_FILE;
        #endif
    }

    readTasks(filename);

    return 0;
}