#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(has_edge_success_and_direction)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_edge(g, a, b), true);
    ck_assert_int_eq(graph_has_edge(g, b, a), false);
}
END_TEST

START_TEST(has_edge_missing)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_edge(g, a, c), false);
}
END_TEST

START_TEST(has_edge_null_args)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_has_edge(NULL, a, b), false);
    ck_assert_int_eq(graph_has_edge(g, NULL, b), false);
    ck_assert_int_eq(graph_has_edge(g, a, NULL), false);
}
END_TEST

Suite *test_graph_has_edge(void)
{
    Suite *s = suite_create("Graph Has Edge");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, has_edge_success_and_direction);
    tcase_add_test(tc, has_edge_missing);
    tcase_add_test(tc, has_edge_null_args);

    suite_add_tcase(s, tc);
    return s;
}
