#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(size_empty)
{
    ck_assert_int_eq(graph_size(g), 0);
}
END_TEST

START_TEST(size_after_inserts)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;
    int *d = malloc(sizeof(int)); *d = 4;
    int *e = malloc(sizeof(int)); *e = 5;
    int *f = malloc(sizeof(int)); *f = 6;
    int *m = malloc(sizeof(int)); *m = 7;
    int *h = malloc(sizeof(int)); *h = 8;
    int *i = malloc(sizeof(int)); *i = 9;
    int *j = malloc(sizeof(int)); *j = 10;
    int *k = malloc(sizeof(int)); *k = 11;
    int *l = malloc(sizeof(int)); *l = 12;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, d), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, e), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, f), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, m), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, h), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, i), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, j), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, k), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, l), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_size(g), 12);
}
END_TEST

START_TEST(size_null_graph)
{
    ck_assert_int_eq(graph_size(NULL), 0);
}
END_TEST

Suite *test_graph_size(void)
{
    Suite *s = suite_create("Graph Size");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, size_empty);
    tcase_add_test(tc, size_after_inserts);
    tcase_add_test(tc, size_null_graph);

    suite_add_tcase(s, tc);
    return s;
}
