1#include <iostream>
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
typedef complex<ddouble> Point;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (llong)4223372036854775807
#define PI 3.1415926
#define MOD 1000000007
#define Y imag()
#define X real()

vector<pair<llong,llong> > ptrs;

struct Fraction{
	llong num, den;
	bool valid = true;
	Fraction(){num = -1; den = -1; valid = false;}
	Fraction(llong n, llong d){
		if(n==-1 || d==-1) valid = false;
		num = n; den = d;
        if(valid) {assert(n>=0); assert(d>0);}
		num /= gcd(n,d);
		den /= gcd(n,d); 
	}
	const bool operator < ( const Fraction &o ) const{
		if(!valid) return false;
		if(!o.valid) return true;
        return num*o.den < o.num*den;
    }
};

ostream& operator<<(ostream& os, const Fraction& f)
{
    os << f.num << '/' << f.den;
    return os;
}

struct Line{
	llong h, v;
	Line(){h=-inf/2;v=0;}
	Line(llong h_, llong v_){h=h_;v=v_;}
	Fraction intersect(Line other){
        if(v==other.v && h==other.h) return Fraction(0,1);
		llong th = h, lh = other.h;
		llong tv = v, lv = other.v;
		if(other.h>h) {th = other.h; tv = other.v; lh = h; lv = v;}
		if(tv==lv){
			cout<<v<<" "<<h<<" "<<other.v<<" "<<other.h<<endl;
		}
        assert(tv-lv!=0);
		if(((ddouble)th-lh)/((ddouble)tv-lv)<0)
			return Fraction(-1,-1);
		llong num = th-lh;
		llong den = tv-lv;
		return Fraction(num, den);
	}
	Point intersectP(Line other){
        assert(!(v==other.v && h==other.h));
		llong th = h, lh = other.h;
		llong tv = v, lv = other.v;
		if(other.h>h) {th = other.h; tv = other.v; lh = h; lv = v;}
		ddouble tt = (th-lh)/(tv-lv);
		assert(tt>=-0.00000001);
		return Point(tt,h - tt*v);
	}
};

vector<Fraction> results;
deque<pair<Point, Line> > hull;

Fraction find_point(llong y, llong v){
	Line cline = Line(y,v);
	llong ll = 0, rr = hull.size()-2, ans = -1;
	Point p = {0.0, (ddouble)y};
	Point vec = {1.0, -(ddouble)v};
	while(ll <= rr){
		llong cur = (ll + rr)/2;
		llong nxt = cur + 1;
		ddouble c1 = (conj(vec)*(hull[cur].first - p)).Y;
		ddouble c2 = (conj(vec)*(hull[nxt].first - p)).Y;
		if(c1>0 && c2>0){
			ll = cur + 1;
		}else if(c1<0 && c2<0){
			rr = cur - 1;
		}else{
			ans = cur;
			break;
		}
	}
	if(ans == -1) return Fraction(-1,-1);
	Fraction ret = cline.intersect(hull[ans].second);
	assert(ret.valid);
	return ret;
}

void add_line(Line l){
	while(true){
		auto top = hull.front(); hull.pop_front();
		Line topl = top.second;
		if(hull.size() == 0){
			hull.push_front(make_pair(l.intersectP(topl), topl));
			hull.push_front(make_pair(Point(0,l.h), l));
			break;
		}
		auto top2 = hull.front();
		Line top2l = top2.second;
		auto interl = l.intersect(topl);
		auto intero = topl.intersect(top2l);
		if(!interl.valid || intero<interl)
			continue;
		hull.push_front(make_pair(l.intersectP(topl), topl));
		hull.push_front(make_pair(Point(0,l.h), l));
		break;
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream fin("falling.in");
    ofstream fout("falling.out");
    llong n; fin >> n;
    ptrs = vector<pair<llong,llong> >(n+1); // h, v
    vector<llong> questions(n+1);
    for(llong i=1;i<=n;i++) fin >> get<0>(ptrs[i]); // guaranteed distinct
    for(llong i=1;i<=n;i++) get<1>(ptrs[i]) = i;
    for(llong i=1;i<=n;i++) fin >> questions[i];

    ptrs[0] = make_pair(inf, inf);
    sort(ptrs.begin(), ptrs.end(), greater<pair<llong,llong> >());

    vector<llong> map2s(n+1);
    for(llong i = 1; i <= n; i++) map2s[get<1>(ptrs[i])] = i;
    vector<llong> map2u(n+1);
    for(llong i = 1; i <= n; i++) map2u[i] = get<1>(ptrs[i]);

    results = vector<Fraction>(n+5);
    hull = deque<pair<Point, Line> >();
    hull.push_back(make_pair(Point(0,-inf/2), Line(-inf/2,0)));
    for(llong i = 1; i <= n; i++){
    	llong y = get<0>(ptrs[i]);
    	llong v = get<1>(ptrs[i]);
        llong q = questions[map2u[i]];
        llong id = map2u[i];
        llong qn = map2s[q];
        llong qy = get<0>(ptrs[qn]);
        llong qv = get<1>(ptrs[qn]);
        if(qy >= y) continue;
        Line l(y,v);
        Line ql(qy,qv);
        results[id] = find_point(qy,qv);
        results[id] = min(results[id], l.intersect(ql));
        add_line(Line(y,v));
    }

    // second half
    llong maxH = 0;
    llong maxV = 0;
    for(llong i=1; i<=n; i++) maxH = max(maxH, get<0>(ptrs[i]));
    for(llong i=1; i<=n; i++) maxV = max(maxV, get<1>(ptrs[i]));
    for(llong i=1; i<=n; i++){
        get<0>(ptrs[i]) = - get<0>(ptrs[i]);
        get<1>(ptrs[i]) = - get<1>(ptrs[i]);
    }
    sort(ptrs.begin(), ptrs.end(), greater<pair<llong,llong> >());

    for(llong i = 1; i <= n; i++) map2s[-get<1>(ptrs[i])] = i;
    for(llong i = 1; i <= n; i++) map2u[i] = -get<1>(ptrs[i]);

    for(llong i=1; i<=n; i++){
        get<0>(ptrs[i]) += maxH+1;
        get<1>(ptrs[i]) += maxV+1;
    }

    hull = deque<pair<Point, Line> >();
    hull.push_back(make_pair(Point(0,-inf/2), Line(-inf/2,0)));
    for(llong i = 1; i <= n; i++){
        llong y = get<0>(ptrs[i]);
        llong v = get<1>(ptrs[i]);
        llong q = questions[map2u[i]];
        llong id = map2u[i];
        llong qn = map2s[q];
        llong qy = get<0>(ptrs[qn]);
        llong qv = get<1>(ptrs[qn]);
        if(qy >= y) continue;
        Line l(y,v);
        Line ql(qy,qv);
        results[id] = min(results[id],find_point(qy,qv));
        results[id] = min(results[id], l.intersect(ql));
        add_line(Line(y,v));
    }

    for(llong i=1; i<=n; i++){
    	if(!results[i].valid) fout<<-1<<endl;
    	else{
            assert(results[i].num!=0);
            fout<<results[i].num<<"/"<<results[i].den<<endl;
        }
    }
    fout.close();
}


/*

consider each world from top to bottom. Draw their worldlines!!! 
Visualize motion on world lines let's go!!!

build min convex hull gradually. Use binary search to query intersection

*/