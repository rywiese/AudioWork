#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

//struct that represents a digital audio sample
struct sample {

    //holds the audio data
    int* buffer;

    //length of the buffer
    int length;

    //index of the buffer currently being read
    int read;
};

//creates a sample struct with one cycle given the amplitude, frequency,
//and sample rate and returns a pointer to that struct
struct sample* createSample(int amplitude, double frequency, double sampleRate) {

    //calculate the period and the time between each sample
    double period = 1/frequency;
    double sampleTime = 1/sampleRate;

    //calculate the number of cycles required to eliminate any phase shift
    int numCycles = 1;
    while (floor((((double) numCycles) * period) / sampleTime) != ceil((((double) numCycles) * period) / sampleTime)) {
        numCycles ++;
        printf("%f, \n", (((double) numCycles) * period) / sampleTime);
    }

    //initialize struct
    struct sample* s = (struct sample*) malloc(sizeof(struct sample));
    s->length = (int) ((((double) numCycles) * period) / sampleTime);
    s->buffer = (int*) malloc(s->length * sizeof(int));

    //calculate the values for each index in the buffer
    double x = 0;
    for(int i=0; i<s->length; i++) {
        s->read = i;
        s->buffer[i] = amplitude * sin(2*PI*frequency*x);
        x += sampleTime;
    }
    s->read = 0;

    return s;
}

//deletes a malloc'ed sample struct
void deleteSample(struct sample* s) {
    free(s->buffer);
    free(s);
}

//copies the first n values from a sample struct into a
//newly malloc'ed sample struct
struct sample* getSamples(struct sample* source, int n) {

    //make sure n is not too big
    if(n > source->length) {
        printf("Too many samples requested");
        return NULL;
    }

    //initialize destination sample struct
    struct sample* dest = (struct sample*) malloc(sizeof(struct sample));
    dest->length = n;
    dest->buffer = (int*) malloc(n * sizeof(int));

    //copy first n values
    for(int i=0; i<n; i++) {
        dest->buffer[i] = source->buffer[i];
    }
    dest->read = 0;

    return dest;
}

//prints every value in a sample struct
void printSample(struct sample* s) {
    for(int i=0; i<s->length-1; i++)
        printf("%d,", s->buffer[i]);
    printf("%d\n", s->buffer[s->length - 1]);
}

//returns the least common multiple of two numbers
int lcm(int a, int b) {
    int max = (a >= b) ? a : b;
    int min = (a >= b) ? b : a;
    int lcm = max;
    while(lcm % min != 0)
        lcm += max;
    return lcm;
}

int main(int argc, char* argv[]) {
    struct sample* s;
    float Fs = 16000.0;

    for (int n=0; n < 16; n++) {
      float Freq = 1000 + n*(Fs/2.0)/16.0;
      printf("\n");
      s = createSample(16384.0, Freq, Fs);
      printf("Frequency: %6.1f\n", Freq);
      printSample(s);
      deleteSample(s);
    }
    struct sample* s2 = createSample(100, 200, 10000);
    printSample(s2);
    deleteSample(s2);

    //test lcm
    //printf("lcm(3,5) = %d\n", lcm(3,5));

    return 0;
}
