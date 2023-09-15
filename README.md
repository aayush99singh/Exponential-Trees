# Exponential Trees Sorting Algorithm

Sorting integers efficiently has long captivated the attention of researchers and developers. In this project, we introduce an innovative sorting algorithm based on Exponential Trees, which achieves a time complexity of O(nloglogn). Although the original algorithm is intricate and challenging to implement, we've harnessed a modified version of Exponential Trees for this project.

## Key Properties
- Each node at level 'k' holds 'k' integers.
- Each node at level 'k' has 'k+1' children.
- All keys within a node are sorted.

This modified Exponential Trees approach bears resemblance to binary trees, but with a crucial difference : the number of children a node can hold increases exponentially as the node's depth grows.

## Creator
- Aayush Singh : 2020CHB1036

## Deployment

To run this project in a Windows terminal, follow these steps :

1. Clone the repository using the provided Git URL :

```bash
git clone (git URL)
```

2. Navigate to the "Exponential-Trees" directory.

3. Compile the main program using GCC :

```bash
gcc ./main.c
```

4. Run the compiled program :

```bash
./a.exe
```

## Input
Input is read from a file named "input.txt." To change the input, modify the contents of this file. The maximum file size allowed is 50,000,007.

The input file format is as follows :
- The first number in the file represents the total number of integers.
- The subsequent N integers are taken as input and will be inserted into the trees.

## Output
The output provides CPU run-time statistics for sorting integers using the Exponential Trees algorithm, Binary Trees, and the Quick Sort algorithm. Key observations include :

- For smaller values of N (e.g., 10^5 - 10^6), the run-time for Exponential Tree Sorting and Quick Sort should be approximately the same.
- Binary Tree sorting typically exhibits longer run-times compared to the other methods.

Enjoy exploring the world of Exponential Trees sorting..!