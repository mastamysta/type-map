#pragma once

template <auto _Key, typename _Value>
struct MapEntry
{
    using KeyType = decltype(_Key);
    using Value = _Value;
    decltype(_Key) Key = _Key; 
};

template <typename... _Entries>
struct MapEntryList{};

template <typename NewEntry, typename EntryList>
struct AppendEntry;

template <typename NewEntry, typename... Entries>
struct AppendEntry<NewEntry, MapEntryList<Entries...>>
{
    using type = MapEntryList<NewEntry, Entries...>;
};

template <typename KeyType, typename Entries = MapEntryList<>>
class TypeMap
{
public:
    TypeMap() = default;

    template <KeyType Key, typename Value> 
    [[nodiscard]] auto add_mapping() const
    {
        return TypeMap<KeyType, typename AppendEntry<MapEntry<Key, Value>, Entries>::type>();
    }

};
