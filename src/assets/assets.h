/*
 * assets - textures, models, etc.
 */
#ifndef __ASSETS_H__
#define __ASSETS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[640 * 160 * 4 + 1];
} menu_texture;

const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[97 * 47 * 4 + 1];
} font;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __ASSETS_H__ */
