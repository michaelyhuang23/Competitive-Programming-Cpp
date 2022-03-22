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

vector<vector<iint> > bits(1000000, vector<iint>(1000000));

inline iint low_bit(iint num){
    return num & (-num);
}
inline llong query(iint xp, iint yp){ // idx starts at 1
    llong sum = 0;
    for(iint x = xp; x>0; x -= low_bit(x))
        for(iint y = yp; y>0; y -= low_bit(y))
            sum += bits[x][y];
    return sum;
}
inline void update(iint xp, iint yp, iint val){
    for(iint x = xp; x<=bits.size()-1; x+= low_bit(x))
        for(iint y = yp; y<=bits[0].size()-1; y+=low_bit(y))
            bits[x][y] += val;
}




