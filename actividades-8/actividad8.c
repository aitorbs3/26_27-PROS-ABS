#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file actividad8.c
 * @brief Comunicación entre tres procesos mediante dos pipes.
 *
 * El programa crea una jerarquía de procesos:
 *
 *      ABUELO
 *         |
 *       HIJO
 *         |
 *       NIETO
 *
 * Se utilizan dos pipes:
 *
 * fd1:
 * - ABUELO -> HIJO
 * - NIETO -> HIJO
 *
 * fd2:
 * - HIJO -> NIETO
 * - HIJO -> ABUELO
 *
 * El proceso HIJO actúa como intermediario entre el ABUELO
 * y el NIETO.
 *
 * @author Aitor Barros
 * @return 0 si la ejecución finaliza correctamente.
 */

int main() {

    /*
     * fd1 se utiliza para enviar información desde el ABUELO
     * al HIJO y desde el NIETO al HIJO.
     */
    int fd1[2];

    /*
     * fd2 se utiliza para enviar información desde el HIJO
     * al NIETO y desde el HIJO al ABUELO.
     */
    int fd2[2];

    /*
     * Creación del primer pipe.
     */
    if (pipe(fd1) == -1) {
        perror("Error al crear fd1");
        return 1;
    }

    /*
     * Creación del segundo pipe.
     */
    if (pipe(fd2) == -1) {
        perror("Error al crear fd2");
        return 1;
    }

    /*
     * El proceso ABUELO crea al proceso HIJO.
     */
    pid_t pid_hijo = fork();

    if (pid_hijo < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    /*
     * =========================================================
     * PROCESO HIJO
     * =========================================================
     */
    if (pid_hijo == 0) {

        /*
         * El proceso HIJO crea al proceso NIETO.
         */
        pid_t pid_nieto = fork();

        if (pid_nieto < 0) {
            perror("Error al crear el proceso nieto");
            return 1;
        }

        /*
         * =====================================================
         * PROCESO NIETO
         * =====================================================
         */
        if (pid_nieto == 0) {

            char mensaje[100];

            /*
             * El NIETO:
             *
             * - Lee de fd2.
             * - Escribe en fd1.
             *
             * Por tanto, cierra los extremos que no utiliza.
             */
            close(fd1[0]);
            close(fd2[1]);

            /*
             * El NIETO recibe el mensaje enviado por el HIJO.
             */
            read(fd2[0], mensaje, sizeof(mensaje));

            printf("NIETO: He recibido del HIJO: %s\n", mensaje);

            /*
             * El NIETO prepara una respuesta para el HIJO.
             */
            strcpy(mensaje, "Hola HIJO, soy el NIETO.");

            /*
             * Envía la respuesta al HIJO mediante fd1.
             */
            write(fd1[1], mensaje, strlen(mensaje) + 1);

            printf("NIETO: Mensaje enviado al HIJO.\n");

            /*
             * Cerramos los descriptores utilizados.
             */
            close(fd2[0]);
            close(fd1[1]);

            return 0;
        }

        /*
         * =====================================================
         * PROCESO HIJO
         * =====================================================
         */

        char mensaje[100];

        /*
         * El HIJO mantiene abiertos los cuatro extremos porque
         * necesita comunicarse tanto con el ABUELO como con el NIETO.
         */

        /*
         * El HIJO recibe el primer mensaje enviado por el ABUELO
         * mediante fd1.
         */
        read(fd1[0], mensaje, sizeof(mensaje));

        printf("HIJO: He recibido del ABUELO: %s\n", mensaje);

        /*
         * El HIJO envía un mensaje al NIETO mediante fd2.
         */
        strcpy(mensaje, "Hola NIETO, soy el HIJO.");

        write(fd2[1], mensaje, strlen(mensaje) + 1);

        printf("HIJO: Mensaje enviado al NIETO.\n");

        /*
         * El HIJO espera la respuesta del NIETO.
         *
         * El NIETO utiliza fd1 para enviar la respuesta.
         */
        read(fd1[0], mensaje, sizeof(mensaje));

        printf("HIJO: He recibido del NIETO: %s\n", mensaje);

        /*
         * Una vez recibida la respuesta del NIETO,
         * el HIJO prepara la respuesta final para el ABUELO.
         */
        strcpy(mensaje, "El NIETO me ha respondido correctamente.");

        /*
         * El HIJO envía la respuesta al ABUELO mediante fd2.
         */
        write(fd2[1], mensaje, strlen(mensaje) + 1);

        printf("HIJO: Respuesta enviada al ABUELO.\n");

        /*
         * El HIJO espera a que termine el proceso NIETO.
         */
        wait(NULL);

        /*
         * Cerramos los descriptores utilizados por el HIJO.
         */
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);

        return 0;
    }

    /*
     * =========================================================
     * PROCESO ABUELO
     * =========================================================
     */

    char mensaje[100];

    /*
     * El ABUELO:
     *
     * - Escribe en fd1 para enviar información al HIJO.
     * - Lee de fd2 para recibir la respuesta final del HIJO.
     *
     * Por tanto, cierra los extremos que no utiliza.
     */
    close(fd1[0]);
    close(fd2[1]);

    /*
     * El ABUELO envía el primer mensaje al HIJO mediante fd1.
     */
    strcpy(mensaje, "Hola HIJO, soy el ABUELO.");

    write(fd1[1], mensaje, strlen(mensaje) + 1);

    printf("ABUELO: Mensaje enviado al HIJO.\n");

    /*
     * IMPORTANTE:
     *
     * El ABUELO espera a que termine el HIJO antes de leer de fd2.
     *
     * De esta manera evita leer el mensaje que el HIJO envía
     * inicialmente al NIETO.
     */
    wait(NULL);

    /*
     * Una vez terminado el HIJO, el ABUELO recibe la respuesta
     * final mediante fd2.
     */
    read(fd2[0], mensaje, sizeof(mensaje));

    printf("ABUELO: He recibido del HIJO: %s\n", mensaje);

    /*
     * Cerramos los descriptores utilizados por el ABUELO.
     */
    close(fd1[1]);
    close(fd2[0]);

    printf("ABUELO: El proceso HIJO ha terminado.\n");

    return 0;
}