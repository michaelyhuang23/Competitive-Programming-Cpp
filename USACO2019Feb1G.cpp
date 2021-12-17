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

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (int i=0 ; i<j ; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

struct SegTree
{
	static iint pow_up(iint num){
		For(i,32) if(1LL<<i >= num) return 1LL<<i;
		return -1;
	}
	iint* tree;
	iint n;
	SegTree(iint* arr,iint size){
		n = pow_up(size);
		tree = new iint[2*n];
		copy(arr, arr+size, tree+n);
		fill(tree+n+size,tree+2*n,0);
		build();
	}
	inline void build(){
		for(iint i = n-1; i>=1; i--) tree[i] = tree[i<<1] ^ tree[i<<1|1];
	}
	inline void change(iint idx, iint val){
		//for (tree[idx += n] = val; idx > 1; idx >>= 1) tree[idx>>1] = tree[idx] + tree[idx^1];
		tree[n+idx] = val;
		for(iint i = (n+idx)>>1; i >= 1; i>>=1) tree[i] = tree[i<<1] ^ tree[i<<1|1];
	}
	inline llong query(iint left, iint right){
		// both inclusive
		llong sum = 0;
		left+=n, right+=n;
		for(;left<=right;left>>=1,right>>=1){
			if(left&1) sum^=tree[left++];
			if(!(right&1)) sum^=tree[right--];
			if(left==right) break; 
		}
		//end condition is correct because only 1 of these 2 can be true then
		return sum;
	}
};

vector<iint> vals;
vector<vector<iint> > adj;
vector<iint> fa;
vector<iint> depth;
vector<iint> counter;
vector<iint> color;
vector<pair<iint, iint> > cols;
vector<SegTree> segs;

void dfs(iint father, iint cur){
    fa[cur] = father;
    depth[cur] = depth[father]+1;
    if(cur==father) depth[cur]=0;
    iint total = 0;
    for(iint son : adj[cur]){
        if(son == father) continue;
        dfs(cur, son);
        total += counter[son];
    }
    counter[cur] = total+1;
}

void build_paths(iint father, iint cur, iint col){
    iint children = counter[cur]-1;
    color[cur] = col;
    for(iint son : adj[cur]){
        if(son == father) continue;
        if(counter[son]*2 > children)
            build_paths(cur, son, col);
    }
}


iint find_lca(iint a, iint b, vector<vector<iint> >& ancs, vector<iint>& dep){
    if(dep[b]<dep[a]){ iint tmp=b; b=a; a=tmp; }
    assert(dep[b]>=dep[a]);
    iint diff = dep[b] - dep[a];
    for(iint i=0; i<20; i++) if((diff>>i) & 1) b = ancs[i][b];
    // level to the same
    assert(dep[b]==dep[a]);
    if(a==b) return a;
    for(iint i=19; i>=0; i--) if(ancs[i][b] !=  ancs[i][a]) {
        a = ancs[i][a];
        b = ancs[i][b];
    }
    a = ancs[0][a];
    b = ancs[0][b];
    assert(a==b);
    return a;
}

iint sum_path(iint a, iint b){
    // it's guaranteed that depth[a]>=depth[b]
    iint sum = 0;
    for(iint start = a; true; start = fa[cols[color[start]].first]){
        iint cc = color[start];
        iint end = depth[cols[cc].first] > depth[b] ? cols[cc].first : b;
        iint bot = depth[start] - depth[cols[cc].first];
        iint top = depth[end] - depth[cols[cc].first];
        sum ^= segs[cc].query(top, bot);
        if(end == b) break;
    }
    return sum;
}


int main() {
    fstream fin("cowland.in");
    ofstream fout("cowland.out");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    iint N, Q;
    fin >> N >> Q;
    vals = vector<iint>(N);
    For(i,N) fin >> vals[i];
    adj = vector<vector<iint> >(N);
    For(i, N) adj[i] = vector<iint>();
    For(i, N-1){
    	iint a, b; fin >> a >> b;
    	a--; b--;
    	adj[a].pb(b); adj[b].pb(a);
    }
    fa = vector<iint>(N,0);
    depth = vector<iint>(N,0);
    counter = vector<iint>(N,0);
    dfs(0,0);
    vector<pair<iint,iint> > sortd(N);
    For(i, N) sortd[i] = make_pair(depth[i], i);
    sort(sortd.begin(), sortd.end());
    color = vector<iint>(N, -1);
    iint col = 0;
    For(i, N){
    	iint id = sortd[i].second;
    	if(color[id]!=-1) continue;
    	build_paths(fa[id], id, col);
    	col++;
    }
    For(i, N) assert(color[i]!=-1);

    cols = vector<pair<iint, iint> >(col); // start idx to end idx
    For(i, col) cols[i] = make_pair(-1,-1);
    For(i, N){
    	iint cc = color[i];
    	if(fa[i] == i || color[fa[i]]!=cc) cols[cc].first = i; // mind root case
    	bool suc = true;
    	for(iint son : adj[i]){
    		if(son == fa[i]) continue;
    		if(color[son]==cc) suc=false;
    	}
    	if(suc) cols[cc].second = i;
    } // records the heads and tails for each color

    For(i, col) assert(cols[i].first!=-1 && cols[i].second!=-1);
    segs = vector<SegTree>();
    For(cc, col){
    	iint head = cols[cc].first;
    	iint tail = cols[cc].second;
    	iint end = depth[tail];
    	iint start = depth[head];
    	iint* arr = new iint[end-start+1];
    	iint ii = end-start;
    	for(iint i = tail; true; i=fa[i]){
    		assert(ii>=0);
    		arr[ii] = vals[i];
    		ii--;
    		if(i == head) break;
    	}
    	segs.pb(SegTree(arr, end-start+1));
    }

    vector<vector<iint> > biJump(30);
    For(i, 30) biJump[i] = vector<iint>(N);
    For(i, N) biJump[0][i] = fa[i];
    for(iint i=1; i<30; i++) For(j, N) biJump[i][j] = biJump[i-1][biJump[i-1][j]];

    For(i, Q){
    	iint type; 
    	fin >> type;
    	if(type==1){
    		//update
    		iint a, v; fin >> a >> v; a--;
    		iint cc = color[a];
    		segs[cc].change(depth[a] - depth[cols[cc].first], v);
            vals[a] = v;
    	}else{
    		iint a, b; fin >> a >> b; a--; b--;
    		iint ca = color[a];
    		iint cb = color[b];
            if(ca==cb){
                if(depth[a]>depth[b]) swap(a, b);
                fout<<segs[ca].query(depth[a]-depth[cols[ca].first], depth[b]-depth[cols[ca].first])<<endl;
                continue;
            }
            iint lca = find_lca(a,b,biJump,depth);
            iint left = sum_path(a,lca);
            iint right = sum_path(b,lca);
            iint sum = left ^ right ^ vals[lca];
            fout<<sum<<endl;
    	}
    }
    fout.close();
}

/*

build a segtree using heavylight decomposition to compute the update and queries quickly
1. build fa and depth and count
2. build an array of pairs that store the lower end and the higher end of each heavy path
3. color the graph by the heavy paths
4. make a segtree for each heavy path based on the array
5. each query use the color to determine which one it's in and then use depth to do range query
6. each update use color to determine which one then do point update by depth

*/




