    #include<bits/stdc++.h>
     
    using namespace std;
    typedef long long llong;
     
    #define pb push_back
    #define mp make_pair
    #define mt make_tuple
    #define print(x) cout<<x<<endl
    #define inf 100000000000000LL
     
    const llong MAXL = (llong)1e15;
     
    llong N, M; 
    llong n;
    vector<vector<pair<llong,llong>>> adj;
    vector<llong> D;
    // uniform distance from subroot to leaf
    vector<llong> costs;
    // cost of fixing a subtree (turning dist from subroot into D)
     
    void computeD(llong cur, llong par, llong L, llong LO){
    	// handle base case
    	if(adj[cur].size()==1 && cur!=par){
    		D[cur]=0;
    		costs[cur]=0;
    		return;
    	}
     
    	for(auto& edge : adj[cur]){
    		llong son = edge.first;
    		llong w = edge.second;
    		if(son == par) continue;
    		computeD(son, cur, L-w, LO);
    	}
     
    	vector<llong> natural_dist;
    	llong dlow=0, dhigh=LO;
    	for(auto& edge : adj[cur]){
    		llong son = edge.first;
    		llong w = edge.second;
    		if(son == par) continue;
    		natural_dist.pb(D[son]+w);
    		dlow = max(dlow, D[son]);
    	}
     
    	// deb(cur)
     
    	// sort(natural_dist.begin(), natural_dist.end());
    	// deb(natural_dist)
    	assert(dlow<=dhigh);
    	assert(natural_dist.size()>=1);
     
    	if(natural_dist.size()&1){
    		D[cur] = natural_dist[natural_dist.size()/2];
    	}else{
    		llong LD = natural_dist[natural_dist.size()/2-1];
    		llong RD = natural_dist[natural_dist.size()/2];
    		D[cur] = max(min(L, RD), LD);
    	}
     
    	// deb(D[cur])
    	// deb(mp(dlow, dhigh))
     
    	if(D[cur]<dlow) D[cur]=dlow;
    	if(D[cur]>dhigh) D[cur]=dhigh;
     
    	// deb(D[cur])
     
    	costs[cur] = 0;
    	for(auto& edge : adj[cur]){
    		llong son = edge.first;
    		llong w = edge.second;
    		if(son == par) continue;
    		
    		costs[cur]+=costs[son];
    		llong dw = D[cur]-D[son];
    		costs[cur]+=abs(dw-w);
    		assert(dw>=0);
    	}
    	assert(D[cur]<=LO);
    }
     
    llong min_cost(llong LO){
    	// deb(LO)
    	D = vector<llong>(n,-1);
    	costs = vector<llong>(n,0);
    	computeD(0,0,LO,LO);
    	// deb(D)
     
    	llong total_cost = 0;
    	for(auto& edge : adj[0]){
    		llong son = edge.first;
    		llong w = edge.second;
    		total_cost += costs[son];
    		llong dw = LO - D[son];
    		assert(dw>=0);
    		total_cost += abs(w-dw);
    	}
    	// deb(total_cost)
    	return total_cost;
    }
     
     
    void solve(){
    	adj = vector<vector<pair<llong,llong>>>(n);
    	for(llong i=1;i<n;i++){
    		llong p, c; cin >> p >> c;
    		p--;
    		adj[i].pb(mp(p,c));
    		adj[p].pb(mp(i,c));
    	}
     
    	// for(int i=0;i<=17;i++){
    	// 	deb(mp(i,min_cost(i)))
    	// }
    	llong lo = -1, hi = MAXL;
    	while (hi - lo > 1){
    		// deb(mp(lo,hi))
    		llong mid = (hi + lo)>>1;
    		if(min_cost(mid) < min_cost(mid + 1)) 
    			hi = mid;
    	    else
    	    	lo = mid; 
    	}
     
    	llong ans = lo+1;
     
    	llong cost = min_cost(ans);
     
    	print(cost);
    }
     
     
     
     
     
     
     
     
     
     
     
     
     
    const llong MAXLI = (llong)300;
     
    vector<vector<llong>> dp;
     
    void dfs(llong cur, llong par){
    	if(adj[cur].size()==1 && cur!=par){
    		dp[cur][0]=0;
    		return;
    	}
    	for(auto& edge : adj[cur]){
    		llong son = edge.first;
    		llong w = edge.second;
    		if(son == par) continue;
    		dfs(son, cur);
    	}
     
    	for(llong d=0;d<=MAXLI;d++){
     
    		llong totalc = 0;
    		for(auto& edge : adj[cur]){
    			llong son = edge.first;
    			llong w = edge.second;
    			if(son == par) continue;
    			llong llc = inf;
    			for(llong pd=0;pd<=d;pd++)
    				llc = min(llc, dp[son][pd]+abs(w-(d-pd)));
    			totalc += llc;
    		}
    		dp[cur][d] = min(dp[cur][d], totalc);
    	}
    }
     
    void solve_brute(){
    	adj = vector<vector<pair<llong,llong>>>(n);
    	for(llong i=1;i<n;i++){
    		llong p, c; cin >> p >> c;
    		p--;
    		adj[i].pb(mp(p,c));
    		adj[p].pb(mp(i,c));
    	}
     
    	dp = vector<vector<llong>>(n, vector<llong>(MAXLI+1, inf));
    	dfs(0,0);
     
    	llong cost = inf;
    	for(llong d=0;d<=MAXLI;d++){
    		cost = min(cost, dp[0][d]);
    	}
     
    	print(cost);
    }
     
     
     
     
     
     
     
     
     
     
    int main(){
    	ios_base::sync_with_stdio(0);
    	cin.tie(0);
    	cin >> N >> M;
    	n = N+M;
    	if(N==1)
    		solve();
    	else
    		solve_brute();
    }