#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);

static int destroyed_count = 0;

static void counting_destroy(void *p)
{
    destroyed_count++;
    free(p);
}

START_TEST(destroy_calls_destroy_fn_for_each_payload)
{
    destroyed_count = 0;

    Graph *local = graph_create(my_compare_ints, counting_destroy);
    ck_assert_ptr_nonnull(local);

    int *a = malloc(sizeof(int)); 
    *a = 1;
    int *b = malloc(sizeof(int)); 
    *b = 2;
    int *c = malloc(sizeof(int)); 
    *c = 3;

    ck_assert_int_eq(graph_insert(local, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(local, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(local, c), GRAPH_STATUS_OK);

    graph_destroy(local);

    ck_assert_int_eq(destroyed_count, 3);
}
END_TEST

START_TEST(destroy_with_null_destroy_fn_does_not_crash)
{
    Graph *local = graph_create(my_compare_ints, NULL);
    ck_assert_ptr_nonnull(local);

    int *a = malloc(sizeof(int));
    *a = 10;

    ck_assert_int_eq(graph_insert(local, a), GRAPH_STATUS_OK);

    graph_destroy(local);

    free(a);
}
END_TEST

START_TEST(destroy_null_graph_safe)
{
    graph_destroy(NULL);
}
END_TEST


START_TEST(destroy_calls_destroy_fn_once_per_payload_even_with_edges)
{
    destroyed_count = 0;

    Graph *local = graph_create(my_compare_ints, counting_destroy);
    ck_assert_ptr_nonnull(local);

    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    ck_assert_int_eq(graph_insert(local, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(local, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(local, c), GRAPH_STATUS_OK);

    // Add edges to make adjacency lists non-empty */
    ck_assert_int_eq(graph_connect(local, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(local, b, c), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(local, c, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(local, a, a), GRAPH_STATUS_OK); 

    graph_destroy(local);

    ck_assert_int_eq(destroyed_count, 3);
}
END_TEST


START_TEST(remove_calls_destroy_fn_once)
{
    destroyed_count = 0;

    Graph *local = graph_create(my_compare_ints, counting_destroy);
    ck_assert_ptr_nonnull(local);

    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(local, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(local, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_remove(local, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(destroyed_count, 1); 

    graph_destroy(local);
    ck_assert_int_eq(destroyed_count, 2); 
}
END_TEST





Suite *test_graph_destroy(void)
{
    Suite *s = suite_create("Graph Destroy");
    TCase *tc = tcase_create("Basic");

    tcase_add_test(tc, destroy_calls_destroy_fn_for_each_payload);
    tcase_add_test(tc, destroy_with_null_destroy_fn_does_not_crash);
    tcase_add_test(tc, destroy_null_graph_safe);
    tcase_add_test(tc, destroy_calls_destroy_fn_once_per_payload_even_with_edges);
    tcase_add_test(tc, remove_calls_destroy_fn_once);

    suite_add_tcase(s, tc);
    return s;
}
