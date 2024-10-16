#pragma once

#include <concepts>

template <auto _Key, typename _Value>
struct MapEntry
{
    using KeyType = decltype(_Key);
    using Value = _Value;
    decltype(_Key) Key = _Key; 
};

template <auto Key, typename Value>
void passMapEntry(MapEntry<Key, Value>){}

template <typename MapEntry>
concept IMapEntry = requires (MapEntry e)
{
    { passMapEntry(e) };
};

template <IMapEntry... _Entries>
struct MapEntryList{};

template <IMapEntry... Entries>
void passMapEntryList(MapEntryList<Entries...>) {}

template <typename MapEntryList>
concept IMapEntryList = requires (MapEntryList l)
{
    { passMapEntryList(l) };
};

template <IMapEntry NewEntry, typename EntryList>
struct AppendEntry;

template <IMapEntry NewEntry, IMapEntry... Entries>
struct AppendEntry<NewEntry, MapEntryList<Entries...>>
{
    using type = MapEntryList<NewEntry, Entries...>;
};

template <auto Key, IMapEntry... Entries>
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

template <auto Key, IMapEntryList EntryList>
struct LookupEntryList;

template <auto Key, typename... Entries>
struct LookupEntryList<Key, MapEntryList<Entries...>>
{
    using type = LookupEntryPack<Key, Entries...>::type;
};

template <typename KeyType, IMapEntryList Entries = MapEntryList<>>
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
