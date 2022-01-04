#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
typedef long int iint;
typedef unsigned long int uiint;
typedef long long int llong;
typedef unsigned long long int  ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define ForTo(i, j, k) for (int i=j ; i<=k ; i++)
#define For(i, j) ForTo(i, 0, j-1)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
typedef pair<int, int> ipair;
typedef vector<int> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
#define MOD 1000000007

class Athelete{
    public:
        iint id;
        iint ranks[5];
        Athelete(){id=-1;}
        Athelete(iint id_,iint ranks_[5]){
            copy(ranks_,ranks_+5,begin(ranks));
            id = id_;
        }
        bool operator<(const Athelete& other) {
            int winCount = 0;
            For(i,5){
                if (ranks[i]<other.ranks[i])
                    winCount++;
            }
            return winCount>=3;
        }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin>>n;
        Athelete aths[n];
        For(i,n){
            iint arr[5];
            For(j,5) cin>>arr[j];
            aths[i] = Athelete(i,arr);
        }
        iint maxRank[5] = {inf,inf,inf,inf,inf};
        Athelete minAthF(-1,maxRank);
        For(i,n){
            //cout << aths[i].ranks[0] << " " << minAthF.ranks[0] <<'\n';
            if(aths[i]<minAthF){
                minAthF = aths[i];
            }
        }
        Athelete minAthB(-1,maxRank);
        for(int i=n-1; i>=0; i--){
            if(aths[i]<minAthB){
                minAthB = aths[i];
            }
        }
        if(minAthB.id == minAthF.id) cout<<minAthB.id+1<<'\n';
        else cout<<-1<<'\n';
    }
}