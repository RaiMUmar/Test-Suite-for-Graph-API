#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(indegree_zero)
{
    int *a = malloc(sizeof(int)); *a = 1;
    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_indegree(g, a), 0);
}
END_TEST

START_TEST(indegree_counts_incoming)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, c), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_indegree(g, c), 2);
    ck_assert_int_eq(graph_indegree(g, a), 0);
}
END_TEST

START_TEST(indegree_null_args)
{
    int *a = malloc(sizeof(int)); *a = 1;
    ck_assert_int_eq(graph_indegree(NULL, a), 0);
    ck_assert_int_eq(graph_indegree(g, NULL), 0);
}
END_TEST

Suite *test_graph_indegree(void)
{
    Suite *s = suite_create("Graph Indegree");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, indegree_zero);
    tcase_add_test(tc, indegree_counts_incoming);
    tcase_add_test(tc, indegree_null_args);

    suite_add_tcase(s, tc);
    return s;
}
