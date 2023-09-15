/*
    TOPIC - Exponential Trees
    AIM - Comparing The Sorting Time and Analysis Among Exponential Trees, Binary Trees and Quick Sort Algorithm
*/

// -------------------------------------------------- C CODE LIBRARIES AND TYPEDEFS--------------------------------------------------

#include <stdio.h>  // Importing The basic Library of C
#include <stdlib.h> // Importing The standard Library of C
#include <string.h> // Importing The string Library
#include <time.h>   // Importing The time Library For Calculating The Execution Time of Functions

clock_t ET_TIME; // Intitalising The Time Variables For Exponential Tree
clock_t BT_TIME; // Intitalising The Time Variables For Binary Tree
clock_t QS_TIME; // Intitalising The Time Variables For Quick Sort

typedef struct Node node; // TypeDefining the Node For Easier Use in The Code
#define INPUT_FILE_NAME "input.txt" // Defining Input File Name For Easier Use in The Code



// -------------------------------------------------- EXPONENTIAL TREE UTILITIES BEGINS --------------------------------------------------

struct Node // Creating Node For Exponential Tree
{
    int level;    // Gives The Level of The Node of The Exponential Tree
    int count;    // Number of Integers Present Currently in The Node
    node **child; // Array For The Children of Each Node of The Tree, For Every Element in The Node
    int data[];
};

// This Function Will Be Used in Inserting The Node in The Exponential Tree, It Will Find The Correct Spot For The Insertion 
int binarySearch(node *ptr, int element)
{
    if (ptr->count == 0) return 0; // If The Node is Empty Then Return 0
    if (element > ptr->data[ptr->count - 1]) return ptr->count; // If The Element Is Greater Than The Biggest Element in The Array Then Return The Count of The Array

    // Executing Binary Search in The Individual Nodes
    int start = 0; int end = ptr->count - 1;
    int mid = start + (end - start) / 2;
    // We Mainly Divide The Array Into Two Parts and Check The First Element of Both Parts of Array and This Works in a Loop Until We Find Out Element
    while (start < end)
    {
        if (element > ptr->data[mid]) start = mid + 1;  // Second Part of Array
        else end = mid; // First Part of Array

        mid = start + (end - start) / 2;
    }

    return mid; // Return The Mid, The Ultimate Answer of Search
}

// Function For Creating The Node of The Exponential Tree
// This Function Will Be Used When We Have Found The Correct Spot For Insertion of The Element, Then We Will Create The Node and Insert it at The Position

node *createNode(const int level) // Level Signifies The Depth From The Root of The Tree , Root Has Level 1
{
    if (level <= 0)
        return NULL;

    // Allocate Node With 2**(Level-1) Integers 
    node *pNewNode = (node *)malloc(sizeof(node) + sizeof(int) * (1 << (level - 1))); // Allocating The Memory For The Integer Array
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1))); // This Sets The Data of The Node Elements to Zero

    // Allocate 2**Level Child Node Pointers 
    pNewNode->child = (node **)malloc(sizeof(node *) * (1 << level)); // Allocating The Memory For The Children of The Node
    memset(pNewNode->child, 0, sizeof(int) * (1 << level));

    pNewNode->count = 0; // Currently The Number of Elements in The Node is 0

    pNewNode->level = level; // Setting The Level to The Mentioned Level

    return pNewNode;
}

// Function to Insert The Node at The Position
void insert(node *root, int element)
{
    node *ptr = root; //  For Not Using The Root
    node *parent = NULL;
    int i = 0;

    while (ptr != NULL)
    {
        int level = ptr->level;
        int count = ptr->count;
        i = binarySearch(ptr, element); // Finding The Node in The Tree

        if (count < (1 << (level - 1))) // Only if The Count is Less Than The Maximum Allowed Size of The Array
        {
            for (int j = count; j >= i + 1; --j) ptr->data[j] = ptr->data[j - 1]; // Shifting The Array Elements

            ptr->data[i] = element; // Putting The Element at The Place
            ++ptr->count;           // Increasing The Count By 1
            return;
        }

        parent = ptr;
        ptr = ptr->child[i];
    }

    parent->child[i] = createNode(parent->level + 1);
    insert(parent->child[i], element);
}

void InOrderTrace(node *root) // Performing The In-Order Trace, This Function is The Only Function That Essentialy Performs The Sorting
{

    if (root == NULL) return;
 
    for (int i = 0; i < root->count; ++i)
    {
        InOrderTrace(root->child[i]);
        // printf("%d\n", root->data);
    }
    
    if (root->child[root->count]) InOrderTrace(root->child[root->count]);
}

// -------------------------------------------------- EXPONENTIAL TREE UTILITIES ENDS --------------------------------------------------



// -------------------------------------------------- BINARY TREE UTILITIES BEGINS --------------------------------------------------

struct node // Creating Node For Binary Tree
{
    int key; // The Data Present in The Node
    struct node *left, *right; // The Left and Right Child of The Node
};

// A Utility Function To Create a New BST Node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating The Memory For The Node in The Heap
    temp->key = item; // Giving The Data
    temp->left = temp->right = NULL; // Initialising The Children of The Node
    return temp; // Returning The Node
}

// An Utility Function For InOrder Traversal of BST
void inorder(struct node *root) // InOrder Traversal of BST
{
    if (root != NULL)
    {
        inorder(root->left);
        // printf("%d \n", root->key);
        // Here The Data is'nt Printed Because We Just Need To Calculate The Time Which Tree Takes To Sort The Data
        inorder(root->right);
    }
}

// A Utility Function to Insert a New Node With Given Key in BST
struct node *insertBT(struct node *node, int key)
{ 
    if (node == NULL) return newNode(key); // If The Tree is Empty, Return a New Node

    // Otherwise, Recur Down The Tree According to The Position of The Insertion of Node
    if (key < node->key) node->left = insertBT(node->left, key);
    else if (key > node->key) node->right = insertBT(node->right, key);

    return node; // Returning The Head Pointer
}

// -------------------------------------------------- BINARY TREE UTILITIES ENDS --------------------------------------------------



// -------------------------------------------------- QUICK SORT UTILITIES BEGINS --------------------------------------------------

int array[50000007]; // Declaring The Array For Quick Sort, The Array is Declared as Global to Increase The Size Constraints in Local Functions

void swap(int *a, int *b) // Swapping The Elements Using Temporary Variable
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition Function to Help in The QuickSort Funciton This Function Places The Pivot at it's Correct Place
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    // Fixing The Last Element as Pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]); // Swapping if Condition Satisfies
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); // Return The Partition Index
}

void quickSort(int arr[], int low, int high)
{
    // Performing The Quick Sort
    if (low < high)
    {
        int partitionIndex = partition(arr, low, high); // Getting The Partition

        // Recursively Performing The QuickSort Function on The Left & The Right Side of The Array Rround The Partition 
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// -------------------------------------------------- QUICK SORT UTILITIES ENDS --------------------------------------------------



// -------------------------------------------------- FUNCTION CALL UTILITIES BEGINS --------------------------------------------------

void EXPONENTIAL_TREE_METHOD()
{
    FILE *INPUT_FILE;   INPUT_FILE = fopen(INPUT_FILE_NAME, "r"); 

    node *pRoot = createNode(1); 

    if (INPUT_FILE == NULL)
    { 
        return ; 
    }

    int N;  fscanf(INPUT_FILE, "%d", &N);

    int N0;
    ET_TIME = clock();  

    for (int i = 0; i < N; i++)
    { 
        fscanf(INPUT_FILE, "%d", &N0);
        insert(pRoot, N0); 
    }

    InOrderTrace(pRoot);  

    ET_TIME = clock() - ET_TIME;
    double totalExecutionTime = (double)ET_TIME / CLOCKS_PER_SEC;

    printf("ET EXECUTION TIME IS : %f\n", totalExecutionTime);
    fclose(INPUT_FILE); 
}

void BINARY_TREE_METHOD()
{
    FILE *INPUT_FILE;   INPUT_FILE = fopen(INPUT_FILE_NAME, "r");

    struct node *root = NULL;   root = insertBT(root, 1); 

    if (INPUT_FILE == NULL)
    {
        return ; 
    }

    int N; fscanf(INPUT_FILE, "%d", &N); 

    int N0;
    BT_TIME = clock();  

    for (int i = 0; i < N; i++)
    { 
        fscanf(INPUT_FILE, "%d", &N0);
        insertBT(root, N0); 
    }

    inorder(root); 

    BT_TIME = clock() - BT_TIME; 
    double totalExecutionTime = (double)BT_TIME / CLOCKS_PER_SEC;

    printf("BT EXECUTION TIME IS : %f\n", totalExecutionTime);
    fclose(INPUT_FILE); 
}

void QUICK_SORT_METHOD()
{
    FILE *INPUT_FILE;   INPUT_FILE = fopen(INPUT_FILE_NAME, "r"); 

    if (INPUT_FILE == NULL)
    {
        return ; 
    }

    int N;  fscanf(INPUT_FILE, "%d", &N); 
    
    int N0;
    QS_TIME = clock(); 

    for (int i = 0; i < N; i++)
    {
        fscanf(INPUT_FILE, "%d", &N0); 
        array[i] = N0;
    }

    quickSort(array, 0, N - 1);  

    // for(int i = 0; i < N; i++) printf("%d\n", array[i]);

    QS_TIME = clock() - QS_TIME; 
    double totalExecutionTime = (double)QS_TIME / CLOCKS_PER_SEC;

    printf("QS EXECUTION TIME IS : %f\n", totalExecutionTime);
    fclose(INPUT_FILE);
}

// -------------------------------------------------- FUNCTION CALL UTILITIES ENDS --------------------------------------------------


int main()
{
    EXPONENTIAL_TREE_METHOD();
    BINARY_TREE_METHOD();
    QUICK_SORT_METHOD();
    return 0;
}