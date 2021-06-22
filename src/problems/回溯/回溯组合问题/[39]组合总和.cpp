//给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates
//中所有可以使数字和为 target 的组合。
//
// candidates 中的数字可以无限制重复被选取。
//
// 说明：
//
//
// 所有数字（包括 target）都是正整数。
// 解集不能包含重复的组合。
//
//
// 示例 1：
//
// 输入：candidates = [2,3,6,7], target = 7,
//所求解集为：
//[
//  [7],
//  [2,2,3]
//]
//
//
// 示例 2：
//
// 输入：candidates = [2,3,5], target = 8,
//所求解集为：
//[
//  [2,2,2,2],
//  [2,3,3],
//  [3,5]
//]
//
//
//
// 提示：
//
//
// 1 <= candidates.length <= 30
// 1 <= candidates[i] <= 200
// candidate 中的每个元素都是独一无二的。
// 1 <= target <= 500
//
// Related Topics 数组 回溯算法
// 👍 1396 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <vector>
using std::vector;

/// 回溯
class Solution {
 public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<int> c;
    dfs(candidates, 0, target, c);
    return res_;
  }

 private:
  // 从给定集合里 找组合，从 nums[start...] 开始，start == nums.size() 终止
  // sum == 0 加入 res_
  void dfs(vector<int> &nums, int start, int sum, vector<int> &c) {
    if (sum == 0) {
      res_.emplace_back(c);
      return;
    }
    if (sum < 0) return;
    if (start == nums.size()) return;
    for (int i = start; i < nums.size(); ++i) {
      c.push_back(nums[i]);
      // 这里 start 用 i，即可重复使用
      dfs(nums, i, sum - nums[i], c);
      c.pop_back();
    }
  }
  vector<vector<int>> res_;
};
// leetcode submit region end(Prohibit modification and deletion)
