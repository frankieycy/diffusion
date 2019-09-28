#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tool.c"

#define N 2000 // num of particles
#define T 50 // total time
#define m 1. // mass
#define f 1. // fric coeff
#define X0 1. // mag of rand force
#define dt 0.1 // time step

FILE
*pos,*data,*traj; // outputs

float
x[N],y[N],vx[N],vy[N]; // kinematic param

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
	sigma2 = var(N,x);
	t+=dt;
}

void print_traj(FILE *out){
	/* print tracer track */
	fprintf(out,"%.1f %.4f %.4f\n",t,x[0],y[0]);
}

void print_xyz(FILE *out){
	/* print coordinates of all particles */
	fprintf(out,"%d\n\n",N);
	for(int i=0; i<N; i++) fprintf(out,"H %.4f %.4f %.4f\n",x[i],y[i],0.);
}

void print_dat(FILE *out){
	/* print statistics */
	fprintf(out,"%.4f %.4f %.4f %.4f\n",t,mu,sigma,sigma2);
}

void iter(){
	while(t<T){
		update();
		print_traj(traj);
		print_xyz(pos);
		print_dat(data);
	}
}

/************************************************/

int main(){
	pos=fopen("pos.xyz","w"); // coordinates
	data=fopen("data.txt","w"); // statistics
	traj=fopen("traj.txt","w"); // tracer track
	iter();

	fclose(pos);
	fclose(data);
	fclose(traj);
	return 0;
}
