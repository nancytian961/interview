void initPatt(char*** pp)
{
    *pp = (char**)malloc(sizeof(char*)*3);
    (*pp)[0] = (char*)malloc(sizeof(char)*(16));
    (*pp)[1] = (char*)malloc(sizeof(char)*(16));
    (*pp)[2] = (char*)malloc(sizeof(char)*(16));
}

#if 0
void cpyPatt(char** dst, char** src)
{
    printf("cpyPatt, src : %s, %s, %s\n", src[0], src[1], src[2]);
   strcpy(dst[0], src[0][0]);
     printf("cpyPatt, dst : %s \n", dst[0]);
    strcpy(dst[1], src[0][1]);
    printf("cpyPatt, dst : %s, %s\n", dst[0], dst[1]);
    strcpy(dst[2], src[0][2]);
    printf("cpyPatt, ret : %s, %s, %s\n", dst[0], dst[1], dst[2]);
}
#endif
        
void freePatt(char** pp)
{
    free(pp[0]);
    free(pp[1]);
    free(pp[2]);
    free(pp);
}

void sortbyusr(char ** username, int usernameSize, int* timestamp, char ** website)
{
    int i = 0, j = 0;
    char* user = NULL;
    int   tms  = 0;
    char* webs = NULL;
    
    for(i=1;i<usernameSize; i++)
    {
        user = username[i];
        tms  = timestamp[i];
        webs = website[i];
        j = i-1;
        while(j>=0 &&  strcmp(user, username[j]) < 0)
        {
            username[j+1] = username[j];
            timestamp[j+1] = timestamp[j];
            website[j+1] = website[j];
            j--;
        }
        username[j+1] = user;
        timestamp[j+1] = tms;
        website[j+1] = webs;
    }
}

void sortbytime(int* timestamp, char** website, int s, int e)
{
    int i = 0, j = 0;
    int   tms  = 0;
    char* webs = NULL;
    for(i=s+1; i<e; i++)
    {
        tms  = timestamp[i];
        webs = website[i];
        j = i-1;
        while(j>=s &&  tms < timestamp[j])
        {
            timestamp[j+1] = timestamp[j];
            website[j+1] = website[j];
            j--;
        }
        timestamp[j+1] = tms;
        website[j+1] = webs;
    }
    
    //for(i=s; i<e; i++)
    {
        //printf(" [%d %s]", timestamp[i], website[i]);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** mostVisitedPattern(char ** username, int usernameSize, 
                           int* timestamp, int timestampSize, 
                           char ** website, int websiteSize, int* returnSize)
{   
    
    //1
    sortbyusr(username, usernameSize, timestamp, website);
    
   
    //2 pattern
    int pattlen = websiteSize*(websiteSize-1)*(websiteSize-2);
    char*** pattern = (char***)malloc(sizeof(char**)*(pattlen));
    char* user = username[0];
    int s = 0, e = 0;
    int i = 0;
    int m1 = 0, m2 = 0, m3 = 0,k = 0;
    for(i=1; i<usernameSize; i++)
    {
        if(strcmp(username[i], user) != 0)
        {
            e = i-1;
            sortbytime(timestamp, website, s, i);
            printf("s= %d e = %d\n", s, e);
            if(e-s >= 2)
            {
                for(m1=s; m1<i-2; m1++)
                {
                    for(m2=m1+1; m2<i-1; m2++)
                    {
                        for(m3=m2+1; m3<i; m3++)
                        {
                            initPatt(&(pattern[k]));   
                            strcpy(pattern[k][0], website[m1]);
                            strcpy(pattern[k][1], website[m2]);
                            strcpy(pattern[k][2], website[m3]);
                            k++; 
                        }
                    }
                }
            }
            
            s = i;
            e = i;
            user = username[i];
        }        
    }
    
    if(i-s >= 3)
    {   
        sortbytime(timestamp, website, s, i);
        for(m1 = s; m1<i-2; m1++)
        {
            for(m2=m1+1; m2<i-1; m2++)
            {
                for(m3=m2+1; m3<i; m3++)
                {
                    initPatt(&(pattern[k]));
                   
                    strcpy(pattern[k][0], website[m1]);
                    strcpy(pattern[k][1], website[m2]);
                    strcpy(pattern[k][2], website[m3]);
                    k++; 
                }
            }
        }
    }
    //printf("pattern number : k = %d\n", k);
    
    if(k == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    if(k == 1)
    {
        *returnSize = 3;
        char ** ret = NULL;
        initPatt(&ret);
       
        strcpy(ret[0], pattern[0][0]);
        strcpy(ret[1], pattern[0][1]);
        strcpy(ret[2], pattern[0][2]);
        //cpyPatt(ret, pattern[0]);
        //printf(" k==1, ret : %s, %s, %s\n", ret[0], ret[1], ret[2]);
        freePatt(pattern[0]);
        free(pattern);
        return ret;
    }
  
   
   //3 compare
    int j = 0;
    int max = 1, index = 0;
    int cmp1 = 0, cmp2 = 0, cmp3 = 0;
    
    int* count = (int*)malloc(sizeof(int*)*(k+1));
    count[0] = 1;
    
    for(i=1; i<k; i++)
    {
        printf("i=%d : [%s, %s, %s] \n",  i, pattern[i][0],  pattern[i][1],  pattern[i][2]);  
        for(j=i-1; j>=0; j--)
        {
            if( strcmp(pattern[i][0], pattern[j][0]) == 0
                && strcmp(pattern[i][1], pattern[j][1]) == 0
                && strcmp(pattern[i][2], pattern[j][2]) == 0 )
            {
                count[i] = count[j]+1;
                if(max < count[i])
                {
                    max = count[i];
                    index = i;
                }
                break;
            } 
        }
        if(j == -1)
        {
            count[i] = 1;
        }
    }
    
    //4 ret
    char ** ret = NULL ;
    initPatt(&ret);
    //cpyPatt(&ret, pattern[index]);
    strcpy(ret[0], pattern[index][0]);
    strcpy(ret[1], pattern[index][1]);
    strcpy(ret[2], pattern[index][2]);
    printf("ret : [%s, %s, %s] , max =%d\n", ret[0], ret[1], ret[2], max);  
    for(i = 0; i<k; i++)
    {
        if(max == count[i] && index != i)
        {
            printf("i : [%s, %s, %s] \n",  pattern[i][0],  pattern[i][1],  pattern[i][2]);  
            cmp1 = strcmp(ret[0], pattern[i][0]);
            cmp2 = strcmp(ret[1], pattern[i][1]);
            cmp3 = strcmp(ret[2], pattern[i][2]);
            //printf("cmp: [%d %d %d]\n", cmp1, cmp2, cmp3);
            if(cmp1 > 0)
            {
                strcpy(ret[0], pattern[i][0]);
                strcpy(ret[1], pattern[i][1]);
                strcpy(ret[2], pattern[i][2]);
            }
            else if(cmp1== 0 && cmp2 > 0)
            {
                strcpy(ret[0], pattern[i][0]);
                strcpy(ret[1], pattern[i][1]);
                strcpy(ret[2], pattern[i][2]);
            }
            else if(cmp2 == 0 && cmp3 > 0)
            {
                 strcpy(ret[0], pattern[i][0]);
                strcpy(ret[1], pattern[i][1]);
                strcpy(ret[2], pattern[i][2]);
            }
            printf("----------- ret : [%s, %s, %s] \n", ret[0], ret[1], ret[2]); 
        }
    }
       
    for(i=0; i<k; i++)
        freePatt(pattern[i]);      
    free(pattern);
    free(count);
    
    //printf("ret : [%s, %s, %s] \n", ret[0], ret[1], ret[2]);  
    *returnSize = 3;
    return ret;

}
