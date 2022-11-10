#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define  MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;
int distance[MAX_VERTICES]; //최단경로의 거리
int found[MAX_VERTICES]; // 방문한 정점표시

//최단경로가 찾아진 정점집합s에 속하지 않는 정점들 중에서 현재의 dist값이 가장 작은 정점의 인덱스를 반환 하는 함수
int choose(int *distance,int n,int *found)
{
    int i,min,minpos;
    min=INT_MAX;
    minpos=-1;
    for(int i=0;i<n;i++)
    {
        if(distance[i]<min && !found[i])
        {
            min=distance[i];
            minpos=i;
        }
    }
    return minpos;
}
//각 step에서의 최종 경로 정보를 출력하는 함수
void print_status(GraphType *g)
{
    static int step=1;
    printf("STEP %d: ",step++);
    printf("distance: ");
    for(int i=0;i<g->n;i++)
    {
        if(distance[i]==INF) printf(" * ");
        else printf("%2d ",distance[i]);
    }
    printf("\n");
    printf("         found:   ");
    for(int i=0;i<g->n;i++)
    {
        printf("%2d ",found[i]);
    }
    printf("\n\n");
}


//dijkstra 최단경로 시작정점 start interger value ID

void shortest_path(GraphType *g,int start)
{
    int i,u,w;
    for(i=0;i<g->n;i++)
    {
        distance[i]=g->weight[start][i];
        found[i]=0;
    }
    found[start]=1; //시작정점 방문 표시
    distance[start]=0;

    for(i=0;i<g->n;i++) //모든정점이 s에 포함될때까지 실행
    {
        print_status(g); //step distance
        u=choose(distance,g->n,found); //가장작은 정점u를 찾음

        found[u]=1; //집합에 포함시킴

        for(w=0;w<g->n;w++)
        {
            if(found[w]==0)
            {
                if(distance[u]+g->weight[u][w]<distance[w])
                {
                    distance[w]=distance[u]+g->weight[u][w];
                }
            }
        }
    }
}
int main(){
    GraphType g={7,
    {
    {0,7,INF,INF,3,10,INF},
    {7,0,4,10,2,6,INF},
    {INF,4,0,2,INF,INF,INF},
    {INF,10,2,0,11,9,4},
    {3,2,INF,11,0,INF,5},
    {10,6,INF,9,INF,0,INF},
    {INF,INF,INF,4,5,INF,0}
    }
    };
    shortest_path(&g,0);
    return 0;
}