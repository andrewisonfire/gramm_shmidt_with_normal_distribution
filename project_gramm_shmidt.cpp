#include <iostream>
//#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <fstream>
#include <vector>

#define N 1000
#define DIM 10
#define epsylon 0.000001

using namespace std;
/////////////////////////////////////////////////////////////////////////////
double dot_product(vector<double> vektor_1,vector<double> vektor_2)          //dot product 
{
double result=0;
for(int i=0;i<N;++i)
	result=result+vektor_1[i]*vektor_2[i];
return result;
}
/////////////////////////////////////////////////////////////////////////////
vector<double> operator_projection(vector<double> vektor_1,vector<double> vektor_2)
{
double compression,size_of_vector_1=vektor_1.size(),size_of_vector_2=vektor_2.size();
vector<double> result(size_of_vector_1);
compression=dot_product(vektor_1,vektor_2)/dot_product(vektor_2,vektor_2);
	for (int i=0;i<size_of_vector_1;++i)
	{
		result[i]=vektor_2[i]*compression;
	}
return result;
}
/////////////////////////////////////////////////////////////////////////////
vector<vector<double> > gramm_shmidt(vector<vector<double> > system_of_vectors)
{
double num_of_vectors=system_of_vectors.size();
vector<double> booble=system_of_vectors[0];
double dim=booble.size();
vector<vector<double> >ortogonal_system_of_vectors;                        //if you want this crap working, don't touch anything
ortogonal_system_of_vectors=system_of_vectors;
	for (int i=1;i<num_of_vectors;++i)
	{
		for (int k=0;k<i;++k)
		{
			for (int j=0;j<dim;++j)
			{
ortogonal_system_of_vectors[i][j]=ortogonal_system_of_vectors[i][j]-operator_projection(system_of_vectors[i],ortogonal_system_of_vectors[k])[j];
			}
		}
	}
return ortogonal_system_of_vectors;
}
//////////////////////////////////////////////////////////////////////////////
vector< vector<double> > noise_generator(int number_of_vectors,int dim)
{
//vector< vector<double> > ortogonal_noise_vector(number_);
vector<vector <double> > A(number_of_vectors),ort_A(number_of_vectors);
vector<double> booble(dim);
double rand_max=RAND_MAX;
double x,y,u,v,s,pi=acos(-1.0);
//////////////////////////////////////////////////////////////////////////////
for (int i=0;i<number_of_vectors;++i)
{
	A[i]=booble;
	ort_A[i]=booble;                                                      //need for size of vectors
}
//////////////////////////////////////////////////////////////////////////////
int bOOble=number_of_vectors/2;;
if (number_of_vectors%2==0)
{ 
	for (int j=0;j<bOOble;++j)
	{
		for(int i=0;i<dim;++i)
		{
	u=rand()/rand_max;
	v=rand()/rand_max;
	s=pow(u,2)+pow(v,2);
	x=sqrt(-2*log(v))*cos(2*acos(-1.0)*u);                                        //geting normal distribution system(called A)
	y=sqrt(-2*log(v))*sin(2*acos(-1.0)*u);                                        //x,y,u,v,s - need for calculating
	A[j][i]=x;
	A[j+bOOble][i]=y;

		}
	}
} else
{
	for (int j=0;j<bOOble;++j)
	{
		for(int i=0;i<dim;++i)
		{
	u=rand()/rand_max;
	v=rand()/rand_max;
	s=pow(u,2)+pow(v,2);
	x=sqrt(-2*log(v))*cos(2*acos(-1.0)*u);                                        //geting normal distribution system(called A)
	y=sqrt(-2*log(v))*sin(2*acos(-1.0)*u);                                        //x,y,u,v,s - need for calculating
	A[j][i]=x;
	A[j+bOOble][i]=y;

		}
	}
	for(int i=0;i<dim;++i)
	{
	u=rand()/rand_max;
	v=rand()/rand_max;
	s=pow(u,2)+pow(v,2);
	x=sqrt(-2*log(v))*cos(2*acos(-1.0)*u);                                        //geting normal distribution system(called A)
	y=sqrt(-2*log(v))*sin(2*acos(-1.0)*u); 
	A[number_of_vectors-1][i]=x;
	} 
}
//////////////////////////////////////////////////////////////////////////////
ort_A=gramm_shmidt(A);                                                        //ortogonalization
//////////////////////////////////////////////////////////////////////////////
int tmp=0;
for (int i=0;i<DIM;++i)
	for (int j=i+1;j<DIM;++j)
if(abs(dot_product(ort_A[i],ort_A[j]))>epsylon)				// Orthogonalization check
{
++tmp;
break;
}

if(tmp==0)
{
return ort_A;//ortogonal_noise_vector;
}else
{
cout<<"something is going wrong"<<endl;
}
}
//////////////////////////////////////////////////////////////////////////////
int main ()
{

vector<vector <double> > ort_A;
vector<double> booble;
char a,b;
ort_A= noise_generator(10,1000);//gramm_shmidt(A);                                                        //ortogonalization
booble=ort_A[0];
int number_of_vectors=ort_A.size();
//////////////////////////////////////////////////////////////////////////////

return 0;                                                                     //stream may be done in file called project_gramm_test.txt
}

