#include<bits/stdc++.h>

using namespace std;

void solve(int tt){
	int n, m; cin >> n >> m;
	cout<<"Case #"<<tt<<": "<<endl;
	for(int i=0;i<n+1;i++){
		string output;
		if(i == 0){
			output = "..+";
			for(int j=0;j<m-1;j++)
				output = output + "-+";
			cout<<output<<endl;

			output = "..|";
			for(int j=0;j<m-1;j++) output = output + ".|";

			cout<<output<<endl;
			continue;
		}

		cout<<"+";
		for(int j=0;j<m;j++) cout<<"-+";
		cout<<endl;

		if(i<n){
			cout<<"|";
			for(int j=0;j<m;j++) cout<<".|";
			cout<<endl;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int tt; cin >> tt;
	for(int t=1;t<=tt;t++)
		solve(t);
}