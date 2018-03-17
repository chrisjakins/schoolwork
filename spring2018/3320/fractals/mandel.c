
#include "bitmap.h"

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int iteration_to_color( int i, int max );
int iterations_at_point( double x, double y, int max );
void * compute_image_threaded(void * arg);
//void compute_image( struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max );

//
//
//

typedef struct arg_struct {
    struct bitmap * bm;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    int max;
    int low_row;
    int high_row;
} arg;


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
	char c;

	// These are the default configuration values used
	// if no command line arguments are given.

	const char *outfile = "mandel.bmp";
	double xcenter = 0;
	double ycenter = 0;
	double scale = 4;
	int    image_width = 500;
	int    image_height = 500;
	int    max = 1000;
    int    num_threads = 1;
    int    low_row = 0;
    int    high_row = image_height;

	// For each command line argument given,
	// override the appropriate configuration value.

	while((c = getopt(argc,argv,"n:x:y:s:W:H:m:o:h"))!=-1) {
		switch(c) {
            case 'n':
                num_threads = atoi(optarg);
                break;
			case 'x':
				xcenter = atof(optarg);
				break;
			case 'y':
				ycenter = atof(optarg);
				break;
			case 's':
				scale = atof(optarg);
				break;
			case 'W':
				image_width = atoi(optarg);
				break;
			case 'H':
				image_height = atoi(optarg);
				break;
			case 'm':
				max = atoi(optarg);
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'h':
				show_help();
				exit(1);
				break;
		}
	}
    
    arg thread_args[num_threads];

	// Display the configuration of the image.
	printf("mandel: x=%lf y=%lf scale=%lf max=%d outfile=%s\n",
                    xcenter, ycenter, scale, max, outfile);

	// Create a bitmap of the appropriate size.
	struct bitmap *bm = bitmap_create(image_width, image_height);

	// Fill it with a dark blue, for debugging
	bitmap_reset(bm, MAKE_RGBA(0,0,255,0));
   
    /*****
        SETUP
    *****/ 
   
    int i = 0;
    int offset = image_height / num_threads;
    low_row = 0;
    high_row /= num_threads;
    for (i = 0; i < num_threads; i++) {
        thread_args[i].bm = bm;
        thread_args[i].xmin = xcenter - scale;
        thread_args[i].xmax = xcenter + scale;
        thread_args[i].ymin = ycenter - scale;
        thread_args[i].ymax = ycenter + scale;
        thread_args[i].max = max;


        if (image_height % num_threads) {
            // height is not evenly divisible by number of threads
            thread_args[i].low_row = low_row;

            if (i == num_threads - 1)
                thread_args[i].high_row = image_height;
            else 
                thread_args[i].high_row = high_row;

            low_row += offset;
            high_row += offset;
        } else {
            // is divisible
            thread_args[i].low_row = low_row;
            thread_args[i].high_row = high_row;
            low_row += offset;
            high_row += offset;
        }
    }

	// Compute the Mandelbrot image
    pthread_t row_threads[num_threads];
    for (i = 0; i < num_threads; i++) {

        printf("thread %d: %f %f %f %f %d %d %d\n", i, thread_args[i].xmin,
                    thread_args[i].xmax, thread_args[i].ymin, thread_args[i].ymax,
                    thread_args[i].max, thread_args[i].low_row, thread_args[i].high_row);

        if (pthread_create(&row_threads[i], NULL, compute_image_threaded, &thread_args[i])) {
            printf("Error creating thread\n");
            return 1;
        }
    }

    for (i = 0; i < num_threads; i++) {
        if (pthread_join(row_threads[i], NULL)) {
            printf("Error joining thread\n");
            return 1;
        }
    }
    //compute_image_threaded(&thread_args[i]);
    /*
	compute_image(bm, xcenter - scale, xcenter + scale,
                  ycenter - scale, ycenter + scale, max);
    */

	// Save the image in the stated file.
	if(!bitmap_save(bm, outfile)) {
		fprintf(stderr, "mandel: couldn't write to %s: %s\n", outfile, strerror(errno));
		return 1;
	}

	return 0;
}

/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
*/
void * compute_image_threaded(void * void_vals)
//void compute_image(struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max )
{
    arg * vals = (arg *) void_vals;
	int i, j;

	int width = bitmap_width(vals->bm);
	int height = bitmap_height(vals->bm);

	// For every pixel in the image...

	for(j = vals->low_row; j < vals->high_row; j++) {

		for(i = 0; i < width; i++) {

			// Determine the point in x,y space for that pixel.
			double x = vals->xmin + i * (vals->xmax - vals->xmin) / width;
			double y = vals->ymin + j * (vals->ymax - vals->ymin) / height;

			// Compute the iterations at that point.
			int iters = iterations_at_point(x, y, vals->max);

			// Set the pixel in the bitmap.
			bitmap_set(vals->bm, i, j, iters);
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




