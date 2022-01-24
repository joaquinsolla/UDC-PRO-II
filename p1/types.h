/*
* TITLE: PROGRAMMING II LABS
* SUBTITLE: Practical 1
* AUTHOR 1: JOAQUÍN SOLLA VÁZQUEZ LOGIN 1: joaquin.solla
* AUTHOR 2: ADRIÁN FRAGUELA CASTRO LOGIN 2: a.fraguela
* GROUP: 1.2
* DATE: 20 / 02 / 2020
*/

#ifndef TYPES_H
#define TYPES_H

#define NAME_LENGTH_LIMIT 20

typedef char tPartyName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;

typedef struct tItemL {
    tPartyName partyName;
    tNumVotes numVotes;
} tItemL;


#endif //TYPES_H