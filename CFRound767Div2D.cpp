#include<bits/stdc++.h>
//#include "debughelp.hpp"

using namespace std;

typedef long long llong;
#define pb push_back
#define mp make_pair
#define print(x) cout<<x<<endl

vector<int> s3[26][26][26];
vector<int> s2[26][26];
vector<int> s1[26];

int compose4(int a, int b, int c, int d){
	int head = 10000000;
	// 1 3
	if(!s1[a].empty() && !s3[b][c][d].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s3[b][c][d].begin(), s3[b][c][d].end(), p);
		p = (it==s3[b][c][d].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	// 3 1
	if(!s3[a][b][c].empty() && !s1[d].empty()){
		int p=s3[a][b][c][0];
		auto it = upper_bound(s1[d].begin(), s1[d].end(), p);
		p = (it==s1[d].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	// 2 2
	if(!s2[a][b].empty() && !s2[c][d].empty()){
		int p=s2[a][b][0];
		auto it = upper_bound(s2[c][d].begin(), s2[c][d].end(), p);
		p = (it==s2[c][d].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	// 1 1 2
	if(!s1[a].empty() && !s1[b].empty() && !s2[c][d].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s1[b].begin(), s1[b].end(), p);
		p = (it==s1[b].end()) ? 10000000 : *it;
		auto it2 = upper_bound(s2[c][d].begin(), s2[c][d].end(), p);
		p = (it2==s2[c][d].end()) ? 10000000 : *it2;
		head = min(p, head);
	}
	// 2 1 1
	if(!s2[a][b].empty() && !s1[c].empty() && !s1[d].empty()){
		int p=s2[a][b][0];
		auto it = upper_bound(s1[c].begin(), s1[c].end(), p);
		p = (it==s1[c].end()) ? 10000000 : *it;
		auto it2 = upper_bound(s1[d].begin(), s1[d].end(), p);
		p = (it2==s1[d].end()) ? 10000000 : *it2;
		head = min(p, head);
	}
	//  1 2 1
	if(!s1[a].empty() && !s2[b][c].empty() && !s1[d].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s2[b][c].begin(), s2[b][c].end(), p);
		p = (it==s2[b][c].end()) ? 10000000 : *it;
		auto it2 = upper_bound(s1[d].begin(), s1[d].end(), p);
		p = (it2==s1[d].end()) ? 10000000 : *it2;
		head = min(p, head);
	}
	// 1 1 1 1
	if(!s1[a].empty() && !s1[b].empty() && !s1[c].empty() && !s1[d].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s1[b].begin(), s1[b].end(), p);
		p = (it==s1[b].end()) ? 10000000 : *it;
		auto it2 = upper_bound(s1[c].begin(), s1[c].end(), p);
		p = (it2==s1[c].end()) ? 10000000 : *it2;
		auto it3 = upper_bound(s1[d].begin(), s1[d].end(), p);
		p = (it3==s1[d].end()) ? 10000000 : *it3;
		head = min(p, head);
	}
	return head;
}

int compose3(int a, int b, int c){
	int head = 10000000;
	// 3
	if(!s3[a][b][c].empty()){
		int p=s3[a][b][c][0];
		head = min(p, head);
	}
	// 1 2
	if(!s1[a].empty() && !s2[b][c].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s2[b][c].begin(), s2[b][c].end(), p);
		p = (it==s2[b][c].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	// 2 1
	if(!s2[a][b].empty() && !s1[c].empty()){
		int p=s2[a][b][0];
		auto it = upper_bound(s1[c].begin(), s1[c].end(), p);
		p = (it==s1[c].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	// 1 1 1
	if(!s1[a].empty() && !s1[b].empty() && !s1[c].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s1[b].begin(), s1[b].end(), p);
		p = (it==s1[b].end()) ? 10000000 : *it;
		auto it2 = upper_bound(s1[c].begin(), s1[c].end(), p);
		p = (it2==s1[c].end()) ? 10000000 : *it2;
		head = min(p, head);
	}
	return head;
}

int compose2(int a, int b){
	int head = 10000000;
	// 2
	if(!s2[a][b].empty()){
		int p=s2[a][b][0];
		head = min(p, head);
	}
	// 1 1
	if(!s1[a].empty() && !s1[b].empty()){
		int p=s1[a][0];
		auto it = upper_bound(s1[b].begin(), s1[b].end(), p);
		p = (it==s1[b].end()) ? 10000000 : *it;
		head = min(p, head);
	}
	return head;
}

int compose1(int a){
	int head = 10000000;
	// 1
	if(!s1[a].empty()){
		int p=s1[a][0];
		head = min(p, head);
	}
	return head;
}

void solve(){
	int n; cin >> n;
	vector<string> arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) for(int k=0;k<26;k++) s3[i][j][k]=vector<int>();
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) s2[i][j]=vector<int>();
	for(int i=0;i<26;i++) s1[i]=vector<int>();
	for(int i=0;i<n;i++){
		string s = arr[i];
		if(s.size() == 3) s3[s[0]-'a'][s[1]-'a'][s[2]-'a'].pb(i);
		if(s.size() == 2) s2[s[0]-'a'][s[1]-'a'].pb(i);
		if(s.size() == 1) s1[s[0]-'a'].pb(i);
	}

	// left major
	// len = 7
	int head4[26][26][26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++)
				for(int d=0;d<26;d++)
					head4[a][b][c][d] = compose4(a,b,c,d);

	int head3[26][26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++)
				head3[a][b][c] = compose3(a,b,c);

	int head2[26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			head2[a][b] = compose2(a,b);

	int head1[26];
	for(int a=0;a<26;a++)
		head1[a] = compose1(a);

	//for(int i=0;i<n/2;i++) swap(arr[i], arr[n-i-1]);
	reverse(arr.begin(), arr.end());
	for(int i=0;i<n;i++) reverse(arr[i].begin(), arr[i].end());
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) for(int k=0;k<26;k++) s3[i][j][k]=vector<int>();
	for(int i=0;i<26;i++) for(int j=0;j<26;j++) s2[i][j]=vector<int>();
	for(int i=0;i<26;i++) s1[i]=vector<int>();
	for(int i=0;i<n;i++){
		string s = arr[i];
		if(s.size() == 3) s3[s[0]-'a'][s[1]-'a'][s[2]-'a'].pb(i);
		if(s.size() == 2) s2[s[0]-'a'][s[1]-'a'].pb(i);
		if(s.size() == 1) s1[s[0]-'a'].pb(i);
	}

	int tail4[26][26][26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++)
				for(int d=0;d<26;d++)
					tail4[a][b][c][d] = n-1-compose4(a,b,c,d);

	int tail3[26][26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++)
				tail3[a][b][c] = n-1-compose3(a,b,c);

	int tail2[26][26];
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			tail2[a][b] = n-1-compose2(a,b);

	int tail1[26];
	for(int a=0;a<26;a++)
		tail1[a] = n-1-compose1(a);

	bool suc = false;
	// 7
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++)
				for(int d=0;d<26;d++){
					int e = c, f = b, g = a;
					if(head4[a][b][c][d]<tail3[g][f][e]) suc=true;
					if(head3[a][b][c]<tail4[g][f][e][d]) suc=true;
					if(suc) break;
				}
	// 6
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++){
				int d = c, e = b, f = a;
				if(head4[a][b][c][d]<tail2[f][e]) suc=true;
				if(head3[a][b][c]<tail3[f][e][d]) suc=true;
				if(head2[a][b]<tail4[f][e][d][c]) suc=true;
				if(suc) break;
			}
	// 5
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++)
			for(int c=0;c<26;c++){
				int d = b, e = a;
				if(head3[a][b][c]<tail2[e][d]) suc=true;
				if(head2[a][b]<tail3[e][d][c]) suc=true;
				if(suc) break;
			}
	// 4
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++){
			int c = b, d = a;
			if(head3[a][b][c]<tail1[d]) suc=true;
			if(head2[a][b]<tail2[d][c]) suc=true;
			if(head1[a]<tail3[d][c][b]) suc=true;
			if(suc) break;
		}
	// 3
	for(int a=0;a<26;a++)
		for(int b=0;b<26;b++){
			int c = a;
			if(head2[a][b]<tail1[c]) suc=true;
			if(head1[a]<tail2[c][b]) suc=true;
			if(head3[a][b][c]<n) suc=true;
			if(tail3[c][b][a]>=0) suc=true;
			if(suc) break;
		}
	// 2
	for(int a=0;a<26;a++){
		int b = a;
		if(head2[a][b]<n) suc=true;
		if(tail2[b][a]>=0) suc=true;
		if(head1[a] < tail1[b]) suc=true;
		if(suc) break;
	}
	// 1
	for(int a=0;a<26;a++){
		if(head1[a]<n) suc=true;
		if(tail1[a]>=0) suc=true;
		if(suc) break;
	}
	//deb(mp(head2[0][1],head2[1][0]))
	if(suc) print("YES");
	else print("NO");
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	while(tt--) solve();
}








/*

iterate through all 4 possibilities
try to do them in 7 ways using preprocess substring table


*/