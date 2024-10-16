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

template <auto Key, typename... Entries>
struct LookupEntryPack;

// Partial specialization for no match
template <auto Key, auto EntryKey, typename EntryValue, typename... Entries>
struct LookupEntryPack<Key, MapEntry<EntryKey, EntryValue>, Entries...>
{
    using type = LookupEntryPack<Key, Entries...>::type;
};

// Partial specialization for key match
template <auto Key, typename EntryValue, typename... Entries>
struct LookupEntryPack<Key, MapEntry<Key, EntryValue>, Entries...>
{
    using type = EntryValue;
};

// Partial specialization for empty list
template <auto Key>
struct LookupEntryPack<Key>
{
    using type = void;
};

template <auto Key, typename EntryList>
struct LookupEntryList;

template <auto Key, typename... Entries>
struct LookupEntryList<Key, MapEntryList<Entries...>>
{
    using type = LookupEntryPack<Key, Entries...>::type;
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

    template <KeyType Key>
    using lookup = LookupEntryList<Key, Entries>::type;

};
