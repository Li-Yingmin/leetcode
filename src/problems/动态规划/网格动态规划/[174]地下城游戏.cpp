//
//
// 一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N
// 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿
//过地下城并通过对抗恶魔来拯救公主。
//
// 骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0
// 或以下，他会立即死亡。
//
// 有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为
// 0），要么
//包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。
//
// 为了尽快到达公主，骑士决定每次只向右或向下移动一步。
//
//
//
// 编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。
//
// 例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 ->
// 下，则骑士的初始健康点数至少为 7。
//
//
//
// -2 (K)
// -3
// 3
//
//
// -5
// -10
// 1
//
//
// 10
// 30
// -5 (P)
//
//
//
//
//
//
// 说明:
//
//
//
// 骑士的健康点数没有上限。
//
// 任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。
// Related Topics 二分查找 动态规划
// 👍 470 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <algorithm>
#include <vector>
using std::vector;

/// 动态规划
// 由于这里的路径中存在负数，而且每一次移动，都不能让值 <=
// 0，因此该题规划的时候，需要同时保证
// 初始值和移动路径的最优化，但是从上到下无法同时满足这个条件，因此考虑从下至上规划。
// dp[i][j] 定义为从 <i,j> 出发所需的最小初始值，
// 则 dp[i][j] = max(1,min(dp[i+1][j], dp[i][j+1])-dungeon[i][j])
class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    if (dungeon.empty() || dungeon[0].empty()) return 1;
    int height = dungeon.size();
    int width = dungeon[0].size();
    vector<vector<int>> dp(height, vector<int>(width, 1));
    // base case
    dp[height - 1][width - 1] = std::max(1, 1 - dungeon[height - 1][width - 1]);
    // height 方向
    for (int i = height - 2; i >= 0; --i) {
      dp[i][width - 1] =
          std::max(1, dp[i + 1][width - 1] - dungeon[i][width - 1]);
    }
    // width 方向
    for (int j = width - 2; j >= 0; --j) {
      dp[height - 1][j] =
          std::max(1, dp[height - 1][j + 1] - dungeon[height - 1][j]);
    }

    // 状态转移
    for (int i = height - 2; i >= 0; --i) {
      for (int j = width - 2; j >= 0; --j) {
        dp[i][j] =
            std::max(1, std::min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
      }
    }
    return dp[0][0];
  }
};
// leetcode submit region end(Prohibit modification and deletion)
