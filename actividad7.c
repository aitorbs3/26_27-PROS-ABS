#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Comprueba el comportamiento de una variable después de crear
 * un nuevo proceso mediante fork().
 *
 * El proceso parte de un valor inicial y, después de ejecutar
 * fork(), el proceso hijo resta 5 al valor mientras que el
 * proceso padre suma 5. Cada proceso muestra su resultado.
 *
 * @author Aitor Barros
 * @return 0 si la ejecución finaliza correctamente.
 */
int main() {

    int valor = 6;

    // Se muestra el valor inicial antes de crear el nuevo proceso.
    printf("Valor inicial: %d\n", valor);

    // Se crea un nuevo proceso mediante fork().
    pid_t pid = fork();

    if (pid < 0) {
        // Se controla el error producido al crear el proceso.
        printf("Error al crear el proceso\n");
        return 1;
    }
    else if (pid == 0) {

        // El proceso hijo resta 5 al valor que tenía inicialmente.
        valor = valor - 5;

        printf("Proceso hijo:\n");
        printf("valor = %d\n", valor);
    }
    else {
        // El proceso padre suma 5 al valor inicial.
        valor = valor + 5;

        printf("Proceso padre:\n");
        printf("valor = %d\n", valor);

        // El padre espera a que termine el proceso hijo.
        wait(NULL);
    }

    return 0;
}