#include "data_structures/linked_list_tests.hpp"
#include <string>
#include "test_utils/test_group.hpp"

bool linkedListTestDefaultConstructor() {
    bool result = true;

    LinkedList<int> int_list;
    result &= (int_list.data == 0);
    result &= (!int_list.next);

    return result;
}

bool linkedListTestDataConstructor() {
    bool result = true;

    LinkedList<int> int_list(4);
    result &= (int_list.data == 4);
    result &= (!int_list.next);

    LinkedList<char> char_list('a');
    result &= (char_list.data == 'a');
    result &= (!char_list.next);

    return result;
}

bool linkedListTestFullConstructor() {
    bool result = true;

    // We don't call delete because temp is linked to int_list
    // int_list is allocated on the stack, so it automatically gets destroyed
    LinkedList<int>* temp = new LinkedList<int>(5);
    LinkedList<int> int_list(4, temp);
    result &= (int_list.data == 4);
    result &= (int_list.next->data == 5);

    return result;
}

bool linkedListTestCopyConstructor() {
    bool result = true;

    LinkedList<int> one_next(4, new LinkedList<int>(5));
    LinkedList<int> one_next_copy(one_next);
    result &= (one_next_copy.data == one_next.data);
    result &= (one_next_copy.next->data == one_next.next->data);
    result &= (&one_next_copy != &one_next);
    result &= (&one_next_copy.next != &one_next.next);

    LinkedList<int> two_next(4, new LinkedList<int>(3, new LinkedList<int>(6)));
    LinkedList<int> two_next_copy(two_next);
    result &= (two_next_copy.data == two_next.data);
    result &= (two_next_copy.next->data == two_next.next->data);

    result &= (&two_next_copy != &two_next);
    result &= (&two_next_copy.next != &two_next.next);

    result &= (two_next_copy.next->data == two_next.next->data);
    result &= (two_next_copy.next->next->data == two_next.next->next->data);

    result &= (&two_next_copy != &two_next);
    result &= (&two_next_copy.next != &two_next.next);
    result &= (&two_next_copy.next->next != &two_next.next->next);

    return result;
}

bool linkedListTestAssignmentOperator() {
    bool result = true;

    LinkedList<int> original(4, new LinkedList<int>(5));
    LinkedList<int> assigned = original;
    result &= (assigned.data == original.data);
    result &= (assigned.next->data == original.next->data);

    return result;
}

bool linkedListTestInsertAtTail() {
    bool result = true;

    LinkedList<int>* init_as_empty = nullptr;
    result &= !init_as_empty;
    linkedListInsertAtTail(&init_as_empty, 4);
    result &= init_as_empty->data == 4;
    result &= !init_as_empty->next;
    delete init_as_empty;

    LinkedList<int>* not_empty = new LinkedList<int>(4);
    linkedListInsertAtTail(&not_empty, 5);
    result &= not_empty->next->data == 5;
    result &= !not_empty->next->next;
    delete not_empty;

    return result;
}

bool linkedListTestInsertAtHead() {
    bool result = true;

    LinkedList<int>* init_as_empty = nullptr;
    result &= !init_as_empty;
    linkedListInsertAtHead(&init_as_empty, 6);
    result &= (init_as_empty->data == 6);
    result &= !init_as_empty->next;
    delete init_as_empty;

    LinkedList<int>* not_empty = new LinkedList<int>(8);
    linkedListInsertAtHead(&not_empty, 7);
    result &= not_empty->data == 7;
    result &= not_empty->next->data == 8;
    delete not_empty;

    return result;
}

bool linkedListTestGetLength() {
    bool result = true;

    LinkedList<int>* empty_list = nullptr;
    result &= linkedListGetLength(empty_list) == 0;

    LinkedList<int>* non_empty = new LinkedList<int>(5, new LinkedList<int>(2));
    result &= linkedListGetLength(non_empty) == 2;
    delete non_empty;

    return result;
}

bool linkedListTestFindNthOccurrence() {
    bool result = true;

    LinkedList<char>* not_found = new LinkedList<char>('a');
    LinkedList<char>* not_found_result =
        linkedListFindNthOccurrence(not_found, 'b', 1);
    result &= !not_found_result;
    delete not_found;

    LinkedList<int>* not_enough = new LinkedList<int>(3);
    linkedListInsertAtTail(&not_enough, 3);
    linkedListInsertAtTail(&not_enough, 5);
    LinkedList<int>* not_enough_result =
        linkedListFindNthOccurrence(not_enough, 3, 3);
    result &= !not_enough_result;
    delete not_enough;

    LinkedList<std::string>* found_one = new LinkedList<std::string>("5");
    linkedListInsertAtTail(&found_one, std::string("4"));
    LinkedList<std::string>* found_one_result =
        linkedListFindNthOccurrence(found_one, std::string("5"), 1);
    result &= found_one_result == found_one;
    delete found_one;

    return result;
}

void linkedListTestsRegisterTests(TestManager* test_manager) {
    TestGroup test_group("linked lists");
    testGroupAddTest(&test_group,
        UnitTest("default constructor", linkedListTestDefaultConstructor));
    testGroupAddTest(&test_group,
        UnitTest("data constructor", linkedListTestDataConstructor));
    testGroupAddTest(&test_group,
        UnitTest("full constructor", linkedListTestFullConstructor));
    testGroupAddTest(&test_group,
        UnitTest("copy constructor", linkedListTestCopyConstructor));
    testGroupAddTest(&test_group,
        UnitTest("assignment operator", linkedListTestAssignmentOperator));
    testGroupAddTest(&test_group,
        UnitTest("insert at tail", linkedListTestInsertAtTail));
    testGroupAddTest(&test_group,
        UnitTest("insert at head", linkedListTestInsertAtHead));
    testGroupAddTest(&test_group,
        UnitTest("length", linkedListTestGetLength));
    testGroupAddTest(&test_group,
        UnitTest("find nth occurrence", linkedListTestFindNthOccurrence));
    test_manager->test_groups.push_back(test_group);
}
