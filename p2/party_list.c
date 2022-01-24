/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
 * AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
 * GROUP: 1.2
 * DATE: 04 / 04 / 2020
 */

#include "party_list.h"

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

tPosL findPosition(tList L, tItemL d){
    //preCD: la lista no está vacía
    tPosL p;
    p = L;
    while((p->next != LNULL) && strcmp(p->next->data.partyName, d.partyName)<0)
        p = p->next;
    return p;
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

tPosL findItem(tPartyName d, tList L){  //MÁS EFICIENTE
    tPosL p;
    if(isEmptyList(L)) return LNULL;
    else {
        for (p = L; (p != LNULL) && strcmp(p->data.partyName, d)<0 ; p = p->next);
        if(p != LNULL && strcmp(p->data.partyName,d)==0) return p;
        else return LNULL;
    }
}

bool createNode(tPosL *p){
    *p=malloc(sizeof(struct tNode));
    return *p != LNULL;
}

bool insertItem(tItemL d, tList *L){
    tPosL q, p;
    if(!createNode(&q)) return false;
    else {
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL) //insertar en lista vacía
            *L = q;
        else {
            if(strcmp(d.partyName, (*L)->data.partyName)<0){ //insertar al principio //
                q->next = *L;
                *L = q;
            }
            else {
                p = findPosition(*L, d); //buscamos la posición
                q->next = p->next; //asigna NULL si insertamos al final
                p->next = q;
            }
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