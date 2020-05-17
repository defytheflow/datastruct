#include "../src/vector.h"

#include <check.h>

#include <stdbool.h>

#define INIT_CAPACITY  4

static void vector_fill_up_to(Vector* v, int limit);
static int int_cmp(const void*, const void*);

/*
 *                                Construction.
 */

START_TEST(test_vector_create)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    ck_assert_uint_eq(v.data_size, sizeof(int));
    ck_assert_uint_eq(v.size, 0);
    ck_assert_uint_eq(v.capacity, INIT_CAPACITY);
    ck_assert_ptr_eq(v.free_func, NULL);

    vector_free(&v);
}
END_TEST

/*
 *                               Size/Capacity.
 */

START_TEST(test_vector_size)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    ck_assert_uint_eq(vector_size(&v), 0);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_capacity)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    ck_assert_uint_eq(vector_capacity(&v), INIT_CAPACITY);

    vector_free(&v);
}
END_TEST

/*
 *                             Emptiness/Fullness.
 */

START_TEST(test_vector_is_empty)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    ck_assert_uint_eq(vector_is_empty(&v), true);
    vector_fill_up_to(&v, 100);
    ck_assert_uint_eq(vector_is_empty(&v), false);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_is_full)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, INIT_CAPACITY);
    ck_assert_uint_eq(vector_is_full(&v), true);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_is_sorted)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);
    ck_assert_uint_eq(vector_is_sorted(&v, int_cmp), true);

    vector_free(&v);
}
END_TEST

/*
 *                                  Indexing.
 */

START_TEST(test_vector_get)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    int data = 24;
    vector_push_back(&v, &data);

    ck_assert_int_eq(*(int*) vector_get(&v, 0), data);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_set)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    int data = 24;
    vector_push_back(&v, &data);

    int new_data = 25;
    vector_set(&v, 0, &new_data);

    ck_assert_int_eq(*(int*) vector_get(&v, 0), new_data);

    vector_free(&v);
}
END_TEST

/*
 *                               Concatenation.
 */

START_TEST(test_vector_concat)
{
    Vector v1, v2;
    vector_create(&v1, sizeof(int), NULL);
    vector_create(&v2, sizeof(int), NULL);

    vector_fill_up_to(&v1, 100);
    vector_fill_up_to(&v2, 100);

    vector_concat(&v1, &v2);
    ck_assert_int_eq(vector_size(&v1), 200);

    for (int i = 0, j = 100; j < 100; ++i, ++j)
        ck_assert_int_eq(*(int*) vector_get(&v1, j), *(int*) vector_get(&v2, i));

    vector_free(&v1);
    vector_free(&v2);
}
END_TEST

/*
 *                                  Equality.
 */

START_TEST(test_vector_equals)
{
    Vector v1, v2;
    vector_create(&v1, sizeof(int), NULL);
    vector_create(&v2, sizeof(int), NULL);

    vector_fill_up_to(&v1, 100);
    vector_fill_up_to(&v2, 100);

    ck_assert_int_eq(vector_equals(&v1, &v2, int_cmp), true);

    int data = 24;
    vector_push_back(&v1, &data);

    ck_assert_int_eq(vector_equals(&v1, &v2, int_cmp), false);

    vector_free(&v1);
    vector_free(&v2);
}
END_TEST

/*
 *                                 Insertion.
 */

START_TEST(test_vector_push_back)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    int data = 24;
    vector_push_back(&v, &data);

    ck_assert_uint_eq(vector_size(&v), 1);
    ck_assert_int_eq(*(int*) vector_get(&v, 0), data);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_insert)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    int data = 24;
    vector_insert(&v, 5, &data);

    ck_assert_uint_eq(vector_size(&v), 101);
    ck_assert_int_eq(*(int*) vector_get(&v, 5), data);

    vector_free(&v);
}
END_TEST

/*
 *                                  Removal.
 */

START_TEST(test_vector_pop_back)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    int last_elem = *(int*) vector_get(&v, vector_size(&v) - 1);
    ck_assert_int_eq(*(int*) vector_pop_back(&v), last_elem);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_erase)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    int data = *(int*) vector_get(&v, 2);

    vector_erase(&v, 2);

    ck_assert_int_eq(vector_size(&v), 99);
    ck_assert_int_ne(*(int*) vector_get(&v, 2), data);

    vector_free(&v);
}
END_TEST

/*
 *                                   Resize.
 */

START_TEST(test_vector_resize)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    vector_resize(&v, 1000);
    ck_assert_uint_eq(vector_capacity(&v), 1000);

    vector_resize(&v, 10);

    ck_assert_uint_eq(vector_capacity(&v), 10);
    ck_assert_uint_eq(vector_size(&v), 10);

    vector_free(&v);
}
END_TEST

START_TEST(test_vector_shrink_to_fit)
{

    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    vector_shrink_to_fit(&v);
    ck_assert_uint_eq(vector_size(&v), vector_capacity(&v));

    vector_free(&v);

}
END_TEST

START_TEST(test_vector_clear)
{
    Vector v;
    vector_create(&v, sizeof(int), NULL);

    vector_fill_up_to(&v, 100);

    vector_clear(&v);
    ck_assert_uint_eq(vector_size(&v), 0);
    ck_assert_uint_eq(vector_capacity(&v), INIT_CAPACITY);

    vector_free(&v);
}
END_TEST

/*
 *                                 Reversion.
 */

START_TEST(test_vector_reverse)
{
    Vector v1, v2;
    vector_create(&v1, sizeof(int), NULL);
    vector_create(&v2, sizeof(int), NULL);

    for (int i = 0; i <= 100; ++i)
        vector_push_back(&v1, &i);

    for (int i = 100; i >= 0; --i) {
        vector_push_back(&v2, &i);
    }

    vector_reverse(&v2);
    ck_assert_int_eq(vector_equals(&v1, &v2, int_cmp), true);

    vector_free(&v1);
    vector_free(&v2);
}
END_TEST

Suite *vector_suite(void)
{
    Suite* s = suite_create("Vector");
    TCase* tc_core = tcase_create("Core");

    /* Construction. */
    tcase_add_test(tc_core, test_vector_create);

    /* Field accessing. */
    tcase_add_test(tc_core, test_vector_size);
    tcase_add_test(tc_core, test_vector_capacity);

    /* State. */
    tcase_add_test(tc_core, test_vector_is_empty);
    tcase_add_test(tc_core, test_vector_is_full);
    tcase_add_test(tc_core, test_vector_is_sorted);

    /* Indexing. */
    tcase_add_test(tc_core, test_vector_get);
    tcase_add_test(tc_core, test_vector_set);

    /* Concatenation. */
    tcase_add_test(tc_core, test_vector_concat);

    /* Equality. */
    tcase_add_test(tc_core, test_vector_equals);

    /* Insertion. */
    tcase_add_test(tc_core, test_vector_push_back);
    tcase_add_test(tc_core, test_vector_insert);

    /* Removal. */
    tcase_add_test(tc_core, test_vector_pop_back);
    tcase_add_test(tc_core, test_vector_erase);

    /* Resize. */
    tcase_add_test(tc_core, test_vector_resize);
    tcase_add_test(tc_core, test_vector_shrink_to_fit);
    tcase_add_test(tc_core, test_vector_clear);

    /* Reversion. */
    tcase_add_test(tc_core, test_vector_reverse);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    Suite* s = vector_suite();
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

static void vector_fill_up_to(Vector* v, int limit)
{
    for (int i = 0; i < limit; ++i)
        vector_push_back(v, &i);
}
