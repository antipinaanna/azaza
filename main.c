#define STB_IMAGE_IMPLEMENTATION
#include <math.h>
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include<strings.h>
#include<stdio.h>
#include<stdlib.h>

void svertka_Gauss (size_t w, size_t h, unsigned char **graph, unsigned char **graph1){
    int i, j;
    printf ("6");
    for (i = 1; i < h + 1; i++){
        printf ("8");
        for (j = 1; j < w + 1; j++){
            graph[i - 1][j - 1] = unsigned char((graph1[i - 1][j - 1] + graph1[i - 1][j + 1] + graph1[i + 1][j - 1] + graph1[i + 1][j + 1])* 0.0924 + (graph1[i - 1][j] + graph1[i][j - 1] + graph1[i][j + 1] + graph1[i + 1][j])* 0.1192 + graph1[i][j] * 0.1538);
        }
    }
   return;
}
    

void Gauss_blur(size_t w, size_t h, unsigned char **graph, unsigned char **graph1){
    int i, j;
    for (i = 1; i < h + 1; i++){
        for (j = 1; j < w + 1; j++){
            graph1[i][j] = graph[i - 1][j - 1];
        }    
    }
    printf ("4");
    for (i = 1; i < h + 1; i++){
        graph1[i][0] = graph[i - 1][0];
        graph1[i][w + 1] = graph[i - 1][w - 1];
    }
    for (j = 0; j < w + 2; j++){
        graph1[0][j] = graph1[1][j];
        graph1[h + 1][j] = graph1[h][j];
    }
    printf ("5");
    svertka_Gauss (w, h, graph, graph1);
    return;  
}


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
  unsigned char *gray_img = malloc(gray_img_size);
  
  int k = 0, i, j;
  for (i = 0; i < img_size; i += 3) {
    gray_img[k++] = (img[i] * 11 + img[i + 1] * 16 + img[i + 2] * 5) / 32;
    //gray_img[k++] = 255;
  }
     printf ("1");
    unsigned char **graph = (unsigned char **)malloc(height * sizeof(unsigned char*));
    for (i = 0; i < height; i++) graph[i] = (unsigned char*)malloc(width * sizeof (unsigned char));
    unsigned char **graph1 = (unsigned char **)malloc((height + 2) * sizeof(unsigned char*));
    for (i = 0; i < height; i++) graph1[i] = (unsigned char*)malloc((width + 2) * sizeof (unsigned char));
    printf ("2");
    for (i = 0; i < height; i++)
      for (j = 0; j < width; j++){
        graph[i][j] = gray_img[i * width + j];
      }
    printf ("3");
    Gauss_blur(width, height, graph, graph1);
   printf ("7");
    for (i = 0; i < height; i++)
          for (j = 0; j < width; j++){
            gray_img[i * width + j] = graph[i][j];
          }
  
  stbi_write_jpg("hamster_gray.jpg", width, height, 1, gray_img, 100);
  
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
 
}
