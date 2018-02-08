/* Chris Jakins */
/* CSE1320 */
/* HW3 */
/* Due 7/5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* inFile;     /*0         1          2         3*/
    char* items[] = {"book", "clothing", "flowers", "phone"};
    double sums[4];
    int numCounts[4];
    char line[51], filename[13];
    int start, end, i;

    /* validate command line input */
    if (argc != 3)
    {
        printf("usage: executable startInt stopInt\n");
        exit(1);
    }

    start = atoi(argv[1]); end = atoi(argv[2]);
    if (start > end)
    {
        printf("startInt should be <= stopInt\n");
        exit(1);
    }

    /* meat of the code here */
    for (; start <= end; start++)
    {   /* generate filename and open file */
        sprintf(filename, "data-%03d.txt", start);
        if ((inFile = fopen(filename, "r")) == NULL)
        {
            printf("unable to open %s for reading\n", filename);
            exit(1);
        }
        
        /* init/re-init arrays to 0 */
        for (i = 0; i < 4; i++)
        {
            sums[i] = 0;
            numCounts[i] = 0;
        } 
        
        /* read and parse each line */ 
        while (fgets(line, sizeof(line), inFile) != NULL) 
        {
            for (i = 0; i < 4; i++)
            {
                if (strstr(line, items[i]))
                {
                    numCounts[i]++;
                    sums[i] += atof((strstr(line, "$") + 1));
                }
            }
        }
        fclose(inFile);
        
        /* first three items are printed within the loop
           last item is printed without the trailing comma */
        printf("%s:", filename);
        for (i = 0; i < 3; i++)
        {
            if (numCounts[i] > 0)
                printf(" %s = %5.2f,", items[i], sums[i] / numCounts[i]);
            else
                printf(" %s =  none,", items[i]);
        }
        printf(" %s = %5.2f\n", items[3], sums[3] / numCounts[3]);
    }
    return EXIT_SUCCESS;
}
