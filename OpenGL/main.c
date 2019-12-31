/*
 * main - entry point
 */
#include <stdio.h>
#include <stdlib.h>

/* Basic objects */
#include "coord.h"
#include "prim.h"

int main(int argc, char* argv[])
{
    /* instantiate */
    point2d point1 = { 0, 1 };
    point2d point2 = { 1, 0 };
    point2d point3 = { -1, 0 };
    tri2d *myTriangle = NULL;
    size_t counter;

    /* initialize */
    myTriangle = new_poly2d(3, point1, point2, point3);
    if (myTriangle == NULL)
        return EXIT_FAILURE;

    /* test */
    counter = myTriangle->point_count;
    printf("Triangle coordinates:\n\n");

    printf("\tx\ty\n");
    do {
        printf("\t%d\t%d\n", myTriangle->points[counter-1].x, myTriangle->points[counter-1].y);
    } while (counter-- > 1);

    printf("\nDone\n");

    return EXIT_SUCCESS;
}