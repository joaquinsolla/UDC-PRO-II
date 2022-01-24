/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
 * AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
 * GROUP: 1.2
 * DATE: 04 / 04 / 2020
 */

#ifndef PARTY_LIST_H
#define PARTY_LIST_H

#include "types.h"

/* Write your code here... */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LNULL NULL

typedef struct tItemL {
    tPartyName partyName;
    tNumVotes numVotes;
} tItemL;

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
bool insertItem (tItemL, tList *L);
void deleteAtPosition (tPosL, tList *L);
tItemL getItem (tPosL, tList);
tPosL findPosition(tList L, tItemL);
void updateVotes (tNumVotes , tPosL, tList *L);
tPosL findItem (tPartyName , tList L);


#endif