#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(has_cycle_false)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_cycle(g), false);
}
END_TEST

START_TEST(has_cycle_true)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, c, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_cycle(g), true);
}
END_TEST

START_TEST(self_cycle)
{
    int *a = malloc(sizeof(int)); *a = 1;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_cycle(g), true);
}
END_TEST

START_TEST(has_cycle_null_graph)
{
    ck_assert_int_eq(graph_has_cycle(NULL), false);
}
END_TEST

Suite *test_graph_has_cycle(void)
{
    Suite *s = suite_create("Graph Has Cycle");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, has_cycle_false);
    tcase_add_test(tc, has_cycle_true);
    tcase_add_test(tc, has_cycle_null_graph);
    tcase_add_test(tc, self_cycle);

    suite_add_tcase(s, tc);
    return s;
}
