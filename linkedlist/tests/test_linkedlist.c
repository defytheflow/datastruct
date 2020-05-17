#include "../src/linkedlist.h"

#include <check.h>

#include <stdbool.h>
#include <string.h>

static size_t linkedlist_filist_with_strings(LinkedList* list);

/*
 *                                Construction.
 */

START_TEST(test_linkedlist_create)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(list.data_size, sizeof(char*));
    ck_assert_uint_eq(list.size, 0);
    ck_assert_ptr_eq(list.free_func, NULL);
    ck_assert_ptr_eq(list.head, NULL);

    linkedlist_free(&list);
}
END_TEST

/*
 *                                   Sizeof.
 */

START_TEST(test_linkedlist_sizeof)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    size_t size = sizeof(LinkedList) + linkedlist_size(&list) * sizeof(struct ListNode);
    ck_assert_uint_eq(linkedlist_sizeof(&list), size);

    linkedlist_free(&list);
}
END_TEST

/*
 *                                    Size.
 */

START_TEST(test_linkedlist_size)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(linkedlist_size(&list), 0);
    linkedlist_free(&list);
}
END_TEST

/*
 *                                 Emptiness.
 */

START_TEST(test_linkedlist_is_empty)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(linkedlist_is_empty(&list), true);
    linkedlist_filist_with_strings(&list);
    ck_assert_uint_eq(linkedlist_is_empty(&list), false);

    linkedlist_free(&list);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_linkedlist_get)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    const char* data = "Data";
    linkedlist_push_back(&list, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(&list, linkedlist_size(&list) - 1), data);

    linkedlist_free(&list);
}
END_TEST

START_TEST(test_linkedlist_set)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    linkedlist_filist_with_strings(&list);

    const char* data = "Data";
    linkedlist_set(&list, linkedlist_size(&list) - 1, &data);

    ck_assert_str_eq(*(char**) linkedlist_get(&list, linkedlist_size(&list) - 1), data);

    linkedlist_free(&list);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_linkedlist_push_back)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    size_t num_strings = linkedlist_filist_with_strings(&list);

    const char* data = "Data";
    linkedlist_push_back(&list, &data);

    ck_assert_uint_eq(linkedlist_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&list, linkedlist_size(&list) - 1), data);

    linkedlist_free(&list);
}
END_TEST

START_TEST(test_linkedlist_push_front)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    size_t num_strings = linkedlist_filist_with_strings(&list);

    const char* data = "Data";
    linkedlist_push_front(&list, &data);

    ck_assert_uint_eq(linkedlist_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&list, 0), data);

    linkedlist_free(&list);
}
END_TEST

START_TEST(test_linkedlist_insert)
{
    LinkedList list;
    linkedlist_create(&list, sizeof(char*), NULL);

    size_t num_strings = linkedlist_filist_with_strings(&list);

    const char* data = "Data";
    linkedlist_insert(&list, num_strings / 2, &data);

    ck_assert_uint_eq(linkedlist_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) linkedlist_get(&list, num_strings / 2), data);

    linkedlist_free(&list);
}
END_TEST

/*
 *                                  Removal.
 */

/* START_TEST(test_linkedlist_pop_back) */
/* { */
    /* LinkedList list; */
    /* linkedlist_create(&list, sizeof(char*), NULL); */

/*     const char* data = "Data"; */
/*     linkedlist_push_back(list, &data); */

/*     ck_assert_uint_eq(linkedlist_size(list), 1); */
/*     ck_assert_str_eq(*(char**) linkedlist_pop_back(list), data); */
/*     ck_assert_uint_eq(linkedlist_size(list), 0); */

    /* linkedlist_free(&list); */
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

static size_t linkedlist_filist_with_strings(LinkedList* list)
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
        linkedlist_push_back(list, &strings[i]);

    return sizeof(strings) / sizeof(strings[0]);
}
