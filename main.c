
#define STB_IMAGE_IMPLEMENTATION
#include <math.h>
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include<strings.h>
#include<stdio.h>
#include<stdlib.h>


void high_contrast (unsigned char** graph, int w, int h, int black, int white) {
    for (int i = 2; i < h - 1; i++) {
        for (int j = 2; j < w - 1; j++) {
            if (graph[i][j] <= black-1) graph[i][j] = 0;
            if (graph[i][j] >= white + 1) graph[i][j] = 255;
        }
    }
}

void svertka_Gauss (int w, int h, unsigned char **graph, unsigned char **graph1){
    int i, j;
    printf ("6\n");
    for (i = 1; i < h + 1; i++){
        for (j = 1; j < w + 1; j++){
            graph[i - 1][j - 1] = (unsigned char)((graph1[i - 1][j - 1] + graph1[i - 1][j + 1] + graph1[i + 1][j - 1] + graph1[i + 1][j + 1])* 0.0924 + (graph1[i - 1][j] + graph1[i][j - 1] + graph1[i][j + 1] + graph1[i + 1][j])* 0.1192 + graph1[i][j] * 0.1538);
        }
    }
   return;
}
    

void Gauss_blur(int w, int h, unsigned char **graph, unsigned char **graph1){
    int i, j;
    printf ("467\n");
    for (i = 1; i < h + 1; i++){
        for (j = 1; j < w + 1; j++){
            graph1[i][j] = graph[i - 1][j - 1];
        }    
    }
    printf ("4\n");
    for (i = 1; i < h + 1; i++){
        graph1[i][0] = graph[i - 1][0];
        graph1[i][w + 1] = graph[i - 1][w - 1];
    }
    for (j = 0; j < w + 2; j++){
        graph1[0][j] = graph1[1][j];
        graph1[h + 1][j] = graph1[h][j];
    }
    printf ("5\n");
    svertka_Gauss (w, h, graph, graph1);
    return;  
}

void dfs(int *colour, int i, int n, unsigned char** graph)
{
    printf ("777\n");
    int j, k = 0, h = 0, g;
    colour[i] = 1;
    for (j = 0; j < n; j++)
    {
        if ((graph[i][j] < 50) && (colour[j] == 0))
            dfs(colour, j, n, graph);
    }
       colour[i] = 2;

        return;
    }

int main(void) {
  printf("hello world!\n");
  int width, height, channels;
  unsigned char *img = stbi_load("hamster_gray.jpg", &width, &height, &channels, 0);
  if(img == NULL) {
      printf("Error in loading the image\n");
      exit(1);
  }
  printf("hello world!\n");
  int img_size = width * height * channels;
  int gray_img_size = width * height;
  unsigned char *gray_img = (unsigned char *)malloc(gray_img_size*sizeof(unsigned char));
  printf("hello world!\n");
  int k = 0, i, j;  
  printf ("%d %d\n", width, height); 
  printf ("%d %d\n", gray_img_size, img_size);
  for (i = 0; i < img_size - 2; i += 3) {
//    printf ("%d %d\n", i, k);
    gray_img[k++] = (img[i] * 11 + img[i + 1] * 16 + img[i + 2] * 5) / 32;
  //  gray_img[k++] = 255;
  }
    int black = 100;
    int white = 150;
    int *colour = (int*)calloc(height * width, sizeof(int));
    
    unsigned char **graph = (unsigned char **)malloc(height * sizeof(unsigned char*));
    for (i = 0; i < height; i++) graph[i] = (unsigned char*)malloc(width * sizeof (unsigned char));
    unsigned char **graph1 = (unsigned char **)malloc((height + 2) * sizeof(unsigned char*));
    for (i = 0; i < height + 2; i++) graph1[i] = (unsigned char*)malloc((width + 2) * sizeof (unsigned char));
    

    for (i = 0; i < height; i++)
      for (j = 0; j < width; j++){
        graph[i][j] = gray_img[i * width + j];
      }

   high_contrast (graph, width, height, black, white);
    
   Gauss_blur(width, height, graph, graph1);
    
    int n = height * width;
    int res[n][n];    
    int cnt = 0;
    int skip[n];
    printf ("888\n");
    for (i = 0; i < n; ++i) skip[i] = 0;
        for (i = 0; i < n; i++)
    {
        if (skip[i] == 1) {
            continue;
        }
          printf ("767\n");
        cnt++;
        dfs(colour, i, n, graph);
        for (int g = 0; g < n; g++)
        {
            if ((graph[i][g] != 0) || (graph[g][i] != 0)) {
                colour[g] = 2;
            }
                
            if ((g > i) && (colour[g] == 2)){
                skip[g] = 1;
            } 
            res[i][g] = colour[g];
            res[i][i] = 2;
            colour[g] = 0;
         }
        
    }
    
 printf("%d\n", cnt);
    for (i = 0; i < n; ++i) {
        if (skip[i] == 1) continue;
        
        int sum = 0;
        for (j = i; j < n; ++j) {
            if (j < n && res[i][j] == 2) sum++;
        }
        
        printf("%d\n", sum);
        
        for (j = i; j < n; ++j) {
            if (res[i][j] == 2) printf("%d ", j + 1);
        }
        
        printf("\n");
    } 
    
    
   printf ("7\n");
    for (i = 0; i < height; i++)
          for (j = 0; j < width; j++){
            gray_img[i * width + j] = graph[i][j];
          }
    
  stbi_write_jpg("hamster_gray1.jpg", width, height, 1, gray_img, 100);
  
  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
 
}
