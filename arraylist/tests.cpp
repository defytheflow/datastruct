#include "arraylist.h"

#include <gtest/gtest.h>

#define INIT_CAPACITY  4
#define NOT_FOUND     -1
#define TRUE           1
#define FALSE          0

int int_cmp(const void*, const void*);

/* Constructor */
TEST(ArrayListNewTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    ASSERT_EQ(al->data_size, sizeof(int));
    ASSERT_EQ(al->size, 0);
    ASSERT_EQ(al->capacity, INIT_CAPACITY);
    ASSERT_EQ(al->free_func, (void*) NULL);

    arraylist_del(al);
}

/* Fields. */

TEST(ArrayListDataSizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    ASSERT_EQ(al->data_size, arraylist_data_size(al));

    arraylist_del(al);
}

TEST(ArrayListSizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    ASSERT_EQ(al->size, arraylist_size(al));

    arraylist_del(al);
}

TEST(ArrayListCapacityTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    ASSERT_EQ(al->capacity, arraylist_capacity(al));

    arraylist_del(al);
}

/* State. */

TEST(ArrayListIsEmptyTest, TrueWhenEmpty)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    ASSERT_EQ(arraylist_is_empty(al), TRUE);

    arraylist_del(al);
}

TEST(ArrayListIsEmptyTest, FalseWhenNotEmpty)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < 25; ++i)
        arraylist_push_back(al, &i);

    ASSERT_EQ(arraylist_is_empty(al), FALSE);

    arraylist_del(al);
}

TEST(ArrayListIsFullTest, TrueWhenFull)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < INIT_CAPACITY; ++i)
        arraylist_push_back(al, &i);

    ASSERT_EQ(arraylist_is_full(al), TRUE);

    arraylist_del(al);
}

TEST(ArrayListIsFullTest, FalseWhenNotFull)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < INIT_CAPACITY - 1; ++i)
        arraylist_push_back(al, &i);

    ASSERT_EQ(arraylist_is_full(al), FALSE);

    arraylist_del(al);
}

TEST(ArrayListIsSortedTest, TrueWhenSorted)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    ASSERT_EQ(arraylist_is_sorted(al, int_cmp), TRUE);

    arraylist_del(al);
}

TEST(ArrayListIsSortedTest, FalseWhenNotSorted)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    int data = -56;
    arraylist_push_back(al, &data);

    ASSERT_EQ(arraylist_is_sorted(al, int_cmp), FALSE);

    arraylist_del(al);
}

/* Index operator. */

TEST(ArrayListGetTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    ASSERT_EQ(*(int*) arraylist_get(al, 0), data);

    arraylist_del(al);
}

TEST(ArrayListSetTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    int new_data = 25;
    arraylist_set(al, 0, &new_data);

    ASSERT_EQ(*(int*)arraylist_get(al, 0), new_data);

    arraylist_del(al);
}

/* Concatenation operator. */

TEST(ArrayListConcatTest, _)
{
#define SIZE 100
    ArrayList* al1 = arraylist_new(sizeof(int), NULL);
    ArrayList* al2 = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i) {
        arraylist_push_back(al1, &i);
        arraylist_push_back(al2, &i);
    }

    al1 = arraylist_concat(al1, al2);

    ASSERT_EQ(arraylist_size(al1), SIZE + SIZE);

    for (int i = 0, j = SIZE; j < SIZE; ++i, ++j)
        ASSERT_EQ(*(int*) arraylist_get(al1, j), *(int*) arraylist_get(al2, i));

    arraylist_del(al1);
    arraylist_del(al2);
#undef SIZE
}

/* Equals operator. */

TEST(ArrayListEqualsTest, TrueWhenArraysAreEqual)
{
#define SIZE 100
    ArrayList* al1 = arraylist_new(sizeof(int), NULL);
    ArrayList* al2 = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i) {
        arraylist_push_back(al1, &i);
        arraylist_push_back(al2, &i);
    }

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);

    arraylist_del(al1);
    arraylist_del(al2);
#undef SIZE
}

TEST(ArrayListEqualsTest, FalseWhenArraysAreDifferent)
{
#define SIZE 100
    ArrayList* al1 = arraylist_new(sizeof(int), NULL);
    ArrayList* al2 = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i) {
        arraylist_push_back(al1, &i);
        arraylist_push_back(al2, &i);
    }

    int data = 24;
    arraylist_push_back(al1, &data);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), FALSE);

    arraylist_del(al1);
    arraylist_del(al2);
#undef SIZE
}

/* Insert. */

TEST(ArrayListPushBackTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    int data = 24;
    arraylist_push_back(al, &data);

    ASSERT_EQ(arraylist_size(al), 1);
    ASSERT_EQ(*(int*) arraylist_get(al, 0), data);

    arraylist_del(al);
}

TEST(ArrayListInsertTest, _)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int data = 24;
    arraylist_insert(al, 5, &data);

    ASSERT_EQ(arraylist_size(al), SIZE + 1);
    ASSERT_EQ(*(int*) arraylist_get(al, 5), data);

    arraylist_del(al);
#undef SIZE
}

/* Remove. */

TEST(ArrayListPopTest, _)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int last_elem = *(int*) arraylist_get(al, arraylist_size(al) - 1);

    ASSERT_EQ(*(int*)arraylist_pop(al), last_elem);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListEraseTest, _)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int data = *(int*) arraylist_get(al, 2);

    arraylist_erase(al, 2);

    ASSERT_EQ(arraylist_size(al), SIZE - 1);
    ASSERT_NE(*(int*) arraylist_get(al, 2), data);

    arraylist_del(al);
#undef SIZE
}

/* Search. */

TEST(ArrayListLsearchTest, DataExists)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int exist_data = 85;
    ASSERT_EQ(arraylist_lsearch(al, &exist_data, int_cmp), 85);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListLsearchTest, DataDoesntExist)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int non_exist_data = 1000;
    ASSERT_EQ(arraylist_lsearch(al, &non_exist_data, int_cmp), NOT_FOUND);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListBsearchTest, DataExists)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    int exist_data = 85;
    ASSERT_EQ(arraylist_bsearch(al, &exist_data, int_cmp), 85);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListBsearchTest, DataDoesntExist)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    int non_exist_data = 1000;
    ASSERT_EQ(arraylist_bsearch(al, &non_exist_data, int_cmp), NOT_FOUND);

    arraylist_del(al);
#undef SIZE
}

/* Resize. */

TEST(ArrayListResizeTest, ResizeMore)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_resize(al, 1000);
    ASSERT_EQ(arraylist_capacity(al), 1000);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListResizeTest, ResizeLess)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_resize(al, 10);

    ASSERT_EQ(arraylist_capacity(al), 10);
    ASSERT_EQ(arraylist_size(al), 10);

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListShrinkToFitTest, _)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_shrink_to_fit(al);

    ASSERT_EQ(arraylist_size(al), arraylist_capacity(al));

    arraylist_del(al);
#undef SIZE
}

TEST(ArrayListClearTest, _)
{
#define SIZE 100
    ArrayList* al = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i < SIZE; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_clear(al);

    ASSERT_EQ(arraylist_size(al), 0);
    ASSERT_EQ(arraylist_capacity(al), INIT_CAPACITY);

    arraylist_del(al);
#undef SIZE
}

/* Sort. */

TEST(ArrayListSortTest, _)
{
#define SIZE 100
    ArrayList* al1 = arraylist_new(sizeof(int), NULL);
    ArrayList* al2 = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i <= SIZE; ++i)
        arraylist_push_back(al1, &i);

    for (int i = SIZE; i >= 0; --i)
        arraylist_push_back(al2, &i);

    al2 = arraylist_sort(al2, int_cmp);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);
    ASSERT_EQ(arraylist_is_sorted(al1, int_cmp), TRUE);

    arraylist_del(al1);
    arraylist_del(al2);
#undef SIZE
}

/* Reverse. */

TEST(ArrayListReverseTest, _)
{
#define SIZE 100
    ArrayList* al1 = arraylist_new(sizeof(int), NULL);
    ArrayList* al2 = arraylist_new(sizeof(int), NULL);

    for (int i = 0; i <= SIZE; ++i)
        arraylist_push_back(al1, &i);

    for (int i = SIZE; i >= 0; --i) {
        arraylist_push_back(al2, &i);
    }

    al2 = arraylist_reverse(al2);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);

    arraylist_del(al1);
    arraylist_del(al2);
#undef SIZE
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int int_cmp(const void* a_ptr, const void* b_ptr)
{
    int a_val = *(int*)a_ptr;
    int b_val = *(int*)b_ptr;

    if (a_val < b_val) return -1;
    else if (a_val > b_val) return 1;
    else return 0;
}
