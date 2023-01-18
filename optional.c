#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define UPPER_LIMIT 10000
#define LOWER_LIMIT 1000

int N;
int number_of_threads;

int minimum_g;
int maximum_g;
int range_g;
int mode_g;
double median_g;
int sum_g;
double arithmetic_mean_g;
double harmonic_mean_g;
double standard_deviation_g;
double quartile_range_g;

struct thread_info {
    bool functions[10];
    int *numbers;
};


void quicksort(int *target, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    int tmp, pivot = target[i];
    for (;;) {
        while (target[i] < pivot) i++;
        while (pivot < target[j]) j--;
        if (i >= j) break;
        tmp = target[i];
        target[i] = target[j];
        target[j] = tmp;
        i++;
        j--;
    }
    quicksort(target, left, i - 1);
    quicksort(target, j + 1, right);
}

void calculateMinimum(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int minimum = threadInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (threadInfo.numbers[i] < minimum) {
            minimum = threadInfo.numbers[i];
        }
    }
    minimum_g = minimum;
}

void calculateMaximum(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int maximum = threadInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (threadInfo.numbers[i] > maximum) {
            maximum = threadInfo.numbers[i];
        }
    }
    maximum_g = maximum;
}

void calculateRange(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int maximum = threadInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (threadInfo.numbers[i] > maximum) {
            maximum = threadInfo.numbers[i];
        }
    }
    int minimum = threadInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (threadInfo.numbers[i] < minimum) {
            minimum = threadInfo.numbers[i];
        }
    }
    int range = maximum - minimum;
    range_g = range;
}

void calculateMode(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int mode = 0, max_count = 0;

    for (int i = 0; i < N; i++) {
        int count = 0;

        for (int j = 0; j < N; j++) {
            if (threadInfo.numbers[j] == threadInfo.numbers[i])
                count++;
        }

        if (count > max_count) {
            max_count = count;
            mode = threadInfo.numbers[i];
        }
    }
    mode_g = mode;
}

void calculateMedian(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int numbersCopy[N];
    memcpy(numbersCopy, threadInfo.numbers, N * sizeof(int));
    double median;
    quicksort(numbersCopy, 0, N - 1);
    if (N % 2 == 0) {
        int first_val = numbersCopy[N / 2 - 1];
        int second_val = numbersCopy[N / 2];
        median = (double) (first_val + second_val) / 2;
    } else {
        median = numbersCopy[(N - 1) / 2];
    }
    median_g = median;
}

void calculateSum(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += threadInfo.numbers[i];
    }
    sum_g = sum;
}

void calculateArithmeticMean(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    int sum = 0;
    double arithmetic_mean;
    for (int i = 0; i < N; ++i) {
        sum += threadInfo.numbers[i];
    }
    arithmetic_mean = (double) sum / N;
    arithmetic_mean_g = arithmetic_mean;
}

void calculateHarmonicMean(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    double temp = 0;
    double temp2;
    double harmonic_mean;
    for (int i = 0; i < N; ++i) {
        temp = (double) temp + ((double) 1 / threadInfo.numbers[i]);
    }
    temp2 = pow(temp, -1);
    harmonic_mean = N * temp2;
    harmonic_mean_g = harmonic_mean;

}

void calculateStandardDeviation(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    double standard_deviation, arithmetic_mean, temp = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += threadInfo.numbers[i];
    }
    arithmetic_mean = (double) sum / N;

    for (int i = 0; i < N; i++) {
        temp += (double) pow(threadInfo.numbers[i] - arithmetic_mean, 2);
    }
    standard_deviation = (double) sqrt(temp / ((double) N - 1));
    standard_deviation_g = standard_deviation;
}

void calculateInterquartileRange(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    double first_quartile, quartile_range, third_quartile;
    int numbersCopy[N];
    memcpy(numbersCopy, threadInfo.numbers, N * sizeof(int));
    quicksort(numbersCopy, 0, N - 1);
    if (N % 2 != 0) {
        int m = ((N + 1) / 2) - 1;
        if (m % 2 != 0) {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = numbersCopy[q1];
            int q3 = ((m + 1) / 2) + m;
            third_quartile = numbersCopy[q3];
            quartile_range = third_quartile - first_quartile;
        } else {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = ((double) numbersCopy[q1] + numbersCopy[q1 + 1]) / 2;
            int q3 = ((m + 1) / 2) + m;
            third_quartile = ((double) numbersCopy[q3] + numbersCopy[q3 + 1]) / 2;
            quartile_range = third_quartile - first_quartile;
        }
    } else {
        int m = ((N + 1) / 2) - 1;
        if (m % 2 == 0) {
            int q1 = (m + 1) / 2;
            first_quartile = numbersCopy[q1];
            int q3 = q1 + m + 1;
            third_quartile = numbersCopy[q3];
            quartile_range = third_quartile - first_quartile;
        } else {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = ((double) numbersCopy[q1] + numbersCopy[q1 + 1]) / 2;
            int q3 = q1 + m + 1;
            third_quartile = ((double) numbersCopy[q3] + numbersCopy[q3 + 1]) / 2;
            quartile_range = third_quartile - first_quartile;
        }
    }
    quartile_range_g = quartile_range;
}

void calculate(void *args) {
    struct thread_info threadInfo;
    threadInfo = *(struct thread_info *) args;
    if (threadInfo.functions[0]) {
        calculateMinimum(args);
    }
    if (threadInfo.functions[1]) {
        calculateMaximum(args);
    }
    if (threadInfo.functions[2]) {
        calculateRange(args);
    }
    if (threadInfo.functions[3]) {
        calculateMode(args);
    }
    if (threadInfo.functions[4]) {
        calculateMedian(args);
    }
    if (threadInfo.functions[5]) {
        calculateSum(args);
    }
    if (threadInfo.functions[6]) {
        calculateArithmeticMean(args);
    }
    if (threadInfo.functions[7]) {
        calculateHarmonicMean(args);
    }
    if (threadInfo.functions[8]) {
        calculateStandardDeviation(args);
    }
    if (threadInfo.functions[9]) {
        calculateInterquartileRange(args);
    }

}

int main(int argc, char *argv[]) {
    struct timespec start, stop;
    struct thread_info threadInfoMain;

    N = atoi(argv[1]);
    number_of_threads = atoi(argv[2]);
    srand(time(NULL));
    int *numbers_list = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        numbers_list[i] = (rand() % (UPPER_LIMIT - LOWER_LIMIT + 1)) + LOWER_LIMIT;
    }
    clock_gettime(CLOCK_REALTIME, &start);

    threadInfoMain.numbers = numbers_list;
    pthread_t thread_ids[number_of_threads];

    struct thread_info threadInformations[number_of_threads];

    int number_to_divide = ceil((double) 10 / number_of_threads);
    int counter = 0;
    for (int j = 0; j < 10; ++j) {
        threadInfoMain.functions[j] = false;
    }
    for (int i = 1; i <= 10; ++i) {
        threadInfoMain.functions[i-1] = true;
        if (i % number_to_divide == 0 || i == 10) {
            threadInformations[counter].numbers = threadInfoMain.numbers;
            for (int j = 0; j < 10; ++j) {
                threadInformations[counter].functions[j] = threadInfoMain.functions[j];
            }
            pthread_create(&thread_ids[counter], NULL, calculate, &threadInformations[counter]);
            counter++;
            for (int j = 0; j < 10; ++j) {
                threadInfoMain.functions[j] = false;
            }
        }
    }
    for (int i = 0; i < number_of_threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    double time_between;
    clock_gettime(CLOCK_REALTIME, &stop);
    time_between = ((float ) (stop.tv_nsec - start.tv_nsec) / pow(10, 9)) +
                   (float ) (stop.tv_sec - start.tv_sec);
    FILE *fp;
    fp = fopen("output4.txt", "w");
    fprintf(fp, "%d\n%d\n%d\n%d\n%f\n%d\n%f\n%f\n%f\n%f\n%lf", minimum_g, maximum_g, range_g,
            mode_g, median_g, sum_g, arithmetic_mean_g, harmonic_mean_g,
            standard_deviation_g, quartile_range_g, time_between);
    fclose(fp);
    return 0;
}

