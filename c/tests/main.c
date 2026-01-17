#include <check.h>


// Forward declaration of the function that creates the test suite
// This function must be defined in the respective test suite file
Suite *starter_suite(void);
Suite *test_graph_create(void);
Suite *test_graph_insert(void);
Suite *test_graph_connect(void);
Suite *test_graph_get_neighbors(void);
Suite *test_graph_size(void);
Suite *test_graph_contains(void);
Suite *test_graph_outdegree(void);
Suite *test_graph_has_edge(void);
Suite *test_graph_indegree(void);
Suite *test_graph_edge_count(void);
Suite *test_graph_get_all_payloads(void);
Suite *test_graph_reachable(void);
Suite *test_graph_has_cycle(void);
Suite *test_graph_is_connected(void);
Suite *test_graph_disconnect(void);
Suite *test_graph_remove(void);
Suite *test_graph_destroy(void);


// Entry point for running all test suites
int main(void) {
    // Array of test suites to run. Add more suites to the array as you write them.
    Suite *suites[] = { starter_suite(), 
        test_graph_create(), 
        test_graph_destroy(),
        test_graph_insert(), 
        test_graph_connect(), 
        test_graph_get_neighbors(), 
        test_graph_size(),
        test_graph_contains(),
        test_graph_outdegree(),
        test_graph_has_edge(),
        test_graph_indegree(),
        test_graph_edge_count(),
        test_graph_get_all_payloads(),
        test_graph_reachable(),
        test_graph_has_cycle(),
        test_graph_is_connected(),
        test_graph_disconnect(),
        test_graph_remove(),
        NULL };

    // The test runner must be created with an initial suite (cannot start empty),
    // so we use the first suite in the array to initialize it.
    SRunner *runner = srunner_create(suites[0]);

    /* If there are more suites, add them to the runner one by one.
     This two-step process is required because srunner_create() needs a non-NULL suite to start,
     and additional suites can only be added after the runner is created.*/
    for (int i = 1; suites[i] != NULL; ++i) {
        srunner_add_suite(runner, suites[i]);
    }

    // Run all tests in normal mode
    srunner_run_all(runner, CK_NORMAL);

    // Get the number of failed tests
    int failed = srunner_ntests_failed(runner);

    // Clean up the test runner
    srunner_free(runner);

    // Return 1 if any tests failed, 0 otherwise
    if (failed) {
        return 1;
    }
    return 0;
}
