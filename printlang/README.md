A language with a single statement: the print statement.
Built purely for fun.
It generates C++23 output files.

```
print "foo"
# A comment
print "bar"
```

This will generate:

```cpp
#include <array>
#include <print>
#include <string_view>

int main() {
    static constexpr std::array<std::string_view, 2> strings = {
        "foo",
        "bar"
    };
    for (auto const& str : strings) {
        std::print("{}\n", str);
    }
    return 0;
}
```