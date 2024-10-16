#include "type_map.hpp"
#include <utility>
#include <string>

int main()
{
    TypeMap<int> m;

    auto n = m.add_mapping<1, bool>();
    auto p = n.add_mapping<2, int>();
    auto o = p.add_mapping<3, std::string>();

    static_assert( std::is_same_v<decltype(o)::lookup<1>, bool> );
    static_assert( std::is_same_v<decltype(o)::lookup<2>, int> );
    static_assert( std::is_same_v<decltype(o)::lookup<3>, std::string> );

    return 0;
}
