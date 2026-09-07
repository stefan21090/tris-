#include <stdio.h>
char tabella[3][3]; // tabella dichiarata globalmente
void tabellaIniziale(); //tabella inizializzata vuota
void stampa_tabella(); // stampa la tabella aggiornata di volta in volta
int controlloVincitore(char player); // controlla il vincitore
int MossaValida(int riga, int colonna, int mosse, int player); /*se il giocatore inserisce una casella 
non valida, la mossa si considera non valida.*/

int main() {
int riga, colonna;
char player = 'X';
int mosse = 0; // conteggio delle mosse
tabellaIniziale();

while(1) { //while(1) perchè finchè il controllo vincitore non restituisce 0, il gioco non finisce, salvo pareggio
    stampa_tabella();
    printf("Giocatore %c, inserisci la riga e la colonna (da 1 a 3): ", player);
    scanf("%d %d", &riga, &colonna);
    MossaValida(riga, colonna, mosse, player);
    if(controlloVincitore(player)) {
        stampa_tabella();
        printf("Giocatore %c ha vinto!\n", player);
        break;
    } else if(mosse == 9) {
        stampa_tabella();
        printf("Pareggio!\n");
        break;
    }
    player = (player == 'X') ? 'O' : 'X'; // passa il turno al prossimo giocatore
}
return 0;
}

void tabellaIniziale() 
{
for(int i = 0; i < 3; i++) {
  for(int j = 0; j < 3; j++) {
     tabella[i][j] = ' ';
  }
 }
}

void stampa_tabella() {
printf("\n");
for(int i = 0; i < 3; i++) {
 printf(" %c | %c | %c \n", tabella[i][0], tabella[i][1], tabella[i][2]);
 if(i < 2) {
     printf("---|---|---\n");
  } 
}
printf("\n");
}

int controlloVincitore(char player)
{
for(int i = 0; i < 3; i++) {
 if((tabella[i][0] == player && tabella[i][1] == player && tabella[i][2] == player) || (tabella[0][i] == player && tabella[1][i] == player && tabella[2][i] == player)) {
 return 1;
}
}
if((tabella[0][0] == player && tabella[1][1] == player && tabella[2][2] == player) || (tabella[0][2] == player && tabella[1][1] == player && tabella[2][0] == player)) {
return 1;
}
return 0;
}

int MossaValida(int riga, int colonna, int mosse, int player){
if(riga >= 1 && riga <= 3 && colonna >= 1 && colonna <= 3 && tabella[riga-1][colonna-1] == ' ') {
        tabella[riga-1][colonna-1] = player;
        mosse++;
    } else {
        printf("Mossa non valida. Riprova.\n");
    }
	return 0;
}	
