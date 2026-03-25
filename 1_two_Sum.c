#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct Node {
    int index;
    int value;
    struct Node* nextNode;
}Node;

int hash(int number) {
    if (number < 0) {
        number = -number;
    }
    return (number%MAX);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i=0;
    int valueNeeded = 0;

    int valueIndex = -1;
    int posIndex = -1;

    *returnSize = 0;
    int *ret = (int*)malloc(2*sizeof(int));
    if (!ret) return NULL;

    Node* table[MAX];

    /* initialize table */
    for (i=0; i<MAX; i++) {
        table[i] = NULL;
    }

    for (i=0; i<numsSize; i++) {
        valueNeeded = target - nums[i];
        valueIndex = hash(valueNeeded);

        Node* cur = table[valueIndex];
        while (cur != NULL) {
            if (cur->value == valueNeeded) {
                ret[0] = cur->index;
                ret[1] = i;
                *returnSize = 2;
                return ret;
            }
            cur = cur->nextNode;
        }

        /* if not found, add entry */
        valueIndex = hash(nums[i]);
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = nums[i];
        newNode->index = i;
        newNode->nextNode = table[valueIndex];
        table[valueIndex] = newNode;
    }
    return ret;
}

int main() {
    int nums[] = {3, 2, 4};
    int target = 6;
    int returnSize = 0;

    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int* result = twoSum(nums, numsSize, target, &returnSize);

    if (result != NULL && returnSize == 2) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No solution found\n");
    }

    return 0;
}

