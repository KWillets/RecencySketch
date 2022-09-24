#include <stddef.h>
#include <algorithm>
#include <functional>

template<class KeyType, class TimeType, size_t n, size_t k>
class RecencySketch {

  TimeType times[n][k];

  size_t hash(size_t i, KeyType x) {
    std::size_t h = i * std::hash<KeyType>()(x);
    return h % n;
  }

public:

  RecencySketch(): times() {}

  TimeType probe(KeyType key) {
    TimeType t = times[hash(0,key)][0];
    for(size_t i = 1; i < k; i++) {
      size_t h = hash(i,key); 
      t = std::min(t, times[h][i]);
    }
    return t;
  }

  void add(KeyType key, TimeType t) {
    for(size_t i = 0; i < k; i++) {
      size_t h = hash(i,key); 
      times[h][i] = std::max(t, times[h][i]);
    }
  }

};
