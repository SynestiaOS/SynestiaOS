//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KLIST_TEST_H__
#define __KERNEL_KLIST_TEST_H__

#include <list.h>

void should_klist_insert()
{
    ListNode list;
    list.prev = nullptr;
    list.next = nullptr;

    ListNode newNode;
    newNode.prev = nullptr;
    newNode.next = nullptr;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode);
    ASSERT_EQ(newNode.prev, &list);
}

void should_klist_append()
{
    ListNode list;
    list.prev = nullptr;
    list.next = nullptr;

    ListNode newNode;
    newNode.prev = nullptr;
    newNode.next = nullptr;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode);
    ASSERT_EQ(newNode.prev, &list);

    ListNode newNode2;
    newNode2.prev = nullptr;
    newNode2.next = nullptr;
    klist_append(&list, &newNode2);

    ASSERT_EQ(list.next, &newNode);
    ASSERT_EQ(newNode.prev, &list);
    ASSERT_EQ(newNode.next, &newNode2);
    ASSERT_EQ(newNode2.prev, &newNode);
}

void should_klist_remove_node()
{
    ListNode list;
    list.prev = nullptr;
    list.next = nullptr;

    ListNode newNode;
    newNode.prev = nullptr;
    newNode.next = nullptr;

    klist_insert(&list, &newNode);

    ASSERT_EQ(list.next, &newNode);
    ASSERT_EQ(newNode.prev, &list);

    ListNode newNode2;
    newNode2.prev = nullptr;
    newNode2.next = nullptr;
    klist_insert(&newNode, &newNode2);
    ASSERT_EQ(newNode.next, &newNode2);
    ASSERT_EQ(newNode2.prev, &newNode);

    klist_remove_node(&newNode);
    ASSERT_EQ(list.next, &newNode2);
    ASSERT_EQ(newNode2.prev, &list);
}

void should_klist_return_size()
{
    ListNode list;
    list.prev = nullptr;
    list.next = nullptr;

    ListNode newNode;
    newNode.prev = nullptr;
    newNode.next = nullptr;

    klist_insert(&list, &newNode);
    ASSERT_EQ(klist_size(&list), 2);

    ASSERT_EQ(list.next, &newNode);
    ASSERT_EQ(newNode.prev, &list);

    ListNode newNode2;
    newNode2.prev = nullptr;
    newNode2.next = nullptr;
    klist_insert(&newNode, &newNode2);
    ASSERT_EQ(newNode.next, &newNode2);
    ASSERT_EQ(newNode2.prev, &newNode);
    ASSERT_EQ(klist_size(&list), 3);

    klist_remove_node(&newNode);
    ASSERT_EQ(list.next, &newNode2);
    ASSERT_EQ(newNode2.prev, &list);
    ASSERT_EQ(klist_size(&list), 2);
}

#endif //__KERNEL_KLIST_TEST_H__
