/*--- tarb.h ---*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

struct fisier;
struct director;

typedef struct fisier
{
	char *nume;
	struct director *parinte;
	struct fisier *st, *dr;
} TNodFis, *TArbFis, **AArbFis;

typedef struct director
{
	char *nume;
	struct director *parinte;
	struct fisier *fisier;
	struct director *subdir;
	struct director *st, *dr;
} TNodDir, *TArbDir, **AArbDir;

// functii directoare

TArbDir init_dir(char *, TArbDir);	   // initializeaza cu nume si parinte
void ins_dir(char *, TArbDir *);	   // inserare in director
int exist_dir(char *, TArbDir);		   // verifica existenta intr-un arbore a unui nume
void ins_remv_dir(TArbDir *);		   // functia necesara remove-ului de inserare inapoi a elementelor pierdute
void remv_dir(char *, TArbDir *);	   // functia de remove dir
void find_dir(char *, TArbDir, int *); // functia de find
void print_dir(TArbDir);			   // functia de print
void delete_dir(TArbDir);			   // functia de delete

TArbDir cd(char *, TArbDir); // functia de cd
void pwd(TArbDir);			 // functia de pwd

// functii fisiere (toate sunt cam la fel ca la directoare)

TArbFis init_file(char *, TArbDir);
void ins_file(char *, TArbDir *);
int exist_file(char *, TArbFis);
void ins_remv_file(TArbFis *);
void remv_file(char *, TArbFis *);
void find_file(char *, TArbDir, int *);
void print_file(TArbFis);
void delete_file(TArbFis);

#endif
