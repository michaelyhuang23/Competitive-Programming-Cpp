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
    iint tt; cin >> tt;
    vector<iint> prefix(3*1000000);
    prefix[0] = 0;
    for(iint i=1; i<3*1000000; i++)
    	prefix[i] = prefix[i-1] ^ i;
    while(tt--){
    	iint a, b;
    	cin >> a >> b;
    	iint len = a;
    	iint u = prefix[a-1];
    	if(u==b){ cout<<len<<endl; continue; }
    	iint x = u^b;
    	if(x==a) len+=2;
    	else len+=1;
    	cout<<len<<endl;
    }
}


/*

MEX dictates arr must have at least a terms
0,1,2,...,a-1

XOR 

u $ x = b
x = b $ u

if x <= a
we need to decompose x into 2 numbers

y $ z = x
(y, z) can be very big!

*/