#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP

#include "linked_list.cpp"
#include "queue.cpp"

/**
 * @brief Binary tree implementation
 * 
 * @tparam T The type of the binary tree's data
 */
template <typename T>
struct BinaryTree {
    // Fields
    T data;
    BinaryTree<T>* left;
    BinaryTree<T>* right;

    // Constructors
    // TODO: remove full param constructor
    BinaryTree(): data(T()), left(nullptr), right(nullptr) {}
    BinaryTree(const T& data): data(data), left(nullptr), right(nullptr) {}
    BinaryTree(
            const T& data, 
            BinaryTree<T>* const& left, 
            BinaryTree<T>* const& right): 
        data(data), left(left), right(right) {}
    BinaryTree(const BinaryTree<T>& other) {
        data = other.data;
        left = other.left ? new BinaryTree<T>(*other.left) : nullptr;
        right = other.right ? new BinaryTree<T>(*other.right) : nullptr;
    }

    // Destructors
    ~BinaryTree() {
        delete left;
        delete right;
    }

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom
     * discussed in the Linked List file
     * 
     * @param rhs The binary tree to copy
     * @return BinaryTree<T>& A copied binary tree
     */
    BinaryTree<T>& operator = (BinaryTree<T> rhs) {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Checks equality of two binary trees
     * 
     * @param lhs The first binary tree to check
     * @param rhs The second binary tree to check
     * @return true if the trees are equal, otherwise false
     */
    friend bool operator == (BinaryTree<T>& lhs, BinaryTree<T>& rhs) {
        if ((lhs.data != rhs.data)
        || (lhs.left && !rhs.left) 
        || (!lhs.left && rhs.left) 
        || (lhs.right && !rhs.right)
        || (!lhs.right && rhs.right)) {return false;}

        bool result = true;

        if (lhs.left && rhs.left) {result &= *lhs.left == *rhs.left;}
        if (lhs.right && rhs.right) {result &= *lhs.right == *rhs.right;}

        return result;
    }

    /**
     * @brief Checks inequality of two binary trees
     * 
     * @param lhs The first binary tree to check
     * @param rhs The second binary tree to check
     * @return true if the trees are inequal, otherwise false 
     */
    friend bool operator != (BinaryTree<T>& lhs, BinaryTree<T>& rhs) {
        return !(lhs == rhs);
    }

    // Utility Functions

    /**
     * @brief Swaps the provided binary trees
     * 
     * @param first The first binary tree to swap
     * @param second The second binary tree to swap
     */
    friend void swap(BinaryTree<T>& first, BinaryTree<T>& second) {
        // enables ADL - we could use namespaces to change functionality
        using std::swap;

        swap(first.data, second.data);
        swap(first.left, second.left);
        swap(first.right, second.right);
    }
};

/**
 * @brief Helper function to get height of tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @param level The current level of the tree
 * @return int The total height of the tree
 */
template <typename T>
int binaryTreeGetHeightHelper(BinaryTree<T>* const& tree, int level) {
    if (!tree) {return level;}
    int left = binaryTreeGetHeightHelper(tree->left, level + 1);
    int right = binaryTreeGetHeightHelper(tree->right, level + 1);
    return left > right ? left : right;
}

/**
 * @brief Gets the height of the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @return int The total height of the tree
 */
template <typename T>
int binaryTreeGetHeight(BinaryTree<T>* const& tree) {
    return binaryTreeGetHeightHelper(tree, 0);
}

/**
 * @brief Gets the total number of nodes in the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @return int The total number of nodes in the tree
 */
template <typename T>
int binaryTreeGetNumNodes(BinaryTree<T>* const& tree) {
    if (!tree) {return 0;}
    return 1 + binaryTreeGetNumNodes(tree->left) 
             + binaryTreeGetNumNodes(tree->right);
}

/**
 * @brief Helper function to insert a node into the tree
 * 
 * @tparam T The type of the tree's data
 * @param node The node to insert a value for
 * @param data The data to insert into the tree
 */
template <typename T>
void binaryTreeInsertNodeHelper(BinaryTree<T>** node, T data) {
    if (*node) {binaryTreeInsertNode(node, data);} 
    else {*node = new BinaryTree<T>(data);}
}

/**
 * @brief Inserts a node into the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @param data The data to insert into the tree
 */
template <typename T>
void binaryTreeInsertNode(BinaryTree<T>** tree, T data) {
    if (!*tree) {*tree = new BinaryTree<T>(data);}
    T node_data = (*tree)->data;
    if (node_data == data) {return;}
    BinaryTree<T>** next = data < node_data ? &(*tree)->left : &(*tree)->right;
    binaryTreeInsertNodeHelper(next, data);
}

/**
 * @brief Gets preorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The preorder of the tree
 */
template <typename T>
LinkedList<T>* binaryTreeGetPreorder(BinaryTree<T>* const& tree) {
    if (!tree) {return nullptr;}
    LinkedList<T>* result = nullptr;
    linkedListInsertAtTail(&result, tree->data);
    LinkedList<T>* left_preorder = binaryTreeGetPreorder(tree->left);
    linkedListConcatenate(&result, &left_preorder);
    LinkedList<T>* right_preorder = binaryTreeGetPreorder(tree->right);
    linkedListConcatenate(&result, &right_preorder);
    return result;
}

/**
 * @brief Gets inorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The inorder of the tree
 */
template <typename T>
LinkedList<T>* binaryTreeGetInorder(BinaryTree<T>* const& tree) {
    if (!tree) {return nullptr;}
    LinkedList<T>* result = binaryTreeGetInorder(tree->left);
    linkedListInsertAtTail(&result, tree->data);
    LinkedList<T>* right_inorder = binaryTreeGetInorder(tree->right);
    linkedListConcatenate(&result, &right_inorder);
    return result;
}

/**
 * @brief Gets postorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The postorder of the tree
 */
template <typename T>
LinkedList<T>* binaryTreeGetPostorder(BinaryTree<T>* const& tree) {
    if (!tree) {return nullptr;}
    LinkedList<T>* result = binaryTreeGetPostorder(tree->left);
    LinkedList<T>* right_postorder = binaryTreeGetPostorder(tree->right);
    linkedListConcatenate(&result, &right_postorder);
    linkedListInsertAtTail(&result, tree->data);
    return result;
}

template <typename T>
LinkedList<T>* binaryTreeGetLevelOrder(BinaryTree<T>* const& tree) {
    if (!tree) {return nullptr;}
    LinkedList<T>* result = nullptr;
    Queue<BinaryTree<T>*> queue(tree);
    while (!queueEmpty(queue)) {
        BinaryTree<T>* front = queueFront(queue);
        linkedListInsertAtTail(&result, front->data);
        if (front->left) {queuePush(queue, front->left);}
        if (front->right) {queuePush(queue, front->right);}
        queuePop(queue);
    }
    return result;
}

/**
 * @brief Gets the node in the binary tree with matching data
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to search
 * @param data The data to search for
 * @return BinaryTree<T>* The node if found, otherwise nullptr
 */
template <typename T>
BinaryTree<T>* binaryTreeGetNode(BinaryTree<T>* const& tree, T data) {
    if (!tree || tree->data == data) {return tree;}
    else if (data < tree->data) {return binaryTreeGetNode(tree->left, data);}
    else {return binaryTreeGetNode(tree->right, data);}
}

/**
 * @brief Gets the prede/suc cessor to the desired order.
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to search
 * @param data The data to search for
 * @param order_fn The tree traversal function (such as preorder)
 * @param cessor_function A function to get either the predecessor or successor
 * @return BinaryTree<T>* The node if found, otherwise nullptr
 */
template <typename T>
BinaryTree<T>* binaryTreeGetOrderCessor(
        BinaryTree<T>* const& tree, 
        T data, 
        LinkedList<T>* (*order_fn)(BinaryTree<T>* const& root),
        LinkedList<T>* (*cessor_fn)(
            LinkedList<T>* const& head, 
            T data, 
            int n, 
            bool (*equality_fn)(const T& lhs, const T& rhs))) {
    if (!order_fn) {return nullptr;}
    LinkedList<T>* order = order_fn(tree);
    LinkedList<T>* item = linkedListGetNthOccurrence(order, data, 1);
    LinkedList<T>* prev = cessor_fn(order, item->data, 1, nullptr);

    if (!prev) {return nullptr;}
    return binaryTreeGetNode(tree, prev->data);
}

template <typename T>
BinaryTree<T>* binaryTreeGetPreorderPredecessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetPreorder, 
        linkedListGetPredecessorOfNthOccurrence);
}

template <typename T>
BinaryTree<T>* binaryTreeGetPreorderSuccessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetPreorder, 
        linkedListGetSuccessorOfNthOccurrence);
}

template <typename T>
BinaryTree<T>* binaryTreeGetInorderPredecessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetInorder, 
        linkedListGetPredecessorOfNthOccurrence);
}

template <typename T>
BinaryTree<T>* binaryTreeGetInorderSuccessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetInorder, 
        linkedListGetSuccessorOfNthOccurrence);
}

template <typename T>
BinaryTree<T>* binaryTreeGetPostorderPredecessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetPostorder, 
        linkedListGetPredecessorOfNthOccurrence);
}

template <typename T>
BinaryTree<T>* binaryTreeGetPostorderSuccessor(
        BinaryTree<T>* const& tree, 
        T data) {
    return binaryTreeGetOrderCessor(
        tree, 
        data, 
        binaryTreeGetPostorder, 
        linkedListGetSuccessorOfNthOccurrence);
}

/**
 * @brief Gets the parent of the provided data within the tree, if it exists
 * 
 * @tparam T The type of the tree's data
 * @param tree The tree to search
 * @param data The data to find the parent of
 * @return BinaryTree<T>* The parent of the node, or nullptr if none is found
 */
template <typename T>
BinaryTree<T>* binaryTreeGetParentOf(BinaryTree<T>* const& tree, T data) {
    // Base cases
    if (!tree || tree->data == data) {return nullptr;}
    BinaryTree<T> *left = tree->left, *right = tree->right;
    if (left) {
        if (data == left->data) {return tree;}
        if (data < tree->data) {return binaryTreeGetParentOf(left, data);}
    }
    if (right) {
        if (data == right->data) {return tree;}
        if (data > tree->data) {return binaryTreeGetParentOf(right, data);}
    }
    return nullptr;
}

/**
 * @brief Deletes the specififed node from the list, if it exists
 * TODO: Can we refactor this with a helper function?
 * I tried using function pointers with getters but that doesn't work
 * 
 * @tparam T The type of the tree's data
 * @param tree The tree to delete the node from
 * @param data The data of the node to delete
 */
template <typename T>
void binaryTreeDeleteNode(BinaryTree<T>** tree, T data) {
    BinaryTree<T>* to_delete = binaryTreeGetNode(*tree, data);
    if (!to_delete) {return;}

    if (!to_delete->left && !to_delete->right) {
        delete to_delete;
        return;
    } else if (to_delete->left) {
        BinaryTree<T>* predecessor = binaryTreeGetInorderPredecessor(
            *tree, 
            to_delete->data);
        BinaryTree<T>* parent = binaryTreeGetParentOf(
            *tree, 
            predecessor->data);

        // Set parent's child to predecessor's chlid
        if (parent == to_delete) {
            parent->left = predecessor->left;
        } else {
            parent->right = predecessor->left;
        }
        to_delete->data = predecessor->data;

        // Delete predecessor
        predecessor->left = nullptr;
        predecessor->right =  nullptr;
        delete predecessor;
        return;
    } else /* to_delete->right */ {
        BinaryTree<T>* successor = binaryTreeGetInorderSuccessor(
            *tree, 
            to_delete->data);
        BinaryTree<T>* parent = binaryTreeGetParentOf(
            *tree, 
            successor->data);

        // Set parent's child to predecessor's chlid
        if (parent == to_delete) {
            parent->right = successor->right;
        } else {
            parent->left = successor->right;
        }
        to_delete->data = successor->data;

        // Delete predecessor
        successor->left = nullptr;
        successor->right =  nullptr;
        delete successor;
        return;
    }
}
#endif
