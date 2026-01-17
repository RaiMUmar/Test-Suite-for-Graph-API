#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(edge_count_empty)
{
    ck_assert_int_eq(graph_edge_count(g), 0);
}
END_TEST

START_TEST(edge_count_after_connects)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;
    int *d = malloc(sizeof(int)); *d = 4;
    int *e = malloc(sizeof(int)); *e = 5;
    //int *f = malloc(sizeof(int)); *f = 6;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, e), GRAPH_STATUS_OK);
    //ck_assert_int_eq(graph_insert(g, f), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, c, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, c, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, d, e), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_edge_count(g), 12);
}
END_TEST

START_TEST(edge_count_null_graph)
{
    ck_assert_int_eq(graph_edge_count(NULL), 0);
}
END_TEST

Suite *test_graph_edge_count(void)
{
    Suite *s = suite_create("Graph Edge Count");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, edge_count_empty);
    tcase_add_test(tc, edge_count_after_connects);
    tcase_add_test(tc, edge_count_null_graph);

    suite_add_tcase(s, tc);
    return s;
}
