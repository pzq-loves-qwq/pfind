#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <queue>
#include <unordered_set>
#include "blah.hpp"

std::vector<node*> hash[HASHMOD];

const int POOLSIZE = 1 << 22;
node pool[POOLSIZE]; int poolcnt;

inline node *newnode(node n)
{
    if (poolcnt < POOLSIZE)
        return &(pool[poolcnt++] = n);
    std::printf("Ran out of nodes. Aborting search...\n");
    std::exit(1);
}

inline void print_spaceship(node *n)
{
    if (n == &pool[0]) return;
    std::printf("x = 0, y = 0\n");
    while (n != &pool[0])
    {
        output_row(n -> row);
        printf("\n");
        n = kth_parent(n, p);
    }
    printf("!\n");
}

inline void initialize()
{
    pool[0].row = 0;
    pool[0].parent = &pool[0];
    hash[0].push_back(&pool[0]);
}

const u64 dfs_depth = p, dfs_threshold = 1 << 20;
node tmp_nodes[dfs_depth];

bool dfs(node *n, int depth)
{
    if (depth == 0)
        return true;

    node *v = kth_parent(n, p - y - 1);
    u64 c = v -> row;
    v = kth_parent(v, y);
    u64 b = v -> row;
    v = kth_parent(v, p);
    u64 a = v -> row;

    tmp_nodes[depth - 1].parent = n;
    for (u64 x = 0; x < (u64(1) << w); x++)
        if (ev2(a, b, x) == c)
        {
            tmp_nodes[depth - 1].row = x;
            if (dfs(&tmp_nodes[depth - 1], depth - 1))
                return true;
        }
    return false;
}

void bfs()
{
    int qhead = 0, qtail = 1;
    while (qhead < qtail)
    {
        if (qtail - qhead > dfs_threshold)
        {
            std::printf("Compating queue...");
            for (int i = qhead; i < qtail; i++)
                if (!dfs(&pool[i], dfs_depth))
                    pool[i].parent = NULL;
        }

        node *u = &pool[qhead];
        if (u -> parent == NULL)
            continue;
        qhead++;
        
        // printf("Inside node:\n");
        // for (int i = 0; i < 2 * p; i++)
        //     output_row(kth_parent(u, i) -> row);

        node *v = kth_parent(u, p - y - 1);
        u64 c = v -> row;
        v = kth_parent(v, y);
        u64 b = v -> row;
        v = kth_parent(v, p);
        u64 a = v -> row;
        // printf("a = %lu, b = %lu, c = %lu\n", a, b, c);

        for (u64 x = 0; x < (u64(1) << w); x++)
            if (ev2(a, b, x) == c)
            {
                // printf("x = %lu\n", x);
                node *v = newnode(node(x, u));
                if (hash_node(v) == 0)
                {
                    print_spaceship(v);
                    continue;
                }
                for (auto&& w : hash[hash_node(v)])
                    if (is_same_as(v, w))
                        continue;
                hash[hash_node(v)].push_back(v);
                pool[qtail++] = *v;
            }
    }
}

int main()
{
    initialize();
    bfs();
}
