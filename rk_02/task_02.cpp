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
        if ((*root)->value >= new_bst_node->value) {
            if ((*root)->left == NULL)
                (*root)->left = new_bst_node;
            else
                bst_add_node(&((*root)->left), new_bst_node);
        } else if ((*root)->value < new_bst_node->value) {
            if ((*root)->right == NULL)
                (*root)->right = new_bst_node;
            else
                bst_add_node(&((*root)->right), new_bst_node);
        }
    }
}

int find_shortest(bst_node_t* root)
{
    int result = 0;
    if (root) {
        int left_shortest = find_shortest(root->left);
        if (left_shortest != 0)
            result = left_shortest;
        int right_shortest = find_shortest(root->right);
        if (right_shortest != 0 && (right_shortest < left_shortest || left_shortest == 0))
            result = right_shortest;
        result++;
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
    std::cout << find_shortest(bst) << std::endl;
    free_bst(bst);
    return 0;
}