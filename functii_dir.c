#include "structs.h"

TArbDir init_dir(char *name, TArbDir curr_dir)
{
    TArbDir dir = calloc(1, sizeof(TNodDir));
    if (dir == NULL)
        return NULL;

    dir->nume = malloc(strlen(name) + 1);
    if (dir->nume == NULL)
        return NULL;
    strcpy(dir->nume, name);
    dir->parinte = curr_dir;

    return dir;
}

void ins_dir(char *name, TArbDir *curr_dir)
{
    // este ca si functia ABC din laborator
    TArbDir *sub = &((*curr_dir)->subdir);
    TArbDir p, n;
    if (*sub == NULL)
    {
        *sub = init_dir(name, *curr_dir);
        return;
    }
    n = *sub;
    while (n)
    {
        p = n;
        if (strcmp(name, n->nume) < 0)
            n = n->st;
        else if (strcmp(name, n->nume) > 0)
            n = n->dr;
        else
        {
            printf("Directory %s already exists!\n", name);
            return;
        }
    }
    TArbDir aux = init_dir(name, *curr_dir);
    if (strcmp(name, p->nume) < 0)
        p->st = aux;
    else
        p->dr = aux;
}

int exist_dir(char *name, TArbDir dir)
{
    if (dir == NULL)
        return 0;
    if (!strcmp(dir->nume, name))
        return 1;
    else if (strcmp(dir->nume, name) < 0)
        exist_dir(name, dir->dr);
    else
        exist_dir(name, dir->st);
}

void ins_remv_dir(TArbDir *dir)
{
    if ((*dir) == NULL)
        return;
    // inseram in arbore directorul, apoi apelam pentru cei din stanga si dreapta lui
    ins_dir((*dir)->nume, &((*dir)->parinte));
    ins_remv_dir(&((*dir)->st));
    ins_remv_dir(&((*dir)->dr));
    // dupa ce terminam cu el trebuie sa il eliberam
    free((*dir)->nume);
    free((*dir));
    (*dir) = NULL;
}

void remv_dir(char *name, TArbDir *dir)
{
    if ((*dir) == NULL)
        return;
    // mergem pana cand gasim directorul care trebuie eliminat
    if (strcmp((*dir)->nume, name) > 0)
        remv_dir(name, &((*dir)->st));
    else if (strcmp((*dir)->nume, name) < 0)
        remv_dir(name, &((*dir)->dr));
    else
    {
        // cand il gasim ne uitam daca are ceva in dreapta sau in stanga lui
        // daca da putem doar sa luam acel elemement si sa il interschimbam
        if ((*dir)->st == NULL && (*dir)->dr == NULL)
        {
            delete_dir((*dir)->subdir);
            delete_file((*dir)->fisier);
            free((*dir)->nume);
            free((*dir));
            (*dir) = NULL;
        }
        else if ((*dir)->st == NULL)
        {
            TArbDir aux = *dir;
            delete_dir(aux->subdir);
            delete_file(aux->fisier);
            (*dir) = (*dir)->dr;
            free(aux->nume);
            free(aux);
        }
        else if ((*dir)->dr == NULL)
        {
            TArbDir aux = *dir;
            delete_dir(aux->subdir);
            delete_file(aux->fisier);
            (*dir) = (*dir)->st;
            free(aux->nume);
            free(aux);
        }
        else
        {
            // daca are elemente si in stanga si in dreapta
            // il interschimbam cu unul dintre ele (in cazul de aici cu cel din dreapta)
            // si apoi bagam toate elementele din subarborele din stanga inapoi in arbore
            TArbDir aux_dir = *dir;
            TArbDir aux_st = (*dir)->st;
            delete_dir(aux_dir->subdir);
            delete_file(aux_dir->fisier);
            (*dir) = (*dir)->dr;
            free(aux_dir->nume);
            free(aux_dir);
            ins_remv_dir(&(aux_st));
        }
    }
}

TArbDir cd(char *name, TArbDir dir)
{
    while (dir != NULL)
    {
        if (strcmp(dir->nume, name) > 0)
            dir = dir->st;
        else if (strcmp(dir->nume, name) < 0)
            dir = dir->dr;
        else
        {
            return dir;
        }
    }
    printf("Directory not found!\n");
    return NULL;
}

void pwd(TArbDir curr)
{
    if (curr == NULL)
        return;
    pwd(curr->parinte);
    printf("/%s", curr->nume);
}

void find_dir(char *name, TArbDir dir, int *done)
{
    // folosesc done daca am gasit directorul
    if (*done)
        return;
    if (dir == NULL)
        return;
    find_dir(name, dir->st, done);
    find_dir(name, dir->dr, done);
    if (exist_dir(name, dir->subdir))
    {
        // daca il gasesc done devine unu si il afisez cu pwd
        *done = 1;
        printf("Directory %s found!\n", name);
        // pwd merge pana la parinte asa ca trebuie sa il afisam si pe el
        pwd(dir);
        printf("/%s\n", name);
        return;
    }
    find_dir(name, dir->subdir, done);
    if (*done)
        return;
}

void print_dir(TArbDir dir)
{
    if (dir == NULL)
        return;
    // merge cat mai in stanga adica la cel mai mic lexico-grafic
    print_dir(dir->st);
    printf("%s ", dir->nume);
    print_dir(dir->dr);
}
void delete_dir(TArbDir dir)
{
    if (dir == NULL)
        return;
    delete_dir(dir->st);
    delete_dir(dir->dr);
    delete_dir(dir->subdir);
    delete_file(dir->fisier);
    free(dir->nume);
    free(dir);
}
