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
#include <iomanip>
#include <complex>

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    iint c;
    cout<<fixed;
    cout<<setprecision(1);
    while(cin >> c){
    	if(c == 0) break;
    	vector<Point> ptrs(c+1);
    	For(i, c){
    		iint x, y; cin >> x >> y;
    		ptrs[i] = {(ddouble)x, (ddouble)y};
    	}
    	ptrs[c] = ptrs[0];
    	ddouble sum = 0;
    	For(i, c){
    		sum += ptrs[i].X * ptrs[i+1].Y - ptrs[i].Y * ptrs[i+1].X;
    	}
    	sum /= 2;
    	if(sum>0){
    		cout<<"CCW "<<sum<<endl;
    	}else{
    		cout<<"CW "<<-sum<<endl;
    	}
    }
}















