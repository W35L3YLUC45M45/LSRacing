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

// Librerias generales del sistema
#include <stdio.h>
#include <string.h>

// Librerias propias
#include "LS_allegro.h"

// Include del fichero .h del mismo módulo
#include "opcion1.h"

// Funcion que se encarga de mostrar el panel de configuracion inferior, donde se muestra los motores seleccionados para
// cada pieza.
void muestraPanelConfInf (InfoPieza *pieza, int num_piezas){
    int k = 0, l = 0;

    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE), 1100,500, 0, "%s", "CONFIGURACION ACTUAL");

    for (k = 0; k < num_piezas; k++){
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1100,550 + (30 * k), 0, "%s",pieza[k].nom_compnt);
        al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1325,550 + (30 * k), 0, "%s", pieza[k].motor[pieza[k].sel_piez].compst);
    }

    LS_allegro_clear_and_paint(BLACK);
}

// Funcion que se encarga de mostrar los controles los cuales el usuario puede hacer servir durante la seleccion de la
// pieza/motor de preferencia.
void muestraControlesOpc1 (ALLEGRO_BITMAP *z){
    // Left arrow
    al_draw_filled_rectangle(1185, 212, 1215, 262, LS_allegro_get_color(WHITE));
    al_draw_filled_triangle(1135, 237, 1185, 187, 1185, 287, LS_allegro_get_color(WHITE));

    // Right arrow
    al_draw_filled_rectangle(1395, 212, 1425, 262, LS_allegro_get_color(WHITE));
    al_draw_filled_triangle(1475, 237, 1425, 187, 1425, 287, LS_allegro_get_color(WHITE));

    // Up arrow
    al_draw_filled_rectangle(1275, 135, 1325, 165, LS_allegro_get_color(WHITE));
    al_draw_filled_triangle(1300, 85, 1250, 135, 1350, 135, LS_allegro_get_color(WHITE));

    // Down arrow
    al_draw_filled_rectangle(1275, 320, 1325, 350, LS_allegro_get_color(WHITE));
    al_draw_filled_triangle(1300, 400, 1250, 350, 1350, 350, LS_allegro_get_color(WHITE));

    al_draw_scaled_bitmap(z, 0, 0, 300, 250, 1250, 200, 100, 83, 0);
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de izquierda.
void inputLeft (InfoPieza *pieza, int *i){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_LEFT)){

        if (pieza[*i].sel_piez == 0){
            pieza[*i].sel_piez = pieza[*i].num_motores - 1;
        }else{
            pieza[*i].sel_piez--;
        }
    }
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de derecha.
void inputRight (InfoPieza *pieza, int *i){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_RIGHT)){

        if (pieza[*i].sel_piez == pieza[*i].num_motores - 1){
            pieza[*i].sel_piez = 0;
        }else{
            pieza[*i].sel_piez++;
        }
    }
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de arriba.
void inputUp (InfoPieza *pieza, int *i, int num_piezas){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_UP)){

        if (*i == 0){
            *i = num_piezas - 1;
        }else{
            (*i)--;
        }

        if (pieza[*i].aviso_piez == 0){
            pieza[*i].sel_piez = 0;
            pieza[*i].aviso_piez = 1;
        }
    }
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de abajo.
void inputDown (InfoPieza *pieza, int *i, int num_piezas){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_DOWN)){
        if (*i == num_piezas - 1){
            *i = 0;
        }else{
            (*i)++;
        }

        if (pieza[*i].aviso_piez == 0){
            pieza[*i].sel_piez = 0;
            pieza[*i].aviso_piez = 1;
        }
    }
}

// Funcion que se encarga de mostrar el panel de configuracion superior durante la seleccion de la pieza/motor.
void muestraPanelConfSup (InfoPieza *pieza, int *i){
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE), 1330, 25,0, "%s", pieza[*i].nom_compnt);
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1510,125, 0, "%s", "COMPUESTO");
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1660,125, 0, "%s",pieza[*i].motor[pieza[*i].sel_piez].compst);
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1510,175, 0, "%s", "VELOCIDAD");
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1660,175, 0, "%s", pieza[*i].motor[pieza[*i].sel_piez].vel);
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1510,225, 0, "%s", "ACELERACION");
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1660,225, 0, "%s", pieza[*i].motor[pieza[*i].sel_piez].acel);
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1510,275, 0, "%s", "CONSUMO");
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1660,275, 0, "%s", pieza[*i].motor[pieza[*i].sel_piez].cons);
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1510,325, 0, "%s", "FIABILIDAD");
    al_draw_textf(LS_allegro_get_font(NORMAL),LS_allegro_get_color(WHITE), 1660,325, 0, "%s", pieza[*i].motor[pieza[*i].sel_piez].fiab);
}

// Funcion que se encarga de mostrar la imagen del coche en el garaje durante la seleccion de la pieza/motor.
void muestraGaraje (ALLEGRO_BITMAP *a){
    al_draw_bitmap(a, 0, 0, 0);
}

// Funcion que se encarga de cargar en la pantalla no solo las imagenes en formato png de la pantalla del configurador
// del coche, sino tambien englobar toda la funcionalidad de la seleccion de piezas/motores.
void muestraConfigurador (InfoPieza *pieza, int num_piezas, int *opc1_in){
    int nSortir = 0;
    int i = 0, j = 0;
    ALLEGRO_BITMAP *a, *z;

    LS_allegro_init(1800, 810, "Configurador de coche");
    a = al_load_bitmap("boxes.png");
    z = al_load_bitmap("neumaticos.png");

    // Inicializacion de variables a 0 para evitar cualquier problema mas adelante.
    for (i = 0; i < num_piezas; i++){

        for (j = 0; j < pieza[i].num_motores; j++){
            pieza[i].motor[j].sel_mot = 0;
            pieza[i].aviso_piez = 0;
            pieza[i].sel_piez = 0;
            pieza[i].motor[j].aviso_mot = 0;
        }
    }

    i = 0;
    j = 0;

    while (!nSortir) {

        // Si el usuario presiona la tecla 'ESC' mientras el programa arranca, este parara la ejecucion y guarda toda
        // la configuracion guardad de la pieza/motor seleccionado.
        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
            nSortir = 1;
            *opc1_in = 1;
        }else{
            pieza[0].aviso_piez = 1;

            // Funcion que se encarga de mostrar la imagen del coche en el garaje durante la seleccion de la pieza/motor.
            muestraGaraje (a);

            // Funcion que se encarga de mostrar el panel de configuracion superior durante la seleccion de la pieza/motor.
            muestraPanelConfSup (pieza, &i);

            // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de abajo.
            inputDown (pieza, &i, num_piezas);

            // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de arriba.
            inputUp (pieza, &i, num_piezas);

            // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de derecha.
            inputRight (pieza, &i);

            // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de izquierda.
            inputLeft (pieza, &i);

            // Funcion que se encarga de mostrar los controles los cuales el usuario puede hacer servir durante la
            // seleccion de la pieza/motor de preferencia.
            muestraControlesOpc1 (z);

            // Funcion que se encarga de mostrar el panel de configuracion inferior, donde se muestra los motores
            // seleccionados para cada pieza.
            muestraPanelConfInf (pieza, num_piezas);
        }
    }
    LS_allegro_exit();
}

// Funcion que se encarga de guardar la gestion de neumaticos del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerGestNeum (OpcionUno opc_1){
    int i = 0;
    opc_1.i_gest_neum = -1;

    while (((opc_1.i_gest_neum < 0) || (opc_1.i_gest_neum > 10)) || ((opc_1.len_gest_neum > 2) || (opc_1.len_gest_neum < 1))) {
        opc_1.i_gest_neum = 0;

        printf("Gestion de neumaticos?");
        fgets(opc_1.aux_c_gest_neum, 100, stdin);
        opc_1.aux_c_gest_neum[strlen(opc_1.aux_c_gest_neum) - 1] = '\0';
        opc_1.len_gest_neum = strlen(opc_1.aux_c_gest_neum);
        for (i = 0; opc_1.aux_c_gest_neum[i] != '\0'; i++){
            opc_1.i_gest_neum = (opc_1.i_gest_neum * 10) + (opc_1.aux_c_gest_neum[i] - '0');
        }

        if ((opc_1.len_gest_neum > 2) || (opc_1.len_gest_neum < 1)) {
            printf("\nError, la gestion de neumaticos tiene que ser un entero entre 0 y 10, incluidos\n");
        } else {

            if ((opc_1.i_gest_neum < 0) || (opc_1.i_gest_neum > 10)) {
                printf("\nError, la gestion de neumaticos tiene que ser un entero entre 0 y 10, incluidos\n");
            } else {
                strcpy(opc_1.c_gest_neum, opc_1.aux_c_gest_neum);
            }
        }
    }

    return opc_1;
}

// Funcion que se encarga de guardar el temperamento del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerTemp (OpcionUno opc_1){
    int i = 0;
    opc_1.i_temp = -1;

    while (((opc_1.i_temp < 0) || (opc_1.i_temp > 10)) || ((opc_1.len_temp > 2) || (opc_1.len_temp < 1))) {
        opc_1.i_temp = 0;

        printf("Temperamento?");
        fgets(opc_1.aux_c_temp, 100, stdin);
        opc_1.aux_c_temp[strlen(opc_1.aux_c_temp) - 1] = '\0';
        opc_1.len_temp = strlen(opc_1.aux_c_temp);

        for (i = 0; opc_1.aux_c_temp[i] != '\0'; i++){
            opc_1.i_temp = (opc_1.i_temp * 10) + (opc_1.aux_c_temp[i] - '0');
        }

        if ((opc_1.len_temp > 2) || (opc_1.len_temp < 1)) {
            printf("\nError, el temperamento tiene que ser un entero entre 0 y 10, incluidos\n");
        } else {

            if ((opc_1.i_temp < 0) || (opc_1.i_temp > 10)) {
                printf("\nError, el temperamento tiene que ser un entero entre 0 y 10, incluidos\n");
            } else {
                strcpy(opc_1.c_temp, opc_1.aux_c_temp);
            }
        }
    }
    return opc_1;
}

// Funcion que se encarga de guardar la condicion fisica del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerCondFis (OpcionUno opc_1){
    int i = 0;
    opc_1.i_cond_fis = -1;

    while (((opc_1.i_cond_fis < 0) || (opc_1.i_cond_fis > 10)) || ((opc_1.len_cond_fis > 2) || (opc_1.len_cond_fis < 1))) {
        opc_1.i_cond_fis = 0;

        printf("Condicion fisica?");
        fgets(opc_1.aux_c_cond_fis, 100, stdin);
        opc_1.aux_c_cond_fis[strlen(opc_1.aux_c_cond_fis) - 1] = '\0';
        opc_1.len_cond_fis = strlen(opc_1.aux_c_cond_fis);

        for (i = 0; opc_1.aux_c_cond_fis[i] != '\0'; i++){
            opc_1.i_cond_fis = (opc_1.i_cond_fis * 10) + (opc_1.aux_c_cond_fis[i] - '0');
        }

        if ((opc_1.len_cond_fis > 2) || (opc_1.len_cond_fis < 1)) {
            printf("\nError, la condicion fisica tiene que ser un entero entre 0 y 10, incluidos\n");
        } else {

            if ((opc_1.i_cond_fis < 0) || (opc_1.i_cond_fis > 10)) {
                printf("\nError, la condicion fisica tiene que ser un entero entre 0 y 10, incluidos\n");
            } else {
                strcpy(opc_1.c_cond_fis, opc_1.aux_c_cond_fis);
            }
        }
    }

    return opc_1;
}

// Funcion que se encarga de guardar los reflejos del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerReflejos (OpcionUno opc_1){
    int i = 0;
    opc_1.i_reflej = -1;

    while (((opc_1.i_reflej < 0) || (opc_1.i_reflej > 10)) || ((opc_1.len_reflej > 2) || (opc_1.len_reflej < 1))) {
        opc_1.i_reflej = 0;

        printf("Reflejos?");
        fgets(opc_1.aux_c_reflej, 100, stdin);
        opc_1.aux_c_reflej[strlen(opc_1.aux_c_reflej) - 1] = '\0';
        opc_1.len_reflej = strlen(opc_1.aux_c_reflej);

        for (i = 0; opc_1.aux_c_reflej[i] != '\0'; i++){
            opc_1.i_reflej = (opc_1.i_reflej * 10) + (opc_1.aux_c_reflej[i] - '0');
        }

        if ((opc_1.len_reflej > 2) || (opc_1.len_reflej < 1)) {
            printf("\nError, los reflejos tiene que ser un entero entre 0 y 10, incluidos\n");
        } else {

            if ((opc_1.i_reflej < 0) || (opc_1.i_reflej > 10)) {
                printf("\nError, los reflejos tiene que ser un entero entre 0 y 10, incluidos\n");
            } else {
                strcpy(opc_1.c_reflej, opc_1.aux_c_reflej);
            }
        }
    }

    return opc_1;
}

// Funcion que se encarga de guardar el numero de dorsal del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerNumDorsal (OpcionUno opc_1){
    int i = 0;
    opc_1.i_dorsal = 0;

    while (((opc_1.i_dorsal < 1) || (opc_1.i_dorsal > 99)) || ((opc_1.len_dorsal > 2) || (opc_1.len_dorsal < 1))) {
        opc_1.i_dorsal = 0;

        printf("Dorsal?");
        fgets(opc_1.aux_c_dorsal, 100, stdin);
        opc_1.aux_c_dorsal[strlen(opc_1.aux_c_dorsal) - 1] = '\0';
        opc_1.len_dorsal = strlen(opc_1.aux_c_dorsal);

        for (i = 0; opc_1.aux_c_dorsal[i] != '\0'; i++){
            opc_1.i_dorsal = (opc_1.i_dorsal * 10) + (opc_1.aux_c_dorsal[i] - '0');
        }

        if ((opc_1.len_dorsal > 2) || (opc_1.len_dorsal < 1)) {
            printf("\nError, el dorsal tiene que ser un entero entre 1 y 99\n");
        } else {

            if ((opc_1.i_dorsal < 1) || (opc_1.i_dorsal > 99)) {
                printf("\nError, el dorsal tiene que ser un entero entre 1 y 99\n");
            } else {
                strcpy(opc_1.c_dorsal, opc_1.aux_c_dorsal);
            }
        }
    }

    return opc_1;
}

// Funcion que se encarga de guardar el nombre de escuderia dentro del tipo 'OpcionUno'.
OpcionUno extraerNomEscuderia (OpcionUno opc_1){
    opc_1.len_escuderia = 26;

    while ((opc_1.len_escuderia > 25) ||(opc_1.len_escuderia == 0)) {
        printf("Nombre de la escuderia?");
        fgets(opc_1.aux_escuderia, 100, stdin);
        opc_1.aux_escuderia[strlen(opc_1.aux_escuderia) - 1] = '\0';
        opc_1.len_escuderia = strlen(opc_1.aux_escuderia);

        if ((opc_1.len_escuderia > 25) || (opc_1.len_escuderia == 0)) {
            printf("\nError, el nombre de escuderia no puede superar los 25 caracteres.\n");
        } else {
            strcpy(opc_1.escuderia, opc_1.aux_escuderia);
        }
    }

    return opc_1;
}

// Funcion que se encarga de guardar el nombre del piloto dentro del tipo 'OpcionUno'.
OpcionUno extraerNomPiloto (OpcionUno opc_1){
    opc_1.len_nombre = 26;

    while ((opc_1.len_nombre > 25) ||(opc_1.len_nombre == 0)) {
        printf("\nNombre del piloto?");
        fgets(opc_1.aux_nombre, 100, stdin);
        opc_1.aux_nombre[strlen(opc_1.aux_nombre) - 1] = '\0';
        opc_1.len_nombre = strlen(opc_1.aux_nombre);

        if ((opc_1.len_nombre > 25) ||(opc_1.len_nombre == 0)) {
            printf("\nError, el nombre del piloto no puede superar los 25 caracteres.\n");
        } else {
            strcpy(opc_1.nombre, opc_1.aux_nombre);
        }
    }

    return opc_1;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Llenar las variables del tipo propio 'OpcionUno', ademas de reproducir la ventana grafica de seleccion
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
OpcionUno getOpc1Info (OpcionUno opc_1, InfoPieza *pieza, int num_piezas, int *opc1_in){
    if (opc_1.acceso == 0){
        // Funcion que se encarga de guardar el nombre del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerNomPiloto(opc_1);

        // Funcion que se encarga de guardar el nombre de escuderia dentro del tipo 'OpcionUno'.
        opc_1 = extraerNomEscuderia(opc_1);

        // Funcion que se encarga de guardar el numero de dorsal del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerNumDorsal(opc_1);

        // Funcion que se encarga de guardar los reflejos del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerReflejos(opc_1);

        // Funcion que se encarga de guardar la condicion fisica del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerCondFis(opc_1);

        // Funcion que se encarga de guardar el temperamento del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerTemp(opc_1);

        // Funcion que se encarga de guardar la gestion de neumaticos del piloto dentro del tipo 'OpcionUno'.
        opc_1 = extraerGestNeum(opc_1);
        printf("\nCargando configurador ...\n\n");
        opc_1.acceso = 1;
    }else{

        // Funcion que se encarga de cargar en la pantalla no solo las imagenes en formato png de la pantalla del
        // configurador del coche, sino tambien englobar toda la funcionalidad de la seleccion de piezas/motores.
        muestraConfigurador (pieza, num_piezas, opc1_in);
    }

    return opc_1;
}
