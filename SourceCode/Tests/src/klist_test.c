//
// Created by XingfengYang on 2020/7/6.
//


#include <klist_test.h>
#include <tests_lib.h>
#include <list.h>


void should_klist_insert() {
    ListNode list;
    ListNode newNode;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode)
    ASSERT_EQ(newNode.prev, &list)
}

void should_klist_remove_node() {
    ListNode list;
    ListNode newNode;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode)
    ASSERT_EQ(newNode.prev, &list)

    ListNode newNode2;
    klist_insert(&newNode, &newNode2);
    ASSERT_EQ(newNode.next, &newNode2)
    ASSERT_EQ(newNode2.prev, &newNode)

    klist_remove_node(&newNode);
    ASSERT_EQ(list.next, &newNode2)
    ASSERT_EQ(newNode2.prev, &list)
}

void should_klist_return_size() {
    ListNode list;
    ListNode newNode;

    klist_insert(&list, &newNode);
    ASSERT_EQ(klist_size(&list), 2)

    ASSERT_EQ(list.next, &newNode)
    ASSERT_EQ(newNode.prev, &list)

    ListNode newNode2;
    klist_insert(&newNode, &newNode2);
    ASSERT_EQ(newNode.next, &newNode2)
    ASSERT_EQ(newNode2.prev, &newNode)
    ASSERT_EQ(klist_size(&newNode2), 3)

    klist_remove_node(&newNode);
    ASSERT_EQ(list.next, &newNode2)
    ASSERT_EQ(newNode2.prev, &list)
    ASSERT_EQ(klist_size(&list), 2)
}
