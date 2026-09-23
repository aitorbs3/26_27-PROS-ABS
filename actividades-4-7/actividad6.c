#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Crea una estructura jerárquica de procesos.
 *
 * El proceso padre crea dos procesos hijos directamente.
 * Posteriormente, el segundo hijo crea un tercer proceso.
 * Se muestran los PID de cada proceso para identificar
 * la relación entre padres e hijos.
 *
 * @author Aitor Barros
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {

    printf("Proceso padre -> mi PID es: %d\n", getpid());

    // El proceso padre crea el primer hijo.
    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Error al crear el hijo 1\n");
        return 1;
    }

    if (pid1 == 0) {
        printf("Yo soy el hijo 1, mi padre es PID= %d, yo soy PID= %d\n",
               getppid(), getpid());

        return 0;
    }

    // El padre espera a que termine el primer hijo.
    wait(NULL);

    // El proceso padre crea el segundo hijo.
    pid_t pid2 = fork();

    if (pid2 < 0) {
        printf("Error al crear el hijo 2\n");
        return 1;
    }

    if (pid2 == 0) {

        printf("Yo soy el hijo 2, mi padre es PID= %d, yo soy PID= %d\n",
               getppid(), getpid());

        // El segundo hijo crea al tercer proceso.
        pid_t pid3 = fork();

        if (pid3 < 0) {
            printf("Error al crear el hijo 3\n");
            return 1;
        }

        if (pid3 == 0) {
            printf("Yo soy el hijo del hijo 2, mi padre (hijo 2) es PID= %d, yo soy PID= %d\n",
                   getppid(), getpid());

            return 0;
        }

        // El hijo 2 espera a que termine el tercer proceso.
        wait(NULL);

        return 0;
    }

    // El padre espera a que termine el segundo hijo.
    wait(NULL);

    return 0;
}