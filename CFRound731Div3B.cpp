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
        string s;
        cin >> s;
        int n = s.length();
        bool success = true;

        for(char c = 'a'; c<='z'; c++){
            bool found = false;
            For(i, n)
                if(s.at(i)==c){
                    if(found)
                        success=false;
                    else
                        found=true;
                }
        }
        int lhot=-1, rhot=-1;
        For(i, n)
            if(s.at(i)=='a'){
                lhot = i;
                rhot = i;
            }
        if(lhot==-1 && rhot==-1)
            success=false;
        while(rhot-lhot+1<n){
            int k = rhot-lhot+1;
            char c = k+'a';
            if(lhot>0 && s.at(lhot-1)==c)
                lhot--;
            else if(rhot<n-1 && s.at(rhot+1)==c)
                rhot++;
            else{
                success=false;
                break;
            }
        }
        if(success)
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
}