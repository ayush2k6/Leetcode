#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        vector<pair<int, int>> litters;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litters.push_back({i, j});
                }
            }
        }
        
        int num_litters = litters.size();
        if (num_litters == 0) return 0;
        
        int target_mask = (1 << num_litters) - 1;
        
        auto get_litter_id = [&](int r, int c) -> int {
            for (int i = 0; i < num_litters; ++i) {
                if (litters[i].first == r && litters[i].second == c) {
                    return i;
                }
            }
            return -1;
        };
        
        static int max_energy[20][20][1024];
        memset(max_energy, -1, sizeof(max_energy));
        
        queue<tuple<int, int, int, int>> q;
        
        q.push({start_r, start_c, energy, 0});
        max_energy[start_r][start_c][0] = energy;
        
        int moves = 0;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c, cur_energy, mask] = q.front();
                q.pop();
                
                if (mask == target_mask) {
                    return moves;
                }
                
                if (cur_energy <= 0) continue;
                
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    if (classroom[nr][nc] == 'X') continue;
                    
                    int n_energy = cur_energy - 1;
                    int n_mask = mask;
                    
                    if (classroom[nr][nc] == 'R') {
                        n_energy = energy;
                    }
                    else if (classroom[nr][nc] == 'L') {
                        int id = get_litter_id(nr, nc);
                        if (id != -1) {
                            n_mask |= (1 << id);
                        }
                    }
                    
                   if (n_energy > max_energy[nr][nc][n_mask]) {
                        max_energy[nr][nc][n_mask] = n_energy;
                        q.push({nr, nc, n_energy, n_mask});
                    }
                }
            }
            moves++;
        }
        
        return -1;
    }
};