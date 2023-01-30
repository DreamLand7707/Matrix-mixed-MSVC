#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    system("color 02");
    int memory_size = 0;
    printf("please enter memory\n");
    while (memory_size == 0)
    {
        scanf_s("%d", &memory_size);
    }
    getchar();
    system("CLS");
    int loop_pos[99] = {0};
    unsigned char *memory = (unsigned char *)malloc(memory_size);
    unsigned char *command = (unsigned char *)malloc(4096);
    int pos1 = -1;

    memset(memory, 0, memory_size);
    memset(command, 0, 4096);

    int pos = 0;
    int command_length = 0;
    printf("BF> ");

    for (fgets((char *)command, 4096, stdin);; fgets((char *)command, 4096, stdin))
    {
        pos1 = -1;
        if (strcmp((char *)command, "quit\n") == 0)
            break;
        if (strcmp((char *)command, "cls\n") == 0)
        {
            system("cls");
            printf("BF> ");
            continue;
        }
        command_length = strlen((char *)command);
        if (command_length == 0)
            continue;
        for (int i = 0; i < command_length; i++)
        {
            if (command[i] == '\n')
                break;
            if (command[i] == '<')
            {
                if (pos == 0)
                {
                    printf("memory overflow\n");
                    break;
                }
                pos--;
            }
            else if (command[i] == '>')
                if (pos == memory_size)
                    pos = 0;
                else
                    pos++;
            else if (command[i] == '+')
                if (memory[pos] == 255)
                    memory[pos] = 0;
                else
                    memory[pos]++;
            else if (command[i] == '-')
                if (memory[pos] == 0)
                    memory[pos] = 255;
                else
                    memory[pos]--;
            else if (command[i] == '.')
                printf("%c", memory[pos]);

            else if (command[i] == '/')
                printf("%d\n", memory[pos]);
            else if (command[i] == '{')
                printf("pos: %d\n", pos);
            else if (command[i] == ';')
                pos = 0;
            else if (command[i] == ':')
                memory[pos] = 0;
            else if (command[i] == '*')
            {
                int range, begin;
                scanf_s("%d%d", &begin, &range);
                for (int i = 0; (i < range) && (i + begin < memory_size); i++)
                {
                    if (i && (i % 16 == 0))
                        printf("\n");
                    printf("%d ", memory[i + begin]);
                }
                printf("\n");
                getchar();
            }
            else if (command[i] == '?')
            {
                printf("< to left     > to right\n"
                       ", to putin    . to putout    / to putout in dex    * to watch memory    { to pos\n"
                       "[] to loop    + to add       - to sub\n"
                       "; let pos=0   : let mem = 0\n");
            }

            else if (command[i] == ',')
                memory[pos] = _getche();
            else if (command[i] == '[')
            {
                if (memory[pos])
                {
                    pos1++;
                    loop_pos[pos1] = i;
                    continue;
                }
                else
                {
                    int j;
                    for (j = i + 1; command[j] != ']'; j++)
                        ;
                    i = j;
                }
            }
            else if (command[i] == ']')
                if (memory[pos])
                    i = loop_pos[pos1];
                else
                {
                    pos1--;
                    continue;
                }
            else
                printf("unknown command %c\n", command[i]);
        }
        printf("\nBF> ");
    }


    free(memory);
    free(command);
}