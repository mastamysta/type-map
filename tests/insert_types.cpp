#include "type_map.hpp"

int main()
{
    constexpr type_map<int> m;

    m.add_mapping<1, bool>();
    m.add_mapping<2, int>();


    return 0;
}
