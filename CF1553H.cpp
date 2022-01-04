#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}

/*
The goal:
for each number 1<=x<2^k, find the smallest absolute difference in array a taken xor with x

Analysis:
Consider all represented in binary. |(a $ x) - (b $ x)|
xor is also bit flipper

p <=> 2^k - 1 - p
these 2 are complementary
111111001000
000000110111
if f, g are complementary
then x$f and x$g are complementary (flipping the complementary sets of bits)
so x$f - x$g = x$g - x$f

is x$a unique for a unique x?
certainly,
$a is an invertible functional mapping, so it's one-to-one.

If we divide [0,2^k) to interval of size 2^t; then prove that all the mirror sum of the interval is either 2^t-1 or 2^k+2^t-1
x$a+y$a
y = 2^t-1-x
x,y are complementary wrt 2^t-1
x$a + y$a
if a < 2^t
then x$a is complementary to y$a
if 2^(t+1) > a >= 2^t
then its first digit must be 1, so
x$a is complementary to y$a is the smaller part.
So they are complementary part + 2^t + 2^t
= 2^(t+1) + 2^t - 1
if even larger
= 2^t - 1 + 2*larger_part

x - y = z
11 - x - (3 - y) = 14 - z
3 - y - (11 - x) = z - 8
z + 8
- 14 - z

differences across x can only be odd numbers < 2^k

It seems all caseworking requires us to know the size of a, so let us sort a in ascending order first.
We can do div and conquer on the size of a.








*/








