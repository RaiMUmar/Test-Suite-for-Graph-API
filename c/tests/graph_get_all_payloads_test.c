#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(get_all_payloads_success_order)
{
    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 20;
    int *c = malloc(sizeof(int)); *c = 30;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, c), GRAPH_STATUS_OK);

    const void * const *payloads = NULL;
    int count = -1;

    ck_assert_int_eq(graph_get_all_payloads(g, &payloads, &count), GRAPH_STATUS_OK);
    ck_assert_int_eq(count, 3);

    ck_assert_ptr_eq(payloads[0], a);
    ck_assert_ptr_eq(payloads[1], b);
    ck_assert_ptr_eq(payloads[2], c);
}
END_TEST

START_TEST(get_all_payloads_invalid_preconditions)
{
    const void * const *payloads = NULL;
    int count = 0;

    ck_assert_int_eq(graph_get_all_payloads(NULL, &payloads, &count), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_get_all_payloads(g, NULL, &count), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_get_all_payloads(g, &payloads, NULL), GRAPH_STATUS_NULL_ARGUMENT);
}
END_TEST

Suite *test_graph_get_all_payloads(void)
{
    Suite *s = suite_create("Graph Get All Payloads");
    TCase *tc = tcase_create("Basic");
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    tcase_add_test(tc, get_all_payloads_success_order);
    tcase_add_test(tc, get_all_payloads_invalid_preconditions);

    suite_add_tcase(s, tc);
    return s;
}
