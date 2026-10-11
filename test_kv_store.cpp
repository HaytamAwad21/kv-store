#include <cassert>
#include <iostream>
#include "kv_store.hpp"

// Helpers: remove the repeated assert patterns
void expect_value(const KVStore& kv, const std::string& key, const std::string& expected) {
    auto result = kv.get(key);
    assert(result.has_value());
    assert(result.value() == expected);
}

void expect_missing(const KVStore& kv, const std::string& key) {
    assert(!kv.get(key).has_value());
}

void test_set_and_get() {
    KVStore kv;
    kv.set("a", "1");
    expect_value(kv, "a", "1");
}

void test_get_missing() {
    KVStore kv;
    expect_missing(kv, "nope");
}

void test_overwrite() {
    KVStore kv;
    kv.set("a", "1");
    kv.set("a", "2");
    expect_value(kv, "a", "2");
    assert(kv.size() == 1);
}

void test_del_existing() {
    KVStore kv;
    kv.set("a", "1");
    assert(kv.del("a") == true);
    expect_missing(kv, "a");
}

void test_del_missing() {
    KVStore kv;
    assert(kv.del("nope") == false);
}

void test_empty_value() {
    KVStore kv;
    kv.set("k", "");
    expect_value(kv, "k", "");
}

void test_size_after_mix() {
    KVStore kv;
    kv.set("a", "1");
    kv.set("b", "2");
    kv.set("c", "3");
    kv.del("b");
    kv.del("zzz");
    assert(kv.size() == 2);
}

int main() {
    test_set_and_get();
    test_get_missing();
    test_overwrite();
    test_del_existing();
    test_del_missing();
    test_empty_value();
    test_size_after_mix();
    std::cout << "All tests passed\n";
    return 0;
}