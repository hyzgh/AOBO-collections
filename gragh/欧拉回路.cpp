int head[Max_N]= {-1};
struct Edge
{
    int to,next,w;
} edge[Max_M];

void dfs(int x)
{
    t.push(x);
    for(int i=1; i<=n; i++)
    {
        if(path[x][i])         //�ҵ����߲�ɾ�����Ӹõ����dfs
        {
            path[x][i]=path[i][x]=0;//ɾ���˱�
            dfs(i);
            break;
        }
    }
}
void  Fleury(int x)
{
    t.push(x);
    while(!t.empty())
    {
        int b=0;
        for(int i=1; i<=n; i++)
        {
            if(path[t.top()][i])
            {
                b=1;
                break;
            }
        }
        if(!b)                       //����ĵ�û������
        {
            printf("%d ",t.top());  //����õ�     ���·��
            t.pop();
        }
        else                //���� ������������
        {
            int y=t.top();
            t.pop();
            dfs(y);
        }
    }
    printf("\n");
}

/*path*/
int ans[max_m];
int ansi=0;  //for counting
bool visit[2*max_m];    //"2*" means undirected graph
void dfs(int now)
{
    for(int k=edge[now][i]; k!=0; k=edge[k].next)
    {
        if(!vis[k])
        {
            vis[k]=true;         //sign the edge
            vis[k^1]=true;       //sign the reverse edge
            dfs(edge[k].to);
            ans[cnt++]=k;
        }
    }
}
int main()
{
    memset(s,0,sizeof s);       //����0��ʼ��memsetΪ-1
    for(int i=1; i<=m; i++)     //mΪ����
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        edge[i].to=b;
        edge[i].w=c;
        edge[i].next=head[a];
        head[a]=i;
    }
    for(int i=1; i<=n; i++)    //nΪ������
    {
        for(int k=head[i]; k!=0; k=edge[k].next)
        {
            cout<<i<<" "<<edge[k].to<<endl;
        }
    }
    return 0;
}
