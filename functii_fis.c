#include "structs.h"

TArbFis init_file(char *name, TArbDir curr_dir)
{
    TArbFis file = calloc(1, sizeof(TNodFis));
    if (file == NULL)
        return NULL;

    file->nume = malloc(strlen(name) + 1);
    if (file->nume == NULL)
        return NULL;
    strcpy(file->nume, name);
    file->parinte = curr_dir;

    return file;
}

void ins_file(char *name, TArbDir *curr_dir)
{
    // este ca si functia ABC din laborator
    TArbFis *file = &((*curr_dir)->fisier);
    TArbFis p, n;
    if (*file == NULL)
    {
        *file = init_file(name, *curr_dir);
        return;
    }
    n = *file;
    while (n)
    {
        p = n;
        if (strcmp(name, n->nume) < 0)
            n = n->st;
        else if (strcmp(name, n->nume) > 0)
            n = n->dr;
        else
        {
            printf("File %s already exists!\n", name);
            return;
        }
    }
    TArbFis aux = init_file(name, *curr_dir);
    if (strcmp(name, p->nume) < 0)
        p->st = aux;
    else
        p->dr = aux;
}

int exist_file(char *name, TArbFis file)
{
    if (file == NULL)
        return 0;
    if (!strcmp(file->nume, name))
        return 1;
    else if (strcmp(file->nume, name) < 0)
        exist_file(name, file->dr);
    else
        exist_file(name, file->st);
}

void ins_remv_file(TArbFis *file)
{
    if ((*file) == NULL)
        return;
    // inseram in arbore fisierul, apoi apelam pentru cei din stanga si dreapta lui
    ins_file((*file)->nume, &((*file)->parinte));
    ins_remv_file(&((*file)->st));
    ins_remv_file(&((*file)->dr));
    // dupa ce terminam cu el trebuie sa il eliberam
    free((*file)->nume);
    free((*file));
    (*file) = NULL;
}

void remv_file(char *name, TArbFis *file)
{
    if ((*file) == NULL)
        return;
    // mergem pana cand gasim fisierul care trebuie eliminat
    if (strcmp((*file)->nume, name) > 0)
        remv_file(name, &((*file)->st));
    else if (strcmp((*file)->nume, name) < 0)
        remv_file(name, &((*file)->dr));
    else
    {
        // cand il gasim ne uitam daca are ceva in dreapta sau in stanga lui
        // daca da putem doar sa luam acel elemement si sa il interschimbam
        if ((*file)->st == NULL && (*file)->dr == NULL)
        {
            free((*file)->nume);
            free((*file));
            (*file) = NULL;
        }
        else if ((*file)->st == NULL)
        {
            TArbFis aux = *file;
            (*file) = (*file)->dr;
            free(aux->nume);
            free(aux);
        }
        else if ((*file)->dr == NULL)
        {
            TArbFis aux = *file;
            (*file) = (*file)->st;
            free(aux->nume);
            free(aux);
        }
        else
        {
            // daca are elemente si in stanga si in dreapta
            // il interschimbam cu unul dintre ele (in cazul de aici cu cel din dreapta)
            // si apoi bagam toate elementele din subarborele din stanga inapoi in arbore
            TArbFis aux_file = *file;
            TArbFis aux_st = (*file)->st;
            (*file) = (*file)->dr;
            free(aux_file->nume);
            free(aux_file);
            ins_remv_file(&(aux_st));
        }
    }
}

void find_file(char *name, TArbDir dir, int *done)
{
    // folosesc done daca am gasit fisierul
    if (dir == NULL)
        return;
    find_file(name, dir->st, done);
    find_file(name, dir->dr, done);
    if (exist_file(name, dir->fisier))
    {
        // daca il gasesc done devine unu si il afisez cu pwd
        *done = 1;
        printf("File %s found!\n", name);
        pwd(dir);
        printf("\n");
        return;
    }
    find_file(name, dir->subdir, done);
    if (*done)
        return;
}

void print_file(TArbFis file)
{
    if (file == NULL)
        return;
    // merge cat mai in stanga adica la cel mai mic lexico-grafic
    print_file(file->st);
    printf("%s ", file->nume);
    print_file(file->dr);
}

void delete_file(TArbFis fis)
{
    if (fis == NULL)
        return;
    delete_file(fis->st);
    delete_file(fis->dr);
    free(fis->nume);
    free(fis);
}