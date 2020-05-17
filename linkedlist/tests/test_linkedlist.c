#include "../src/linkedlist.h"

#include <check.h>

#include <stdbool.h>
#include <string.h>

static size_t linkedlist_fill_with_strings(LinkedList* ll);


/*
 *                                Construction.
 */

START_TEST(test_linkedlist_create)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    ck_assert_uint_eq(ll->data_size, sizeof(char*));
    ck_assert_uint_eq(ll->size, 0);
    ck_assert_ptr_eq(ll->free_func, NULL);
    ck_assert_ptr_eq(ll->head, NULL);

    linkedlist_free(ll);
}
END_TEST

/*
 *                              Field Accessing.
 */

START_TEST(test_linkedlist_data_size)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);
    ck_assert_uint_eq(linkedlist_data_size(ll), sizeof(char*));
    linkedlist_free(ll);
}
END_TEST

START_TEST(test_linkedlist_size)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);
    ck_assert_uint_eq(linkedlist_size(ll), 0);
    linkedlist_free(ll);
}
END_TEST

/*
 *                                   State.
 */

START_TEST(test_linkedlist_is_empty)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    ck_assert_uint_eq(linkedlist_is_empty(ll), true);
    linkedlist_fill_with_strings(ll);
    ck_assert_uint_eq(linkedlist_is_empty(ll), false);

    linkedlist_free(ll);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_linkedlist_get)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    const char* data = "Data";
    linkedlist_push_back(ll, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(ll, linkedlist_size(ll) - 1), data);

    linkedlist_free(ll);
}
END_TEST

START_TEST(test_linkedlist_set)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    linkedlist_fill_with_strings(ll);

    const char* data = "Data";
    linkedlist_set(ll, linkedlist_size(ll) - 1, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(ll, linkedlist_size(ll) - 1), data);

    linkedlist_free(ll);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_linkedlist_push_back)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(ll);

    const char* data = "Data";
    linkedlist_push_back(ll, &data);

    ck_assert_uint_eq(linkedlist_size(ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(ll, linkedlist_size(ll) - 1), data);

    linkedlist_free(ll);
}
END_TEST

START_TEST(test_linkedlist_push_front)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(ll);

    const char* data = "Data";
    linkedlist_push_front(ll, &data);

    ck_assert_uint_eq(linkedlist_size(ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(ll, 0), data);

    linkedlist_free(ll);
}
END_TEST

START_TEST(test_linkedlist_insert)
{
    LinkedList* ll = linkedlist_create(sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(ll);

    const char* data = "Data";
    linkedlist_insert(ll, num_strings / 2, &data);

    ck_assert_uint_eq(linkedlist_size(ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(ll, num_strings / 2), data);

    linkedlist_free(ll);
}
END_TEST

/*
 *                                  Removal.
 */

Suite *linkedlist_suite(void)
{
    Suite* s = suite_create("LinkedList");
    TCase* tc_core = tcase_create("Core");

    /* Construction. */
    tcase_add_test(tc_core, test_linkedlist_create);

    /* Field accessing. */
    tcase_add_test(tc_core, test_linkedlist_size);
    tcase_add_test(tc_core, test_linkedlist_data_size);

    /* State. */
    tcase_add_test(tc_core, test_linkedlist_is_empty);

    /* Indexing. */
    tcase_add_test(tc_core, test_linkedlist_get);
    tcase_add_test(tc_core, test_linkedlist_set);

    /* Insertion. */
    tcase_add_test(tc_core, test_linkedlist_push_back);
    tcase_add_test(tc_core, test_linkedlist_push_front);
    tcase_add_test(tc_core, test_linkedlist_insert);

    /* Removal. */

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    Suite* s = linkedlist_suite();
    SRunner* runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);

    return 0;
}

static size_t linkedlist_fill_with_strings(LinkedList* ll)
{
    static const char* strings[] = {
        "Very",
        "Interesting",
        "Strings",
        "Over",
        "Here,",
        "Lads!",
    };

    for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); ++i)
        linkedlist_push_back(ll, &strings[i]);

    return sizeof(strings) / sizeof(strings[0]);
}
