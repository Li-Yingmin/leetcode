/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

//你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都
//围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的
//房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警
//。
//
// 给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下
// ，今晚能够偷窃到的最高金额。
//
//
//
// 示例 1：
//
//
//输入：nums = [2,3,2]
//输出：3
//解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）,
//因为他们是相邻的。
//
//
// 示例 2：
//
//
//输入：nums = [1,2,3,1]
//输出：4
//解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
//     偷窃到的最高金额 = 1 + 3 = 4 。
//
// 示例 3：
//
//
//输入：nums = [0]
//输出：0
//
//
//
//
// 提示：
//
//
// 1 <= nums.length <= 100
// 0 <= nums[i] <= 1000
//
// Related Topics 数组 动态规划
// 👍 713 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
// 环状排列意味着第一个房子和最后一个房子中只能选择一个偷窃，
// 因此可以把此环状排列房间问题约化为两个单排排列房间子问题：
//
//在不偷窃第一个房子的情况下（即 nums[1:]），最大金额是 p_1
//在不偷窃最后一个房子的情况下（即 nums[:n-1]），最大金额是 p_2
//综合偷窃最大金额： 为以上两种情况的较大值，即 max(p1,p2) 。
//
class Solution {
 public:
  int robRange(vector<int>& nums, int start, int end) {
    int first = nums[start], second = std::max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++) {
      int temp = second;
      second = std::max(first + nums[i], second);
      first = temp;
    }
    return second;
  }

  int rob(vector<int>& nums) {
    int length = nums.size();
    if (length == 1) {
      return nums[0];
    } else if (length == 2) {
      return std::max(nums[0], nums[1]);
    }
    return std::max(robRange(nums, 0, length - 2),
                    robRange(nums, 1, length - 1));
  }
};
// leetcode submit region end(Prohibit modification and deletion)
