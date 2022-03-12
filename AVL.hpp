#ifndef __AVL_HPP__
#define __AVL_HPP__

#include <iostream>

typedef struct s_node
{
    int data;
    struct s_node *left; // The left subtree , keys lesser than node's key
    struct s_node *right; // The right subtree , keys greater than node's key

} t_node ;

t_node*     newNode(int item)
{
    t_node* tmp = new t_node();
    tmp->data = item;
    tmp->left = tmp->right = NULL;
    return tmp;
}

t_node*     insert(t_node* node, int data)
{
    if(!node)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

// Display elements; inorder traversal of BST  : non-decreasing order.
void        inorder(t_node *root)
{
    if (root)
    {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder traversal;  first visits the root node and then traverses the left and the right subtree // for copy !!
void        preorder(t_node *root)
{
    if(root)
    {
        std::cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal ;first traverses the left and the right subtree and then visits the root node. It is used to delete the tree.
void       postorder(t_node *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        std::cout << root->data << " ";
    }
}

// height of the BST
// The depth of a node in a binary tree is the total number of edges from the root node to the target node
int        height(t_node* node)
{
    if (!node)
        return 0;
    else
    {
        // calculate the depth of each subtree
        int l_depth = height(node->left);
        int r_depth = height(node->right);
        // use the larger one
        return (std::max(l_depth, r_depth) + 1);
    }
}

void    printGivenLevel(t_node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        std::cout << root->data << " ";
    else if (level > 1)
    {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

void    printLevelOrder(t_node *root)
{
    int h = height(root);
    for (int i = 0; i <= h; i++)
    {
       printGivenLevel(root, i);
       std::cout << "\n";
    }
}

// --- Returns the node with minimum key value found in that tree
t_node* minValueNode(t_node *node)
{
    t_node* current = node;
    while (current && current->left )
        current = current->left;
    return current;
}
// --- Delete a data and returns the new root

t_node* findNode(t_node *root, int key)
{
    if (root)
    {
        if (root->data == key)
            return (root);
        else
        {
            t_node *found_node = findNode(root->left, key);
            if (found_node == NULL)
                found_node = findNode(root->right, key);
            return found_node;
        }
    }
    else
        return (NULL);
}

t_node* deleteNode(t_node *root, int data)
{
    // Stop Condition
    if (!root)
        return (root);
    
    // If data to be deleted is smaller than the root data.
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // If data to be deleted is greater than the root data.
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // If data to be deleted is same as the root data.
    else
    {
        // Case 1 and 2: Node with only one childe or non child
        if (!root->left) // right of node is exist
        {
            t_node* tmp = root->right;
            free(root);
            return(tmp);
        }
        else if (!root->right) // left of node is exist
        {
            t_node* tmp = root->left;
            free(root);
            return tmp;
        }
        // Case 3: Node with two children 
            // -- get smallest in right subtree
        t_node* tmp = minValueNode(root->right);
            // -- copy the inorder successor's content to the this node;
        root->data = tmp->data;
            // -- delete the inorder successor
        root->right = deleteNode(root->right, tmp->data); 
    }
    return (root);
}
#endif