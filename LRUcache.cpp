#include "LRUcache.h"

using namespace std;

template <class K, class V>
LRU_Cache<K, V>::LRU_Cache(int capacity, V defaultValue) {
  head = nullptr;
  tail = nullptr;
  size = capacity;
  def = defaultValue;
}

template <class K, class V>
LRU_Cache<K, V>::node::node(K k) { key = k; }

template <class K, class V>
LRU_Cache<K, V>::node::node(K k, node* nextNode, node* prevNode) {
  key = k;
  next = nextNode;
  prev = prevNode;
}

template <class K, class V>
V LRU_Cache<K, V>::get(K key) {
  if ( LRU_Cache::cache.count(key) == 0 )
    return def;

  V value = LRU_Cache::cache[key];
  removeKey(key);

  put(key, value);
  return cache[key];
}

template <class K, class V>
void LRU_Cache<K, V>::put(K key, V value) {
  if (head == nullptr && size > 0 ) {
    cache[key] = value;
    head = new node(key, nullptr, nullptr);
    tail = head;
    nodePointers[key] = head;
    return;
  }

  if ( cache.count(key) > 0 )
    removeKey(key);

  if ( cache.size() == 0 ) {
    put(key, value);
    return;
  }

  cache[key] = value;
  node* newNode = new node( key, nullptr, tail );
  tail -> next = newNode;
  tail = newNode;
  nodePointers[key] = newNode;

  if ( cache.size() > size ) {
    cache.erase(head -> key);
    nodePointers.erase(head -> key);
    head = head -> next;
  }
}

// Assumes that key exists
template <class K, class V>
void LRU_Cache<K, V>::removeKey( K key ) {

  node* existing = nodePointers[key];

  if ( existing == head && existing == tail ) {
    head = nullptr;
    tail = nullptr;
  } else {

    if ( existing != head )
      existing -> prev -> next = existing -> next;
    else
      head = head -> next;

    if ( existing != tail )
      existing -> next -> prev = existing -> prev;
    else
      tail = tail -> prev;
  }

  cache.erase(key);
  nodePointers.erase(key);
}
