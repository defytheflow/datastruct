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
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    ck_assert_uint_eq(ll.data_size, sizeof(char*));
    ck_assert_uint_eq(ll.size, 0);
    ck_assert_ptr_eq(ll.free_func, NULL);
    ck_assert_ptr_eq(ll.head, NULL);

    linkedlist_free(&ll);
}
END_TEST

/*
 *                                   Sizeof.
 */

START_TEST(test_linkedlist_sizeof)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    size_t size = sizeof(LinkedList) + linkedlist_size(&ll) * sizeof(struct LLNode);
    ck_assert_uint_eq(linkedlist_sizeof(&ll), size);

    linkedlist_free(&ll);
}
END_TEST

/*
 *                                    Size.
 */

START_TEST(test_linkedlist_size)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    ck_assert_uint_eq(linkedlist_size(&ll), 0);
    linkedlist_free(&ll);
}
END_TEST

/*
 *                                 Emptiness.
 */

START_TEST(test_linkedlist_is_empty)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    ck_assert_uint_eq(linkedlist_is_empty(&ll), true);
    linkedlist_fill_with_strings(&ll);
    ck_assert_uint_eq(linkedlist_is_empty(&ll), false);

    linkedlist_free(&ll);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_linkedlist_get)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    const char* data = "Data";
    linkedlist_push_back(&ll, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(&ll, linkedlist_size(&ll) - 1), data);

    linkedlist_free(&ll);
}
END_TEST

START_TEST(test_linkedlist_set)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    linkedlist_fill_with_strings(&ll);

    const char* data = "Data";
    linkedlist_set(&ll, linkedlist_size(&ll) - 1, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(&ll, linkedlist_size(&ll) - 1), data);

    linkedlist_free(&ll);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_linkedlist_push_back)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(&ll);

    const char* data = "Data";
    linkedlist_push_back(&ll, &data);

    ck_assert_uint_eq(linkedlist_size(&ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&ll, linkedlist_size(&ll) - 1), data);

    linkedlist_free(&ll);
}
END_TEST

START_TEST(test_linkedlist_push_front)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(&ll);

    const char* data = "Data";
    linkedlist_push_front(&ll, &data);

    ck_assert_uint_eq(linkedlist_size(&ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&ll, 0), data);

    linkedlist_free(&ll);
}
END_TEST

START_TEST(test_linkedlist_insert)
{
    LinkedList ll;
    linkedlist_create(&ll, sizeof(char*), NULL);

    size_t num_strings = linkedlist_fill_with_strings(&ll);

    const char* data = "Data";
    linkedlist_insert(&ll, num_strings / 2, &data);

    ck_assert_uint_eq(linkedlist_size(&ll), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&ll, num_strings / 2), data);

    linkedlist_free(&ll);
}
END_TEST

/*
 *                                  Removal.
 */

/* START_TEST(test_linkedlist_pop_back) */
/* { */
    /* LinkedList ll; */
    /* linkedlist_create(&ll, sizeof(char*), NULL); */

/*     const char* data = "Data"; */
/*     linkedlist_push_back(ll, &data); */

/*     ck_assert_uint_eq(linkedlist_size(ll), 1); */
/*     ck_assert_str_eq(*(char**) linkedlist_pop_back(ll), data); */
/*     ck_assert_uint_eq(linkedlist_size(ll), 0); */

    /* linkedlist_free(&ll); */
/* } */
/* END_TEST */

Suite *linkedlist_suite(void)
{
    Suite* s = suite_create("LinkedList");
    TCase* tc_core = tcase_create("Core");

    /* Construction. */
    tcase_add_test(tc_core, test_linkedlist_create);

    /* Sizeof. */
    tcase_add_test(tc_core, test_linkedlist_sizeof);

    /* Size. */
    tcase_add_test(tc_core, test_linkedlist_size);

    /* Emptiness. */
    tcase_add_test(tc_core, test_linkedlist_is_empty);

    /* Indexing. */
    tcase_add_test(tc_core, test_linkedlist_get);
    tcase_add_test(tc_core, test_linkedlist_set);

    /* Insertion. */
    tcase_add_test(tc_core, test_linkedlist_push_back);
    tcase_add_test(tc_core, test_linkedlist_push_front);
    tcase_add_test(tc_core, test_linkedlist_insert);

    /* Removal. */
    /* tcase_add_test(tc_core, test_linkedlist_pop_back); */

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
