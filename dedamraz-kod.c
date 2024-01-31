#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define BROJ_PATULJAKA 9
#define BROJ_IRVASA 9

int patuljci;
int irvasi;

sem_t* dedaMraz;
sem_t* irvasSemafor;
sem_t* patuljakSemafor;
sem_t* mutex;

int patuljciPomocna = 0;

void *dedaMrazFunkcija (void *arg) {
    printf("Deda Mraz nit je pokrenuta!\n");

    while (1) {

        if(patuljciPomocna == BROJ_PATULJAKA) break;

        sem_wait(dedaMraz);
        sem_wait(mutex);

        if (irvasi == BROJ_IRVASA) {

            printf("Deda Mraz priprema sanke\n");
            for (int r=0; r<BROJ_IRVASA; r++) sem_wait(irvasSemafor);

            printf("Sanke su pripremljene!\n");
            irvasi = 0;

        } else {
            if(patuljci > 0) printf("Deda Mraz pomaze svim patuljcima koji su trazili pomoc\n");
            for(int i = 0; i < patuljci; i++) sem_post(patuljakSemafor);
            patuljci = 0;
        }

        sem_post(mutex);
    }

    return arg;
}

void *irvasiFunkcija (void *arg) {

    int id = *(int*) arg;
    printf("Irvas broj %d je pokrenut\n",id+1);

    sem_wait(mutex);
    
    irvasi++;
    if (irvasi == BROJ_IRVASA) sem_post(dedaMraz);

    sem_post(mutex);
    sem_post(irvasSemafor);
    printf("Irvas se prikljucuje Deda Mrazu\n");
    sleep(2);
    return arg;

}

void *patuljakFunkcija (void *arg) {

    int id = *(int*) arg;

    printf("Patuljak broj %d je pokrenut\n",id+1);

    int pomoc = rand()%10;

    if (pomoc>5) {
        sem_wait(mutex);
        patuljci++;

        if (patuljci == 3) sem_post(dedaMraz);
        printf("Patuljak broj %d trazi pomoc od Deda Mraza\n",id+1);

        sem_post(mutex);

        sem_wait(patuljakSemafor);
        sleep(3);

    }

    sem_wait(mutex);
    patuljciPomocna++;
    if (BROJ_PATULJAKA < patuljciPomocna + 2) sem_post(dedaMraz);
    sem_post(mutex);
    
    printf("Patuljak broj %d radi svoj posao\n",id+1);
    sleep(2);
    return arg;

}

int main (void) {

    patuljci = 0;
    irvasi = 0;

    dedaMraz = sem_open("Deda Mraz",O_CREAT,0644,0);
    irvasSemafor = sem_open("Irvasi",O_CREAT,0644,0);
    patuljakSemafor = sem_open("Patuljci",O_CREAT,0644,0);
    mutex = sem_open("Mutex",O_CREAT,0644,0);

    sem_init(dedaMraz, 0, 0);
    sem_init(irvasSemafor, 0, 0);
    sem_init(patuljakSemafor,0,0);
    sem_init(mutex,0,1);

    pthread_t dedaMrazNit;
    pthread_create(&dedaMrazNit, NULL, dedaMrazFunkcija, NULL);

    int irvasiNiz[BROJ_IRVASA];
    for(int i=0;i<BROJ_IRVASA;i++) irvasiNiz[i]=i;

    pthread_t irvasiNiti[BROJ_IRVASA];
    for (int i=0; i<BROJ_IRVASA; i++) pthread_create(&irvasiNiti[i], NULL, irvasiFunkcija, (void*)&irvasiNiz[i]);
    
    int patuljciNiz[BROJ_PATULJAKA];
    for(int i=0;i<BROJ_PATULJAKA;i++) patuljciNiz[i]=i;
    
    pthread_t patuljciNiti[BROJ_IRVASA];
    for (int i=0; i<BROJ_PATULJAKA; i++) pthread_create(&patuljciNiti[i], NULL, patuljakFunkcija, (void*)&patuljciNiz[i]);

    for(int i = 0; i < BROJ_PATULJAKA; i++) pthread_join(patuljciNiti[i], NULL);
    for(int i = 0; i < BROJ_IRVASA; i++) pthread_join(irvasiNiti[i], NULL);
    

    pthread_join(dedaMrazNit,NULL);
    printf("\nKraj!");

    sem_close(dedaMraz);
    sem_unlink("Deda Mraz");
    sem_destroy(dedaMraz);

    sem_close(irvasSemafor);
    sem_unlink("Irvasi");
    sem_destroy(irvasSemafor);

    sem_close(patuljakSemafor);
    sem_unlink("Patuljci");
    sem_destroy(patuljakSemafor);

    sem_close(mutex);
    sem_unlink("Mutex");
    sem_destroy(mutex);

    return 0;
}
