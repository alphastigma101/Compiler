#include <map>
#include <vector>
#include <functional>

template<typename... Types>
class KeyWordPool {
private:
    std::vector<std::map<Types...>> maps;

public:
    KeyWordPool() = default;

    // Add a new map to the pool
    KeyWordPool& operator()() {
        maps.emplace_back();
        return *this;
    }

    // Add a new map to the pool and insert a key-value pair
    template<typename Key, typename Value>
    KeyWordPool& operator()(const Key& key, const Value& value) {
        maps.emplace_back();
        maps.back()[key] = value;
        return *this;
    }

    // Insert a key-value pair into the last map
    template<typename Key, typename Value>
    KeyWordPool& operator=(const std::pair<Key, Value>& pair) {
        if (maps.empty()) {
            maps.emplace_back();
        }
        maps.back()[pair.first] = pair.second;
        return *this;
    }

    // Connect all maps into a single map
    std::map<Types...> connect() const {
        std::map<Types...> result;
        for (const auto& map : maps) {
            result.insert(map.begin(), map.end());
        }
        return result;
    }

    // Other utility functions can be added here
    // For example:
    // - Size of the pool
    // - Clear the pool
    // - Access individual maps
    // - Custom connection strategies
};
