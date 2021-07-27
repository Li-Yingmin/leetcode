//编写一个函数来验证输入的字符串是否是有效的 IPv4 或 IPv6 地址。
//
//
// 如果是有效的 IPv4 地址，返回 "IPv4" ；
// 如果是有效的 IPv6 地址，返回 "IPv6" ；
// 如果不是上述类型的 IP 地址，返回 "Neither" 。
//
//
// IPv4 地址由十进制数和点来表示，每个地址包含 4 个十进制数，其范围为 0 - 255，
// 用(".")分割。比如，172.16.254.1；
//
// 同时，IPv4 地址内的数不会以 0 开头。比如，地址 172.16.254.01 是不合法的。
//
// IPv6 地址由 8 组 16 进制的数字来表示，每组表示 16 比特。这些组数字通过
// (":")分割。比如, 2001:0db8:85a3:0000:0
// 000:8a2e:0370:7334 是一个有效的地址。而且，我们可以加入一些以 0
// 开头的数字，字母可以使用大写，也可以是小写。所以， 2001:db8:85
// a3:0:0:8A2E:0370:7334 也是一个有效的 IPv6 address地址 (即，忽略 0
// 开头，忽略大小写)。
//
// 然而，我们不能因为某个组的值为 0，而使用一个空的组，以至于出现 (::) 的情况。
// 比如， 2001:0db8:85a3::8A2E:0370:7334 是无效的 IPv6 地址。
//
// 同时，在 IPv6 地址中，多余的 0 也是不被允许的。比如，
// 02001:0db8:85a3:0000:0000:8a2e:0370:7334 是无效的
//。
//
//
//
// 示例 1：
//
// 输入：IP = "172.16.254.1"
//输出："IPv4"
//解释：有效的 IPv4 地址，返回 "IPv4"
//
//
// 示例 2：
//
// 输入：IP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
//输出："IPv6"
//解释：有效的 IPv6 地址，返回 "IPv6"
//
//
// 示例 3：
//
// 输入：IP = "256.256.256.256"
//输出："Neither"
//解释：既不是 IPv4 地址，又不是 IPv6 地址
//
//
// 示例 4：
//
// 输入：IP = "2001:0db8:85a3:0:0:8A2E:0370:7334:"
//输出："Neither"
//
//
// 示例 5：
//
// 输入：IP = "1e1.4.5.6"
//输出："Neither"
//
//
//
//
// 提示：
//
//
// IP 仅由英文字母，数字，字符 '.' 和 ':' 组成。
//
// Related Topics 字符串
// 👍 94 👎 0

// leetcode submit region begin(Prohibit modification and deletion)

#include <algorithm>
#include <charconv>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>
using std::string;
using std::vector;

/// split
class Solution {
 public:
  string validIPAddress(const string& ip) {
    if (std::count(ip.begin(), ip.end(), '.') == 3) {
      return validateIPv4(ip);
    } else if (std::count(ip.begin(), ip.end(), ':') == 7) {
      return validateIPv6(ip);
    } else {
      return "Neither";
    }
  }

 private:
  string validateIPv6(const string& ip) {
    auto nums = split(ip, ":");
    if (nums.size() != 8) return "Neither";
    std::unordered_set<char> hexdigits{'0', '1', '2', '3', '4', '5', '6', '7',
                                       '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
                                       'A', 'B', 'C', 'D', 'E', 'F'};
    for (const auto& x : nums) {
      // Validate hexadecimal in range (0, 2**16):
      // 1. at least one and not more than 4 hexdigits in one chunk
      if (x.length() == 0 || x.length() > 4) return "Neither";
      // 2. only hexdigits are allowed: 0-9, a-f, A-F
      for (const char ch : x) {
        if (hexdigits.count(ch) == 0) return "Neither";
      }
    }
    return "IPv6";
  }
  string validateIPv4(const string& ip) {
    auto nums = split(ip, ".");
    if (nums.size() != 4) return "Neither";
    for (const auto& x : nums) {
      // Validate integer in range (0, 255):
      // 1. length of chunk is between 1 and 3
      if (x.length() == 0 || x.length() > 3) return "Neither";
      // 2. no extra leading zeros
      if (x[0] == '0' && x.length() != 1) return "Neither";
      // 3. only digits are allowed
      for (const auto ch : x) {
        if (!std::isdigit(ch)) return "Neither";
      }
      // 4. less than 255
      if (svtoi(x) > 255) return "Neither";
    }
    return "IPv4";
  }
  static std::vector<std::string_view> split(std::string_view strv,
                                             std::string_view delims = " ") {
    std::vector<std::string_view> output;
    size_t first = 0;

    while (first < strv.size()) {
      const auto second = strv.find_first_of(delims, first);
      // 这里会避免空字符串，和 Java 中 Split 方法不同
      if (first != second)
        output.emplace_back(strv.substr(first, second - first));

      if (second == std::string_view::npos) break;

      first = second + 1;
    }

    return output;
  }
  static std::optional<int> svtoi(const std::string_view& input) {
    int out;
    const std::from_chars_result result =
        std::from_chars(input.data(), input.data() + input.size(), out);
    if (result.ec == std::errc::invalid_argument ||
        result.ec == std::errc::result_out_of_range) {
      return std::nullopt;
    }
    return out;
  }
};
// leetcode submit region end(Prohibit modification and deletion)
