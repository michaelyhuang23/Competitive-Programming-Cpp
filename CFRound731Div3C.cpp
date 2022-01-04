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
    cin>>t;
    while(t--){
        cin.ignore(256, '\n');
        int k, n, m;
        cin >> k >> n >> m;
        int arr[n];
        For(i,n) cin>>arr[i];
        For(i,n) arr[i]-=k;
        int brr[m];
        For(i,m) cin>>brr[i];
        For(i,m) brr[i]-=k;
        int a=0, b=0;
        int length = 0;
        bool success = true;
        int crr[n+m];
        while(a<n && b<m){
            if(arr[a]<brr[b]){
                if(arr[a]==-k)
                    length++;
                if(arr[a]<=length){
                    crr[a+b]=arr[a];
                    a++;
                }else{
                    success=false;
                    break;
                }
            }else{
                if(brr[b]==-k)
                    length++;
                if(brr[b]<=length){
                    crr[a+b]=brr[b];
                    b++;
                }else{
                    success=false;
                    break;
                }
            }
        }
        while(a<n){
            if(arr[a]==-k)
                length++;
            if(arr[a]<=length){
                crr[a+b]=arr[a];
                a++;
            }else{
                success=false;
                break;
            }
        }
        while(b<m){
            if(brr[b]==-k)
                length++;
            if(brr[b]<=length){
                crr[a+b]=brr[b];
                b++;
            }else{
                success=false;
                break;
            }
        }
        if(!success){
            cout<<-1<<'\n';
            continue;
        }

        For(i,a+b-1){
            cout<<crr[i]+k<<" ";
        }
        cout<<crr[a+b-1]+k<<'\n';
    }
}