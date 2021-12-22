#include <iostream>

typedef struct bst_node bst_node_t;

struct bst_node {
    int value;
    bst_node_t* left;
    bst_node_t* right;
};

void bst_add_node(bst_node_t** root, bst_node_t* new_bst_node)
{
    if (*root == NULL)
        *root = new_bst_node;
    else {
        if ((*root)->value > new_bst_node->value) {
            if ((*root)->left == NULL)
                (*root)->left = new_bst_node;
            else
                bst_add_node(&((*root)->left), new_bst_node);
        } else if ((*root)->value <= new_bst_node->value) {
            if ((*root)->right == NULL)
                (*root)->right = new_bst_node;
            else
                bst_add_node(&((*root)->right), new_bst_node);
        }
    }
}

int check_is_even(bst_node_t* root)
{
    int result = 1;
    if (root) {
        if (root->left && root->left->value != root->value || root->right && root->right->value != root->value)
            result = 0;
        if (result) {
            result *= check_is_even(root->left);
            if (result)
                result *= check_is_even(root->right);
        }
    }
    return result;
}

void free_bst(bst_node_t* root)
{
    if (root != NULL) {
        bst_node_t* left = root->left;
        bst_node_t* right = root->right;
        delete root;
        free_bst(left);
        free_bst(right);
    }
}

int main()
{
    bst_node_t* bst = NULL;
    int value = 0;
    bst_node_t* new_node = NULL;
    while (std::cin >> value) {
        new_node = new bst_node();
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = value;
        bst_add_node(&bst, new_node);
    }
    std::cout << check_is_even(bst) << std::endl;
    free_bst(bst);
    return 0;
}