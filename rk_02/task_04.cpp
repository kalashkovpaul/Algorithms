// FAILED :(    

#include <iostream>

typedef struct avl_node avl_node_t;

struct avl_node {
    int value;
    char height;
    avl_node_t* left;
    avl_node_t* right;
};

void avl_add_node(avl_node_t** root, avl_node_t* new_avl_node)
{
    if (*root == NULL)
        *root = new_avl_node;
    else {
        if ((*root)->value >= new_avl_node->value) {
            if ((*root)->left == NULL)
                (*root)->left = new_avl_node;
            else
                avl_add_node(&((*root)->left), new_avl_node);
        } else if ((*root)->value < new_avl_node->value) {
            if ((*root)->right == NULL)
                (*root)->right = new_avl_node;
            else
                avl_add_node(&((*root)->right), new_avl_node);
        }
    }
}

char get_height(avl_node_t* node)
{
    return node ? node->height : 0;
}

char get_bfactor(avl_node_t* node)
{
    return node ? (get_height(node->right) - get_height(node->left)) : 0;
}

void fix_height(avl_node_t* root)
{
    if (root) {
        char height_left = get_height(root->left);
        char height_right = get_height(root->right);
        root->height = (height_left > height_right ? height_left : height_right) + 1;
    }
}

avl_node_t* rotate_right(avl_node_t* node)
{
    avl_node_t* rotated = node->left;
    node->left = rotated->right;
    rotated->right = node;
    fix_height(node);
    fix_height(rotated);
    return rotated;
}

avl_node_t* rotate_left(avl_node_t* node)
{
    avl_node_t* rotated = node->right;
    node->right = rotated->left;
    rotated->left = node;
    fix_height(node);
    fix_height(rotated);
    return rotated;
}

avl_node_t* balance_node(avl_node_t* node)
{
    fix_height(node);
    if (get_bfactor(node) >= 2) {
        if (get_bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    } else if (get_bfactor(node) <= -2) {
        if (get_bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

avl_node_t* insert(avl_node_t* root, int key)
{
    if (!root) {
        avl_node_t* new_node = new avl_node_t;
        new_node->value = key;
        new_node->height = 1;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (key < root->value)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return balance_node(root);
}

void exists(avl_node_t* root, int searched, int* found)
{
    if (root) {
        if (root->value == searched) {
            *found = 1;
        } else {
            exists(root->left, searched, found);
            if (*found == 0) {
                exists(root->right, searched, found);
            }
        }
    }
}

avl_node_t* find_min(avl_node_t* root)
{
    return root->left ? find_min(root->left) : root;
}

avl_node_t* remove_min(avl_node_t* root)
{
    if (root->left == 0)
        return root->right;
    root->left = remove_min(root->left);
    return balance_node(root);
}

avl_node_t* remove(avl_node_t* root, int value)
{
    if (!root)
        return NULL;
    if (value < root->value)
        root->left = remove(root->left, value);
    else if (value > root->value)
        root->right = remove(root->right, value);
    else {
        avl_node_t* tmp = root->left;
        avl_node_t* t = root->right;
        delete root;
        if (!t)
            return tmp;
        avl_node_t* min = find_min(t);
        min->right = remove_min(t);
        min->left = tmp;
        return balance_node(min);
    }
    return balance_node(root);
}

avl_node_t* next(avl_node_t* root, int value)
{
    if (root && root->value > value && root->left == NULL)
        return root;
    else if (root && root->value > value && root->left->value >= value)
        return next(root->left, value);
    else if (root && root->value > value && root->left->value < value)
        return root;
    else if (root && root->value <= value)
        return root->right;
    return NULL;
}

avl_node_t* prev(avl_node_t* root, int value)
{
    if (root && root->value < value && root->right == NULL)
        return root;
    else if (root && root->value < value && root->right->value <= value)
        return prev(root->right, value);
    else if (root && root->value < value && root->right->value > value)
        return root;
    else if (root && root->value >= value)
        return root->left;
    return NULL;
}

void free_avl(avl_node_t* root)
{
    if (root != NULL) {
        avl_node_t* left = root->left;
        avl_node_t* right = root->right;
        delete root;
        free_avl(left);
        free_avl(right);
    }
}

int main()
{
    avl_node_t* root = NULL;
    std::string command;
    int value = 0;
    int result = false;
    while (std::cin >> command) {
        if (command == "insert") {
            std::cin >> value;
            root = insert(root, value);
        } else if (command == "delete") {
            std::cin >> value;
            root = remove(root, value);
        } else if (command == "exists") {
            std::cin >> value;
            result = 0;
            exists(root, value, &result);
            if (result)
                std::cout << "true" << std::endl;
            else
                std::cout << "false" << std::endl;
        } else if (command == "next") {
            std::cin >> value;
            avl_node_t* tmp = next(root, value);
            if (tmp)
                std::cout << tmp->value << std::endl;
            else
                std::cout << "none" << std::endl;
        } else if (command == "prev") {
            std::cin >> value;
            avl_node_t* tmp = prev(root, value);
            if (tmp)
                std::cout << tmp->value << std::endl;
            else
                std::cout << "none" << std::endl;
        }
    }
    free_avl(root);
    return 0;
}
