#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// care for :
//      1 list = null; 2 just one node in list; 3 just two nodes in list; 4 first and last node 
struct linknode{
    int val;
    struct linknode* next;
};

void printList(struct linknode *head)
{
    struct linknode *p = head;
    while(p)
    {
        printf(" %d", p->val);
        p = p->next;
    }
    printf("\n");
}

void printList20(struct linknode *head)
{
    int i = 0;
    struct linknode *p = head;
    while(p && i<20)
    {
        printf(" %d", p->val);
        p = p->next;
        i++;
    }
    printf("\n");
}

//build a newList
void newList(struct linknode** list, int* arr, int n)
{
    if(n<=0)
    {
        *list = NULL;
        return ;
    }
    struct linknode *head = (struct linknode*)malloc(sizeof(struct linknode));
    head->val = arr[0];
    head->next = NULL;

    int i = 1;
    struct linknode *p = head;
    for(i = 1; i<n; i++)
    {
        struct linknode *q = (struct linknode*)malloc(sizeof(struct linknode));
        q->val = arr[i];
        q->next = NULL;
        p->next = q;
        p = p->next;

    }
    *list = head;
    return;
}

//build a loopList
void newloopList(struct linknode** list, int* arr, int n, int index)
{
    if(n<=0 || index > n || index == n-1)
    {
        *list = NULL;
        return ;
    }

    struct linknode *loopPot = NULL;
    struct linknode *head = (struct linknode*)malloc(sizeof(struct linknode));
    head->val = arr[0];
    head->next = NULL;

    if(index == 0)
        loopPot = head;

    int i = 1;
    struct linknode *p = head;
    for(i = 1; i<n; i++)
    {
        struct linknode *q = (struct linknode*)malloc(sizeof(struct linknode));
        q->val = arr[i];
        q->next = NULL;
        p->next = q;
        p = p->next;

        if(i == index)
            loopPot = q;
        if(i == n-1)
        {
            q->next = loopPot;
        }

    }
    *list = head;
    return;
}

//insert a node
void addNodeToHead(struct linknode** list, int val)
{
    struct linknode *p = (struct linknode*)malloc(sizeof(struct linknode));
    p->val = val;
    p->next = *list;
    *list = p;
    return;
}

void addNodeToTail(struct linknode** list, int val)
{
    struct linknode *p = (struct linknode*)malloc(sizeof(struct linknode));
    p->val = val;
    p->next = NULL;

    struct linknode *cur = *list;
    while(cur->next)
    {
        cur = cur->next;
    }
    cur->next = p;
    return;

}

void reverseList(struct linknode** list)
{
    if(*list == NULL)
        return;

    struct linknode* cur = *list;
    struct linknode* cnext = NULL;
    //head
    cnext = cur->next;
    cur->next = NULL;
    cur = cnext;

    while(cur)
    {
        cnext = cur->next;
        cur->next = *list;
        *list = cur;
        cur = cnext;
    }
    return;
}

void deleteNode(struct linknode** list, int val)
{
    struct linknode* p   = *list;
    struct linknode* cur = *list;

    if((*list)->val == val)
    {
        (*list) = (*list)->next;
        free(cur);
        return;
    }
    while(cur && cur->val != val)
    {
        p = cur;
        cur = cur->next;
    }
    if(cur)
    {
        p->next = cur->next;
        free(cur);
    }
    return;
}

/*delete nth node from list*/
void deleteNodeN(struct linknode** list, int nth)
{
    struct linknode* cur = *list;
    if(nth == 0)
    {
        *list = (*list)->next;
        free(cur);
        return;
    }

    int i = 0;
    struct linknode* pre = *list;
    while(cur && i != nth)
    {
        i++;
        pre = cur;
        cur = cur->next;
    }
    if(cur)
    {
        pre->next = cur->next;
        free(cur);
    }

}

void sortList(struct linknode** list)
{
    if(*list == NULL)
        return;

    struct linknode* cur = *list;
    struct linknode* pre = *list;
    struct linknode* cOld = cur->next;
    struct linknode* cONext = cur->next;

    cur->next = NULL;
    while(cOld)
    {
        cONext = cOld->next;
        cOld ->next = NULL;
        //new head
        if(cOld->val < (*list)->val)
        {
            cOld->next = *list;
            *list = cOld;
        }
        else
        {
            cur = *list;
            pre = *list;
            while(cur && cOld->val > cur->val)
            {
                pre = cur;
                cur = cur->next;
            }
            if(cur)
            {
                cOld->next = cur;
                pre->next = cOld;
            }
            else
            {
                pre->next = cOld;
            }
                
        }
    
    cOld = cONext;
    }//while
}

//0 --- no loop
//1 --- is loop
int isLoop(struct linknode* list)
{
    if(list == NULL)
        return 0;

    struct linknode* step1 = list;
    struct linknode* step2 = list->next;
    while(step1 && step2)
    {
        if(step1 == step2)
        {
            return 1;
        }
        step1 = step1->next;
        if(step2->next)
            step2 = step2->next->next;
        else
        {
            break;
        }
    }
    return 0;
}

/* list1, list2 is in ordered */
struct linknode* mergeList(struct linknode* list1, struct linknode* list2)
{
    if(list1 == NULL && list2 == NULL)
        return NULL;
    else if(list1 == NULL)
        return list1;
    else if(list2 == NULL)
        return list2;

    struct linknode* rHead = NULL;
    struct linknode* curR  = NULL;
    struct linknode* cur1  = list1;
    struct linknode* cur2  = list2;
    struct linknode* l1Next = NULL;
    struct linknode* l2Next = NULL;

    while(cur1 && cur2)
    {
        if(cur1->val < cur2->val)
        {
            l1Next = cur1->next;
            cur1->next = NULL;
            if(NULL == rHead)
            {
                rHead = cur1;
                curR = rHead;
            }
            else
            {
                curR->next = cur1;
                curR = curR->next;
            }
            cur1 = l1Next;            
        }
        else
        {
            l2Next = cur2->next;
            cur2->next = NULL;
            if(NULL == rHead)
            {
                rHead = cur2;
                curR = rHead;
            }
            else
            {
                curR->next = cur2;
                curR = curR->next;
            }
            cur2 = l2Next;
        }
    }
    return rHead;
}


void addNodeInorder(struct linknode** list, int val)
{
    struct linknode* nNode = (struct linknode*)malloc(sizeof(struct linknode*));
    nNode->val = val;
    nNode->next = NULL;

    if(*list == NULL)
    {
        *list = nNode;
        return;
    }
    if(val < (*list)->val)
    {
        nNode->next = *list;
        *list = nNode;
        return;
    }
    
    struct linknode* cur = *list;
    struct linknode* pre = *list;
    while(cur && cur->val < val)
    {
        pre = cur;
        cur = cur->next;
    }
    
    if(cur)
    {
        nNode->next = cur;
        pre->next = nNode;
    }
    else
        pre->next = nNode;

    return;
}

void freelist(struct linknode** list)
{
    if(list == NULL)
        return;

    struct linknode* cur = *list;
    while(cur)
    {
        *list = cur->next;
        cur->next = NULL;
        free(cur);
        cur = *list;
    }

}

int main()
{
    int arr1[] = {6,7,3,9,12,34,17,54,13,82};
    int size1 = sizeof(arr1)/sizeof(int);

    /*link: create, insert, delete, reverse, sort*/
    struct linknode* list1 = NULL;
    newList(&list1, arr1, size1);
    printf("     new list1 from arr : "); printList(list1);

    int val = 55;
    addNodeToHead(&list1, val);
    printf("      add (%3d) to head : ", val); printList(list1);

    int val2 = 66;
    addNodeToTail(&list1, val2);
    printf("      add (%3d) to tail : ", val2); printList(list1);

    int valD = 55;
    deleteNode(&list1, valD);
    printf("   del (%3d) from list1 : ", valD); printList(list1);

    int nth = 5;
    deleteNodeN(&list1, nth);
    printf(" del (%3dth) from list1 : ", nth); printList(list1);

    reverseList(&list1);
    printf("          after reverse : "); printList(list1);

    sortList(&list1);
    printf("             after sort : "); printList(list1);
    
    int valA = 23;
    addNodeInorder(&list1, valA);
    printf("insert (%3d) into list1 : ", valA); printList(list1);

    int arr2[] = {9,3,4,5,14,54,74,21,32};
    int size2 = sizeof(arr2)/sizeof(int);
    struct linknode* list2 = NULL;
    newList(&list2, arr2, size2);
    printf("     new list2 from arr : "); printList(list2);

    sortList(&list2);
    printf("             after sort : "); printList(list2);

    struct linknode *merL = mergeList(list1, list2);
    printf("            after merge : "); printList(merL);


    int arr3[] = {17,9,3,4,5,14,54,74,21,32};
    int size3 = sizeof(arr2)/sizeof(int);
    struct linknode* loop = NULL;
    newloopList(&loop, arr3, size3, 5);
    printf("  new looplist from arr : "); printList20(loop);
    printf("        looplist loop ? : %d\n", isLoop(loop));
    printf("           list1 loop ? : %d\n", isLoop(list1));

    freelist(&merL);
    freelist(&loop);
    return 0;
}
