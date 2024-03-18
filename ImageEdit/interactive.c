#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "imageprocessing.h"
#define SIZE 50
struct photo {
    int N;
    int M;
    int ***matrix;
};
struct filter {
    int N;
    float **grid;
};
int main() {
    int number = 0;
    char option[SIZE];
    int numberfilter = 0;
    struct photo pictures[SIZE];
    struct filter filt[SIZE];
    for (;;) {
        scanf("%s", option);
        if (option[0] == 'e')
            break;
        if (option[0] == 'l') {
            int N = 0, M = 0;
            char name[SIZE];
            scanf("%d %d %s", &N, &M, name);
            pictures[number].N = N;
            pictures[number].M = M;
            pictures[number].matrix = (int ***) malloc(N * sizeof(int **));
            for (int i = 0; i < N; i++) {
                pictures[number].matrix[i] = (int **) malloc(M * sizeof(int *));
                for (int j = 0; j < M; j++) {
                    pictures[number].matrix[i][j] = (int *) malloc(3 * sizeof(int));
                }
            }
            read_from_bmp(pictures[number].matrix, pictures[number].N, pictures[number].M, name);
            number++;
        }
        if (option[0] == 's') {
            int index = 0;
            char nameout[SIZE];
            scanf("%d %s", &index, nameout);
            write_to_bmp(pictures[index].matrix, pictures[index].N, pictures[index].M, nameout);
        }
        if (option[0] == 'a' && option[1] == 'h') {
            int index1 = 0;
            scanf("%d", &index1);
            pictures[index1].matrix = flip_horizontal(pictures[index1].matrix, pictures[index1].N, pictures[index1].M);
        }
        if (option[0] == 'a' && option[1] == 'r') {
            int index2 = 0;
            scanf("%d", &index2);
            pictures[index2].matrix = rotate_left(pictures[index2].matrix, pictures[index2].N, pictures[index2].M);
            int aux = 0;
            aux = pictures[index2].N;
            pictures[index2].N = pictures[index2].M;
            pictures[index2].M = aux;
        }
        if (option[0] == 'a' && option[1] == 'c') {
            int x = 0, y = 0, w = 0, h = 0, index3 = 0;
            scanf("%d %d %d %d %d", &index3, &x, &y, &w, &h);
            pictures[index3].matrix = crop(pictures[index3].matrix, pictures[index3].N, pictures[index3].M, x, y, h, w);
            pictures[index3].N = h;
            pictures[index3].M = w;
        }
        if (option[0] == 'a' && option[1] == 'e') {
            int rows = 0, cols = 0, r = 0, g = 0, b = 0, index4 = 0;
            scanf("%d %d %d %d %d %d", &index4, &rows, &cols, &r, &g, &b);
            pictures[index4].matrix = extend(pictures[index4].matrix, pictures[index4].N,
            pictures[index4].M, rows, cols, r, g, b);
            pictures[index4].N = 2 * rows + pictures[index4].N;
            pictures[index4].M = 2 * cols + pictures[index4].M;
        }
        if (option[0] == 'a' && option[1] == 'p') {
            int index_dst = 0, index_src = 0, x = 0, y = 0;
            scanf("%d %d %d %d", &index_dst, &index_src, &x, &y);
            pictures[index_dst].matrix = paste(pictures[index_dst].matrix, pictures[index_dst].N,
             pictures[index_dst].M, pictures[index_src].matrix, pictures[index_src].N, pictures[index_src].M, x, y);
        }
        if (option[0] == 'c' && option[1] == 'f') {
            int n = 0;
            scanf("%d", &n);
            filt[numberfilter].N = n;
            filt[numberfilter].grid = (float **) malloc(n * sizeof(float *));
            for (int i = 0; i < n; i++)
                filt[numberfilter].grid[i] = (float *) malloc(n * sizeof(float));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    scanf("%f", &filt[numberfilter].grid[i][j]);
                }
            numberfilter++;
        }
        if (option[0] == 'a' && option[1] == 'f') {
            int indeximg = 0, indexfilter = 0;
            scanf("%d %d", &indeximg, &indexfilter);
            pictures[indeximg].matrix = apply_filter(pictures[indeximg].matrix, pictures[indeximg].N,
            pictures[indeximg].M, filt[indexfilter].grid, filt[indexfilter].N);
        }
        if (option[0] == 'd' && option[1] == 'i') {
            int index5 = 0;
            scanf("%d", &index5);
            for (int i = 0; i < pictures[index5].N; i++) {
                for (int j = 0; j < pictures[index5].M; j++) {
                    free(pictures[index5].matrix[i][j]);
                }
                free(pictures[index5].matrix[i]);
            }
            free(pictures[index5].matrix);
            for (int i = index5; i < number; i++)
                pictures[i] = pictures[i + 1];
            number--;
        }
        if (option[0] == 'd' && option[1] == 'f') {
            int index6 = 0;
            scanf("%d", &index6);
            for (int i = 0; i < filt[index6].N; i++)
                free(filt[index6].grid[i]);
            free(filt[index6].grid);
            for (int i = index6; i < numberfilter; i++)
                filt[i] = filt[i + 1];

            numberfilter--;
        }
    }
    for (int j = 0; j < number; j++) {
        int index5 = 0;
        index5 = j;
        for (int i = 0; i < pictures[index5].N; i++) {
            for (int j = 0; j < pictures[index5].M; j++) {
                free(pictures[index5].matrix[i][j]);
            }
            free(pictures[index5].matrix[i]);
        }
        free(pictures[index5].matrix);
    }
    for (int j = 0; j < numberfilter; j++) {
        int index6 = 0;
        index6 = j;
        for (int i = 0; i < filt[index6].N; i++)
            free(filt[index6].grid[i]);
        free(filt[index6].grid);
    }

    return 0;
}
