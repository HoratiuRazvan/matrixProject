# matrixProject
Ideea jocului este de a face diverse calcule în baza 2. Am folosit o placă arduino une, o matrice de leduri(8X8) cu driver(cu rezistanta 10k, condensator 10 microF, 104 picoF), două butoane(cu doua rezistente de câte 10k), un display LCD si breadboard-urile necesare.
Cum decurge jocul:
La început setăm nivelul de dificultate dorit, cu ajutorul celor două butoane.După alegerea nivelului dorit apăsăm concomitent ambele butoane pentru începerea jocului. Avem două butoane: cel din stânga însemnand „true”, iar cel din dreapta „false”. Apoi sunt generate în funcție de nivelul de dificultate ales două numere în baza 2 pe liniile 1 și 5 ale matricei de leduri(led aprins însemnând 1, iar led stins 0) și un semn pe liniile dintre ele(„+” „-” „X”, ”/”). Scopul utilizatorului este de a introduce pe linia 7 a matricei de leduri, de la dreapta la stânga rezultatul obținut.
Spre exemplu, dacă primele 5 linii sunt de forma

0 0 0 0 1 0 1 0
0 0 0 1 0 0 0 0
0 0 1 1 1 0 0 0
0 0 0 1 0 0 0 0
0 1 0 0 1 0 0 1

Rezultatul obținut este:
0 1 0 1 0 0 1 1

În permanență pe ecran este afișat scorul si numărul de vieți. Scopul este de a obține un scor cât mai mare și de a ajunge până la urmă obișnuit cu transformările și calculele în baza 2.
ENJOY!

https://www.youtube.com/watch?v=YG53MLDDoww&feature=youtu.be
