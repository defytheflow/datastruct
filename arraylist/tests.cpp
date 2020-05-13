#include "arraylist.h"

#include <gtest/gtest.h>

/* Constructor */
TEST(ArrayListNewTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));
    ASSERT_EQ(al->size, 0);
    ASSERT_EQ(al->capacity, 4);
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
    ASSERT_EQ(arraylist_is_empty(al), 1);
    arraylist_del(al);
}

TEST(ArrayListIsFullTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 4; ++i) {
        arraylist_push_back(al, &i);
    }

    ASSERT_EQ(arraylist_is_full(al), 1);

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

    for (int i = 0; i < 10; ++i)
        arraylist_push_back(al, &i);

    int data = 24;
    arraylist_insert(al, 5, &data);

    ASSERT_EQ(arraylist_size(al), 11);
    ASSERT_EQ(*(int*)arraylist_get(al, 5), data);

    arraylist_del(al);
}

/* Removal. */
// TODO bad tests rewrite.
TEST(ArrayListPopTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i)
        arraylist_push_back(al, &i);

    ASSERT_EQ(*(int*)arraylist_pop(al), 9);

    arraylist_del(al);
}

// TODO bad tests rewrite.
TEST(ArrayListEraseTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i)
        arraylist_push_back(al, &i);

    arraylist_erase(al, 2);
    ASSERT_EQ(arraylist_size(al), 9);
    ASSERT_NE(*(int*)arraylist_get(al, 2), 2);

    arraylist_del(al);
}

// TODO bad tests rewrite.
TEST(ArrayListRemoveTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 10; ++i)
        arraylist_push_back(al, &i);

    int data = 8;
    arraylist_remove(al, &data);
    ASSERT_EQ(arraylist_size(al), 9);
    ASSERT_NE(*(int*)arraylist_get(al, 8), 8);

    arraylist_del(al);
}

/* Searching. */
TEST(ArrayListLsearchTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    int good_needle = 85;
    ASSERT_EQ(arraylist_lsearch(al, &good_needle), 85);

    int bad_needle = 1000;
    ASSERT_EQ(arraylist_lsearch(al, &bad_needle), -1);

    arraylist_del(al);
}

/* Resizing. */
TEST(ArrayListShrinkToFitTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_shrink_to_fit(al);
    ASSERT_EQ(arraylist_size(al), arraylist_capacity(al));

    arraylist_del(al);
}

TEST(ArrayListResizeTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_resize(al, 1000);
    ASSERT_EQ(arraylist_capacity(al), 1000);

    al = arraylist_resize(al, 10);

    ASSERT_EQ(arraylist_capacity(al), 10);
    ASSERT_EQ(arraylist_size(al), 10);

    arraylist_del(al);
}

TEST(ArrayListClearTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 0; i < 100; ++i)
        arraylist_push_back(al, &i);

    al = arraylist_clear(al);
    ASSERT_EQ(arraylist_size(al), 0);
    ASSERT_EQ(arraylist_capacity(al), 4);

    arraylist_del(al);
}


/* Sorting. */

int int_cmp(const void* a_ptr, const void* b_ptr)
{
    int a_val = *(int*)a_ptr;
    int b_val = *(int*)b_ptr;

    if (a_val < b_val) return -1;
    else if (a_val > b_val) return 1;
    else return 0;
}

TEST(ArrayListSortTest, _)
{
    ArrayList* al = arraylist_new(sizeof(int));

    for (int i = 100; i >= 0; --i)
        arraylist_push_back(al, &i);

    al = arraylist_sort(al, int_cmp);

    ASSERT_EQ(*(int*)arraylist_get(al, 0), 0);
    ASSERT_EQ(*(int*)arraylist_get(al, arraylist_size(al) - 1), 100);

    arraylist_del(al);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}