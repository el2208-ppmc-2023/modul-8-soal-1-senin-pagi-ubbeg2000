/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           : main.c
 *   Deskripsi           :
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Deklarasi struktur data tree
struct node
{
    char txt[10];
    struct node *left;
    struct node *right;
};

// Deklarasi stack
typedef struct node2
{
    char name[255];
    struct node2 *next;
} node2;

typedef struct Stack
{
    node2 *head;
} Stack;


// Fungsi-fungsi yang diperlukan
// Membuat node di tree
struct node *newNode(char name[10])
{
    struct node *node = (struct node *)malloc(sizeof(struct node));

    strcpy(node->txt, name);

    node->left = NULL;
    node->right = NULL;
    return (node);
}

int isStackEmpty(Stack *stack)
{
    return stack->head == NULL;
}

void push(Stack *stack, char new_data[10])
{
    node2 *new_node = (node2 *)malloc(sizeof(node2));
    strcpy(new_node->name, new_data);
    new_node->next = stack->head;

    stack->head = new_node;
}

void pop(Stack *stack, char ret_val[10])
{
    node2 *temp = stack->head;
    if (temp != NULL)
    {
        strcpy(ret_val, temp->name);
        stack->head = temp->next;
        free(temp);
    }
}

void clearStack(Stack *stack)
{
    node2 *temp = stack->head;
    if (!isStackEmpty(stack))
    {
        char top[10];
        pop(stack, top);
        clearStack(stack);
    }
}

// insert data di paling bawah
void insertAtBottom(Stack *stack, char item[10])
{
    if (isStackEmpty(stack))
    {
        push(stack, item);
    }
    else
    {
        char top[10];
        pop(stack, top);
        insertAtBottom(stack, item);
        push(stack, top);
    }
}

// untuk mengatur stack dari bawah ke atas
void reverse(Stack *stack)
{
    if (!isStackEmpty(stack))
    {
        char top[10];
        pop(stack, top);
        reverse(stack);
        insertAtBottom(stack, top);
    }
}

void printStack(Stack *stack)
{
    node2 *current = stack->head;

    while (current != NULL)
    {
        printf("%s", current->name);
        current = current->next;
    }
}

int ifNodeExists(struct node *node, char inp[], Stack *stack, int kirikanan, int count)
{ //DFD
    char temp[10];
    if (node == NULL)
    {
        return 0; // jika node kosong
    }
    if (kirikanan == 0 && count != 0)
    {
        push(stack, "0"); // masukkan path ke stack
    }
    else if (kirikanan == 1 && count != 0)
    {
        push(stack, "1"); // masukkan path ke stack
    }
    count++;

    if ((strcmp(node->txt, inp)) == 0)
    { // jika input ditemukan pada node
        return 1;
    }

    if (ifNodeExists(node->left, inp, stack, 0, count)) // rekursif ke cabang left
    {
        return 1;
    }

    if (ifNodeExists(node->right, inp, stack, 1, count)) // rekursif ke cabang right
    {
        return 1;
    }
    pop(stack, temp); // backtracking jika node tidak ditemukan di path sekarang
}

int main()
{
    // Deklarasi/inisiasi variabel
    char inp[20];
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->head = NULL;

    // Masukkan huffman hierarchy ke dalam tree
    struct node *root = newNode("_dcumhtpa");
    root->left = newNode("_dcum");
    root->right = newNode("htpa");

    root->left->left = newNode("m");
    root->left->right = newNode("_dcu");

    root->left->right->left = newNode("u");
    root->left->right->right = newNode("_dc");

    root->left->right->right->left = newNode("_d");
    root->left->right->right->right = newNode("c");

    root->left->right->right->left->left = newNode("_");
    root->left->right->right->left->right = newNode("d");

    root->right->left = newNode("a");
    root->right->right = newNode("htp");

    root->right->right->left = newNode("p");
    root->right->right->right = newNode("ht");

    root->right->right->right->left = newNode("t");
    root->right->right->right->right = newNode("h");

    // Template
    printf("Masukkan kata yang ingin dikonversi: ");
    scanf("%s", &inp);
    printf("\nHasil konversi dengan Huffman Coding adalah sebagai berikut\n");

    int len = strlen(inp);
    int i = 0;
    char temp[2];
    while (i < len)
    { //pencarian dan output
        temp[0] = inp[i];
        ifNodeExists(root, temp, stack, 0, 0);
        reverse(stack); // karena yang dicetak dimulai dari bawah
        printStack(stack);
        clearStack(stack); //mulai ulang stack
        i++;
    }

    return 0;
}
