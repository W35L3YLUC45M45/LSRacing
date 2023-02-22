/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente para la opcion 3 del programa. Aquí principalmente se trabaja en ordenar
 *             las posiciones de los pilotos en base a dos factores: el tiempo y los puntos acumulados en cada GP. Se
 *             nos pedirá ejecutar una ventana gráfica con los resultados de ranking en base a estos dos factores
 *             previamente mencionados, y para llevarlo a cabo, se tendrá que trabajar y manejar con la memoria dinámica
 *             de todas las variables con las que se han trabajado.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_OPCION3_H_
#define _PJ2_WESLEY_LUCAS_OPCION3_H_

// Librerias generales del sistema
#include <string.h>

// Librerias propias
#include "estructuras.h"
#include "sortedlist.h"
#include "LS_allegro.h"

/***********************************************************************************************************************
 *
 * @Finalidad: Mostrar el ranking de mayor a menor tiempo de completar la carrera de cada GP participado.
 * @Parametros:     in/out: opc_3 = tipo propio 'OpcionTres' que contiene todas las variables referentes a la opcion 3.
 *                  in: opc_2 = tipo propio 'OpcionDos' que contiene todas las variables referentes a la opcion 2.
 *                  in: j = variable que hace referencia al grande premioa actual sobre el que nos hallamos en el
 *                          momento (variable indice).
 *                  in: num_pilotos = variable que indica el numero de pilotos que hay en total en el fichero binario de
 *                                    corredores.
 *                  in: opc2_in = variable de flag que avisa que al presionar la opcion 3 sin antes haber pasado por la
 *                                opcion 2 nos retorna al menu.
 * @Retorno: Devuelve la variable opc_3 del tipo propio 'OpcionTres' llena de informacion para dicho propio.
 *
 **********************************************************************************************************************/
OpcionTres *displayOpc3Results (OpcionTres *opc_3, OpcionDos *opc_2, int j, int num_pilotos, int opc2_in);

/***********************************************************************************************************************
 *
 * @Finalidad: Llenar el tipo propio 'DatosTotal' de la informacion esencial a mostrar luego en los resultados finales
 *             del ranking de la temporada finalizada.
 * @Parametros:     in/out: suma_p = tipo propio 'DatosTotal' que contiene todas las variables referentes a la muestra
 *                                   de resultados finales al acabar la temporada.
 *                  in: opc_3 = tipo propio 'OpcionTres' que contiene todas las variables referentes a la opcion 3.
 *                  in: opc_1 = tipo propio 'OpcionUno' que contiene todas las variables referentes a la opcion 1.
 *                  in: corredor = tipo propio 'InfoCorredor' que contiene todas las variables referentes a los
 *                                 corredores.
 *                  in: j = variable que hace referencia al grande premioa actual sobre el que nos hallamos en el
 *                          momento (variable indice).
 *                  in: num_pilotos = variable que indica el numero de pilotos que hay en total en el fichero binario de
 *                                    corredores.
 *                  in: num_premios = variable que indica el numero de premios que hay en total en el fichero de texto
 *                                    de grandes premios.
 * @Retorno: Devuelve la variable suma_p del tipo propio 'DatosTotal' llena de informacion para dicho propio.
 *
 **********************************************************************************************************************/
DatosTotal *sortPoints (DatosTotal *suma_p, OpcionTres *opc_3, OpcionUno opc_1, InfoCorredor *corredor, int *j, int num_pilotos, int num_premios);

/***********************************************************************************************************************
 *
 * @Finalidad: Mostrar el ranking de la clasificacion final de temporada en base al numero de puntos acumulado en cada
 *             grande premio participado de cada corredor.
 * @Parametros:     in: suma_p = tipo propio 'DatosTotal' que contiene todas las variables referentes a la muestra
 *                               de resultados finales al acabar la temporada.
 *                  in: j = variable que hace referencia al grande premioa actual sobre el que nos hallamos en el
 *                          momento (variable indice).
 *                  in: num_pilotos = variable que indica el numero de pilotos que hay en total en el fichero binario de
 *                                    corredores.
 * @Retorno: ----
 *
 **********************************************************************************************************************/
void displayPointsRanking (DatosTotal *suma_p, int j, int num_pilotos);

#endif