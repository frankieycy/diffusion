#ifndef TOOL
#define TOOL
#include <math.h>

void line(){
	printf("--------------\n");
}

void fline(FILE *f){
	fprintf(f,"--------------\n");
}

float mod0(float x, float d){
	/* modulus mapped to [-d/2,d/2] */
	while(x>+d/2) x-=d;
	while(x<-d/2) x+=d;
	return x;
}

float min0(float a, float b){
	/* min of two num */
	if(a<b) return a;
	return b;
}

float roundsf(float a, int n){
	/* round to n sig fig */
	return roundf(a*pow(10,n))/pow(10,n);
}

float uniform(float a, float b){ 
	/* uniform sampling */
	float u=(float)rand()/RAND_MAX;
	return a+(b-a)*u;
}

float normal(float a, float b){ 
	/* normal sampling */
	float u1=uniform(0,1),u2=uniform(0,1);
	float z= sqrt(-2*log(u1))*cos(2*M_PI*u2);
	return a+b*z;
}

float less(float a, float b){
	/* smaller */
	if(a<b) return a;
	return b;
}

float mean(int l, float *a){
	float x=0;
	for(int i=0; i<l; i++) x+=a[i];
	return x/l;
}

float var(int l, float *a){
	float x=0;
	for(int i=0; i<l; i++) x+=pow(a[i],2);
	return x/l-pow(mean(l,a),2);
}

float sd(int l, float *a){
	return sqrt(var(l,a));
}

#endif
