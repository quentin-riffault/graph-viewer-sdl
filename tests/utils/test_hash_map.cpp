extern "C" {
    #include "utils/hash_map.h"
}

#include <gtest/gtest.h>

class HashMapTest : public testing::Test {
protected:
    HashMapTest(){
        map_not_empty.buckets[0] = NULL;

        hash_map_insert(MAX_BUCKET_SIZE*0, &relevant_data, &map_not_empty);
        hash_map_insert(MAX_BUCKET_SIZE*1, NULL, &map_not_empty);
        hash_map_insert(MAX_BUCKET_SIZE*2, NULL, &map_not_empty);

    }

    ~HashMapTest(){
        free_hash_map(&map_empty);
        free_hash_map(&map_not_empty);
    }
    
    HashMap map_empty;
    HashMap map_not_empty;

    int relevant_data = 5;

};

// ===================================================================================================================
// hash_fn tests 
//==================================================================================================================== 

TEST(HashFunction, Computation){
    EXPECT_EQ(19%MAX_BUCKET_SIZE, hash_fn(19));
}

// ===================================================================================================================
// hash_map_find tests 
//==================================================================================================================== 

TEST_F(HashMapTest, CanFind_empty_map){
    EXPECT_EQ(NULL,             hash_map_find(MAX_BUCKET_SIZE*0, &map_empty));
}

TEST_F(HashMapTest, CanFind_NULL_map){
    EXPECT_EQ(NULL,             hash_map_find(MAX_BUCKET_SIZE*0, NULL));
}

TEST_F(HashMapTest, CanFind_not_empty_map){
    EXPECT_EQ(&relevant_data,   hash_map_find(MAX_BUCKET_SIZE*0, &map_not_empty));
    EXPECT_EQ(NULL,             hash_map_find(MAX_BUCKET_SIZE*1, &map_not_empty));
}

// ===================================================================================================================
// hash_map_insert tests 
//==================================================================================================================== 

TEST_F(HashMapTest, CanInsert){
    float myvalue = 12.0f;
    
    EXPECT_EQ(1, hash_map_insert(
        MAX_BUCKET_SIZE*3,
        (void*)(&myvalue),
        &map_not_empty
    ));

    EXPECT_EQ(0, hash_map_insert(
        0,
        NULL,
        NULL
    ));

    EXPECT_EQ(true, hash_map_insert(
        MAX_BUCKET_SIZE*4,
        NULL,
        &map_not_empty
    ));

    EXPECT_EQ(&myvalue, hash_map_find(MAX_BUCKET_SIZE*3, &map_not_empty));
    EXPECT_EQ(NULL, hash_map_find(MAX_BUCKET_SIZE*4, &map_not_empty));
}

// ===================================================================================================================
// hash_map_remove tests 
//==================================================================================================================== 


TEST_F(HashMapTest, CanRemove_no_deallocate){

    float* myvalue = (float*)malloc(sizeof(float));
    *myvalue = 5.0f;
    float* previous_value = myvalue;
    int another_value = 3;

    EXPECT_EQ(1, hash_map_insert(
        MAX_BUCKET_SIZE*3,
        (void*)(myvalue),
        &map_not_empty
    ));

    EXPECT_EQ(1, hash_map_insert(
        MAX_BUCKET_SIZE*4,
        (void*)(&another_value),
        &map_not_empty
    ));

    EXPECT_EQ(1, hash_map_remove(
        MAX_BUCKET_SIZE*3,
        &map_not_empty,
        false
    ));

    EXPECT_EQ(previous_value, myvalue);

    EXPECT_EQ(
        &another_value, 
        hash_map_find(MAX_BUCKET_SIZE*4, &map_not_empty)
    ) << "Removal of a node broke the linked list. \n";

    EXPECT_EQ(
        NULL, 
        hash_map_find(MAX_BUCKET_SIZE*3, &map_not_empty)
    );


    free(myvalue);

}

TEST_F(HashMapTest, CanRemove_deallocate){

    float* myvalue = (float*)malloc(sizeof(float));
    float* previous_value = myvalue;

    EXPECT_EQ(1, hash_map_insert(
        MAX_BUCKET_SIZE*3,
        (void*)(myvalue),
        &map_not_empty
    ));

    EXPECT_EQ(1, hash_map_remove(
        MAX_BUCKET_SIZE*3,
        &map_not_empty,
        true
    ));
}

TEST_F(HashMapTest, CanRemove_not_found){

    EXPECT_EQ(0, hash_map_remove(
        0,
        NULL,
        false
    ));

    EXPECT_EQ(0, hash_map_remove(
        MAX_BUCKET_SIZE*10,
        &map_empty,
        false
    ));
}


