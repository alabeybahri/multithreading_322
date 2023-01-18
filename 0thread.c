#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define UPPER_LIMIT 10000
#define LOWER_LIMIT 1000

int N;

struct function_info {
    int minimum;
    int maximum;
    int range;
    int mode;
    double median;
    int sum;
    double arithmetic_mean;
    double harmonic_mean;
    double standard_deviation;
    double quartile_range;
    int *numbers;
} functionInfo;


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
    functionInfo = *(struct function_info *) args;
    int minimum = functionInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (functionInfo.numbers[i] < minimum) {
            minimum = functionInfo.numbers[i];
        }
    }
    functionInfo.minimum = minimum;
}

void calculateMaximum(void *args) {
    functionInfo = *(struct function_info *) args;
    int maximum = functionInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (functionInfo.numbers[i] > maximum) {
            maximum = functionInfo.numbers[i];
        }
    }
    functionInfo.maximum = maximum;
}

void calculateRange(void *args) {
    functionInfo = *(struct function_info *) args;
    int maximum = functionInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (functionInfo.numbers[i] > maximum) {
            maximum = functionInfo.numbers[i];
        }
    }
    int minimum = functionInfo.numbers[0];
    for (int i = 1; i < N; i++) {
        if (functionInfo.numbers[i] < minimum) {
            minimum = functionInfo.numbers[i];
        }
    }
    int range = maximum - minimum;
    functionInfo.range = range;
}

void calculateMode(void *args) {
    functionInfo = *(struct function_info *) args;
    int mode = 0, max_count = 0;

    for (int i = 0; i < N; i++) {
        int count = 0;

        for (int j = 0; j < N; j++) {
            if (functionInfo.numbers[j] == functionInfo.numbers[i])
                count++;
        }

        if (count > max_count) {
            max_count = count;
            mode = functionInfo.numbers[i];
        }
    }
    functionInfo.mode = mode;
}

void calculateMedian(void *args) {
    functionInfo = *(struct function_info *) args;
    int numbersCopy[N];
    memcpy(numbersCopy, functionInfo.numbers, N * sizeof(int));
    double median;
    quicksort(numbersCopy, 0, N - 1);
    if (N % 2 == 0) {
        int first_val = numbersCopy[N / 2 - 1];
        int second_val = numbersCopy[N / 2];
        median = (double) (first_val + second_val) / 2;
    } else {
        median = numbersCopy[(N - 1) / 2];
    }
    functionInfo.median = median;
}

void calculateSum(void *args) {
    functionInfo = *(struct function_info *) args;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += functionInfo.numbers[i];
    }
    functionInfo.sum = sum;
}

void calculateArithmeticMean(void *args) {
    functionInfo = *(struct function_info *) args;
    int sum = 0;
    double arithmetic_mean;
    for (int i = 0; i < N; ++i) {
        sum += functionInfo.numbers[i];
    }
    arithmetic_mean = (double) sum / N;
    functionInfo.arithmetic_mean = arithmetic_mean;
}

void calculateHarmonicMean(void *args) {
    functionInfo = *(struct function_info *) args;
    double temp = 0;
    double temp2;
    double harmonic_mean;
    for (int i = 0; i < N; ++i) {
        temp = (double) temp + ((double) 1 / functionInfo.numbers[i]);
    }
    temp2 = pow(temp, -1);
    harmonic_mean = N * temp2;
    functionInfo.harmonic_mean = harmonic_mean;

}

void calculateStandardDeviation(void *args) {
    functionInfo = *(struct function_info *) args;
    double standard_deviation, arithmetic_mean, temp = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += functionInfo.numbers[i];
    }
    arithmetic_mean = (double) sum / N;

    for (int i = 0; i < N; i++) {
        temp += (double) pow(functionInfo.numbers[i] - arithmetic_mean, 2);
    }
    standard_deviation = (double) sqrt(temp / ((double) N - 1));
    functionInfo.standard_deviation = standard_deviation;
}

void calculateInterquartileRange(void *args) {
    functionInfo = *(struct function_info *) args;
    double first_quartile, quartile_range, third_quartile;
    int numbersCopy[N];
    memcpy(numbersCopy, functionInfo.numbers, N * sizeof(int));
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
    functionInfo.quartile_range = quartile_range;
}

int main(int argc, char *argv[]) {
    struct timespec start, stop;
    N = atoi(argv[1]);
    srand(time(NULL));
    int *numbers_list = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        numbers_list[i] = (rand() % (UPPER_LIMIT - LOWER_LIMIT + 1)) + LOWER_LIMIT;
    }
    functionInfo.numbers = numbers_list;

    double time_between;
    clock_gettime(CLOCK_REALTIME, &start);
    calculateMinimum(&functionInfo);
    calculateMaximum(&functionInfo);
    calculateRange(&functionInfo);
    calculateMode(&functionInfo);
    calculateMedian(&functionInfo);
    calculateSum(&functionInfo);
    calculateArithmeticMean(&functionInfo);
    calculateHarmonicMean(&functionInfo);
    calculateStandardDeviation(&functionInfo);
    calculateInterquartileRange(&functionInfo);
    clock_gettime(CLOCK_REALTIME, &stop);
    time_between = ((double) (stop.tv_nsec - start.tv_nsec) / pow(10, 9)) + (double) (stop.tv_sec - start.tv_sec);

    FILE *fp;
    fp = fopen("output1.txt", "w");
    fprintf(fp, "%d\n%d\n%d\n%d\n%f\n%d\n%f\n%f\n%f\n%f\n%lf", functionInfo.minimum, functionInfo.maximum,
            functionInfo.range,
            functionInfo.mode, functionInfo.median, functionInfo.sum, functionInfo.arithmetic_mean,
            functionInfo.harmonic_mean,
            functionInfo.standard_deviation, functionInfo.quartile_range, time_between);
    fclose(fp);
    return 0;
}
