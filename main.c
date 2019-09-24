#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tool.c"

#define N 500
#define T 50
#define m 1.
#define f 1.
#define X0 1.
#define dt 0.1

FILE *pos,*data; // outputs

float
x[N],y[N],vx[N],vy[N]; // particles

float
t,mu,sigma,sigma2; // statistics

/************************************************/

void init(){
	/* initialisation */
	t=0;
	for(int i=0; i<N; i++){
		x[i]=0;
		y[i]=0;
		vx[i]=normal(0,1);
		vy[i]=normal(0,1);
	}
}

void update(){
	/* update with EOM */
	float z1,z2;
	for(int i=0; i<N; i++){
		/* Euler's algorithm */
		z1 = normal(0,1);
		z2 = normal(0,1);
		x[i] += vx[i]*dt;
		y[i] += vy[i]*dt;
		// random force X is normal
		vx[i] += (-f/m*vx[i]+X0/m*z1)*dt;
		vy[i] += (-f/m*vy[i]+X0/m*z2)*dt;
	}
	/* gather statistics */
	mu = mean(N,x);
	sigma = sd(N,x);
	sigma2 = sd(N,x);
	t+=dt;
}

void print_xyz(FILE *out){
	/* print coordinates */
	fprintf(out,"%d\n\n",N);
	for(int i=0; i<N; i++)
		fprintf(out,"H %.4f %.4f %.4f\n",x[i],y[i],0.);
}

void print_dat(FILE *out){
	/* print statistics */
	fprintf(out,"%.4f %.4f %.4f %.4f\n",t,mu,sigma,sigma2);
}

void iter(){
	while(t<T){
		update();
		print_xyz(pos);
		print_dat(data);
	}
}

int main(){
	pos=fopen("pos.xyz","w"); // coordinates
	data=fopen("data.txt","w"); // statistics

	iter();

	fclose(pos);
	fclose(data);
	return 0;
}
