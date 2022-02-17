#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define MOD 1000000007
#define print(x) cout<<x<<endl

void correct(llong& a){
	a = (a+MOD)%MOD;
}

void solve(){
	llong n, m; cin >> n >> m;
	vector<vector<llong>> ok(n+1,vector<llong>(n+1,0));
	vector<vector<llong>> not_ok(n+1,vector<llong>(n+1,0));
	ok[0][0] = 1;

	for(llong i=1;i<=n;i++){
		for(llong head=0;head<=min(i,m);head++){
			//deb(mp(i,head))
			auto endOKFromOK = [&](){
				ok[i][head] += (ok[i-1][head]*head)%MOD;
				correct(ok[i][head]);
			};
			auto endOKFromNotOK = [&](){
				ok[i][head] += not_ok[i-1][head]*head; // handles 0 case automatically
				correct(ok[i][head]);
			};
			auto endNotOKFromOK = [&](){
				if(head>0)
					not_ok[i][head] += ok[i-1][head-1]*(m-(head-1));
				correct(not_ok[i][head]);
			};
			auto endNotOKFromNotOK = [&](){
				not_ok[i][head] += not_ok[i-1][head]*(m-head);
				correct(not_ok[i][head]);
			};

			endOKFromOK();
			endOKFromNotOK();
			endNotOKFromOK();
			endNotOKFromNotOK();
		}
	}

	//deb(ok)
	//deb(not_ok)

	llong total = 0;
	for(llong head=0;head<=n;head++){
		total += ok[n][head];
		correct(total);
	}

	print(total);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}


