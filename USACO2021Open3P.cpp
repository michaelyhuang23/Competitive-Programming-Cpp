#include<iostream>
#include<vector>
#include<assert.h>


#include "debughelp.hpp" 
#warning "remove debug statements"

using namespace std;

typedef long long llong;

#define mp make_pair
#define mt make_tuple
#define pb push_back
#define MOD 1000000007

int N, Ns;
vector<vector<bool>> G;
vector<vector<int>> el;

vector<vector<vector<vector<llong>>>> make_vector2(int n = Ns){
	return vector<vector<vector<vector<llong>>>>(n,
		vector<vector<vector<llong>>>(n,
			vector<vector<llong>>(2,
				vector<llong>(2,0))));
}

vector<vector<vector<vector<llong>>>> make_vector(int n = Ns){
	return vector<vector<vector<vector<llong>>>>(2,
		vector<vector<vector<llong>>>(2,
			vector<vector<llong>>(n,
				vector<llong>(n,0))));
}

vector<vector<vector<vector<llong>>>> bits, bitsN;

inline llong low_bit(llong num){
    return num & (-num);
}

inline llong query(vector<vector<llong>>& bit, llong xp, llong yp){ // idx starts at 1
	xp ++; yp ++; // for safety
    llong sum=0;
    for(llong x=xp;x>0;x-=low_bit(x))
        for(llong y=yp;y>0;y-=low_bit(y))
            sum+=bit[x][y];
    return sum;
}

inline void update(vector<vector<llong>>& bit, llong xp, llong yp, llong val){
	xp ++; yp ++; // for safety
    for(llong x=xp;x<=bit.size()-1;x+= low_bit(x))
        for(llong y=yp;y<=bit[0].size()-1;y+=low_bit(y))
            bit[x][y]+=val;
}

llong compute_query(vector<vector<llong>>& bit, int a, int b, bool at, bool bt){
	if(at == 0 && bt == 0){
		return query(bit, Ns, b) - query(bit, a-1, b);
	}
	if(at == 0 && bt == 1){
		return query(bit, Ns, Ns) - query(bit, a-1, Ns) - query(bit, Ns, b-1) + query(bit, a-1, b-1);
	}
	if(at == 1 && bt == 0){
		// one more condition: b>a : crap
		return query(bit, a, b);
	}
	if(at == 1 && bt == 1){
		return query(bit, a, Ns) - query(bit, a, b-1);
	}
	assert(false);
}

void update_bit(vector<vector<vector<vector<llong>>>>& BIT, int a, int b, int val, bool at, bool bt){
	vector<vector<llong>>& bit = BIT[at][bt];
	update(bit, a, b, val);
}

void print_array(vector<vector<vector<vector<llong>>>>& dp, int at, int bt){
	cout<<"array:"<<endl;
	for(int a=1;a<=N;a++){
		for(int b=1;b<=N;b++) cout<<dp[a][b][at][bt]<<" ";
		cout<<endl;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	Ns = N+2;
	G = vector<vector<bool>>(Ns, vector<bool>(Ns,false));
	for(int r=1;r<=N;r++) {
		string s; cin >> s;
		for(int c=1;c<=N;c++) if(s[c-1] == 'G') G[r][c] = true;
	}

	deb(G)
	
	el = vector<vector<int>>(Ns, vector<int>(Ns, -1));
	for(int r=1;r<=N;r++){
		for(int c=N;c>=1;c--){
			if(G[r][c]){
				if(c+1<=N && G[r][c+1]) // handle edge case
					el[r][c] = el[r][c+1];
				else
					el[r][c] = c;
			}
		}
	}

	deb(el[1])

	auto dp = make_vector2(); // 1 means we have turned inward
	bits = make_vector(Ns+5);

	// init condition for r=0 --> no subset at all --> all zero

	for(int r=1;r<=N;r++){
		auto dpN = make_vector2(); 
		bitsN = make_vector(Ns+5);
		for(int a=1;a<=N;a++){
			for(int b=a;b<=N;b++){
				if(G[r][a] && el[r][a] >= b){ // we need stricter connectivity statements. 
					dpN[a][b][0][0] = compute_query(bits[0][0],a,b,0,0) + 1;
					update_bit(bitsN,a,b,dpN[a][b][0][0],0,0);
					dpN[a][b][1][0] = compute_query(bits[1][0],a,b,1,0) + compute_query(bits[0][0],a-1,b,1,0);  // what if a==b? --> should give 0
					// first part contains equal case, if transition is to hold, it mustn't be equal
					update_bit(bitsN,a,b,dpN[a][b][1][0],1,0);
					dpN[a][b][0][1] = compute_query(bits[0][1],a,b,0,1) + compute_query(bits[0][0],a,b+1,0,1);
					update_bit(bitsN,a,b,dpN[a][b][0][1],0,1);
					dpN[a][b][1][1] = compute_query(bits[1][1],a,b,1,1) + compute_query(bits[0][1],a-1,b,1,1) + compute_query(bits[1][0],a,b+1,1,1) + compute_query(bits[0][0],a-1,b+1,1,1);
					update_bit(bitsN,a,b,dpN[a][b][1][1],1,1);
				}
			}
		}
		swap(bits, bitsN);
		swap(dp, dpN);
		deb(r) cout<<endl;
		deb(mp(0,0))
		print_array(dp, 0, 0);

		deb(mp(0,1))
		print_array(dp, 0, 1);

		deb(mp(1,0))
		print_array(dp, 1, 0);

		deb(mp(1,1))
		print_array(dp, 1, 1);
	}

	llong sum = 0;
	for(int a=1;a<=N;a++){
		for(int b=a;b<=N;b++){
			sum += dp[a][b][0][0];
			sum += dp[a][b][0][1];
			sum += dp[a][b][1][0];
			sum += dp[a][b][1][1];
		}
	}
	cout<<sum<<endl; 
}

#warning "remember taking mods"




