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

// Temporary node for case 2
t_node* temp = new t_node;

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

t_node* findMin(t_node* root)
{
    while (root->left)
      root = root->left;
    return root;
}

t_node* findMax(t_node* root)
{
    while (root->right)
        root = root->right;
    return root;
}

t_node* nextNode(t_node* root, t_node* x)
{
    t_node* succ = NULL;
    if (!root)
        return NULL;
    while (1){
        if (x->data < root->data){
            succ = root;
            root = root->left;
        }
        else if (x->data > root->data)
            root = root->right;
        else {
            if (root->right)
                succ = findMin(root->right);
            break;
        }
        if (!root)
          return succ;
    }
    return succ;
}

t_node* previousNode(t_node* root, t_node* x)
{
    t_node* prec = NULL;
    if (!root)
        return NULL;
    while (1){
        if (x->data < root->data)
            root = root->left;
        else if (x->data > root->data){
            prec = root;
            root = root->right;
        }
        else {
            if (root->left)
                prec = findMax(root->left);
            break;
        }
        if (!root)
          return prec;
    }
    return prec;
}

// // function to find left most node in a tree
// t_node* leftMostNode(t_node* node)
// {
//     while (node != NULL && node->left != NULL)
//         node = node->left;
//     return node;
// }
 
// // function to find right most node in a tree
// t_node* rightMostNode(t_node* node)
// {
//     while (node != NULL && node->right != NULL)
//         node = node->right;
//     return node;
// }
 
// // recursive function to find the Inorder Successor
// // when the right child of node x is NULL
// t_node* findInorderRecursive(t_node* root, t_node* x )
// {
//     if (!root)
//         return NULL;
 
//     if (root==x || (temp = findInorderRecursive(root->left,x)) ||
//                    (temp = findInorderRecursive(root->right,x)))
//     {
//         if (temp)
//         {
//             if (root->left == temp)
//             {
//                 // std::cout << "Inorder Successor of " << x->data;
//                 // std::cout << " is "<< root->data << "\n";
//                 return NULL;
//             }
//         }
 
//         return root;
//     }
 
//     return NULL;
// }
 
// // function to find inorder successor of
// // a node
// t_node* inorderSuccessor(t_node* root, t_node* x)
// {
//     // Case1: If right child is not NULL
//     if (x->right != NULL)
//     {
//         t_node* inorderSucc = leftMostNode(x->right);
//         // std::cout<<"Inorder Successor of "<<x->data<<" is ";
//         // std::cout<<inorderSucc->data<<"\n";
//         return (inorderSucc);
//     }
 
//     // Case2: If right child is NULL
//     if (x->right == NULL)
//     {   
//         t_node* rightMost = rightMostNode(root);
 
//         // case3: If x is the right most node
//         if (rightMost == x)
//             return (NULL);
//         else
//             return (findInorderRecursive(root, x));
//     }
//     return NULL;
// }

#endif