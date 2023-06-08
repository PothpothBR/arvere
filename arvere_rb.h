#ifndef INCLUDE_ARVERE_RB_INCLUDED
#define INCLUDE_ARVERE_RB_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define class struct

#define RED 0
#define BLACK 1

// helper to flip node color
#define flip(v) v != v
// helper to spy node color
#define is_color(n) (!n ? BLACK : n->color)
// helper to asign color to node
#define asign_color(n, c) if (n) n->color = c

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

// artist data
typedef class _Artist {
    const char* name;
    unsigned int* film_ids;
} Artist;

// tree node
typedef class _Node {
    char color;
    class _Node *left;
    class _Node *right;
    
    unsigned int key;
    Artist value;
}Node;

void print_key_tree(Node* root){
    if (!root){ return; }
    printf("[");
    print_key_tree(root->left);
    printf(root->color == RED ? "\033[31m%i\033[0m" :  "\033[34m%i\033[0m", root->key);
    print_key_tree(root->right);
    printf("]");
}

void print_value_tree(Node* root){
    if (!root){ return; }
    printf("[");
    print_value_tree(root->left);
    printf(root->color == RED ? "\033[31m%s\033[0m" :  "\033[34m%s\033[0m", root->value.name);
    print_value_tree(root->right);
    printf("]");
}

int find_deep(Node* root, int deep){
    if (!root) return deep;
    return max(find_deep(root->left, deep+1), find_deep(root->right, deep+1));
}

// helper for parse id "nm0000001" to int 1
unsigned int get_id(const char* id){
    return atoi(&id[2]);
}

// helper for create root node
Node** create_root(){
    Node** root = calloc(sizeof(Node*), 1);
    return root;
}

Node** _root;
// single rotate tree left and replace colors
Node* rotate_left(Node* node){
    Node* aux = node->right;
    node->right = aux->left;
    aux->left = node;
    aux->color = node->color;
    node->color = RED;
    return aux;
}

// single rotate tree right and replace colors
Node* rotate_right(Node* node){
    Node* aux = node->left;
    node->left = aux->right;
    aux->right = node;
    aux->color = node->color;
    node->color = RED;
    return aux;
}

void changeColor(Node *root, Node* upper, Node* node){
    Node *uncle = (upper->left == root ? upper->right : upper->left);
    if (is_color(node) == RED && is_color(root) == RED && is_color(uncle) == RED){
        asign_color(root, BLACK);
        asign_color(uncle, BLACK);
        asign_color(upper, RED);
    }
}

// create a new node
Node* create_node(unsigned int key, const char* name, unsigned int* film_ids){
    Node* node = calloc(sizeof(Node), 1);
    node->key = key;
    node->value.name = name;
    node->value.film_ids = film_ids;
    return node;
}

void insert_node3(Node** root, Node** upper, Node* node){
    if(!*root) *root = node;
    else if (node->key < (*root)->key) insert_node3(&(*root)->left, root, node);
    else insert_node3(&(*root)->right, root, node);

    if ((*root)->color == BLACK) return;

    if (!upper) return;

    changeColor(*root, *upper, (*root)->left);
    changeColor(*root, *upper,(*root)->right);
    if ((*root)->color == RED && is_color((*upper)) == BLACK){
        if (is_color((*upper)->left) == BLACK){
            if (is_color((*root)->left) == RED) *root = rotate_right(*root);
            if (is_color((*root)->right) == RED) *upper = rotate_left(*upper);
            
        }
        else if (is_color((*upper)->right) == BLACK){
            if (is_color((*root)->right) == RED) *root = rotate_left(*root);
            if (is_color((*root)->left) == RED) *upper = rotate_right(*upper);
        }      
    }
}

// insert a node in tree
void insert_node(Node** root, Node* node){
    if (!root) printf("[erro] não é possivel inserir em uma raiz vazia");
    if (!node) printf("[erro] não é possivel inserir um nó vazio");

    insert_node3(root, 0, node);

    // root is always black
    (*root)->color = BLACK;
}

// create and insert a new node in tree using param values
Node* emplace_node(Node** root, unsigned int key, const char* name, unsigned int* film_ids){
    Node* node = create_node(key, name, film_ids);
    insert_node(root, node);
    return node;
}

#endif // INCLUDE_ARVERE_RB_INCLUDED