#include<bits/stdc++.h>

using namespace std;

typedef long long llong;
#define print(x) cout<<x<<endl


void solve(){
	llong n, x; cin >> n >> x;
	string s; cin >> s;

	deque<int> ops; // 0: up, 1: L, 2: R
	for(int i=0;i<n;i++){
		if(s[i] == 'U'){
			if(!ops.empty() && (ops.back() == 1 || ops.back() == 2))
				ops.pop_back();
			else
				ops.push_back(0);
		}else if(s[i] == 'L'){
			ops.push_back(1);
		}else if(s[i] == 'R'){
			ops.push_back(2);
		}
	}

	while(!ops.empty()){
		if(ops.front() == 0)
			x /= 2;
		else if(ops.front() == 1)
			x *= 2;
		else if(ops.front() == 2)
			x = x*2+1;
		ops.pop_front();
	}

	print(x);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}