#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Empty -1
#define Size 55
const int ASCII0=48;
int Table[Size][Size],Subtree[Size][3],dis_Table[20][20];
int Selected_Edges[Size][3],Steiner[Size][3];
int Searched_Edges[Size][3];
int SEC,n_Edge;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,i,j,n,x,y;
	int MRST, MSpT;
	char flag=1;
	do{
		open_file();
		modify_Table();		
		distance();
		/**********
		 *Calculate each vertex's distance to each other.
		 **********/
		MSpT=prim_Algorithm();
		/**********
		 *Use dis_Table to find the minimum spanning tree. 
		 **********/
		printf("\nChoose (1)x axis or (2)y axis first when weight is even.");
		a=ask();
		printf("\nChoose (1)short edge or (2)long edge first for rectangle.");
		b=ask();
		printf("\na=%d b=%d\n",a,b);
		n=find_Steiner();	//n=total numbers of steiner points.		
		/**********
		 *Grow the whole steiner points.
		 **********/
		final_Vertex(a,b,n);
		/**********
		 *Delete the no used steiner points and create the table of used vertex.
		 **********/
		distance();	
		MRST=prim_Algorithm();		
		improved_Result(MRST, MSpT);
		/*********
		 *Compare two parameters and show the information.
		 *********/
		flag=ask_Restart();
		/**********
		 *If flag==1 than restart from the beginning, else will end the program. 
		 **********/
	}while(flag==1);
	system("pause");
	return 0;
}
void final_Vertex(int a, int b, int n){
	int Vx,Vy,i,j;
	int TVN,c=1,flag;
	TVN=dis_Table[0][1];
	for(i=1;i<=n;i=i+2){		
		if(Steiner[i][2]==2 && Steiner[i+1][2]==2){
			if(a==1){
				Vx=Steiner[i+1][0];
				Vy=Steiner[i+1][1];
			}
			else{
				Vx=Steiner[i][0];
				Vy=Steiner[i][1];
			}
		}
		else if(b==1){
			if(Steiner[i][2]==0 && Steiner[i+1][2]==1){
				Vx=Steiner[i][0];
				Vy=Steiner[i][1];
			}
			else{
				Vx=Steiner[i+1][0];
				Vy=Steiner[i+1][1];
			} 
		} 
		else if(b==2){
			if(Steiner[i][2]==1 && Steiner[i+1][2]==0){
				Vx=Steiner[i][0];
				Vy=Steiner[i][1];
			}
			else{
				Vx=Steiner[i+1][0];
				Vy=Steiner[i+1][1];
			} 
		} 
		else {
			printf("\ncheck\n");
			break;			
		}		
		for(j=1;j<TVN+c;j++){
			if(Table[j][1]==Vx && Table[j][2]==Vy){
				flag=0;				
				break;
			}
			else flag=1;
		}		
		while(flag==1){
			Table[TVN+c][1]=Vx;
			Table[TVN+c][2]=Vy;
			c++; break;
		}
	}
	Table[0][1]=TVN+c-1;
}
int find_Steiner(void){
	int i,j,n,Vax,Vay,Vbx,Vby;
	n=1;
	for(i=0;i<Size;i++){
		for(j=0;j<3;j++) Steiner[i][j]=0;
	}
	for(i=0;i<n_Edge;i++){
		Vax=Table[Selected_Edges[i][0]][1];
		Vay=Table[Selected_Edges[i][0]][2];
		Vbx=Table[Selected_Edges[i][1]][1];
		Vby=Table[Selected_Edges[i][1]][2];		
		if(Vby-Vay!=0 && Vbx-Vax!=0){
			if(Vax<Vbx){			
				Steiner[n][0]=Vax;
				Steiner[n][1]=Vby;
				Steiner[n+1][0]=Vbx;
				Steiner[n+1][1]=Vay;
				if(fabs(Vby-Vay)<fabs(Vbx-Vax)){
					Steiner[n][2]=0;
					Steiner[n+1][2]=1;
				}
				else if(fabs(Vby-Vay)>fabs(Vbx-Vax)){
					Steiner[n][2]=1;
					Steiner[n+1][2]=0;
				}
				else{
					Steiner[n][2]=2;
					Steiner[n+1][2]=2;
				}
				n=n+2;
			}
			else{
				Steiner[n][0]=Vbx;
				Steiner[n][1]=Vay;
				Steiner[n+1][0]=Vax;
				Steiner[n+1][1]=Vby;
			
				if(fabs(Vby-Vay)>fabs(Vbx-Vax)){
					Steiner[n][2]=0;
					Steiner[n+1][2]=1;
				}
				else if(fabs(Vby-Vay)<fabs(Vbx-Vax)){
					Steiner[n][2]=1;
					Steiner[n+1][2]=0;
				}
				else{
					Steiner[n][2]=2;
					Steiner[n+1][2]=2;
				}
				n=n+2;
			}
		}		
	}
	return n-1;
}
void improved_Result(int MRST, int MSpT){
	float div;
	div=(float)MRST/(float)MSpT;
	printf("============Final Result=============\n");
	printf("Ratio of MRST/MSpT = %d/%d = %f\n",MRST,MSpT,div);
	if(div==1) printf("Doesn't improved.\n");
	else if(div<1 && div>0){
		printf("Decrease: %d\n",MSpT-MRST);
		printf("Improved: %f%c\n",100*(1-div),37);
	}
	else printf("Error result.\n");
}
int ask_Restart(void){
	int i,j,flag;
	do{
		j=0;
		printf("\nWant to restart the program?(Y/N)");
		i=getch();
		if(i==89||i==121){
			flag=1; j=1;
			system("cls");
		} 
		else if(i==78||i==110){
			flag=0; j=1;
		} 
		else{
			printf("\nPlease enter Y/N");
			flag=0; j=0;
		} 
	}while(j==0);
	return flag;
}
int ask(void){
	int i, j;
	char flag;	
	do{
		i=getch();
		if(i==49){
			flag=1; return 1;
		} 
		else if(i==50){
			flag=1; return 2;
		}
		else{
			printf("\nplease enter 1/2.");
			flag=0;
		}
	}while(flag!=1);
}
void distance(void) {
	int ax,ay,bx,by,x,y;
	int i,j;	
	for(i=0;i<10;i++)
		for(j=0;j<10;j++) dis_Table[i][j]=0;	
	for(i=1;Table[i][1]!=Empty;i++){
		ax=Table[i][1]; ay=Table[i][2];
		for(j=i+1;Table[j][1]!=Empty;j++){
			bx=Table[j][1]; by=Table[j][2];
			x=bx-ax; y=by-ay;
			if(x<0) x=x-2*x;
			if(y<0) y=y-2*y;
			dis_Table[i][j]=x+y;
		}
	}	
	dis_Table[0][1]=Table[0][1];	
	for(i=1; i<=dis_Table[0][1];i++){
		for(j=i+1; j<=dis_Table[0][1];j++){
			dis_Table[j][i] = dis_Table[i][j];			
		}
	}
}
int prim_Algorithm(void) {
	int i,j,n,sum;
	int TVN=0;
	TVN = dis_Table[0][1];	//total vertex number
	n_Edge=0; SEC=0;
	for(i=0;i<Size;i++){
		for(j=0;j<3;j++){
			Subtree[i][j]=0;
			Selected_Edges[i][j]=0;
			Searched_Edges[i][j]=0;
		}
	} 	
	find_Subtree(1,TVN);
	while(n_Edge<TVN-1){
		n=choose_Edge();
		n_Edge++;
		if(n_Edge<TVN-1) {
			find_Subtree(n,TVN);			
		}
		else break;		
	}	
	sum=show_Result();	
	return sum;
}
void open_file(void) {
	FILE *fp;
	int i,count=0;
	char fname[50],line[Size];
	/*Enter a file name*/
	printf("Enter a file:");
	gets(fname);
	/*convert txt to array*/
	fp = fopen(fname, "r");
	if(fp!=NULL) {
		printf("Opening file:[%s]\n", fname);
		while(fgets(line,Size,fp)!=NULL) {
			printf("%s",line);
			for(i=0; i<Size; i++) {
				Table[count][i]=line[i];
			}
			count++;
		}
		fclose(fp);
	} 
	else{
		printf("Open [%s] file fail.", fname);
		exit(1);
	} 	
	printf("\n");
}
void modify_Table(void){
	int i,j,n,sum=0;
	/*Convert ASCII to integer and remove the control characters*/
	for(i=0;i<Size;i++){
		n=1;
		for(j=0;j<Size;j++){
			if(Table[i][j]!=0){			
				if(Table[i][j]>=ASCII0 && Table[i][j]<=ASCII0+9)
					sum=sum*10+Table[i][j]-ASCII0;	//For the value is bigger than 10
				else{
					Table[i][n]=sum;
					sum=0;
					n++;
				}
			}
			else break;
		}		
		for(;n<Size;n++)Table[i][n]=Empty;	//Fill "Empty" to unused space	
	}
}
void find_Subtree(int v1,int TVN){
	int i,v2,weight,n;
	int j,min,i_min,temp;
	char flag;
	n=0;
	/*find edges*/
	for(v2=1;v2<=TVN;v2++){
		weight=dis_Table[v1][v2];
		if(weight!=0 && weight!=Empty){
			/*check the edge has been searched or not*/
			flag=0;
			for(i=0;i<=SEC;i++){
				if((v1==Searched_Edges[i][0] && v2==Searched_Edges[i][1]) 
				|| (v1==Searched_Edges[i][1] && v2==Searched_Edges[i][0])){
					flag=0;
					break;
				}					
				else flag=1;
			}
			while (flag==1){
				Subtree[n][0]=v1;
				Subtree[n][1]=v2;
				Subtree[n][2]=weight;
				n++;
				Searched_Edges[SEC][0]=v1;
				Searched_Edges[SEC][1]=v2;
				SEC++;
				flag=0;								
			}
		}
	}
	/*sort the Subtree*/
	for(i=0;i<Size;i++){
		/*comparison*/
		min=Subtree[i][2];
		for(j=i+1;j<Size;j++)
			while(Subtree[j][2]<min){
				min=Subtree[j][2];
				i_min=j;
				flag=1;
		}		
		while(flag==1){
			for(j=0;j<=2;j++){
				/*swap*/
				temp=Subtree[i][j];
				Subtree[i][j]=Subtree[i_min][j];
				Subtree[i_min][j]=temp;
			}
			flag=0;
		}		
	}	
}
int choose_Edge(void){
	int i,j,v2;
	char flag;
	flag=1;
	for(i=0;flag!=0;i++){
		while(Subtree[i][0]==0) i++;
		v2=Subtree[i][1]; 
		flag=loop_Check(v2);
		if(flag==0) break;
		else {
			printf("%c-%c(%d) will create a loop. Ignore it.\n",
				Subtree[i][0]+64,Subtree[i][1]+64,Subtree[i][2]);
			for(j=0;j<=2;j++) Subtree[i][j]=0;
		}
	}
	for(j=0;j<=2;j++) Selected_Edges[n_Edge][j]=Subtree[i][j];
	v2=Selected_Edges[n_Edge][1];
	for(j=0;j<=2;j++) Subtree[i][j]=0;	
	return v2;
}
int loop_Check(int v2){
	int i,j; char flag=0;
	for(i=0;i<=n_Edge;i++){
		if(v2==Selected_Edges[i][1]){
			flag=1;			
			break;
		}
		else flag=0;		
	}
	return flag;
}
int show_Result(void) {
	int i,sum;
	sum=0;
	for(i=0;i<n_Edge;i++)sum=sum+Selected_Edges[i][2];
	printf("MST has found!\n");
	printf("The final path is\n");
	for(i=0;i<n_Edge;i++) printf("%c-%c(%d) -> ",Selected_Edges[i][0]+64,
							Selected_Edges[i][1]+64,Selected_Edges[i][2]);
	printf("The weight of the MST is %d\n",sum);
	return sum;	
}