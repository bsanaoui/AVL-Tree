#ifndef __AVL_HPP__
#define __AVL_HPP__

#include <iostream>


typedef struct s_node
{
    int             data;
    struct s_node   *left; // The left subtree , keys lesser than node's key
    struct s_node   *right; // The right subtree , keys greater than node's key
    int             height;

} t_node ;

t_node* minValueNode(t_node *node);

t_node*     newNode(int data)
{
    t_node* tmp = new t_node();
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    tmp->height = 1;
    return tmp;
}

// Calculate height fast
int height(t_node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// Get the balance factor of each node
int getBalanceFactor(t_node *node) {
  if (node == NULL)
    return 0;
  return height(node->left) -
       height(node->right);
}

// Rotate right
t_node *rightRotate(t_node *y) {
  t_node *x = y->left;
  t_node *beta = x->right;
  x->right = y;
  y->left = beta;
  y->height = std::max(height(y->left),
          height(y->right)) +
        1;
  x->height = std::max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

// Rotate left
t_node *leftRotate(t_node *x) {
  t_node *y = x->right;
  t_node *beta = y->left;
  y->left = x;
  x->right = beta;
  x->height = std::max(height(x->left),
          height(x->right)) +
        1;
  y->height = std::max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

t_node*     insert(t_node* node, int data)
{
    // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(data));
  if (data < node->data)
    node->left = insert(node->left, data);
  else if (data > node->data)
    node->right = insert(node->right, data);
  else
    return node;

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + std::max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (data < node->left->data) {
      return rightRotate(node);
    } else if (data > node->left->data) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (data > node->right->data) {
      return leftRotate(node);
    } else if (data < node->right->data) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
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
// int        height(t_node* node)
// {
//     if (!node)
//         return 0;
//     else
//     {
//         // calculate the depth of each subtree
//         int l_depth = height(node->left);
//         int r_depth = height(node->right);
//         // use the larger one
//         return (std::max(l_depth, r_depth) + 1);
//     }
// }

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
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) ||
        (root->right == NULL)) {
        t_node *temp = root->left ? root->left : root->right;
        if (temp == NULL) {
            temp = root;
            root = NULL;
        } else
            *root = *temp;
        free(temp);
        } else {
        t_node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right,
                    temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + std::max(height(root->left),
                height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
        } else {
        root->left = leftRotate(root->left);
        return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
        } else {
        root->right = rightRotate(root->right);
        return leftRotate(root);
        }
    }
    return root;
}

// Print the tree
void printTree(t_node *root, std::string indent, bool last) {
  if (root != nullptr) {
    std::cout << indent;
    if (last) {
      std::cout << "R----";
      indent += "   ";
    } else {
      std::cout << "L----";
      indent += "|  ";
    }
    std::cout << root->data << std::endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}

#endif