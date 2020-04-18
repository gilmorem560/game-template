/*
 * texture - texture utilities
 */
#include <stdio.h>
#include <stdlib.h>
#include "texture.h"

/* general texture */
texture *texture_new(size_t width, size_t height, size_t bpp)
{	
	size_t data_size = width * height * bpp;
	texture *texture = malloc(sizeof (texture));
		texture->data = malloc(data_size * sizeof (char));
		texture->width = width;
		texture->height = height;
		texture->bpp = bpp;
	
	return texture;
}

void texture_free(texture *texture)
{
	free(texture->data);
	free(texture);
}

/* texture_rgba - uncompressed rgba data */
texture_rgba *texture_rgba_new(FILE *rgba_data, size_t width, size_t height, size_t bpp)
{
	texture_rgba *texture = texture_new(width, height, bpp);
	fread(texture->data, sizeof (char), width*height*bpp, rgba_data);
	
	return texture;
}

