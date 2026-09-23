#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Crea tres procesos hijos a partir de un proceso padre.
 *
 * El proceso padre utiliza fork() para crear tres hijos.
 * Cada hijo muestra su número, el PID de su padre y su propio PID.
 * El proceso padre espera a que finalicen los tres hijos mediante wait().
 *
 * @author Aitor Barros
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {

    // El proceso padre crea tres procesos hijos.
    for (int i = 1; i <= 3; i++) {

        pid_t pid = fork();

        switch (pid) {

            case 0:
                // El hijo muestra su número, el PID de su padre y su propio PID.
                printf("Soy el hijo %d, Mi padre es %d y mi PID es %d\n",
                       i, getppid(), getpid());
                return 0;

            case -1:
                // Se controla el error producido al intentar crear un hijo.
                printf("error al crear el hijo");
                i--;
                return -1;
        }
    }

    // El proceso padre espera a que terminen los tres hijos.
    for (int i = 1; i <= 3; i++) {
        wait(NULL);
    }

    // El proceso padre muestra su propio PID después de esperar a los hijos.
    printf("Proceso padre %d\n\n", getpid());

    return 0;
}