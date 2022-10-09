/*-- functii.h --- LISTA DUBLU INLANTUITA GENERICA FARA SANTINELA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{
  void* info;           /* adresa informatie */
  struct celulag *next;   /* adresa urmatoarei celule */
  struct celulag *pre;
} TCelulaG, *TLG;    /* tipurile Celula, Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);

/* functii lista generica */
int InsLG(TLG*, void*);  //insereaza la sfarsitul listei elementul
size_t LungimeLG(TLG*);   /* numarul de elemente din lista */

void Afisare(TLG*, TF, FILE* f);/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
int InitializareLG(TLG* aL, void* ae);//initializeaza lista
int VidaLG(TLG aL);//lista e vida (nealocata)
int CmpDns(void* a, void* b);
void DistrugDns(void *ae);

/*--- TABELA HASH---*/
typedef struct
{
    int M;
    TFHash fh;
    TLG *v;
} TH;//tabela H

int InsTH(TH* a, void*ae);//insereaza elementul in tabela
TH* IniTH(size_t M, TFHash fh);//initializeaza tabela
void AfiTH(TH* ah, TF afiEl, FILE* f);//afisaza elementele din tabelea
TLG FindInTh(TH* a, void* ae);//returneaza lista in care se afla elementul dat sau NULL
void Remove(TH* a, void* ae);//elimina din tabela elementul dat
void AfiBuck(TH* ah, TF afiEl, FILE* f, int bucket);//afisare elemente dintr-un bucket specific

#endif
