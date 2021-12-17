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
#include <complex>
#include <fstream>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
typedef long double ddouble;
typedef complex<ddouble> Point;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007
#define X real()
#define Y imag()


bool cmp(Point p1, Point p2){
    return (arg(p1) < arg(p2)); // arg returns - pi to pi
}

bool same_side(Point p1, Point p2){
	if((conj(p1)*p2).X >= 0) return true;
	else return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint n; cin >> n;
    vector<Point> ptrs(n);
    For(i,n){
    	iint x, y; cin >> x >> y;
    	ptrs[i] = {(ddouble)x, (ddouble)y};
    }
    sort(ptrs.begin(), ptrs.end(), cmp);
    vector<Point> ptrs2(n*2);
    copy(ptrs.begin(),ptrs.end(),ptrs2.begin());
    copy(ptrs.begin(),ptrs.end(),ptrs2.begin()+n);
    iint j = 0;
    Point dd = {0.0,0.0};
    llong maxNorm = 0;
    for(iint i = 0; i<2*n; ){
    	Point r = ptrs2[i];
    	Point l = ptrs2[j];
    	if(same_side(r, dd)){
    		dd += r;
    		i++;
    		while(!same_side(l, dd)){
    			dd -= l;
    			j++;
    			l = ptrs2[j];
    		}
    	}else{
    		dd -= l;
    		j++;
    	}
    	maxNorm = max(maxNorm,(llong)round(norm(dd)));
    }
    cout<<maxNorm<<endl;
}








