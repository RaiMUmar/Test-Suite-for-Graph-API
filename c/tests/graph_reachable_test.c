#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(reachable_success_path)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_reachable(g, a, c), true);
    ck_assert_int_eq(graph_reachable(g, a, a), true);
    ck_assert_int_eq(graph_reachable(g, c, a), false);
}
END_TEST

START_TEST(reachable_missing_or_null_args)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_reachable(NULL, a, b), false);
    ck_assert_int_eq(graph_reachable(g, NULL, b), false);
    ck_assert_int_eq(graph_reachable(g, a, NULL), false);

    int *not_in_graph = malloc(sizeof(int)); *not_in_graph = 999;
    ck_assert_int_eq(graph_reachable(g, a, not_in_graph), false);
    free(not_in_graph);
}
END_TEST

Suite *test_graph_reachable(void)
{
    Suite *s = suite_create("Graph Reachable");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, reachable_success_path);
    tcase_add_test(tc, reachable_missing_or_null_args);

    suite_add_tcase(s, tc);
    return s;
}
