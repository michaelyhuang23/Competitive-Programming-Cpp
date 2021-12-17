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
#include <unordered_map>
#include <unordered_set>
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
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (iint i = 0; i < j; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
typedef pair<iint, iint> ipair;
typedef vector<iint> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
#define MOD 1000000007

iint gcd(iint a, iint b){
    if(b==0)
        return a;
    return gcd(b, a%b);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint maxPrimeDiv[1000001];
    For(i,1000001) maxPrimeDiv[i]=1;
    for(int k=2; k<1000001; k++){
        if(maxPrimeDiv[k]!=1)
            continue;
        for(int j=0; j*k<1000001; j++)
            maxPrimeDiv[j*k]=k;
    }
    int t;
    cin >> t;
    while(t--){
        iint n;
        cin >>n;
        iint arr[n];
        For(i,n)
            cin>>arr[i];

        iint gcdd = arr[0];
        for(int i=1; i<n; i++)
            gcdd = gcd(gcdd,arr[i]);
        
        For(i,n) arr[i]/=gcdd;
        //For(i,n) cout<<arr[i]<<" ";
        //cout<<'\n';
        
        unordered_map<iint, pair<iint,vector<iint>>> minPrime;
        unordered_map<iint, int> primeCount[n];
        For(i,n){
            iint num = arr[i];
            while(num>1){
                iint div = maxPrimeDiv[num];
                if(primeCount[i].find(div)==primeCount[i].end())
                    primeCount[i][div]=1;
                else
                    primeCount[i][div]++;
                num/=div;
            }
        }
        unordered_map<iint, iint> primeHead;
        for(const auto &[ key, value ] : primeCount[0])
            For(i,n)
                if(primeCount[i].find(key) != primeCount[i].end()) primeHead[key]=i+1; else break;

        unordered_map<iint, iint> primeTail;
        for(const auto &[ key, value ] : primeCount[n-1])
            for(iint i=n-1; i>=0; i--)
                if(primeCount[i].find(key) != primeCount[i].end()) primeTail[key]=n-i; else break;
        
        unordered_map<iint, iint> primeInterv;
        unordered_map<iint, iint> curInterv;
        for(iint i=1; i<n; i++){
            for(const auto &[ key, value ] : primeCount[i]){
                if(primeCount[i-1].find(key)==primeCount[i-1].end())
                    curInterv[key] = 1;
                else
                    curInterv[key]++;
                if(primeInterv.find(key)==primeInterv.end())
                    primeInterv[key] = curInterv[key];
                else
                    primeInterv[key] = max(primeInterv[key], curInterv[key]);
            }
        }

        for(const auto &[ key, value ] : primeHead){
            iint len = primeHead[key];
            //cout<<"primehead "<<key<<" has len "<<len;
            if(primeTail.find(key)!=primeTail.end()){
                len+=primeTail[key];
                //cout<<"primetail "<<key<<" has len "<<primeTail[key];
            }
            len = min(len, n);
            if(primeInterv.find(key)!=primeInterv.end())
                primeInterv[key] = max(primeInterv[key], len);
            else
                primeInterv[key] = len;
        }
        iint totalMaxSep=0;
        for(const auto &[ key, value ] : primeInterv){
            //cout<< "prime "<<key <<" has consec "<<value<<'\n';
            totalMaxSep = max(totalMaxSep,value+1);
        }
        
        cout<<max(0L,totalMaxSep-1)<<'\n';
    }
}