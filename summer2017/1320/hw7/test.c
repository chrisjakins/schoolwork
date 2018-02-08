#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char command[100];
    int i;

    for (i = 1; i <= 100; i++)
    {
        printf("FILE #%d\n", i);
        sprintf(command, "./a.out < data-%03d.txt > myoutput", i);
        system(command);
        sprintf(command, "./brezeale-hw07 < data-%03d.txt > correct", i);
        system(command);
        system("diff correct myoutput");
    }
}
