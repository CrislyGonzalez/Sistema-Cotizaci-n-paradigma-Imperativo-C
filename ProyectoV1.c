#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"
#include <stdio.h>



struct productos{
	char descripcion[140];
	int  cantidadProductos;
	int precioDolar;
	int id;
	struct productos *sig;
}product;


struct factura{
	char nombreNegocio[40];
	char ubicacionNegocio[40];
	char nombreCliente[40];
	int precioDolar;
	struct factura *sig;
	struct productos *producto;
}factura;

struct productos *cabeza;
struct factura *cabezaFac;

int tipoCambio;
int PrecioTotalD= 0;

struct numero{
	int numero;
	struct numero *sig;
};

struct numero *cabezaNum;


void crearFacturaHTML(){
	FILE *fp;
	struct factura *temporal= cabezaFac;
	

    //clrscr();
    fp = fopen("Cotizacion.html", "w");   /* Abrir archivo para escritura */
    fprintf(fp, "<html> \n");
    fprintf(fp,"<head> \n ");
    fprintf(fp,"<title> Cotizacion </title>  \n ");
    fprintf(fp,"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css'>");
    fprintf(fp,"<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css'>");
	fprintf(fp,"</head> \n ");
    
    fprintf(fp,"<div class = 'row'>");
    fprintf(fp,"<div class = 'col-md-3'></div>");
    fprintf(fp,"<div class = 'col-md-6'>");
    
    fprintf(fp, "<Body> \n");
    fprintf(fp, "<span>  Cotizacion  </span> <br><br>");
    
    fprintf(fp, "<table class='table table-bordered'> ");
    
    
    time_t t;
    struct tm *tm;
    char fechayhora[100];
    char *meses[12]={"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    t=time(NULL);
    tm=localtime(&t);
    fprintf(fp, "<tr>");
       	    fprintf(fp, " <td> Fecha </td> \n");
       	    fprintf(fp, " <td colspan='3'>");
       	    char dia[20];
       	    itoa(tm->tm_mday,dia,10);
       	    
       	     char anno[20];
       	    itoa(1900+tm->tm_year,anno,10);
       	    
       	    fprintf(fp,dia);
       	    fprintf(fp,"/");
       	    fprintf(fp,meses[tm->tm_mon]);
       	    fprintf(fp,"/");
       	    fprintf(fp,anno);
       	    fprintf(fp, " </td> \n");
       	
    fprintf(fp, "</tr>");
    
    
        fprintf(fp, "<tr>");
       	    fprintf(fp, " <td> Negocio</td> \n");
       	    fprintf(fp, " <td colspan='3'>");
       	    fprintf(fp,temporal->nombreNegocio);
       	    fprintf(fp, " </td> \n");
       	
       fprintf(fp, "</tr>");
       
       
        fprintf(fp, "<tr>");
            fprintf(fp, " <td> Ubicacion </td> \n");
       	    fprintf(fp, " <td colspan='3'>");
       	    fprintf(fp,temporal->ubicacionNegocio);
       	    fprintf(fp, " </td> \n");
	   fprintf(fp, "</tr>");
       
       
        fprintf(fp, "<tr>");
       	   fprintf(fp, " <td> Cliente </td> \n");
       	    fprintf(fp, " <td colspan='3'>");
       	    fprintf(fp,temporal->nombreCliente);
       	    fprintf(fp, " </td> \n");
       fprintf(fp, "</tr>");

       	   
	   fprintf(fp, "<tr>");
       	
       	    fprintf(fp, " 	<th>id</th> \n");
       	   	fprintf(fp, " 	<th>Descripcion</th> \n");
       	   	fprintf(fp, " 	<th>Precio Dolar</th> \n");
       	   	fprintf(fp, " 	<th>Precio Colones</th> \n");
       	   	
       	   	
       	   	
       fprintf(fp, "</tr>");
       int totalDo=0;
       
       while(temporal!= NULL){
       	struct productos *temporalProducto = temporal->producto;
       
       		fprintf(fp, "<tr>");
       	  
       	    fprintf(fp, " 	<td>");
       	    char id[20];
       	    itoa(temporalProducto->id, id,10);
       	    fprintf(fp,id);
       	    fprintf(fp,"</td> \n");
       	    
       	   	fprintf(fp, " 	<td>");
       	   	fprintf(fp,temporalProducto->descripcion);
       	    fprintf(fp,"</td> \n");
       	   	
       	   	fprintf(fp, " 	<td>");
       	   	char dolares[20];
       	    itoa(temporalProducto->precioDolar, dolares,10);
       	   	fprintf(fp,dolares);
       	    fprintf(fp,"</td> \n");
       	    
       	   	fprintf(fp, " 	<td>");
       	   	char colones[20];
       	    itoa(temporalProducto->precioDolar*tipoCambio, colones,10);
       	   	fprintf(fp,colones);
       	    fprintf(fp,"</td> \n");
       	   
           fprintf(fp, "</tr>");
           
           
           temporal=temporal->sig;
	   }
	   
       
        fprintf(fp, "<tr>");
        	fprintf(fp, "<td > Total colones </td> \n");
        	
        	fprintf(fp, "<td colspan='3'>");
        	char totalColones[20];
       	    itoa(PrecioTotalD*tipoCambio,totalColones,10);
        	fprintf(fp, totalColones);
        	
			fprintf(fp, "</td>");
			
		fprintf(fp, "</tr>");
		
		fprintf(fp, "<tr>");
        	fprintf(fp, "<td > Total Dolares </td> \n");
        
        	fprintf(fp, "<td colspan='3'>");
        	char totalDolares[20];
       	    itoa(PrecioTotalD,totalDolares,10);
        	fprintf(fp,totalDolares);
        	
        	fprintf(fp, "</td>");
        	
		fprintf(fp, "</tr>");
       
       
       	fprintf(fp, "<tr>");
        	fprintf(fp, "<td > Impuesto %13 </td> \n");
        
        	fprintf(fp, "<td colspan='3'>");
        	char totalImpuesto[20];
        	int impuesto = (PrecioTotalD*tipoCambio)*0.13;
        //	printf("\n Impuesto %i",impuesto);
       	    itoa(impuesto,totalImpuesto,10);
        	fprintf(fp,totalImpuesto);
        	
        fprintf(fp, "</td>");
        	
        
		fprintf(fp, "<tr>");
        	fprintf(fp, "<td > Total </td> \n");
        
        	fprintf(fp, "<td colspan='3'>");
        	char Total[20];
        	int total = (((PrecioTotalD*tipoCambio)+impuesto));
        //	printf("\n Impuesto %i",impuesto);
       	    itoa(total,Total,10);
        	fprintf(fp,Total);
        	
        fprintf(fp, "</td>");	
        	
        	
        	
        	
		fprintf(fp, "</tr>");
       
       
       
       
    fprintf(fp, "</table></div>");
	fprintf(fp,"<div class = 'col-md-3'></div></div>");


    fclose(fp);    /* Cerrar el archivo antes de terminar el programa */
    printf("\n\n Se ha creado el archivo Cotizacion.htm \n");

    getch();
}



void agregarNum(int num){
		
	struct numero *nn;
	nn= (struct numero*) malloc (sizeof(struct numero));	
	nn->numero= num;
	nn->sig= NULL;
	
	if(cabezaNum== NULL){
		cabezaNum=nn;
	}else{
		nn->sig= cabezaNum;
		cabezaNum=nn;
	}
}




void crearfactura(struct productos* producto, char* nombreNegocio, char* ubicacionNegocio, char* nombreCliente){
		
	struct factura *nn;
	nn= (struct factura*) malloc (sizeof(struct factura));	
	strcpy(nn->nombreNegocio,nombreNegocio);
	strcpy(nn->ubicacionNegocio,ubicacionNegocio);
	strcpy(nn->nombreCliente,nombreCliente);
	nn->producto= producto;
	nn->sig=NULL;
	
	if(cabezaFac== NULL){
		cabezaFac= nn;
	}else{
		nn->sig= cabezaFac;
		cabezaFac=nn;
	}
}



struct productos* obtenerProductos(int id){
	struct productos *tempP;
	tempP=cabeza;
	while(tempP!=NULL){
		if(tempP->id == id){
			return tempP;
		}else{
			tempP=tempP->sig;
		}
	}
	
	tempP = NULL;
	return tempP;
}



void imprimirFacturas(){
	if(cabezaFac == NULL){
		printf("Lista vacia");
	}
	
	else {
		struct factura* tempFactura = cabezaFac;
		
		printf("\n\n************************COTIZACION***************************************\n\n");
			/*Nombre Cliente*/
			int len=strlen(tempFactura->nombreCliente);
			printf("\n Cliente: ");
			int i;
 			for(i=0;i<len;i++)
   				printf("%c",tempFactura->nombreCliente[i]);	
			
			/*Nombre Negocio*/
			int len1=strlen(tempFactura->nombreNegocio);
			printf("\n Negocio: ");
			int e;
 			for( e=0;e<len1;e++)
   				printf("%c",tempFactura->nombreNegocio[e]);	
		
			
			/*Nombre Ubicacion*/
			int len2=strlen(tempFactura->ubicacionNegocio);
			printf("\n Ubicacion: ");
			int j;
 			for(j=0;j<len2;j++)
   				printf("%c",tempFactura->ubicacionNegocio[j]);	
		
			
		time_t t;
  		struct tm *tm;
  		char fechayhora[100];
  		char *meses[12]={"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
		
			printf("\n\n\n");
			int precioDolar;	
			t=time(NULL);
            
			tm=localtime(&t);
            printf ("Fecha: %02d/%s/%d\n", tm->tm_mday, meses[tm->tm_mon], 1900+tm->tm_year);
			printf("\n ID   Descripcion  Precio Dolares  Precio Colones \n");
		    while(tempFactura!= NULL){
			
		
			printf("\n %d       %s                    %d             %d", tempFactura->producto->id,tempFactura->producto->descripcion,
			tempFactura->producto->precioDolar,tempFactura->producto->precioDolar*tipoCambio);
			
			
			precioDolar = tempFactura->producto->precioDolar;
			PrecioTotalD= PrecioTotalD+precioDolar;
		
			
		
		    tempFactura = tempFactura->sig;
		}
		int impuesto = (PrecioTotalD*tipoCambio)*0.13;
		int totalFac = (((PrecioTotalD*tipoCambio)+impuesto));
		
		
		printf("\n\n\n\n															Total Dolares: %d",PrecioTotalD);
		printf("\n										                                        Total Colones: %d",PrecioTotalD*tipoCambio);
		printf("\n										                                        IVA(13%): %d",impuesto);
		printf("\n										                                        Total: %d",totalFac);
}
		
}


void seleccionarProductos(char* nombreNegocio, char* ubicacionNegocio, char* nombreCliente){
	
	
	if(cabeza == NULL){
		printf("Lista vacia ");
	}
	
	else {
		printf("\n\n Elementos del stock");
		struct productos *temp = cabeza;
		
		while(temp!= NULL){
			
			printf("\n ID %d",temp->id);
			int len=strlen(temp->descripcion);
			printf("\n Descripcion: ");
			int i;
 			for(i=0;i<len;i++)
   				printf("%c",temp->descripcion[i]);			
			printf("\n cantidad: %d\n Precio: %d", temp->cantidadProductos,temp->precioDolar);
			temp = temp->sig;
			printf("\n\n\n");			
		}
	    int contadorB=9;
		int cantidad;
		int id;
		struct productos *productoR;
		
		printf("\n Ingrese la cantidad de productos que desea agregar a la cotizacion: ");
		scanf("%d",&cantidad);
		
		if(cantidad<9){
			printf("\n\n No puede cotizar menos de 9 elementos\n\n\n");
			main();
		}
		

			while(cantidad!=0){
				printf("\n Ingrese el ID: ");
				scanf("%d",&id);
			
				int estaEnLista = comprobarListaNum(id);
			
			    
				if(estaEnLista == 0){
					productoR= obtenerProductos(id);
					agregarNum(id);
					if(productoR != NULL){
						crearfactura(productoR,nombreNegocio,ubicacionNegocio,nombreCliente);
						cantidad= cantidad-1;
						if(id<9){
							contadorB--;
					}
					}
				else{
					printf("\nId digitado no encontrado");
						
					}
		    	}
		    	else{
		    	printf("\n\nproducto ya agregado");
		    	
				}
			
		
		
	}
	}	
	
}

void facturaBasica(){
	//char* nombreNegocio, char* ubicacionNegocio, char* nombreCliente
	/*
	char nombreNegocio [40] ="DESA S.A";
	char ubicacionNegocio[40]= "San Jose";
	char nombreCliente[40]= "Crisly Gonzalez";
	*/
	
	char nombreNegocio [40];
	char ubicacionNegocio[40];
	char nombreCliente[40];
	
	
	printf("\n\n\n\n");

	fflush( stdin );
	printf("\nIngrese el nombre del negocio: "); 
	fflush(stdin);
	scanf("%[^\n]",&nombreNegocio);
	
	
	printf("\nIngrese la ubicacion del negocio: ");
	fflush( stdin );
	scanf("%[^\n]",&ubicacionNegocio);
	
	printf("\nIngrese el nombre del cliente: ");
	fflush( stdin );
	scanf("%[^\n]",&nombreCliente);
	
	
	seleccionarProductos(nombreNegocio,ubicacionNegocio,nombreCliente);

}

int comprobarListaNum(int pnum){
		
		struct numero *num= cabezaNum;
		while(num!=NULL){
			if(num->numero == pnum){
				return 1;
			}
			num= num->sig;
		}
		return 0;
}




void insertarProductos( char * nombreP,int cantidadProductos ,int precioDolar,int id){
	struct productos *nn;
	nn= (struct productos*) malloc (sizeof(struct productos));
	strcpy(nn->descripcion,nombreP);
	nn->cantidadProductos= cantidadProductos;
	nn->precioDolar=precioDolar;
	nn->id=id;
	

	if(cabeza== NULL){
		cabeza= nn;
		nn->sig=NULL;
	}else{
		nn->sig= cabeza;
		cabeza=nn;
	}
}



int escribirArchivoTxt(){
	
	
	printf("Ingrese ID de producto: ");
	fflush( stdin );
    scanf("%d",&product.id);
	
	
	printf("Descripcion: ");
	fflush( stdin);
	scanf("%[^\n]",&product.descripcion);

/**
	printf("Cantidad de productos: ");
	
	scanf("%d",&product.cantidadProductos);
**/	

	printf("Precio: ");
	
	scanf("%d",&product.precioDolar);
	
	
	
	
	FILE *puntA;
	puntA=fopen("Productos.txt","a");
		if(puntA==NULL){
			printf("no se pudo crear");
			return 0;
		}
		fwrite(&product,sizeof(product),1,puntA);
		//printf("Datos guardados");
		fclose(puntA);
	
	getch();

}


int leerArchivoTxt(){

	int contador=0;
	FILE *puntA = fopen("Productos.txt","r");
		if(puntA==NULL){
			printf("no se pudo leer");
			return 1;
		}	
	while(!feof(puntA)){
		fread(&product,sizeof(product),1,puntA);
			
			printf("ID %d\n Nombre: %s\n Precio: %d",product.id,product.descripcion,product.precioDolar);
			insertarProductos( product.descripcion,product.cantidadProductos,product.precioDolar,product.id);
		   
			
			//printf(" agregado list");
			printf("\n\n\n\n");	
			
	}
	
	fclose(puntA);
}

int imprimirListaProductos(){
	
	if(cabeza == NULL){
		printf("Lista vacia");
	}
	
	else {
		printf("\n\n Elementos del stock");
		struct productos *temp = cabeza;
		
		while(temp!= NULL){
			
			printf("\n ID %d",temp->id);
	
			int len=strlen(temp->descripcion);
			printf("\n Nombre producto: ");
			int i;
 			for(i=0;i<len;i++)
   				printf("%c",temp->descripcion[i]);	
		
			printf("\n cantidad: %d\n Precio: %d", temp->cantidadProductos,temp->precioDolar);
			temp = temp->sig;
			printf("\n\n\n");
			
		}
		if(temp==NULL){
			return 0;
		}
	}
}



int main(){

	int opcion,elemt;
	int contador;
	printf("Instrucciones basicas: \n\n 1)Antes de iniciar ingresar el tipo de cambio del dolar\n\n 2)Leer productos del archivo antes de cotizar\n\n\n");
	printf("1.Tipo Cambio Dolar\n2.Ingresar productos al archivo\n3.Leer de archivo \n4.Lista productos \n5.Corizacion \n6.Salir\n Option: ");
	scanf("%d",&opcion);
	switch(opcion)
	{
		case 1:
			printf(" \n Ingrese el tipo de cambio actual $$: ");
			scanf("%i",&tipoCambio);
			printf("\n\n");
			printf("\n\n");
			main();
			
		case 2:
			printf("\n Ingresando productos al almacen\n\n");
			contador=0;
			while(contador!=2){
				fflush( stdout );
				escribirArchivoTxt();
        		printf("\n\n");
				contador++;
				}
	
			main();
			printf("\n\n");
			
			
			
		case 3:
			
			printf("\n Productos del almacen (cargados desde el archivo)\n\n");
			leerArchivoTxt();
			main();
			printf("\n\n");
		
			
		   
			
		case 4:
			printf("\n Imprimiendo lista \n\n");
		    imprimirListaProductos();
			main();
			printf("\n\n");
			
			
		
			
		case 5:
			facturaBasica();
			printf("\n\n");
			imprimirFacturas();
			crearFacturaHTML();
			printf("\n\n");
			printf("\n\n\n");
			main();
			printf("\n\n\n");
			
		case 6:
			return 0;
		


	return 0;
   
}
}



