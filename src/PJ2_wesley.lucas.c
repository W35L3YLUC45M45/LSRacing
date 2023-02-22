/***********************************************************************************************************************
 *
 * @Proposito: Trabajar y entender de forma practica como estructurar un codigo de extension larga en varios modulos,
 *             ademas de trabajar conceptos vitales como la memoria dinamica, tratamiento de ficheros, uso de
 *             estructuras de datos lineales, etc... En general, en este proyecto se trabajan no solo los conceptos
 *             aprendidos desde el principio del curso, sino nuevos tambien aprendidos durante el segundo semestre que
 *             nos ayuda a entender, como estudiantes de programacion, como seguir el modelo ideal de un proyecto de
 *             programacion trabajando con memoria dinamica, encapsulacion, etc...
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Librerías generales de sistema
#include <stdio.h>
#include <stdlib.h>

// Librerías propias
#include "ficheros.h"
#include "menu.h"
#include "sortedlist.h"

int main(int argc, char **argv) {
    FILE *p, *gps, *c, *b;
    int i = 0, num_piezas = 0, num_premios = 0, num_pilotos = 7, num_coches = 1, f_size = 0;
    OpcionUno opc_1;
    OpcionDos *opc_2;
    OpcionTres *opc_3;
    InfoPieza *pieza;
    StructSuma suma;
    InfoGPs *gpese;
    InfoCorredor *corredor;
    InfoBase *stats, stats_def;
    DatosTotal *suma_p;
    SortedList list;
    InfoGPs gps_;
    GPese node_opc2;

    // Si el numero de argumentos que recibe el programa es menor a 5, se finaliza automaticamente.
    if (argc != 5) {
        printf("Error. El programa tiene que recibir 5 argumentos.");
    }else{
        // Abre un fichero de texto. Sobretodo comprueba que no haya un error de procesamiento de fichero.
        p = aperturaFicheroTxt(argv[1]);

        if (p != NULL) {
            // Comprueba si el fichero sobre el que se lee contiene informacion o no.
            f_size = compruebaEstadoFichero(p, f_size);

            if (f_size != 0) {
                // Lee el fichero de texto de piezas y almacenar toda la informacion que se encuentra dentro de este en
                // un tipo creado especificamente para este, llamado 'InfoPieza'.
                pieza = guardadoInfoPiezas(p, &num_piezas);

                // Abre un fichero de texto. Sobretodo comprueba que no haya un error de procesamiento de fichero.
                gps = aperturaFicheroTxt(argv[2]);

                if (gps != NULL) {
                    // Comprueba si el fichero sobre el que se lee contiene informacion o no.
                    f_size = compruebaEstadoFichero(gps, f_size);

                    if (f_size != 0) {
                        // Leer el fichero de texto de piezas y almacenar toda la informacion que se encuentra dentro de
                        // este en un tipo creado especificamente para este, llamado 'InfoGPs'.
                        gpese = guardadoInfoGPs(gps, &num_premios);

                        // Crea una lista ordenada vacia. Si la lista falla en crear el nodo fantasma, esta actualizara
                        // el valor de error del codigo a LIST_ERROR_MALLOC
                        list = SORTEDLIST_create();

                        for (i = 0; i < num_premios; i++) {
                            gps_ = gpese[i];

                            // Inserta el elemento especificado en la lista en la posicion definida por el algoritmo de
                            // orden. Cambia el punto de vista del elemento (si es que hay) y cualquiera de los
                            // elementos hacia la derecha. Si la lista falla en crear el nuevo nodo donde guardar el
                            // elemento, actualizara el valor de error a LIST_ERROR_MALLOC.
                            SORTEDLIST_sortedAdd(&list, gps_, num_premios);
                        }
                        // Abre un fichero binario. Sobretodo comprueba que no haya un error de procesamiento de
                        // fichero.
                        c = aperturaFicheroBin(argv[3]);

                        if (c != NULL) {
                            // Comprueba si el fichero sobre el que se lee contiene informacion o no.
                            f_size = compruebaEstadoFichero(c, f_size);

                            if (f_size != 0) {
                                // Leer el fichero de texto de corredores y almacenar toda la informacion que se
                                // encuentra dentro de este en un tipo creado especificamente para este, llamado
                                // 'InfoCorredor'.
                                corredor = guardadoInfoCorredores(c, num_pilotos);

                                // Abre un fichero binario. Sobretodo comprueba que no haya un error de procesamiento de
                                // fichero.
                                b = aperturaFicheroBin(argv[4]);

                                if (b != NULL) {
                                    // Comprueba si el fichero sobre el que se lee contiene informacion o no.
                                    f_size = compruebaEstadoFichero(b, f_size);

                                    if (f_size != 0) {
                                        // Leer el fichero de texto de piezas y almacenar toda la informacion que se
                                        // encuentra dentro de este en un tipo creado especificamente para este, llamado
                                        // 'Pieza'.
                                        stats = guardadoInfoBase(b, num_coches);

                                        // Copia la informacion del fichero de estadisticas base a uno del mismo tipo
                                        // considerado definitivo.
                                        stats_def = *stats;

                                        // Peticion de memoria dinamica para el tipo 'OpcionDos'.
                                        opc_2 = (OpcionDos *) malloc (num_premios * sizeof(OpcionDos));

                                        if (opc_2 == NULL) {
                                            printf("No tenemos reserva memoria.\n");
                                        }else{

                                            // Peticion de memoria dinamica para diferentes subtipos del tipo
                                            // principal 'OpcionDos'. En este caso los subtipos son 'ControlTiempo' y
                                            // 'InfoCarrera'.
                                            for (i = 0; i < num_premios; i++) {
                                                opc_2[i].t_total = (ControlTiempo *) malloc ((num_pilotos + 1) * sizeof(ControlTiempo));

                                                if (opc_2[i].t_total == NULL) {
                                                    printf("No tenemos reserva memoria.\n");
                                                }else{
                                                    opc_2[i].ranking = (InfoCarrera *) malloc ((num_pilotos + 1) * sizeof(InfoCarrera));

                                                    if (opc_2[i].ranking == NULL) {
                                                        printf("No tenemos reserva memoria.\n");
                                                    }else{
                                                    }
                                                }
                                            }

                                            // Peticion de memoria dinamica para el tipo 'OpcionTres'.
                                            opc_3 = (OpcionTres *) malloc (num_premios * sizeof(OpcionTres));

                                            if (opc_3 == NULL) {
                                                printf("No tenemos reserva memoria.\n");
                                            }else{

                                                // Peticion de memoria dinamica para un subtipo del tipo
                                                // principal 'OpcionTres'. En este caso el subtipo en cuestion es
                                                // 'DefRanking'.
                                                for (i = 0; i < num_premios; i++) {
                                                    opc_3[i].rank_def = (DefRanking *) malloc ((num_pilotos + 1) * sizeof(DefRanking));

                                                    if (opc_3[i].rank_def == NULL) {
                                                        printf("No tenemos reserva memoria.\n");
                                                    }else{
                                                    }
                                                }

                                                // Peticion de memoria dinamica para el tipo 'DatosTotal'.
                                                suma_p = (DatosTotal *) malloc ((num_pilotos + 1) * sizeof(DatosTotal));

                                                if (suma_p == NULL){
                                                    printf("No tenemos reserva memoria.\n");
                                                }else{

                                                    // Agrupa y ejecuta todas las funciones que van desde la opcion 1
                                                    // hasta la 4 del programa.
                                                    menuExe(opc_1, opc_2, opc_3, pieza, corredor, &stats_def, list, node_opc2, &suma, suma_p, num_piezas, num_premios, num_pilotos);

                                                    // Libera la memoria del tipo 'DatosTotal'.
                                                    free(suma_p);

                                                    // Libera la memoria del subtipo 'DefRanking'.
                                                    for (i = 0; i < num_premios; i++){
                                                        free(opc_3[i].rank_def);
                                                    }
                                                }
                                                // Libera la memoria del tipo 'OpcionTres'.
                                                free(opc_3);

                                                // Libera la memoria de los subtipos 'ControlTiempo' y 'InfoCarrera'.
                                                for (i = 0; i < num_premios; i++){
                                                    free(opc_2[i].ranking);
                                                    free(opc_2[i].t_total);
                                                }
                                            }
                                            // Libera la memoria del tipo 'OpcionDos'.
                                            free(opc_2);
                                        }
                                        // Libera la memoria del tipo 'InfoBase'.
                                        free(stats);
                                        // Cierra el fichero de estadisticas base sobre el que ya hemos operado.
                                        cierreFichero(b);
                                    }
                                    // Libera la memoria del tipo 'InfoCorredor'.
                                    free(corredor);
                                }
                                // Cierra el fichero de corredores sobre el que ya hemos operado.
                                cierreFichero(c);
                            }
                            // Libera la memoria del tipo 'InfoGPs'.
                            free(gpese);
                        }
                        SORTEDLIST_destroy(&list);
                        // Cierra el fichero de grandes premios sobre el que ya hemos operado.
                        cierreFichero(gps);
                    }

                    // Libera la memoria del subtipo 'Motor' del tipo 'Pieza'.
                    for (i = 0; i < num_piezas; i++) {
                        free(pieza[i].motor);
                    }
                    // Libera la memoria del tipo 'InfoPieza'.
                    free(pieza);
                }
                // Cierra el fichero de piezas sobre el que ya hemos operado.
                cierreFichero(p);
            }
        }
    }
    return 0;
}