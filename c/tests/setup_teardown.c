#include <check.h>
#include <stdlib.h>
#include "graph.h"

Graph *g = NULL;

int my_compare_ints(const void *a, const void *b) {
    const int *ia = a;
    const int *ib = b;
    if (*ia < *ib) return -1;
    if (*ia > *ib) return 1;
    return 0;
}

void my_destroy_int(void *p) {
    free(p);
}

void my_setup_graph(void)
{
    g = graph_create(my_compare_ints, my_destroy_int);
    ck_assert_ptr_nonnull(g);
}

void my_teardown_graph(void)
{
    /* graph_destroy must call destroy_int on all payloads */
    graph_destroy(g);
    g = NULL;
}
