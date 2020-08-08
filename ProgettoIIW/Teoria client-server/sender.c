#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PKT_SIZE 2
int file_divider(FILE *file, char ***pkts, int *num_pkt){
	int file_size;

	//dimesione del file e numero dei pacchetti
	if(fseek(file, 0, SEEK_END) < 0) {
		perror("fseek_end");
		return -1;
	}
	if((file_size = ftell(file)) < 0) {
		perror("ftell");
		return -1;
	}

	*num_pkt = (file_size % PKT_SIZE) == 0 ? (int) file_size/PKT_SIZE : (int) (file_size/PKT_SIZE) + 1;
	printf("Numero pacchetti: %d\n" , *num_pkt );
	// allochiamo spazio necessario per i pacchetti
	if((*pkts = calloc(*num_pkt, PKT_SIZE+1)) == NULL){
		perror("calloc");
		return -1;
	}

	//riempiamo array con i pacchetti
	//imposto seek a inizio file
	if(fseek(file, 0, SEEK_SET) < 0) {
		perror("fseek_set");
		return -1;
	}

//provo a leggere solo le prime due lettere
	if(fread(**pkts, PKT_SIZE, 1, file) != (unsigned int) 2){
		perror("fread");
		return -1;
	}
	printf("%s\n",**pkts );
	/*printf("Primo elemento del puntatore a puntatore :%s\n", pkts[0]);
	printf("Secondo elemento del puntatore a puntatore :%s\n", pkts[1]);

	//leggiamo il file PKT_SIZE byte alla volta
	/for( int j=0; j<*num_pkt; j++){
		if ((int)fread(*pkts+(j*(PKT_SIZE+1)), PKT_SIZE, 1, file) != PKT_SIZE) {
	    	perror("fread");
	    	return -1;
		}
		pkts[(j+1)*PKT_SIZE] = '\0';
	}


	if (ftell(file) != file_size){
		perror("ftell");
		return -1;
	}
	*/

	return 0;
}

int main(int argc, char *argv[]){
	argc = argc;
	argv = argv;

  char **pkts;
	int num_pkt;
	FILE *f;

	if((f = fopen("./pippo.txt", "w+")) == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char *buf = "abdullah";
	fwrite(buf, strlen(buf), 1, f);

	file_divider(f, &pkts, &num_pkt);
	/*for (int i = 0; i < num_pkt; i++){
		printf("Pacchetto numero %d\nContenuto :%c\n",i+1,pkts[i]);
		printf("-------\n");
	}
	*/
	fclose(f);
	free(pkts);
	return 0;
}
