#include<bits/stdc++.h>

using namespace std;
#define mp make_pair
#define pb push_back
#define print(x) cout<<x<<endl

int n;
vector<vector<int>> adj;
vector<int> sizes, parent, depth, ins, outs;
vector<int> head; 
// each node is in a heavy path. Connection between heavy paths are light paths
// head gives the head of the heavy path
int t = 0;

void dfs_process(int cur, int par){
	sizes[cur] = 1;
	parent[cur] = par;
	if(cur==par) depth[cur]=0;
	else depth[cur] = depth[par]+1;
	for(int& son : adj[cur]){
		if(son == par) continue;
		dfs_process(son, cur);
		sizes[cur] += sizes[son];

		if(adj[cur][0]==par || sizes[son] > sizes[adj[cur][0]]) swap(son, adj[cur][0]);
	}
}

void dfs_hld(int cur, int par){
	if(cur==par) head[cur]=cur;
	ins[cur] = t++;
	for(int son : adj[cur]){
		if(son == par) continue;
		head[son] = (son == adj[cur][0] ? head[cur] : son);
		dfs_hld(son, cur);
	}
	outs[cur] = t;
}

struct Node{
	int val;
	Node():val(0){}
	Node(int val_):val(val_){}
	void update(int val_){val=val_;};
	static Node merge(Node& ll, Node& rr){return Node(max(ll.val,rr.val));}
	void pull_up(Node& ll, Node& rr){(*this)=merge(ll,rr);}
	int ans(){return val;}
};

struct segtree{
	static int pow_up(int num){
		for(int i=0;i<32;i++) if(1<<i >= num) return 1<<i;
		return -1;
	}
	vector<Node> tree;
	int n;
	segtree(int size){
		n = pow_up(size);
		tree = vector<Node>(n*2);
		build();
	}
	void build(){
		for(int i = n-1; i>=1; i--) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	void change(int idx, int val){
		tree[n+idx].update(val);
		for(int i = (n+idx)>>1; i >= 1; i>>=1) tree[i].pull_up(tree[i<<1], tree[i<<1|1]);
	}
	int query(int left, int right){
		Node ll, rr;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) ll=Node::merge(ll,tree[left++]);
			if(!(right&1)) rr=Node::merge(tree[right--],rr);
			if(left==right) break; 
		}
		return Node::merge(ll,rr).ans();
	}
};



int query_path(int ans, int cur, segtree& tree){
	int total = 0;
	while(depth[head[cur]]>depth[ans]){		
		total = max(total, tree.query(ins[head[cur]], ins[cur]));
		cur = parent[head[cur]];
	}
	if(depth[cur]>=depth[ans]) 
		total = max(total, tree.query(ins[ans], ins[cur]));
	return total;
}












void solve(){
	int q; cin >> n >> q;
	sizes = vector<int>(n);
	parent = vector<int>(n);
	head = vector<int>(n);
	ins = vector<int>(n);
	outs = vector<int>(n);
	depth = vector<int>(n);
	vector<int> values(n);
	adj = vector<vector<int>>(n);
	for(int i=0;i<n;i++) cin>>values[i];
	for(int i=0;i<n-1;i++){
		int a,b; cin >> a >> b; a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	dfs_process(0,0);
	dfs_hld(0,0);
	vector<vector<int>> lift(20, vector<int>(n,0));
	lift[0] = parent;
	for(int i=1;i<20;i++)
		for(int j=0;j<n;j++)
			lift[i][j] = lift[i-1][lift[i-1][j]];
	auto get_lca = [&](int a, int b){
		if(depth[a]<depth[b]) swap(a,b);
		for(int i=19;i>=0;i--) if(depth[lift[i][a]]>=depth[b]) a=lift[i][a];
		assert(depth[a]==depth[b]);
		if(a==b) return a;
		for(int i=19;i>=0;i--) if(lift[i][a]!=lift[i][b]) {
			a = lift[i][a];
			b = lift[i][b];
		}
		assert(lift[0][a] == lift[0][b]);
		return lift[0][a];
	};
	segtree tree(n);
	for(int i=0;i<n;i++) tree.change(ins[i], values[i]);
	for(int i=0;i<q;i++){
		int type; cin >> type;
		if(type == 1){
			int s,x; cin >> s >> x; s--;
			tree.change(ins[s],x);
		}else{
			int a,b; cin >> a >> b; a--; b--;
			int lca = get_lca(a,b);
			cout<<max(query_path(lca,a,tree), query_path(lca,b,tree))<<" ";
		}
	}
	cout<<endl;
}






int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}