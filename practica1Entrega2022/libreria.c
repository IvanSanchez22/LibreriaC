#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h"
#define MAX_LENGTH_LINE 1024

//Funcion Head
int head(int n){

    //Declaracion de variables
    char lineBuffer[MAX_LENGTH_LINE];
    int counter;
    int i;
    int lenght;
    int topLimit;
    char **list;

    //Asignaciones iniciales
    counter = 0;
    lenght = 0;
    list = NULL;

    //Si n es positivo solo muestra las n primeras lineas
    if(n > 0){
        //Mostramos las n primeras lineas o hasta que se acaben si hay menos que n 
        while(counter < n && fgets(lineBuffer, MAX_LENGTH_LINE, stdin) != NULL){
            fputs(lineBuffer, stdout);
            counter ++; //Variable para controlar las líneas que llevamos mostradas
        }
    }

    //Si n es negativo muestra todas las lineas menos las n ultimas, por ello se van creando posiciones en la lista por cada linea nueva
    else if (n < 0){
        list = calloc(1, sizeof(char*));
        counter = 0;
        while(fgets(lineBuffer, MAX_LENGTH_LINE, stdin) != NULL){
            lenght = strlen(lineBuffer); //Guardamos la longitud de la linea
            lineBuffer[lenght - 1] = '\n'; //Añadimos salto de línea al final
            list[counter] = calloc(lenght, sizeof(char)); //Reservamos el espacio de memoria estrictamente necesario en cada posicion
            strcpy(list[counter], lineBuffer); //Copiamos en la posición de la lista que corresponde la línea
            counter ++; //Aumentamos la variable counter para tener siempre los elementos totales de la lista
            list = realloc(list, (counter+1)*sizeof(*list)); //Creamos nuevas posiciones en la lista
        }
        topLimit = counter + n; //La variable topLimit es hasta la posición que tenemos que mostrar ya que n es negativo
        if (topLimit <=0){
            return 0;
        }
        //Mostramos por pantalla y liberamos memoria
        for (i = 0; i < topLimit; i++){
            fputs(list[i], stdout);
            free(list[i]);
        }
        free(list);
    }
    return 0;
}

//Funcion Tail
int tail(int n){

    //Declaracion de variables
    char lineBuffer[MAX_LENGTH_LINE];
    int counter;
    int j;
    int i;
    int length;
    char **list;

    //Asignaciones iniciales
    counter = 0;
    length = 0;
    list = NULL;

    //Si n es menor que 0, tomamos su valor absoluto, si es 0 salimos al no mostrar nada
    if(n < 0){n = abs(n);}
    else if (n == 0 ){ return 0;}

    list = calloc(n, sizeof(char*)); //Reservamos solo las n posiciones que nos piden
    //En este bucle tenemos la insercion hasta n de lineas que queremos, al llegar a rellenar este array, entramos en el primer if
    //que nos permite retroceder una posicion hacia atras en todas las posiciones, aniadiendole al final la nueva linea que tenemos
    //asi conseguimos quedarnos con las n ultimas lineas y no con todas, haciendo un uso eficiente de la memoria.
    while(fgets(lineBuffer, MAX_LENGTH_LINE, stdin) != NULL){
        if(counter == n-1){
            for(j = 0; j < n-1; j++){ //Una vez la lista llena si se siguen leyendo nuevas lineas se desplaza la lista entera
                list[j] = list[j+1]; // perdiendo el primer elemento sucesivamente para qudarnos con las n últimas
            }
        }
        else if (counter < n)  {counter++;}
        length = strlen(lineBuffer);
        list[counter] = calloc(length, sizeof(char));
        strcpy(list[counter], lineBuffer);
    }
    //Una vez aquí ya tenemos la lista llena con las n últimas posiciones
    //Muestra por pantalla y libera la memoria
    for (i = 0; i < n; i++){
        if(list[i]){
           fputs(list[i], stdout);
           free(list[i]); //Liberamos cada posición
        }    
    }
    free(list); //Liberamos la lista entera
    return 0;
}

//Funcion longlines
int longlines(int n){

    //Declaración de variables
    char lineBuffer[MAX_LENGTH_LINE];
    char **list;
    int counter;
    int i,k;
    char *aux;
    int origin;
      
    //Asignaciones iniciales
    list = NULL;
    counter = 0;

    //Si n es menor que 0, tomamos su valor absoluto, si es 0 salimos al no mostrar nada
    if(n < 0){n = abs(n);}
    else if (n == 0){return 0;}

    list = calloc(1, sizeof(char*));

    //En caso de que n sea 1, solo comprobamos si el valor previo es mayor y lo mantenemos de ser asi.
    if(n == 1){
        list[0] = calloc(MAX_LENGTH_LINE, sizeof(char));
        while(fgets(lineBuffer, MAX_LENGTH_LINE, stdin) != NULL){
            if(strlen(list[0]) <= strlen(lineBuffer)){
                strcpy(list[0], lineBuffer);
            }
        }    
    }
    //Al no ser uno, automaticamente guardaremos todas las lineas en la lista y las ordenaremos posteriormente
    else{
        //Leemos y almacenamos todas las lineas
        while(fgets(lineBuffer, MAX_LENGTH_LINE, stdin) != NULL){
            list[counter] = calloc(MAX_LENGTH_LINE, sizeof(char));
            strcpy(list[counter], lineBuffer);
            counter ++;
            list = realloc(list, (counter+1)*sizeof(*list)); //Añadimos nueva posición
        }
        //Ordenacion de las lineas de menor a mayor
        for (i = 0; i  < counter ; i++){
            for (k = 0; k < counter; k++){
                if(strlen(list[i]) < strlen(list[k])){
                    aux = strdup(list[i]); //almacenamos la cadena de la posición i en aux para no perderla
                    strcpy(list[i], list[k]); //en la posición i guardamos la cadena de la posición k
                    strcpy(list[k], aux); //en la posición k guardamos la cadena almacenada anteriormente en aux
                }
            }
        }
    }      
    //Variable para corregir que si pedimos 40 lineas y solo hay 5, nos imprima desde 0. Si no, la variable es counter - n.
    if (n > counter){
        origin = 0;
    }else{
        origin = counter - n; //origin sería hasta la posición que queremos imprimir empezando desde el final 
                              // ya que están ordenadas de menor a mayor (quizá deberíamos haberla llamado end)
    }
    //Mostramos por pantalla de forma inversa para imprimir de mayor a menor y liberamos memoria
    for (i = counter; i >= origin; i--){
        if(list[i]){
            fputs(list[i], stdout);
            free(list[i]);
        }
    }
    free(list);
    return 0; 
}