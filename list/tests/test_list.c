#include "../src/list.h"

#include <check.h>

#include <stdbool.h>
#include <string.h>

static size_t list_fill_with_strings(List* list);

/*
 *                                Construction.
 */

START_TEST(test_list_create)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(list.data_size, sizeof(char*));
    ck_assert_uint_eq(list.size, 0);
    ck_assert_ptr_eq(list.free_func, NULL);
    ck_assert_ptr_eq(list.head, NULL);

    list_free(&list);
}
END_TEST

/*
 *                                   Sizeof.
 */

START_TEST(test_list_sizeof)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    size_t size = sizeof(List) + list_size(&list) * sizeof(struct ListNode);
    ck_assert_uint_eq(list_sizeof(&list), size);

    list_free(&list);
}
END_TEST

/*
 *                                    Size.
 */

START_TEST(test_list_size)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(list_size(&list), 0);
    list_free(&list);
}
END_TEST

/*
 *                                 Emptiness.
 */

START_TEST(test_list_is_empty)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    ck_assert_uint_eq(list_is_empty(&list), true);
    list_fill_with_strings(&list);
    ck_assert_uint_eq(list_is_empty(&list), false);

    list_free(&list);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_list_get)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    const char* data = "Data";
    list_push_back(&list, &data);

    ck_assert_str_eq(*(char**) list_get(&list, list_size(&list) - 1), data);

    list_free(&list);
}
END_TEST

START_TEST(test_list_set)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    list_fill_with_strings(&list);

    const char* data = "Data";
    list_set(&list, list_size(&list) - 1, &data);

    ck_assert_str_eq(*(char**) list_get(&list, list_size(&list) - 1), data);

    list_free(&list);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_list_push_back)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    size_t num_strings = list_fill_with_strings(&list);

    const char* data = "Data";
    list_push_back(&list, &data);

    ck_assert_uint_eq(list_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) list_get(&list, list_size(&list) - 1), data);

    list_free(&list);
}
END_TEST

START_TEST(test_list_push_front)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    size_t num_strings = list_fill_with_strings(&list);

    const char* data = "Data";
    list_push_front(&list, &data);

    ck_assert_uint_eq(list_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) list_get(&list, 0), data);

    list_free(&list);
}
END_TEST

START_TEST(test_list_insert)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    size_t num_strings = list_fill_with_strings(&list);

    const char* data = "Data";
    list_insert(&list, num_strings / 2, &data);

    ck_assert_uint_eq(list_size(&list), num_strings + 1);
    ck_assert_str_eq(*(char**) list_get(&list, num_strings / 2), data);

    list_free(&list);
}
END_TEST

/*
 *                                  Removal.
 */

START_TEST(test_list_pop_back)
{
    List list;
    list_create(&list, sizeof(char*), NULL);

    /* const char* data = "Data"; */
    /* list_push_back(&list, &data); */

    /* ck_assert_uint_eq(list_size(&list), 1); */

    /* char data_ptr[sizeof(char*)]; */
    /* ck_assert_str_eq(*(char**) list_pop_back(&list, data_ptr), data); */

    ck_assert_uint_eq(list_size(&list), 0);

    list_free(&list);
}
END_TEST

Suite *list_suite(void)
{
    Suite* s = suite_create("List");
    TCase* tc_core = tcase_create("Core");

    /* Construction. */
    tcase_add_test(tc_core, test_list_create);

    /* Sizeof. */
    tcase_add_test(tc_core, test_list_sizeof);

    /* Size. */
    tcase_add_test(tc_core, test_list_size);

    /* Emptiness. */
    tcase_add_test(tc_core, test_list_is_empty);

    /* Indexing. */
    tcase_add_test(tc_core, test_list_get);
    tcase_add_test(tc_core, test_list_set);

    /* Insertion. */
    tcase_add_test(tc_core, test_list_push_back);
    tcase_add_test(tc_core, test_list_push_front);
    tcase_add_test(tc_core, test_list_insert);

    /* Removal. */
    tcase_add_test(tc_core, test_list_pop_back);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    Suite* s = list_suite();
    SRunner* runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);

    return 0;
}

static size_t list_fill_with_strings(List* list)
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
        list_push_back(list, &strings[i]);

    return sizeof(strings) / sizeof(strings[0]);
}
