/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
 * AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
 * GROUP: 1.2
 * DATE: 04 / 04 / 2020
 */

#ifndef CENTER_LIST_H
#define CENTER_LIST_H

#include "types.h"

/* Write your code here... */

#include "party_list.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define NULLC -1
#define MAX 10

typedef int tPosC;

typedef struct tItemC {
    tCenterName centerName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tList partyList;
} tItemC;

typedef struct {
    tItemC data[MAX];
    tPosC lastPos;
} tListC;



void createEmptyListC (tListC *L);
bool insertItemC (tItemC d, tListC *L);
void updateItemC (tItemC, tPosC, tListC *L);
void updateValidVotesC (tNumVotes, tPosC, tListC *C);
void updateNullVotesC (tNumVotes, tPosC, tListC *C);
void deleteAtPositionC (tPosC, tListC *L);
tPosC findItemC (tCenterName , tListC);
bool isEmptyListC (tListC);
tItemC getItemC (tPosC, tListC);
tPosC firstC (tListC);
tPosC lastC (tListC);
tPosC previousC (tPosC, tListC);
tPosC nextC (tPosC, tListC);
void updateListC(tList L,tPosC p,tListC *C);

#endif
