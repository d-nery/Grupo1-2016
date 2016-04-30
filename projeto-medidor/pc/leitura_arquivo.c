#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Uso: %s arquivo\n", argv[0]);
		return -1;
	}

	int fd;
	// Tenta abrir em apenas leitura.
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		// Se abertura falhou, open retorna -1.
		// A função perror mostra na tela a razão da falho.
		perror("open");
		return -1;
	}

	for (;;) {
		unsigned char buffer[40];
		ssize_t count;

		// read retorna o número de bytes lidos, que é salvo na variável count.
		// Se for -1, indica que houve erro. Se for 0, indica que o arquivo acabou.
		count = read(fd, buffer, sizeof(buffer));

		switch (count) {
		case -1:
			perror("read");
			return -1;

		case 0:
			// Fim do arquivo, fecha e termina o programa.
			close(fd);
			return 0;

		default:
			{
				// Se chegou aqui, a leitura deu certo e você pode fazer alguma
				// coisa com os dados.


				if (buffer[0] < 7) {
					/*if (buffer[7] != (unsigned char)(buffer[0]+buffer[1]+buffer[2]+buffer[3]+buffer[4]+'\r'+'\n'))
						printf("Erro checksum. Perda de bytes.\n");
					else */{
						printf("Celula: %d ", buffer[0]);
						printf("Voltagem: %c%c%c%c", buffer[1], buffer[2], buffer[3], buffer[4]) ;
						printf("\n");
					}
					/*printf("Buffer[7]:%d \n", buffer[7]);
					printf("Soma: %d \n", (unsigned char)(buffer[0]+buffer[1]+buffer[2]+buffer[3]+buffer[4]+'\r'+'\n'));*/

				}
				else if(buffer[0] == 'T'){
					/*if (buffer [5] != (unsigned char)('T'+buffer[1]+buffer[2]+buffer[3]+buffer[4]))
						printf("Erro checksum. Perda de bytes.\n");
					else*/{
						printf("Total: %c%c%c%c", buffer[1], buffer[2], buffer[3], buffer[4]);
						printf("\n");
					}
					/*printf("Buffer[5]:%d \n", buffer[5]);
					printf("Soma: %d \n", (unsigned char)('T'+buffer[1]+buffer[2]+buffer[3]+buffer[4]));*/
				}
			}

		}
	}
}
