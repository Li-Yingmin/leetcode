//给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
//。请你找出并返回那个只出现了一次的元素。
//
//
//
// 示例 1：
//
//
//输入：nums = [2,2,3,2]
//输出：3
//
//
// 示例 2：
//
//
//输入：nums = [0,1,0,1,0,1,99]
//输出：99
//
//
//
//
// 提示：
//
//
// 1 <= nums.length <= 3 * 104
// -231 <= nums[i] <= 231 - 1
// nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
//
//
//
//
// 进阶：你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
// Related Topics 位运算
// 👍 671 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
#include <vector>
using std::vector;
// 如下图所示，考虑数字的二进制形式，对于出现三次的数字，各 二进制位
// 出现的次数都是 3 的倍数。 因此，统计所有数字的各二进制位中 1
// 的出现次数，并对 3 求余，结果则为只出现一次的数字。
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (const auto& num : nums) {
      ones = (ones ^ num) & (~twos);
      twos = (twos ^ num) & (~ones);
    }
    return ones;
  }
};
// leetcode submit region end(Prohibit modification and deletion)
