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
#define Mem(a, b) memset(a, (b), sizeof(a))
#define ForTo(i, j, k) for (int i=j ; i<=k ; i++)
#define For(i, j) ForTo(i, 0, j-1)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (int)2147483647
#define PI 3.1415926
typedef pair<int, int> ipair;
typedef vector<int> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    string str;
    cin>>str;
    int endP = n-1;
    For(i,n-1){
        if(str.at(i+1)>str.at(0)){
            endP = i; break;
        }
    }
    bool hasEq = false;
    ForTo(i,1,n-1) if(str.at(i)==str.at(0)) hasEq=true;
    if(endP<n-1){
        //
    }else if(endP==n-1 && !hasEq){
        //
    }else if(endP==n-1 && hasEq){

    }

}