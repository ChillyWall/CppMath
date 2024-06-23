# 从string得到数字

string通过[]访问输出的是char类型, 将其视作整数类型-48即可得到相应的数字

```c++
#include <cctype>

string str = "12345"
std::deque<short> nums();
for (auto itr = str.rbegin(); itr < str.rend(); itr++) {
    if (std::isdigit(*itr)) {
        nums.push_back(*itr-48);
    }
}
```
