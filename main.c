#define STB_IMAGE_IMPLEMENTATION
#include <math.h>
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


int main(void) {
  printf("hello world!\n");
  int width, height, channels;
  unsigned char *img = stbi_load("hamster.jpg", &width, &height, &channels, 0);
  if(img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
  }
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
 
}
