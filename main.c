#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

struct producto
{
	int id;
	char nombre[20];
	int cant;
	double precio;
};

void abrir(char *, char*);
void crear(char*);
void escribir(producto*);
bool buscar(producto*, int);
void insertar(char*, producto*);
void menu();
void ordenar(producto*, int);
void reporte(producto*, int);


int main(int argc, char**argv)
{
	char file1[20]={"canteras.dat"};
	char file2[20]={"prados.dat"};
	
	crear(file1);
	crear(file2);
	
	menu();
	
	cout<<endl;
	system("pause");
	return 0;
}

void menu()
{
	
	char file1[20]={"canteras.dat"};
	char file2[20]={"prados.dat"};
	
	char res;
	do{
		
		
		
	producto vec[10];
	char file1[20]={"canteras.dat"};
	char file2[20]={"prados.dat"};
	
	
	for(int i=0; i<10; i++)
	{
	
		vec[i].id=0;
		strcpy(vec[i].nombre,"");
		vec[i].cant=0;
		vec[i].precio=0;
	}
		
	int op;
	
	cout<<endl<<"ELIGE UNA OPCION:";
	cout<<endl<<"1.Dar de alta en Canteras.dat";
	cout<<endl<<"2.Dar de alta Prados.dat";
	cout<<endl;
	cin>>op; 
	
	switch(op)
	{
		case 1: escribir(vec);
		        insertar(file1, vec); break;
		case 2: escribir(vec);
		        insertar(file2, vec); break;
	}
	
	cout<<endl<<"Otra interaccion s/n: ";
	cin>>res;
	
	}while(res=='s');
	
	abrir(file1, file2);
}


void insertar(char* archivo, producto vec[10])
{
	fstream file;
	producto registro;
	int i=0;
	file.open(archivo, ios::binary | ios::out |ios::in);
	
	if(!file)
	  cout<<endl<<"ERROR";
	while(i<10)
	{
		if(vec[i].id!=0)
		{
		registro.id=vec[i].id;
	    strcpy(registro.nombre, vec[i].nombre);
	    registro.cant=vec[i].cant;
	    registro.precio=vec[i].precio;
	 
		file.seekp( (registro.id -1) * sizeof(producto) );
		file.write(reinterpret_cast<char*>(&registro),sizeof(producto));
		
		registro.id=0;
		strcpy(registro.nombre,"");
		registro.cant=0;
		registro.precio=0;
		}
	   
		i++;
	}
	
	file.close();
}

void ordenar(producto* aux, int tam)
{
	producto* final=new producto[tam];
	int b=0, j;
	bool band;
	
	for(int i=0; i<tam; i++)
	{
		band=true;
		for( j=0; j<i; j++)
		{
			if(final[j].id == aux[i].id)
			{
				final[j].cant=final[j].cant+aux[i].cant;
				band=false;
			}
				
		}
		if(band==true)
		{
			final[b].id=aux[j].id;
			final[b].cant=aux[j].cant;
			final[b].precio=aux[j].precio;
			strcpy(final[b].nombre, aux[j].nombre);
			b++;
		}
			
    }

	int min, id, cant, precio;
	char nom[20];
	
	j=0;
	for(int i=0; i<b; i++)
	{
		min=i;
		for(j=i+1; j<b; j++)
		{
			if(final[j].nombre[0]< final[min].nombre[0])
			  min=j;
		}
		strcpy(nom, final[min].nombre);
		cant=final[min].cant;
		precio=final[min].precio;
		id=final[min].id;
		
		strcpy(final[min].nombre, final[i].nombre);
		final[min].cant=final[i].cant;
		final[min].precio=final[i].precio;	
		final[min].id=final[i].id;
		
		strcpy(final[i].nombre, nom);
		final[i].cant=cant;
		final[i].precio=precio;
		final[i].id=id;
	
	}
	
	reporte(final, b);
}

void reporte(producto* v, int tam)
{
	fstream file;
	int total=0;
	file.open("Inventario.txt", ios::out | ios::app);
	
	cout<<endl<<endl<<"Inventario"<<endl;
	cout<<setw(3)<<"ID"<<setw(20)<<"Producto"<<setw(10)<<"Cantidad"<<setw(10)<<"Compra"<<endl;
	
	int i=0;
	if(!file)
	  cout<<endl<<"ERROR";
	
	else
	{
		while(i<tam)
		{
			cout<<setw(3)<<v[i].id<<setw(20)<<v[i].nombre <<setw(10)<<v[i].cant <<setw(10)<<v[i].precio<<endl;
			total=total+(v[i].cant * v[i].precio);
			file<<v[i].id<<" "<<v[i].nombre <<" "<<v[i].cant <<" "<<v[i].precio<<endl;
			i++;
		}
		
	}
	file.close();
	
	cout<<endl<<setw(20)<<"TOTAL: "<<total;
	
}

void abrir(char *archivo1, char *archivo2)
{
	producto aux[10]={0, "", 0, 0};
	producto registro;
	int i=0;
	
	fstream file1;
	fstream file2;
	
	file1.open(archivo1 , ios::binary | ios::in |ios::app);
	file2.open(archivo2 , ios::binary | ios::in | ios::app);
	

	if(!file1 || !file2)
	  cout<<endl<<"ERROR al abrir el archivo";

		while(!file1.eof())
		{
			aux[i].id=registro.id;
		        if(registro.id !=0)
		        {
		        	strcpy(aux[i].nombre, registro.nombre);
		        	aux[i].cant=registro.cant;
		        	aux[i].precio=registro.precio;
		        	i++;
		        }
			    
			file1.read((char *)&registro, sizeof(producto));
		}
		
		while(!file2.eof())
		{
			aux[i].id=registro.id;
		        if(registro.id !=0 )
		        {
		        	
		        	strcpy(aux[i].nombre, registro.nombre);
		        	aux[i].cant=registro.cant;
		        	aux[i].precio=registro.precio;
		        	i++;
		        
		        }
		          
			file2.read((char *)&registro, sizeof(producto));
		}
			
	file1.close();
	file2.close();
	
	ordenar(aux, i);	
}


void crear(char *archivo)
{
	fstream file;
	
	file.open(archivo, ios::binary | ios::out |ios::app);
	if(!file)
	  cout<<"ERROR";
	else
	{
		producto registro={0, "", 0, 0};
		for(int i=0; i<10; i++)
		{
			file.write( reinterpret_cast<char *> (&registro),sizeof(producto));
		}
	}
	file.close();
}

void escribir(producto vec[10])
{
	int aux;
	int res=1;
	int cant=0;
	do{
		cout<<endl<<"Ingresa el ID del producto: ";
		cin>>aux;
	}while(aux>10 || aux<0); 
	
	while(res==1)
	{
		if(buscar(vec, aux)==false)
		{
			vec[aux-1].id=aux;
			cout<<endl<<"Ingresa nombre: ";
			fflush(stdin);
			cin.getline(vec[aux-1].nombre, 20);
			cout<<endl<<"Cantidad: ";
			cin>>vec[aux-1].cant;
			cout<<endl<<"Precio: ";
			cin>>vec[aux-1].precio;
		}
		else
		{
			cout<<endl<<"Cantidad a ingresar: ";
			cin>>cant;
			vec[aux-1].cant=vec[aux-1].cant+cant;
		}
		
		cout<<endl<<"Ingresar otro (1=si / 0=no): ";
		cin>>res;
		
		if(res==1)
		{
			do{
			cout<<endl<<"Ingresa el ID del producto: ";
			cin>>aux;
			}while(aux>10 || aux<0); 
		
		}
	
	}
	
	
}

bool buscar(producto vec[10], int aux)
{
	bool band=false;  
	  
	  for(int i=0; i<10;  i++)
	  {
	  	if(vec[i].id==aux)
	  	   band=true;
	  	  
	  }
	  
	  if(band==true)
	  	 return true;
	  else
	   return false;
	  
}




