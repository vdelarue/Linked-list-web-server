// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(empty){
    List<int> l1;
    ASSERT_TRUE(l1.empty());

    l1.push_back(7);
    ASSERT_FALSE(l1.empty());

    l1.pop_back();
    ASSERT_TRUE(l1.empty());

    //nice
    l1.push_back(69);
    ASSERT_FALSE(l1.empty());

    l1.pop_front();
    ASSERT_TRUE(l1.empty());
}

TEST(push_front){
    List<int> l69;
    l69.push_front(17);
    l69.push_front(420);
    l69.push_front(69);
    ASSERT_EQUAL(l69.front(), 69);
    ASSERT_EQUAL(l69.back(), 17);
    ASSERT_EQUAL(l69.size(), 3);
}

TEST(push_back){
    List<int> isa;
    isa.push_back(69);
    isa.push_back(420);
    isa.push_back(1);
    isa.push_back(-1);
    isa.push_back(0);
    isa.push_back(30000);

    ASSERT_EQUAL(isa.front(), 69);
    ASSERT_EQUAL(isa.back(), 30000);
    ASSERT_EQUAL(isa.size(), 6);
}


// clear is a private function
// TEST(clear){
//     List<int> vivi;

//     ASSERT_TRUE(vivi.empty());
//     vivi.clear();
//     ASSERT_TRUE(vivi.empty());

//     vivi.push_front(69);
//     vivi.push_back(420);    
//     vivi.push_front(420);
//     vivi.clear();
//     ASSERT_TRUE(vivi.empty());
// }

TEST(pop_front){
    List<int> joshua;
    joshua.push_front(10);
    ASSERT_TRUE(!joshua.empty());
    joshua.pop_front();
    ASSERT_TRUE(joshua.empty());

    joshua.push_back(12);
    joshua.push_back(15);
    joshua.push_back(69);
    ASSERT_EQUAL(joshua.front(), 12);
    joshua.pop_front();
    ASSERT_EQUAL(joshua.front(), 15);
    joshua.pop_front();
    //nice
    ASSERT_EQUAL(joshua.front(), 69);
}

TEST(pop_back){
    List<int> biden;
    biden.push_back(69);
    ASSERT_FALSE(biden.empty());
    biden.pop_back();
    ASSERT_TRUE(biden.empty());

    biden.push_back(12);
    biden.push_front(69);
    biden.push_back(86);
    ASSERT_EQUAL(biden.back(), 86);
    biden.pop_back();
    ASSERT_EQUAL(biden.back(), 12);
    biden.pop_back();
    ASSERT_EQUAL(biden.back(), 69);
}

TEST(assignment_constructor_list){
    List<int> list1;
    list1.push_front(12);
    list1.push_back(8);

    List<int> isa;
    isa.push_back(69);
    isa.push_back(-23);
    isa.push_back(0);
    isa  = list1;
    List<int>::Iterator it1 = list1.begin();
    List<int>::Iterator itsa = isa.begin();
    for (int i = 0; i < 2; i++){
        ASSERT_EQUAL(*it1, *itsa);
        ++it1;
        ++itsa;
    }
}

TEST(copy_constructor_list){
    List<int> list1;
    list1.push_back(-38);
    list1.push_back(-38);
    list1.push_back(-7);
    list1.push_back(23);
     
    List<int> list2 = list1;
    List<int>::Iterator it1 = list1.begin();
    List<int>::Iterator it2 = list2.begin();
    for (int i = 0; i < list1.size(); i++){
        ASSERT_EQUAL(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(string_list){
    List<string> list1;
    ASSERT_TRUE(list1.empty());
    list1.push_back("Joshua");
    list1.push_front("Isa");
    list1.pop_front();
    list1.pop_back();
    list1.push_back("Olivia");
    list1.push_back("Juliette");
    list1.push_back("Carine");
    ASSERT_EQUAL(list1.size(), 3);

    List<string> list2 = list1;
    List<string>::Iterator it1 = list1.begin();
    List<string>::Iterator it2 = list2.begin();
    for (int i = 0; i < list1.size(); i++){
        ASSERT_EQUAL(*it1, *it2);
        ++it1;
        ++it2;
    }

    List<string> list3;
    list3.push_back("Carmen");
    list3 = list1;
    List<string>::Iterator it3 = list3.begin();
    it1 = list1.begin();
    for (int i = 0; i < list1.size(); i++){
        ASSERT_EQUAL(*it1, *it3);
        ++it1;
        ++it3;
    }
}

TEST_MAIN();
