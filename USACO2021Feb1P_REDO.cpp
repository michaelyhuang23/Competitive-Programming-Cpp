#include<iostream>
#include<assert.h>
#include<vector>
#include<algorithm>
#include <tuple>

using namespace std;

#define mp make_pair
#define pb push_back
#define inf 1000000000

struct BIT{
	vector<int> bits; // index start from 1
	int n;
	BIT(int n_){
		n = n_+1;
		bits = vector<int>(n,0);
	}
	int lowbit(int n){ return n&(-n); }
	void update(int idx, int val){
        idx++;
		for(int i=idx; i<n; i+=lowbit(i)) bits[i]+=val;
	}
	int get_sum(int idx){
        idx++;
		int sum = 0;
		for(int i=idx; i>0; i-=lowbit(i)) sum += bits[i];
		return sum;
	}
};

int N, Q;
vector<int> cols;
vector<tuple<int,int,int> > ranges;
vector<int> bits;
vector<vector<int> > rmq;

int get_min(int l, int r){ // error prone
	r++;
	if(l>=r) return inf;
	int j=0;
	for(;(1<<j)<=r-l;j++);
	j--;
	return min(rmq[j][l],rmq[j][r-(1<<j)]);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	cols = vector<int>(N);
	for(int i=0;i<N;i++) cin >> cols[i];

	vector<int> prev(N);
	vector<int> lastLoc(N+5,-1);
	for(int i=0;i<N;i++){
		prev[i] = lastLoc[cols[i]]; // null is set to -1
		lastLoc[cols[i]] = i;
	}

	rmq = vector<vector<int> >(32);
	for(int i=0;i<32;i++) rmq[i] = vector<int>(N);
	for(int i=0;i<N;i++) rmq[0][i] = cols[i];
	for(int i=1;i<32;i++) 
		for(int j=0;j<N;j++)
			rmq[i][j] = min(rmq[i-1][j], rmq[i-1][min(N-1,j+(1<<(i-1)))]);
		// mind bug here


	ranges = vector<tuple<int,int,int> >(Q);
	for(int i=0;i<Q;i++){
		int a,b; cin >> a >> b;
		a--; b--;
		ranges[i] = tuple<int,int,int>(b,a,i); // first is right hand
	}

	vector<int> ans(Q,-1);

	sort(ranges.begin(), ranges.end());

	BIT tracker(N+5);

	int j = 0;
	for(int i=0;i<Q;i++){
		int l = get<1>(ranges[i]);
		int r = get<0>(ranges[i]);
		//deb(mp(l,r))
		while(j<=r){
			//deb(mp(j,prev[j])) 
            if(prev[j]>-1) {
                int c = cols[j];
                int minn = get_min(prev[j] + 1, j - 1);
                //deb(mp(c,minn))
                if (minn > c) {
                	// deb(j)
                 //    deb(prev[j])
                 //    deb(N)
                    tracker.update(prev[j], 1);
                }
            }
			j++;
		}
		// now  j == r
		int save = tracker.get_sum(r) - tracker.get_sum(l-1);
		ans[get<2>(ranges[i])] = r-l+1-save;
	}

	for(int i=0;i<Q;i++){
		cout<<ans[i]<<endl;
	}
}






