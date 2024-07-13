# minitalk

![](https://miro.medium.com/v2/resize:fit:4800/format:webp/1*5CEknZjCQrX1A1aEVRa-Pw.png)

## Comment fonctionne Minitalk ?
La communication entre le client et le serveur est réalisée à l'aide de signaux UNIX .

Le client convertit chaque caractère du message en 8 bits (1 octet) et les envoie au serveur un par un.

## Client
1. Le client lit le PID du serveur et le message à partir des arguments de la ligne de commande.
2. Il itère sur chaque caractère du message.
3. Pour chaque caractère, il appelle la send_signalfonction, qui va convertir le caractère en 8 bits et envoyer chaque bit comme signal au serveur. Il utilise SIGUSR1pour représenter un 1bit et SIGUSR2 pour représenter un 0bit.
4. Après l'envoi de chaque bit, le client attend une courte durée (42 microsecondes) à l'aide de la usleepfonction. Ce délai permet au serveur de traiter les signaux reçus.
## Serveur
1. Le serveur commence par afficher son PID sur la console.
2. Il configure les gestionnaires de signaux et SIGUSR1 les SIGUSR2 signaux utilisant la signalfonction.
3. Le serveur entre dans une boucle infinie et attend des signaux à l'aide de la pausefonction.
4. Lorsqu'un signal est reçu, le gestionnaire de signal correspondant ( handl_signal) est appelé.
5. La handle_signal fonction extrait la valeur du bit (0 ou 1) du signal reçu et l'ajoute au caractère en cours de réception .
6. Si le caractère est entièrement reçu (8 bits), il est affiché sur la console à l'aide deft_printf . L'index de bit et le caractère actuel sont réinitialisés pour préparer le caractère suivant.
7. (Bonus uniquement) Après avoir traité le signal reçu, le serveur renvoie un signal au client . Si le signal reçu était SIGUSR1, il envoie SIGUSR1pour accuser réception du bit reçu. Si le signal reçu était SIGUSR2, il renvoie SIGUSR2.

## Fonctionnalités bonus
Le code source fourni inclut une version bonus ( client_bonus.cet server_bonus.c) qui ajoute des fonctionnalités supplémentaires :

- Les caractères Unicode comme 🦁 sont déjà pris en charge dans la partie obligatoire.
- Le renvoi d'un accusé de réception de lecture peut être réalisé en utilisant la sigactionstructure, qui permet d'accéder aux métadonnées sur la transmission du signal.
- Le client affiche ensuite un message sur la console pour chaque bit reconnu. Il affiche « Reçu bit 1 » pour SIGUSR1 et « Reçu bit 0 » pour SIGUSR2. Cela peut aider à visualiser le processus de communication.
## Comment faire du Minitalk ?
```
Pour rester concis, nous analyserons uniquement les 2 fonctions principales de la partie obligatoire .
```
send_signal<em><strong>(client)<em><strong>.

```client

void  send_signal ( int pid, unsigned  char caractère)
 {
 int     i;
 unsigned  char temp_char;

i = 8 ;
temp_char = caractère;
 while (i > 0 )
{
  i--;
  temp_char = caractère >> i;
  if (temp_char % 2 == 0 )
   kill(pid, SIGUSR2);
  else
    kill(pid, SIGUSR1);
  usleep( 42 );
}
}
```
Cette fonction utilise d’abord un `temp_char` tampon intermédiaire pour lire chaque bit characterun par un.

A chaque itération, `temp_char` la valeur de `character` décalée est attribuée aux bons `i` instants.

Disons que nous voulons lire <em><strong>01100001<em><strong> bit par bit, en commençant par <em><strong>le bit le plus significatif<em><strong> (à gauche).

Nous décalons d’abord la valeur de charactervers la droite 7 fois, ce qui nous donne 0000000 0 .

```
⚠️ Remarque : le <em><strong> bit le moins significatif (à droite) détermine si un nombre est pair ou impair . Si le bit le moins significatif est 1 , le nombre est impair . Si le bit le moins significatif est 0 , le nombre est pair <em><strong>.
```
Nous calculons ensuite temp_char % 2, ce qui révèle si le 
nombre est<em><strong> impair<em><strong> (LSB = 1) ou <em><strong> pair<em><strong> ( LSB = 0) .

Dans ce cas, temp_char % 2 c'est 0, nous envoyons donc un SIGUSR2 signal au serveur, qui l'interprétera comme un bit 0.

Nous<em><strong> décalons ensuite la valeur decharacter<em><strong> vers la droite 6 fois, ce qui nous donne 000000<em><strong> 01<em><strong> .

Dans ce cas, temp_char % 2 c'est 1, donc nous envoyons un SIGUSR1 signal au serveur, qui l'interprétera comme un bit 1.

Nous répétons ce processus jusqu'à ce que nous ayons envoyé les 8 bits.

handle_signal<em><strong>(serveur)<em><strong>.
```
void  handle_signal ( int signal)
 {
 statique  unsigned  char current_char;
 statique  int     bit_index;

current_char |= (signal == SIGUSR1);
bit_index++;
 si (bit_index == 8 )
{
  si (current_char == FIN_TRANSMISSION)
   ft_printf( "\n" );
  sinon
    ft_printf( "%c" , current_char);
  bit_index = 0 ;
  current_char = 0 ;
}
 sinon
   current_char <<= 1 ;
}
```

Cette fonction utilise deux variables statiques :
```
caractère non signé  statique current_char ; int
statique      bit_index;
```

L'utilisation de variables statiques nous permet de conserver les informations même après la fin de l'exécution de la fonction.

- current_charstocke le caractère en cours de réception.
- bit_indexstocke l'index du bit en cours de réception.
Ensuite, la ligne suivante extrait la valeur du bit (0 ou 1) du signal reçu de manière très condensée :**

```
caractère_courant |= (signal == SIGUSR1);
```

-  Le résultat (signal == SIGUSR1)sera soit 00000000 pour faux, soit 00000001 pour vrai.
-  L' |=opérateur est un opérateur d'affectation de type OU au niveau du bit. Il compare deux octets dans leur représentation binaire et, pour chaque bit, attribue 0 si les deux bits sont 0, et 1 sinon.

![](https://miro.medium.com/v2/resize:fit:1400/format:webp/1*j5rQ6VYibVsq1mZrpCsyrw.png)

-  En répétant cette opération et en la décalant vers la gauche, nous: pourrons stocker le caractère entier dans `current*char`.
