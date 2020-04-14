#ifndef BSP_IMAGE_H
#define BSP_IMAGE_H "BSP_IMAGE_H"

int is_in_array(short x, short y, short height, short width);
void bilinera_interpolation(short** in_array, short height, short width, 
                            short** out_array, short out_height, short out_width);
#endif //BSP_IMAGE_H