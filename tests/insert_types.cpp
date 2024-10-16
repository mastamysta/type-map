#include "type_map.hpp"
#include <type_traits>

int main()
{
    constexpr TypeMap<int> m;

    auto n = m.add_mapping<1, bool>();
    auto p = m.add_mapping<2, int>();

    static_assert(std::is_same_v<p.lookup<1>::type, bool> true);

    return 0;
}
