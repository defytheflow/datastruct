#include "../src/arraylist.h"

#include <check.h>

#include <stdbool.h>

#define INIT_CAPACITY  4
#define NOT_FOUND     -1
#define SIZE          100

static void arraylist_fill_up_to(ArrayList* al, int limit);

static int int_cmp(const void*, const void*);

/*
 *                                Construction.
 */

START_TEST(test_arraylist_create)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    ck_assert_uint_eq(al->data_size, sizeof(int));
    ck_assert_uint_eq(al->size, 0);
    ck_assert_uint_eq(al->capacity, 4);
    ck_assert_ptr_eq(al->free_func, NULL);

    arraylist_free(al);
}
END_TEST

/*
 *                              Field Accessing.
 */

START_TEST(test_arraylist_data_size)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);
    ck_assert_uint_eq(arraylist_data_size(al), sizeof(int));
    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_size)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);
    ck_assert_uint_eq(arraylist_size(al), 0);
    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_capacity)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);
    ck_assert_uint_eq(arraylist_capacity(al), INIT_CAPACITY);
    arraylist_free(al);
}
END_TEST

/*
 *                                   State.
 */

START_TEST(test_arraylist_is_empty)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    ck_assert_uint_eq(arraylist_is_empty(al), true);
    arraylist_fill_up_to(al, 100);
    ck_assert_uint_eq(arraylist_is_empty(al), false);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_is_full)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, INIT_CAPACITY);
    ck_assert_uint_eq(arraylist_is_full(al), true);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_is_sorted)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, 100);
    ck_assert_uint_eq(arraylist_is_sorted(al, int_cmp), true);

    arraylist_free(al);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_arraylist_get)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    ck_assert_int_eq(*(int*) arraylist_get(al, 0), data);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_set)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    int new_data = 25;
    arraylist_set(al, 0, &new_data);

    ck_assert_int_eq(*(int*) arraylist_get(al, 0), new_data);

    arraylist_free(al);
}
END_TEST

/*
 *                               Concatenation.
 */

START_TEST(test_arraylist_concat)
{
    ArrayList* al1 = arraylist_create(sizeof(int), NULL);
    ArrayList* al2 = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al1, SIZE);
    arraylist_fill_up_to(al2, SIZE);

    al1 = arraylist_concat(al1, al2);
    ck_assert_int_eq(arraylist_size(al1), SIZE + SIZE);

    for (int i = 0, j = SIZE; j < SIZE; ++i, ++j)
        ck_assert_int_eq(*(int*) arraylist_get(al1, j), *(int*) arraylist_get(al2, i));

    arraylist_free(al1);
    arraylist_free(al2);
}
END_TEST

/*
 *                                  Equality.
 */

START_TEST(test_arraylist_equals)
{
    ArrayList* al1 = arraylist_create(sizeof(int), NULL);
    ArrayList* al2 = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al1, SIZE);
    arraylist_fill_up_to(al2, SIZE);

    ck_assert_int_eq(arraylist_equals(al1, al2, int_cmp), true);

    int data = 24;
    arraylist_push_back(al1, &data);

    ck_assert_int_eq(arraylist_equals(al1, al2, int_cmp), false);

    arraylist_free(al1);
    arraylist_free(al2);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_arraylist_push_back)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    ck_assert_uint_eq(arraylist_size(al), 1);
    ck_assert_int_eq(*(int*) arraylist_get(al, 0), data);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_insert)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);

    int data = 24;
    arraylist_insert(al, 5, &data);

    ck_assert_uint_eq(arraylist_size(al), SIZE + 1);
    ck_assert_int_eq(*(int*) arraylist_get(al, 5), data);

    arraylist_free(al);
}
END_TEST

/*
 *                                  Removal.
 */

START_TEST(test_arraylist_pop_back)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);
    int last_elem = *(int*) arraylist_get(al, arraylist_size(al) - 1);
    ck_assert_int_eq(*(int*) arraylist_pop_back(al), last_elem);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_erase)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);

    int data = *(int*) arraylist_get(al, 2);

    arraylist_erase(al, 2);

    ck_assert_int_eq(arraylist_size(al), SIZE - 1);
    ck_assert_int_ne(*(int*) arraylist_get(al, 2), data);

    arraylist_free(al);
}
END_TEST

/*
 *                                   Resize.
 */

START_TEST(test_arraylist_resize)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);

    al = arraylist_resize(al, 1000);
    ck_assert_uint_eq(arraylist_capacity(al), 1000);

    al = arraylist_resize(al, 10);

    ck_assert_uint_eq(arraylist_capacity(al), 10);
    ck_assert_uint_eq(arraylist_size(al), 10);

    arraylist_free(al);
}
END_TEST

START_TEST(test_arraylist_shrink_to_fit)
{

    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);
    al = arraylist_shrink_to_fit(al);
    ck_assert_uint_eq(arraylist_size(al), arraylist_capacity(al));

    arraylist_free(al);

}
END_TEST

START_TEST(test_arraylist_clear)
{
    ArrayList* al = arraylist_create(sizeof(int), NULL);

    arraylist_fill_up_to(al, SIZE);
    al = arraylist_clear(al);
    ck_assert_uint_eq(arraylist_size(al), 0);
    ck_assert_uint_eq(arraylist_capacity(al), INIT_CAPACITY);

    arraylist_free(al);
}
END_TEST

/*
 *                                 Reversion.
 */

START_TEST(test_arraylist_reverse)
{
    ArrayList* al1 = arraylist_create(sizeof(int), NULL);
    ArrayList* al2 = arraylist_create(sizeof(int), NULL);

    for (int i = 0; i <= SIZE; ++i)
        arraylist_push_back(al1, &i);

    for (int i = SIZE; i >= 0; --i) {
        arraylist_push_back(al2, &i);
    }

    al2 = arraylist_reverse(al2);
    ck_assert_int_eq(arraylist_equals(al1, al2, int_cmp), true);

    arraylist_free(al1);
    arraylist_free(al2);
}
END_TEST

Suite *arraylist_suite(void)
{
    Suite* s = suite_create("ArrayList");
    TCase* tc_core = tcase_create("Core");

    /* Construction. */
    tcase_add_test(tc_core, test_arraylist_create);

    /* Field accessing. */
    tcase_add_test(tc_core, test_arraylist_data_size);
    tcase_add_test(tc_core, test_arraylist_size);
    tcase_add_test(tc_core, test_arraylist_capacity);

    /* State. */
    tcase_add_test(tc_core, test_arraylist_is_empty);
    tcase_add_test(tc_core, test_arraylist_is_full);
    tcase_add_test(tc_core, test_arraylist_is_sorted);

    /* Indexing. */
    tcase_add_test(tc_core, test_arraylist_get);
    tcase_add_test(tc_core, test_arraylist_set);

    /* Concatenation. */
    tcase_add_test(tc_core, test_arraylist_concat);

    /* Equality. */
    tcase_add_test(tc_core, test_arraylist_equals);

    /* Insertion. */
    tcase_add_test(tc_core, test_arraylist_push_back);
    tcase_add_test(tc_core, test_arraylist_insert);

    /* Removal. */
    tcase_add_test(tc_core, test_arraylist_pop_back);
    tcase_add_test(tc_core, test_arraylist_erase);

    tcase_add_test(tc_core, test_arraylist_resize);
    tcase_add_test(tc_core, test_arraylist_shrink_to_fit);
    tcase_add_test(tc_core, test_arraylist_clear);

    tcase_add_test(tc_core, test_arraylist_reverse);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    Suite* s = arraylist_suite();
    SRunner* runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);

    return 0;
}

static int int_cmp(const void* a_ptr, const void* b_ptr)
{
    int a_val = *(int*)a_ptr;
    int b_val = *(int*)b_ptr;

    if (a_val < b_val) return -1;
    else if (a_val > b_val) return 1;
    else return 0;
}

static void arraylist_fill_up_to(ArrayList* al, int limit)
{
    for (int i = 0; i < limit; ++i)
        arraylist_push_back(al, &i);
}
