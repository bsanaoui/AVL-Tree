#include "AVL.hpp"
#include <time.h>

int main(){
    srand(time(0));
    t_node *root = NULL;

    // root = insert(root, 100);
    // int j = 0;
    // std::cout << j << " ";
    // for (size_t i = 1; i < 10; i++)
    // {
    //     insert(root, rand() % 99);
    // }

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
  
    /* 
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80
    */  
    
    // // -- inorder display -----------------/
    // std::cout << "\n< --------------- Inorder ----------------- >\n" << std::endl;
    // inorder(root);
    // std::cout << std::endl;

    //  // -- display in preorder traversal --/
    // std::cout << "\n< ------------ PreOrder traversal ---------- >\n" << std::endl;
    // preorder(root);
    // std::cout << std::endl;

    //  // -- display in preorder traversal --/
    // std::cout << "\n< ------------ PostOrder traversal ---------- >\n" << std::endl;
    // postorder(root);
    // std::cout << std::endl;
    
    std::cout << "\n< ------------ Height of AVL ---------- >\n" << std::endl;
    std::cout << "Height of our BST : " << height(root) << std::endl;


    std::cout << "\n< ------------ Delete Nodes ---------- >\n" << std::endl;
    // deleteNode(root, 50);


    std::cout << "\n< ------------ printLevelOrder ---------- >\n" << std::endl;
    printLevelOrder(root);

    std::cout << "\n< ------------ print Tree ---------- >\n" << std::endl;
    printTree(root, "", true);

    std::cout << "\n< ------------ Next Node---------- >\n" << std::endl;
    std::cout << "Inorder Successor of " << root->right->left->data << " is ";
    t_node *next = nextNode(root, root->right->left); //60
    if (next)
      std::cout << next->data << std::endl;

    std::cout << "\n< ---------------- END Tests ---------------- >\n" << std::endl;
    // while(1);
    return (0);
}