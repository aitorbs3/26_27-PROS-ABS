#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Crea un número de procesos hijos indicado por el usuario.
 *
 * El proceso padre solicita al usuario el número de hijos que desea
 * crear. Cada hijo muestra su PID y el PID de su proceso padre.
 * El proceso padre espera a que termine cada hijo antes de continuar.
 *
 * @author Aitor Barros
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {

    int hijos;

    // Se solicita al usuario el número de procesos hijos que desea crear.
    printf("Introduce el numero de hijos: ");
    scanf("%d", &hijos);

    // Se muestra el PID del proceso padre.
    printf("Proceso padre -> mi PID es: %d\n", getpid());

    // El proceso padre crea los hijos indicados por el usuario.
    for (int i = 1; i <= hijos; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            // Se controla el error producido al crear un proceso hijo.
            printf("error al crear el hijo");
        }
        else if (pid == 0) {
            // El hijo muestra su número, su PID y el PID de su padre.
            printf("Yo soy el hijo %d --> mi PID es %d, el PID de mi padre es %d\n",
                   i, getpid(), getppid());
        }
        else {
            // El padre espera a que termine el hijo antes de continuar.
            wait(NULL);
            break;
        }
    }

    return 0;
}