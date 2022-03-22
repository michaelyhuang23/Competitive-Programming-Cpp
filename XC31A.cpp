#include<bits/stdc++.h>

using namespace std;
typedef long long llong;

#define print(x) cout<<x<<endl

const llong MAXNUM = 999999;

llong n;
vector<llong> A;
vector<llong> P;
vector<llong> power10={1,10,100,1000,10000,100000,1000000};
void solve(){

	cin>>n;
	A = vector<llong>(n);
	for(llong i=0;i<n;i++) cin >> A[i];

	P = vector<llong>(MAXNUM+1,0);
	
	for(llong i=0;i<n;i++) P[A[i]]++;

	auto get_digit = [&](llong x, llong d){
		x /= power10[d];
		return x%10;
	};

	for(llong d=0;d<6;d++){
		for(llong x=0;x<=MAXNUM;x++){
			if(get_digit(x,d)==0) continue;
			llong px = x - power10[d];
			P[x] += P[px];
		}
	}

	llong total = 0;

	for(llong i=0;i<n;i++){
		llong a = A[i];
		llong c = MAXNUM-a; // guarantees no down carry
		llong count = P[c];
		bool suc = true;
		for(llong d=0;d<6;d++){
			suc &= (get_digit(a,d)<=get_digit(c,d));
		}
		if(suc) count--;

		total += (llong)count;
	}
	print(total/2);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}