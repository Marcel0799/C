/*
 * Vorgabe für die Aufgabe. Nicht modifizieren!
 */ 
/* Noetige Includes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "main.h"

int main (void) {
    /* Start-Status der beiden Mitarbeiter */
    mitarbeiter_a_status = andere_arbeit;
    mitarbeiter_b_status = andere_arbeit;
	/*
	 * Signalhandler fuer den Programmabruch registrieren.
	 * Bei z.B. CTRL-C aus der Shell wird die Funktion programm_abbruch ausgefuehrt.
	 */
	struct sigaction aktion;
	aktion.sa_handler = &programm_abbruch;
	aktion.sa_flags = 0;
	sigemptyset(&aktion.sa_mask);
	if (sigaction(SIGINT, &aktion, NULL) == -1) {
		perror("Konnte Signalhandler nicht setzen");
		exit(EXIT_FAILURE);
	}
	

	/*
	 * Semaphoren initialisieren.
	 */
    init_semaphores();

	/*
	 * Die Mitarbeiter-Threads werden nun erzeugt.
	 */
	if (pthread_create(&mitarbeiter_a_thread, NULL, &mitarbeiter_a, NULL) != 0) {
		perror("Konnte thread fuer Mitarbeiter A nicht erzeugen");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&mitarbeiter_b_thread, NULL, &mitarbeiter_b, NULL) != 0) {
		perror("Konnte thread fuer Mitarbeiter B nicht erzeugen");
		exit(EXIT_FAILURE);
	}

	/* 
	 * Der Vaterprozess uebernimmt die deadlock_erkennung.
	 */
	deadlock_erkennung();

	return 0;
}



/*
 * Die Funktion fuer einen Mitarbeiter-Thread.
 * Hier wird die andere Arbeit implementiert.
 */
void andere_arbeit_ausfuehren(char name) {
	static int i = 5;
	int dauer;

	/* 
	 * Mitarbeiter A arbeitet immer fuer 8 Zeiteinheiten, Mitarbeiter B fuer unterschiedliche Zeiteinheiten.
	 * Durch diesen zeitlichen Ablauf wird ein Deadlock provoziert.
	 */
	if (name == 'A') {
		printf("Mitarbeiter %c: Meine andere Arbeit dauert 8 Sekunden.\n", name);
		sleep(8);
	} else {
		if (i >= 8) {
			i = 0;
		}
		dauer = (8 - i);
		printf("Mitarbeiter %c: Meine andere Arbeit dauert %d Sekunden.\n", name, dauer);
		sleep(dauer);
		i+=6;
	}
}

/*
 * Die Funktion des Vaterprozesses.
 * Hier findet die deadlock_erkennung und -beseitigung statt.
 */
void deadlock_erkennung(void) {
	while (1) {
		sleep(12);
		check_for_deadlocks();
		 
	}
}

/*
 * Die Funktion, die bei einem programm_abbruch ausgefuehrt wird (z.B. bei
 * CTRL-C in der Shell). Hier werden die Mitarbeiter Threads abgebrochen und
 * die Semaphoren aufgeräumt.
 */
void programm_abbruch(int sig) {
	printf("Programm wurde abgebrochen.\n");
	
	/* Ueberpruefe ob Threads abgebrochen werden konnten */
	if (pthread_cancel(mitarbeiter_a_thread) == -1) {
		perror("Fehler beim Beenden der Threads");
		exit(EXIT_FAILURE);
	}
	if (pthread_cancel(mitarbeiter_b_thread) == -1) {
		perror("Fehler beim Beenden der Threads");
		exit(EXIT_FAILURE);
	}

	if (sem_destroy(&klausuren) == -1) {
		perror("Fehler beim Entfernen der Semaphore klausuren");
		exit(EXIT_FAILURE);
	}
	if (sem_destroy(&liste) == -1) {
		perror("Fehler beim Entfernen der Semaphore liste");
		exit(EXIT_FAILURE);
	}

    if (sem_destroy(&status) == -1) {
		perror("Fehler beim Entfernen der Semaphore status");
		exit(EXIT_FAILURE);
	}
	
	exit(0);
}
