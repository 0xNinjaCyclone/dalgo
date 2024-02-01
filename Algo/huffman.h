#ifndef _dalgo_huffman
#define _dalgo_huffman

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "hash.h"
#include "helpers.h"

typedef struct _HuffmanTreeNode HuffmanTreeNode;

struct _HuffmanTreeNode
{
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    unsigned char data;
    unsigned long ulFrequency; 
};

HuffmanTreeNode *huffman_calcfreq(unsigned char *data, size_t ulSize, size_t *ulpNumberOfNodes);
HuffmanTreeNode *huffman_build(HuffmanTreeNode *hNodes, size_t ulSize);
void huffman_cleanup(HuffmanTreeNode **root);

#endif