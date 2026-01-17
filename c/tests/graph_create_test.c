#include <check.h>
#include <stdlib.h>
#include "graph.h"

int my_compare_ints(const void *a, const void *b);

START_TEST(create_invalid_compare_fn)
{
    Graph *local = graph_create(NULL, NULL);
    ck_assert_ptr_null(local);
}
END_TEST

START_TEST(create_success_destroy_fn_null_allowed)
{
    Graph *local = graph_create(my_compare_ints, NULL);
    ck_assert_ptr_nonnull(local);
    graph_destroy(local);
}
END_TEST

START_TEST(create_success_with_destroy_fn)
{
    void local_destroy(void *p) { free(p); }

    Graph *local = graph_create(my_compare_ints, local_destroy);
    ck_assert_ptr_nonnull(local);
    graph_destroy(local);
}
END_TEST

Suite *test_graph_create(void)
{
    Suite *s = suite_create("Graph Create");
    TCase *tc = tcase_create("Basic");

    tcase_add_test(tc, create_invalid_compare_fn);
    tcase_add_test(tc, create_success_destroy_fn_null_allowed);
    tcase_add_test(tc, create_success_with_destroy_fn);

    suite_add_tcase(s, tc);
    return s;
}
