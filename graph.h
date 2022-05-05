#pragma once

#include "utils.h"

// Represents a directed graph with at most N vertices and M edges. 
template <u64 N, u64 M>
struct graph
{
    struct edge
    {
        u64 dst; edge *next;
    };

    edge e[M], *head[N]; u64 ecnt;

    void clear()
    {
        cnt = 0, memset(head, 0, sizeof head);
    }

    graph()
    {
        clear();
    }

    void add_edge(u64 u, u64 v)
    {
        e[ecnt].dst = v, e[ecnt].next = head[u];
        head[u] = &e[ecnt];
        ecnt++;
    }

    u64 newnode() {return ecnt++; }
    void popnode() {cnt--; }
};
