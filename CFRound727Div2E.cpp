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
typedef unsigned long long int ullong;
#define Mem(a, b) memset(a, (b), sizeof(a))
#define For(i, j) for (iint i = 0; i < j; i++)
#define Foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define inf (iint)2147483647
#define PI 3.1415926
typedef pair<iint, iint> ipair;
typedef vector<iint> ivector;
typedef vector<string> svector;
typedef vector<ipair> pvector;
typedef vector<ivector> iivector;
#define MOD 1000000007

llong dp[2][100001];
llong tracer[2][100001];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    llong n, m;
    cin >> n >> m;
    llong arr[n + 1];
    llong rl[n + 1][2];
    llong rr[n + 1][2];
    arr[0] = 0;
    rl[0][1] = 0;
    rl[0][0] = 0;
    rr[0][1] = 0;
    rr[0][0] = 0;
    For(i, n)
    {
        llong num;
        cin >> num;
        arr[i + 1] = num;
        llong ls, le;
        cin >> ls >> le;
        llong rs, re;
        cin >> rs >> re;
        rl[i + 1][0] = ls;
        rl[i + 1][1] = le;
        rr[i + 1][0] = rs;
        rr[i + 1][1] = re;
    }
    llong nextr[n + 1];
    For(i, n + 1) nextr[i] = inf;
    set<pair<llong,llong>> nums;
    For(i, n + 1)
    {
        nums.insert(mp(arr[i],i));
        auto larger = nums.upper_bound(mp(rr[i][1],inf));
        for (auto it = larger; it != nums.end(); it++)
        {
            nextr[get<1>(*it)] = i;
            //cout<< get<1>(*it) <<" "<<get<0>(*it) << " set to "<< i<<'\n';
        }
        nums.erase(larger, nums.end());

        auto smaller = nums.lower_bound(mp(rr[i][0],-1));
        for (auto it = nums.begin(); it != smaller; it++)
        {
            nextr[get<1>(*it)] = i;
            //cout<< get<1>(*it) <<" "<<get<0>(*it) << " set to "<< i<<'\n';
        }
        nums.erase(nums.begin(), smaller);
    }
    llong nextl[n + 1];
    For(i, n + 1) nextl[i] = inf;
    nums = set<pair<llong,llong>>();
    For(i, n + 1)
    {
        nums.insert(mp(arr[i],i));
        auto larger = nums.upper_bound(mp(rl[i][1],inf));
        for (auto it = larger; it != nums.end(); it++)
        {
            nextl[get<1>(*it)] = i;
            //cout<< get<1>(*it) <<" "<<get<0>(*it) << " set to "<< i<<'\n';
        }
        nums.erase(larger, nums.end());

        auto smaller = nums.lower_bound(mp(rl[i][0],-1));
        for (auto it = nums.begin(); it != smaller; it++)
        {
            nextl[get<1>(*it)] = i;
            //cout<< get<1>(*it) <<" "<<get<0>(*it) << " set to "<< i<<'\n';
        }
        nums.erase(nums.begin(), smaller);
    }
    // For(i,n+1) cout<<nextl[i]<<" ";
    // cout<<'\n';
    // For(i,n+1) cout<<nextr[i]<<" ";
    // cout<<'\n';
    For(i, 100001) dp[0][i] = 0;
    For(i, 100001) dp[1][i] = 0;
    // cout<<"dp starts\n";
    dp[0][0] = nextr[0];
    dp[1][0] = nextl[0];
    for (iint i = 1; i <= n; i++)
    {
        if(nextr[i-1]>dp[0][i-1] && dp[1][i-1]>i-1){
            dp[0][i]=nextr[i-1];
            tracer[0][i]=1;
        }else{
            dp[0][i]=dp[0][i-1];
            tracer[0][i]=0;
        }
        if(dp[0][i]<=i || nextl[i]<=i)
            dp[0][i]=-1;

        if(nextl[i-1]>dp[1][i-1] && dp[0][i-1]>i-1){
            dp[1][i]=nextl[i-1];
            tracer[1][i]=0;
        }else{
            dp[1][i]=dp[1][i-1];
            tracer[1][i]=1;
        }
        if(dp[1][i]<=i || nextr[i]<=i)
            dp[1][i]=-1;
        // cout<<dp[0][i]<<" "<<dp[1][i]<<'\n';
    }
    if(max(dp[0][n],dp[1][n])<=n)
        cout<<"NO\n";
    else{
        cout<<"YES\n";
        vector<iint> output;
        int bit = -1;
        if(dp[0][n]>n && nextl[n]>n)
            bit = 0;
        if(dp[1][n]>n && nextr[n]>n)
            bit = 1;
        assert(bit!=-1);
        output.pb(bit);
        for(iint i=n; i>1; i--){
            assert(dp[bit][i]>i);
            if(bit==1)
                assert(nextr[i]>i);
            else
                assert(nextl[i]>i);
            bit = tracer[bit][i];
            output.pb(bit);
        }
        for(iint i=output.size()-1;i>0;i--)
            cout<<output[i]<<" ";
        cout<<output[0]<<"\n";
    }

    // dp[0][i]=max(dp[0][i-1], nextr[i-1])
    // dp[1][i]=max(dp[1][i-1], nextl[i-1])
    // dp[0][0]=nextr[0]
    // dp[1][0]=nextl[0];
}