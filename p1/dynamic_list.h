/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"

/* Write your code here... */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LNULL -1

typedef struct tNode *tPosL;
struct tNode {
    tItemL data;
    tPosL next;
    };
typedef struct tNode *tList;


void createEmptyList (tList *L);
bool isEmptyList (tList);
tPosL first (tList);
tPosL last (tList);
tPosL next (tPosL, tList);
tPosL previous (tPosL, tList);
bool insertItem (tItemL, tPosL, tList *L);
void deleteAtPosition (tPosL, tList *L);
tItemL getItem (tPosL, tList);
void updateVotes (tNumVotes , tPosL, tList *L);
tPosL findItem (tPartyName , tList L);


#endif