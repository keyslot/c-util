/**
 * Programa de ejemplo para uso de GnuPG con AES-192 en GCM
 *
 * Versiones:
 *              Libgcryp: 1.8.8
 *              GCC: 10.2.1
 *
 * Info: Cifra y Descifra un vector fuente del sistema.
 * Importante: no se verifca la versión instalada.
 *
 * https://www.gnupg.org/documentation/manuals/gcrypt/
 *
 * author->keyslot
 */

#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>
/**
 * Configuración de Libgcrypt 
 * Algoritmo criptográfico y longitud de vectores.
 * Llave secreta.
 * */
#define AES GCRY_CIPHER_AES192         /*  Longitud de bloque AES.                      */
#define MODE GCRY_CIPHER_MODE_GCM      /*  Modo de cifrado de bloques (Galois).         */
#define LONGITUD_K 16                  /*  Longitud de K (2^4).                         */
#define BYTES 1024                     /*  Longiutd de 2^10 compu.                      */
#define SEC_MEM_POOL 16384             /*  Reserva de memoria(16kb) segura.             */
#define PASSWORD "·NOT·NOṬ̣̣̣̣̣̣̣"            /*  Llave secreta, debería ser un vector fuente. */
#define FLAG 0                         /*  Bandera para conf. opcionales de Libcrypt.   */

/**
 * EXIT_FAILURE
 */
void exit_if(int);

/* *
 * liberar_manejador_seguro (gcry_cipher_hd):
 * Limpia memoria para el struct hd_t de Gcry
 *
*/
static void liberar_manejador_seguro(gcry_cipher_hd_t *hd);

/**
 * Evalua el error mediante el manejador libgpg-error.
 * Imprimiendo en el flujo stderr del sistema
 *
 */
static void evaluar_error(gcry_error_t error);

/**
 * Recibe un apuntador del manejador de cifrado
 * para configurar el vector usado para el cifrado
 *
 **/
static void configurar_llave_cifrado(gcry_cipher_hd_t *hd);

/**
 * Crea un objeto para el manejador seguro de cifrado
 * de biblioteca Libgcryp
 * Prapara la inicialización de memoria segura
 */
static gcry_cipher_hd_t crear_manejador_seguro(void);

/**
 * Puede invocar las operaciones criptográficas:
 * `gcry_cipher_encrypt` o `gcry_cipher_decrypt` 
 * 
 * Lectura del archivo x
 **/
static void seguridad_archivo(char *x,char *y,gcry_error_t(*cripto)());

/**
 * f(x) -> y
*/
void cifrar_archivo(char *x,char *y);
void des_cifrar_archivo(char *x,char *y);

int main(int argc, char *argv[]) 
{
        int args = 0;
        if(argc == 4) {
           char opt = argv[1][1];
           char *in = argv[2];
           char *out = argv[3];
           args = 1;
           switch(opt) {
                   case 'e': 
		             cifrar_archivo(in,out);
                             puts(out);
                             break;
                   case 'd': 
		             des_cifrar_archivo(in,out);
                             puts(out);
                             break;
                   default:  
		             args = 0; 
                             break;
               }
        }
        
	if(!args) { 
          printf("%s opcion inputFile outputFile", *argv);
          printf("\nopcion:\n");
          printf("\t -e cifrar el archivo input\n");
          printf("\t -d descifrar el archivo input\n");
        }

        return 0;
}

void
exit_if(int expre) 
{
        if(expre){
                perror("Info. error");
                exit(EXIT_FAILURE);
        }
}

static void 
liberar_manejador_seguro(gcry_cipher_hd_t *hd) 
{
       exit_if(!hd);
       gcry_cipher_close(*hd);
       hd = NULL;
}

static void 
evaluar_error(gcry_error_t error) 
{
       if(error){
               fprintf(stderr,"\b\f");
               fprintf(stderr, "Libgcrypt error:\t%s:%s",
                       gcry_strsource(error),
                       gcry_strerror(error)
                      );
               fprintf(stderr,"\n");
               exit(EXIT_FAILURE);
         }
}

static void
configurar_llave_cifrado(gcry_cipher_hd_t *hd)
{	
	exit_if(!hd);
        /**
         * Dependiendo el modo de cifrado, se podría llegar a ocupar
         * un vector de longitud K:
         * char vector_inicial[LONGITUD_K] = {0};
         * memset(vector_inicial,0,LONGITUD_K);
         */
        size_t tam_key  = gcry_cipher_get_algo_keylen(AES);
        /* printf("\nTam_key = %d\n", (int) tam_key); */
        gcry_error_t error =  gcry_cipher_setkey(*hd, PASSWORD, tam_key);
        evaluar_error (error);
}

static gcry_cipher_hd_t 
crear_manejador_seguro (void)
{
        gcry_cipher_hd_t hd = 0;
	gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
        gcry_control(GCRYCTL_INIT_SECMEM, SEC_MEM_POOL, 0); /* 16kb */
        gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
        gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
        exit_if(!gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P));
        evaluar_error(gcry_cipher_open(&hd, AES, MODE, FLAG));
        configurar_llave_cifrado(&hd);
        return hd;
}

static void
seguridad_archivo(char *nombre_archivo,char *salida,
                  gcry_error_t(*cripto)()) 
{
	/* Sobre-escribir un vector no es permitido por Libgcrypt */
        exit_if(!nombre_archivo || !salida || !strcmp(nombre_archivo,salida));
        FILE *archivo = fopen(nombre_archivo,"rb");
        FILE *nuevo_archivo = fopen(salida,"wb");
        exit_if(!archivo || !nuevo_archivo);
        int lectura = 0;
        char x[BYTES] = "\0";
	char y[BYTES] = "\0";
        gcry_cipher_hd_t hd = crear_manejador_seguro();
	do{
	   lectura = fread(x,1,BYTES,archivo);
	   exit_if(lectura < 0);
	   evaluar_error(cripto(hd,y,lectura,x,lectura));
	   fwrite(y,lectura,1,nuevo_archivo);
	   memset(x,0,BYTES);
	   memset(y,0,BYTES);
	}while(lectura > 0);
	fclose(archivo);
	fclose(nuevo_archivo);
	archivo = NULL;
	nuevo_archivo = NULL;
        liberar_manejador_seguro(&hd);
}

void
cifrar_archivo(char *x,char *y)
{
	seguridad_archivo(x,y,gcry_cipher_encrypt);
}

void
des_cifrar_archivo(char *x,char *y)
{
	seguridad_archivo(x,y,gcry_cipher_decrypt);
}

