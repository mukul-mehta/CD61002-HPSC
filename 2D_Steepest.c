#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void mulAx(double *p,double q[],double r[],int n){
  int i,j;
  double sum=0;
  for(i=0;i<n;i++){
    sum=0;
    for(j=0;j<n;j++){
      sum=sum+*(p+i*n+j)*q[j];
    }
    r[i]=sum;
  }
}
//vector vector dot product /
double mulxy(double *p,double *q,int n){  
  int i; double sum;
  sum=0;
  for(i=0;i<n;i++){
    sum=sum+*(p+i)**(q+i);
  }
  return sum;
}
//vector matrix dot product //
int mulyAx(double *y,double *A,double *x,int n){
int i; double sum;
  sum=0;
  for(i=0;i<n;i++){
    sum=sum+*(y+i)*mulxy(A+i*n,x,n);
  }
  return sum;

}

int main(){
  int R;
  printf("Enter the size of the interior mesh:\n");
  scanf("%d",&R);
  int MESH[R][R];
  int ii,jj;
  for(jj=0;jj<R;jj++){
    for(ii=0;ii<R;ii++){
      MESH[ii][jj]=jj*R+ii;
    }
  }
  int n;n=R*R;
  double A[n][n];double b[n];
  int i,j,k;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        A[i][j]=0;
    }
    b[i]=0;
  }
  for(jj=1;jj<(R-1);jj++){
    for(ii=1;ii<(R-1);ii++){
      A[MESH[ii][jj]][MESH[ii+1][jj]]=1;
      A[MESH[ii][jj]][MESH[ii-1][jj]]=1;
      A[MESH[ii][jj]][MESH[ii][jj+1]]=1;
      A[MESH[ii][jj]][MESH[ii][jj-1]]=1;
      A[MESH[ii][jj]][MESH[ii][jj]]=-4;
    }
  }
  double Tb,Tt,Tl,Tr;
  printf("Enter the value of tempertaure at bottom boundary:\n");
  scanf("%lf",&Tb);
  printf("Enter the value of tempertaure at top boundary:\n");
  scanf("%lf",&Tt);
  printf("Enter the value of tempertaure at left boundary:\n");
  scanf("%lf",&Tl);
  printf("Enter the value of tempertaure at right boundary:\n");
  scanf("%lf",&Tr);

  for(jj=1;jj<R-1;jj++){
    A[MESH[0][jj]][MESH[1][jj]]=1;
    A[MESH[0][jj]][MESH[0][jj+1]]=1;
    A[MESH[0][jj]][MESH[0][jj-1]]=1;
    A[MESH[0][jj]][MESH[0][jj]]=-4;
    b[MESH[0][jj]]=-Tl;
  }
  for(jj=1;jj<R-1;jj++){
    A[MESH[R-1][jj]][MESH[R-2][jj]]=1;
    A[MESH[R-1][jj]][MESH[R-1][jj+1]]=1;
    A[MESH[R-1][jj]][MESH[R-1][jj-1]]=1;
    A[MESH[R-1][jj]][MESH[R-1][jj]]=-4;
    b[MESH[R-1][jj]]=-Tr;
  }
  for(ii=1;ii<R-1;ii++){
    A[MESH[ii][0]][MESH[ii+1][0]]=1;
    A[MESH[ii][0]][MESH[ii-1][0]]=1;
    A[MESH[ii][0]][MESH[ii][1]]=1;
    A[MESH[ii][0]][MESH[ii][0]]=-4;
    b[MESH[ii][0]]=-Tb;
  }
  for(ii=1;ii<R-1;ii++){
    A[MESH[ii][R-1]][MESH[ii+1][R-1]]=1;
    A[MESH[ii][R-1]][MESH[ii-1][R-1]]=1;
    A[MESH[ii][R-1]][MESH[ii][R-2]]=1;
    A[MESH[ii][R-1]][MESH[ii][R-1]]=-4;
    b[MESH[ii][R-1]]=-Tt;
  }
  A[MESH[0][0]][MESH[0][1]]=1;
  A[MESH[0][0]][MESH[1][0]]=1;
  A[MESH[0][0]][MESH[0][0]]=-4;
  b[MESH[0][0]]=-Tl-Tb;
  A[MESH[R-1][0]][MESH[R-2][0]]=1;
  A[MESH[R-1][0]][MESH[R-1][1]]=1;
  A[MESH[R-1][0]][MESH[R-1][0]]=-4;
  b[MESH[R-1][0]]=-Tr-Tb;
  A[MESH[R-1][R-1]][MESH[R-1][R-2]]=1;
  A[MESH[R-1][R-1]][MESH[R-2][R-1]]=1;
  A[MESH[R-1][R-1]][MESH[R-1][R-1]]=-4;
  b[MESH[R-1][R-1]]=-Tr-Tt;
  A[MESH[0][R-1]][MESH[0][R-2]]=1;
  A[MESH[0][R-1]][MESH[1][R-1]]=1;
  A[MESH[0][R-1]][MESH[0][R-1]]=-4;
  b[MESH[0][R-1]]=-Tl-Tt;

  double x0[n],x1[n],r[n],p[n];


  for(i=0;i<n;i++){
    printf("\n");
    for(j=0;j<n;j++){
      printf("%lf  ",A[i][j]);
    }
    printf("%lf ",b[i]);
  }printf("\n");

  for(i=0;i<n;i++){
    x1[i]=0;
    x0[i]=0;
  }
  double epsilon,error;int count; 
  double *ptr;
  ptr=&A[0][0];
  for(i=0;i<n;i++){
  r[i]=b[i]-mulxy(ptr+i*n,x0,n); \\//r=b-Ax, A is stored in vector form//
  }
  

  double alpha;
  mulAx(ptr,r,p,n); //p=Ar//

  printf("Enter the desired accuracy:");
  scanf("%lf",&epsilon);
  count=0;
  error=2*epsilon;

  while(error>epsilon && count<2000){ //iteration loop starts

  for(k=0;k<n;k++){
    x0[k]=x1[k];
  }

    alpha=mulxy(r,r,n)/mulxy(p,r,n); //calculate alpha//

    for(i=0;i<n;i++){
    x1[i]=x1[i]+alpha*r[i];
    r[i]=r[i]-alpha*p[i];
    }

 
    mulAx(ptr,r,p,n);//Calculate r within the loop

    error=fabs(x1[0]-x0[0]);
    for(k=1;k<n;k++){
    if(error<fabs(x1[k]-x0[k])){error=fabs(x1[k]-x0[k]);}
    }
    count++;
    printf("Iteration %d Error=%lf\n",count,error);
  }

  for(k=0;k<n;k++){
  printf("Final x[%d]=%lf\n",k,x1[k]);}


  return 0;
}
