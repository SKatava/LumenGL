// tests/test_result.cpp
#include <gtest/gtest.h>
#include "lumengl/util/Result.h"

using namespace lgl;

TEST(Result, OkHoldsValue) {
    auto r = Result<int>::ok(42);
    EXPECT_TRUE(r.isOk());
    EXPECT_FALSE(r.isErr());
    EXPECT_EQ(r.value(), 42);
}

TEST(Result, ErrHoldsMessage) {
    auto r = Result<int>::err("something failed");
    EXPECT_TRUE(r.isErr());
    EXPECT_FALSE(r.isOk());
    EXPECT_EQ(r.error(), "something failed");
}

TEST(Result, MoveOutOfValue) {
    auto r = Result<std::string>::ok("hello");
    std::string s = std::move(r).value();
    EXPECT_EQ(s, "hello");
}

TEST(Result, MapOnOk) {
    auto r = Result<int>::ok(10)
        .map([](int v) { return v * 2; });
    EXPECT_TRUE(r.isOk());
    EXPECT_EQ(r.value(), 20);
}

TEST(Result, MapOnErrPropagates) {
    auto r = Result<int>::err("bad")
        .map([](int v) { return v * 2; });
    EXPECT_TRUE(r.isErr());
    EXPECT_EQ(r.error(), "bad");
}

TEST(Result, MapChangesType) {
    auto r = Result<int>::ok(5)
        .map([](int v) { return std::to_string(v); });
    EXPECT_TRUE(r.isOk());
    EXPECT_EQ(r.value(), "5");
}

TEST(ResultVoid, OkIsOk) {
    auto r = Result<void>::ok();
    EXPECT_TRUE(r.isOk());
}

TEST(ResultVoid, ErrHoldsMessage) {
    auto r = Result<void>::err("failed");
    EXPECT_TRUE(r.isErr());
    EXPECT_EQ(r.error(), "failed");
}
