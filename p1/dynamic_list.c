/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#include "dynamic_list.h"

/* Write your code here... */

void createEmptyList(tList*L){
    *L = LNULL;
}

bool isEmptyList(tList L){
    return L==LNULL;
}

tItemL getItem(tPosL p, tList L){
    return p->data;
}

void updateVotes(tNumVotes d, tPosL p, tList *L){
    p->data.numVotes=d;
}

tPosL first(tList L){
    return L;
}

tPosL last(tList L){
    tPosL  p;
    for(p=L; (p->next!=LNULL); p=p->next);
    return p;
}

tPosL next(tPosL p, tList L){
    return p->next;
}

tPosL previous(tPosL p, tList L){
    tPosL q;
    if(p==L) return LNULL;
    else {
        for (q = L; (q->next != p); q = q->next);
        return q;
    }
}

tPosL findItem(tPartyName d, tList L){
    tPosL p;
    if(isEmptyList(L)) p=LNULL;
    else {
        for (p = L; (p != LNULL) && (strcmp(p->data.partyName, d)); p=p->next);
        if (p==LNULL);
        else if (strcmp(p->data.partyName, d)) p = LNULL;
    }
    return p;
}

bool createNode(tPosL *p){
    *p=malloc(sizeof(struct tNode));
    return *p != LNULL;
}

bool insertItem (tItemL d, tPosL p, tList *L) {
    tPosL q, r;
    if (!createNode(&q)) return false;
    else {
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL) *L = q;
        else if (p == LNULL) {
            for (r = *L; r->next != LNULL; r = r->next);
            r->next = q;
        } else if (p == *L) {
            q->next = p;
            *L = q;
        } else {
            q->next = p->next;
            p->next = q;
            q->data = p->data;
            p->data = d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L){
    tPosL q;
    if(p==*L)   //Borrar primer elemento
        *L=(*L)->next;
    else if (p->next==LNULL){   //Eliminar última posición
        for(q=*L; q->next != p; q=q->next); //Buscar anterior de p
        q->next=LNULL;
    }
    else{   //Eliminar pos intermedia
        q=p->next;
        p->data=q->data;
        p->next=q->next;
        p=q; //Se borra realmente el nodo siguiente a p
    }
    free(p);
}