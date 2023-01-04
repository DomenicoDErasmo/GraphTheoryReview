#include "graph_tests.hpp"
#include <data_structures/graph.cpp>

bool graphTestDefaultConstructor() {
    bool result = true;

    Graph<int> empty;
    result &= !empty.adjacency_matrix;

    return result;
}

/**
 * @brief Helper function for the file path constructor.
 * 
 * @param graph The graph to check
 * @param node The node to check
 * @param length The expected length of the node's adjacency list
 * @param n The edge within the adjacency list to check
 * @param to The expected to value of the nth edge
 * @return true if all checks succeed, otherwise false 
 */
bool graphTestFilePathConstructorHelper(
        const Graph<int>& graph,
        int node,
        int length,
        int n,
        int to) {
    bool result = true;
    AdjacencyList<int> adj_list = linkedListGetNthOccurrence(
        graph.adjacency_matrix,
        AdjacencyList<int>(node),
        1,
        adjacencyListWeakEquality)->data;
    if (length == -1) {
        result &= !adj_list.edges;
    }
    else {
        result &= linkedListGetLength(adj_list.edges) == length;
        result &= linkedListGetNthNode(adj_list.edges, n)->data.to == to;
    }
    return result;
}

bool graphTestFilePathConstructor() {
    bool result = true;

    Graph<int> directed("../resources/test_graph.txt", GRAPH_DIRECTED);
    result &= linkedListGetLength(directed.adjacency_matrix) == 10;
    result &= graphTestFilePathConstructorHelper(directed, 0, -1, 0, -1);
    result &= graphTestFilePathConstructorHelper(directed, 1, 1, 0, 2);
    result &= graphTestFilePathConstructorHelper(directed, 3, 2, 0, 4);
    result &= graphTestFilePathConstructorHelper(directed, 3, 2, 1, 5);
    result &= graphTestFilePathConstructorHelper(directed, 4, 1, 0, 5);
    result &= graphTestFilePathConstructorHelper(directed, 6, 2, 0, 7);
    result &= graphTestFilePathConstructorHelper(directed, 6, 2, 1, 9);
    result &= graphTestFilePathConstructorHelper(directed, 8, 2, 0, 7);
    result &= graphTestFilePathConstructorHelper(directed, 8, 2, 1, 9);

    Graph<int> undirected("../resources/test_graph.txt", GRAPH_UNDIRECTED);
    result &= graphTestFilePathConstructorHelper(undirected, 5, 2, 0, 3);
    result &= graphTestFilePathConstructorHelper(undirected, 5, 2, 1, 4);

    return result;
}

bool graphTestCopyConstructor() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy(original);
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_matrix, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy = original;
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_matrix, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestEqualityOperator() {
    bool result = true;

    Graph<int> inequal_lhs;
    linkedListInsertAtTail(
        &inequal_lhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &inequal_lhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            inequal_lhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4));
    Graph<int> inequal_rhs;
    linkedListInsertAtTail(
        &inequal_rhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &inequal_rhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            inequal_rhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4, 1.1));
    result &= !(inequal_lhs == inequal_rhs);

    Graph<int> equal_lhs;
    linkedListInsertAtTail(
        &equal_lhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &equal_lhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            equal_lhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4));
    Graph<int> equal_rhs;
    linkedListInsertAtTail(&equal_rhs.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&equal_rhs.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            equal_rhs.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    result &= equal_lhs == equal_rhs;
    return result;
}

bool graphTestGetNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphGetNode(node_not_found, 4);

    Graph<int> node_found;
    linkedListInsertAtTail(&node_found.adjacency_matrix, AdjacencyList<int>(5));
    LinkedList<AdjacencyList<int>>* list = graphGetNode(node_found, 5);
    result &= list->data.from == 5;

    return result;
}

bool graphTestHasNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphHasNode(node_not_found, 5);

    Graph<int> node_found;
    result &= !node_found.adjacency_matrix;
    linkedListInsertAtTail(
        &node_found.adjacency_matrix, 
        AdjacencyList<int>(5));
    result &= graphHasNode(node_found, 5);

    return result;
}

bool graphTestAddNode() {
    bool result = true;

    Graph<int> can_insert;
    result &= !can_insert.adjacency_matrix;
    graphAddNode(can_insert, 4);
    result &= can_insert.adjacency_matrix->data == 4;

    Graph<int> already_found;
    result &= !already_found.adjacency_matrix;
    linkedListInsertAtTail(
        &already_found.adjacency_matrix, 
        AdjacencyList<int>(5));
    result &= linkedListGetLength(already_found.adjacency_matrix) == 1;
    graphAddNode(already_found, 5);
    result &= linkedListGetLength(already_found.adjacency_matrix) == 1;

    return result;
}

bool graphTestGetEdge() {
    bool result = true;

    Graph<int> adj_list_not_found;
    try {
        graphGetEdge(adj_list_not_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> has_edge;
    graphAddNode(has_edge, 4);
    LinkedList<AdjacencyList<int>>* adj_list = graphGetNode(has_edge, 4);
    linkedListInsertAtTail(&adj_list->data.edges, Edge<int>(4, 5));
    LinkedList<Edge<int>>* edge = graphGetEdge(has_edge, Edge<int>(4, 5));
    result &= edge->data.to == 5;
    result &= edge == adj_list->data.edges;
    edge->data.to = 3;
    result &= adj_list->data.edges->data.to == 3;

    return result;
}

bool graphTestHasEdge() {
    bool result = true;

    Graph<int> missing_node;
    result &= !graphHasEdge(missing_node, Edge<int>(4, 5));

    Graph<int> missing_edge;
    graphAddNode(missing_edge, 4);
    result &= !graphHasEdge(missing_node, Edge<int>(4, 5));

    Graph<int> has_edge;
    graphAddNode(has_edge, 4);
    graphAddEdge(has_edge, Edge<int>(4, 5));
    result &= graphHasEdge(has_edge, Edge<int>(4, 5));

    return result;
}

bool graphTestAddEdge() {
    bool result = true;

    Graph<int> adj_list_not_found;
    try {
        graphAddEdge(adj_list_not_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> edge_found;
    graphAddNode(edge_found, 4);
    linkedListInsertAtTail(
        &edge_found.adjacency_matrix->data.edges, 
        Edge<int>(4, 3));
    try {
        graphAddEdge(edge_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> found;
    graphAddNode(found, 4);
    graphAddEdge(found, Edge<int>(4, 5, 1.2));
    result &= found.adjacency_matrix->data.edges->data == Edge<int>(4, 5, 1.2);

    return result;
}

void graphTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("graph");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        graphTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("file path constructor", 
        graphTestFilePathConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        graphTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator", 
        graphTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        graphTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("get node", graphTestGetNode));
    testGroupAddTest(&test_group, UnitTest("has node", graphTestHasNode));
    testGroupAddTest(&test_group, UnitTest("add node", graphTestAddNode));
    testGroupAddTest(&test_group, UnitTest("get edge", graphTestGetEdge));
    testGroupAddTest(&test_group, UnitTest("has edge", graphTestHasEdge));
    testGroupAddTest(&test_group, UnitTest("add edge", graphTestAddEdge));

    testManagerAddTestGroup(test_manager, test_group);
}
