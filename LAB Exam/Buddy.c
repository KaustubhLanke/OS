#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdint>

#define MAX_LEVELS 20

typedef struct Block {
    int size;
    struct Block* next;
} Block;

Block* freeList[MAX_LEVELS];

int maxLevels;

int nextPowerOfTwo(int n) {
    int power = 0;
    while (pow(2, power) < n) {
        power++;
    }
    return power;
}

void initializeBuddySystem(int memorySize) {
    maxLevels = nextPowerOfTwo(memorySize) + 1;

    for (int i = 0; i < maxLevels; i++) {
        freeList[i] = NULL;
    }

    Block* initialBlock = (Block*)malloc(sizeof(Block));
    initialBlock->size = memorySize;
    initialBlock->next = NULL;

    freeList[maxLevels - 1] = initialBlock;
}

Block* splitBlock(Block* block, int level) {
    if (level <= 0) {
        return block;
    }

    Block* buddy = (Block*)malloc(sizeof(Block));
    buddy->size = block->size;
    buddy->next = freeList[level - 1];

    freeList[level - 1] = buddy;

    return splitBlock(block, level - 1);
}

Block* allocateBlock(int size) {
    int level = nextPowerOfTwo(size);

    for (int i = level; i < maxLevels; i++) {
        if (freeList[i] != NULL) {
            Block* allocatedBlock = freeList[i];
            freeList[i] = allocatedBlock->next;
            
            if (i > level) {
                allocatedBlock = splitBlock(allocatedBlock, i - level);
            }

            return allocatedBlock;
        }
    }

    printf("Memory allocation failed. No suitable block found.\n");
    return NULL;
}

void deallocateBlock(Block* block) {
    int level = nextPowerOfTwo(block->size);

    while (level < maxLevels - 1) {
        Block* buddy = (Block*)(((intptr_t)block) ^ (1 << level));
        
        Block* current = freeList[level];

        if (current == NULL) {
            freeList[level] = block;
            block->next = NULL;
            return;
        }

        if (current == buddy) {
            // Merge blocks
            freeList[level] = current->next;
            level++;
            block = (Block*)(((intptr_t)block < (intptr_t)buddy) ? block : buddy);
        } else {
            block->next = freeList[level];
            freeList[level] = block;
            return;
        }
    }

    block->next = freeList[level];
    freeList[level] = block;
}

void displayFreeList() {
    printf("Free List:\n");

    for (int i = 0; i < maxLevels; i++) {
        printf("Level %d: ", i);
        Block* current = freeList[i];

        while (current != NULL) {
            printf("[%d] -> ", current->size);
            current = current->next;
        }

        printf("NULL\n");
    }
}

int main() {
    int memorySize = 128;
    initializeBuddySystem(memorySize);

    displayFreeList();

    // Allocate blocks
    Block* block1 = allocateBlock(10);
    Block* block2 = allocateBlock(25);

    displayFreeList();

    // Deallocate blocks
    deallocateBlock(block1);
    deallocateBlock(block2);

    displayFreeList();

    return 0;
}