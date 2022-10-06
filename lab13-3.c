#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct list{
    int *arr;
    int s;
    int e;
}list_t;


void dfs(list_t *g,int i,int n,int *v,int *c)
{
    v[i]=1;
    (*c)++;
    g[i].s = *c;
    for(int j=0;j<n;j++){
       if(!v[j]&&g[i].arr[j]==1)
            dfs(g,j,n,v,c);
    }
    (*c)++;
    g[i].e = *c;
}

void scc(list_t *g,int n){
    int *v = malloc(sizeof(int)*n);
    int *v2 = malloc(sizeof(int)*n);
    int c=0;
    for(int i=0;i<n;i++){
        if(g[i].s==0)
            dfs(g,i,n,v,&c);
    }
    list_t *t = malloc(sizeof(list_t)*n);
    for(int i=0;i<n;i++){
        t[i].arr = malloc(sizeof(int)*n);
        t[i].s = 0;
        t[i].e = 0;
        for(int j=0;j<n;j++){
            t[i].arr[j] = 0;
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) 
            t[j].arr[i] = g[i].arr[j];
    int cc = c;
    int num=-1;
    c = 0;
    for(int j = cc; j > 0; --j){
        for(int i = 0; i < n; ++i){
            if(g[i].e==j&&t[i].s==0){
                dfs(t,i,n,v2,&c);
            }
        }
    }
   
    
    int *ans = malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        ans[i] = -1;
    int count = 1;
    while(count<=c){
        int *arr = malloc(sizeof(int)*n);
        int a=-1 ;
        for(int i = 0; i < n; ++i)
            arr[i] = -1;
        for(int i = 0; i < n; ++i){
            if(t[i].s == count){
                arr[i] = 0;
                 a = i;
                 break;
            }
        }
        while(count!=t[a].e){
            count++;
            for(int i = 0; i < n; ++i){
                if(t[i].s == count||t[i].e == count){
                    arr[i] = 0;
                    break;
                }
            }
        }
        count++;
        int c1=0,c2=0;
        for(int i = 0; i < n; ++i){
            if(ans[i]==0)
                c1++;
            if(arr[i]==0)
                c2++;
        }
        if(c2>c1){
            for(int i = 0; i < n; ++i)
                ans[i] = arr[i];
        }
        free(arr);
    }
    for(int i = 0; i < n; ++i)
        if(ans[i]==0)
            printf("%d ",i);
    printf("\n");
}

int main()
{
    int m,n,u,v;
    scanf("%d %d", &n,&m);
    list_t *list = malloc(sizeof(list_t)*n);
    for(int i=0;i<n;i++){
        list[i].arr = malloc(sizeof(int)*n);
        list[i].s = 0;
        list[i].e = 0;
        for(int j=0;j<n;j++){
            list[i].arr[j] = 0;
        }
    }
    
    for(int i=0;i<m;i++){
        scanf("%d %d", &u,&v);
        list[u].arr[v] = 1;
    }
    

    scc(list,n);
}
