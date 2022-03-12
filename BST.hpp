#ifndef __AVL_HPP__
#define __AVL_HPP__

#include <iostream>

typedef struct s_node
{
    int data;
    struct s_node *left; // The left subtree , keys lesser than node's key
    struct s_node *right; // The right subtree , keys greater than node's key
    struct s_node *parent;

} t_node ;

t_node*     newNode(int item)
{
    t_node* tmp = new t_node();
    tmp->data = item;
    tmp->left = tmp->right = tmp->parent = NULL;
    return tmp;
}

t_node*     insert(t_node* node, int data)
{
    if(!node)
        return newNode(data);

    if (data < node->data)
    {
        t_node  *lchild = insert(node->left, data);
        node->left = lchild;
        lchild->parent = node;
        
    }
    else if (data > node->data)
    {
        t_node  *rchild = insert(node->right, data);
        node->right = rchild;
        rchild->parent = node;
    }
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

t_node* deleteNode(t_node *root, int key)
{
    t_node* del_node = findNode(root, key);
    if (!del_node)
        return (NULL);

    //---- 1 - Case if key is leaf node ----//
   if (!del_node->left && !del_node->right)
   {
       if (del_node->parent->left->data == key)
       {
           delete del_node->parent->left;
            del_node->parent->left = NULL;
       }
       else
       {
           delete del_node->parent->right;
            del_node->parent->right = NULL;
       }    
   }
   //---- 2-1 - Case if node found has 1 child on left ----//
   else if (del_node->left && !del_node->right)
   {    
       del_node->left->parent = del_node->parent; // change parent of child left
       // if node is on left parent
       if (del_node->parent->left->data == key)
       {
            del_node->parent->left = del_node->left;
            delete del_node;
       }
       // if node is on right parent
       else
       {
           del_node->parent->right = del_node->left;
           delete del_node;
       }
   }
    //---- 2-1 - Case if node has 1 child right----//
    else if (!del_node->left && del_node->right)
    {   
        del_node->right->parent = del_node->parent; // change parent of child right
        // if node is on left parent
       if (del_node->parent->left->data == key)
       {
            del_node->parent->left = del_node->right;
            delete del_node;
       }
       // if node is on left parent
       else
       {
           del_node->parent->right = del_node->right;
            delete del_node;
       }
    }
   // ---- 3 - Case if node has 2 child----//
    else  if (del_node->left && del_node->right)
    {
        // find minimum value
        t_node* minVal = minValueNode(del_node->right);
        int min = minVal->data;
        deleteNode(root, min);
        del_node->data = min;
    }
   return root;
}
#endif