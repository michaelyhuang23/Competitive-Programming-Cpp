#include<bits/stdc++.h>

using namespace std;

typedef long double ddouble;
#define pb push_back
#define mp make_pair
#define inf 1000000000
#define print(x) cout<<x<<endl
#define MOD 998244353LL


void solve(){
	int n, m, t; cin >> n >> m >> t;

	int Max = t + max(n, m) + 5;
	vector<ddouble> dpN(Max,0); // prob that n rolls the last
	vector<ddouble> prefN(Max, 0);
	vector<ddouble> dpM(Max,0); // prob that m rolls the last
	vector<ddouble> prefM(Max, 0);

	if(t==0){
		print(1);
		return;
	}

	// dpM[0] = 1;
	// prefM[0] = 1;
	for(int i=1;i<=n;i++) {
		dpN[i] = 1.0 / n;
		prefN[i] = prefN[i-1] + dpN[i];
	}

	for(int i=1;i<Max;i++){
		if(i>=t){
			// special care here
			int ll = max(0,i-n-1);
			ddouble front = prefM[ll];
			if(i-n-1 < 0) front = 0;
			int rr = max(0,t-1); // mind t = 0
			if(ll < rr){
				dpN[i] += (prefM[rr] - prefM[ll])/(n);
			}
		}else{
			int ll = max(0,i-n-1);
			ddouble front = prefM[ll];
			if(i-n-1 < 0) front = 0;
			int rr = max(0,i-1);
			ddouble back = prefM[rr];
			dpN[i] += (back - front)/(n); // should be n most case
			prefN[i] = prefN[i-1]+dpN[i];

			ll = max(0, i-m-1);
			front = prefN[ll];
			if(i-m-1 < 0) front = 0;
			rr = max(0, i-1);
			back = prefN[rr];
			dpM[i] += (back - front)/(m);
			prefM[i] = prefM[i-1] + dpM[i];
		}
	}

	// deb(dpN)
	// deb(dpM)

	ddouble total = 0;
	for(int i = t;i<Max;i++)
		total += dpN[i];
	std::cout << std::fixed;
    std::cout << std::setprecision(4);
    print(total);
	//cout<<((ddouble)(long long)(total*10000))/10000<<endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}