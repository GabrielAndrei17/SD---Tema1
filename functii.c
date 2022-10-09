/* ANDREI Gabriel - 313CB */
/*--- operatii de baza pentru lista dublu circulara generica---*/
#include "functii.h"

int InsLG(TLG* aL, void* ae)
{
	if(*aL == NULL) //lista neinitializata
	{
		return InitializareLG(aL, ae);
	}
	TLG aux = malloc(sizeof(TCelulaG));
	if(aux == NULL)
	    return 0;

	TLG ultim = (*aL)->pre;

	aux->pre = ultim;
	ultim->next->pre = aux;
	aux->next = ultim->next;
	ultim->next = aux;

	aux->info = ae;


	return 1;
}
int InitializareLG(TLG* aL, void* ae)
{
	*aL = malloc(sizeof(TCelulaG));
	if(*aL == NULL)
	    return 0;

	(*aL)->next = *aL;
	(*aL)->pre = *aL;

	(*aL)->info = ae;

	return 1;
}
int VidaLG(TLG aL)
{
	if(aL == NULL)
		return 1;
	else
		return 0;
}
size_t LungimeLG(TLG *a)      /* numarul de elemente din lista */
{
	size_t lg = 1;
	if((*a)->next == *a)
		return 1;
	TLG p = (*a)->next;

     /* parcurge lista, numarand celulele */
	for (; p != *a; p = p->next)
        lg++;

	return lg;
}

void Afisare(TLG *aL, TF afiEL, FILE* f)
{
	TLG p = *aL;
	for(; p->next != *aL; p = p->next) {
		afiEL(p->info, f);
		fprintf(f, " ");
    }
	afiEL(p->info, f);
	fprintf(f, " \n");
}

/*-- operatii pentru tabela hash---*/
void AfiBuck(TH* ah, TF afiEl, FILE* f, int bucket)
{
	
    TLG p, el;
    int ok = 1; // TH este vida?
	p = ah->v[bucket];
	if(p != NULL){
        Afisare(&p, afiEl, f);
		ok = 0;
	}

	if(ok == 1)
		fprintf(f, "VIDA\n");
}
void AfiTH(TH* ah, TF afiEl, FILE* f)
{
	TLG p, el;
	int i;
	for(i = 0; i < ah->M; i++) {
        	p = ah->v[i];
			if(p != NULL){
				fprintf(f, "%d: ", i);
        		Afisare(&p, afiEl, f);
			}
    	}

}
TH* IniTH(size_t M , TFHash fh) 
{
    TH* h = (TH *) calloc(1, sizeof(TH));
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
	h->fh = fh;
    return h;
}
int InsTH(TH* a, void* ae)
{
    int cod = (a->fh(ae) % a->M);
	TLG aux = a->v[cod];

	if(aux == NULL)
		return InsLG(&a->v[cod], ae);

	do{
		if(CmpDns( aux->info, ae  ) == 0 )
			return 0;//daca numele mai apare in lista nu il adaug

		aux = aux->next;
	}while(aux != a->v[cod]);

	if(CmpDns( a->v[cod]->info, ae  ) > 0 )//trebuie sa inserez elementul pe prima poz
	{
		int rez = InsLG(&a->v[cod], ae);
		a->v[cod] = a->v[cod]->pre;//deci se va modifica inceputul listei
		return rez;
	}


	a->v[cod] = a->v[cod]->next;
	while(aux != a->v[cod])//caut primul element care nu este inaintea elementului dpdv alfabetic
	{
		if(CmpDns( a->v[cod]->info, ae  ) > 0 )
				break;

		a->v[cod] = a->v[cod]->next;
	}

    int rez = InsLG(&a->v[cod], ae);
	a->v[cod] = aux;//pastrez inceputul listei
    return rez;
}
TLG FindInTh(TH* a, void* ae)
{
	int cod = (a->fh(ae) % a->M);
	TLG aux = a->v[cod];

	if(aux == NULL)
		return NULL;

	do
	{
		if(CmpDns( aux->info, ae  ) == 0 )
			return aux;

		aux = aux->next;
	}while(aux != a->v[cod]);
	
	return NULL;
}
void Remove(TH* a, void* ae)
{
	int cod = (a->fh(ae) % a->M), rez;
	TLG aux = a->v[cod];
	int ok = 0;
	if(aux == NULL)
		return ;

	do{
		if(CmpDns( (void*)((a->v[cod])->info), ae  ) == 0 )
			{
				ok = 1;
				break;
			}

		a->v[cod] = (a->v[cod])->next;
	}while(aux != a->v[cod]);


	if(ok == 1)//trebuie sa il elimin
	{

		TLG aux2 = a->v[cod];
		a->v[cod] = a->v[cod]->pre;

		if(aux2 != (aux2)->next)
		{
			a->v[cod]->next = a->v[cod]->next->next;

			if( (aux2)->next == (aux2)->pre)//daca lista era formata din 2 celule
				a->v[cod]->next = a->v[cod]->pre = a->v[cod];
		}
		else
			a->v[cod] = NULL;
	}
}