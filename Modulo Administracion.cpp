#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*
Universidad Tecnologica Nacional
Facultad Regional Tucuman
Comision 5- Trabajo Integrado 2do Cuatrimestre
Bonilla valentina
Legajo 49929
valentinabonilla@alu.frt.utn.edu.ar
Navarro Carolina
carolinanavarro@alu.frt.utn.edu.ar
*/
typedef char cadena[60];

struct Dia
{
	cadena NombreDia;
	bool trabaja;
	int turnos;	
};


struct veterinario
{
	cadena apeynom;
	cadena usuarios;
	Dia DiaTrabajo[6];
	int matricula;
	cadena contrasenia;
	cadena Telefono;
};

struct usuarios
{
	cadena usuario;
	cadena contrasenia;
	cadena apeynom;
};

struct turno
{
	int matricula;
	cadena dia;
	int DNI;
 
	cadena usuarios;
	bool activo;
};


bool compDias(cadena diaObj)
{
	if(strcmp(diaObj,"lunes")==0 || strcmp(diaObj,"martes")==0 || strcmp(diaObj,"miercoles")==0 || strcmp(diaObj,"jueves")==0 || strcmp(diaObj,"viernes")==0 || strcmp(diaObj,"sabado")==0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int menu()
{
	int opc;
	do
	{
		system("cls");
		printf("					Modulo Administracion\n");
		printf("                ==============================================================\n");
		printf("			1.- Registrar Veterinario.\n");
		printf("			2.- Registrar Usuario Asistente\n");
	 
		printf("			3.- Ranking de veterinarios por atenciones\n\n");
		printf("			0.- salir\n");
		printf("                ==============================================================\n");
		printf("\n");
		printf("            		ingrese opcion: ");
		scanf("%d", &opc);
	}while(opc<0 && opc>5);
	return opc; 
}


// veterinario
bool buscarVeterinario(int objetivo)
{
	veterinario regi;
	FILE *archi;
	bool resp=false;
	archi=fopen("Veterinarios.dat","rb");
	rewind(archi);
	fread(&regi,sizeof(regi),1,archi);
	while(!feof(archi))
	{
		if(objetivo==regi.matricula)
		{
			resp=true;
		}
		fread(&regi,sizeof(regi),1,archi);
	}
	fclose(archi);
	return resp;
}

bool validarPass(cadena contrasenia)
{
	int i=0;
	char letra;
	int menos=0;
	int mas=0;
	int mayuscula=0;
	int minuscula=0;
	int numero=0;
	int caracter=0;
	int consecutivoNumero=0;
	cadena repass;
	int consecutivoLetra=0;
	int pass=0;
	
	printf("reingrese contrasenia: ");
	gets(repass);
	if(strcmp(contrasenia,repass)==0)
	{
		pass=1;
	}
	
	if(strlen(contrasenia)<6)
	{
		menos=1;
	}
	if(strlen(contrasenia)>32)
	{
		mas=1;
	}
	for(i=0;i<strlen(contrasenia);i++)
	{
		if(contrasenia[i]>='0' && contrasenia[i]<='9')
		{
			numero=1;
			if(contrasenia[i+1]-contrasenia[i]==1 && contrasenia[i+2]-contrasenia[i+1]==1)
			{
				consecutivoNumero=1;
			}
		}
		if(contrasenia[i]>='a' && contrasenia[i]<='z')
		{
			minuscula=1;
		}
		if(contrasenia[i]>='A' && contrasenia[i]<='Z')
		{
			mayuscula=1;
		}
		if((contrasenia[i]<'A' && contrasenia[i]>'Z') && (contrasenia[i]<'a' && contrasenia[i]>'z') && (contrasenia[i]<'0' && contrasenia[i]>'9'))
		{
			caracter=1;
		}
		if((contrasenia[i]>='a' && contrasenia[i]<='z') && (contrasenia[i]>='A' && contrasenia[i]<='Z'))
		{
			if((contrasenia[i+1]-contrasenia[i]==1) || (contrasenia[i+1]-contrasenia[i]==33))
			{
			consecutivoLetra=1;
			}
		}
	}
	printf("\n");
	
	if(mayuscula==0)
	{
		printf("la contrasenia debe tener al menos un caracter en mayuscula\n");
	}
	if(minuscula==0)
	{
		printf("la contrasenia debe tener al menos una minuscula\n");
	}
	if(numero==0)
	{
		printf("la contrasenia debe tener al menos un numero\n");
	}
	if(caracter==1)
	{
		printf("la contrasenia debe ser solo alfanumerica\n");
	}
	if(menos==1)
	{
		printf("La contrasenia debe tener al menos 6 caracteres\n");
	}
	if(mas==1)
	{
		printf("la contrasenia debe tener menos de 32 caracteres\n");
	}
	if(consecutivoNumero==1)
	{
		printf("la contrasenia no puede tener 3 numeros consecutivos\n");
	}
	if(consecutivoLetra==1)
	{
		printf("la contrasenia no puede tener 2 letras consecutivas ascendentes\n");
	}
	if(pass==0)
	{
		printf("no son iguales las contrasenias\n");
	}
	if(mayuscula==1 && minuscula==1 && numero==1 && caracter==0 && menos==0 && mas==0 && consecutivoNumero==0 && consecutivoLetra==0 && pass==1)
	{
		return true;
	}
	else
	{
		system("pause");
		return false;
	}
}


void regVeterinario()
{
 
	FILE *archi;
	archi=fopen("Veterinarios.dat","a+b");
	rewind(archi);
	veterinario regi;
	int i=0;
	cadena diaObj;
	cadena dias[6]={"lunes","martes","miercoles","jueves","viernes","sabado"};
	int opc=0;
 
	
	system("cls");
	printf("          Registrar Veterinario\n");
	printf("==============================\n");
	printf("Matricula: ");
	scanf("%d", &regi.matricula);
	if(buscarVeterinario(regi.matricula))
	{
		printf("Este Veterinario ya esta registrado\n\n");
		system("pause");
		return;
	}
	printf("Apellido y nombre: ");
	_flushall();
	gets(regi.apeynom);
	strlwr(regi.apeynom);
	printf("Telefono: ");
	_flushall();
	gets(regi.Telefono);
	do
	{
		system("cls");
		printf("          Registrar veterinario\n");
		printf("==============================\n");
		printf("Matricula: %d",regi.matricula);
		printf("\nApellido y nombre: ");
		puts(regi.apeynom);
		printf("Telefono: ");
		puts(regi.Telefono);
		printf("Contrasenia: ");
		_flushall();
		gets(regi.contrasenia);
	}while(validarPass(regi.contrasenia)==false);
	

	fwrite(&regi,sizeof(regi),1,archi);
	fclose(archi);
	printf("\n\nVeterinario registrado con exito\n\n");
	system("pause");
	
}





// usuario
bool buscarUsuario(cadena objetivo)
{
	FILE *archi;
	usuarios regi;
	bool resp=false;
	archi=fopen("Usuarios.dat","rb");
	rewind(archi);
	fread(&regi,sizeof(regi),1,archi);
	while(!feof(archi))
	{
		if(strcmp(objetivo,regi.usuario)==0)
		{
			resp=true;
		}
		fread(&regi,sizeof(regi),1,archi);
	}
	fclose(archi);
	return resp;
}

bool validarUsuario(cadena objetivo)
{
	int i=0;
	int repetido=0;
	int comienzo=0;
	int numero=0;
	int mayuscula=0;
	int contadormayus=0;
	int contadornumero=0;

	if(buscarUsuario(objetivo))
	{
		repetido=1;
	}
	for(i=0;i<strlen(objetivo);i++)
	{
		if(objetivo[0]>='a' && objetivo[0]<='z')
		{
			comienzo=1;
		}
		if(objetivo[i]>='A' && objetivo[i]<='Z')
		{
			contadormayus++;
		}
		if(contadormayus>1)
		{
			mayuscula=1;
		}
		if(objetivo[i]>=0 && objetivo[i]<=9)
		{
			contadornumero++;
		}
		if(contadornumero>3)
		{
			numero=1;
		}
		
	}
	printf("\n");
	if(repetido==1)
	{
		printf("Este usuario ya exite\n");
	}
	if(comienzo==0)
	{
		printf("El usuario debe comenzar con minuscula\n");
	}
	if(mayuscula==0)
	{
		printf("El usuario debe tener al menos 2 mayusculas\n");
	}
	if(numero==1)
	{
		printf("El usuario no debe tener mas de 3 numeros\n");
	}
		
	if(repetido==0 && comienzo==1 && mayuscula==1 && numero==0)
	{
		return true;
	}
	else
	{
		system("pause");
		return false;
	}
}

void regUsuario()
{
	FILE *archi;
	archi=fopen("Usuarios.dat","a+b");
	system("cls");
	usuarios regi;
	
	do
	{
		system("cls");
		printf("          Registrar usuario\n");
		printf("==============================\n");
		printf("nombre de usuario: ");
		_flushall();
		gets(regi.usuario);
	}
	while(validarUsuario(regi.usuario)==false);
	
	printf("nombre y apellido: ");
	_flushall();
	gets(regi.apeynom);
	strlwr(regi.apeynom);
	
	do
	{
		system("cls");
		printf("          Registrar usuario\n");
		printf("==============================\n");
		printf("nombre de usuario: %s", regi.usuario);
		printf("\nnombre y apellido: %s", regi.apeynom);
		printf("\ncontrasenia: ");
		_flushall();
		gets(regi.contrasenia);
	}
	while(validarPass(regi.contrasenia)==false);
	printf("\nusuario registrado con exito\n\n");
	system("pause");
	fwrite(&regi,sizeof(regi),1,archi);
	fclose(archi);	
}


 
void mayorRegistros()
{
	int contador=0;
	turno regi;
	usuarios reg;
	usuarios regiU;
	FILE *archi;
	FILE *archiU;
	archi=fopen("Turnos.dat","rb");
	archiU=fopen("Usuarios.dat","rb");
	rewind(archi);
	
	printf("         Usuario con mayor registros\n");
	printf("=======================================\n");
	fread(&regiU,sizeof(regiU),1,archiU);
	while(!feof(archiU))
	{
		contador=0;
		printf("apellido y nombre			:");
		puts(regiU.apeynom);
		printf("nombre de usuario			:");
		puts(regiU.usuario);
		rewind(archi);
		fread(&regi,sizeof(regi),1,archi);
		while(!feof(archi))
		{
			if(strcmp(regiU.usuario,regi.usuarios)==0)
			{
				contador++;
			}
			fread(&regi,sizeof(regi),1,archi);
		}
		fread(&regiU,sizeof(regiU),1,archiU);
		printf("cantidad de turnos registrados		: %d",contador);	
		printf("\n\n");
	}
	system("pause");
}

main()
{
	int opc=0;
	FILE *archi;
	archi=fopen("Veterinarios.dat","a+b");
	fclose(archi);
	archi=fopen("Usuarios.dat","a+b");
	fclose(archi);
 
	
	
	do
	{
		system("cls");
		opc=menu();
		switch(opc)
		{
			case 1: regVeterinario();
					break;
			case 2: regUsuario();
					break;
	 
			case 3: mayorRegistros();
					break;
				 
	 
		}
	}
	while(opc!=0);	
}
