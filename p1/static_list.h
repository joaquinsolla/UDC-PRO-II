/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

/* Write your code here... */

#include <stdbool.h>
#include <string.h>
#define LNULL -1
#define MAX 25

typedef int tPosL;

typedef struct tList {
    tItemL data[MAX];
    tPosL lastPos;
    } tList;

void createEmptyList (tList *L);
bool isEmptyList (tList);
tPosL first (tList);
tPosL last (tList);
tPosL next (tPosL, tList);
tPosL previous (tPosL, tList);
bool insertItem (tItemL, tPosL, tList *L);
void deleteAtPosition (tPosL, tList *L);
tItemL getItem (tPosL, tList);
void updateVotes (tNumVotes , tPosL, tList *L); //
tPosL findItem (tPartyName , tList);


#endif