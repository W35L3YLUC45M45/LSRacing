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

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_MENU_H_
#define _PJ2_WESLEY_LUCAS_MENU_H_

// Librerias propias
#include "estructuras.h"
#include "opcion1.h"
#include "opcion2.h"
#include "opcion3.h"
#include "sortedlist.h"

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
void menuExe (OpcionUno opc_1, OpcionDos *opc_2, OpcionTres *opc_3, InfoPieza *pieza, InfoCorredor *corredor, InfoBase *stats_def, SortedList list, GPese node_opc2, StructSuma *suma, DatosTotal *suma_p, int num_piezas, int num_premios, int num_pilotos);

#endif
