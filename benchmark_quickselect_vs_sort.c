#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quickselect(int arr[], size_t n, size_t k) {
    if (n == 1) return arr[0];
    int pivot = arr[rand() % n];
    int *lows = malloc(n * sizeof(int));
    int *highs = malloc(n * sizeof(int));
    int *pivots = malloc(n * sizeof(int));
    size_t low_c = 0, high_c = 0, pivot_c = 0;

    for (size_t i = 0; i < n; i++) {
        if (arr[i] < pivot) lows[low_c++] = arr[i];
        else if (arr[i] > pivot) highs[high_c++] = arr[i];
        else pivots[pivot_c++] = arr[i];
    }

    int result;
    if (k < low_c)
        result = quickselect(lows, low_c, k);
    else if (k < low_c + pivot_c)
        result = pivot;
    else
        result = quickselect(highs, high_c, k - low_c - pivot_c);

    free(lows);
    free(highs);
    free(pivots);
    return result;
}

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void benchmark(size_t n, FILE* jsonFile) {
    int *data = malloc(n * sizeof(int));
    if (!data) {
        fprintf(stderr, "{\"error\":\"Memory allocation failed for size %zu\"}\n", n);
        return;
    }
    for (size_t i = 0; i < n; ++i) data[i] = rand() % 1000000;
    
    double total_qs_time = 0;
    for (int i = 0; i < 100; ++i) {  // Use 100 for speed
        int *sample = malloc(n * sizeof(int));
        if (!sample) {
            fprintf(stderr, "{\"error\":\"Memory allocation failed during QuickSelect sample\"}\n");
            free(data);
            return;
        }
        for (size_t j = 0; j < n; ++j) sample[j] = data[j];
        size_t k = rand() % n;

        clock_t start = clock();
        quickselect(sample, n, k);
        clock_t end = clock();
        total_qs_time += (double)(end - start) / CLOCKS_PER_SEC;

        free(sample);
    }
    double qs_avg = total_qs_time / 100;

    int *sort_sample = malloc(n * sizeof(int));
    if (!sort_sample) {
        fprintf(stderr, "{\"error\":\"Memory allocation failed during sort\"}\n");
        free(data);
        return;
    }
    for (size_t i = 0; i < n; ++i) sort_sample[i] = data[i];
    clock_t start = clock();
    qsort(sort_sample, n, sizeof(int), cmpfunc);
    clock_t end = clock();
    double sort_time = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(jsonFile, "{\"n\":%zu, \"quickselect\":%.6f, \"quicksort\":%.6f}\n", n, qs_avg, sort_time);

    free(data);
    free(sort_sample);
}

int main() {
    srand(time(NULL));
    size_t ns[] = {1000000, 2000000, 4000000, 8000000, 16000000};  
    size_t len = sizeof(ns) / sizeof(ns[0]);
    FILE *jsonFile = fopen("result-1.json", "w");
    if (!jsonFile) {
        fprintf(stderr, "{\"error\":\"Failed to open result.json for writing\"}\n");
        return 1;
    }
    fprintf(jsonFile, "[\n");
    for (size_t i = 0; i < len; ++i) {
        benchmark(ns[i], jsonFile);
        if (i != len-1) fprintf(jsonFile, ",\n");
    }
    fprintf(jsonFile, "\n]\n");
    fclose(jsonFile);
    return 0;
}