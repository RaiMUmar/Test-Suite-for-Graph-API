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
    int *value = malloc(sizeof(int));
    *value = 30;
    ck_assert_int_eq(graph_insert(g, value), GRAPH_STATUS_OK);
}
END_TEST

START_TEST(invalid_preconditions)
{
    // g = NULL
    int *value = malloc(sizeof(int));
    *value = 10;
    ck_assert_int_eq(graph_insert(NULL, value), GRAPH_STATUS_NULL_ARGUMENT);
    
    // payload = NULL
    ck_assert_int_eq(graph_insert(g, NULL), GRAPH_STATUS_NULL_ARGUMENT);
}
END_TEST


START_TEST(duplicate_payload)
{
    int *value = malloc(sizeof(int));
    *value = 50;
    ck_assert_int_eq(graph_insert(g, value), GRAPH_STATUS_OK);
    
    // payload = duplicate
    ck_assert_int_eq(graph_insert(g, value), GRAPH_STATUS_DUPLICATE_PAYLOAD);
}
END_TEST

START_TEST(insert_duplicate_by_value_not_pointer)
{
    int *x = malloc(sizeof(int)); *x = 50;
    int *y = malloc(sizeof(int)); *y = 50;   // same value, different pointer

    ck_assert_int_eq(graph_insert(g, x), GRAPH_STATUS_OK);
    ck_assert_int_eq(graph_insert(g, y), GRAPH_STATUS_DUPLICATE_PAYLOAD);

    free(y);
}
END_TEST


Suite *test_graph_insert(void){
    // Initialize
    Suite *s = suite_create("Graph Insert"); // Create Suite
    TCase *tc =  tcase_create("Basic"); // Create Test Group
    tcase_add_checked_fixture(tc, my_setup_graph, my_teardown_graph);

    // Test the function
    tcase_add_test(tc, success);
    tcase_add_test(tc, invalid_preconditions);
    tcase_add_test(tc, duplicate_payload);
    tcase_add_test(tc, insert_duplicate_by_value_not_pointer);

    suite_add_tcase(s, tc);
    return s;
}
