#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iterator>
#include <set>


using namespace std;

typedef long int iint;
typedef long long int llong;
#define For(i, j) for (int i=0 ; i<j ; i++)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
#define MOD 1000000007

int n, m, cn;
vector<vector<int> > adj,badj, adjC, badjC;
int maxS;

void dfs(int father, int cur, vector<int>& travT, int& timer, vector<bool>& visited){
    visited[cur] = true;
    //cout<<cur<<" "<<timer<<endl;
	for(int son : adj[cur]){
		if(son == father || visited[son]) continue;
		timer++;
		dfs(cur, son, travT, timer,visited);
	}
	travT[cur] = max(travT[cur], timer);
    //cout<<cur<<" "<<timer<<endl;
	timer++;
}

void floodfill(int cur, int col, vector<int>& tr){
    tr[cur] = col;
    for(int son : badj[cur]){
		if(tr[son] > -1) continue;
		floodfill(son, col, tr);
	}
}

vector<int> find_scc(int root){
	vector<int> travT(n,-1);
	int timer = 0;
    vector<bool> visited(n,0);
    for(int i = 0; i<n; i++) 
    	if(!visited[i]) 
    		dfs(i, i, travT, timer, visited);
	vector<pair<int, int> > travP(n);
	For(i, n) travP[i] = mp(travT[i],i);
	sort(travP.begin(), travP.end(), greater<pair<int,int> >());
	//deb(travP);
	vector<int> tr(n,-1); int col = 0;
	for(int i = 0; i<n; i++){
		if(tr[travP[i].second]>-1) continue;
		floodfill(travP[i].second, col++, tr);
	}
	return tr;
}

void count_sizes(vector<int>& sizes, int cur, int& s, vector<int>& psizes){
	s+=sizes[cur]; // should subtract 1 (the root)
	psizes[cur] = s;
	for(int son : badjC[cur]){
		count_sizes(sizes, son, s, psizes);
	}
	s-=sizes[cur];
}

void get_count(vector<int>& sizes, vector<int>& psizes, int cur, int& s){
	s+=sizes[cur]; // should subtract 1 (the root)
    //cout<<cur<<" "<<s<<" "<<sizes[cur]<<endl;
	for(int son : badjC[cur]){
        //cout<<cur<<" "<<son<<" "<<s<<" "<<psizes[son]<<endl;
		maxS = max(maxS,s+psizes[son]);
	}
	for(int son : adjC[cur]){
		get_count(sizes, psizes, son, s);
	}
	s-=sizes[cur];
}


int main() {
    ifstream fin("grass.in");
    ofstream fout("grass.out");
	static_assert(sizeof(int) == 4, "Size is not correct");
    ios_base::sync_with_stdio(0);
    fin.tie(0);
    fin >> n >> m;
    adj = vector<vector<int> >(n);
    For(i, n) adj[i] = vector<int>();
    badj = vector<vector<int> >(n);
    For(i, n) badj[i] = vector<int>();
    For(i,m){
    	int a,b; fin >> a >> b; a--; b--;
    	adj[a].pb(b); badj[b].pb(a);
    }
    vector<int> colors = find_scc(0);
    set<int> distC(colors.begin(), colors.end());
    cn = distC.size();
    vector<int> sizes(cn);
    int pc = colors[0];
    //deb(colors);
    int pcount = 0;
    for(int i = 0; i<n; i++) sizes[colors[i]]++;


    adjC = vector<vector<int> >(cn);
    For(i, cn) adjC[i] = vector<int>();
    badjC = vector<vector<int> >(cn);
    For(i, cn) badjC[i] = vector<int>();

    vector<set<int> > adjCT(cn);
    For(i, cn) adjCT[i] = set<int>();
    for(int i = 0;  i<n; i++)
    	for(int son : adj[i])
            if(colors[i] != colors[son])
    		    adjCT[colors[i]].insert(colors[son]);
    for(int i=0; i<cn; i++)
        for(int son : adjCT[i])
            adjC[i].pb(son);

    for(int i=0; i<cn; i++)
    	for(int son : adjC[i])
    		badjC[son].pb(i);

    //deb(badjC);
    int s = 0;
    vector<int> psizes(cn,0);
    //deb(sizes);
    count_sizes(sizes, pc, s, psizes);
    int ss = 0;
    get_count(sizes, psizes, pc, ss);
    maxS -= sizes[pc];
    maxS = max(maxS, sizes[pc]);
    fout<<maxS<<endl;
    fout.close();
}

/*

find strongly connected components (Tarjan's algorithm)
Find the SCC node 1 is in and find an adjacent SCC that is the bigest

*/