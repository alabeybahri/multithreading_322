#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define UPPER_LIMIT 10000
#define LOWER_LIMIT 1000

int N;
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
int *numbers;

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

void calculateMinimum() {
    int minimum = numbers[0];
    for (int i = 1; i < N; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
    }

    minimum_g = minimum;
}

void calculateMaximum() {
    int maximum = numbers[0];
    for (int i = 1; i < N; i++) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }
    maximum_g = maximum;
}

void calculateRange() {
    int maximum = numbers[0];
    for (int i = 1; i < N; i++) {
        if (numbers[i] > maximum) {
            maximum = numbers[i];
        }
    }
    int minimum = numbers[0];
    for (int i = 1; i < N; i++) {
        if (numbers[i] < minimum) {
            minimum = numbers[i];
        }
    }
    int range = maximum - minimum;
    range_g = range;
}

void calculateMode() {
    int max_value = 0, max_count = 0;

    for (int i = 0; i < N; i++) {
        int count = 0;

        for (int j = 0; j < N; j++) {
            if (numbers[j] == numbers[i])
                count++;
        }

        if (count > max_count) {
            max_count = count;
            max_value = numbers[i];
        }
    }
    mode_g = max_value;
}

void calculateMedian() {
    int numbersCopy[N];
    memcpy(numbersCopy, numbers,N*sizeof (int ));

    quicksort(numbersCopy,0,N-1);
    if (N % 2 == 0) {
        int first_val = numbersCopy[N / 2 - 1];
        int second_val = numbersCopy[N / 2];
        double median = (double) (first_val + second_val) / 2;
        median_g = median;
    } else {
        int median = numbersCopy[(N - 1) / 2];
        median_g = median;
    }

}

void calculateSum() {
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += numbers[i];
    }
    sum_g = sum;
}

void calculateArithmeticMean() {
    int sum = 0;
    double arithmetic_mean;
    for (int i = 0; i < N; ++i) {
        sum += numbers[i];
    }
    arithmetic_mean = (double) sum / N;
    arithmetic_mean_g = arithmetic_mean;
}

void calculateHarmonicMean() {
    double temp = 0;
    double temp2;
    double harmonic_mean;
    for (int i = 0; i < N; ++i) {
        temp = (double) temp + ((double) 1 / numbers[i]);
    }
    temp2 = pow(temp, -1);
    harmonic_mean = N * temp2;
    harmonic_mean_g = harmonic_mean;
}

void calculateStandardDeviation() {
    double standard_deviation, arithmetic_mean, temp = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += numbers[i];
    }
    arithmetic_mean = (double) sum / N;

    for (int i = 0; i < N; i++) {
        temp += (double) pow(numbers[i] - arithmetic_mean, 2);
    }
    standard_deviation = (double) sqrt(temp / ((double)N - 1));
    standard_deviation_g = standard_deviation;
}

void calculateInterquartileRange(){
    double first_quartile,quartile_range,third_quartile;
    int numbersCopy[N];
    memcpy(numbersCopy, numbers,N*sizeof (int ));
    quicksort(numbersCopy,0,N-1);
    if (N % 2 != 0) {
        int m = ((N + 1) / 2) - 1;
        if (m % 2 != 0) {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = numbersCopy[q1];
            int q3 = ((m + 1) / 2) + m;
            third_quartile = numbersCopy[q3];
            quartile_range = third_quartile - first_quartile;
            quartile_range_g = quartile_range;
        } else {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = ((double )numbersCopy[q1] + numbersCopy[q1 + 1]) / 2;
            int q3 = ((m + 1) / 2) + m;
            third_quartile = ((double )numbersCopy[q3] + numbersCopy[q3 + 1]) / 2;
            quartile_range = third_quartile - first_quartile;
            quartile_range_g = quartile_range;
        }
    } else {
        int m = ((N + 1) / 2) - 1;
        if (m % 2 == 0) {
            int q1 = (m + 1) / 2;
            first_quartile = numbersCopy[q1];
            int q3 = q1 + m + 1;
            third_quartile = numbersCopy[q3];
            quartile_range = third_quartile - first_quartile;
            quartile_range_g = quartile_range;

        } else {
            int q1 = ((m + 1) / 2) - 1;
            first_quartile = ((double )numbersCopy[q1] + numbersCopy[q1 + 1]) / 2;
            int q3 = q1 + m + 1;
            third_quartile = ((double )numbersCopy[q3] + numbersCopy[q3 + 1]) / 2;
            quartile_range = third_quartile - first_quartile;
            quartile_range_g = quartile_range;
        }
    }
}

void calculateMaxMin(){
    calculateMinimum();
    calculateMaximum();
}
void calculateRangeMode(){
    calculateRange();
    calculateMode();
}

void calculateMedianSum(){
    calculateMedian();
    calculateSum();
}

void calculateArithmeticHarmonic(){
    calculateArithmeticMean();
    calculateHarmonicMean();
}

void calculateStandardInterquartile(){
    calculateStandardDeviation();
    calculateInterquartileRange();
}

int main(int argc, char *argv[]) {
    struct timespec start, stop;
    clock_gettime(CLOCK_REALTIME, &start);


    N = atoi(argv[1]);
    srand(time(NULL));
    int *numbers_list = (int *) calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        numbers_list[i] = (rand() % (UPPER_LIMIT - LOWER_LIMIT + 1)) + LOWER_LIMIT;
    }
    numbers = numbers_list;

    pthread_t tid;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_t tid5;

    pthread_create(&tid, NULL, calculateMaxMin, NULL);
    pthread_create(&tid2, NULL, calculateRangeMode, NULL);
    pthread_create(&tid3, NULL, calculateMedianSum, NULL);
    pthread_create(&tid4, NULL, calculateArithmeticHarmonic, NULL);
    pthread_create(&tid5, NULL, calculateStandardInterquartile, NULL);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);



    double time_between;
    clock_gettime(CLOCK_REALTIME, &stop);
    time_between = ((float ) (stop.tv_nsec - start.tv_nsec) / pow(10, 9)) +
                   (float ) (stop.tv_sec - start.tv_sec);
    FILE *fp;
    fp = fopen("output2.txt", "w");
    fprintf(fp, "%d\n%d\n%d\n%d\n%f\n%d\n%f\n%f\n%f\n%f\n%lf", minimum_g, maximum_g, range_g,
            mode_g, median_g, sum_g, arithmetic_mean_g, harmonic_mean_g,
            standard_deviation_g, quartile_range_g, time_between);
    fclose(fp);
    return 0;
}
