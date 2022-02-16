#include<vector>
#include<algorithm>
#include<math.h>
#include<assert.h>
#include<iostream>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl

struct BIT{
	vector<int> bits; // index start from 1
	int n;
	BIT(int n_){
		n = n_+2;
		bits = vector<int>(n,0);
	}
	int lowbit(int n){ return n&(-n); }
	void update(int idx, int val){
		idx+=2; // for safety
		for(int i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	int get_sum(int idx){
		if(idx<0) return 0;
		idx+=2; // for safety
		int sum = 0;
		for(int i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};

struct Interval{
	int a, b, c;
	Interval(int a_, int b_, int c_): a(a_), b(b_), c(c_) {}
	Interval(){}
	bool operator<(const Interval other) const { 
		return b<other.b;
	}
};

void solve(){
	int n; cin >> n;
	vector<Interval> intervals(n);
	for(int i=0;i<n;i++){
		int a, b, c; cin >> a >> b >> c;
		intervals[i] = Interval(a,b,c);
	}
	sort(intervals.begin(), intervals.end());
	BIT tracker(50001);
	vector<pair<int,int> > fillInt;
	for(int i=0;i<n;i++){
		int a,b,c;
		a = intervals[i].a;
		b = intervals[i].b;
		c = intervals[i].c;

		int end = tracker.get_sum(b);
		int start = tracker.get_sum(a-1);
		int sum = end-start;
		if(sum>=c){
			;
		}else{
			int need = c-sum;
			int cur_b = b;
			while(need>0){
				if(fillInt.empty()){
					int cur_a = cur_b - need + 1;
					int reduce = cur_b - cur_a + 1;
					need -= reduce;
					for(int j = cur_a; j<=cur_b; j++){
						assert(tracker.get_sum(j)-tracker.get_sum(j-1) == 0);
						tracker.update(j, 1);
					}
					fillInt.pb(mp(cur_a, b));
				}else{
					int cur_a = max(fillInt.back().second+1, cur_b - need + 1);
					int reduce = cur_b - cur_a + 1;
					need -= reduce;
					for(int j = cur_a; j<=cur_b; j++){
						assert(tracker.get_sum(j)-tracker.get_sum(j-1) == 0);
						tracker.update(j, 1);
					}
					assert(need>=0);
					if(need > 0){
						// this should include the case need > 0
						cur_b = fillInt.back().first-1; // mind bound
						fillInt.pop_back();
						assert(cur_b >= a);
					}else{
						fillInt.pb(mp(cur_a, b));
					} // there's much more graceful way to do this with binary search
				}
			}

		}
	}

	print(tracker.get_sum(50001));
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}


