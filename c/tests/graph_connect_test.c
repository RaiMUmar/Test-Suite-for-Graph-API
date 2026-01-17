#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);
void my_destroy_int(void *p);
void my_setup_graph(void);
void my_teardown_graph(void);
extern Graph *g;

START_TEST(success)
{
    int *value_from = malloc(sizeof(int));
    *value_from = 30;
    int *value_to = malloc(sizeof(int));
    *value_to = 50;
    graph_insert(g, value_from);
    graph_insert(g, value_to);

    ck_assert_int_eq(graph_connect(g, value_from, value_to), GRAPH_STATUS_OK);
}
END_TEST

START_TEST(endpoint)
{
    int *value_inserted = malloc(sizeof(int));
    *value_inserted = 30;

    int *value_not_inserted = malloc(sizeof(int));
    *value_not_inserted = 50;
    
    graph_insert(g, value_inserted);

    ck_assert_int_eq(graph_connect(g, value_inserted, value_not_inserted), GRAPH_STATUS_NOT_FOUND);
    ck_assert_int_eq(graph_connect(g, value_not_inserted, value_inserted), GRAPH_STATUS_NOT_FOUND);
}
END_TEST


START_TEST(duplicate)
{
    int *value_from = malloc(sizeof(int));
    *value_from = 30;
    int *value_to = malloc(sizeof(int));
    *value_to = 50;
    graph_insert(g, value_from);
    graph_insert(g, value_to);


    ck_assert_int_eq(graph_connect(g, value_from, value_to), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, value_from, value_to), GRAPH_STATUS_DUPLICATE_EDGE);
}
END_TEST

START_TEST(invalid_preconditions)
{
    int *value = malloc(sizeof(int));
    *value = 30;
    int *value2 = malloc(sizeof(int));
    *value2 = 50;

    ck_assert_int_eq(graph_insert(g, value), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, value2), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, value, NULL), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_connect(g, NULL, value2), GRAPH_STATUS_NULL_ARGUMENT);
    ck_assert_int_eq(graph_connect(NULL, value, value2), GRAPH_STATUS_NULL_ARGUMENT);
}
END_TEST

START_TEST(connect_to_itself)
{
    int *value = malloc(sizeof(int));
    *value = 30;
    
    graph_insert(g, value);

    ck_assert_int_eq(graph_connect(g, value, value), GRAPH_STATUS_OK);
}
END_TEST

START_TEST(connect_by_value_not_pointer)
{
    int *a = malloc(sizeof(int)); *a = 30;
    int *b = malloc(sizeof(int)); *b = 50;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    int *a2 = malloc(sizeof(int)); *a2 = 30; 
    int *b2 = malloc(sizeof(int)); *b2 = 50;

    ck_assert_int_eq(graph_connect(g, a2, b2), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_has_edge(g, a, b), true);
    ck_assert_int_eq(graph_edge_count(g), 1);

    free(a2);
    free(b2);
}
END_TEST

START_TEST(connect_reverse_direction_is_not_duplicate)
{
    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;

    ck_assert_int_eq(graph_insert(g, a), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, b), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_connect(g, a, b), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_connect(g, b, a), GRAPH_STATUS_OK);

    ck_assert_int_eq(graph_edge_count(g), 2);
    ck_assert_int_eq(graph_has_edge(g, a, b), true);
    ck_assert_int_eq(graph_has_edge(g, b, a), true);
}
END_TEST




Suite *test_graph_connect(void){
    // Initialize
    Suite *s = suite_create("Graph Connect"); // Create Suite
    TCase *tc =  tcase_create("Basic"); // Create Test Group
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    // Test the function
    tcase_add_test(tc, success);
    tcase_add_test(tc, endpoint);
    tcase_add_test(tc, duplicate);
    tcase_add_test(tc, invalid_preconditions);
    tcase_add_test(tc, connect_to_itself);
    tcase_add_test(tc, connect_by_value_not_pointer);
    tcase_add_test(tc, connect_reverse_direction_is_not_duplicate);

    


    suite_add_tcase(s, tc);
    return s;
}
