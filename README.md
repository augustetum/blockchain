<img width = 200, src="https://logoeps.com/wp-content/uploads/2013/12/lidl-supermarkets-vector-logo.png">
<h1>LIDL hashas</h1>


<p>Šis ranka kurtas hashas kaip vieną iš savo unikalių savybių naudoja "LIDL" prekių kodus (juos galima rasti <a href="https://www.lidl.lt/static/assets/NMP-ispardavimas-parduotuvese-182_185_175-1-673101.pdf">čia</a>). Hash'o pseudokodas pateikiamas žemiau: </p>

<p>Hash'o pseudokodas:</p>

````
1. Skaičiuojama svertinė įvesties simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
2. Gautas skaičius naudojamas kaip indeksas į Maximos prekių kodų masyvą
3. Maximos prekės kodas naudojamas kaip seed (custom linear generatoriui)
4. Įvestis verčiama į hex ir paskaičiuojama svertinė hex simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
5. Gautas skaičius naudojamas kaip offset (custom linear generatoriui)
6. Custom linear generatorius naudoja seed ir offset, kad gautų hash'o reikšmę (output verčiamas į hex)
7. Gaunamas 8 simbolių hex stringas, kuris ir yra hashas
````

<h1>Savybės</h1>
<h2>Veikimas su įvairiais failais</h2>
  Hash'as buvo ištestuotas su visais testiniais failais, kuriuos galima rasti repozitorijos "failaiHashavimui" folderyje. Čia pasimato ir deterministiškumo savybė, nes kiekvienas failas buvo hashuotas tris kartus (pateikiamas trijų bandymų laikų vidurkis) ir visada buvo gaunamas tas pats hashas. Tušti ir vieno simbolio failai taip pat sėkmingai hashuojami, o dideli failai (konstitucija.txt) taip pat greitai apdorojami.
  
  Rezultatai:
  
````
  atsitiktiniaiSimboliai1.txt failas
  3b8b92c0
  Hashavimas truko: 0.00113221 s

  atsitiktiniaiSimboliai2.txt failas
  b1666ac3
  Hashavimas truko: 0.000782417 s

  konstitucija.txt failas
  b20d67ac
  Hashavimas truko: 0.0125679 s

  pasikartojantysSimb1.txt failas
  6ef3cafa
  Hashavimas truko: 0.0005755 s

  pasikartojantysSimb2.txt failas
  12e25fe9
  Hashavimas truko: 0.000573916 s

  tusciasFailas.txt failas
  e2260bf6
  Hashavimas truko: 1.2708e-05 s

  vienasSimbolis1.txt failas
  62438e48
  Hashavimas truko: 8.916e-06 s

  vienasSimbolis2.txt failas
  60dc5c3e
  Hashavimas truko: 7.166e-06 s

````

<h2>Efektyvumo tyrimas</h2>

````
Failas: ../failaiHashavimui/konstitucija.txt
Iš viso eilučių: 789
------------------------------------------------------------
 Eilučių          Laikas (s)    Vid. laikas (ms)        Hash'as
------------------------------------------------------------
         1        1.866700e-05            0.018667       d6ce781e
         2        2.833400e-05            0.028334       ae492895
         4        4.604100e-05            0.046041       8449b63b
         8        7.816700e-05            0.078167       cfa877a9
        16        2.549580e-04            0.254958       55922159
        32        3.862080e-04            0.386208       407e2237
        64        7.353340e-04            0.735334       edf96096
       128        1.589500e-03            1.589500       363336af
       256        3.648292e-03            3.648292       6708c835
       512        6.985041e-03            6.985041       a6e547e9
       789        9.464792e-03            9.464792       d18c9c3a
------------------------------------------------------------
````
Hashavimo laiko priklausomybė nuo eilučių kiekio pateikiama diagramoje:
<img width="600" height="371" alt="Eilučių kiekio ir laiko santykis" src="https://github.com/user-attachments/assets/cd405688-fa3b-42b0-b15d-ae5aadb0acfc" />



<h2>Kolizijų paieška</h2>
Kolizijų testas atskleidė šio hasho silpnybę, nes visiškai kolizijų visgi neišvengiama - iš 100000 porų vidutiniškai sulaukiama 3 kolizijų:

````
String vienos poros simbolių skaičius: 10
Porų skaičius: 1000000
Porų kolizijų skaičius: 3
Porų kolizijų tikimybė: 0.000300 %
Laikas: 3.052459 s

(trijų iteracijų vidutiniai rezultatai)
````

<h2>Lavinos efekto testas</h2>
Nors rezultatai čia neblogi, visgi sulaukiame dar nemažai kolizijų.

````
Iš viso išbandyta porų: 100000
Testo trukmė: 1.42 s
Hash'o dydis: 8 hex simboliai (32 bitai)

--- Bitų lygmenyje ---
  Minimalus skirtumas: 0/32 bitų (0.00%)
  Maksimalus skirtumas: 27/32 bitų (84.38%)
  Vidutinis skirtumas: 15.95 bitų (49.84%)
  0 bitų skirtumas: 7 (0.0070%)

--- Hex simbolių lygmenyje ---
  Minimalus skirtumas: 0/8 simbolių (0.00%)
  Maksimalus skirtumas: 8/8 simbolių (100.00%)
  Vidutinis skirtumas: 7.48 simbolių (93.47%)
  0 simbolių skirtumas: 7 (0.0070%)
````

<h2>Hiding/puzzle-friendliness testas</h2>
Testas atskleidė neblogas hiding ir puzzle friendliness savybes. Didelis standartinis nuokrypis parodė tai, jog hash'as neprognozuojamas. Klaustukai matomi dėl terminalo unreadable ASCII.

````

=== Hiding savybės testas ===
   Salt (r): E��I�WwUe�OeaHJLWS�Y��rVm�Imn�q1
   Secret (x): Slapta žinutė
   H(r || x): bafe0aed

=== Puzzle-Friendliness testas ===
Ieškoma x' tokio, kad H(r || x') prasideda su '0'...
   Bandymas #1: x' rastas po 30 bandymų (x' = ��qR�X�N�W, H = 0f3f00de)
   Bandymas #2: x' rastas po 13 bandymų (x' = P�r6k�6w6A, H = 0fc92a1f)
   Bandymas #3: x' rastas po 8 bandymų (x' = gd�N�HS�cT, H = 0f3f022b)
   Bandymas #4: x' rastas po 16 bandymų (x' = �6kOc�NaJh, H = 02fe8082)
   Bandymas #5: x' rastas po 45 bandymų (x' = P�T���Od7I, H = 04460746)
   Bandymas #6: x' rastas po 21 bandymų (x' = �tt�m�yd�C, H = 06f945e3)
   Bandymas #7: x' rastas po 1 bandymų (x' = Z�C�EEHC�z, H = 06f9472e)
   Bandymas #8: x' rastas po 1 bandymų (x' = 7om�r��25�, H = 0fc92a0a)
   Bandymas #9: x' rastas po 10 bandymų (x' = �iH�0kv0�l, H = 0de54e4d)
   Bandymas #10: x' rastas po 37 bandymų (x' = ůr�m�o�Qb, H = 0c5c4e18)

   Statistika per 10 bandymų:
   - Tikėtina bandymų (16^1): ~16
   - Faktinis vidurkis: 18.20
   - Standartinis nuokrypis: 14.19
   - Mažiausiai bandymų: 1
   - Daugiausiai bandymų: 45
   - Santykis (faktinis/tikėtinas): 1.14
   ````
