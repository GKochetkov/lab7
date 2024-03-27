#include <stdio.h>
#include <malloc.h>
#include "graph_stack.h"

#define MAX_VRTX_CNT 2000
#define MAX_EDGE_CNT n*(n+1)/2
#define B1 *buff
#define B2 *(buff+1)
#define INPUT Input(buff)


//getting input
char Input(int *buff) {
    char chr;
    int i = 0;

    *buff = 0;
    *(buff+1) = 0;

    chr = getchar();
    while (chr != EOF & chr != '\n') {
        if (chr == ' ')
            i++;
        else {
        *(buff+i) *= 10;
        *(buff+i) += chr-48;
        }

        chr = getchar();
    }

    return chr;
}

LIST* TopSort(LIST **graph, int *nCnt, int vCnt) {
    LIST *res = Create(0);
    LIST *stack = Create(0);
    int sCnt = 0;

    //adding first vertexes
    for (int i = 0; i < vCnt; i++) {
        if (*(nCnt+i) == 0) {
            Add(stack, Create(i));
            Add(res, Create(i+1));
            sCnt++;
        }
    }

    while (stack -> next != NULL) {
        //taking vertex from stack
        int curV = Take(stack);
        LIST *curE = (*(graph+curV)) -> next;

        //checking all vertex's neighbors
        while (curE != NULL) {
            int curN = curE -> value;

            *(nCnt+curN) -= 1;
            if (*(nCnt+curN) == -1) {
                Clear(stack);
                return res;
            }
            else if (*(nCnt+curN) == 0) {
                Add(stack, Create(curN));
                Add(res, Create(curN+1));
                sCnt++;
            }

            curE = curE -> next;
        }
    }

    free(stack);
    //checking if all graph is sorted
    if (sCnt == vCnt)
        res -> value = 1;
    return res;
}

int main() {
    int n, m, edgeCnt = 0;
    int *buff, *nCnt;
    char lastChr;
    LIST **graph, *res;

    buff = (int*)malloc(2*sizeof(int));

    //getting input
    lastChr = INPUT;

    n = B1;
    if (n < 0 || n > MAX_VRTX_CNT) {
        printf("bad number of vertices");
        return 0;
    }

    lastChr = INPUT;

    m = B1;
    if (m == 0) {
        printf("bad number of lines");
        return 0;
    } else if (m < 0 || m > MAX_EDGE_CNT) {
        printf("bad number of edges");
        return 0;
    }

    //creating adjacency list
    graph = (LIST**)malloc(n*sizeof(LIST*));
    nCnt = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        *(graph+i) = Create(0);
        *(nCnt+i) = 0;
    }

    //making adjacency list
    while (lastChr != EOF && edgeCnt != m) {
        lastChr = INPUT;
        if (B1 == B2 && B1 == 0) {
            printf("bad number of lines");
            return 0;
        }

        if (B1 < 1 || B1 > n || B2 < 1 || B2 > n) {
            printf("bad vertex");
            return 0;
        }
        Add(*(graph+B1-1), Create(B2-1));
        *(nCnt+B2-1) += 1;
        edgeCnt += 1;
    }

    free(buff);
    if (edgeCnt != m) {
        printf("bad number of lines");
        for (int i = 0; i < n; i++)
            Clear(*(graph+i));
        free(graph);
        free(nCnt);
        return 0;
    }

    res = TopSort(graph, nCnt, n);

    //output
    if (res -> value == 0)
        printf("impossible to sort");
    else {
        LIST *cur = res -> next;
        while (cur != NULL) {
            printf("%d ", cur -> value);
            cur = cur -> next;
        }
    }

    //clearing memory
    Clear(res);
    free(nCnt);
    for (int i = 0; i < n; i++)
        Clear(*(graph+i));
    free(graph);

    return 0;
}
