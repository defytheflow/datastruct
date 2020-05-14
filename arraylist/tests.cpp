#include "arraylist.h"

#define INIT_CAPACITY  4
#define NOT_FOUND     -1
#define TRUE           1
#define FALSE          0

#include <gtest/gtest.h>

int int_cmp(const void* a_ptr, const void* b_ptr);

/* Constructor */
TEST(ArrayListNewTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(al->size, 0);
    ASSERT_EQ(al->capacity, INIT_CAPACITY);
    ASSERT_EQ(al->data_size, sizeof(int));
    arraylist_del(al);
}

/* Destructor */
TEST(ArrayListDelTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    arraylist_del(al);
    ASSERT_EQ(al->buffer_ptr, (void*)NULL);
}

/* Getters */
TEST(ArrayListDataSizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(al->data_size, arraylist_data_size(al));
    arraylist_del(al);
}

TEST(ArrayListSizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(al->size, arraylist_size(al));
    arraylist_del(al);
}

TEST(ArrayListCapacityTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(al->capacity, arraylist_capacity(al));
    arraylist_del(al);
}

/* State */
TEST(ArrayListIsEmptyTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(arraylist_is_empty(al), TRUE);

    int data = 42;
    arraylist_push_back(al, &data);
    ASSERT_EQ(arraylist_is_empty(al), FALSE);

    arraylist_del(al);
}

TEST(ArrayListIsFullTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < INIT_CAPACITY; ++i) {
        arraylist_push_back(al, &i);
    }

    ASSERT_EQ(arraylist_is_full(al), TRUE);

    arraylist_del(al);
}

TEST(ArrayListIsSortedTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    ASSERT_EQ(arraylist_is_sorted(al, int_cmp), TRUE);

    int data = -56;
    arraylist_push_back(al, &data);

    ASSERT_EQ(arraylist_is_sorted(al, int_cmp), FALSE);

    arraylist_del(al);
}

/* Index operator. */
TEST(ArrayListGetTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int data = 24;
    arraylist_push_back(al, &data);

    ASSERT_EQ(*(int*)arraylist_get(al, 0), data);

    arraylist_del(al);
}

TEST(ArrayListSetTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

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
    ArrayList* al1 = arraylist_new(sizeof(int));
    ArrayList* al2 = arraylist_new(sizeof(int));

    int size = 10;

    for (int i = 0; i < size; ++i) {
        arraylist_push_back(al1, &i);
        arraylist_push_back(al2, &i);
    }

    al1 = arraylist_concat(al1, al2);
    ASSERT_EQ(arraylist_size(al1), size + al2->size);

    for (int i = 0, j = size; j < al1->size; ++i, ++j) {
        ASSERT_EQ(*(int*)arraylist_get(al1, j), *(int*)arraylist_get(al2, i));
    }

    arraylist_del(al1);
    arraylist_del(al2);
}

/* Equals operator. */
TEST(ArrayListEqualsTest, _)
{
    ArrayList* al1 = arraylist_new(sizeof(int));
    ArrayList* al2 = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i) {
        arraylist_push_back(al1, &i);
        arraylist_push_back(al2, &i);
    }

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);

    int data = 24;
    arraylist_push_back(al1, &data);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), FALSE);

    arraylist_del(al1);
    arraylist_del(al2);
}

/* Insertion. */
TEST(ArrayListPushBackTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int data = 24;
    arraylist_push_back(al, &data);

    ASSERT_EQ(arraylist_size(al), 1);
    ASSERT_EQ(*(int*)arraylist_get(al, 0), data);

    arraylist_del(al);
}

TEST(ArrayListInsertTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int size = 10, data = 24;

    for (int i = 0; i < size; ++i) {
        arraylist_push_back(al, &i);
    }

    arraylist_insert(al, 5, &data);

    ASSERT_EQ(arraylist_size(al), size + 1);
    ASSERT_EQ(*(int*)arraylist_get(al, 5), data);

    arraylist_del(al);
}

/* Removal. */
TEST(ArrayListPopTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int size = 10;

    for (int i = 0; i < size; ++i) {
        arraylist_push_back(al, &i);
    }

    int last_elem = *(int*)arraylist_get(al, arraylist_size(al) - 1);

    ASSERT_EQ(*(int*)arraylist_pop(al), last_elem);

    arraylist_del(al);
}

TEST(ArrayListEraseTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int size = 10;

    for (int i = 0; i < size; ++i) {
        arraylist_push_back(al, &i);
    }

    int data = *(int*)arraylist_get(al, 2);
    arraylist_erase(al, 2);

    ASSERT_EQ(arraylist_size(al), size - 1);
    ASSERT_NE(*(int*)arraylist_get(al, 2), data);

    arraylist_del(al);
}

TEST(ArrayListRemoveTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    int size = 2, data = 1;

    for (int i = 0; i < size; ++i) {
        arraylist_push_back(al, &i);
    }

    arraylist_remove(al, &data);

    ASSERT_EQ(arraylist_size(al), size - 1);

    arraylist_del(al);
}

/* Searching. */
TEST(ArrayListLsearchTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    int exist_data = 85;
    ASSERT_EQ(arraylist_lsearch(al, &exist_data), 85);

    int non_exist_data = 1000;
    ASSERT_EQ(arraylist_lsearch(al, &non_exist_data), NOT_FOUND);

    arraylist_del(al);
}

/* Resizing. */
TEST(ArrayListShrinkToFitTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    al = arraylist_shrink_to_fit(al);
    ASSERT_EQ(arraylist_size(al), arraylist_capacity(al));

    arraylist_del(al);
}

TEST(ArrayListResizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    int big_capacity = 1000, small_capacity = 15;

    al = arraylist_resize(al, big_capacity);
    ASSERT_EQ(arraylist_capacity(al), big_capacity);

    al = arraylist_resize(al, small_capacity);

    ASSERT_EQ(arraylist_capacity(al), small_capacity);
    ASSERT_EQ(arraylist_size(al), small_capacity);

    arraylist_del(al);
}

TEST(ArrayListClearTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i) {
        arraylist_push_back(al, &i);
    }

    al = arraylist_clear(al);
    ASSERT_EQ(arraylist_size(al), 0);
    ASSERT_EQ(arraylist_capacity(al), INIT_CAPACITY);

    arraylist_del(al);
}

/* Sorting. */

TEST(ArrayListSortTest, _)
{
    ArrayList* al1 = arraylist_new(sizeof(int));
    ArrayList* al2 = arraylist_new(sizeof(int));

    for (int i = 0; i <= 100; ++i) {
        arraylist_push_back(al1, &i);
    }

    for (int i = 100; i >= 0; --i) {
        arraylist_push_back(al2, &i);
    }

    al2 = arraylist_sort(al2, int_cmp);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);
    ASSERT_EQ(arraylist_is_sorted(al1, int_cmp), TRUE);

    arraylist_del(al1);
    arraylist_del(al2);
}

TEST(ArrayListReverseTest, _)
{
    ArrayList* al1 = arraylist_new(sizeof(int));
    ArrayList* al2 = arraylist_new(sizeof(int));

    for (int i = 0; i <= 100; ++i) {
        arraylist_push_back(al1, &i);
    }

    for (int i = 100; i >= 0; --i) {
        arraylist_push_back(al2, &i);
    }

    al2 = arraylist_reverse(al2);

    ASSERT_EQ(arraylist_equals(al1, al2, int_cmp), TRUE);

    arraylist_del(al1);
    arraylist_del(al2);
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