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
#include <complex>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
typedef long double ddouble;
typedef complex<llong> Point;
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

struct Line{
	Point s, e;
    iint id;
	Line(){ s = {0,0}; e = {0, 0}; }
	Line(llong x1, llong y1, llong x2, llong y2, iint id_){
		s = {x1, y1};
		e = {x2, y2};
        id = id_;
	}
	bool operator<(const Line& o) const {
		if(s.X > o.s.X){
			return (conj(o.e-o.s)*(s-o.s)).Y<0;
		}else{ // should work for equal as well
			return (conj(e - s)*(o.s - s)).Y>0;
		}
    }
};



int main() {
    ifstream fin("hillwalk.in");
    ofstream fout("hillwalk.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    iint N; fin >> N;
    vector<Line> lines(N);
    vector<tuple<iint,iint,bool,iint> > ptrs;
    For(i,N){
    	llong x1,x2,y1,y2;
    	fin >> x1 >> y1 >> x2 >> y2;
    	lines[i] = Line(x1,y1,x2,y2,i);
    	ptrs.pb(make_tuple(x1,y1,1,i));
    	ptrs.pb(make_tuple(x2,y2,0,i));
    }

    sort(ptrs.begin(), ptrs.end());

    set<Line> tracker;
    iint cur_id = 0;
    Line curLine = lines[0];
    iint count = 1;
    assert(get<0>(ptrs[0]) == 0 && get<1>(ptrs[0]) == 0 && get<3>(ptrs[0]) == 0);
    For(i, ptrs.size()){
    	bool ishead = get<2>(ptrs[i]);
    	iint id = get<3>(ptrs[i]);
    	if(id == cur_id){
    		if(ishead) continue;
    		if(tracker.rbegin() == tracker.rend()) break;
    		curLine = *tracker.rbegin();
            tracker.erase(curLine);
            cur_id = curLine.id;
    		count++;
    	}else{
    		if(ishead){ // compare with current
    			if(lines[id] < curLine){
                    tracker.insert(lines[id]);
                }
    		}else{
    			tracker.erase(lines[id]);
    		}
    	}
    }
    fout<<count<<endl;
    fout.close();
}

/*

use a priority queue to keep all the lines. Because there's no intersections, 
there's a strict y ordering of line segments, which we can order by comparing 
using cross products.

Consider the event of start and finish for each line segment. 

*/









