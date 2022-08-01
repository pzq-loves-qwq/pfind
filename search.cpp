#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <queue>
#include <unordered_set>
#include "blah.hpp"

std::vector<node*> nodes;
std::unordered_set<u64> st;
node *root;

inline void print_spaceship(node *n)
{
    if (n == root) return;
    std::printf("x = 0, y = 0\n");
    while (n != root)
    {
        output_row(n -> row);
        printf("\n");
        n = kth_parent(n, p);
    }
    printf("!\n");
}

inline void initialize()
{
    root = (node*) std::malloc(sizeof(node));
    nodes.push_back(root);
    root -> row = 0;
    root -> parent = root;
}

void bfs()
{
    std::queue<node*> q;
    q.push(root);

    while (!q.empty())
    {
        node *u = q.front();
        q.pop();
        st.insert(hash_node(u));
        
        // printf("Inside node:\n");
        // for (int i = 0; i < 2 * p; i++)
        //     output_row(kth_parent(u, i) -> row);

        u64 a = kth_parent(u, 2 * p - 1) -> row, b = kth_parent(u, p - 1) -> row, c = kth_parent(u, p - y - 1) -> row;
        // printf("a = %lu, b = %lu, c = %lu\n", a, b, c);

        for (u64 x = 0; x < (u64(1) << w); x++)
            if (ev2(a, b, x) == c)
            {
                // printf("x = %lu\n", x);
                node *v = (node*) std::malloc(sizeof(node));
                v -> row = x;
                v -> parent = u;
                if (hash_node(v) == 0)
                    print_spaceship(v);
                if (st.count(hash_node(v)))
                {
                    std::free(v);
                    continue;
                }
                q.push(v);
                nodes.push_back(v);
            }
    }
}

struct helper
{
    ~helper()
    {
        std::printf("Cleanup...\n");
        for (node *p : nodes)
            std::free(p);
    }
} _;

int main()
{
    initialize();
    bfs();
}
