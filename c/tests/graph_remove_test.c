#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(remove_success_updates_graph)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_size(g), 3);
    ck_assert_int_eq(graph_edge_count(g), 3);

    ck_assert_int_eq(graph_remove(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_size(g), 2);
    ck_assert_int_eq(graph_contains(g, b), false);

    ck_assert_int_eq(graph_edge_count(g), 1);
    ck_assert_int_eq(graph_has_edge(g, a, b), false);
    ck_assert_int_eq(graph_has_edge(g, b, c), false);
    ck_assert_int_eq(graph_has_edge(g, a, c), true);
}
END_TEST

START_TEST(remove_not_found)
{
    int *a = malloc(sizeof(int)); *a = 1;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    int *not_in_graph = malloc(sizeof(int)); *not_in_graph = 999;
    ck_assert_int_eq(graph_remove(g, not_in_graph), GRAPH_STATUS_NOT_FOUND);

    free(not_in_graph);
}
END_TEST

START_TEST(remove_invalid_preconditions)
{
    int *a = malloc(sizeof(int)); *a = 1;

    ck_assert_int_eq(graph_remove(NULL, a), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_remove(g, NULL), GRAPH_STATUS_NULL_ARGUMENT);

    free(a);
}
END_TEST

Suite *test_graph_remove(void)
{
    Suite *s = suite_create("Graph Remove");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, remove_success_updates_graph);
    tcase_add_test(tc, remove_not_found);
    tcase_add_test(tc, remove_invalid_preconditions);

    suite_add_tcase(s, tc);
    return s;
}
