#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(is_connected_true_chain_from_first)
{
    int *a = malloc(sizeof(int)); *a = 1; /* first inserted */
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_is_connected(g), true);
}
END_TEST

START_TEST(is_connected_false_disconnected_node)
{
    int *a = malloc(sizeof(int)); *a = 1; /* first inserted */
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    /* c is not reachable from a */

    ck_assert_int_eq(graph_is_connected(g), false);
}
END_TEST

START_TEST(is_connected_null_graph)
{
    ck_assert_int_eq(graph_is_connected(NULL), false);
}
END_TEST

Suite *test_graph_is_connected(void)
{
    Suite *s = suite_create("Graph Is Connected");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, is_connected_true_chain_from_first);
    tcase_add_test(tc, is_connected_false_disconnected_node);
    tcase_add_test(tc, is_connected_null_graph);

    suite_add_tcase(s, tc);
    return s;
}
