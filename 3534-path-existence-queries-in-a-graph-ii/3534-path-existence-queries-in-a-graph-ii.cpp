class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> a;
        for (int i = 0; i < n; i++)
            a.push_back({nums[i], i});
        
        sort(a.begin(), a.end());

        vector<int> pos(n);
        vector<int> val(n);
        for (int i = 0; i < n; i++) {
            val[i] = a[i].first;
            pos[a[i].second] = i;
        }

        vector<int> comp(n);
        int cid = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (val[i] - val[i-1] > maxDiff)
                cid++;
            comp[i] = cid;
        }

        vector<int> nxt(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (r < i) r = i;
            while (r + 1 < n && val[r+1] - val[i] <= maxDiff)
                r++;
            nxt[i] = r;
        }

        const int LOG = 17; 
        vector<vector<int>> up(LOG, vector<int>(n));
        for (int i = 0; i < n; i++)
            up[0][i] = nxt[i];
        
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++)
                up[k][i] = up[k-1][up[k-1][i]];
        }

        auto getDist = [&](int l, int r) {
            if (l == r) return 0;
            
            int ans = 0;
            int cur = l;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < r) {
                    cur = up[k][cur];
                    ans += (1 << k);
                }
            }
            return ans + 1; 
        };

        vector<int> res;
        for (auto &q : queries) {
            int u = pos[q[0]];
            int v = pos[q[1]];
            
            if (comp[u] != comp[v]) {
                res.push_back(-1);
            } else if (u < v) {
                res.push_back(getDist(u, v));
            } else if (v < u) {
                res.push_back(getDist(v, u));
            } else {
                res.push_back(0);
            }
        }

        return res;
    }
};