#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

int ***flip_horizontal(int ***image, int N, int M) {
    int aux = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M / 2; j++) {
            aux = image[i][j][0];
            image[i][j][0] = image[i][M - j - 1][0];
            image[i][M - j - 1][0] = aux;
            aux = image[i][j][1];
            image[i][j][1] = image[i][M - j - 1][1];
            image[i][M - j - 1][1] = aux;
            aux = image[i][j][2];
            image[i][j][2] = image[i][M - j - 1][2];
            image[i][M - j - 1][2] = aux;
        }
    return image;
}


int ***rotate_left(int ***image, int N, int M) {
    int ***m = (int ***) malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        m[i] = (int **) malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            m[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }
    for (int j = M - 1; j >= 0; j--)
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < 3; k++) {
                m[M - j - 1][i][k] = image[i][j][k];
            }
        }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);

    return m;
}


int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***newimage = (int ***) malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        newimage[i] = (int **) malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            newimage[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }
    int col = 0;
    int line = 0;

    for (int i = y; i < y + h; i++) {
        col = 0;
        for (int j = x; j < x + w; j++) {
            for (int k = 0; k < 3; k++)
                newimage[line][col][k] = image[i][j][k];
            col++;
        }
        line++;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);

    return newimage;
}


int ***extend(int ***image, int N, int M, int rows, int cols, int new_R,
              int new_G, int new_B) {
    int newrows = 0;
    int newcols = 0;
    newrows = rows * 2 + N;
    newcols = cols * 2 + M;

    int ***newimage = (int ***) malloc(newrows * sizeof(int **));
    for (int i = 0; i < newrows; i++) {
        newimage[i] = (int **) malloc(newcols * sizeof(int *));
        for (int j = 0; j < newcols; j++) {
            newimage[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }
    for (int i = 0; i < newrows; i++)
        for (int j = 0; j < newcols; j++) {
            newimage[i][j][0] = new_R;
            newimage[i][j][1] = new_G;
            newimage[i][j][2] = new_B;
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 3; k++)
                newimage[rows + i][cols + j][k] = image[i][j][k];
        }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return newimage;
}


int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src,
             int N_src, int M_src, int x, int y) {
    int col = 0;
    int row = 0;
    for (int i = y; i < N_dst; i++) {
        for (int j = x; j < M_dst; j++) {
            for (int k = 0; k < 3; k++)
                image_dst[i][j][k] = image_src[row][col][k];
            col++;
            if (col == M_src) {
                col = 0;
                break;
            }
        }
        row++;
        col = 0;
        if (row == N_src)
            break;
    }

    return image_dst;
}


int ***apply_filter(int ***image, int N, int M, float **filter,
                    int filter_size) {
    int ***newimage = (int ***) malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        newimage[i] = (int **) malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            newimage[i][j] = (int *) malloc(3 * sizeof(int));
        }
    }
    int newi = 0;
    int newj = 0;
    const int limitup = 255;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            newi = i - filter_size / 2;
            newj = j - filter_size / 2;
            float sumR = 0, sumG = 0, sumB = 0;
            for (int x = newi; x < newi + filter_size; x++) {
                if (x >= 0 && x < N) {
                  for (int y = newj; y < newj + filter_size; y++) {
                        if (y >= 0 && y < M && x >= 0 && x < N) {
                            sumR = sumR + filter[x - newi][y - newj] * (float) image[x][y][0];
                            sumG = sumG + filter[x - newi][y - newj] * (float) image[x][y][1];
                            sumB = sumB + filter[x - newi][y - newj] * (float) image[x][y][2];
                        }
                    }
                }
            }
            if ((int) sumR >= limitup)
                sumR = (float) limitup;
            if ((int) sumR < 0)
                sumR = 0;
            if ((int) sumG >= limitup)
                sumG = (float) limitup;
            if ((int) sumG < 0)
                sumG = 0;
            if ((int) sumB >= limitup)
                sumB = (float) limitup;
            if ((int) sumB < 0)
                sumB = 0;
            newimage[i][j][0] = (int) sumR;
            newimage[i][j][1] = (int) sumG;
            newimage[i][j][2] = (int) sumB;
        }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]);
        }
        free(image[i]);
    }
    free(image);
    return newimage;
}
