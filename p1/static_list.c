/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#include "static_list.h"

/* Write your code here... */

void createEmptyList(tList *L) {
    L->lastPos=LNULL;}

bool isEmptyList(tList L){
    if(L.lastPos==LNULL) return true;
    else return (false);}

tPosL first(tList L){
    return 0;}

tPosL last(tList L){
    return L.lastPos;}

tPosL next(tPosL p, tList L){
    if(p==L.lastPos) return LNULL;
    else return ++p;}

tPosL previous(tPosL p, tList L){
    return --p;}

bool insertItem(tItemL d, tPosL p, tList *L) {
    tPosL i;
    if (L->lastPos == MAX - 1) return false;
    else {
        L->lastPos++;
        if (p == LNULL)
            L->data[L->lastPos] = d;
        else {
            for (i = L->lastPos; i >= p + 1; i--){
                L->data[i] = L->data[i - 1];}
            L->data[p] = d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL i;
    L->lastPos--;
    for (i = p; i <= L->lastPos; i++) {
        L->data[i] = L->data[i + 1];
    }
}

tItemL getItem(tPosL p, tList L){
    return(L.data[p]);}


void updateVotes (tNumVotes d, tPosL p, tList *L){
    L->data[p].numVotes=d;}

tPosL findItem(tPartyName d, tList L){
tPosL p;
if(isEmptyList(L)) return LNULL;
else {for(p=0; (p<L.lastPos && strcmp(L.data[p].partyName, d)); p++);

if(!strcmp(L.data[p].partyName, d)) return p;
else return LNULL;
}
}