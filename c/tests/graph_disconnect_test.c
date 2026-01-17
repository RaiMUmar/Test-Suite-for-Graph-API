#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(disconnect_success)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_disconnect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_has_edge(g, a, b), false);
    ck_assert_int_eq(graph_edge_count(g), 0);
}
END_TEST

START_TEST(disconnect_not_found)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_disconnect(g, a, b), GRAPH_STATUS_NOT_FOUND);
}
END_TEST

START_TEST(disconnect_invalid_preconditions)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_disconnect(NULL, a, b), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_disconnect(g, NULL, b), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_disconnect(g, a, NULL), GRAPH_STATUS_NULL_ARGUMENT);
}
END_TEST

START_TEST(disconnect_endpoint_missing_returns_not_found)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;  

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_disconnect(g, a, c), GRAPH_STATUS_NOT_FOUND);
    ck_assert_int_eq(graph_disconnect(g, c, b), GRAPH_STATUS_NOT_FOUND);

    free(c);
}
END_TEST


Suite *test_graph_disconnect(void)
{
    Suite *s = suite_create("Graph Disconnect");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, disconnect_success);
    tcase_add_test(tc, disconnect_not_found);
    tcase_add_test(tc, disconnect_invalid_preconditions);
    tcase_add_test(tc, disconnect_endpoint_missing_returns_not_found);


    suite_add_tcase(s, tc);
    return s;
}
