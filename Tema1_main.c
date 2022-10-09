/* ANDREI Gabriel - 313CB */
/*-- Tema1_main.c  */
#include <stdio.h>
#include "functii.h"
#include <string.h>

typedef struct {
	char* name;
	char* IP;
} DNS;

int codHash(void * ae)
{
	int sum = 0, i;
	char* string = (char*)((DNS*)ae)->name;

	for(i = 0; string[i]!='\0'; i++)
		sum += (int)string[i];

	return sum;
}
int CmpDns(void* a, void* b)
{
	DNS* el1 = (DNS*)a;
	DNS* el2 = (DNS*)b;

	return strcmp(el1->name, el2->name) ;

}
void DistrugDns(void *ae)
{
	DNS* aux = (DNS *)ae;
	free(aux->IP);
	free(aux->name);
}
void afisareD(void * element, FILE* f)
{
	DNS * aux = (DNS *) element;
	fprintf(f, "%s", aux->IP);
	
}
DNS* InitDNS(char* n, char* i)
{
	DNS* el = (DNS *)calloc(1, sizeof(DNS));
	if(el == NULL)
		return el;
	el->name = (char *)calloc(strlen(n) + 1, 1);
	el->IP = (char *)calloc(strlen(i) + 1, 1);

	strcpy(el->name, n);
	strcpy(el->IP, i);

	return el;
}

int main(int argc, char *argv[])
{
	int M = atoi(argv[1]);
	FILE *f, *f2;
	char * line = NULL;
	size_t len = 0;
	
	TH* Tabela = IniTH(M, codHash);
	if(Tabela == NULL)
		printf("eroare la initializarea tabelei\n");

	f = fopen(argv[2], "rt");
	if (f == NULL)
	{
		printf("nu exista fisierul %s\n", argv[2]);
		return -1;
	}
	f2 = fopen(argv[3], "wt");
	if (f2 == NULL)
	{
		printf("nu exista fisierul %s\n", argv[3]);
		return -1;
	}
	while (getline(&line, &len, f) != -1) {  //prelucrarea informatiei din fisier

		char * comand = strtok(line, " ");
		if (comand[strlen(comand) - 1] == '\n')
		{
			comand[strlen(comand) - 1] = '\0';
		}

		if(strcmp(comand, "put") == 0)///functia put
		{
			char * name = strtok(NULL, " ");
			char * ip = strtok(NULL, " ");

			if (ip[strlen(ip) - 1] == '\n')
			{
				ip[strlen(ip) - 1] = '\0';
			}

			DNS * informatie = InitDNS(name, ip);
			
			if (informatie == NULL)
				printf("Eroare la adaugarea DNS\n");

			InsTH(Tabela, (void *) informatie);

			continue;
		}
		if(strcmp(comand, "print") == 0)///functia print
		{
			AfiTH(Tabela, afisareD, f2);
			continue;
		}
		if(strcmp(comand, "print_bucket") == 0) ///functia print_bucket
		{
			char * numar = strtok(NULL, " ");
			int i = atoi(numar);

			AfiBuck(Tabela, afisareD, f2, i);
			continue;
		}
		if(strcmp(comand, "find") == 0) //functia find
		{
			char * name = strtok(NULL, " ");
			if (name[strlen(name) - 1] == '\n')
			{
				name[strlen(name) - 1] = '\0';
			}
			DNS * informatie = InitDNS(name, "null");

			TLG gasit = FindInTh(Tabela, (void*)informatie);

			if(gasit != NULL)
				fprintf(f2, "True\n");
			else
				fprintf(f2, "False\n");
			DistrugDns(informatie);
			continue;
		}
		if(strcmp(comand, "get") == 0) //functia get
		{
			char * name = strtok(NULL, " ");
			if (name[strlen(name) - 1] == '\n')
			{
				name[strlen(name) - 1] = '\0';
			}
			DNS * informatie = InitDNS(name, "null");
			TLG gasit = FindInTh(Tabela, (void*)informatie);

			if(gasit != NULL)
				afisareD( (void*) gasit->info, f2);
			else
				fprintf(f2, "NULL");
			fprintf(f2, "\n");
			DistrugDns(informatie);
			continue;
		}
		if(strcmp(comand, "remove") == 0) //functia remove
		{
			char * name = strtok(NULL, " ");
			if (name[strlen(name) - 1] == '\n')
			{
				name[strlen(name) - 1] = '\0';
			}
			DNS * informatie = InitDNS(name, "null");
			Remove(Tabela, (void*)informatie);

			DistrugDns(informatie);
			continue;
		}
		
		printf("Nu exista comanda %s\n", comand);
			
    }
	fclose(f);
	fclose(f2);

	return 0;
}
