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
    int t;
    cin >> t;
    while(t--){
        iint n,k;
        cin >> n >> k;
        iint arrs[k];
        llong tempArr[n];
        For(i,n) tempArr[i]=inf;
        For(i,k) cin >> arrs[i];
        For(i,k) arrs[i]--;
        For(i,k){
            llong temp;
            cin >> temp;
            tempArr[arrs[i]]=temp;
        }
        llong leftLow[n];
        llong rightLow[n];
        For(i,n){
            if(i==0){
                leftLow[i]=tempArr[i];
                continue;
            }
            leftLow[i] = min(leftLow[i-1]+1,tempArr[i]);
        }
        for(int i=n-1;i>=0;i--){
            if(i==n-1){
                rightLow[i]=tempArr[i];
                continue;
            }
            rightLow[i] = min(rightLow[i+1]+1,tempArr[i]);
        }
        For(i,n) tempArr[i] = min(leftLow[i],rightLow[i]);
        For(i,n-1) cout<<tempArr[i]<<" ";
        cout<<tempArr[n-1]<<'\n';
    }
}