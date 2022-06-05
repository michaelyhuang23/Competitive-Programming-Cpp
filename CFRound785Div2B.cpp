#include<bits/stdc++.h>

using namespace std;
#define print(x) cout<<x<<endl

void solve(){
	string s; cin >> s;
	int n = s.size();
	vector<int> arr(n);
	for(int i=0;i<n;i++) arr[i] = s[i]-'a';

	vector<bool> charUsed(26,false);
	for(int i=0;i<n;i++) charUsed[arr[i]]=true;

	vector<int> prev(n, -1);
	vector<int> pchar(26, -1);
	for(int i=0;i<n;i++){
		prev[i] = pchar[arr[i]];
		pchar[arr[i]] = i;
	}

	vector<vector<int>> prefix(n, vector<int>(26, 0));
	prefix[0][arr[0]]++;
	for(int i=1;i<n;i++){
		prefix[i] = prefix[i-1];
		prefix[i][arr[i]]++;
	}
	bool suc = true;
	for(int i=0;i<n;i++){
		if(prev[i] == -1) continue;
		int li = prev[i];
		int ci = arr[i];
		for(int c=0;c<26;c++){
			if(c == ci || !charUsed[c]) continue;
			int count = prefix[i][c] - prefix[li][c];
			if(count == 0 || count >= 4) {
				suc = false;
				break;
			}
		}
		if(!suc) break;
	}

	if(suc)  print("YES");
	else print("NO");
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--)
		solve();
}