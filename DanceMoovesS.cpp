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
#include <unordered_set>
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

iint* colors = new iint[200001];
unordered_set<iint>* occurs = new unordered_set<iint>[200001];

inline void dfs(iint i, iint* permute, iint color, unordered_set<iint>* reaches){
	if(colors[i]>-1){
		assert(colors[i]==color);
		return;
	}
	colors[i] = color;
	occurs[color].insert(reaches[i].begin(),reaches[i].end());
	dfs(permute[i],permute,color,reaches);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint N, K;
    cin >> N >> K;
    iint* permute = new iint[N];
    unordered_set<iint>* reaches = new unordered_set<iint>[N];
    For(i,N) permute[i] = i;
    For(i,N) reaches[i].insert(i);
    For(i,K){
    	iint a, b;
    	cin >> a >> b;
    	a--; b--;
    	reaches[permute[a]].insert(b);
    	reaches[permute[b]].insert(a);
    	iint temp = permute[a]; permute[a] = permute[b]; permute[b] = temp;
    }
    fill(colors,colors+N,-1);
    iint color = 0;
    For(i,N){
    	if(colors[i]>-1) continue;
    	dfs(i,permute,color,reaches);
    	color++;
    }
    For(i,N){
    	cout<<occurs[colors[i]].size()<<endl;
    }
}




