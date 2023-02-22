/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente para encapsular el menu del juego. Es decir, con tal de reducir el numero
 *             de lineas del main.c (o PJ2_wesley.lucas.c), he creado este modulo para envolver toda la funcionalidad
 *             del menu, ya sea mostrar las opciones, meter la funcionalidad de cada una de estas y ademas de generar el
 *             fichero log.txt de la opcion 4. Remarcar que no he implementado un modulo de la opcion 4, ya que a
 *             diferencia de los otros 3 modulos, esta contiene muy pocas lineas de codigo (para ser exactos, 17 lineas)
 *             y no tendria sentido crear un modulo exclusivamente para esta.
 *             P.D. No se si esta bien visto este aspecto, pero he introducido bastantes argumentos de entrada en el
 *             procedimiento de menuExe. He intentado cambiar la logica, reducir el numero de variables, etc... Pero por
 *             mas que pensase en como llevarlo a cabo, no solo perdia mas tiempo al reformularlo de distintas maneras,
 *             sino que atrasaba el desarrollo del programa. Principalmente, mi intencion con este proyecto ha sido hacerlo
 *             lo optimo posible a nivel de lineas de codigo.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Librerias generales del sistema
#include <stdio.h>
#include <stdlib.h>

// Librerias propias
#include "opcion1.h"
#include "opcion2.h"
#include "opcion3.h"
#include "sortedlist.h"

// Include del fichero .h del mismo módulo
#include "menu.h"

// Funcion que se encarga de generar el log de texto de los resultados finales de final de temporada.
void generaLog(int j, int l, int k, int num_premios, int num_pilotos, FILE *logp, OpcionTres *opc_3){
    if (j != 5) {
        printf("La temporada aun no ha finalizado.\n");
    }else{
        logp = fopen ("log.txt", "w");

        for (l = 0; l < num_premios; l++) {
            fprintf(logp, "%s %s %s%c", "Clasificacion", "del", opc_3[l].nombre_gp, '\n');

            // Los datos relevantes a guardar son el nombre del grande premio, la posicion de cada corredor en la que ha
            // quedado en cada grande premi, el nombre del corredor, tiempo que ha tardado y los puntos obtenidos.
            for (k = 0; k < num_pilotos + 1; k++) {
                fprintf(logp, "%d%s %s %s %.2f %s%s %s%s %d%c", opc_3[l].rank_def[k].posicion, ".", opc_3[l].rank_def[k].nombre, "con", opc_3[l].rank_def[k].tiempo, "segundos", ".", "Puntos", ":", opc_3[l].rank_def[k].puntos, '\n');
            }
            fprintf(logp, "%c", '\n');
        }
        fclose(logp);
        printf("\nInformacion guardada con exito en archivo generado 'log.txt' (cmake-build-debug -> log.txt)\n\n");
    }
}

// Funcion que se encarga de mostrar las diferentes opciones que ofrece al usuario escoger, ademas de añadir como
// funcion extra el poner por teclado a que opcion acceder y procesar la respuesta.
void displayMenu(char opcion[100], char salida[10], int *exit_cmp, int *atoi_opc){
    int i = 0;

    printf("Bienvenidos a LS Racing!\n\n");
    printf("\t1.Configurar coche\n");
    printf("\t2.Carrera\n");
    printf("\t3.Ver clasificacion\n");
    printf("\t4.Guardar temporada\n\n");
    printf("Que opcion quieres ejecutar?");
    fgets(opcion, 100, stdin);
    opcion[strlen(opcion) - 1] = '\0';
    *exit_cmp = strcmp(salida, opcion);
    for (i = 0; opcion[i] != '\0'; i++){
        *atoi_opc = (*atoi_opc * 10) + (opcion[i] - '0');
    }
    *atoi_opc = atoi(opcion);
}

// Funcion que unicamente se encarga de inicializar algunas variables a unos valores predeterminados necesarios para
// que funcione debidamente. Comentar que hacer un strcpy de la variable salida junto con el mensaje 'exit' fastidiaba
// completamente el programa. De ahi a que voy casilla por casilla asignando una letra de la palabra.
// Devuelve como valor de retorno el valor de acceso de opcion 1.
OpcionUno initVars(OpcionUno opc_1, int *exit_cmp, char salida[5]){
    opc_1.acceso = 0;
    *exit_cmp = 1;
    salida[0] = 'e';
    salida[1] = 'x';
    salida[2] = 'i';
    salida[3] = 't';
    salida[4] = '\0';

    return opc_1;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Agrupar y ejecutar todas las funciones que van desde la opcion 1 hasta la 4 del programa.
 * @Parametros:     in: opc_1 = tipo propio 'OpcionUno' que contiene todas las variables referentes a la opcion 1.
 *                  in: opc_2 = tipo propio 'OpcionDos' que contiene todas las variables referentes a la opcion 2.
 *                  in: opc_3 = tipo propio 'OpcionTres' que contiene todas las variables referentes a la opcion 3.
 *                  in: pieza = tipo propio 'InfoPieza' que contiene todas las variables referentes a las piezas.
 *                  in: corredor = tipo propio 'InfoCorredor' que contiene todas las variables referentes a los
 *                                 corredores.
 *                  in: stats_def = tipo propio 'InfoBase' que contiene todas las variables referentes a las
 *                                  estadisticas base.
 *                  in: list = tipo propio 'SortedList' que contiene todas las variables necesarias para pasar de un
 *                             nodo a otro.
 *                  in: node_opc2 = tipo propio 'GPese' que contiene todas las variables referentes a los grandes
 *                                  premios para moverse por los nodos de la lista ordenada.
 *                  in: suma = tipo propio 'StructSuma' que contiene todas las variables referentes a la suma
 *                             acumulativa de factores como velocidad, aceleracion, etc...
 *                  in: suma_p = tipo propio 'DatosTotal' que contiene todas las variables referentes a la muestra
 *                               de resultados finales al acabar la temporada.
 *                  in: num_piezas = variable que indica el numero de piezas que hay en total en el fichero de texto de
 *                                   piezas.
 *                  in: num_premios = variable que indica el numero de premios que hay en total en el fichero de texto de
 *                                    grandes premios.
 *                  in: num_pilotos = variable que indica el numero de pilotos que hay en total en el fichero binario de
 *                                    corredores.
 * @Retorno: ----
 *
 **********************************************************************************************************************/
void menuExe (OpcionUno opc_1, OpcionDos *opc_2, OpcionTres *opc_3, InfoPieza *pieza, InfoCorredor *corredor, InfoBase *stats_def, SortedList list, GPese node_opc2, StructSuma *suma, DatosTotal *suma_p, int num_piezas, int num_premios, int num_pilotos){
    FILE *logp;
    int opc1_in = 0, opc2_in = 0, j = 0, k = 0, l = 0;
    int exit_cmp = 0, atoi_opc = 0;
    char opcion[100], salida[5], nom_piloto[27];

    // Funcion que se encarga de generar el log de texto de los resultados finales de final de temporada.
    opc_1 = initVars(opc_1, &exit_cmp, salida);
    // Nos situamos al principio de la lista ordenada.
    SORTEDLIST_goToHead(&list);

    // Mientras lo que escribamos en el teclado no sea 'exit', entramos dentro de un bucle infinito.
    while (exit_cmp != 0) {
        displayMenu(opcion, salida, &exit_cmp, &atoi_opc);

        // Si escribimos la palabra 'exit', nos salimos del programa y finalizamos cuando queramos.
        if (exit_cmp == 0) {
            printf("\nHasta pronto!\n\n");
        }else{

            if (atoi_opc > 4 || atoi_opc < 1) {
                printf("Error. Opcion no valida.\n\n");
            }else{

                if (atoi_opc == 1) {

                    // Llena las variables del tipo propio 'OpcionUno', ademmas de reproducir la ventana grafica de
                    // seleccion de piezas y motores de preferencia.
                    opc_1 = getOpc1Info(opc_1, pieza, num_piezas, &opc1_in);
                    strcpy(nom_piloto, opc_1.nombre);
                }else{

                    if (atoi_opc == 2) {

                        // Si entramos en la opcion 2 sin antes haber configurado nuestro coche en la opcion 1, nos
                        // salta error y tendremos que configurar el coche antes si queremos proseguir.
                        if (opc1_in != 1) {
                            printf("Aun no has configurado el coche.\n\n");
                        }else{
                            // Pillamos el nodo actual de grande premio a cursar.
                            node_opc2 = SORTEDLIST_get(&list);

                            // Si hemos acabado de cursar todos los grandes premios, no tenemos derecho a volver a
                            // seleciionar la opcion 2.
                            if (SORTEDLIST_isAtEnd(list)) {
                                printf("Ya has finalizado la temporada.\n\n");
                            }else{
                                // Llena las variables del tipo propio 'OpcionDos', ademmas de reproducir la ventana
                                // grafica de simulacion de la carrera los resultados de nuestro piloto respecto a la
                                // posicion del ranking en la que se posiciona.
                                opc_2 = getOpc2Info(opc_2, opc_1, num_pilotos, num_piezas, pieza, stats_def, suma, node_opc2, corredor, j);
                                strcpy(opc_1.nombre, nom_piloto);

                                // Aumentamos los valor de indice como indicador de cuando acceder a segun que
                                // resultados de la opcion 3, ademas de pasar al siguiente nodo de grande premio a
                                // cursar respectivamente.
                                j++;
                                SORTEDLIST_next(&list);
                                opc2_in++;
                            }

                        }
                    }else{
                        if (atoi_opc == 3) {

                            // Si entramos en la opcion 3 sin antes haber configurado nuestro coche en la opcion 1 o
                            // habiendo empezado la primera clasficiacion GP, nos salta error y tendremos que
                            // completar los pasos previamente mencionados.
                            if (opc2_in < 1) {
                                printf("La temporada aun no ha empezado.\n");
                            }else{

                                // Si el valor de indice j es menor a 5, solo se nos abrira las ventanas graficas de
                                // cada grande premio de forma individual. Es decir, se nos mostrara la clasificacion de
                                // cada grande premio segun el tiempo que han tardado los corredores en completar.
                                if (j < 5){

                                    // Muestra el ranking de mayor a menor tiempo de completar la carrera de cada GP
                                    // participado.
                                    opc_3 = displayOpc3Results(opc_3, opc_2, j, num_pilotos, opc2_in);

                                    // Si el valor de indice j es igual a 4, significa que ha acabado de realizar el
                                    // cuarto grande premio, y por tanto se pone a ordenar los corredores de menor a
                                    // mayor a ranking en funcion de los puntos acumulados en cada grande premio.
                                    if (j == 4){

                                        // Llenar el tipo propio 'DatosTotal' de la informacion esencial a mostrar luego
                                        // en los resultados finales del ranking de la temporada finalizada.
                                        suma_p = sortPoints (suma_p, opc_3, opc_1, corredor, &j, num_pilotos, num_premios);
                                    }
                                }

                                // Si el valor de indice j es igual a 5, significa que no solo hemos acabado los grandes
                                // premios, sino que nos disponemos a finalmente mostrar en una ventana grafica el
                                // ranking final segun los puntos que han sido ordenados previamente por la funcion
                                // sortPoints.
                                if (j == 5){

                                    // Muestra el ranking de la clasificacion final de temporada en base al numero de
                                    // puntos acumulado en cada grande premio participado de cada corredor.
                                    displayPointsRanking (suma_p, j, num_pilotos);
                                }
                            }
                        }else{

                            if (atoi_opc == 4) {
                                // Funcion que se encarga de generar el log de texto de los resultados finales de final
                                // de temporada.
                                generaLog(j, l, k, num_premios, num_pilotos, logp, opc_3);
                            }
                        }
                    }
                }
            }
        }
    }
}