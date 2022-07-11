#include <stdio.h>
#include <math.h>

float divRe(a,b,c,d)
 float a,b,c,d;
 {
  float e;
  e=(a*c+b*d)/(c*c+d*d);
  return(e);
 }

float divIm(a,b,c,d)
 float a,b,c,d;
 {
  float e;
  e=(b*c-a*d)/(c*c+d*d);
  return(e);
 }

float mulRe(a,b,c,d)
 float a,b,c,d;
 {
  float e;
  e=a*c-b*d;
  return(e);
 }

float mulIm(a,b,c,d)
 float a,b,c,d;
 {
  float e;
  e=b*c+a*d;
  return(e);
 }

float Max(float a[],int n)
 {int i;
  float max;
  for(i=0;i<n-1;i++)
     if(a[i]>a[i+1])
       {max=a[i];a[i]=a[i+1];a[i+1]=max;}
  return(max);
 }


main()
{
 int i,j,k=0,n,km=6;
 float eps=0.00001,sumpi1,sumpi2,sumqi1,sumqi2,max,sumir,sumii,I1r,I1i;
 float pi0[5],qi0[5],detpi[5],detqi[5],Iir0[5],Iii0[5],J0[8][8],detsi[8],detui[8],
       u[8][8],l[8][8],y[8],ui1[8],H[4][4],N[4][4],J[4][4],L[4][4],ei1[5],fi1[5];

 static float ybr[5][5]={{6.250,-5.000,-1.250,0,0},{-5.000,10.834,-1.667,-1.667,-2.500},
			{-1.250,-1.667,12.917,-10.000,0},{0,-1.667,-10.000,12.917,-1.250},
			{0,-2.500,0,-1.250,3.750}};
 static float ybi[5][5]={{-18.750,15.000,3.750,0,0},{15.000,-32.500,5.000,5.000,7.500},
			{3.750,5.000,-38.750,30.000,0},{0,5.000,30.000,-38.750,3.750},
			{0,7.500,0,3.750,-11.250}};

 float ei0[5]={1.06,1.0,1.0,1.0,1.0};
 float fi0[5]={0,0,0,0,0};
 float pi[5]={0,0.2,-0.45,-0.4,-0.6};
 float qi[5]={0,0.2,-0.15,-0.05,-0.1};

 do{
   k+=1;
   printf("第 %d 次迭代\n",k);
   for(i=1;i<5;i++)
      printf("Pi[%d]=%-14.6f",i,pi[i]);
  sumpi2=0;
  sumqi2=0;
  for(i=1;i<5;i++)
     {for(j=0;j<5;j++)
	{
	 sumpi1=(ei0[i]*(ybr[i][j]*ei0[j]-ybi[i][j]*fi0[j])+fi0[i]*(ybr[i][j]*fi0[j]+ybi[i][j]*ei0[j]));
	 sumpi2+=sumpi1;
	}
      pi0[i]=sumpi2;
      printf("Pi0[%d]=%-13.6f",i,pi0[i]);
      sumpi2=0;
     }
  for(i=1;i<5;i++)
     {for(j=0;j<5;j++)
	{
	 sumqi1=(fi0[i]*(ybr[i][j]*ei0[j]-ybi[i][j]*fi0[j])-ei0[i]*(ybr[i][j]*fi0[j]+ybi[i][j]*ei0[j]));
	 sumqi2+=sumqi1;
	}
     qi0[i]=sumqi2;
     printf("Qi0[%d]=%-13.6f",i,qi0[i]);
     sumqi2=0;
     }
  for(i=1;i<5;i++)
    {
     detpi[i]=pi[i]-pi0[i];
     detqi[i]=qi[i]-qi0[i];
     printf("detpi[%d]=%-21.6f",i,detpi[i]);
     printf("detqi[%d]=%-21.6f\n",i,detqi[i]);
    }
  for(i=1;i<5;i++)
    {Iir0[i]=divRe(pi0[i],-qi0[i],ei0[i],-fi0[i]);
     Iii0[i]=divIm(pi0[i],-qi0[i],ei0[i],-fi0[i]);
     printf("Iir0[%d]=%-22.6f",i,Iir0[i]);
     printf("Iii0[%d]=%-22.6f\n",i,Iii0[i]);
    }
  for(i=0;i<4;i++)
    {for(j=0;j<4;j++)
	if(i==j) {
		 H[i][j]=-ybi[i+1][j+1]*ei0[i+1]+ybr[i+1][j+1]*fi0[i+1]+Iii0[i+1];
		 N[i][j]=ybr[i+1][j+1]*ei0[i+1]+ybi[i+1][j+1]*fi0[i+1]+Iir0[i+1];
		 J[i][j]=-ybr[i+1][j+1]*ei0[i+1]-ybi[i+1][i+1]*fi0[i+1]+Iir0[i+1];
		 L[i][j]=-ybi[i+1][j+1]*ei0[i+1]+ybr[i+1][j+1]*fi0[i+1]-Iii0[i+1];
		}
	else {
	      H[i][j]=ybr[i+1][j+1]*fi0[i+1]-ybi[i+1][j+1]*ei0[i+1];
	      N[i][j]=ybr[i+1][j+1]*ei0[i+1]+ybi[i+1][j+1]*fi0[i+1];
	      J[i][j]=-ybi[i+1][j+1]*fi0[i+1]-ybr[i+1][j+1]*ei0[i+1];
	      L[i][j]=ybr[i+1][j+1]*fi0[i+1]-ybi[i+1][j+1]*ei0[i+1];
	     }
    }
  for(i=0;i<8;i++)
     for(j=0;j<8;j++){
	if(i%2==0 && j%2==0) J0[i][j]=H[i/2][j/2];
	else if(i%2==0&&j%2!=0) J0[i][j]=N[i/2][(j-1)/2];
	else if(i%2!=0&&j%2==0) J0[i][j]=J[(i-1)/2][j/2];
	else J0[i][j]=L[i/2][(j-1)/2];
     }
	 printf("?:\n");
  for(i=0;i<8;i++)
     for(j=0;j<8;j++)
		 printf("%-10.4f",J0[i][j]);
  for(i=0;i<8;i++)
	{if(i%2==0) detsi[i]=detpi[(i+2)/2];
	 else detsi[i]=detqi[(i+1)/2];
	 printf("detsi[%d]=%-11.6f\r",i,detsi[i]);
	}
  for(i=0;i<8;i++) u[i][i]=1.000;
  for(n=0;n<8;n++)
     {for(i=n;i<8;i++)
	 {l[i][n]=J0[i][n];
	  for(j=0;j<=n-1;j++)
	     l[i][n]-=(l[i][j]*u[j][n]);
	 }
      for(j=n+1;j<8;j++)
	 {u[n][j]=J0[n][j];
	  for(i=0;i<=n-1;i++)
	     u[n][j]-=(l[n][i]*u[i][j]);
	     u[n][j] /= l[n][n];
	 }
     }
  for(i=0;i<8;i++)
     {y[i]=detsi[i];
      for(j=0;j<=i-1;j++)
	 y[i]-=(l[i][j]*y[j]);
	 y[i]/=l[i][i];
     }
  for(i=7;i>=0;i--)
     {detui[i]=y[i];
      for(j=i+1;j<n;j++)
	 detui[i]-=(u[i][j]*detui[j]);
     }
  for(i=0;i<8;i++)
      printf("detui[%d]=%-11.6f",i,detui[i]);
  for(i=0;i<8;i++)
     {
	 {if(i%2==0) ui1[i]=detui[i]+fi0[i/2+1];
	  else ui1[i]=detui[i]+ei0[(i+1)/2];
	 }
      printf("ui1[%d]=%-13.6f",i,ui1[i]);
     }
  for(i=1;i<5;i++)
    {ei1[i]=ui1[2*i-1];
     fi1[i]=ui1[2*i-2];
    }
  for(i=1;i<5;i++)
    {printf("ei1[%d]=%-13.6f",i,ei1[i]);
     printf("fi1[%d]=%-13.6f",i,fi1[i]);
    }
  max=Max(detui,8);
  printf("max=%f\n",max);
  for(i=1;i<5;i++)
     {ei0[i]=ei1[i];
      fi0[i]=fi1[i];
     }
  for(i=1;i<5;i++)
     {pi[i]=detpi[i]+pi0[i];
      qi[i]=detqi[i]+qi0[i];
     }
 }while(max>eps && k<km);


 printf("总计 %d 次迭代\n",k);
 sumir=0;
 sumii=0;
 for(i=0;i<k+1;i++)
   {
    I1r=mulRe(ybr[0][i],-ybi[0][i],ei0[i],-fi0[i]);
    I1i=mulIm(ybr[0][i],-ybi[0][i],ei0[i],-fi0[i]);
    sumir+=I1r;
    sumii+=I1i;
   }
 pi[0]=mulRe(ei0[0],fi0[0],sumir,sumii);
 qi[0]=mulIm(ei0[0],fi0[0],sumir,sumii);
 printf("S1=%f+j%f\n",pi[0],qi[0]);
 ei1[0]=ei0[0];
 fi1[0]=fi0[0];
 for(i=0;i<k+1;i++)
   printf("u%d=%f<%f\n",i+1,sqrt(ei1[i]*ei1[i]+fi1[i]*fi1[i]),atan(fi1[i]/ei1[i])*180/3.14159);
}
