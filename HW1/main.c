#include <stdio.h>
#include <stdlib.h>
#define White 0
#define Gray 1
#define Black 2
#define Empty -1
#define Infinite -1 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char table[10][10]= {0};
int Queue[10];
int d[10],up[10];
int color[10];
int Path[10];
const int ASCII0=48;
int u,p=0;
int max_u;
int Qn=0;
int main(int argc, char *argv[]) {
	int s,v;
	int b,i;
	for(i=0;i<10;i++){
		Queue[i]=Empty;
		d[i]=Infinite;
		up[i]=Empty;
		color[i]=White;
	}
	
	open_file();
	modify_table();
	
	s=table[0][0]-ASCII0;
	//printf("s=%d\n",s);
	color[s]=Gray;
	d[s]=0;
	up[s]=Empty;
	EnQueue(s);

	while(Queue[0]!=Empty){
		u=DeQueue(b);
		i=0;
		while(table[u][i]!=Empty){
			v=table[u][i]-ASCII0;
			if(color[v]==White){
				color[v]=Gray;
				d[v]=d[u]+1;
				up[v]=u;
				EnQueue(v);
			}
			i++;
		}
		color[u]=Black;
		show_status(u);				
	}	
	show_result();
	system("pause");
	return 0;
}
void open_file(void) {
	FILE *fp;
	int count=0;
	int i;
	char fname[50], line[10]= {0};

	printf("file name:");
	gets(fname);

	fp = fopen(fname, "r");
	if(fp!=NULL) {
		printf("Opening file : [%s]\n", fname);
		while(fgets(line,10,fp) != NULL) {
			printf("%s",line);
			for(i=0; i<10; i++) {
				table[count][i]=line[i];
			}
			count++;
		}
		fclose(fp);
	} else	printf("Open [%s] file fail.", fname);
	printf("\n\n");
}
void modify_table(void){
	//char temp[10]={0};
	int i,j,m,n;
	int count=-1;
	int sum;
	/*for(i=1;i<10;i++){
		n=0;
		for(j=0;j<10;j++){
			if(table[i][j]==0){
				break;
			}
			else if(table[i][j]>=ASCII0 && table[i][j]<=(ASCII0+9)){
				count++;
			}
			else{
				sum=0;
				for(m=j;count>=0;count--){
					sum=sum+(table[i][m-count]-ASCII0)*10^count;
				}
				table[i][n]=sum;
				n++;
			}
				
		}
		while(n<10){
			table[i][n]=Empty;
			n++;
		}
	}*/
	
	for (i=1;i<10;i++){
		if(table[i][0]-ASCII0==i){
			n=0;
			for(j=2;j<10;j++){				
				if(table[i][j]!=0 && 
				table[i][j]>=ASCII0 && table[i][j]<=(ASCII0+9)){
					table[i][n]=table[i][j];
					n++;
				}				
			}
			while(n<10){
				table[i][n]=Empty;
				n++;
			}
		}
		else break;		
	}
}
void EnQueue(int n){
	Queue[Qn]=n;
	Qn++;
}
int DeQueue(int b){
	int i;
	b=Queue[0];
	Path[p]=Queue[0];
	for(i=1;i<=Qn;i++) Queue[i-1]=Queue[i];
	Qn--;
	p++;
	return b;
}
void show_status(int now) {
	int i;
	printf("Choosen vertex is %d\n",now);
	printf("Next vertex is\n");
	i=0;
	while(table[now][i]!=Empty){
		printf("node=%d ",table[now][i]-ASCII0);
		printf("Distance is %d ",d[table[now][i]-ASCII0]);
		if(color[i]==Black)printf("Visited Vertex -> Throw Away");
		printf("\n");
		i++;
	}
	printf("\n");
}
void show_result(void) {
	int i;
	printf("The final path is\n");
	for(i=0;i<p;i++) printf("%d -> ",Path[i]);
	printf("Done!\n");
	printf("BFS is finished!\n");
}
