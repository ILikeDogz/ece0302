#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.hpp"

typedef BinarySearchTree<int, int> TreeType;

TEST_CASE("Test Construction", "[construction]") {
    TreeType bst1;

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("Test Insert", "[insert]") {
    TreeType bst1;

    bst1.insert(10, 10);
    REQUIRE(!bst1.isEmpty());
}

TEST_CASE("Test Duplicate Insert", "[duplicate insert]") {
    TreeType bst1;
    
    bst1.insert(12, 12);
    REQUIRE(!bst1.insert(12, 12));
}

TEST_CASE("Test Insert 2", "[insert]") {
    TreeType bst1;

    for(int i = -5; i < 10; i++){ //test negatives and 0
        bst1.insert(i, i);
    }
    REQUIRE(!bst1.isEmpty());

    for(int i = -5; i < 10; i++){ //all duplicates
        REQUIRE_FALSE(bst1.insert(i, i));
    }
}

TEST_CASE("Test Retrieve", "[retrieve]") {
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;
    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(10, item));
}

TEST_CASE("Test Retrieve 2", "[insert]") {
    TreeType bst1;

    for(int i = -5; i < 10; i++){ //test negatives and 0
        bst1.insert(i, i);
    }
    REQUIRE(!bst1.isEmpty());
    int item;
    for(int i = -5; i < 10; i++){ //test negatives and 0
        bst1.retrieve(i, item);
    }

}

TEST_CASE("Test Remove", "[remove]") {
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;
    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(10, item));

    bst1.remove(12);
    REQUIRE(!bst1.retrieve(12, item));

    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(10, item));
    bst1.remove(18);
    REQUIRE(!bst1.retrieve(18, item));

    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(10, item));
    bst1.remove(5);
    REQUIRE(!bst1.retrieve(5, item));

    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(10, item));
    
    bst1.remove(10);
    REQUIRE(!bst1.retrieve(10, item));
    REQUIRE(bst1.retrieve(15, item));
    bst1.remove(15);
    REQUIRE(!bst1.retrieve(15, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("Test Remove 2", "[remove]") {
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;

    //simple remove
    bst1.remove(12);
    REQUIRE(!bst1.retrieve(12, item));

    //remove 2 children
    bst1.remove(15);
    REQUIRE(!bst1.retrieve(15, item));

    //remove leaf
    bst1.remove(18);
    REQUIRE(!bst1.retrieve(18, item));

    //remove node
    bst1.remove(10);
    REQUIRE(!bst1.retrieve(10, item));

    //empty Remove
    TreeType emptyBST;
    REQUIRE(!emptyBST.remove(5)); 

    //remove invalid item
    REQUIRE(!bst1.remove(20));

    bst1.insert(8, 8);
    bst1.insert(2, 2);
    bst1.insert(20, 20);

    //remove one child node
    bst1.remove(5);
    REQUIRE(!bst1.retrieve(5, item));

    //remove one child node
    bst1.remove(8);
    REQUIRE(!bst1.retrieve(8, item));

    //remove root
    bst1.remove(10);
    REQUIRE(!bst1.retrieve(10, item));

    //remove leaf
    bst1.remove(2);
    REQUIRE(!bst1.retrieve(2, item));

    //remove last node
    bst1.remove(20);
    REQUIRE(!bst1.retrieve(20, item));

    REQUIRE(bst1.isEmpty());


    //remove from single node tree
    TreeType singleNodeBST;
    singleNodeBST.insert(100, 100);
    singleNodeBST.remove(100);
    REQUIRE(singleNodeBST.isEmpty());

    //multiple repeated nodes, only one should be inserted
    TreeType sameKeyBST;
    sameKeyBST.insert(5, 5);
    sameKeyBST.insert(5, 5);
    sameKeyBST.insert(5, 5);
    sameKeyBST.insert(5, 5);
    sameKeyBST.insert(5, 5);
    sameKeyBST.remove(5);
    REQUIRE(sameKeyBST.isEmpty());

    //negative numbers
    TreeType negativeKeyBST;
    negativeKeyBST.insert(-10, -10);
    negativeKeyBST.insert(-5, -5);
    negativeKeyBST.insert(-15, -15);
    negativeKeyBST.remove(-5);
    REQUIRE(!negativeKeyBST.retrieve(-5, item));
}


TEST_CASE("Test Copy Assign", "[copy assign]") {
    TreeType bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;

    bst2 = bst1;

    REQUIRE(!bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE(!bst2.retrieve(51, item));
    
}


TEST_CASE("Test sort", "[treeSort]") {
    TreeType bst1;
    int size = 10;
    int my_array[size] = {9,8,7,6,5,4,3,2,1,0};

    bst1.treeSort(my_array, size);

    for(int i = 1; i < size; i++){
        REQUIRE(my_array[i-1] <= my_array[i]);
    }

    TreeType bst2;
    int my_array2[size] = {9,0,2,6,3,5,4,2,7,1};

    bst2.treeSort(my_array2, size);

    for(int i = 1; i < size; i++){
        REQUIRE(my_array[i-1] <= my_array[i]);
    }

    TreeType bst3;
    int my_array_dupes[size] = {9,0,2,6,3,5,4,2,7,0};
    int my_array_dupes2[size] = {9,0,2,6,3,5,4,2,7,0};
    bst1.treeSort(my_array_dupes, size);

    for(int i = 1; i < size; i++){
        REQUIRE(my_array_dupes[i] == my_array_dupes2[i]); //does not change
    }
}
