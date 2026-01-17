#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(contains_success)
{
    int *a = malloc(sizeof(int)); *a = 42;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_contains(g, a), true);
}
END_TEST

START_TEST(contains_missing)
{
    int *a = malloc(sizeof(int)); *a = 1;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    int *b = malloc(sizeof(int)); *b = 999;
    ck_assert_int_eq(graph_contains(g, b), false);

    free(b);
}
END_TEST

START_TEST(contains_null_args)
{
    int *a = malloc(sizeof(int)); *a = 5;
    ck_assert_int_eq(graph_contains(NULL, a), false);
    ck_assert_int_eq(graph_contains(g, NULL), false);
}
END_TEST

Suite *test_graph_contains(void)
{
    Suite *s = suite_create("Graph Contains");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, contains_success);
    tcase_add_test(tc, contains_missing);
    tcase_add_test(tc, contains_null_args);

    suite_add_tcase(s, tc);
    return s;
}
