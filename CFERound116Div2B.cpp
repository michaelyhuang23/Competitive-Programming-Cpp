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
#include <unordered_map>
#include <unordered_set>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint tt; cin >> tt;
    while(tt--){
        llong n,k;
        cin >> n >> k;
        llong left = 0; llong right = 63;
        llong tc = 0;
        while(left<=right){
            llong mid = (left+right)/2;
            if((1LL<<mid)>k){ tc = mid; right = mid-1; }
            else left = mid+1;
        }
        if((1LL<<tc) >= n){
            llong lt = 0, rt = 63;
            llong tf = 0;
            while(lt<=rt){
                llong mid = (lt+rt)/2;
                if((1LL<<mid)>=n){ tf = mid; rt = mid-1; }
                else lt = mid+1;
            }
            assert((1LL<<tf)>=n);
            assert(tf==0 || (1LL<<(tf-1))<n);
            cout<<tf<<endl;
            continue;
        }
        assert(tc>0);
        assert((1LL << tc) > k);
        assert((1LL << (tc-1)) <= k);
        llong t = (n - (1LL<<tc))/k;
        while(k*t + (1LL<<tc) < n) t++;
        assert(k*t + (1LL<<tc) >= n);
        assert(k*(t-1) + (1LL<<tc) < n);
        cout<<t+tc<<endl;
    }
}

/*
after t hours, the number of computers with file is
0: 1
 1: 2
 2: 4
 3: 8
 if 2^(t-1) <= k
 t: 2^t
 else
 t: f(t-1) + k

 find cutoff t first
 if 2^t > k, then after t hours, we cannot duplicate anymore
 so t > log2(k) means t is the last one
 we can do rounddown(log2(k))+1  plus a further precision check

 then we do
 2^t'+k*(t-t') >= n
 kt >= n - 2^t' + kt'
 t >= (n - 2^t' + kt')/k
 */