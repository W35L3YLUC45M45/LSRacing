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

// Librerias generales del sistema
#include <string.h>

// Librerias propias
#include "LS_allegro.h"

// Include del fichero .h del mismo módulo
#include "opcion3.h"

// Funcion que se encarga de mostrar a nivel grafico las opciones de controles que se le ofrece al usuario.
void muestraControlesOpc3(){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 95, 750, 0, "%s", "ANTERIOR");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 320, 750, 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 350, 750, 0, "%s", "A");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 380, 750, 0, "%s", ")");

    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 690, 750, 0, "%s", "SIGUIENTE");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 930, 750, 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 960, 750, 0, "%s", "D");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 990, 750, 0, "%s", ")");
}

// Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos inferiores del ranking.
void displayRestInfo (int i){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 95, 125 + (75 * i), 0, "%d", i + 1);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 120, 125 + (75 * i), 0, "%s", ".");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 520, 125 + (75 * i), 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 670, 125 + (75 * i), 0, "%s", "SEG.");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 745, 125 + (75 * i), 0, "%s", ")");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 780, 125 + (75 * i), 0, "%s", "-");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 870, 125 + (75 * i), 0, "%s", "PUNTOS");
}

// Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
void displayThirdWinnerInfo (int i){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 95, 125 + (75 * i), 0, "%d", i + 1);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 120, 125 + (75 * i), 0, "%s", ".");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 520, 125 + (75 * i), 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 670, 125 + (75 * i), 0, "%s", "SEG.");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 745, 125 + (75 * i), 0, "%s", ")");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 780, 125 + (75 * i), 0, "%s", "-");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 870, 125 + (75 * i), 0, "%s", "PUNTOS");
}

// Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
void displaySecondWinnerInfo (int i){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 95, 125 + (75 * i), 0, "%d", i + 1);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 120, 125 + (75 * i), 0, "%s", ".");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 520, 125 + (75 * i), 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 670, 125 + (75 * i), 0, "%s", "SEG.");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 745, 125 + (75 * i), 0, "%s", ")");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 780, 125 + (75 * i), 0, "%s", "-");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 870, 125 + (75 * i), 0, "%s", "PUNTOS");
}

// Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
void displayFirstWinnerInfo (int i){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 95, 125 + (75 * i), 0, "%d", i + 1);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 120, 125 + (75 * i), 0, "%s", ".");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 520, 125 + (75 * i), 0, "%s", "(");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 670, 125 + (75 * i), 0, "%s", "SEG.");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 745, 125 + (75 * i), 0, "%s", ")");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 780, 125 + (75 * i), 0, "%s", "-");
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 870, 125 + (75 * i), 0, "%s", "PUNTOS");
}

// Funcion que se encarga de mostrar el resto de informacion como caracteres, posicion de ranking, palabras sueltas,
// etc...
void displayRemainingInfo (int i){
    // Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
    if (i == 0){
        displayFirstWinnerInfo(i);
    }else{

        // Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
        if (i == 1){
            displaySecondWinnerInfo(i);
        }else{

            // Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
            if (i == 2){
                displayThirdWinnerInfo(i);
            }else{

                // Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos inferiores del ranking.
                displayRestInfo(i);
            }
        }
    }
}

// Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos inferiores del ranking.
void displayConRest (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_con_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_con_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_con);
}

// Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
void displayConThirdWinner (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_con_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_con_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_con);
}

// Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
void displayConSecondWinner (OpcionDos *opc_2, int i, int k) {
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_con_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_con_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_con);
}

// Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
void displayConFirstWinner (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_con_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_con_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_con);
}

// Funcion que se encarga de mostrar el posicionamiento del ranking de los tres primeros corredores en base a que
// nuestro piloto si ha utilizado pit stops.
void ConRanking (OpcionDos *opc_2, OpcionTres *opc_3, int i, int k){
    // Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
    if (i == 0){
        displayConFirstWinner(opc_2, i, k);
    }else{

        // Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
        if (i == 1){
            displayConSecondWinner (opc_2, i, k);
        }else{

            // Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
            if (i == 2){
                displayConThirdWinner (opc_2, i, k);
            }else{

                // Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos
                // inferiores del ranking.
                displayConRest(opc_2, i, k);
            }
        }
    }
    strcpy(opc_3[k].rank_def[i].nombre, opc_2[k].ranking[i].nom_con_corredor);
    opc_3[k].rank_def[i].posicion = i + 1;
    opc_3[k].rank_def[i].tiempo = opc_2[k].ranking[i].pos_con_pit;
    opc_3[k].rank_def[i].puntos = opc_2[k].ranking[i].puntuacion_con;
}

// Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos inferiores del ranking.
void displaySinRest (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_sin_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_sin_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_sin);
}

// Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
void displaySinThirdWinner (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_sin_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_sin_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_sin);
}

// Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
void displaySinSecondWinner (OpcionDos *opc_2, int i, int k) {
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_sin_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_sin_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_sin);
}

// Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
void displaySinFirstWinner (OpcionDos *opc_2, int i, int k){
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 135, 125 + (75 * i), 0, "%s", opc_2[k].ranking[i].nom_sin_corredor);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 550, 125 + (75 * i), 0, "%.1f", opc_2[k].ranking[i].pos_sin_pit);
    al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 810, 125 + (75 * i), 0, "%d", opc_2[k].ranking[i].puntuacion_sin);
}

// Funcion que se encarga de mostrar el posicionamiento del ranking de los tres primeros corredores en base a que
// nuestro piloto no ha utilizado pit stops.
void SinRanking (OpcionDos *opc_2, OpcionTres *opc_3, int i, int k){
    if (i == 0){
        // Muestra en color rojo la informacion del corredor que se ha posicionado primero en el ranking.
        displaySinFirstWinner(opc_2, i, k);
    }else{
        // Muestra en color verde la informacion del corredor que se ha posicionado segundo en el ranking.
        if (i == 1){
            displaySinSecondWinner (opc_2, i, k);
        }else{
            // Muestra en color azul la informacion del corredor que se ha posicionado tercero en el ranking.
            if (i == 2){
                displaySinThirdWinner (opc_2, i, k);
            }else{
                // Muestra en color gris la informacion del resto de corredores que se ha posicionado en puestos
                // inferiores del ranking.
                displaySinRest(opc_2, i, k);
            }
        }
    }
    strcpy(opc_3[k].rank_def[i].nombre, opc_2[k].ranking[i].nom_sin_corredor);
    opc_3[k].rank_def[i].posicion = i + 1;
    opc_3[k].rank_def[i].tiempo = opc_2[k].ranking[i].pos_sin_pit;
    opc_3[k].rank_def[i].puntos = opc_2[k].ranking[i].puntuacion_sin;
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de 'D' (siguiente):
void inputNext (int *k, int opc2_in){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_D)){
        if (*k == opc2_in - 1){

        }else {
            (*k)++;
        }
    }
}

// Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton 'A' (anterior).
void inputPrevious (int *k){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_A)){
        if (*k == 0){

        }else {
            (*k)--;
        }
    }
}

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
OpcionTres *displayOpc3Results (OpcionTres *opc_3, OpcionDos *opc_2, int j, int num_pilotos, int opc2_in){
    int nSortir = 0, i = 0, k = 0;

    for (k = 0; k < j; k++){
        strcpy(opc_3[k].nombre_gp, opc_2[k].nom_gp);
    }

    k = 0;
    k = j - 1;

    LS_allegro_init(1100, 810,"Clasificacion GP/Temporada");
    while (!nSortir) {

        if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
            nSortir = 1;
        }

        // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton 'A' (anterior).
        inputPrevious (&k);

        // Funcion que se encarga de llevar a cabo el funcionamiento de la logica al presionar el boton de 'D' (siguiente):
        inputNext (&k, opc2_in);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),230, 50, 0, "%s","CLASIFICACION DE");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),615, 50, 0, "%s",opc_2[k].nom_gp);

        for (i = 0; i < num_pilotos + 1; i++) {

            if (opc_2[k].check == 1) {
                // Funcion que se encarga de mostrar el posicionamiento del ranking de los tres primeros corredores en
                // base a que nuestro piloto no ha utilizado pit stops.
                SinRanking (opc_2, opc_3, i, k);
            } else {
                // Funcion que se encarga de mostrar el posicionamiento del ranking de los tres primeros corredores en
                // base a que nuestro piloto si ha utilizado pit stops.
                ConRanking (opc_2, opc_3, i, k);
            }
            // Funcion que se encarga de mostrar el resto de informacion como caracteres, posicion de ranking, palabras
            // sueltas, etc...
            displayRemainingInfo (i);

            // Funcion que se encarga de mostrar a nivel grafico las opciones de controles que se le ofrece al usuario.
            muestraControlesOpc3();
        }

        LS_allegro_clear_and_paint(BLACK);
    }

    LS_allegro_exit();

    return opc_3;
}

/***********************************************************************************************************************
 *
 * @Finalidad: Llenar el tipo propio 'DatosTotal' de la informacion esencial a mostrar luego en los resultados finales
 *             del ranking de la temporada finalizada.
 * @Parametros:     in/out: suma_p =
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
DatosTotal *sortPoints (DatosTotal *suma_p, OpcionTres *opc_3, OpcionUno opc_1, InfoCorredor *corredor, int *j, int num_pilotos, int num_premios){
    int l = 0, k = 0, m = 0, comp_nom = 0, i_aux = 0, i2_aux = 0, i3_aux = 0;
    char c_aux[35];

    suma_p[0].puntuacion = 0;;

    strcpy(suma_p[0].nombre, opc_1.nombre);
    suma_p[0].posicion = 1;
    suma_p[0].dorsal = opc_1.i_dorsal;
    for (l = 0; l < num_premios; l++) {

        for (k = 0; k < num_pilotos + 1; k++) {
            comp_nom = strcmp(opc_3[l].rank_def[k].nombre, suma_p[0].nombre);

            if (comp_nom == 0) {
                suma_p[0].puntuacion = suma_p[0].puntuacion + opc_3[l].rank_def[k].puntos;
            }
        }
    }
    for (k = 0; k < num_pilotos; k++) {
        strcpy(suma_p[k + 1].nombre, corredor[k].nom);
        suma_p[k + 1].posicion = (k + 1) + 1;
        suma_p[k + 1].dorsal = corredor[k].dors;

        for (l = 0; l < num_premios; l++) {

            for (m = 0; m < num_pilotos + 1; m++) {
                comp_nom = strcmp(opc_3[l].rank_def[m].nombre, suma_p[k + 1].nombre);

                if (comp_nom == 0) {
                    suma_p[k + 1].puntuacion = suma_p[k + 1].puntuacion + opc_3[l].rank_def[m].puntos;
                }
            }
        }
    }

    // Ordena el ranking de final de temporada en base al numero de puntos acumulados por cada corredor.
    for (l = 0; l < num_pilotos + 1; l++){

        for (k = l + 1; k < num_pilotos + 1; k++){

            if (suma_p[l].puntuacion < suma_p[k].puntuacion){
                i_aux = suma_p[l].puntuacion;
                strcpy(c_aux, suma_p[l].nombre);
                i2_aux = suma_p[l].posicion;
                i3_aux = suma_p[l].dorsal;

                suma_p[l].puntuacion = suma_p[k].puntuacion;
                strcpy(suma_p[l].nombre, suma_p[k].nombre);
                suma_p[l].posicion = suma_p[k].posicion;
                suma_p[l].dorsal = suma_p[k].dorsal;

                suma_p[k].puntuacion = i_aux;
                strcpy(suma_p[k].nombre, c_aux);
                suma_p[k].posicion = i2_aux;
                suma_p[k].dorsal = i3_aux;
            }
        }
        suma_p[l].posicion = l + 1;
    }
    (*j)++;

    return suma_p;
}

// Funcion que muestra la informacion del resto de corredores que ha llegado mas tarde en el ranking.
void displayRest(DatosTotal *suma_p, int i){
    if (i > 2){
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 160, 175 + (75 * i),0, "%d", suma_p[i].posicion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 185, 175 + (75 * i), 0, "%s", ".");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 200, 175 + (75 * i), 0, "%s", suma_p[i].nombre);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 585, 175 + (75 * i), 0, "%s", "(");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 600, 175 + (75 * i), 0, "%s", "#");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 625, 175 + (75 * i), 0, "%d", suma_p[i].dorsal);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 675, 175 + (75 * i), 0, "%s", ")");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 704, 175 + (75 * i), 0, "%s", "-");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 735, 175 + (75 * i), 0, "%d", suma_p[i].puntuacion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_GRAY), 795, 175 + (75 * i), 0, "%s", "PUNTOS");
    }
}

// Funcion que muestra la informacion del corredor que ha llegado tercero en el ranking.
void displayThirdWinner (DatosTotal *suma_p, int i){
    if (i == 2){
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 160, 175 + (75 * i),0, "%d", suma_p[i].posicion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 185, 175 + (75 * i), 0, "%s", ".");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 200, 175 + (75 * i), 0, "%s", suma_p[i].nombre);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 585, 175 + (75 * i), 0, "%s", "(");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 600, 175 + (75 * i), 0, "%s", "#");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 625, 175 + (75 * i), 0, "%d", suma_p[i].dorsal);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 675, 175 + (75 * i), 0, "%s", ")");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 704, 175 + (75 * i), 0, "%s", "-");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 735, 175 + (75 * i), 0, "%d", suma_p[i].puntuacion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(LIGHT_BLUE), 795, 175 + (75 * i), 0, "%s", "PUNTOS");
    }
}

// Funcion que muestra la informacion del corredor que ha llegado segundo en el ranking.
void displaySecondWinner (DatosTotal *suma_p, int i){
    if (i == 1){
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 160, 175 + (75 * i),0, "%d", suma_p[i].posicion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 185, 175 + (75 * i), 0, "%s", ".");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 200, 175 + (75 * i), 0, "%s", suma_p[i].nombre);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 585, 175 + (75 * i), 0, "%s", "(");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 600, 175 + (75 * i), 0, "%s", "#");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 625, 175 + (75 * i), 0, "%d", suma_p[i].dorsal);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 675, 175 + (75 * i), 0, "%s", ")");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 704, 175 + (75 * i), 0, "%s", "-");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 735, 175 + (75 * i), 0, "%d", suma_p[i].puntuacion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(GREEN), 795, 175 + (75 * i), 0, "%s", "PUNTOS");
    }
}

// Funcion que muestra la informacion del corredor que ha llegado primero en el ranking.
void displayFirstWinner (DatosTotal *suma_p, int i){
    if (i == 0){
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 160, 175 + (75 * i), 0, "%d", suma_p[i].posicion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 185, 175 + (75 * i), 0, "%s", ".");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 200, 175 + (75 * i), 0, "%s", suma_p[i].nombre);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 585, 175 + (75 * i), 0, "%s", "(");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 600, 175 + (75 * i), 0, "%s", "#");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 625, 175 + (75 * i), 0, "%d", suma_p[i].dorsal);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 675, 175 + (75 * i), 0, "%s", ")");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 704, 175 + (75 * i), 0, "%s", "-");
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 735, 175 + (75 * i), 0, "%d", suma_p[i].puntuacion);
        al_draw_textf(LS_allegro_get_font(LARGE), LS_allegro_get_color(RED), 795, 175 + (75 * i), 0, "%s", "PUNTOS");
    }
}

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
void displayPointsRanking (DatosTotal *suma_p, int j, int num_pilotos){
    int nSortir = 0, i = 0;

    if (j == 5){
        LS_allegro_init(1100, 810,"Clasificacion GP/Temporada");

        while (!nSortir) {

            if (LS_allegro_key_pressed(ALLEGRO_KEY_ESCAPE)) {
                nSortir = 1;
            }

            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),160, 100, 0, "%s","CLASIFICACION DE FINAL DE TEMPORADA");

            for (i = 0; i < num_pilotos + 1; i++){
                // Funcion que muestra la informacion del corredor que ha llegado primero en el ranking.
                displayFirstWinner(suma_p, i);

                // Funcion que muestra la informacion del corredor que ha llegado segundo en el ranking.
                displaySecondWinner(suma_p, i);

                // Funcion que muestra la informacion del corredor que ha llegado tercero en el ranking.
                displayThirdWinner(suma_p, i);

                // Funcion que muestra la informacion del resto de corredores que ha llegado mas tarde en el ranking.
                displayRest(suma_p, i);
            }
            LS_allegro_clear_and_paint(BLACK);
        }
    }
    LS_allegro_exit();
}