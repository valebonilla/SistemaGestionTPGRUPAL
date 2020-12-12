#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
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
typedef char cadena60[60];
struct Dia
{
	cadena60 NombreDia;
 	
};

struct RegSesionV
{
	cadena60 AyN;
	cadena60 Telefono;
	Dia dias[6];
	int matricula;
	cadena60 contrasenia;	
};

struct Turnos
{
	int matricula;
	cadena60 dia;
	int dni;
	cadena60 Detalle;
	cadena60 usuario;
	bool activo;
};
struct Evolucion
{	
	int dni;
	char evolucion[350];
	
};
void MostrarMenu()
{	
	printf("              MODULO CONSULTORIO");
	printf("\n");
	printf("\n==============================================");
	printf("\n 1.- Iniciar Sesion como Veterinario         |");
	printf("\n 2.- Visualizar Lista de Espera de Turnos    |");
	printf("\n 3.- Registrar Evolucion de un Mascota       |");
	printf("\n 4.- Visualizar la Evolucion de un Mascota   |");
	printf("\n                                             |");
	printf("\n 5.- Salir de la aplicacion                  |");
	printf("\n==============================================");
}

main()
{

FILE *archit;
FILE *archiV;
FILE *archie;
RegSesionV sesionV;
Turnos turno;
Evolucion mascota;
char contra[10];
int cod = 0;
int mat = 0;
int HABILITADORA = 0;
int banderamat = 0;
int banderadni = 0;
int contraincorrecta = 0;
int dnibuscar = 0;
int matbuscar = 0;
int tamanio = 0;
int tamaniot = 0;


tamanio=sizeof(mascota);
tamaniot = sizeof(turno);
archiV=fopen("Veterinarios.dat", "a+b");
if(archiV==NULL)
{
	printf("No se pudo abrir el archivo de Veterinarios...");
	printf("\n");
	system("pause");
	exit(1);
}

archit=fopen("Turnos.dat", "a+b");
if(archit==NULL)
{
	printf("No se pudo abrir el archivo de Turnos...");
	printf("\n");
	system("pause");
	exit(1);
}

archie=fopen("Evoluciones.dat", "a+b");
if(archie==NULL)
{
	printf("No se pudo abrir el archivo de Evoluciones...");
	printf("\n");
	system("pause");
	exit(1);
}
fclose(archie);
MostrarMenu();

printf("\nIngrese la opcion deseada: ");
scanf("%d", &cod);

while(cod!=5)
{
switch(cod)
{
	case 1: 
			{
		HABILITADORA = 0;
		contraincorrecta=0;
		banderamat=0;
		rewind(archiV);
		printf("Ingrese la matricula: ");
		scanf("%d", &mat);
		fread(&sesionV, sizeof(sesionV), 1, archiV);
			while(!feof(archiV))
			{
				if(sesionV.matricula == mat)
				{
					banderamat=1;
					while(HABILITADORA==0)
					{
					
					printf("Ingrese la contrasena: ");
					_flushall();
					gets(contra);
					if(strcmp(contra, sesionV.contrasenia)==0)
					{
						printf("Se ha iniciado sesion con exito!");
						printf("\n");
						system("pause");
						HABILITADORA = 1;
					}
					else
					{
					contraincorrecta++;
					if(contraincorrecta == 5)
					{
						system("cls");
						printf("SE HAN SUPERADO LOS INTENTOS DE CONTRASENA...Cerrando programa");
						printf("\n");
						system("pause");
						exit(1);
					};
					printf("Contrasena incorrecta!, Intente nuevamente.");
					printf("\n");
					system("pause");	
					}
					}//while habilitador
					
				}
				
				fread(&sesionV, sizeof(sesionV), 1, archiV);
				
			}	
			if(banderamat == 0)
			{
				printf("\nNo se encontro la matricula ingresada, retornando al menu principal...");
				printf("\n");
				system("pause");
			}
			
			break;
			}
	case 2: 
			{
				if(HABILITADORA == 0)
			{
				system("cls");
				printf("\nNo puede realizar esta accion sin iniciar sesion antes!");
				printf("\n\n");
				printf("\n\n");
				system("pause");
			}
			else
			{
				system("cls");
				rewind(archit);
				printf("          PROXIMOS TURNOS");
				printf("\n=======================================");
				fread(&turno, sizeof(turno), 1, archit);
				while(!feof(archit))
				{
					if((turno.activo == true ) && (mat==turno.matricula))
					{
						
						printf("\nDia del turno: %s", turno.dia);
						printf("\nDNI de la Mascota: %d", turno.dni);
						printf("\nObra Descripcion: %s", turno.Detalle);
						
						if(turno.activo==true)
						{
							printf("\nEl Turno este, se encuentra activo. ");
						}
						printf("\n");
					}
					
					
					
					fread(&turno, sizeof(turno), 1, archit);
				}
				
				
				printf("\n=======================================");
				printf("\n           FIN DE LOS TURNOS");
				printf("\n");
				system("pause");
				
			}
		
			break;
			}
	case 3: {
		
		if(HABILITADORA == 0)
			{
				system("cls");
				printf("\nNo puede realizar esta accion sin iniciar sesion antes!");
				printf("\n\n");
				printf("\n\n");
				system("pause");
			}
			else
			{
				
				archie=fopen("Evoluciones.dat", "r+b");
				
				banderadni=0;
				system("cls");
				printf("REGITRAR LA EVOLUCION DE LA MASCOTA");
				printf("\n==============================");
				printf("\nIngrese el DNI del duenio la mascota: ");
				scanf("%d", &dnibuscar);
				fread(&mascota, sizeof(mascota), 1, archie);
				while(!feof(archie))
				{
					if(dnibuscar==mascota.dni)
					{
						banderadni=1;
						printf("Ingrese la evolucion de la mascotas: ");
						_flushall();
						mascota.dni=dnibuscar;
						gets(mascota.evolucion);
						fseek(archie, sizeof(mascota), SEEK_CUR);
						fwrite(&mascota, sizeof(mascota), 1, archie);
						rewind(archit);
						fread(&turno, sizeof(turno), 1, archit);
						while(!feof(archit))
						{
						if((dnibuscar==turno.dni) && (mat==turno.matricula))
						{
							turno.activo=false;
							fseek(archit, sizeof(turno), SEEK_CUR);
							fwrite(&turno, sizeof(turno), 1, archit);
							break;
						}
						fread(&turno, sizeof(turno), 1, archit);
						}
						printf("Se ha almacenado la evolucion del paciente!");
						printf("\n");
						system("pause");
						
						break;
					}
					
					fread(&mascota, sizeof(mascota), 1, archie);
				
				}
				fclose(archie);
				if(banderadni==0)
				{
					
					archie=fopen("Evoluciones.dat", "a+b");
					mascota.dni=dnibuscar;
					printf("Ingrese la evolucion del paciente: ");
					_flushall();
					gets(mascota.evolucion);
					fwrite(&mascota, sizeof(mascota), 1, archie);
					rewind(archit);
					fread(&turno, sizeof(turno), 1, archit);
					while(!feof(archit))
					{
						if((mascota.dni==turno.dni) && (mat==turno.matricula))
						{
							fseek(archit, sizeof(turno), SEEK_CUR);
							turno.activo=true;
							fwrite(&turno, sizeof(turno), 1, archit);
						}
						fread(&turno, sizeof(turno), 1, archit);
					}
					printf("Se ha almacenado la evolucion del mascota!");
					printf("\n");
					system("pause");
					
					fclose(archie);
				}
				
				
				
			}
		
		
			break;
			}
	case 4:	{
		
		if(HABILITADORA == 0)
			{
				system("cls");
				printf("\nNo puede realizar esta accion sin iniciar sesion antes!");
				printf("\n\n");
				printf("\n\n");
				system("pause");
			}
			else
			{
				fopen("Evoluciones.dat", "r+b");
				banderadni=0;
				system("cls");
				printf("VISUALIZAR EVOLUCION DE LA MASCOTA");
				printf("\n==============================");
				printf("\nIngrese el DNI del duenio de la mascota: ");
				scanf("%d", &dnibuscar);
				fread(&mascota, sizeof(mascota), 1, archie);
				while(!feof(archie))
				{
					if(dnibuscar==mascota.dni)
					{
						banderadni=1;
						printf("\nEvolucion de la mascota: ");
						printf("\n");
						printf("%s", mascota.evolucion);
						printf("\n");
						system("pause");
						fclose(archie);
						break;
					}
					
					fread(&mascota, sizeof(mascota), 1, archie);
				}
				if(banderadni==0)
				{
					printf("No se encontro el duenio con el DNI: %d", dnibuscar);
					printf("\n");
					system("pause");
					
				}
				
			}
		
			break;
			}
	
	default:
			{
			system("cls"); 
			printf("\nCODIGO NO EXISTENTE");
			printf("\n");
			system("pause");	
	
			break;
			}
}	
system("cls");
MostrarMenu();

printf("\nIngrese la opcion deseada: ");
scanf("%d", &cod);
	

	
} // FIN WHILE
fclose(archiV);
fclose(archit);
fclose(archie);
system("cls");
printf("SESION CERRADA");
printf("\n");
printf("\nMuchas gracias!");
printf("\n");
printf("\n");
system("pause");


}
