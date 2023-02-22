/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente para la opcion 1 del programa. Desde almacenar la informacion de peticion
 *             de informacion del usuario en el registro 'OpcionUno', hasta mostrar el configurador del programa donde
 *             podemos escoger los diferentes tipos de pieza, motores que nos sea de interes para competir mas adelante
 *             en la simulacion de la carrera en la opcion 2.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_OPCION1_H_
#define _PJ2_WESLEY_LUCAS_OPCION1_H_

// Librerias generales del sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Librerias propias
#include "LS_allegro.h"
#include "estructuras.h"

/***********************************************************************************************************************
 *
 * @Finalidad: Llenar las variables del tipo propio 'OpcionUno', ademms de reproducir la ventana grafica de seleccion
 *             de piezas y motores de preferencia.
 * @Parametros:     in/out: opc_1 = tipo propio 'OpcionUno' que contiene todas las variables referentes a la opcion 1.
 *                  in: pieza = tipo propio 'InfoPieza' que contiene todas las variables referentes a las piezas.
 *                  in: num_piezas = variable que indica el numero de piezas que hay en total en el fichero de texto de
 *                                   piezas.
 *                  in: opc1_in = variable de flag que avisa que al volver a presionar la opcion 1 se nos muestra la
 *                                pantalla de configuracion de nuestro coche en vez de la peticion de datos de nuestro
 *                                piloto.
 * @Retorno: Devuelve la variable opc_1 del tipo propio 'OpcionUno' llena de informacion para dicho propio.
 *
 **********************************************************************************************************************/
OpcionUno getOpc1Info (OpcionUno opc_1, InfoPieza *pieza, int num_piezas, int *opc1_in);

#endif