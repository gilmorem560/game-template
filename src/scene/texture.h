/*
 * texture - texture utilities
 */
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
	
/*
 * texture - a raw texture consisting of uncompressed pixel data
 */
typedef struct texture {
	unsigned char	*data;
    size_t      	width;
    size_t      	height;
    size_t      	bpp; /* 2:RGB16, 3:RGB, 4:RGBA */
} texture;

texture *texture_new(size_t width, size_t height, size_t bpp);
void texture_free(texture *texture);

/*
 * texture_rgba - rgba texture of known proportions
 */
typedef texture texture_rgba;

texture_rgba *texture_rgba_new(FILE *rgba_data, size_t width, size_t height, size_t bpp);

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __TEXTURE_H__ */
