#include <functional>
#include <stddef.h>
#include <vector>
template <typename K, typename V>

class MyHash {
public:
  struct KeyValPair {
    K key;
    V val;
    bool is_occupied = false;
  };

  MyHash() : size(1), elements(0) { bucket_list.resize(size); }

  V get(K key_in) {
    int index = keyhash(key_in) % size;
    while (bucket_list[index].is_occupied) {
      if (bucket_list[index].key == key_in) {
        return bucket_list[index].val;
      } else {
        index = (index + 1) % size;
      }
    }

    return V();
  }
  void put(K new_key, V new_val) {
    int index = keyhash(new_key) % size;

    while (bucket_list[index].is_occupied) {
      if (bucket_list[index].key == new_key) {
        bucket_list[index].val = new_val;
        return;
      }
      index = (index + 1) % size;
    }

    bucket_list[index].key = new_key;
    bucket_list[index].val = new_val;
    bucket_list[index].is_occupied = true;
    elements++;
    if ((float)(elements) / size > 0.4) {
      size = 2 * size;
      reyhash();
    }
  }
  bool remove(K key_in) {
    int index = keyhash(key_in) % size;
    while (bucket_list[index].is_occupied) {
      if (bucket_list[index].key == key_in) {
        break;
      }
      index = (index + 1) % size;
    }
    if (!bucket_list[index].is_occupied) {
      return false;
    }
    bucket_list[index].is_occupied = false;
    elements--;
    int j = index;
    while (true) {
      index = (index + 1) % size;

      if (!bucket_list[index].is_occupied)
        break;

      int k = keyhash(bucket_list[index].key) % size;

      bool should_move = false;
      if (index >= j) {
        if (k <= j || k > index)
          should_move = true;
      } else {
        if (k <= j && k > index)
          should_move = true;
      }

      if (should_move) {
        bucket_list[j] = bucket_list[index];
        bucket_list[index].is_occupied = false;
        j = index;
      }
    }

    if (size > 1 && (float)elements / size < 0.25) {
      size = size / 2;
      reyhash();
    }

    return true;
  }

  std::vector<KeyValPair> getAll() const {
    std::vector<KeyValPair> all;
    for (const auto &pair : bucket_list) {
      if (pair.is_occupied) {
        all.push_back(pair);
      }
    }
    return all;
  }
  MyHash(MyHash &&) = default;
  MyHash(const MyHash &) = default;
  MyHash &operator=(MyHash &&) = default;
  MyHash &operator=(const MyHash &) = default;
  ~MyHash() = default;

private:
  int size;
  int elements;
  std::vector<KeyValPair> bucket_list;
  size_t keyhash(const K &key) const { return std::hash<K>{}(key); }
  void reyhash() {
    std::vector<KeyValPair> temp_list = getAll();
    bucket_list.clear();
    elements = 0;
    bucket_list.resize(size);
    for (KeyValPair node : temp_list) {
      put(node.key, node.val);
    }
  }
};
