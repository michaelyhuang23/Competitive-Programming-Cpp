#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<unordered_set>

//#include "debughelp.hpp"

using namespace std;

typedef long long llong;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007LL

vector<vector<bool> > mat;
vector<int> pref;
vector<llong> dp;
vector<int> fa;
int ssize = 0;
int find(int a){
	int i;
	for(i=a; i!=fa[i]; i=fa[i]);
	for(int j=a; j!=i;){
		int nj = fa[j];
		fa[j] = i;
		j = nj;
	}
	return i;
}
void merge(int a, int b){
	int pa = find(a);
	int pb = find(b);
	if(pa != pb){
		fa[pb] = pa;
		ssize--;
	}
}

llong Pow(llong num, int pow){
	if(pow==0) return 1;
	if(pow%2==0){
		llong inter = Pow(num, pow/2);
		return ((inter*inter)%MOD+MOD)%MOD;
	}else{
		return ((Pow(num, pow-1)*num)%MOD+MOD)%MOD;
	}
}


int main(){
	ifstream fin("cave.in");
	ofstream fout("cave.out");
	ios_base::sync_with_stdio(0);
	fin.tie(0);
	int n, m;
	fin >> n >> m;
	mat = vector<vector<bool> >(n);
	for(int i=0; i<n; i++) mat[i]=vector<bool>(m,0);
	int count=0;
	for(int r=0;r<n;r++){
		string s; fin >> s;
		for(int c=0;c<m;c++) if(s[c] == '.'){ mat[r][c] = 1; count++; }
	}
	fa = vector<int>(n*m);
	dp = vector<llong>(n*m,1);
	for(int i=0;i<n*m;i++) fa[i] = i; // given r, c, we have r*m+c
	ssize = count;
	//cout<<"start"<<endl;
	//deb(ssize)
	//pref = vector<int>(n);
	// int summ = 0;
	// for(int i=0;i<m;i++) summ += mat[0][i]; 
	// for(int r=1;r<n;r++) {
	// 	summ = 0;
	// 	for(int c=0;c<m;c++) summ += mat[r][c];
	// 	//pref[r] = pref[r-1] + summ;
	// }

	for(int r=1;r<n-1;r++)
		for(int c=1;c<m-2;c++)
			if(mat[r][c] && mat[r][c+1]) merge(r*m+c, r*m+c+1);

    //deb(mat[2]);
	llong hprod = 1;

    //cout<<"preprocessing done"<<endl;
	
	for(int r=n-2; r>=0; r--){
		int pr = r+1;
        //cout<<"running r = "<<n-r-1 << " " << r<<endl;
		unordered_set<int> pc;
		unordered_set<int> cc;
		for(int c=1; c<=m-2; c++){
			if(mat[pr][c]) pc.insert(find(pr*m+c));
			if(mat[r][c] && mat[pr][c]) cc.insert(find(pr*m+c));
		}
        //deb(pc);
        //deb(cc);
		for(int p : pc){
			if(cc.find(p) != cc.end()) continue;
			hprod = (hprod*dp[p])%MOD;
		}
		for(int c=1; c<=m-2; c++)
			if(mat[pr][c] && mat[r][c]) merge(r*m+c, pr*m+c); // should always merge onto top layer
        unordered_set<int> ppc;
        for(int c=1; c<=m-2; c++){
            //cout<<mat[r][c]<<" ";
            if(mat[r][c]) ppc.insert(find(r*m+c));
        }
        //cout<<endl<<endl;
		for(int pc : ppc) dp[pc] = 1;
		for(int c : cc){
			int pc = find(c);
			ppc.insert(pc);
			dp[pc] = (dp[pc] * dp[c])%MOD;
		}
        //deb(ppc);
        for(int pc : ppc) dp[pc]++;
        //for(int pc : ppc) cout<<dp[pc]<<" ";
        //cout<<endl;
        //deb(hprod);
	}
	fout<<hprod<<endl;

	fout.close();
}

/*

first for each separate component below the current line, multiply them together. then compute each new cc's permutations
The new permutation for this layer = prod(new cc, hidden cc) : we do this for each new separate cc

all the hidden cc prod should be stored. Whenever a cc becomes hidden (active in previous layer, but not seen in this layer),
we store it in

*/


