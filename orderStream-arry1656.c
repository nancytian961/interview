#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct oStream
{
    int key;
    char value[8];
    struct oStream *next;
};

struct oStream *hLuan = NULL;

/*insert only one node in hLuan, must in order*/
void funcInsertInOrder(struct oStream node)
{
    struct oStream *newNode = (struct oStream *)malloc(sizeof(struct oStream));
    newNode->key = node.key;
    strcpy(newNode->value, node.value);
    newNode->next = NULL;

    struct oStream *cur = hLuan;
    if(hLuan == NULL || node.key < cur->key)
    {
        newNode->next = hLuan;
        hLuan = newNode;
    }
    else
    {
        while(cur->next && cur->key < node.key)
        {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

/*find node in hLuan*/
struct oStream* findInLuan(int key, struct oStream node )
{
    int key2 = key;
    struct oStream *ret = NULL;
    struct oStream *retNode = NULL;
    struct oStream *cur = hLuan;


    //empty 
    if(hLuan == NULL)
    {
        if(node.key == key)
            return NULL;
        else
        {   
            funcInsertInOrder(node); //
            return NULL;
        }
    }
    else
    {
        if(node.key == key)
        {
            if(cur->key != key+1)
                return NULL;
            else
            {
                funcInsertInOrder(node);
                ret = hLuan;
                cur = hLuan;
                while(cur->next && cur->next->key == key2+1)
                {
                    key2++;
                    cur = cur->next;
                }
                hLuan = cur->next;
                cur->next = NULL;

            }
        }
        else
        {
            funcInsertInOrder(node);
            return NULL;
        }
    }
     
    return ret;
}

char* printOutStream(struct oStream nodeIn[], int count, int* returnSize)
{
    int i = 0;
    int   curKey = 1;
    char  curIndex = 0;
    char* outStream = (char*)malloc(128);
    struct oStream *node = NULL;
    struct oStream *curNode= NULL;

    outStream[curIndex++] = '[';
    for(i=0; i<count; i++)
    {
        node = findInLuan(curKey, nodeIn[i]);
        if(node)
        {
            outStream[curIndex++] = '[';
            //output in order
            while(node)
            {
                //printf("--- [%d,%s]---\n", node->key, node->value);
                curNode = node;
                node = node->next;
                strcpy(outStream+curIndex, curNode->value);
                curIndex += strlen(curNode->value);
                curKey = curNode->key+1;
                free(curNode);
                if(node) outStream[curIndex++] = ',';
            }
                outStream[curIndex++] = ']';
                outStream[curIndex++] = ',';
        }
        else
        {
            if(nodeIn[i].key == curKey)
            {
                outStream[curIndex++] = '[';
                //printf("--- [%d,%s]---\n", nodeIn[i].key, nodeIn[i].value);
                strcpy(outStream+curIndex, nodeIn[i].value);
                curIndex += strlen(nodeIn[i].value);
                outStream[curIndex++] = ']';
                outStream[curIndex++] = ',';
                curKey++;
            }
            else
            {
                //printf("--- [] ---\n");
                outStream[curIndex++] = '[';
                outStream[curIndex++] = ']';
                outStream[curIndex++] = ',';
            }
        }

    } //endfor
    outStream[curIndex-1] = ']';

    *returnSize = curIndex;
    printf("============== finally !!===========\n");
    printf("len = %d \n", *returnSize);
    printf("outStream = %s \n", outStream);
}

int main()
{

    struct oStream nodeIn[] = { 
        {5,"5fffff", NULL}, {3,"3aaa", NULL},{1, "1ff", NULL},{6, "6xxx", NULL},
        {2, "2ppp", NULL}, {4, "4kkkk", NULL}
    };
    int count = sizeof(nodeIn)/sizeof(struct oStream);
    char *outStream = NULL;
    int outLen = 0;
    outStream = printOutStream(nodeIn, count, &outLen);


    //printf("result: %s\n", outStream);
    return 0;
}
