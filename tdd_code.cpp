//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     PETER VINARCIK <xvinar00@stud.fit.vutbr.cz>
// $Date:       $2019-01-03
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Peter Vinarcik
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_head = NULL;
}

PriorityQueue::~PriorityQueue()
{
    while (m_head != NULL){
        Element_t *temp;
        temp = m_head->pNext;
        delete m_head;
        m_head = temp;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t *temp = new Element_t;                                //Vytvorenie novej struktury

    if (m_head == NULL){                                            //ak je zoznam prazdny
        temp->value = value;
        temp->pPrev = NULL;
        temp->pNext = NULL;
        m_head = temp;                                              //prida objekt
        return;
    }

    Element_t *point = m_head;                                      //ukazatel na zaciatok zoznamu
    while (point != NULL) {                                         //cyklus bude bezat kym neprideme na posledny prvok
        if (point->value > value && point->pPrev == NULL) {         //kontrola ci novy prvok nebude koren
            temp->value = value;
            temp->pPrev = NULL;
            temp->pNext = point;
            point->pPrev = temp;
            m_head = temp;                                          //novy prvok = koren
            return;
        }

        else if (point->value < value && point->pNext == NULL){     //skontrolujeme ci novy prvok nie je tail
            temp->value = value;
            point->pNext = temp;                                    //next pojde z NULL na novy prvok a az prvok->next = NULL
            temp->pPrev = point;
            temp->pNext = NULL;
            return;
        }

        else if (point->value > value){                             //ak je prvok niekde medzi, najde prvok vyssi ako on
            Element_t *tempPrev;                                    //pomocna struktura
            temp->value = value;
            tempPrev = point->pPrev;
            temp->pPrev = tempPrev;                                 //nova bude ukazovat na staru predchadzajucu
            temp->pNext = point;                                    //nova bude ukazovat na staru nasledujucu
            point->pPrev = temp;                                    //stara predchadzajuca sa stane novym prvkom
            tempPrev->pNext = temp;                                 //stra predchadzajuca bude ukazovat na novu
            return;
        }
        point = point->pNext;
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t *point = m_head;                                      //ukazatel na prvy prvok zoznamu
    while(point != NULL){                                           //cyklus az kym neprideme na koniec
        if (point->value == value && point->pPrev == NULL && point->pNext == NULL){
            m_head = NULL;                                          //ak je prvok posledny v zozname
            delete point;
            return true;                                            // == NULL + return true;
        }
        else if (point->value == value && point->pPrev == NULL){    //ak je prvok na prvom mieste
            m_head = m_head->pNext;                                 //nasledujuci sa stane prvym
            m_head->pPrev = NULL;
            delete point;                                           //zmazeme stary prvy
            return true;
        }
        else if(point->value == value && point->pNext == NULL){     //ak je prvok na poslednom mieste
            Element_t *storePrev;
            storePrev = point->pPrev;                               //pointer na predposledny sa ulozi
            storePrev->pNext = NULL;                                //predposledny bude dalej ukazovat na NULL
            delete point;                                           //zmazeme stary posledny
            return true;
        }
        point = point->pNext;
    }

    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *point = m_head;                                      //ukazatel na prvy prvok zoznamu
    while(point != NULL){                                           //kym neprejdeme na koniec zoznamu
        if (point->value == value){                                 //ak najdeme hladanu hodnotu
            return point;                                           //returneme dany objekt
        }
        point = point->pNext;                                       //iterujeme kym nenajdeme objekt
    }

    return NULL;                                                    //ak sme objekt nenasli return NULL
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_head;
}

/*** Konec souboru tdd_code.cpp ***/
