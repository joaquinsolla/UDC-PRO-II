/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
 * AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
 * GROUP: 1.2
 * DATE: 04 / 04 / 2020
 */

#include "types.h"
#include "center_list.h"

/* Write your code here... */

void createEmptyListC (tListC *L) {
    L->lastPos=NULLC;}

bool insertItemC (tItemC d, tListC *L){
    tPosC i;
    if (L->lastPos == MAX-1){ //comprobamos si el array está lleno
        return false;}
    else{
        if (isEmptyListC(*L) || (strcmp(d.centerName, L->data[L->lastPos].centerName))>0 ){
            L->lastPos++;
            L->data[L->lastPos] = d;
        }
        else{
            L->lastPos++;
            for (i = L->lastPos; i>0 && strcmp(d.centerName, L->data[i-1].centerName)<0; i--)
                L->data[i] = L->data[i-1];
            L->data[i] = d;
        }
        return true;
    }
}

void updateItemC (tItemC d, tPosC p, tListC *L){
    L->data[p]=d;}


void updateValidVotesC (tNumVotes numVotes, tPosC p, tListC *C){
    C->data[p].validVotes+=numVotes;
}

void updateNullVotesC (tNumVotes numVotes, tPosC p, tListC *C){
    C->data[p].nullVotes+=numVotes;
}

void deleteAtPositionC (tPosC p, tListC *L) {
    tPosC i;
    L->lastPos--;
    for (i = p; i <= L->lastPos; i++) {
        L->data[i] = L->data[i + 1];
    }
}

tPosC findItemC (tCenterName d, tListC L){      //MÁS EFICIENTE
    tPosC p;
    if(L.lastPos == NULLC)
        return NULLC;
    else if (strcmp(d, L.data[0].centerName)<0 || strcmp(d, L.data[L.lastPos].centerName)>0){ //si es mayor o menor que todos los elementos de la lista
        return NULLC;}
    else {
        for(p=0; (p<L.lastPos) && strcmp(L.data[p].centerName, d)<0; p++); //recorremos la lista
        //comprobamos si encontramos el elemento
        if (strcmp(L.data[p].centerName, d)==0) return p;
        else return NULLC;
    }
}

bool isEmptyListC (tListC L){
    if(L.lastPos==NULLC) return true;
    else return (false);}

tItemC getItemC (tPosC p, tListC L){
    return(L.data[p]);}

tPosC firstC (tListC L){
    return 0;}

tPosC lastC (tListC L){
    return L.lastPos;}

tPosC previousC (tPosC p, tListC L){
    return --p;}

tPosC nextC (tPosC p, tListC L){
    if(p==L.lastPos) return NULLC;
    else return ++p;}

void updateListC(tList L,tPosC p,tListC *C){
    C->data[p].partyList=L;}