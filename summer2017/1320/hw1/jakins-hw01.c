/* Chris Jakins */
/* Brezeale CSE1320 */
/* Homework 1 */
/* Due 6/14 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	const int NUMROWS = 10;
	const int NUMCOLS = 4;
	double cutoff = 50.0;
	int numValues; 		/* per row */
	double value, total;
	int row, col;

	for (row = 0; row < NUMROWS; row++)
	{
        /* reset row specific values */
		numValues = 0;
        total = 0;

        for (col = 0; col < NUMCOLS; col++)
		{
            value = (rand() % 10000) / 100.0;
            if (value <= cutoff)
            {
                printf("%5.2f  ", value);
                total += value;
				numValues++;
			}
			else
			{
				printf("%7c", ' ');
			}
		}
		/* '|' and '\n' printed even if no values were */
		printf("|");
		if (numValues > 0)
		{
			printf("%7.2f", total / numValues);
		}
		printf("\n");
	}
}
