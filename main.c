
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
  
  size_t img_size = width * height * channels;
  size_t gray_img_size = width * height;
  unsigned char *gray_img = (unsigned char *)malloc(gray_img_size*sizeof(unsigned char));
  
  int k = 0;
  for (int i = 0; i < img_size; i += 3) {
    gray_img[k++] = (img[i] * 11 + img[i + 1] * 16 + img[i + 2] * 5) / 32;
    //gray_img[k++] = 255;
  }
  
  stbi_write_jpg("hamster_gray.jpg", width, height, 1, gray_img, 100);
  
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
 
}
