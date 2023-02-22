/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente para la opcion 2 del programa. Aqui se empieza a trabajar densamente con la
 *             libreria de LS_allegro. Esta sobretodo enfocado en jugar y saber manejar los valores de la informacion
 *             extraida de los ficheros con tal de simular una carrera de coches. Y para ello requiere ademas saber
 *             hacer buen manejo y control de las variables/tipos con punteros.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef PJ2_WESLEY_LUCAS_OPCION2_H
#define PJ2_WESLEY_LUCAS_OPCION2_H

// Librerias generales del sistema
#include <string.h>
#include <stdlib.h>

// Librerias específicas de sistema
#include <time.h>

// Librerias propias
#include "estructuras.h"
#include "sortedlist.h"

/***********************************************************************************************************************
 *
 * @Finalidad: Llenar las variables del tipo propio 'OpcionDos', ademas de reproducir la ventana grafica de simulacion
 *             de la carrera los resultados de nuestro piloto respecto a la posicion del ranking en la que se posiciona.
 * @Parametros:     in/out: opc_2 = tipo propio 'OpcionDos' que contiene todas las variables referentes a la opcion 2.
 *                  in: opc_1 = tipo propio 'OpcionUno' que contiene todas las variables referentes a la opcion 1.
 *                  in: num_pilotos = variable que indica el numero de pilotos que hay en total en el fichero binario de
 *                                    corredores.
 *                  in: num_piezas = variable que indica el numero de piezas que hay en total en el fichero de texto de
 *                                   piezas.
 *                  in: pieza = tipo propio 'InfoPieza' que contiene todas las variables referentes a las piezas.
 *                  in: stats_def = tipo propio 'InfoBase' que contiene todas las variables referentes a las
 *                                  estadisticas base.
 *                  in: suma = tipo propio 'StructSuma' que contiene todas las variables referentes a la suma
 *                             acumulativa de factores como velocidad, aceleracion, etc...
 *                  in: node_opc2 = tipo propio 'GPese' que contiene todas las variables referentes a los grandes
 *                                  premios para moverse por los nodos de la lista ordenada.
 *                  in: corredor = tipo propio 'InfoCorredor' que contiene todas las variables referentes a los
 *                                 corredores.
 *                  in: j = variable que hace referencia al grande premioa actual sobre el que nos hallamos en el
 *                          momento (variable indice).
 * @Retorno: Devuelve la variable opc_2 del tipo propio 'OpcionDos' llena de informacion para dicho propio.
 *
 **********************************************************************************************************************/
OpcionDos * getOpc2Info (OpcionDos *opc_2, OpcionUno opc_1, int num_pilotos, int num_piezas, InfoPieza *pieza, InfoBase *stats_def, StructSuma *suma, GPese node_opc2, InfoCorredor *corredor, int j);

#endif
