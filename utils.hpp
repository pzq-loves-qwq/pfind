#pragma once

#include <stdio.h>
#include <stdint.h>

#include "params.hpp"

using u64 = uint64_t;

inline u64 evolve(u64 a, u64 b, u64 c)
{
    // Extra birth on the right
    if (table[((a & 1) << 8) | ((b & 1) << 5) | ((c & 1) << 2)])
        return u64(-1);

    // Avoid boundary issues
    a <<= 1, b <<= 1, c <<= 1;

    u64 res = 0;
    for (int i = 0; i < 64; i++)
    {
        u64 A = (a >> i) & 7, B = (b >> i) & 7, C = (c >> i) & 7;
        res |= u64(table[(A << 6) | (B << 3) | C]) << i;
    }

    return res;
}

inline u64 mirror(u64 x)
{
    for (int i = 0; i < w; i++)
        x |= (((x >> i) & 1) << (2 * w - 1 - i));
    return x;
}

inline u64 ev2(u64 a, u64 b, u64 c)
{
    a = mirror(a), b = mirror(b), c = mirror(c);
    u64 s = evolve(a, b, c);
    if (s == -1) return -1;
    return s & ((u64(1) << w) - 1);
}

struct __attribute__((aligned(64))) node
{
    u64 row;
    node *parent;

    node() {}
    node(u64 r, node *p) : row(r), parent(p) {}
};

inline node *kth_parent(node *n, int k)
{
    for (int i = 0; i < k; i++)
        n = n -> parent;
    return n;
}

inline void output_row(u64 r)
{
    for (int i = 0; i < w; i++)
        std::printf("%c", "bo"[(r >> i) & 1]);
    std::printf("$");
}

const int HASHB = 1057, HASHMOD = 43128381;

inline u64 hash_node(node *n)
{
    u64 hash = 0;
    for (int i = 0; i < 2 * p; i++)
    {
        hash = (hash * HASHB + (n -> row)) % HASHMOD;
        n = n -> parent;
    }
    return hash;
}

inline bool is_same_as(node *u, node *v)
{
    if (u == v)
        return true;
    for (int i = 0; i < 2 * p; i++)
    {
        if (u -> row != v -> row)
            return false;
        u = u -> parent;
        v = v -> parent;
    }
    return true;
}
