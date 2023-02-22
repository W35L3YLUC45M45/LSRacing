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

#include <string.h>
#include <stdlib.h>

// Librerías específicas de sistema
#include <time.h>

// Librerias propias
#include "LS_allegro.h"

// Include del fichero .h del mismo módulo
#include "opcion2.h"

// Muestra el resultado final en el que nuestro piloto ha quedado de la carrera.
void muestraResultadoPiloto(OpcionDos *opc_2, GPese node_opc2, int j){
    int nSortir = 0;

    while (!nSortir) {

        if (LS_allegro_key_pressed(ALLEGRO_KEY_ENTER)) {
            nSortir = 1;
        }

        if (opc_2[j].count_n_pitstop != (opc_2[j].pit_stop/node_opc2.i_t_pitstop)){
            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),470, 275, 0, "%s", opc_2[j].ranking[opc_2[j].sin].nom_sin_corredor);
        }else{
            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),470, 275, 0, "%s", opc_2[j].ranking[opc_2[j].con].nom_con_corredor);
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),400, 355, 0, "%s","HA FINALIZADO");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),335, 425, 0, "%s","EN LA POSICION Nº");

        if (opc_2[j].count_n_pitstop != (opc_2[j].pit_stop/node_opc2.i_t_pitstop)){
            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 425, 0, "%d", opc_2[j].sin + 1);
        }else{
            al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 425, 0, "%d", opc_2[j].con + 1);
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),200, 600, 0, "%s","PULSA 'ENTER' PARA VOLVER AL MENU");
        LS_allegro_clear_and_paint(BLACK);
    }
    LS_allegro_exit();
}

// Funcion que se encarga de ordenar a los corredores y el piloto en el ranking segun el tiempo que han tardado en
// completar la carrera. En mi caso, se contempla dos tipos de rankings, una donde se realizarn todos los pit stops y la
// otra donde no se realizan. Mas adelante, se guarda en un tipo de ranking definitivo esa informacion para asi no tener
// que depender de dos tipos distintos.
OpcionDos *sortRanked(OpcionDos *opc_2, int i, int *j, int k, int num_pilotos, float temp, float sort_t, char aux_name[35]){
    for (i = 0; i < num_pilotos + 1; i++){

        for (k = i + 1; k < num_pilotos + 1; k++){

            if (opc_2[*j].ranking[i].pos_sin_pit > opc_2[*j].ranking[k].pos_sin_pit){
                temp = opc_2[*j].ranking[i].pos_sin_pit;
                strcpy(aux_name, opc_2[*j].ranking[i].nom_sin_corredor);
                sort_t = opc_2[*j].ranking[i].t_sin_pit;

                opc_2[*j].ranking[i].pos_sin_pit = opc_2[*j].ranking[k].pos_sin_pit;
                strcpy(opc_2[*j].ranking[i].nom_sin_corredor, opc_2[*j].ranking[k].nom_sin_corredor);
                opc_2[*j].ranking[i].t_sin_pit = opc_2[*j].ranking[k].t_sin_pit;

                opc_2[*j].ranking[k].pos_sin_pit = temp;
                strcpy(opc_2[*j].ranking[k].nom_sin_corredor, aux_name);
                opc_2[*j].ranking[k].t_sin_pit = sort_t;
            }
        }
        opc_2[*j].ranking[i].puntuacion_sin = opc_2[*j].puntos[i];
    }

    for (i = 0; i < num_pilotos + 1; i++){

        for (k = i + 1; k < num_pilotos + 1; k++){

            if (opc_2[*j].ranking[i].pos_con_pit > opc_2[*j].ranking[k].pos_con_pit){
                temp = opc_2[*j].ranking[i].pos_con_pit;
                strcpy(aux_name, opc_2[*j].ranking[i].nom_con_corredor);

                opc_2[*j].ranking[i].pos_con_pit = opc_2[*j].ranking[k].pos_con_pit;
                strcpy(opc_2[*j].ranking[i].nom_con_corredor, opc_2[*j].ranking[k].nom_con_corredor);

                opc_2[*j].ranking[k].pos_con_pit = temp;
                strcpy(opc_2[*j].ranking[k].nom_con_corredor, aux_name);
            }
        }
        opc_2[*j].ranking[i].puntuacion_con = opc_2[*j].puntos[i];
    }

    return opc_2;
}

// Funcion que se encarga la penalizacion de nuestro piloto al no haber realizado todos los pit stops de la carrera,
// ademas de localizar nuestro piloto para luego posicionarlo en la pantalla de finalizacion de la carrera y ver en
// que posicion ha quedado de la carrera.
OpcionDos *penalizacion(OpcionDos *opc_2, OpcionUno opc_1, InfoCorredor *corredor, GPese node_opc2, int num_pilotos, int j){
    int i = 0, k = 0, comp = 5, l = 0;
    float temp = 0, sort_t = 0;
    char aux_name[35];

    // Si no se ha realizado todos los pit stops del piloto, se aplica una penalizacion de adicion del tiempo de pit
    // stop del gran premio actual multiplicado por 5.
    if (opc_2[j].print_count != (opc_2[j].pit_stop / node_opc2.i_t_pitstop)){
        opc_2[j].t_total[0].t_sin_pit = opc_2[j].t_total[0].t_sin_pit + (5 * node_opc2.i_t_pitstop * 1.0);
        opc_2[j].ranking[0].pos_sin_pit = opc_2[j].t_total[0].t_sin_pit;
        opc_2[j].check = 1;
    }

    strcpy(opc_2[j].ranking[0].nom_sin_corredor, opc_1.nombre);
    strcpy(opc_2[j].ranking[0].nom_con_corredor, opc_1.nombre);

    for (i = 1; i < num_pilotos + 1; i++){
        strcpy(opc_2[j].ranking[i].nom_sin_corredor, corredor[i - 1].nom);
        strcpy(opc_2[j].ranking[i].nom_con_corredor, corredor[i - 1].nom);
    }

    // Funcion que se encarga de ordenar a los corredores y el piloto en el ranking segun el tiempo que han tardado en
    // completar la carrera. En mi caso, se contempla dos tipos de rankings, una donde se realizarn todos los pit stops
    // y la otra donde no se realizan. Mas adelante, se guarda en un tipo de ranking definitivo esa informacion para
    // asi no tener que depender de dos tipos distintos.
    opc_2 = sortRanked(opc_2, i, &j, k, num_pilotos, temp, sort_t, aux_name);

    opc_2[j].sin = 0;
    opc_2[j].con = 0;

    // Se encarga de encontrar la posicion en la que nuestro piloto se encuentra para guardarnos esa posicion mas
    // adelante al mostrar el resultado final de la posicion en la que ha quedado en la carrera del grande premio actual.
    for (i = 0; i < num_pilotos + 1; i++){
        comp = strcmp(opc_1.nombre, opc_2[j].ranking[i].nom_sin_corredor);

        if (comp == 0){
            opc_2[j].sin = i;
        }
    }

    for (i = 0; i < num_pilotos + 1; i++){
        comp = strcmp(opc_1.nombre, opc_2[j].ranking[i].nom_con_corredor);

        if (comp == 0){
            opc_2[j].con = i;
        }
    }

    return opc_2;
}

// Funcion que se encarga de mostrar los paneles de informacion de la carrera, desde nombre de piloto hasta el tiempo
// que esta transcurriendo en el momento.
void UiVistaCarrera (OpcionUno opc_1, OpcionDos *opc_2, InfoCorredor *corredor, GPese node_opc2, StructSuma *suma, int min, int sec, int num_pilotos, ALLEGRO_BITMAP *za_warudo, int j){
    int i = 0;

    al_draw_filled_rectangle(0, 710, 750, 810,LS_allegro_get_color(BLACK));
    al_draw_filled_rectangle(751, 0, 1100, 810,LS_allegro_get_color(BLACK));

    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),20, 750, 0, "%s","RADIO (R)");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),470, 750, 0, "%s","PIT STOP (P)");

    for (i = 0; i < num_pilotos; i++) {
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLACK), 30,50, 0, "%s", opc_1.c_dorsal);
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(BLACK), 30,135 + (85 * i), 0, "%d",corredor[i].dors);
    }

    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 760,10, 0, "%s", "PILOTO");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 60, 0, "%s", "NOMBRE");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 90, 0, "%s",opc_1.nombre);
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 130, 0, "%s","ESCUDERIA");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 160, 0, "%s",opc_1.escuderia);
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 200, 0, "%s", "DORSAL");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 230, 0, "%s",opc_1.c_dorsal);

    al_draw_filled_rectangle(760, 265, 1090,267,LS_allegro_get_color(LIGHT_GRAY));

    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 760,280, 0, "%s", "COCHE");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 330, 0, "%s","VELOCIDAD");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 360, 0, "%.2f",suma->suma_vel);
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 400, 0, "%s","ACELERACION");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 430, 0, "%.2f",suma->suma_acel);
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 470, 0, "%s", "CONSUMO");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 500, 0, "%.2f",suma->suma_cons);
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),760, 540, 0, "%s","FIABILIDAD");
    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(YELLOW),770, 570, 0, "%.2f",suma->suma_fiab);

    al_draw_filled_rectangle(760, 605, 1090,607,LS_allegro_get_color(LIGHT_GRAY));

    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 850,620, 0, "%02d:", min);
    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 933,620, 0, "%02d", sec);

    al_draw_filled_rectangle(760, 665, 1090,667,LS_allegro_get_color(LIGHT_GRAY));

    al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),957, 710, 0, "%s", "STOPS:");
    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 965,745, 0, "%d", opc_2[j].print_count);
    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 1000,745, 0, "%s", "/");
    al_draw_textf(LS_allegro_get_font(EXTRA_LARGE),LS_allegro_get_color(WHITE), 1035,745, 0, "%d", opc_2[j].pit_stop / node_opc2.i_t_pitstop);

    al_draw_scaled_bitmap(za_warudo, 0, 0, 1073,1024, 760, 640, 175,175, 0);

    LS_allegro_clear_and_paint(WHITE);
}

// Funcion que se encarga de mostrar los controles disponibles que tiene el usuario disponible para hacer uso. En este
// caso solo tiene disponible los controles de radio y pit stop.
void muestraControlesOpc2 (OpcionDos *opc_2, int *radio, GPese node_opc2, double *aviso, int j){
    if (LS_allegro_key_pressed(ALLEGRO_KEY_R)){
        *radio = 1;
    }

    if (LS_allegro_key_pressed(ALLEGRO_KEY_P)) {

        // Si se da el caso de que se ha presionado la tecla de boton pit stop y no se este en proceso de espera,
        // accedemos a...
        if ((opc_2[j].print_count != (opc_2[j].pit_stop / node_opc2.i_t_pitstop)) || ((opc_2[j].print_count != (opc_2[j].pit_stop / node_opc2.i_t_pitstop)) && (*aviso >= 7))) {

            // ...la comprobacion de si se presiono la tecla de radio. En el caso de haberse presionado, se contara
            // un pit stop. En el caso contrario de no haber presionado la tecla de radio, no se cuenta como pit stop
            // y ademas tambien se realiza la espera como consecuencia de no haber pedido previamente por radio el
            // cambio de ruedas.
            if (*radio == 1){
                (opc_2[j].print_count)++;
                *radio = 0;
            }
            *aviso = 0;
            opc_2[j].count_n_pitstop++;
        }
    }
}

// Funcion que se encarga de calcular el recorrido general del resto de corredores y el recorrido de nuestro piloto.
// Sobretoo tiene en cuenta cuando ha de parar segun si ha presionado el pit stop o no.
void movimientoCoches (int *k, int *j, int num_pilotos, int *recorrido_gen, int *recorrido_pil, double *veces, double *veces_aux, OpcionDos *opc_2, GPese node_opc2, ALLEGRO_BITMAP *cochecito, double *aviso, int *toque){
    for (*k = 1; *k < num_pilotos + 1; (*k)++) {
        // Ecuacion que hace que nuestro piloto y el resto de corredores progresen de principio a final de carrera.
        *recorrido_gen = 100 + ((550 / opc_2[*j].t_total[*k].t_sin_pit) * *veces);
        *recorrido_pil = 100 + ((550 / opc_2[*j].t_total[0].t_sin_pit) * *veces_aux);

        // Si se da el caso de que nuestro piloto o cualquier otro corredor llegan o superan el valor del pixel de
        // finalizacion de la carrera, parara.
        if ((*recorrido_gen >= 650) && (*recorrido_pil >= 650)) {
            al_draw_bitmap(cochecito, 650, 40 + (85 * 0),0);
            al_draw_bitmap(cochecito, 650, 40 + (85 * *k),0);
        }else{

            // Si se da el caso de que nuestro piloto o algun corredor llegan a la meta, el programa obligara a que
            // el resto de competidores continuen progresando hasta llegar a la meta.
            if ((*recorrido_gen >= 650) || (*recorrido_pil >= 650)){

                if (*recorrido_gen >= 650){
                    al_draw_bitmap(cochecito, 650, 40 + (85 * *k),0);
                    al_draw_bitmap(cochecito, *recorrido_pil, 40 + (85 * 0),0);
                }

                if (*recorrido_pil >= 650){
                    al_draw_bitmap(cochecito, 650, 40 + (85 * 0),0);
                    al_draw_bitmap(cochecito, *recorrido_gen, 40 + (85 * *k),0);
                }
            }else{

                // Progreso normal de los corredores y nuestro piloto en base a la formula calculada al principio de
                // la funcion.
                if (opc_2[*j].count_n_pitstop >= 1 && *aviso < node_opc2.i_t_pitstop){
                    al_draw_bitmap(cochecito, *recorrido_pil, 40 + (85 * 0),0);
                    al_draw_bitmap(cochecito, *recorrido_gen, 40 + (85 * *k),0);
                    *toque = 1;
                }else{

                    // Si se da el caso de que se ha presionado la tecla de pit stop, y ha pasado el tiempo de
                    // transcurre el piloto continuara progresando, a pesar de que se ha activado el flag.
                    if (opc_2[*j].count_n_pitstop >= 1 && *toque == 1){
                        al_draw_bitmap(cochecito, *recorrido_pil, 40 + (85 * 0),0);
                    }else{

                        // Aqui sin embargo, en el caso contrario de no haber presionado el boton de pit stop,
                        // continuara progresando.
                        if (opc_2[*j].count_n_pitstop < 1){
                            al_draw_bitmap(cochecito, *recorrido_pil, 40 + (85 * 0),0);
                        }
                    }
                    // Independientemente de que pase una situacion u otra de las mencionadas previamente, el resto
                    // de corredores continuando progresando.
                    al_draw_bitmap(cochecito, *recorrido_gen, 40 + (85 * *k),0);
                }
            }
        }
    }
}

// Funcion que se encarga de llevar la logica del tiempo del programa. Es decir, controla cuantos segundos ha de parar
// nuestro piloto cuando se realice el pit stop, cuando parar al final de la carrera, etc... DeVuelve como valor de
// retorno el tipo propio 'OpcionDos' lleno de informacion.
OpcionDos *muestraVistaCarrera (OpcionDos *opc_2, OpcionUno opc_1, InfoCorredor *corredor, StructSuma *suma, GPese node_opc2, int num_pilotos, int j){
    ALLEGRO_BITMAP *cochecito, *za_warudo;
    int i = 0, k = 0, nSortir = 0, sec = 0, min = 0, recorrido_gen = 0, recorrido_pil = 0, toque = 0, radio = 0;
    float t0 = 0, t1 = 0, seg = 0;
    double veces = 0, veces_aux = 0, aviso = 0;

    cochecito = al_load_bitmap("cotxe.png");
    za_warudo = al_load_bitmap("its-time-to-stop.png");

    t0 = (float) clock();
    while ((veces < 10000000 && sec < 10000000) && !nSortir) {

        if (recorrido_pil >= 650) {
            nSortir = 1;
        }

        t1 = (float) clock();
        seg = ((t1 - t0) / (float) CLOCKS_PER_SEC);

        if (seg >= 1) {
            sec++;
            veces++;

            // Si se da el caso de que hemos dado al control de pit stop, nuestro valor auxiliar double del tiempo a
            // controlar se parara. Y una vez haya pasado el tiempo de pit stop correspondiente, continuara aumentando
            // su valor progresvamente en base a cuando pase 1 segundo.
            if (opc_2[j].count_n_pitstop >= 1 && aviso < node_opc2.i_t_pitstop) {
                veces_aux = veces_aux;
            }else{
                veces_aux++;
            }

            aviso++;
            t0 = (float) clock();
        }

        if (sec > 59) {
            min++;
            sec = 0;
        }

        for (i = 0; i < num_pilotos + 1; i++){
            opc_2[j].t_total[i].first_stop = 1;
            opc_2[j].t_total[i].second_stop = 0;
        }

        for (i = 0; i < num_pilotos + 1; i++) {
            al_draw_filled_rectangle(100,60 + (85 * i),650,65 + (85 * i),LS_allegro_get_color(BLACK));
        }

        // Funcion que se encarga de calcular el recorrido general del resto de corredores y el recorrido de nuestro
        // piloto. Sobretoo tiene en cuenta cuando ha de parar segun si ha presionado el pit stop o no.
        movimientoCoches (&k, &j, num_pilotos, &recorrido_gen, &recorrido_pil, &veces, &veces_aux, opc_2, node_opc2, cochecito, &aviso, &toque);

        // Funcion que se encarga de mostrar los controles disponibles que tiene el usuario disponible para hacer uso.
        // En este caso solo tiene disponible los controles de radio y pit stop.
        muestraControlesOpc2 (opc_2, &radio, node_opc2, &aviso, j);

        // Funcion que se encarga de mostrar los paneles de informacion de la carrera, desde nombre de piloto hasta el
        // tiempo que esta transcurriendo en el momento.
        UiVistaCarrera (opc_1, opc_2, corredor, node_opc2, suma, min, sec, num_pilotos, za_warudo, j);
    }

    return opc_2;
}

// Funcion que se encarga de llevar a cabo la logica detras del funcionamiento de las luces del semaforo, como es en
// este caso cuando encender un conjunto de luces en segun cuantos segundos.
void muestraSemaforo (){
    ALLEGRO_BITMAP *fito, *guerrero, *geli, *sanfeliu;
    int i = 0, j = 0;
    float t0 = 0, t1 = 0, seg = 0;
    double veces = 0;

    fito = al_load_bitmap("Fito-Kart.png");
    guerrero = al_load_bitmap("Guillem-Kart.png");
    geli = al_load_bitmap("Javier-Kart.png");
    sanfeliu = al_load_bitmap("Sanfeliu-Kart.png");
    t0 = (float) clock();
    veces = 0;

    // Asociamos una variable de tipo double al numero de segundos reales que sacamos del clock de nuestro sistema
    // para tener en cuenta el tiempo que ha de transcurrir durante el proceso de iluminacion del semaforo.
    while (veces < 7.5) {
        t1 = (float) clock();
        seg = ((t1 - t0) / (float) CLOCKS_PER_SEC);

        for (j = 0; j < 5; j++) {
            al_draw_filled_rectangle(58 + (208 * j),203, 208 +(208 * j),607,LS_allegro_get_color(BLACK));
        }

        for (i = 0; i < 5; i++) {

            for (j = 0; j < 5; j++) {
                al_draw_filled_circle(133 + (208 * i),244 + (80 * j), 33,LS_allegro_get_color(GRAY));
            }
        }

        al_draw_scaled_bitmap(fito, 0, 0, 292,246, 25 + (150 * veces), 25, 175,150, 0);
        al_draw_scaled_bitmap(sanfeliu, 0, 0, 500,370, -250 + (150 * veces), 25, 200,150, 0);
        al_draw_scaled_bitmap(geli, 0, 0, 400,400, 900 + (-150 * veces), 625, 185,160, 0);
        al_draw_scaled_bitmap(guerrero, 0, 0, 302,247, 1175 + (-150 * veces), 625, 210,160, 0);

        // Mientras pase un segundo, que es lo que nos interesa, que aumente el valor de la variable double en la que
        // nos basamos para controlar el tiempo del proceso de iluminacion del semaforo.
        if (seg >= 1) {
            veces++;
            t0 = (float) clock();
        }

        if (veces < 8) {

            // Si el valor de la variable double llega a 7, le sumaremos 0,5 para que acabe la carrera tal y como se
            // nos pedia en el enunciado, ademas de apagar las luces del semaforo durante ese breve periodo de tiempo.
            if (veces == 7) {

                for (i = 0; i < 5; i++) {

                    for (j = 0; j < 5; j++) {
                        al_draw_filled_circle(133 + (208 * i),244 + (80 * j), 33,LS_allegro_get_color(GRAY));
                    }
                }
                veces = veces + 0.5;
            } else {

                // En el caso contrario, se seguiran encenciendo la columna de luces rojas del semaforo.
                for (i = 0; i < veces; i++) {

                    for (j = 3; j < 5; j++) {
                        al_draw_filled_circle(133 + (208 * i),244 + (80 * j), 33,LS_allegro_get_color(RED));
                    }
                }
            }
        }
        LS_allegro_clear_and_paint(WHITE);
    }
}

// Funcion que se encarga de mostrar la pantalla de inicio del gran premio, donde se detalla info. como la velocidad,
// aceleracion, etc... de la carrera.
void muestraInfoGP (GPese node_opc2){
    int nSortir = 0;

    LS_allegro_init(1100, 810,"Vista de la carrera inicial");
    while (!nSortir) {

        if (LS_allegro_key_pressed(ALLEGRO_KEY_R)) {
            nSortir = 1;
        }

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),300, 200, 0, "%s","BIENVENIDO AL ");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),615, 200, 0, "%s",node_opc2.nom_premio);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),325, 275, 0, "%s","VELOCIDAD:");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 275, 0, "%s",node_opc2.c_vel_adec);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),325, 350, 0, "%s","ACELERACION:");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 350, 0, "%s",node_opc2.c_acel_adec);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),325, 425, 0, "%s","CONSUMO:");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 425, 0, "%s",node_opc2.c_cons_adec);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),325, 500, 0, "%s","FIABILIDAD:");
        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),725, 500, 0, "%s",node_opc2.c_fiab_adec);

        al_draw_textf(LS_allegro_get_font(LARGE),LS_allegro_get_color(WHITE),200, 600, 0, "%s","PULSA 'R' PARA COMENZAR LA CARRERA");

        LS_allegro_clear_and_paint(BLACK);
    }
}

// Funcion que se encarga de calcular el tiempo que tarda cada corredor en completar la carrera. Nos servira esta
// informacion mas adelante para ordenar los corredores en el ranking en base al tiempo en que han completado el
// grande premio.
OpcionDos *calculoTiempoTotal (OpcionDos *opc_2, OpcionUno opc_1, InfoCorredor *corredor, StructSuma *suma, InfoPieza *pieza, int num_pilotos, InfoBase *stats_def, GPese node_opc2, int num_piezas, int j){
    int i = 0, k = 0;
    float aux_calc = 0;

    for (i = 0; i < num_pilotos + 1; i++){

        // Si el valor de indice de i es menor que 1, nos disponemos a calcular el tiempo total al completar la carrera
        // para nuestro piloto.
        if (i < 1){

            // Sumamos todos los factores de velodiad, aceleracion, etc...  de los motores de preferencia que hemos
            // seleccionado en la opcion 1.
            for (k = 0; k < num_piezas; k++){
                suma[j].suma_vel = suma[j].suma_vel + atoi(pieza[k].motor[pieza[k].sel_piez].vel);
                suma[j].suma_acel = suma[j].suma_acel + atoi(pieza[k].motor[pieza[k].sel_piez].acel);
                suma[j].suma_cons = suma[j].suma_cons + atoi(pieza[k].motor[pieza[k].sel_piez].cons);
                suma[j].suma_fiab = suma[j].suma_fiab + atoi(pieza[k].motor[pieza[k].sel_piez].fiab);
            }

            // Acto seguido, sumamos los valores base extraidos del fichero de estadisticas base a la suma de motores
            // que hemos calculado antes.
            suma[j].suma_vel = suma[j].suma_vel + (float)stats_def->vel;
            suma[j].suma_acel = suma[j].suma_acel + (float)stats_def->acel;
            suma[j].suma_cons = suma[j].suma_cons + (float)stats_def->cons;
            suma[j].suma_fiab = suma[j].suma_fiab + (float)stats_def->fiab;

            // Calculamos una formula donde nos da una parte del resultado final a calcular.
            aux_calc = ((node_opc2.f_t_base * 60) + abs((node_opc2.i_vel_adec - (int)suma[j].suma_vel)) + abs((node_opc2.i_acel_adec - (int)suma[j].suma_acel)) + abs((node_opc2.i_cons_adec - (int)suma[j].suma_cons)) + abs((node_opc2.i_fiab_adec - (int)suma[j].suma_fiab)));

            // Si la suma acumulada del factor de consumo es menor que el adecuado que nos ofrece el grande premio
            // actual, restaremos un pit stop. En el caso contrario, añadiremos uno mas.
            if (suma[j].suma_cons < (float)node_opc2.i_cons_adec){
                opc_2[j].pit_stop = node_opc2.i_num_pitstop - 1;
            }else{
                opc_2[j].pit_stop = node_opc2.i_num_pitstop + 1;
            }
            // Calculamos finalmente el tiempo total de cada corredor haciendo uso del calculo auxiliar anterior.
            // Aqui tendremos dos tipos de tiempo total segun si ha utilizado todos los pit stops o no.
            opc_2[j].pit_stop = opc_2[j].pit_stop * node_opc2.i_t_pitstop;
            opc_2[j].t_total[i].t_con_pit = (aux_calc + (float)opc_2[j].pit_stop) - ((((float)opc_1.i_reflej + (float)opc_1.i_cond_fis + (float)opc_1.i_temp + (float)opc_1.i_gest_neum) / 4.0) / 2.0);
            opc_2[j].t_total[i].t_sin_pit = opc_2[j].t_total[i].t_con_pit - (float)opc_2[j].pit_stop;
        }else{

            // En este caso, como el valor de indice i es mayor que 0, aqui nos disponemos a calcular el tiempo total
            // del resto de corredores. Es el mismo proceso que antes, solo que con la diferencia de que no tenemos
            // en cuenta el factor del tiempo de pit stop para el resto de corredores.
            if (i > 0){
                aux_calc = (node_opc2.f_t_base * 60) + abs((node_opc2.i_vel_adec - ((corredor[i-1].vel) + stats_def->vel))) + abs((node_opc2.i_acel_adec - ((corredor[i-1].acel) + stats_def->acel))) + abs((node_opc2.i_cons_adec - ((corredor[i-1].cons) + stats_def->cons))) + abs((node_opc2.i_fiab_adec - ((corredor[i-1].fiab) + stats_def->fiab)));

                if ((float)(corredor[i-1].cons) < (float)node_opc2.i_cons_adec){
                    opc_2[j].pit_stop = node_opc2.i_num_pitstop - 1;
                }else{
                    opc_2[j].pit_stop = node_opc2.i_num_pitstop + 1;
                }
                opc_2[j].pit_stop = opc_2[j].pit_stop * node_opc2.i_t_pitstop;
                opc_2[j].t_total[i].t_con_pit = (aux_calc + (float)opc_2[j].pit_stop) - ((((float)(corredor[i-1].reflej) + (float)(corredor[i-1].cond_fis) + (float)(corredor[i-1].temp) + (float)(corredor[i-1].gest_neum)) / 4.0) / 2.0);;
                opc_2[j].t_total[i].t_sin_pit = (aux_calc + (float)opc_2[j].pit_stop) - ((((float)(corredor[i-1].reflej) + (float)(corredor[i-1].cond_fis) + (float)(corredor[i-1].temp) + (float)(corredor[i-1].gest_neum)) / 4.0) / 2.0);
            }
        }
    }

    // Copiamos toda la informacion obtenida dentro de otro tipo distinto llamado 'ranking' donde a partir de adelante
    // solo nos centraremos en usar este tipo con la informacion de nuestro interes.
    for (i = 0; i < num_pilotos + 1; i++){
        opc_2[j].ranking[i].pos_sin_pit = opc_2[j].t_total[i].t_sin_pit;
        opc_2[j].ranking[i].t_sin_pit = opc_2[j].t_total[i].t_sin_pit;
        opc_2[j].ranking[i].pos_con_pit = opc_2[j].t_total[i].t_con_pit;
        opc_2[j].ranking[i].t_con_pit = opc_2[j].t_total[i].t_con_pit;
    }

    return opc_2;
}

// Funcion que se encarga de inicializar varias variables a unos valores predeterminados para evitar problemas mas
// adelante. DeVuelve como valor de retorno el tipo propio 'OpcionDos' lleno de informacion.
OpcionDos *inicializaVars (StructSuma *suma, OpcionDos *opc_2, GPese node_opc2, int j){

    opc_2[j].count_n_pitstop = 0;
    opc_2[j].pit_stop = 0;

    suma[j].suma_vel = 0;
    suma[j].suma_acel = 0;
    suma[j].suma_cons = 0;
    suma[j].suma_fiab = 0;

    opc_2[j].puntos[0] = 25;
    opc_2[j].puntos[1] = 18;
    opc_2[j].puntos[2] = 15;
    opc_2[j].puntos[3] = 10;
    opc_2[j].puntos[4] = 8;
    opc_2[j].puntos[5] = 6;
    opc_2[j].puntos[6] = 5;
    opc_2[j].puntos[7] = 3;

    opc_2[j].check = 0;

    strcpy(opc_2[j].nom_gp, node_opc2.nom_premio);

    return opc_2;
}

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
OpcionDos* getOpc2Info (OpcionDos *opc_2, OpcionUno opc_1, int num_pilotos, int num_piezas, InfoPieza *pieza, InfoBase *stats_def, StructSuma *suma, GPese node_opc2, InfoCorredor *corredor, int j){
    // Funcion que se encarga de inicializar varias variables a unos valores predeterminados para evitar problemas mas
    // adelante. DeVuelve como valor de retorno el tipo propio 'OpcionDos' lleno de informacion.
    opc_2 = inicializaVars(suma, opc_2, node_opc2, j);

    // Funcion que se encarga de calcular el tiempo que tarda cada corredor en completar la carrera. Nos servira esta
    // informacion mas adelante para ordenar los corredores en el ranking en base al tiempo en que han completado el
    // grande premio.
    opc_2 = calculoTiempoTotal(opc_2, opc_1, corredor, suma, pieza, num_pilotos, stats_def, node_opc2, num_piezas, j);

    // Funcion que se encarga de mostrar la pantalla de inicio del gran premio, donde se detalla info. como la velocidad,
    // aceleracion, etc... de la carrera.
    muestraInfoGP(node_opc2);

    // Funcion que se encarga de llevar a cabo la logica detras del funcionamiento de las luces del semaforo, como es en
    // este caso cuando encender un conjunto de luces en segun cuantos segundos.
    muestraSemaforo();

    // Funcion que se encarga de llevar la logica del tiempo del programa. Es decir, controla cuantos segundos ha de
    // parar nuestro piloto cuando se realice el pit stop, cuando parar al final de la carrera, etc... DeVuelve como
    // valor de retorno el tipo propio 'OpcionDos' lleno de informacion.
    opc_2 = muestraVistaCarrera(opc_2, opc_1, corredor, suma, node_opc2, num_pilotos, j);

    // Funcion que se encarga la penalizacion de nuestro piloto al no haber realizado todos los pit stops de la carrera,
    // ademas de localizar nuestro piloto para luego posicionarlo en la pantalla de finalizacion de la carrera y ver en
    // que posicion ha quedado de la carrera.
    opc_2 = penalizacion(opc_2, opc_1, corredor, node_opc2, num_pilotos, j);

    // Muestra el resultado final en el que nuestro piloto ha quedado de la carrera.
    muestraResultadoPiloto(opc_2, node_opc2, j);

    return opc_2;
}