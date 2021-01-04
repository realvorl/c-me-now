# Measure time in NANO-SECONDS

To showcase this, I used a piece of fantastic code from 
[Quake-III-Arena](https://github.com/id-Software/Quake-III-Arena/blob/dbe4ddb10315479fc00086f08e25d968b4b43c49/code/game/q_math.c#L552) Quick Inverse SQRT.

```c 
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;						// evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

#ifndef Q3_VM
#ifdef __linux__
	assert( !isnan(y) ); // bk010122 - FPE?
#endif
#endif
	return y;
}

``` 

## How to use this file

### Generate random input floats
If you run a Unix OS it's a one liner:  
```sh 
awk -v min=2 -v max=676 -v num=64 'BEGIN{srand(); for (i=1;i<=num;i++) print min+rand()*(max-min+1)}' > input-floats.txt
```

### Build & Run the executable 

Build:  
```sh 
g++ inverse-square.c -o inverse-square.o
``` 

Run:  
```sh 
cat input-floats.txt | xargs -I % sh -c './inverse-square.o %'
``` 

Output: 
```st
input:  591.538025
1/sqrt  -> 0.041116 in 679 nanoseconds. 
Q_rsqrt -> 0.041061 in 203 nanoseconds.

input:  350.782013
1/sqrt  -> 0.053393 in 310 nanoseconds. 
Q_rsqrt -> 0.053351 in 74 nanoseconds.

input:  107.823997
1/sqrt  -> 0.096304 in 334 nanoseconds. 
Q_rsqrt -> 0.096155 in 121 nanoseconds.

``
