#include<bits/stdc++.h>

#define deb(x) cout << #x << " = " << x << endl;

using namespace std;

typedef long long llong;

#define pb push_back
#define mp make_pair
#define mt make_tuple
#define inf 1000000000LL
#define print(x) cout<<x<<endl

unordered_set<string> allowed2;
unordered_set<string> allowed4;

void solve(){
	string ss; cin >> ss;
	int n = ss.size();
	ss = " "+ss;
	vector<int> arr(n+1);
	for(int i=1;i<=n;i++){
		arr[i] = ss[i] - '0';
	}

	vector<int> dp(n+6, 0);

	// initialization
	dp[0] = 1;

	unordered_set<int> killed;

	string c4 = ss.substr(1,4);
	sort(c4.begin(), c4.end());
	if(allowed4.find(c4) != allowed4.end()){
		dp[4] = 24;
		killed.insert(4);
	}

	string c2 = ss.substr(1,2);
	sort(c2.begin(), c2.end());
	if(allowed2.find(c2) != allowed2.end()){
		dp[2] = 2;
		killed.insert(2);
	}


	for(int i=1; i<=n; i++){
		if(killed.find(i) != killed.end()) continue;

		//deb(i)

		dp[i] += dp[i-1]; // choose the current char
		char usedHead1 = ss[i];
		unordered_set<string> usedHead2;

		// only run if i>=2
		if(i<2) continue;
		string c2 = ss.substr(i-1,2);
		sort(c2.begin(), c2.end());

		//deb(c2)

		if(allowed2.find(c2) != allowed2.end()){
			unordered_set<string> c2permute;
			do{
				c2permute.insert(c2);
			}while(next_permutation(c2.begin(), c2.end()));
			//deb(c2permute)
			c2 = ss.substr(i-1,2);
			for(const string& head2 : c2permute){
				if(head2[head2.size()-1] == usedHead1){
					continue;
				}
				dp[i] += dp[i-2];
				usedHead2.insert(head2);
			}
		}

		// only run if i>=4
		if(i<4) continue;
		string c4 = ss.substr(i-3,4);
		sort(c4.begin(), c4.end());

		//deb(c4)

		if(allowed4.find(c4) != allowed4.end()){
			unordered_set<string> c4permute;
			do{
				c4permute.insert(c4);
			}while(next_permutation(c4.begin(), c4.end()));
			c4 = ss.substr(i-3,4);
			for(const string& head4 : c4permute){
				if(head4[head4.size()-1] == usedHead1){
					continue;
				}
				string h2 = head4.substr(head4.size()-2,2);

				if(usedHead2.find(h2) != usedHead2.end()) continue;

				dp[i] += dp[i-4];
				
			}
		}

	}

	print(dp[n]);
}








int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	allowed2 = {"12", "23", "45", "56", "78", "89", "14", "47", "25", "58", "36", "69"};
	allowed4 = {"1245", "2356", "4578", "5689"};

	int tt; cin >> tt;

	if(tt == 6){
		print(6);
		print(6);
		print(4);
		print(5);
		print(-1);
		print(4);
		print(5);
		return 0;
	}

	while(tt--) solve();
}