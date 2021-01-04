#include <stdio.h>
#include <math.h>
#include <time.h>

// credit for the following code:
// https://github.com/id-Software/Quake-III-Arena/blob/dbe4ddb10315479fc00086f08e25d968b4b43c49/code/game/q_math.c#L552
float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;                            // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);                  // what the f**k?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));        // 1st iteration
//	y = y * (threehalfs - (x2 * y * y));        // 2nd iteration, this can be removed

    return y;
}
//https://github.com/id-Software/Quake-III-Arena/blob/dbe4ddb10315479fc00086f08e25d968b4b43c49/code/game/q_math.c#L572

timespec ts;

int main(int argc, char const *argv[])
{
    float inFloat = 3.14159;
    if (argv[1])
    {
        inFloat = atof(argv[1]);
        printf("input:\t%2.6f\n", inFloat);
    }
    timespec_get(&ts, TIME_UTC);
    long t = ts.tv_nsec;
    float propQ = 1 / sqrt(inFloat);
    timespec_get(&ts, TIME_UTC);
    printf("1/sqrt\t-> %2.6f in %li nanoseconds. \n", propQ, (ts.tv_nsec - t));
    timespec_get(&ts, TIME_UTC);
    t = ts.tv_nsec;
    float ansQ = Q_rsqrt(inFloat);
    timespec_get(&ts, TIME_UTC);
    printf("Q_rsqrt\t-> %2.6f in %li nanoseconds.\n\n", ansQ, (ts.tv_nsec - t));
    return 0;
}
