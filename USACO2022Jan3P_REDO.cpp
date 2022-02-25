#include<bits/stdc++.h>


using namespace std;

typedef long long llong;
typedef long double ddouble;
typedef complex<ddouble> point;
#define X real()
#define Y imag()
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 10000000000

ddouble cross(point A, point B){
	return (conj(A)*B).Y;
}

pair<point,vector<point>> make_hull(){
	llong G; cin >> G;
	vector<point> ptrs(G);

	point offset(-inf, -inf);
	for(llong i=0;i<G;i++){
		llong x, y; cin >> x >> y;
		ptrs[i] = point(x,y);
		auto cond = [&](point p1, point p2){
			if(p1.Y == p2.Y) return p1.X < p2.X;
			return p1.Y > p2.Y;
		};
		if(cond(ptrs[i], offset))
			offset = ptrs[i];
	}


	for(llong i=0;i<G;i++) 
		ptrs[i] -= offset;


	sort(ptrs.begin(), ptrs.end(),[&](point p1, point p2){
		return arg(p1)<arg(p2);
	});


	vector<point> hull;
	hull.pb(point(0,0));
	auto cond = [&](point ptr){
		if(hull.size() < 2) return false;
		point A = ptr - hull[hull.size()-1];
		point B = hull[hull.size()-1] - hull[hull.size()-2];
		if(cross(B, A) <= 0) return true;
		else return false;
	};
	for(llong i=0;i<G;i++){
		if(ptrs[i] == point(0,0)) continue;
		while(cond(ptrs[i])) hull.pop_back();
		hull.pb(ptrs[i]);
	}

	return mp(offset, hull);
}

void solve(){
	llong N; cin >> N;

	vector<vector<point>> hulls(N);
	point cur;

	for(llong i=0;i<N;i++){
		auto ret = make_hull();
		hulls[i] = ret.second;
		//deb(hulls[i])
		cur += ret.first;
	}


	vector<point> lines;
	for(llong i=0;i<N;i++){
		vector<point>& hull = hulls[i];
		for(llong j=0;j<hull.size()-1;j++){
			lines.pb(hull[j+1]-hull[j]);
		}
		lines.pb(hull[0]-hull[hull.size()-1]); // if is 2, it's just a convex hull with no area
	}


	sort(lines.begin(), lines.end(), [&](point p1, point p2){
		return arg(p1)<arg(p2);
	});

	llong maxD = 0;

	for(llong i=0;i<lines.size();i++){
		llong d = round(norm(cur));
		maxD = max(maxD, d);
		cur += lines[i];
	}

	print(maxD);

}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}