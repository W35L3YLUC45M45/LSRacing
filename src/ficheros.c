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

// Librerias generales del sistema
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include del fichero .h del mismo módulo
#include "ficheros.h"

/***********************************************************************************************************************
 *
 * @Finalidad: Abrir un fichero de texto. Sobretodo comprueba que no haya un error de procesamiento de fichero.
 * @Parametros:     in/out: arg_fichero = puntero del fichero sobre el que queremos leer (modo 'r').
 * @Retorno: Devuelve el puntero libre de errores de procesamiento.
 *
 **********************************************************************************************************************/
FILE *aperturaFicheroTxt (char *arg_fichero) {
    FILE *punt_fich;
    punt_fich = fopen(arg_fichero, "r");
    if (punt_fich == NULL){
        printf("Error. Ha ocurrido un error durante el procesamiento de ficheros.");
    }

    return punt_fich;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Abrir un fichero binario. Sobretodo comprueba que no haya un error de procesamiento de fichero.
 * @Parametros:     in/out: arg_fichero = puntero del fichero sobre el que queremos leer (modo 'rb').
 * @Retorno: Devuelve el puntero libre de errores de procesamiento.
 *
 **********************************************************************************************************************/
FILE *aperturaFicheroBin (char *arg_fichero) {
    FILE *punt_fich;
    punt_fich = fopen(arg_fichero, "rb");
    if (punt_fich == NULL){
        printf("Error. Ha ocurrido un error durante el procesamiento de ficheros.");
    }

    return punt_fich;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Comprobar si el fichero sobre el que se lee contiene informacion o no.
 * @Parametros:     in:     punt_fich = puntero del fichero sobre el que estamos analizando si esta lleno o no.
 *                  in/out: tamano = variable que devuelve el indicador de posicion en el que se encuentra el cursor.
 * @Retorno: Devuelve el valor del indicador de posicion en el que se encuentra el cursor. Si es 0, significa que esta
 *           vacio. En el caso contrario, es que contiene informacion, ergo, esta lleno.
 *
 **********************************************************************************************************************/
int compruebaEstadoFichero (FILE *punt_fich, int tamano){
    fseek(punt_fich, 0, SEEK_END);
    tamano = ftell(punt_fich);
    if (tamano == 0){
        printf("Error. Hay un fichero vacio.");
    }

    return tamano;
}

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
InfoPieza *guardadoInfoPiezas (FILE *p, int *num_piezas){
    int i = 0, j = 0;
    char aux[35];
    InfoPieza *pieza;

    fseek(p, 0 ,SEEK_SET);
    fscanf(p, "%d", num_piezas);
    pieza = (InfoPieza *) malloc (*num_piezas * sizeof(InfoPieza));
    if (pieza == NULL) {
        printf("No tenemos reserva memoria.\n");
    } else {
        fgets(aux, 35, p);

        for (i = 0; i < *num_piezas; i++) {
            fgets(aux, 35, p);
            aux[strlen(aux) - 1] = '\0';
            strcpy(pieza[i].nom_compnt, aux);
            fscanf(p, "%d", &pieza[i].num_motores);
            pieza[i].motor = (InfoMotor *) malloc (pieza[i].num_motores * sizeof(InfoMotor));

            if (pieza[i].motor == NULL) {
                printf("No tenemos reserva memoria.\n");
            } else {
                fgets(aux, 35, p);

                for (j = 0; j < pieza[i].num_motores; j++) {
                    fgets(aux, 35, p);
                    aux[strlen(aux) - 1] = '\0';
                    strcpy(pieza[i].motor[j].compst, aux);
                    fgets(aux, 35, p);
                    aux[strlen(aux) - 1] = '\0';
                    strcpy(pieza[i].motor[j].vel, aux);
                    fgets(aux, 35, p);
                    aux[strlen(aux) - 1] = '\0';
                    strcpy(pieza[i].motor[j].acel, aux);
                    fgets(aux, 35, p);
                    aux[strlen(aux) - 1] = '\0';
                    strcpy(pieza[i].motor[j].cons, aux);
                    fgets(aux, 35, p);
                    aux[strlen(aux) - 1] = '\0';
                    strcpy(pieza[i].motor[j].fiab, aux);
                }
            }
        }
    }

    return pieza;
}

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
InfoGPs *guardadoInfoGPs (FILE *gps, int *num_premios){
    int i = 0;
    char aux[35];
    InfoGPs *gpese;

    fseek(gps, 0 ,SEEK_SET);
    fscanf(gps, "%d", num_premios);
    gpese = (InfoGPs *) malloc (*num_premios * sizeof(InfoGPs));
    if (gpese == NULL) {
        printf("No tenemos reserva memoria.\n");
    } else {
        fgets(aux, 35, gps);

        for (i = 0; i < *num_premios; i++){
            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_pos_calend, aux);
            gpese[i].i_pos_calend = atoi(gpese[i].c_pos_calend);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].nom_premio, aux);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_vel_adec, aux);
            gpese[i].i_vel_adec = atoi(gpese[i].c_vel_adec);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_acel_adec, aux);
            gpese[i].i_acel_adec = atoi(gpese[i].c_acel_adec);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_cons_adec, aux);
            gpese[i].i_cons_adec = atoi(gpese[i].c_cons_adec);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_fiab_adec, aux);
            gpese[i].i_fiab_adec = atoi(gpese[i].c_fiab_adec);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_t_base, aux);
            gpese[i].f_t_base = atof(gpese[i].c_t_base);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_t_pitstop, aux);
            gpese[i].i_t_pitstop = atoi(gpese[i].c_t_pitstop);

            fgets(aux, 35, gps);
            aux[strlen(aux) - 1] = '\0';
            strcpy(gpese[i].c_num_pitstop, aux);
            gpese[i].i_num_pitstop = atoi(gpese[i].c_num_pitstop);
        }
    }

    return gpese;
}

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
InfoCorredor *guardadoInfoCorredores (FILE *c, int num_pilotos){
    int i = 0;
    InfoCorredor *corredor;

    corredor = (InfoCorredor *) malloc (num_pilotos * sizeof(InfoCorredor));
    if (corredor == NULL) {
        printf("No tenemos reserva memoria.\n");
    }else{
        fseek(c, 0, SEEK_SET);

        for (i = 0; i < num_pilotos; i++) {
            fread(&corredor[i], sizeof(InfoCorredor), 1, c);
        }
    }

    return corredor;
}

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
InfoBase *guardadoInfoBase (FILE *b, int num_coches){
    int i = 0;
    InfoBase *stats;

    stats = (InfoBase *) malloc (num_coches * sizeof(InfoBase));
    if (stats == NULL) {
        printf("No tenemos reserva memoria.\n");
    }else {
        fseek(b, 0, SEEK_SET);

        for (i = 0; i < num_coches; i++) {
            fread(&stats[i], sizeof(InfoBase), 1, b);
        }
    }

    return stats;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Cerrar el fichero sobre el que ya hemos operado previamente.
 * @Parametros:     in:     p = puntero del fichero sobre el que hemos operado de principio a fin de programa.
 * @Retorno: ----
 *
 **********************************************************************************************************************/
void cierreFichero (FILE *punt_fich) {
    fclose(punt_fich);
}