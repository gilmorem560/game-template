/*
 * texture - texture utilities
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "texture.h"

/* general texture */
texture *texture_new(size_t width, size_t height, size_t bpp)
{	
	size_t data_size = width * height * bpp;
	texture *new_texture = malloc(sizeof (texture));
		new_texture->data = malloc(data_size * sizeof (char));
		new_texture->width = width;
		new_texture->height = height;
		new_texture->bpp = bpp;
	
	return new_texture;
}

/* texture_rgba - uncompressed rgba data */
texture_rgba *texture_rgba_new(FILE *rgba_data, size_t width, size_t height, size_t bpp)
{
	texture_rgba *new_texture = texture_new(width, height, bpp);
	fread(new_texture->data, sizeof (char), width*height*bpp, rgba_data);
	
	return new_texture;
}

void texture_free(texture *texture_0)
{
	free(texture_0->data);
	free(texture_0);
}



