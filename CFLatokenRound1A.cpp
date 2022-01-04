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
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k) for (int i=j ; i<=k ; i++)
#define REP(i, j) FOR(i, 0, j-1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define MP make_pair
#define PB push_back
#define INF (int)2147483647
#define PI 3.1415926
typedef pair<int, int> ipair;
typedef vector<int> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;
#define MOD 1000000007

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    REP(i,t){
        int n,m;
        cin>>n>>m;
        cin.ignore();
        int r_is_odd = -1;
        bool success = 1;
        char grid[n][m];
        REP(j,n){
            string str;
            getline(cin,str);
            REP(k,m){
                grid[j][k]=str.at(k);
                if(str.at(k)=='.') continue;
                if(r_is_odd==-1){
                    if(str.at(k)=='R'){
                        r_is_odd = abs(k-j)%2;
                    }
                    if(str.at(k)=='W'){
                        r_is_odd = !(abs(k-j)%2);
                    }
                }
                int cr_is_odd = -1;
                if(str.at(k)=='R'){
                    cr_is_odd = abs(k-j)%2;
                }
                if(str.at(k)=='W'){
                    cr_is_odd = !(abs(k-j)%2);
                }
                if(cr_is_odd!=r_is_odd){
                    success=0;
                }
            }
        }
        if(success){
            if(r_is_odd==-1)
                r_is_odd=1;
            char result[n][m];
            cout<<"YES\n";
            REP(r,n){
                REP(c,m){
                    char chr;
                    if((abs(r-c)%2)==r_is_odd)
                        chr='R';
                    else
                        chr='W';
                    if(grid[r][c]!='.')
                        assert(grid[r][c]==chr);
                    result[r][c]=chr;
                    if(r>=1 && c>=1)
                        assert(result[r][c]!=result[r-1][c] && result[r][c]!=result[r][c-1]);
                    cout<<chr;
                }
                cout<<'\n';
            }
        }else{
            cout<<"NO\n";
        }
    }
}