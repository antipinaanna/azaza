
#define STB_IMAGE_IMPLEMENTATION
#include <math.h>
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

void high_contrast(unsigned char *img, int img_size, int black, int white, unsigned char *img_high_contrast)
{
    for (int i = 0; i < img_size; ++i)
    {
        if (img[i] > white)
        {
            img_high_contrast[i] = 255;
        }
        else if (img[i] < black)
        {
            img_high_contrast[i] = 0;
        }
        else
        {
            img_high_contrast[i] = img[i];
        }
    }
}

void svertka_Gauss(int w, int h, unsigned char **graph, unsigned char **graph1)
{
    int i, j;
    //    printf ("6\n");
    for (i = 1; i < h + 1; i++)
    {
        for (j = 1; j < w + 1; j++)
        {
            graph[i - 1][j - 1] = (unsigned char)((graph1[i - 1][j - 1] + graph1[i - 1][j + 1] + graph1[i + 1][j - 1] + graph1[i + 1][j + 1]) * 0.0924 + (graph1[i - 1][j] + graph1[i][j - 1] + graph1[i][j + 1] + graph1[i + 1][j]) * 0.1192 + graph1[i][j] * 0.1538);
        }
    }
    return;
}

void Gauss_blur(int w, int h, unsigned char **graph, unsigned char **graph1)
{
    int i, j;
    //    printf ("467\n");
    for (i = 1; i < h + 1; i++)
    {
        for (j = 1; j < w + 1; j++)
        {
            graph1[i][j] = graph[i - 1][j - 1];
        }
    }
    //    printf ("4\n");
    for (i = 1; i < h + 1; i++)
    {
        graph1[i][0] = graph[i - 1][0];
        graph1[i][w + 1] = graph[i - 1][w - 1];
    }
    for (j = 0; j < w + 2; j++)
    {
        graph1[0][j] = graph1[1][j];
        graph1[h + 1][j] = graph1[h][j];
    }
    //    printf ("5\n");
    svertka_Gauss(w, h, graph, graph1);
    return;
}

void dfs1(int i, int j, int w, int h, unsigned char **data, int **v, int m, int depth)
{
    if (depth > 100000)
        return;
    if (i > 0 && i < h && j > 0 && j < w && v[i][j] != 0)
    {
        return;
    }
    if (i > 0 && i < h && j > 0 && j < w)
    {
        v[i][j] = m;
    }
    else
    {
        return;
    }
    int r = 10;

    if ((i + 1 >= 1) && (i + 1 <= h - 1) && (j >= 1) && (j <= w - 1))
    {
        if ((abs(data[i][j] - data[i + 1][j]) <= r) && (v[i + 1][j] == 0))
        {
            dfs1(i + 1, j, w, h, data, v, m, depth + 1);
        }
    }

    if ((i - 1 >= 1) && (i - 1 <= h - 1) && (j >= 1) && (j <= w - 1))
    {
        if ((abs(data[i][j] - data[i - 1][j]) <= r) && (v[i - 1][j] == 0))
        {
            dfs1(i - 1, j, w, h, data, v, m, depth + 1);
        }
    }
    if ((i >= 1) && (i <= h - 1) && (j + 1 >= 1) && (j + 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i][j + 1]) <= r) && (v[i][j + 1] == 0))
        {
            dfs1(i, j + 1, w, h, data, v, m, depth + 1);
        }
    }
    if ((i >= 1) && (i <= h - 1) && (j - 1 >= 1) && (j - 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i][j - 1]) <= r) && (v[i][j - 1] == 0))
        {
            dfs1(i, j - 1, w, h, data, v, m, depth + 1);
        }
    }

    //-----------------------

    if ((i + 1 >= 1) && (i + 1 <= h - 1) && (j - 1 >= 1) && (j - 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i + 1][j - 1]) <= r) && (v[i + 1][j - 1] == 0))
        {
            dfs1(i + 1, j - 1, w, h, data, v, m, depth + 1);
        }
    }
    if ((i - 1 >= 1) && (i - 1 <= h - 1) && (j - 1 >= 1) && (j - 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i - 1][j - 1]) <= r) && (v[i - 1][j - 1] == 0))
        {
            dfs1(i - 1, j - 1, w, h, data, v, m, depth + 1);
        }
    }
    if ((i - 1 >= 1) && (i - 1 <= h - 1) && (j + 1 >= 1) && (j + 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i - 1][j + 1]) <= r) && (v[i - 1][j + 1] == 0))
        {
            dfs1(i - 1, j + 1, w, h, data, v, m, depth + 1);
        }
    }
    if ((i + 1 >= 1) && (i + 1 <= h - 1) && (j + 1 >= 1) && (j + 1 <= w - 1))
    {
        if ((abs(data[i][j] - data[i + 1][j + 1]) <= r) && (v[i + 1][j + 1] == 0))
        {
            dfs1(i + 1, j + 1, w, h, data, v, m, depth + 1);
        }
    }
}


int main(void)
{
    printf("hello world!\n");
    int width, height, channels, m = 0;
    unsigned char *img = stbi_load("hamster_gray.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("hello world!\n");
    int img_size = width * height * channels;
    int gray_img_size = width * height;
    unsigned char *gray_img = (unsigned char *)malloc(gray_img_size * sizeof(unsigned char));
    printf("hello world!\n");
    int k = 0, i, j;
    printf("%d %d\n", width, height);
    printf("%d %d\n", gray_img_size, img_size);
    for (i = 0; i < img_size - 2; i += 3)
    {
        gray_img[k++] = (img[i] * 11 + img[i + 1] * 16 + img[i + 2] * 5) / 32;
    }

    unsigned char *img_high_contrast = (unsigned char *)malloc(gray_img_size * sizeof(unsigned char));

    int black = 100;
    int white = 150;

    high_contrast(gray_img, gray_img_size, black, white, img_high_contrast);

    stbi_write_jpg("hamster_high_contrast.jpg", width, height, 1, img_high_contrast, 100);

    unsigned char **graph = (unsigned char **)malloc((height + 2) * sizeof(unsigned char *));

    for (i = 0; i < height + 2; i++)
        graph[i] = (unsigned char *)malloc((width + 2) * sizeof(unsigned char));

    for (i = 0; i < height - 1; i++)
        for (j = 0; j < width - 1; j++)
        {
            graph[i][j] = img_high_contrast[i * width + j];
        }

    unsigned char **graph1 = (unsigned char **)malloc((height + 2) * sizeof(unsigned char *));

    for (i = 0; i < height + 2; i++)
        graph1[i] = (unsigned char *)malloc((width + 2) * sizeof(unsigned char));

    Gauss_blur(width, height, graph, graph1);

    printf("WOW\n");
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            gray_img[i * width + j] = graph[i][j];
        }

    stbi_write_jpg("hamster_gauss_blur.jpg", width, height, 1, gray_img, 100);

    int **colour = (int **)malloc((height + 2) * sizeof(int *));
    for (i = 0; i < height; i++)
        colour[i] = (int *)calloc((width + 2), sizeof(int));

    int r = 0;
    for (i = 1; i < height; i++)
    {
        for (j = 1; j < width; j++)
        {
            if (colour[i][j] == 0)
            {
                m += 1;
                printf("%d %d\n", m, m);
                // dfs2(i, j, width, height, graph, colour, m, r);
                dfs1(i, j, width, height, graph, colour, m, 1);
            }
        }
    }

    printf("WOW!!!!!!!!\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            graph[i][j] = colour[i][j];
        }
    }
    //Gauss_blur(width, height, graph, graph1);

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            gray_img[i * width + j] = graph[i][j];
        }
    /*
    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
        {
            gray_img[i * width + j] = (colour[i][j]) % 256;
        }
    */

    stbi_write_jpg("hamster_comps.jpg", width, height, 1, gray_img, 100);

    k = 0;
    int c = 0;
    for (i = 0; i < height * width * 3; i += 3)
    {
        c = gray_img[k] % 74 + gray_img[k] % 13;
        img[i] = 3 * c - 35;
        img[i + 1] = 4 * c + 60;
        img[i + 2] = 5 * c + 13;
        img[i + 3] = 255;
        k++;
    }

    stbi_write_jpg("hamster_comps_3.jpg", width, height, 3, img, 100);


    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
}
