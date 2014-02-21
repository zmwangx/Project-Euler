#ifndef READ_RAD_H
#define READ_RAD_H

#define N 120000

long _rad[N+1] = {0};

void read_rad(void) {
    FILE *input = fopen("rad", "r");
    for (int i = 1; i <= N; i++) {
        fscanf(input, "%ld\n", &_rad[i]);
    }
    return;
}

#endif
