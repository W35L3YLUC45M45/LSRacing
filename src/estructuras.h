/***********************************************************************************************************************
 *
 * @Proposito: Creado unica y exclusivamente como lugar de reunion de todos los tipos definidos que nos ayudan a
 *             almacenar informacion a lo largo del programa.
 *
 * @Autor/es: Wesley Lucas Mas (wesley.lucas@students.salle.url.edu)
 *
 * @Fecha creacion: 02/03/2020
 *
 * @Fecha ultima modificacion: 10/05/2020
 *
 **********************************************************************************************************************/

// Define Guard
#ifndef _PJ2_WESLEY_LUCAS_ESTRUCTURAS_H_
#define _PJ2_WESLEY_LUCAS_ESTRUCTURAS_H_

// Constantes
#define CHAR_NOM 27
#define AUX_NOM 100
#define CHAR_NUM 5

// Tipos propios
// Tipo propio de info. relacionada con la opcion 1 del programa
typedef struct{
    int acceso;
    char nombre[CHAR_NOM];
    char aux_nombre[AUX_NOM];
    int len_nombre;
    char escuderia[CHAR_NOM];
    char aux_escuderia[AUX_NOM];
    int len_escuderia;
    char c_dorsal[CHAR_NUM];
    char aux_c_dorsal[AUX_NOM];
    int i_dorsal;
    int len_dorsal;
    char c_reflej[CHAR_NUM];
    char aux_c_reflej[AUX_NOM];
    int i_reflej;
    int len_reflej;
    char c_cond_fis[CHAR_NUM];
    char aux_c_cond_fis[AUX_NOM];
    int i_cond_fis;
    int len_cond_fis;
    char c_temp[CHAR_NUM];
    char aux_c_temp[AUX_NOM];
    int i_temp;
    int len_temp;
    char c_gest_neum[CHAR_NUM];
    char aux_c_gest_neum[AUX_NOM];
    int i_gest_neum;
    int len_gest_neum;
} OpcionUno;

// Tipo propio de info. relacionada con la carrera de los corredores (tiempo con/sin pitstop, posicion de rank, etc...)
typedef struct{
    float pos_sin_pit;
    float pos_con_pit;
    char nom_sin_corredor[27];
    char nom_con_corredor[27];
    int puntuacion_sin;
    int puntuacion_con;
    float t_sin_pit;
    float t_con_pit;
} InfoCarrera;

// Tipo propio de info. relacionada con el control del tiempo a la hora de hacer mover los corredores en la simulacion
typedef struct{
    int second_stop;
    int first_stop;
    float t_sin_pit;
    float t_con_pit;
} ControlTiempo;

// Tipo propio de info. relacionada con la opcion 2 del programa
typedef struct{
    InfoCarrera *ranking;
    ControlTiempo *t_total;
    int sin;
    int con;
    int puntos[8];
    int count_n_pitstop;
    int pit_stop;
    int print_count;
    char nom_gp[27];
    int check;
} OpcionDos;

// Tipo propio de info. relacionada con el ranking definitivo de los corredores que se utiliza para la opcion 3
typedef struct{
    char nombre[27];
    int posicion;
    float tiempo;
    int puntos;
} DefRanking;

// Tipo propio de info. relacionada con el ranking definitivo de los corredores al mostrar la finalizacion de la season
typedef struct{
    int puntuacion;
    char nombre[27];
    int posicion;
    int dorsal;
} DatosTotal;

// Tipo propio de info. relacionada con la opcion 3 del programa
typedef struct{
    char nombre_gp[27];
    DefRanking *rank_def;
} OpcionTres;

// Tipo propio de info. relacionada con la suma de las velocidad/aceleraciones/etc... acumuladas para la opcion 2
typedef struct{
    float suma_vel;
    float suma_acel;
    float suma_cons;
    float suma_fiab;
} StructSuma;

// Tipo propio de info. relacionada con la seleccion del motor de preferencia de la opcion 1
typedef struct{
    char compst[27];
    char vel[27];
    char acel[27];
    char cons[27];
    char fiab[27];
    int sel_mot;
    int aviso_mot;
} InfoMotor;

// Tipo propio de info. relacionada con la seleccion de la pieza de preferencia de la opcion 1
typedef struct{
    char nom_compnt[27];
    int num_motores;
    char c_num_motores[5];
    int sel_piez;
    int aviso_piez;
    InfoMotor *motor;
} InfoPieza;

// Tipo propio de info. relacionada con los grandes premios
typedef struct{
    char c_pos_calend[27];
    char nom_premio[27];
    char c_vel_adec[27];
    char c_acel_adec[27];
    char c_cons_adec[27];
    char c_fiab_adec[27];
    char c_t_base[27];
    char c_t_pitstop[27];
    char c_num_pitstop[27];

    int i_pos_calend;
    int i_vel_adec;
    int i_acel_adec;
    int i_cons_adec;
    int i_fiab_adec;
    float f_t_base;
    int i_t_pitstop;
    int i_num_pitstop;
} InfoGPs;

// Tipo propio de informacion relacionada con los corredores de la carrera
typedef struct{
    char nom[27];
    int dors;
    char escud[27];
    int vel;
    int acel;
    int cons;
    int fiab;
    int reflej;
    int cond_fis;
    int temp;
    int gest_neum;
} InfoCorredor;

// Tipo propio de informacion relacionada con las estadisticas base de todos los corredores que participan
typedef struct{
    int vel;
    int acel;
    int cons;
    int fiab;
} InfoBase;

#endif