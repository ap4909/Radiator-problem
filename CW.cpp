#include <iostream>
#include <fstream>
using namespace std;

double dx=0.02;
double max_x=4,max_y=10;	//max distance in x and y directions
double **a,**b,**c,**d,**e,**f,**T,**Fx,**Fy;		//arrays to store prefactors,temperature and flux
double k=25;		//Thermal conductivity
double h=100; //External heat transfer coefficient
double T_w=25;	//temperature of water
int max_i,max_j;
int i,j;		//counters



void setup_arrays(void)
{
	T=new double*[max_i];
	Fx=new double*[max_i];
	Fy=new double*[max_i];
	a=new double*[max_i];
	b=new double*[max_i];
	c=new double*[max_i];
	d=new double*[max_i];
	e=new double*[max_i];
	f=new double*[max_i];


	for (i=0;i<max_i;i++)
	{
		T[i]=new double[max_j];
		Fx[i]=new double[max_j];
		Fy[i]=new double[max_j];
		a[i]=new double[max_j];
		b[i]=new double[max_j];
		c[i]=new double[max_j];
		d[i]=new double[max_j];
		e[i]=new double[max_j];
		f[i]=new double[max_j];
	}
	
}

void del(void)
{
	int i;
	for (i=0;i<max_i;i++)
		{
			delete[] T[i];
			delete[] Fx[i];
			delete[] Fy[i];
			delete[] a[i];
			delete[] b[i];
			delete[] c[i];
			delete[] d[i];
			delete[] e[i];
			delete[] f[i];
		}

			delete[] T;
			delete[] Fx;
			delete[] Fy;
			delete[] a;
			delete[] b;
			delete[] c;
			delete[] d;
			delete[] e;
			delete[] f;
		

}
void setup_boundaries(void)
{	
	int i_b,j_b;		//variables to store value of i or j that is constant on a boundary
	
	j_b=0;
	for(i=3/dx;i<(4/dx)+1;i++)	//bottom boundary
	{
		T[i][j_b]=200;

		a[i][j_b]=0;
		b[i][j_b]=0;
		c[i][j_b]=0;
		d[i][j_b]=0;
		e[i][j_b]=1;
		f[i][j_b]=200;

	}
	
	i_b=3/dx;	//this value of i is constant along the bottom left vertical boundary
	for(j=1;j<(4/dx);j++)	//Bottom left vertical boundary up to, and not including, the corner
	{
		T[i_b][j]=0;

		a[i_b][j]=1;
		b[i_b][j]=0;
		c[i_b][j]=0;
		d[i_b][j]=0;
		e[i_b][j]=-1;
		f[i_b][j]=dx*h*(T[i_b][j]-T_w)/k;
	}

	j_b=4/dx;
	for(i=0;i<(3/dx);i++)	//horizontal boundary 4cm from bottom boundary
	{
		T[i][j_b]=0;

		a[i][j_b]=0;
		b[i][j_b]=0;
		c[i][j_b]=1;
		d[i][j_b]=0;
		e[i][j_b]=-1;
		f[i][j_b]=dx*h*(T[i][j_b]-T_w)/k;
	
	}
	
	i_b=0;
	for(j=(4/dx)+1;j<max_j;j++)	//Left-most boundary from just above horizontal boundary to top of system
	{
		T[i_b][j]=0;

		a[i_b][j]=1;
		b[i_b][j]=0;
		c[i_b][j]=0;
		d[i_b][j]=0;
		e[i_b][j]=-1;
		f[i_b][j]=dx*h*(T[i_b][j]-T_w)/k;

	}

	j_b=max_j-1;
	for(i=1;i<2/dx;i++)		//Top left horizontal boundary
	{
		T[i][j_b]=0;

		a[i][j_b]=0;
		b[i][j_b]=0;
		c[i][j_b]=0;
		d[i][j_b]=-1;
		e[i][j_b]=1;
		f[i][j_b]=-dx*h*(T[i][j_b]-T_w)/k;
	}

	i_b=2/dx;
	for(j=(6/dx)+1;j<max_j-1;j++)		//boundary from (2,6) to (2,10)
	{
		T[i_b][j]=0;

		a[i_b][j]=0;
		b[i_b][j]=-1;
		c[i_b][j]=0;
		d[i_b][j]=0;
		e[i_b][j]=1;
		f[i_b][j]=-dx*h*(T[i_b][j]-T_w)/k;
	}

	j_b=6/dx;
	for(i=(2/dx)+1;i<3/dx;i++)		//Boundary from (2,6) to (3,6)
	{
		T[i][j_b]=0;

		a[i][j_b]=0;
		b[i][j_b]=0;
		c[i][j_b]=0;
		d[i][j_b]=-1;
		e[i][j_b]=1;
		f[i][j_b]=-dx*h*(T[i][j_b]-T_w)/k;
	}
	
	i_b=3/dx;

	for(j=(6/dx)+1;j<max_j-1;j++)	//boundary from (3,6) to (3,10)
	{
		T[i_b][j]=0;

		a[i_b][j]=1;
		b[i_b][j]=0;
		c[i_b][j]=0;
		d[i_b][j]=0;
		e[i_b][j]=-1;
		f[i_b][j]=dx*h*(T[i_b][j]-T_w)/k;

	}
	
	j_b=max_j-1;
	for(i=(3/dx);i<(4/dx)+1;i++)		//Boundary from (3,10) to (4,10)
	{
		T[i][j_b]=0;

		a[i][j_b]=0;
		b[i][j_b]=0;
		c[i][j_b]=0;
		d[i][j_b]=-1;
		e[i][j_b]=1;
		f[i][j_b]=-dx*h*(T[i][j_b]-T_w)/k;
	}
	
	i_b=4/dx;
	for(j=1;j<max_j-1;j++)		//Boundary along line of symmetry of system
	{
		T[i_b][j]=0;

		a[i_b][j]=0;
		b[i_b][j]=-1;
		c[i_b][j]=0;
		d[i_b][j]=0;
		e[i_b][j]=1;
		f[i_b][j]=0;
	}


}

void setup_interior(void)
{
	for(i=0;i<3/dx;i++)
	{
		for(j=0;j<4/dx;j++)	// area of water in bottom left of system
		{
			T[i][j]=0;

			a[i][j]=0;
			b[i][j]=0;
			c[i][j]=0;
			d[i][j]=0;
			e[i][j]=0;
			f[i][j]=0;
		}
	}

	for(i=(2/dx)+1;i<3/dx;i++)
	{
		for(j=(6/dx)+1;j<max_j;j++)	// area between left hand prong of radiator and centre prong
		{
			T[i][j]=0;

			a[i][j]=0;
			b[i][j]=0;
			c[i][j]=0;
			d[i][j]=0;
			e[i][j]=0;
			f[i][j]=0;
		}
	}
	
	for(i=0;i<(4/dx);i++)		//loops through all points in left hand side of system
	{
		for(j=0;j<max_j;j++)
		{
			if(T[i][j]!=0.0)	//if either one of these conditions is true, then the point is within the radiator
			{
				if(T[i][j]!=200.0)
				{
					T[i][j]=0;

					a[i][j]=-1;
					b[i][j]=-1;
					c[i][j]=-1;
					d[i][j]=-1;
					e[i][j]=4;
					f[i][j]=0;
				}
			}
		}
	}
}

void flux(void)				//function to calculate flux
{
	for(i=0;i<max_i;i++)		//loop through all points
	{
		for(j=0;j<max_j;j++)
		{
			if(i>0 && e[i-1][j]!=0.0 && i<max_i-1 && e[i+1][j]!=0.0)	//if not on a vertical boundary
			{
				Fx[i][j]=-k*(T[i+1][j]-T[i-1][j])/(2*dx);		//central difference
			}
			else if(i>0 && e[i-1][j]!=0.0)	//if on right boundary
			{
				
				Fx[i][j]=-k*(T[i][j]-T[i-1][j])/dx; //backward difference
				if(i==200 && j==1)
				{
					cout<<T[i][j]<<" "<<T[i-1][j]<<" "<<Fx[i][j]<<endl;
				}
			}
			else	//if on left hand boundary
			{
				Fx[i][j]=-k*(T[i+1][j]-T[i][j])/dx; //forward difference
			}
			
			if(j>0 && e[i][j-1]!=0.0 && j<max_j-1 && e[i][j+1]!=0.0)	//if not on a horizontal boundary
			{
				Fy[i][j]=-k*(T[i][j+1]-T[i][j-1])/2*dx;		//central difference
			}
			else if(j>0 && e[i][j-1]!=0.0)	//if on top boundary
			{
				Fy[i][j]=-k*(T[i][j]-T[i][j-1])/dx; //backward difference
			}
			else	//if on bottom boundary
			{
				Fy[i][j]=-k*(T[i][j+1]-T[i][j])/dx; //forward difference
			}

		}
	
	}

}

void main(void)
{
	max_i=(max_x/dx)+1;	//maximum point in x direction 
	max_j=(max_y/dx)+1;	//maximum point in y direction
	setup_arrays();
	
	setup_boundaries();
	setup_interior();

	
	double E_tot,E,w=1.5;
	
	
	int cnt=0,cnt2;
	do
	{
		
		E_tot=0.0;
		cnt2=0;

		for (i=0;i<(4/dx)+1;i++)
		{
			for (j=0;j<max_j;j++)
			{
				if ((i+j)%2==cnt%2 && e[i][j]!=0.0)		//e=0 in water parts of system; SOR not performed on these parts
				{
					
					E = e[i][j]*T[i][j]-f[i][j];	
					
					if(i!=max_i-1)
					{
						if (e[i+1][j]!=0.0) E+=a[i][j]*T[i+1][j];		//only adds this part of error if not on right hand boundary
					}
					if(i!=0)
					{
						if (e[i-1][j]!=0.0) E+=b[i][j]*T[i-1][j];				//only adds this part of error if not on left hand boundary
					}
					if(j!=max_j-1)
					{
						if (e[i][j+1]!=0.0) E+=c[i][j]*T[i][j+1];		//only adds on error if not on top boundary
					}
					if(j!=0)
					{
						if (e[i][j-1]!=0.0) E+=d[i][j]*T[i][j-1];		//only adds on error if not on bottom boundary
					}
				
					E_tot+=fabs(E);		// add modulus of error to total error
					cnt2++;				// count2 goes up each time
					
					T[i][j]=T[i][j]-w*E/e[i][j];
					
				}
			}
		}	

		E_tot=E_tot/((double) cnt2);			// getting average error value dividing total error by total count( total number of iterations)
		
		cnt++;
		
		if (cnt%100==0) cout<<cnt<<": "<<E_tot<<" "<<endl;	// count 1 divided by 100 with residue 0 meaning every 100, give error value
	}
	while(E_tot>0.18);

	
	fstream outfile;
	
	flux();
	outfile.open("flux.dat",fstream::out);
	outfile<<"\t";
	for(i=0;i<max_i;i++)
	{
		outfile<<i*dx<<"\t";
	}
	outfile<<endl;
	
	for(j=0;j<max_j;j++)
	{
		outfile<<j*dx<<"\t";
		for(i=0;i<max_i;i++)
		{
			outfile<<Fx[i][j]<<"\t";
		}
		outfile<<endl;
	}
	
	outfile.close();
	del();
}