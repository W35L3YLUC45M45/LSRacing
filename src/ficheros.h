/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente solo para el tratamiento de los ficheros que introducimos como argumentos.
 *             Es decir, aparte de abrirlos y ver si estan vacios, tambien nos sirve para extraer toda la informacion
 *             que contienen dentro y luego almacenarla en diferentes tipos creados exclusivamente en el fichero de
 *             "estructuras.h".
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_FICHEROS_H_
#define _PJ2_WESLEY_LUCAS_FICHEROS_H_

// Librerias generales del sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Librerias propias
#include "estructuras.h"

/***********************************************************************************************************************
 *
 * @Finalidad: Abrir un fichero de texto. Sobretodo comprueba que no haya un error de procesamiento de fichero.
 * @Parametros:     in/out: arg_fichero = puntero del fichero sobre el que queremos leer (modo 'r').
 * @Retorno: Devuelve el puntero libre de errores de procesamiento.
 *
 **********************************************************************************************************************/
FILE *aperturaFicheroTxt (char *arg_fichero);

/***********************************************************************************************************************
 *
 * @Finalidad: Abrir un fichero binario. Sobretodo comprueba que no haya un error de procesamiento de fichero.
 * @Parametros:     in/out: arg_fichero = puntero del fichero sobre el que queremos leer (modo 'rb').
 * @Retorno: Devuelve el puntero libre de errores de procesamiento.
 *
 **********************************************************************************************************************/
FILE *aperturaFicheroBin (char *arg_fichero);

/***********************************************************************************************************************
 *
 * @Finalidad: Comprobar si el fichero sobre el que se lee contiene informacion o no.
 * @Parametros:     in:     punt_fich = puntero del fichero sobre el que estamos analizando si esta lleno o no.
 *                  in/out: tamano = variable que devuelve el indicador de posicion en el que se encuentra el cursor.
 * @Retorno: Devuelve el valor del indicador de posicion en el que se encuentra el cursor. Si es 0, significa que esta
 *           vacio. En el caso contrario, es que contiene informacion, ergo, esta lleno.
 *
 **********************************************************************************************************************/
int compruebaEstadoFichero (FILE *punt_fich, int tamano);

/***********************************************************************************************************************
 *
 * @Finalidad: Leer el fichero de texto de piezas y almacenar toda la informacion que se encuentra dentro de este en un
 *             tipo creado especificamente para este, llamado 'InfoPieza'.
 * @Parametros:     in:     p = puntero del fichero sobre el que leemos y extraemos la informacion.
 *                  in:     num_piezas = variable en el que se guarda el numero de piezas total que hay en el fichero.
 *                  out:    pieza = devolvemos el tipo definido 'InfoPieza' con la informacion del fichero ya guardada.
 * @Retorno: Devuelve el tipo 'InfoPieza' lleno de informacion extraida del fichero de piezas.
 *
 **********************************************************************************************************************/
InfoPieza *guardadoInfoPiezas (FILE *p, int *num_piezas);

/***********************************************************************************************************************
 *
 * @Finalidad: Leer el fichero de texto de piezas y almacenar toda la informacion que se encuentra dentro de este en un
 *             tipo creado especificamente para este, llamado 'InfoGPs'.
 * @Parametros:     in:     gps = puntero del fichero sobre el que leemos y extraemos la informacion.
 *                  in:     num_premios = variable en el que se guarda el numero de premios total que hay en el fichero.
 *                  out:    gpese = devolvemos el tipo definido 'InfoGPs' con la informacion del fichero ya guardada.
 * @Retorno: Devuelve el tipo 'InfoGPs' lleno de informacion extraida del fichero de grandes premios.
 *
 **********************************************************************************************************************/
InfoGPs *guardadoInfoGPs (FILE *gps, int *num_premios);

/***********************************************************************************************************************
 *
 * @Finalidad: Leer el fichero de texto de corredores y almacenar toda la informacion que se encuentra dentro de este en
 *             un tipo creado especificamente para este, llamado 'InfoCorredor'.
 * @Parametros:     in:     c = puntero del fichero sobre el que leemos y extraemos la informacion.
 *                  in:     num_pilotos = variable en el que se guarda el numero de pilotos total que hay en el fichero.
 *                  out:    corredor = devolvemos el tipo definido 'InfoCorredor' con la informacion del fichero ya
 *                                     guardada.
 * @Retorno: Devuelve el tipo 'InfoCorredor' lleno de informacion extraida del fichero de corredores.
 *
 **********************************************************************************************************************/
InfoCorredor *guardadoInfoCorredores (FILE *c, int num_pilotos);

/***********************************************************************************************************************
 *
 * @Finalidad: Leer el fichero de texto de piezas y almacenar toda la informacion que se encuentra dentro de este en un
 *             tipo creado especificamente para este, llamado 'Pieza'.
 * @Parametros:     in:     stats = puntero del fichero sobre el que leemos y extraemos la informacion.
 *                  in:     num_coches = variable en el que se guarda el numero de coches total que hay en el fichero.
 *                  out:    stats = devolvemos el tipo definido 'InfoBase' con la informacion del fichero ya guardada.
 * @Retorno: Devuelve el tipo 'InfoBase' lleno de informacion extraida del fichero de estadisticas base.
 *
 **********************************************************************************************************************/
InfoBase *guardadoInfoBase (FILE *b, int num_coches);

/***********************************************************************************************************************
 *
 * @Finalidad: Cerrar el fichero sobre el que ya hemos operado previamente.
 * @Parametros:     in:     p = puntero del fichero sobre el que hemos operado de principio a fin de programa.
 * @Retorno: ----
 *
 **********************************************************************************************************************/
void cierreFichero (FILE *p);

#endif