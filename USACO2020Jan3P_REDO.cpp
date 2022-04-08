#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000

struct Line{
	int k,b,x,id; // xl is the head endpoint of the line
	Line():k(0),b(0),x(0),id(0){}
	Line(int k_,int b_):k(k_),b(b_){}
	Line(int k_,int b_,int i_):k(k_),b(b_),id(i_){}
	bool operator<(Line other){ return k<other.k; }
	int eval(int x){
		return x*k+b;
	}
	double isect(Line& other){
		if(k == other.k) return (b < other.b) ? -inf : inf; // this is dependent
		return (double)(other.b-b)/((double)(k-other.k));
	}
};

bool comp(Line& l1, Line& l2){
	return l1.x < l2.x;
}

struct HullLines{
	vector<Line> lines;
	
	Line query(int x){
		Line ll; ll.x = x;
		auto ret = upper_bound(lines.begin(), lines.end(), ll, comp);
		if(ret == lines.begin()) return Line(); // what else should we do?
		return *prev(ret);
	}

	int query_val(int x){
		return query(x).eval(x);
	}

	void push_backS(Line& ll){ // back means lower k
		assert(lines.empty() || ll.k <= lines.back().k);
		while(!lines.empty() && lines.back().x>=ll.isect(lines.back()))
			lines.pop_back();
		if(lines.empty()){
			ll.x = -inf;
			lines.pb(ll);
		}else{
			ll.x = ll.isect(lines.back());
			lines.pb(ll);
		}
	}

	void push_backL(Line& ll){

	}

};

const double eps = 1e-5;


int n; 
vector<int> H,Q,ans;
vector<pair<int,int>> ptrs;


void solve1(){
	HullLines hull;
	for(auto& ptr : ptrs){
		int i = ptr.second;

		Line lin(H[i],i,i);
		hull.push_backS(lin);
		// put ourselves in

		if(H[i]<H[Q[i]]) continue;

		// now bin-search for w;
		double ll=-inf*2, rr=inf*2;
		int ansj=-1;
		while(rr-ll>eps){
			int w = (ll+rr)/2;
			Line lin = hull.query(w);
			if(Q[i]+w*H[Q[i]]-lin.eval(w)<=0){
				ansj = lin.id;
				ll = w-eps;
			}else rr = w+eps;
		}

		ans[i]=ansj;

	}
}

void solve(){
	cin >> n;
	H = vector<int>(n);
	Q = vector<int>(n);
	ans = vector<int>(n,-1);
	ptrs = vector<pair<int,int>>(n); // H, i
	for(int i=0;i<n;i++) cin >> H[i];
	for(int i=0;i<n;i++) cin >> Q[i];
	for(int i=0;i<n;i++) ptrs[i] = mp(H[i],i);

	sort(ptrs.rbegin(), ptrs.rend());

	solve1();


	// reverse the sequences and stuffs, run solve1 again (mind id changes)
}























int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}