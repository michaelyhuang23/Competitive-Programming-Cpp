#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl



struct Point{
	int x, y;
	complex<double> ptr;
	int c;
	Point(){}
	Point(int x_, int y_, int c_) : x(x_), y(y_), c(c_), ptr(x,y) {}
	int dot(Point other){
		return (int)round((conj(ptr) * other.ptr).real());
	}

	int cross(Point other){
		return (int)round((conj(ptr) * other.ptr).imag());
	}

	bool operator<(const Point& other){
		if(x == other.x) return y<other.y;
		return x<other.x;
	}

	Point operator+(const Point& other){
		Point ret(x+other.x, y+other.y, c);
		return ret;
	}

	Point operator-(const Point& other){
		Point ret(x-other.x, y-other.y, c);
		return ret;
	}

};


vector<Point> make_hull(vector<Point> ptrs){ // might be quite buggy
	Point p0 = min_element(ptrs.begin(), ptrs.end());
	auto compareAng = [&](Point p1, Point p2){
		if(arg(p1.ptr-p0.ptr) == arg(p2.ptr-p0.ptr)) return abs(arg(p1.ptr-p0.ptr)<abs(p2.ptr-p0.ptr);
		return arg(p1.ptr-p0.ptr) < arg(p2.ptr-p0.ptr);
	};
	sort(ptrs.begin(), ptrs.end(), compareAng);
	vector<Point> hull;
	for(int i=0;i<ptrs.size();i++){
		if(hull.size()<2){
			hull.pb(ptrs[i]);
		}else{
			while(hull.size()>=2 && (hull[hull.size()-1]-hull[hull.size()-2]).cross(ptrs[i]-hull[hull.size()-1])<=0)
				hull.pop_back();
			hull.pb(ptrs[i]);
		}
	}

	return hull;
}


int n;
void solve(){
	cin >> n;
	vector<Point> ptrs(n);
	unordered_set<int> cols;
	for(int i=0;i<n;i++) {
		int x,y,c; cin >> x >> y >> c;
		c--;
		ptrs[i] = Point(x,y,c);
		cols.insert(c);
	}

	int nc = cols.size();
	vector<vector<Point>> ptrsC(nc);

	for(int i=0;i<n;i++){
		int x = ptrs[i].x;
		int y = ptrs[i].y;
		int c = ptrs[i].c;
		ptrsC[c].pb(Point(x, y, c));
	}

	vector<vector<Point>>  hulls(nc);
	for(int c=0;c<nc;c++){
		hulls[c] = make_hull(ptrsC[c]);
	}

	
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}




