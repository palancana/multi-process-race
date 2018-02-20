//-----------------------------------------------------------------------------------------------#
//     Grup 4                                                                                    #
//      412                   Pràctica 2 - Processos                  Mario Arias Escalona       #
//                                                                              1362363          #
//      DM13                       Sistemes Operatius                    Rafael Díaz Rodríguez   #
//                                                                              1212588          #
//-----------------------------------------------------------------------------------------------#


#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>


void main(int argc, char** argv)
{
	int fills, nCavalls, process_puntuacio;
	int p[2];// creem la variable del pipe
  	int s[2];// creem la variable del pipe
  	int i, j, k;
  	int rTime, stat;
  	int fitxercarrera, fitxerpuntuacio; //carrera.txt i puntuacio.txt
  	char caracter, buffer[250]; // Buffer per escriure en el fitxer puntuacions.txt
  	char n[2];
  	srand(time(NULL));

  	
  	fitxercarrera = open("carrera.txt", O_RDONLY);
	nCavalls = (rand()%6)+4; //nº aleatori de caballs
  	pipe(s); //pipe que conectara tots els caballs amb el puntuacions
	process_puntuacio = fork();

	switch(process_puntuacio){
		
		case 0 : 
			if ((fitxerpuntuacio = open("puntuacio.txt", O_WRONLY | O_TRUNC)) < 0){
				perror("Fitxer no trobat, o no s'ha pogut obrir");
				exit(1);
			}
			close(s[1]); //Tanquem el pipe d'escritura

			for(k = 0; k < nCavalls ; k++) {
				read(s[0], &buffer, sizeof(buffer));
				 //numero del procés en puntuacions.txt
				caracter = '0'+k; 
				write(fitxerpuntuacio, &caracter, 1);
				caracter = '\t';
				write(fitxerpuntuacio, &caracter, 1);
				i = 0;
				 //string de puntuacions.txt
				while(buffer[i] != '\0') {
					write(fitxerpuntuacio, &buffer[i], 1);
					i++;
				}
				write(fitxerpuntuacio, "\n", 1);
			}
			close(s[0]); //Tanquem el pipe de lectura
			close(fitxerpuntuacio);
			exit(EXIT_SUCCESS);
			break;

		default : //el procés pare creara els processos cavalls
			for(i = 0 ; i<nCavalls ; i++) {
				pipe(p); //pipe pare-fill
				fills = fork(); //creacio del fill
				switch (fills) {
					case -1 : // error
						perror("Error a la creació del procés. ");
						break;
					case 0 : //caball
						close(p[1]);
						close(s[0]);
						read(p[0], &buffer, sizeof(buffer));
						srand((time(NULL)) ^ (getpid() << nCavalls)); // numero de segons aleatoriament
						rTime = (rand()%30)+30;

						i = 0;
						while(buffer[i] != '\0') i++;
						sleep(rTime);
						sprintf(n, "%d", rTime);
						buffer[i] = ' ';
						buffer[i+1] = n[0];
						buffer[i+2] = n[1];
						buffer[i+3] = '\0';
						//Passem l'string per pantalla

						write(s[1], &buffer, sizeof(buffer));
						close(s[1]);
						close(p[0]);
						exit(EXIT_SUCCESS);
						break;
					default : //  master
						close(p[0]);
						j = 0;
						while (read(fitxercarrera, &caracter, 1)){
							buffer[j] = caracter;
							if (caracter == '\n')
								break;
							j++;
						}
						buffer[j] = '\0';
						//Enviem la linea pel pipe a cada caball
						write(p[1], &buffer, sizeof(buffer));
						close(p[1]);
						break;

				}

		}
		break;
	}
	close (fitxercarrera);
	for (i = 0 ; i<nCavalls+1 ; i++)
		wait(&stat);//esperem a que tots els processos fills es tanquin per a que el pare pugui finalitzar.

  }
