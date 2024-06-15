#include "utils/hash_map.h"

/**
 * This function uses the modular value of the ID to 
 * compute the hashmap bucket index.
 */
int hash_fn(int id){
    return id % MAX_BUCKET_SIZE;
}

/**
 * Finds an object in the hashamp. First compute the bucket index,
 * then lookup in the bucket linked list for the searched item. 
 */
void* hash_map_find(int id, HashMap* map){

    if(map == NULL) return NULL;
    HashValue* bucket_ptr = map->buckets[hash_fn(id)];

    do{
        if(bucket_ptr == NULL){
            return NULL;
        }

        if(bucket_ptr->id == id){
            return  bucket_ptr->value;
        }

        bucket_ptr = bucket_ptr->next;
    }while(bucket_ptr != NULL);

    return NULL;
}

/**
 * Inserts an object in the HashMap, from the head of the bucket's linked list.
 */
bool hash_map_insert(int id, void* value, HashMap* map){
    
    if(map == NULL) return 0;

    int bucket_id = hash_fn(id);
    
    HashValue* bucket_ptr = map->buckets[bucket_id];
    HashValue* new_bucket_ptr = (HashValue*)malloc(sizeof(HashValue));
    
    new_bucket_ptr->id = id;
    new_bucket_ptr->value = value;
    new_bucket_ptr->next = bucket_ptr;

    map->buckets[bucket_id] = new_bucket_ptr;

    return 1;
}

/**
 * @brief Get the parent of a HashValue in the HashMap.
 * 
 * @param id ID of the object to find in the HashMap.
 * @param map HashMap to search in
 * @return HashValue* The parent pointer of the HashValue.
 * Example: 
 *   NULL -> &hv1 -> &hv2 -> &hv3 -> NULL
 *   Executing this function for hv2 will return &hv1.
 * 
 */
static HashValue* __get_parent_hash_value_ptr(int id, HashMap* map){
    if(map == NULL) return NULL;

    HashValue* bucket_ptr = map->buckets[hash_fn(id)];
    HashValue* parent_ptr = NULL;

    do{
        if(bucket_ptr == NULL){
            return NULL;
        }

        if(bucket_ptr->id == id){
            return  parent_ptr;
        }

        parent_ptr = bucket_ptr;
        bucket_ptr = bucket_ptr->next;
    }while(bucket_ptr != NULL);

    return NULL;
}

/**
 * Removes an item from the HashMap. Deletes the item in the linked list and
 * link its parent to the child of the node to delete.
 */
bool hash_map_remove(int id, HashMap* map, bool deallocate){
    if(map == NULL) return 0;

    HashValue* bucket_ptr = map->buckets[hash_fn(id)];
    HashValue* found = NULL;

    while(bucket_ptr != NULL && found == NULL){

        if(bucket_ptr->id == id){
            found = bucket_ptr;
            break;
        }

        bucket_ptr = bucket_ptr->next;
    }

    if(found == NULL){
        return 0;
    }

    HashValue* parent_ptr = __get_parent_hash_value_ptr(id, map);

    if(parent_ptr != NULL){
        parent_ptr->next = found->next;
    }

    if(deallocate){
        free(found->value);
    }

    free(found);

    return 1;
}

static void __free_bucket(HashValue* bucket, HashMap* map){
    if(bucket == NULL){
        return;
    }
    HashValue* next_to_remove = bucket->next;
    hash_map_remove(bucket->id, map, false);
    __free_bucket(next_to_remove, map);
}

void free_hash_map(HashMap* map){
    
    for(int i = 0; i < MAX_BUCKET_SIZE; i++){
        __free_bucket(map->buckets[i], map);
    }
}