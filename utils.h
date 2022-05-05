#pragma once

#include <cstdint>
#include <algorithm>

// Fixed-size integers. 
typedef std::int32_t i32;
typedef std::uint32_t u32;
typedef std::int64_t i64;
typedef std::uint64_t u64;

// GCD
u64 gcd(u64 x, u64 y)
{
    if (x < y) std::swap(x, y);
    if (y == 0) return x;
    return gcd(y, x - y);
}
