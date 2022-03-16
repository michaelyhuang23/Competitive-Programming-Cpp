#include<bits/stdc++.h>


using namespace std;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define print(x) cout<<x<<endl
#define inf 1000000000

struct record{
	int pc, pp;
	int psize;
	int prank;
	record(int pc_, int pp_, int psize_, int prank_) : pc(pc_), pp(pp_), psize(psize_), prank(prank_) {}
	record(): pc(-1), pp(-1) {}
};

vector<tuple<int,int,int>> edges;

int n, m;

struct UFDS{
	vector<int> parent;
	vector<int> sizes;
	vector<int> rank;
	stack<record> ch;
	UFDS(int n){
		parent = vector<int>(n);
        sizes = vector<int>(n,1);
        rank = vector<int>(n,1);
		ch = stack<record>();
		iota(parent.begin(), parent.end(), 0);
	}
	int find(int num){
		while(parent[num] != num) num = parent[num];
		return num;
	}
	void merge(int a, int b){
		int pa = find(a);
		int pb = find(b);
		if(pa==pb) {
			ch.push(record());
			return;
		}
		if(rank[pa] <= rank[pb]){ // merge pa onto pb
			ch.push(record(pa,pb,sizes[pb],rank[pb]));
			parent[pa] = pb;
			sizes[pb] += sizes[pa];
			rank[pb] = max(rank[pb], rank[pa]+1);
		}else{
			ch.push(record(pb,pa,sizes[pa],rank[pa]));
			parent[pb] = pa;
			sizes[pa] += sizes[pb];
			rank[pa] = max(rank[pa], rank[pb]+1);
		}
	}
	int size(int num){
		return sizes[find(num)];
	}
	void rollback(){
		record cc = ch.top(); ch.pop();
		if(cc.pc == -1 || cc.pp == -1) return;
		parent[cc.pc] = cc.pc;
		sizes[cc.pp] = cc.psize;
		rank[cc.pp] = cc.prank;
	}
};



vector<int> solve_range(vector<tuple<int,int,int>>& queries){
	vector<int> sedges(edges.size());
	iota(sedges.begin(), sedges.end(), 0);
	auto comp = [&](int l, int r){
		return edges[l] > edges[r];
	};
	sort(sedges.begin(), sedges.end(), comp); // descending
	UFDS tracker(n);
	vector<tuple<int,int,int>> U;
	vector<tuple<int,int,int>> Q;
	int maxT = queries.size()+1;
	vector<int> answers(maxT-1);
	for(int i=0;i<queries.size();i++){
		if(get<0>(queries[i]) == 1){
			int b = get<1>(queries[i]);
			int w = get<2>(queries[i]);
			// update
			U.pb(mt(w,b,i+1));
		}else{
			int s = get<1>(queries[i]);
			int w = get<2>(queries[i]);
			// query
			Q.pb(mt(w,s,i+1));
		}
	}

	sort(Q.rbegin(), Q.rend()); // descending
	sort(U.rbegin(), U.rend()); // descending

	unordered_map<int, vector<pair<int,int>>> hp;
	for(int i=0;i<U.size();i++){
		auto& update = U[i];
		int b = get<1>(update);
		int ut = get<2>(update);
		int uw = get<0>(update);
		if(hp.find(b) == hp.end()){
			hp[b] = {mp(ut,uw)};
		}else{
			hp[b].pb(mp(ut,uw));
		}
	}

	for(auto& elem : hp){
		int b = get<0>(elem);
		vector<pair<int,int>>& updates = get<1>(elem); // pass by reference
		sort(updates.begin(), updates.end()); // verified
	}

	//deb(QB)

	int ec = 0;

	for(auto& query : Q){ 

		int w = get<0>(query);
		int s = get<1>(query);
		int t = get<2>(query);

		// add fixed edges
		while(ec < sedges.size() && get<0>(edges[sedges[ec]]) >= w) {
			if(hp.find(sedges[ec]) == hp.end())
				tracker.merge(get<1>(edges[sedges[ec]]), get<2>(edges[sedges[ec]]));
			ec++;
		}

		// process updates

		int mergeC = 0;

		for(auto& elem : hp){
			int b = get<0>(elem);
			vector<pair<int,int>>& updates = get<1>(elem);
			auto it = upper_bound(updates.begin(), updates.end(), mp(t,inf));
			int weight = 0;
			if(it == updates.begin()){
				// we use old weight;
				weight = get<0>(edges[b]);
			}else{
				it--;
				weight = get<1>(*it);
			}
			if(weight >= w){
				auto edge = edges[b];
				tracker.merge(get<1>(edge), get<2>(edge));
				mergeC++;
			}
		}

		answers[t-1] = tracker.size(s);

		while(mergeC--) tracker.rollback();
	}

	return answers;
}

int magic_num = 1000;

void solve(){
	cin >> n >> m;
	edges = vector<tuple<int,int,int>>(m);
	for(int i=0;i<m;i++){
		int u, v, d; cin >> u >> v >> d; u--; v--;
		edges[i] = mt(d, u, v);
	}
	int q; cin >> q;
	int T = min(q, magic_num);

	int prevC = -1;
	vector<tuple<int,int,int>> queries;
	vector<int> answers;
	vector<pair<int,int>> changebuffer;
	for(int i=1;i<=q;i++){
		if(i % T == 1) {
			prevC = i; //start
			queries = vector<tuple<int,int,int>>();
			// also time to materialize all previous changes
			for(auto& ch : changebuffer){
				get<0>(edges[ch.first]) = ch.second;
			}
			changebuffer = vector<pair<int,int>>();
		}
		int type, a, b;
		cin >> type >> a >> b; a--;
		queries.pb(mt(type,a,b));
		if(type == 1) changebuffer.pb(mp(a,b));
		if(i % T == 0) {
			// range [prevC, i];
			//print('\n');
			//deb(queries)
			vector<int> answer = solve_range(queries);
			answers.insert(answers.end(), answer.begin(), answer.end());
			queries = vector<tuple<int,int,int>>();
		}
	}

	if(queries.size()>0){
		//deb(queries)
		vector<int> answer = solve_range(queries);
		answers.insert(answers.end(), answer.begin(), answer.end());
	}

	for(int i=0;i<answers.size();i++) //print(answers[i]);
		if(answers[i] > 0)
			print(answers[i]);
}




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}













