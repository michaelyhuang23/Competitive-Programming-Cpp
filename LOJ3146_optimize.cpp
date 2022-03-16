#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000
#define print(x) cout<<x<<endl

#define MAXSIZE 40000000

int nodes[MAXSIZE];
int lefts[MAXSIZE], rights[MAXSIZE];
int counter = 0;

int updateVal, updateIdx;
struct DynamicSegtree{

	DynamicSegtree(){
	}
	void pull_up(int idx){
		nodes[idx] = 0;
		if(lefts[idx]!=-1) nodes[idx] += nodes[lefts[idx]];
		if(rights[idx]!=-1) nodes[idx] += nodes[rights[idx]];
	}
	int query(int idx, int ll, int rr, int ts=0, int te=300005){
		//if(ll > rr) return 0; // default
		if(ll == ts && rr == te) return nodes[idx];
		int tm = (ts+te)/2;
		int leftNode = 0, rightNode = 0;
		if(lefts[idx]!=-1 && ll <= tm){
			leftNode = query(lefts[idx], ll, min(rr,tm), ts, tm);
		}
		if(rights[idx]!=-1 && rr > tm){
			rightNode = query(rights[idx], max(ll,tm+1),rr,tm+1,te);
		}
		return leftNode + rightNode;
	}
	void update(int idx, int ts=0, int te=300005){
		if(updateIdx==ts && updateIdx==te){
			nodes[idx]+=updateVal;
			return;
		}
		int tm = (ts+te)/2;
		if(updateIdx <= tm){
			if(lefts[idx]==-1) {
				lefts[idx] = ++counter;
				//rights[counter]=-1; lefts[counter]=-1; nodes[counter]=0;
			}
			update(lefts[idx], ts, tm);
		}else{
			if(rights[idx]==-1) {
				rights[idx] = ++counter;
				//rights[counter]=-1; lefts[counter]=-1; nodes[counter]=0;
			}
			update(rights[idx], tm+1, te);
		}

		pull_up(idx);
	}
};

struct BIT2D{
	vector<int> bits;
	DynamicSegtree tree;
	int n;
	BIT2D(int n_){
		n = n_+2; // safety
		bits = vector<int>(n);
		for(int i=0;i<n;i++) bits[i] = ++counter;
	}

	inline int low_bit(int num){
	    return num & (-num);
	}
	int query(int xp, int yp){ // idx starts at 1
		xp++; // shift index
	    int sum = 0;
	    for(int x = xp; x>0; x -= low_bit(x))
	    	sum += tree.query(bits[x], 0, yp);
	    return sum;
	}
	void update(int xp, int yp, int val){
		xp++; // shift index
	    for(int x = xp; x<=bits.size()-1; x+= low_bit(x)){
	    	updateIdx = yp;
	    	updateVal = val;
	    	tree.update(bits[x]); 
	    }
	}
};



void solve(){

	fill(nodes, nodes+MAXSIZE, 0);
	fill(lefts, lefts+MAXSIZE, -1);
	fill(rights, rights+MAXSIZE, -1);


	int n, q; cin >> n >> q;
	string s; cin >> s;
	vector<bool> open(n);
	for(int i=0;i<n;i++){
		open[i] = s[i] == '1';
	}
	set<pair<int,int>> intervals;
	int px = -1;
	for(int i=0;i<n;i++){
		if(i==0 && open[i] || open[i] && !open[i-1]){
			px = i; // start
		}
		if(i==n-1 && open[i] || open[i] && !open[i+1]){
			intervals.insert(mp(px, i)); // end
		}
	}

	//deb(intervals)

	vector<tuple<bool, int, int>> queries(q+1);
	for(int i=1;i<=q;i++){
		string type; cin >> type;
		if(type[0]=='q'){
			int l, r; cin >> l >> r;
			queries[i] = mt(1,l,r);
		}else{
			int x; cin >> x;
			queries[i] = mt(0,x,0);
		}
	}

	BIT2D tracker(n+5);
	BIT2D sumtracker(n+5);

	auto updateRect = [&](BIT2D& tree, int x1, int x2, int y1, int y2, int val){
		tree.update(x1,y1,val);
		tree.update(x1,y2+1,-val);
		tree.update(x2+1,y1,-val);
		tree.update(x2+1,y2+1,val);
	};

	for(auto& elem : intervals){
		int a = elem.first;
		int b = elem.second;
		for(int i=a;i<=b;i++){
			// goto [i,b]
			updateRect(tracker, i, i, i, b, 1);
			updateRect(sumtracker, i, i, i, b, q);
		}
	}

	for(int i=1;i<=q;i++){
		bool type = get<0>(queries[i]);
		// deb(i)
		// deb(tracker.query(0,1,0,4))
		// deb(intervals)
		if(type){
			int l = get<1>(queries[i]);
			int r = get<2>(queries[i]); r--;
			l--; r--; // r decrease by 2 because it's exclusive
			int state = tracker.query(l, r);
			int sum = sumtracker.query(l, r);
			//deb(mp(state, sum))
			print(sum - state*(q-i));
		}else{
			int x = get<1>(queries[i]);
			x--;
			int updateTracker = 0;
			int updateSum = 0;
			if(open[x]){
				auto it = intervals.upper_bound(mp(x,inf));
				//assert(it != intervals.begin());
				it--;
				pair<int,int> interv = *it;
				int left = interv.first;
				int right = interv.second;

				updateRect(tracker, left,x,x,right, -1);
				updateRect(sumtracker, left,x,x,right, -(q-i));

				intervals.erase(it);
				if(left<=x-1)
					intervals.insert(mp(left,x-1));
				if(x+1<=right)
					intervals.insert(mp(x+1,right));
			}else{
				auto top = intervals.upper_bound(mp(x,inf));
				int right = x;
				if(top != intervals.end() && (*top).first==x+1){
					right = (*top).second;
					intervals.erase(top);
				}
				auto bot = intervals.upper_bound(mp(x,inf)); 
				int left = x;
				if(bot != intervals.begin()){
					bot--;
					if((*bot).second==x-1){
						left = (*bot).first;
						intervals.erase(bot);
					}
				}

				updateRect(tracker, left,x,x,right, 1);
				updateRect(sumtracker, left,x,x,right, (q-i));

				intervals.insert(mp(left,right));
			}

			open[x] = open[x]^1;
		}
	}

}









int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}





