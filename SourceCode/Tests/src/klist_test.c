//
// Created by XingfengYang on 2020/7/6.
//


#include <klist_test.h>
#include <tests_lib.h>
#include <stdbool.h>
#include <list.h>


void should_klist_insert() {
    ListNode list;
    ASSERT_EQ(list.next, nullptr)
    ASSERT_EQ(list.prev, nullptr)

    ListNode newNode;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode)
    ASSERT_EQ(newNode.prev, &list)
}

void should_klist_remove_node() {
    //todo:
    ASSERT_TRUE(false)
}

void should_klist_return_size() {
    //todo:
    ASSERT_TRUE(false)
}
