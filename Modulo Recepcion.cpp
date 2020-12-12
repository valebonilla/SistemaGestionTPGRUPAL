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


struct fecha
{
	int dia;
	int mes;
	int anio;
};

struct usuarios
{
	cadena usuario;
	cadena contrasenia;
	cadena apeynom;
};

 
struct Mascotas
{
	cadena apeynom;
	cadena domicilio;
	int DNI;
	cadena localidad;
	fecha nacimiento;
	float peso;
	cadena Telefono;
};

struct fec
{
	cadena dia;
};

struct Dia
{
	cadena NombreDia;
	bool trabaja;
	int turnos;	
};


struct veterinario
{
	cadena apeynom;
	cadena Telefono;
	Dia DiaTrabajo[6];
	int matricula;
	cadena contrasenia;
};
struct turno
{
	int matricula;
	cadena dia;
	int DNI;
	cadena Detalle;
	cadena usuario;
bool activo;
};

int menu()
{
	int opc;
	do
	{
		system("cls");
		printf("					Modulo asistente\n");
		printf("                ==============================================================\n");
		printf("			1.- Iniciar sesion.\n");
		printf("			2.- Registrar mascota\n");
		printf("			3.- Registrar Turno\n");
		printf("			4.- Listado de atenciones por Veterinario\n");
		printf("			5.- Cerrar sesion\n");
		printf("			0.- salir\n");
		printf("                ==============================================================\n");
		printf("\n");
		printf("            		ingrese opcion: ");
		scanf("%d", &opc);
	}while(opc<0 && opc>5);
	return opc; 

}

bool sesion(cadena user, cadena pass)
{
	int us=0;
	int contra=0;
	usuarios regi;
	bool resp;
	FILE *archi;
	archi=fopen("Usuarios.dat","rb");
	rewind(archi);
	fread(&regi,sizeof(regi),1,archi);
	while(!feof(archi))
	{
		if(strcmp(regi.usuario,user)==0)
		{
			us=1;
		}
		if(strcmp(regi.contrasenia,pass)==0)
		{
			contra=1;
		}
		fread(&regi,sizeof(regi),1,archi);
	}
	fclose(archi);
	if(contra==0)
	{
		if(us==0)
		{
			printf("\nusuario y contrasenia invalidos\n\n");
			system("pause");
			return false;
		}
		else
		{
			printf("\ncontrasenia invalida\n\n");
			system("pause");
			return false;
		}
	}
	else
	{
		if(us==1)
		{
			printf("inicio sesion con exito!!\n\n");
			system("pause");
			return true;
		}
		else
		{
			printf("\nusuario invalido\n\n");
			system("pause");
			return false;
		}
	}	
}


void inicio(int &IS, cadena &US)
{
	usuarios regi;
	cadena objetivo;
	cadena pass;
	bool opc;
	int veces=3;
	do
	{
		system("cls");
		printf("				Inicio de sesion\n");
		printf(" ==============================================================\n");
		printf("usuario: ");
		_flushall();
		gets(objetivo);
		printf("contrasenia: ");
		_flushall();
		gets(pass);
		opc=sesion(objetivo,pass);
		if(opc==false)
		{
			veces--;
		}
		if(veces==0)
		{
			system("cls");
			printf("fallo 3 veces el inicio de sesion");
			exit(-1);
		}
	}
	while(opc==false);
	IS=1;
	strcpy(US,objetivo);
}

bool buscarMascota(int objetivo)
{
	FILE *archi;
	Mascotas regi;
	bool resp=false;
	archi=fopen("Mascotas.dat","rb");
	rewind(archi);
	fread(&regi,sizeof(regi),1,archi);
	while(!feof(archi))
	{
		if(objetivo==regi.DNI)
		{
			printf("\neste paciente ya esta registrado\n\n");
			system("pause");
			resp=true;
		}
		fread(&regi,sizeof(regi),1,archi);
	}
	fclose(archi);
	return resp;
}


void registrarMascota(int IS)
{
	FILE *archi;
	Mascotas regi;
	if(IS==0)
	{
		system("cls");
		printf("				Registrar Mascota\n");
		printf(" ==============================================================\n");
		printf("No se inicio sesion aun!!!\n\n");
		system("pause");
		return;
	}
	else
	{
		do
		{
			system("cls");
			printf("				Registrar Mascota\n");
			printf(" ==============================================================\n");
			printf("DNI: ");
			scanf("%d", &regi.DNI);
		}
		while(buscarMascota(regi.DNI)==true);
		printf("\nApellido y Nombre: ");
		_flushall();
		gets(regi.apeynom);
		strlwr(regi.apeynom);
		printf("\ndomicilio: ");
		_flushall();
		gets(regi.domicilio);
		printf("\nlocalidad: ");
		_flushall();
		gets(regi.localidad);
		printf("\nfecha de nacimiento(dd/mm/aa): \ndia: ");
		do
		{
			scanf("%d", &regi.nacimiento.dia);
		}
		while(regi.nacimiento.dia<1 && regi.nacimiento.dia>31);
		printf("\nmes: ");
		do
		{
			scanf("%d", &regi.nacimiento.mes);
		}
		while(regi.nacimiento.mes<1 && regi.nacimiento.mes>12);
		printf("\nanio: ");
		do
		{
			scanf("%d", &regi.nacimiento.anio);
		}
		while(regi.nacimiento.anio<0 && regi.nacimiento.anio>99);
		printf("\npeso: ");
		scanf("%f", &regi.peso);
		printf("Telefono: ");
		_flushall();
		gets(regi.Telefono);
		system("cls");
		archi=fopen("Mascotas.dat","a+b");
		printf("\n\nel Mascota se cargo exitosamente\n\n");
		fwrite(&regi,sizeof(regi),1,archi);
		fclose(archi);
		system("pause");
	}
}




bool buscarVeterinario(int objetivo)
{
	FILE *archi;
	veterinario regi;
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
	if(resp=false)
	{
		printf("Este Veterinarios no esta registrado\n\n");
		system("pause");
	}
	fclose(archi);
	return resp;
}

bool verificarMascota(int objetivo)
{
	FILE *archi;
	Mascotas regi;
	bool resp=false;
	archi=fopen("Mascotas.dat","rb");
	rewind(archi);
	fread(&regi,sizeof(regi),1,archi);
	while(!feof(archi))
	{
		if(objetivo==regi.DNI)
		{
			resp=true;
		}
		fread(&regi,sizeof(regi),1,archi);
	}
	if(resp==false)
	{
		printf("Este Mascota no esta registrado\n\n");
		system("pause");
	}
	fclose(archi);
	return resp;
}




bool validarDia(cadena objetivo, int matri)
{
	FILE *archi;
	FILE *archiT;
	veterinario regiV;
	turno regiT;
	int escrito=0;
	int corresponde=0;
	int disponibilidad=0;
	int contador=0;
	
	if(strcmp(objetivo,"lunes")!=0 && strcmp(objetivo,"martes")!=0 && strcmp(objetivo,"miercoles")!=0 && strcmp(objetivo,"jueves")!=0 && strcmp(objetivo,"viernes")!=0 && strcmp(objetivo,"sabado")!=0)
	{
		escrito=1;
	}
	archi=fopen("veterinarios.dat","rb");
	rewind(archi);
	fread(&regiV,sizeof(regiV),1,archi);
	while(!feof(archi))
	{
		if(matri==regiV.matricula)
		{
			for(int i=0;i<6;i++)
			{
				if(regiV.DiaTrabajo[i].trabaja==true)
				{
					if(strcmp(regiV.DiaTrabajo[i].NombreDia,objetivo))
					{
						corresponde=1;
					}
					archiT=fopen("Turnos.dat","rb");
					rewind(archiT);
					fread(&regiT,sizeof(regiT),1,archiT);
					while(!feof(archiT))
					{
						if(strcmp(objetivo,regiT.dia)==0)
						{
							if(regiT.matricula==matri)
							{
								contador++;
							}
						}
						if(contador==regiV.DiaTrabajo[i].turnos)
						{
							disponibilidad=1;
						}		
						fread(&regiT,sizeof(regiT),1,archiT);
					}
				}
			}
			
		}
		fread(&regiV,sizeof(regiV),1,archi);
	}
	fclose(archi);
	fclose(archiT);

	if(escrito==1)
	{
		printf("\nno esta bien escrito el dia");
	}
	if(corresponde==0)
	{
		printf("\nese dia no atiende el medico");
	}
	if(disponibilidad==1)
	{
		printf("\nno quedan turnos disponibles para ese dia");
	}
	if(escrito==0 && corresponde==1 && disponibilidad==0)
	{
		return false;
	}
	else
	{
		printf("\n\n");
		system("pause");
		return true;
	}
}

void registrarTurno(int IS, cadena US)
{
	FILE *archi;
	int opc;
	Mascotas regi;
	turno regi2;
	usuarios regi3;
	cadena med;
	if(IS==0)
	{
		system("cls");
		printf("				Registrar turnos\n");
		printf(" ==============================================================\n");
		printf("No se inicio sesion aun!!!\n\n");
		system("pause");
		return;
	}
	else
	{
		do
		{
		system("cls");
		printf("				Registrar turnos\n");
		printf(" ==============================================================\n");
		printf("\n1.registrar turno");
		printf("\n0.Volver");
		printf("\n\nopcion: ");
		scanf("%d", &opc);
		}
		while(opc<0 && opc>2);
		switch(opc)
		{
			case 1:
					do
				{
					system("cls");
					printf("				Registrar Turno\n");
					printf(" ==============================================================\n");
					printf("Matricula: ");
					scanf("%d", &regi2.matricula);
				}
				while(buscarMascota(regi2.matricula)==true);
				do
				{
					system("cls");
					printf("				Registrar Turno\n");
					printf(" ==============================================================\n");
					printf("Matricula: %d", regi2.matricula);
					printf("\ndia: ");
					_flushall();
					gets(regi2.dia);
					strlwr(regi2.dia);
				}
				while(validarDia(regi2.dia, regi2.matricula)==true);
				
				do
				{
					system("cls");
					printf("				Registrar Turno\n");
					printf(" ==============================================================\n");
					printf("Matricula: %d", regi2.matricula);
					printf("\ndia: %s", regi2.dia);
					printf("\nDNI: ");
					scanf("%d", &regi2.DNI);
				}
				while(verificarMascota(regi2.DNI)==false);
				system("cls");
				printf("				Registrar Turno\n");
				printf(" ==============================================================\n");
				printf("Matricula: %d", regi2.matricula);
				printf("\ndia: %s", regi2.dia);
				printf("\nDNI: %d",regi2.DNI);
				printf("\nDetalle: ");
				_flushall();
				gets(regi2.Detalle);
				
				archi=fopen("Turnos.dat","a+b");
				strcpy(regi2.usuario,US);
				fwrite(&regi2,sizeof(regi2),1,archi);
				fclose(archi);
				printf("\n\n turno creado con exito!!\n\n");
				system("pause");
				break;
			
			
			case 2: 
				return;
				break;
		}
	}
}




void listadoAtenciones(int IS)
{
	turno regiT;

	veterinario regiV;
	int contador;
	int opc;
	FILE *archiT;

	FILE *archiV;
	if(IS==0)
	{
		system("cls");
		printf("				Listado atenciones\n");
		printf(" ==============================================================\n");
		printf("No se inicio sesion aun!!!\n\n");
		system("pause");
		return;
	}
	else
	{
		do
		{
			system("cls");
			printf("				Listado atenciones\n");
			printf(" ==============================================================\n");
			printf("\n1.listado de atenciones por Veterinario");
			printf("\n0.volver");
			printf("\n\nopcion: ");
			scanf("%d", &opc);
		}
		while(opc<0 && opc>3);
		switch(opc)
		{
	
			case 1:
				system("cls");
				printf("				Listado atenciones por Veterinario\n");
				printf(" ==============================================================\n");
				printf("Veterinario: ");	
				archiV=fopen("Veterinarios.dat","rb");
				rewind(archiV);
				fread(&regiV,sizeof(regiV),1,archiV);
				while(!feof(archiV))
				{
					contador=0;
					puts(regiV.apeynom);
					archiT=fopen("Turnos.dat","rb");
					rewind(archiT);
					fread(&regiT,sizeof(regiT),1,archiT);
					while(!feof(archiT))
					{
						if(regiT.matricula==regiV.matricula)
						{
							contador++;
						}
						fread(&regiT,sizeof(regiT),1,archiT);
					}
					printf("cantidades: %d",contador);
					fread(&regiV,sizeof(regiV),1,archiV);
					printf("\n\n");
				}
				fclose(archiT);
				fclose(archiV);
				system("pause");
				break;
			
		}
	}
	
}

main()
{
	FILE *archi;
	archi=fopen("Mascotas.dat","a+b");
	fclose(archi);
	archi=fopen("Turnos.dat","a+b");
	fclose(archi);
	usuarios regi;
	
	cadena US;//usuario
	int opc=0;
	int IS=0;//inicio de sesion variable
	do
	{
		system("cls");
		opc=menu();
		switch(opc)
		{
			case 1: inicio(IS, US);
					break;
			case 2: registrarMascota(IS);
					break;
			case 3: registrarTurno(IS, US);
					break;
			case 4:
					listadoAtenciones(IS);
					break;
			case 5: 
					if(IS==0)
					{
						system("cls");
						printf("no se inicio sesion aun!!\n\n");
						system("pause");
						break;
					}
					else
					{
						system("cls");
						IS=0;
						printf("la sesion se cerro con exito\n\n");
						system("pause");
						break;
					}
					
		}
	}
	while(opc!=0);	
	
}

