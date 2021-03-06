#include "bitmap.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int iteration_to_color( int i, int max );
int iterations_at_point( double x, double y, int max );
void compute_image( struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max );

void show_help()
{
	printf("Use: mandel [options]\n");
	printf("Where options are:\n");
	printf("-m <max>    The maximum number of iterations per point. (default=1000)\n");
	printf("-x <coord>  X coordinate of image center point. (default=0)\n");
	printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
	printf("-s <scale>  Scale of the image in Mandlebrot coordinates. (default=4)\n");
	printf("-W <pixels> Width of the image in pixels. (default=500)\n");
	printf("-H <pixels> Height of the image in pixels. (default=500)\n");
	printf("-o <file>   Set output file. (default=mandel.bmp)\n");
	printf("-h          Show this help text.\n");
	printf("\nSome examples are:\n");
	printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
	printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
	printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}

int main( int argc, char *argv[] )
{
    // max # processes to run at once
    int num_processes = 1;
    if (argc > 1) {
        num_processes = atoi(argv[1]);
    }

	char outfile[20];
	double xcenter = 0.19079;
	double ycenter = 0.551489;
	double current_scale = 2;
    double final_scale = 0.00005;
	int    image_width = 500;
	int    image_height = 500;
	int    max = 5000;
    int total_proc = 50;

    int i = 0, proc_count = 1;
    pid_t pid = 1;

    double offset = (current_scale - final_scale) / total_proc;

    // START TIMING
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (proc_count = 0; proc_count <= 50; proc_count++) {
        if (proc_count == 0) {
            // get the ball rolling here
            for (i = 0; i < num_processes; i++) {
                if (pid) {
                    // TODO subtracts offset on the first one
                    current_scale -= offset;
                    proc_count++;
                    pid = fork();
                }
            }
        } else {
            // wait for next child to finish since we already have
            // *num_processes* running
            int status = 0;
            wait(&status);
            
            // adjust scale for next child
            current_scale -= offset;
            pid = fork();
        }

        if (!pid) {
            // Display the configuration of the image.

            sprintf(outfile, "mandel%d.bmp", proc_count);
            printf("mandel: scale=%lf outfile=%s\n", current_scale, outfile);

            // Create a bitmap of the appropriate size.
            struct bitmap *bm = bitmap_create(image_width, image_height);

            // Fill it with a dark blue, for debugging
            bitmap_reset(bm, MAKE_RGBA(0,0,255,0));

            // Compute the Mandelbrot image
            compute_image(bm, xcenter - current_scale, xcenter + current_scale,
                          ycenter - current_scale, ycenter + current_scale, max);

            // Save the image in the stated file.
            if(!bitmap_save(bm,outfile)) {
                fprintf(stderr, "mandel: couldn't write to %s: %s\n", outfile, strerror(errno));
                return 1;
            }

            exit(0);
        }
    }

    struct timespec finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    printf("time taken: %ld\n", (finish.tv_sec * 1000000000 + finish.tv_nsec) -
                                (start.tv_sec * 1000000000 + start.tv_nsec));

	return 0;
}

/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
*/

void compute_image( struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max )
{
	int i,j;

	int width = bitmap_width(bm);
	int height = bitmap_height(bm);

	// For every pixel in the image...

	for(j=0;j<height;j++) {

		for(i=0;i<width;i++) {

			// Determine the point in x,y space for that pixel.
			double x = xmin + i*(xmax-xmin)/width;
			double y = ymin + j*(ymax-ymin)/height;

			// Compute the iterations at that point.
			int iters = iterations_at_point(x,y,max);

			// Set the pixel in the bitmap.
			bitmap_set(bm,i,j,iters);
		}
	}
}

/*
Return the number of iterations at point x, y
in the Mandelbrot space, up to a maximum of max.
*/

int iterations_at_point( double x, double y, int max )
{
	double x0 = x;
	double y0 = y;

	int iter = 0;

	while( (x*x + y*y <= 4) && iter < max ) {

		double xt = x*x - y*y + x0;
		double yt = 2*x*y + y0;

		x = xt;
		y = yt;

		iter++;
	}

	return iteration_to_color(iter,max);
}

/*
Convert a iteration number to an RGBA color.
Here, we just scale to gray with a maximum of imax.
Modify this function to make more interesting colors.
*/

int iteration_to_color( int i, int max )
{
	int gray = 255*i/max;
	return MAKE_RGBA(gray,gray,gray,0);
}




