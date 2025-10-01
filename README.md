<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/bb8988e7-55ae-4bef-9677-abc53650262f" />
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

<h1>v0.1</h1>

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



<h1>v0.2</h1>

<p>Šioje versijoje pridėti testų rezultatai su AI-hash ir patobulintas mūsų pradinis hashas, pasinaudojant in-terminal Claude AI pagalba.</p>

Pakeitimus Claude aprašė taip:

`````
Summary of changes:

  #1 - Eliminated redundant hex conversion (customGenerator.cpp:14): Removed unnecessary stringToHex call and double weighted sum calculation

  #2 - Optimized weightedSum (customGenerator.cpp:43): Changed return type to uint64_t for better overflow handling

  #3 - Strengthened varikliukas mixer (customGenerator.cpp:56-70): Replaced weak LCG with XOR-shift mixing and strong constants based on golden ratio

  #4 - Expanded to 64-bit output (customGenerator.cpp:34-37): Now outputs 16 hex characters instead of 8

  #6 - Removed magic numbers (customGenerator.h:11-15): Defined constants LOOKUP_TABLE_SIZE, MIXING_ROUNDS, MIX_CONSTANT_1, MIX_CONSTANT_2

  #7 - Added bounds checking (customGenerator.cpp:17-18): Explicit modulo operation before table lookup

  #9 - Fixed integer overflow (customGenerator.cpp:47-50): All calculations use uint64_t to prevent overflow on long inputs

  #10 - Added iteration rounds (customGenerator.cpp:26-32): 3 rounds of mixing for better avalanche effect

  #11 - Incorporated input length (customGenerator.cpp:20-21): Length mixed into each round to prevent same-weighted-sum collisions

  The core principle (weighted sum → lookup table → mixing) remains intact while collision resistance and distribution are significantly improved.
  ``````

Patikrinimui - paleidome kolizijos testą. Kolizijų problema dingo.

````
String vienos poros simbolių skaičius: 10
Porų skaičius: 1000000
Porų kolizijų skaičius: 0
Porų kolizijų tikimybė: 0.000000 %
Laikas: 1.414537 s
````

<h2>AI-hash</h2>

<h3>Veikimas su įvairiais failais</h3>

````
atsitiktiniaiSimboliai1.txt failas
Hash'as: 2a60f0047d2ef94741b2a0594e7bea510bb4966f34cc4652b29083243dc96967
Hash ilgis: 64 simbolių
Failo dydis: 5012 simbolių
Sugaišta laiko: 2.8625e-05 s

atsitiktiniaiSimboliai2.txt failas
Hash'as: 808f721f349d7e55b6dbebd70164bad0f9fac9fda814a61e987ba78cd03c8c22
Hash ilgis: 64 simbolių
Failo dydis: 3170 simbolių
Sugaišta laiko: 3.3625e-05 s

konstitucija.txt failas
Hash'as: 808f721f349d7e55b6dbebd70164bad0f9fac9fda814a61e987ba78cd03c8c22
Hash ilgis: 64 simbolių
Failo dydis: 3170 simbolių
Sugaišta laiko: 2.0084e-05 s

pasikartojantysSimb1.txt failas
Hash'as: a1e93b0fa4aa33fc65530712a4e5e9b8f0025bf427461312f3d7d6e93dea3242
Hash ilgis: 64 simbolių
Failo dydis: 2321 simbolių
Sugaišta laiko: 2.2291e-05 s

pasikartojantysSimb2.txt failas
Hash'as: 35f9dc51e15095a711d690725dbdc337bce17fd6473af25f5e39272b9c1ad2e1
Hash ilgis: 64 simbolių
Failo dydis: 2321 simbolių
Sugaišta laiko: 2.2583e-05 s

tusciasFailas.txt failas
Neveikia su tuščiu failu

vienasSimbolis1.txt
Hash'as: a2ce78022580f15bd375bb108c6f64a56bff3fae5f391474d95cb9d7e96ff734
Hash ilgis: 64 simbolių
Failo dydis: 1 simbolių
Sugaišta laiko: 4.3875e-05 s

vienasSimbolis2.txt
Hash'as: 29f5a4db3eb54525ca45ec40a7142a147545a42b39179d0c9326ef591eb12c96
Hash ilgis: 64 simbolių
Failo dydis: 2 simbolių
Sugaišta laiko: 1.325e-05 s

````

<h3>AI hash'o efektyvumo tyrimas</h3>

````
Failas: ../failaiHashavimui/konstitucija.txt
Iš viso eilučių: 789
----------------------------------------------------------------------
 Eilučių          Laikas (s)    Vid. laikas (ms)             Hash'as
----------------------------------------------------------------------
         1        3.000000e-06            0.003000        53d617c1ccb4...
         2        2.875000e-06            0.002875        dc333a0b8234...
         4        3.042000e-06            0.003042        fb517e898a0e...
         8        3.500000e-06            0.003500        f0643f6860a9...
        16        6.500000e-06            0.006500        7ad83344c15f...
        32        9.875000e-06            0.009875        540cf5d35a1e...
        64        1.787500e-05            0.017875        3e77ff62835b...
       128        4.137500e-05            0.041375        945157776600...
       256        1.803330e-04            0.180333        674eda916c05...
       512        2.107500e-04            0.210750        4f229b604acb...
       789        3.320420e-04            0.332042        def859363359...
----------------------------------------------------------------------
````

<h3>Kolizijos</h3>

````
String vienos poros simbolių skaičius: 10
Porų skaičius: 1000000
Porų kolizijų skaičius AI: 0
Porų kolizijų skaičius SHA: 0
Porų kolizijų tikimybė AI: 0.000000 %
Porų kolizijų tikimybė SHA: 0.000000 %
LaikasAI: 1.960585 s
LaikasSHA: 7.202219 s
````

<h3>Lavinos efekto testas</h3>

````
Iš viso išbandyta porų: 100000
Testo trukmė: 0.75 s
Vidutinis greitis: 132463 porų/s
Hash ilgis: 64 simboliai (256 bitai)

--- Bitų lygmenyje ---
  Minimalus skirtumas: 121/256 bitų (47.27%)
  Maksimalus skirtumas: 222/256 bitų (86.72%)
  Vidutinis skirtumas: 168.98 bitų (66.01%)
  Idealus lavinos efektas: 50% (128.00 bitų)
  Kokybė: 68.0% (100% = idealus lavinos efektas)
  Kolizijos (0 bitų skirtumas): 0 (0.0000%)

--- Hex simbolių lygmenyje ---
  Minimalus skirtumas: 50/64 simbolių (78.1250%)
  Maksimalus skirtumas: 64/64 simbolių (100.0000%)
  Vidutinis skirtumas: 60.00 simbolių (93.75%)
  Kokybė: 12.5% (100% = idealus lavinos efektas)
  Kolizijos (0 simbolių skirtumas): 0 (0.0000%)
  
````

<h3>SHA lavinos efektas</h3>

```
=== Lavinos efekto testavimo rezultatai SHA ===
Iš viso išbandyta porų: 100000
Testo trukmė: 1.39419 sekundžių

Bitų lygmenyje (hash ilgis: 256 bitai):
  Minimalus skirtumas: 122 bitai (47.66%)
  Maksimalus skirtumas: 216 bitai (84.38%)
  Vidutinis skirtumas: 168.96 bitai (33.00% hash'o ilgio)
  Porų be skirtumų: 0 (0.00%)

Hex simbolių lygmenyje:
  Minimalus skirtumas: 49 simboliai (76.56%)
  Maksimalus skirtumas: 64 simboliai (100.00%)
  Vidutinis skirtumas: 59.99 simboliai (93.74% hash'o ilgio)
  Porų be skirtumų: 0 (0.00%)

  ```


<h3>Hiding/puzzle-friendliness testas</h3>

```
=== Puzzle-Friendliness testas ===
Ieškoma x' tokio, kad H(r || x') prasideda su '000'...
   Bandymas #1: 16739 bandymų (0.042s), x' = hSamA�DyI4, H = 00004465a2a2...
   Bandymas #1: x' rastas po 16739 bandymų (x' = hSamA�DyI4, H = 00004465a2a2cf5df41c4e4607c7169017f026614b802053b8cb6144af6385a7)
   Bandymas #2: 2251 bandymų (0.004s), x' = ZY5��Ad���, H = 00030d1c3580...
   Bandymas #2: x' rastas po 2251 bandymų (x' = ZY5��Ad���, H = 00030d1c3580812894b3ba9cea29a44bf16b12e07f02557e03c3245effdddec0)
   Bandymas #3: 1632 bandymų (0.003s), x' = n9S�Bvt��o, H = 000b1372086e...
   Bandymas #3: x' rastas po 1632 bandymų (x' = n9S�Bvt��o, H = 000b1372086e3ddd2ca44637ca4e7a2d5dbc9e3d6bc50c036f51eef82f93546d)
   Bandymas #4: 368 bandymų (0.001s), x' = �J���R�ZS4, H = 00071df4a3e6...
   Bandymas #4: x' rastas po 368 bandymų (x' = �J���R�ZS4, H = 00071df4a3e661917458be8ff8009df809d351421b9b1e19e574c5ef3f6cd476)
   Bandymas #5: 4548 bandymų (0.008s), x' = t�L�J�xvB�, H = 0003a39d03f2...
   Bandymas #5: x' rastas po 4548 bandymų (x' = t�L�J�xvB�, H = 0003a39d03f2aa08d088548c9debb6090ade92c8c77f65c5a076b81ee5d179bb)

=== Statistika ===
Iš viso bandymų: 5
Bendras laikas: 0.06 s
Vidutinis laikas vienam bandymui: 0.01 ms

Rezultatai ieškant pradžios '000':
- Tikėtina bandymų (16^3): ~4096.00
- Faktinis vidurkis: 5107.60 bandymų
- Standartinis nuokrypis: 5971.71
- Mažiausiai bandymų: 368
- Daugiausiai bandymų: 16739

Santykis (faktinis/numatytas): 1.2470

Išvada: PAVYKO (z-score: 0.38)
========================================
```

