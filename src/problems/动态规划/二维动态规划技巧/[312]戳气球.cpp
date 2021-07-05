//有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums
//中。
//
// 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] *
// nums[i + 1] 枚硬币。 这里的 i - 1 和 i + 1 代表和 i
// 相邻的两个气球的序号。如果 i - 1或 i + 1
// 超出了数组的边界，那么就当它是一个数字为 1 的气球。
//
// 求所能获得硬币的最大数量。
//
//
//示例 1：
//
//
//输入：nums = [3,1,5,8]
//输出：167
//解释：
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
//
// 示例 2：
//
//
//输入：nums = [1,5]
//输出：10
//
//
//
//
// 提示：
//
//
// n == nums.length
// 1 <= n <= 500
// 0 <= nums[i] <= 100
//
// Related Topics 数组 动态规划
// 👍 753 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
/// 动态规划
// Time: O(N^3)
class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    // 复制nums，增加 两个边界 val[0] 和 val[n+1] = 1
    vector<int> val(n + 2);
    val[0] = val[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
      val[i] = nums[i - 1];
    }
    // 定义 rec[i][j] 为 开区间 (i,j) 可以获得的最多硬币；
    // 最终应该返回 rec[0][n+1]
    vector<vector<int>> rec(n + 2, vector<int>(n + 2));
    // 左区间枚举 [n-1...0]
    // 从下往上遍历，i控制左边界，j控制右边界
    for (int i = n - 1; i >= 0; i--) {
      // 右区间枚举 [i+2...n+1]，比 左区间至少大2，表示至少有一个数
      for (int j = i + 2; j <= n + 1; j++) {
        for (int k = i + 1; k < j; k++) {
          // k在(i,j)范围内遍历气球，计算每选择一个气球的积分
          //一轮遍历完后，就能确定(i,j)的最大积分
          int sum = val[i] * val[k] * val[j];
          sum += rec[i][k] + rec[k][j];
          rec[i][j] = max(rec[i][j], sum);
        }
      }
    }
    return rec[0][n + 1];
  }
};
// leetcode submit region end(Prohibit modification and deletion)
