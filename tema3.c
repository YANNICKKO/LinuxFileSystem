#include "structs.h"

#define MAXline 1 << 8

int main()
{
    TArbDir root = init_dir("root", NULL);
    TArbDir curr = root;
    char *line = malloc(MAXline);
    char *instr;

    while (fgets(line, MAXline, stdin))
    {
        instr = strtok(line, " \n");
        if (!strcmp(instr, "touch"))
        {
            char *name = strtok(NULL, " \n");
            if (exist_dir(name, curr->subdir))
                printf("Directory %s already exists!\n", name);
            else
                ins_file(name, &curr);
        }
        else if (!strcmp(instr, "mkdir"))
        {
            char *name = strtok(NULL, " \n");
            if (exist_file(name, curr->fisier))
                printf("File %s already exists!\n", name);
            else
                ins_dir(name, &curr);
        }
        else if (!strcmp(instr, "ls"))
        {
            print_dir(curr->subdir);
            print_file(curr->fisier);
            printf("\n");
        }
        else if (!strcmp(instr, "rm"))
        {
            char *name = strtok(NULL, " \n");
            if (!exist_file(name, curr->fisier))
                printf("File %s doesn't exist!\n", name);
            else
                remv_file(name, &(curr->fisier));
        }
        else if (!strcmp(instr, "rmdir"))
        {
            char *name = strtok(NULL, " \n");
            if (!exist_dir(name, curr->subdir))
                printf("Directory %s doesn't exist!\n", name);
            else
                remv_dir(name, &(curr->subdir));
        }
        else if (!strcmp(instr, "cd"))
        {
            char *name = strtok(NULL, " \n");
            if (!strcmp(name, ".."))
            {
                // in caz ca suntem in root nu facem nimic
                // daca nu mergem in spate
                if (strcmp(curr->nume, "root"))
                    curr = curr->parinte;
            }
            else
            {
                TArbDir aux = cd(name, curr->subdir);
                if (aux != NULL)
                    curr = aux;
            }
        }
        else if (!strcmp(instr, "pwd"))
        {
            pwd(curr);
            printf("\n");
        }
        else if (!strcmp(instr, "find"))
        {
            char *instr = strtok(NULL, " \n");
            char *name = strtok(NULL, " \n");
            if (!strcmp(instr, "-f"))
            {
                int done = 0;
                find_file(name, root, &done);
                if (done == 0)
                    printf("File %s not found!\n", name);
            }
            else
            {
                int done = 0;
                find_dir(name, root, &done);
                if (done == 0)
                    printf("Directory %s not found!\n", name);
            }
        }
        else if (!strcmp(instr, "quit"))
        {
            free(line);
            delete_dir(root);
            break;
        }
    }
    return 0;
}