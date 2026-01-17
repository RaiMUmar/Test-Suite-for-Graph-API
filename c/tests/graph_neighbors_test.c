#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(neighbors_success_order)
{
    int *a = malloc(sizeof(int)); 
    *a = 1;
    int *b = malloc(sizeof(int)); 
    *b = 2;
    int *c = malloc(sizeof(int)); 
    *c = 3;
    int *d = malloc(sizeof(int)); 
    *d = 4;
    int *e = malloc(sizeof(int)); 
    *e = 5;
    int *f = malloc(sizeof(int)); 
    *f = 6;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, f), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, f), GRAPH_STATUS_OK);

    const void * const *neighbors = NULL;
    int count = -1;

    ck_assert_int_eq(graph_get_neighbors(g, a, &neighbors, &count), GRAPH_STATUS_OK);
    ck_assert_int_eq(count, 5);
    ck_assert_ptr_eq(neighbors[0], b);
    ck_assert_ptr_eq(neighbors[1], c);
    ck_assert_ptr_eq(neighbors[2], d);
    ck_assert_ptr_eq(neighbors[3], e);
    ck_assert_ptr_eq(neighbors[4], f);
}
END_TEST

START_TEST(neighbors_zero_outgoing)
{
    int *a = malloc(sizeof(int)); *a = 10;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    const void * const *neighbors = (const void * const *)0x1; /* sentinel */
    int count = -1;

    ck_assert_int_eq(graph_get_neighbors(g, a, &neighbors, &count), GRAPH_STATUS_OK);
    ck_assert_int_eq(count, 0);
}
END_TEST

START_TEST(neighbors_payload_missing)
{
    int *a = malloc(sizeof(int)); *a = 1;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    int *not_in_graph = malloc(sizeof(int));
    *not_in_graph = 999;

    const void * const *neighbors = NULL;
    int count = 0;

    ck_assert_int_eq(graph_get_neighbors(g, not_in_graph, &neighbors, &count), GRAPH_STATUS_NOT_FOUND);

    free(not_in_graph);
}
END_TEST

START_TEST(neighbors_invalid_preconditions)
{
    int *a = malloc(sizeof(int)); *a = 5;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    const void * const *neighbors = NULL;
    int count = 0;

    ck_assert_int_eq(graph_get_neighbors(NULL, a, &neighbors, &count), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_get_neighbors(g, NULL, &neighbors, &count), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_get_neighbors(g, a, NULL, &count), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_get_neighbors(g, a, &neighbors, NULL), GRAPH_STATUS_NULL_ARGUMENT);
}
END_TEST

Suite *test_graph_get_neighbors(void)
{
    Suite *s = suite_create("Graph Get Neighbors");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, neighbors_success_order);
    tcase_add_test(tc, neighbors_zero_outgoing);
    tcase_add_test(tc, neighbors_payload_missing);
    tcase_add_test(tc, neighbors_invalid_preconditions);

    suite_add_tcase(s, tc);
    return s;
}
