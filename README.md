<img width="200" height="200" alt="image" src="https://github.com/user-attachments/assets/bb8988e7-55ae-4bef-9677-abc53650262f" />
<h1>LIDL hash</h1>

<p>Šis ranka kurtas hashas kaip vieną iš savo unikalių savybių naudoja "LIDL" prekių kodus (juos galima rasti <a href="https://www.lidl.lt/static/assets/NMP-ispardavimas-parduotuvese-182_185_175-1-673101.pdf">čia</a>). Hash'o pseudokodas pateikiamas žemiau: </p>

## Hash'o pseudokodas

1. Skaičiuojama svertinė įvesties simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
2. Gautas skaičius naudojamas kaip indeksas į Maximos prekių kodų masyvą
3. Maximos prekės kodas naudojamas kaip seed (custom linear generatoriui)
4. Įvestis verčiama į hex ir paskaičiuojama svertinė hex simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
5. Gautas skaičius naudojamas kaip offset (custom linear generatoriui)
6. Custom linear generatorius naudoja seed ir offset, kad gautų hash'o reikšmę (output verčiamas į hex)
7. Gaunamas 8 simbolių hex stringas, kuris ir yra hashas

# v0.1 hash'o versijos testavimas
 ### Tyrimas testuoja hash:
 - Deterministiškumą;
 - Efektyvumą;
 - Atsparumą kolizijoms;
 - Lavinos efektą (angl. _avalanche effect_)
 - Negrįžtamumą;

### Tyrimo metu naudoti failai 
| Failo pavadinimas | Savybės |
|--------- |  ------- |
| atsitiktiniaiSimboliai1.txt | failai su daug (>1000) atsitiktinių simbolių |
| atsitiktiniaiSimboliai2.txt | failai su daug (>1000) atsitiktinių simbolių |
| konstitucija.txt | Lietuvos Respublikos Konstitucija |
| pasikartojantysSimb1.txt | failai su daug (>1000) atsitiktinių simbolių, kurie skiriasi tik vienu (pvz. viduriniu) simboliu |
| pasikartojantysSimb2.txt | failai su daug (>1000) atsitiktinių simbolių, kurie skiriasi tik vienu (pvz. viduriniu) simboliu |
| tusciasFailas.txt | tusčias failas |
| vienasSimbolis1.txt | failai su vienu simboliu (pvz. a , b ) |
| vienasSimbolis2.txt | failai su vienu simboliu (pvz. a , b ) |


# Failų hashavimo rezultatai

| Failo pavadinimas | Hashas (angl. _hash value_) | Hashavimo laikas (s)|
| ------ | ------- | --------- |
| atsitiktiniaiSimboliai1.txt |  3b8b92c0 | 0.00113221 |
| atsitiktiniaiSimboliai2.txt |  b1666ac3 | 0.000782417 |
| konstitucija.txt |  b20d67ac | 0.0125679 |
| pasikartojantysSimb1.txt |  6ef3cafa | 0.0005755 |
| pasikartojantysSimb2.txt |  12e25fe9 | 0.000573916 |
| tusciasFailas.txt |  e2260bf6 | 1.2708e-05 |
| vienasSimbolis1.txt |  62438e48 | 8.916e-06 |
| vienasSimbolis2.txt |  60dc5c3e | 7.166e-06 |

# Efektyvumo tyrimas konstitucija.txt

| Eilučių skaičius | Hashas (angl. _hash value_) | Vidutinis hashavimo laikas (ms)|
| ------ | ------- | --------- |
| 1 |  d6ce781e | 0.018667 |
| 2 |  ae492895 | 0.028334 |
| 4 |  8449b63b | 0.046041 |
| 8 |  cfa877a9 | 0.078167 |
| 16 |  55922159 | 0.254958 |
| 32 |  407e2237 | 0.386208 |
| 64 |  edf96096 | 0.735334 |
| 128 |  363336af | 1.589500 |
| 256 |  6708c835 | 3.648292 |
| 512 |  a6e547e9 | 6.985041|
| Visos eilutės |  d18c9c3a | 9.464792 |


<img width="752" height="452" alt="image" src="https://github.com/user-attachments/assets/fe2fe6ed-9192-4dad-903e-ebe8934b7385" />


# Kolizijų paieška

Kolizijų testas atskleidė šio hasho silpnybę, nes visiškai kolizijų visgi neišvengiama - iš 100000 porų vidutiniškai (nustatyta iteruojant 3 kartus) sulaukiama 3 kolizijų:

- **String vienos poros simbolių skaičius:** 10
- **Porų skaičius:** 1000000
- **Porų kolizijų skaičius:** 3
- **Porų kolizijų tikimybė:** 0.000300 %
- **Laikas:** 3.052459 s

# Lavinos efekto (angl. _avalanche effect_) testas
 | Išbandyta porų | 100000 |
 | ---- | ---- |
 | Testo trukmė | 1.42 s |
 | Hash dydis | 8 hex simboliai (32 bitai) |

<table>
  <tr>
    <td></td>
    <td> <h2>Hex simbolių lygmuo</h2></td>
    <td> <h2>Bitų lygmuo</h2></td>
  </tr>
    <tr>
    <td> <h3>Minimalus skirtumas</h3></td>
    <td> 0/8 simbolių (0.00%)</td>
    <td> 0/32 bitų (0.00%)</td>
  </tr>

  <tr>
    <td> <h3>Maksimalus skirtumas</h3></td>
    <td> 8/8 simbolių (100.00%) </td>
    <td> 27/32 bitų (84.38%) </td>
  </tr>

  <tr>
    <td> <h3>Vidutinis skirtumas</h3></td>
    <td>  7.48 simbolių (93.47%) </td>
    <td> 15.95 bitų (49.84%) </td>
  </tr>

  <tr>
    <td> <h3>0 simbolių skirtumas</h3></td>
    <td>  7 (0.0070%)</td>
    <td>  7 (0.0070%)</td>
  </tr>

  
  
</table>

 # Hiding/puzzle-friendliness testas

Testas atskleidė neblogas hiding ir puzzle friendliness savybes. Didelis standartinis nuokrypis parodė tai, jog hash'as neprognozuojamas. Klaustukai matomi dėl terminalo neperskaitomo ASCII (angl. _unreadable ASCII_).

## Hiding savybės testas

| Salt (r) | E��I�WwUe�OeaHJLWS�Y��rVm�Imn�q1 |
| ----- | ----- |
| Secret (x) | Slapta žinutė |
| H(r || x) | bafe0aed |

## Puzzle-Friendliness testas
### Ieškoma x' tokio, kad H(r || x') prasideda su '0'...

| Bandymo numeris | Bandymų sk. rasti x' | x' | H |
| ---- | ---- | ----- | ----- |
| 1 | 30 | ��qR�X�N�W | 0f3f00de |
| 2 | 13 | P�r6k�6w6A | 0fc92a1f |
| 3 | 8 | gd�N�HS�cT | 0f3f022b | 
| 4 | 16| �6kOc�NaJh | 02fe8082 |
| 5 | 45 | P�T���Od7I | 04460746 |
| 6 | 21 | �tt�m�yd�C | 06f945e3 |
| 7 | 1 | Z�C�EEHC�z | 06f9472e | 
| 8 | 1 | 7om�r��25� | 0fc92a0a | 
| 9 | 10 | �iH�0kv0�l | 0de54e4d |
| 10 | 37 | ůr�m�o�Qb | 0c5c4e18 |


   ### Statistika per 10 bandymų:
   - Tikėtina bandymų (16^1): ~16
   - Faktinis vidurkis: 18.20
   - Standartinis nuokrypis: 14.19
   - Mažiausiai bandymų: 1
   - Daugiausiai bandymų: 45
   - Santykis (faktinis/tikėtinas): 1.14




#  v0.2 hash'o versijos testavimas

Šioje versijoje pridėti testų rezultatai su AI-hash ir patobulintas mūsų pradinis hashas, pasinaudojant in-terminal Claude AI pagalba.

Pakeitimus Claude aprašė taip:

-  Pašalinta perteklinė hex konversija (customGenerator.cpp:14): Pašalintas nereikalingas stringToHex kvietimas ir dvigubas svertinės sumos (angl. _weighted sum_) skaičiavimas
-  Optimizuota weightedSum (customGenerator.cpp:43): Pakeistas grąžinimo tipas į uint64_t geresniam perpildymo tvarkymui (angl. _overflow handling_)
-  Sustiprintas varikliukas mixer (customGenerator.cpp:56-70): Pakeistas silpnas LCG į XOR-shift maišymą ir stiprias konstantas pagrįstas aukso pjūviu (angl. _golden ratio_)
-  Išplėsta iki 64-bitų išvesties (customGenerator.cpp:34-37): Dabar išveda 16 hex simbolių vietoj 8
-  Pašalinti magiškai skaičiai (customGenerator.h:11-15): Apibrėžtos konstantos LOOKUP_TABLE_SIZE, MIXING_ROUNDS, MIX_CONSTANT_1, MIX_CONSTANT_2
-  Pridėta ribų patikra (angl. _bounds checking_) (customGenerator.cpp:17-18): Aiški modulo operacija prieš lentelės paiešką (angl. _explicit modulo operation before table lookup_)
-  Ištaisytas sveikųjų skaičių perpildymas (angl. _overflow_) (customGenerator.cpp:47-50): Visi skaičiavimai naudoja uint64_t perpildymo prevencijai ilguose įvestyse (angl. _prevent overflow on long inputs_)
-  Pridėti iteracijos raundai (customGenerator.cpp:26-32): 3 hashinimo raundai geresniam lavinos efektui (angl. _avalanche effect_)
-   Įtrauktas įvesties ilgis (customGenerator.cpp:20-21): Ilgis įmaišomas į kiekvieną raundą siekiant išvengti vienodos svertinės sumos kolizijų. Pagrindinis principas (svertinė suma → paieškos lentelė → maišymas) lieka nepakitęs, tuo tarpu kolizijų atsparumas ir pasiskirstymas yra žymiai pagerintas.
  
Patikrinimui - paleidome kolizijos testą. Kolizijų problema dingo.

- **String vienos poros simbolių skaičius:** 10
- **Porų skaičius:** 1000000
- **Porų kolizijų skaičius:** 0
- **Porų kolizijų tikimybė:** 0.000000 %
- **Laikas:** 1.414537 s

# Dirbtinio intelekto generuotas hash

## Failų hashavimo rezultatai

Testavimas darytas naudojant failus su kuriais buvo testuojamas ir mūsų kurtas hashas

| Failo pavadinimas | Hashas (angl. _hash value_) | Failo dydis | Hashavimo laikas (s)|
| ------ | ------- | --------- | ----- |
| atsitiktiniaiSimboliai1.txt |  2a60f0047d2ef94741b2a0594e7bea510bb4966f34cc4652b29083243dc96967 | 5012 simbolių |  2.8625e-05 |
| atsitiktiniaiSimboliai2.txt |  808f721f349d7e55b6dbebd70164bad0f9fac9fda814a61e987ba78cd03c8c22 | 3170 simbolių | 3.3625e-05 |
| konstitucija.txt |  808f721f349d7e55b6dbebd70164bad0f9fac9fda814a61e987ba78cd03c8c22 |3170 simbolių | 2.0084e-05 |
| pasikartojantysSimb1.txt |  a1e93b0fa4aa33fc65530712a4e5e9b8f0025bf427461312f3d7d6e93dea3242 | 2321 simbolių | 2.2291e-05 |
| pasikartojantysSimb2.txt |  35f9dc51e15095a711d690725dbdc337bce17fd6473af25f5e39272b9c1ad2e1 | 2321 simbolių | 2.2583e-05 |
| tusciasFailas.txt | - | - | - |
| vienasSimbolis1.txt |  29f5a4db3eb54525ca45ec40a7142a147545a42b39179d0c9326ef591eb12c96 | 64 simboliai | 4.3875e-05 |
| vienasSimbolis2.txt |  29f5a4db3eb54525ca45ec40a7142a147545a42b39179d0c9326ef591eb12c96 | 64 simboliai | 1.325e-05 |

## DI hash efektyvumo tyrimas

| Eilučių skaičius | Hashas (angl. _hash value_) | Vidutinis hashavimo laikas (ms)|
| ------ | ------- | --------- |
| 1 |  53d617c1ccb4... | 0.003000 |
| 2 |  dc333a0b8234... | 0.002875 |
| 4 |  fb517e898a0e... | 0.003042 |
| 8 |  f0643f6860a9... | 0.003500 |
| 16 |  7ad83344c15f... | 0.006500 |
| 32 |  540cf5d35a1e... | 0.009875 |
| 64 |   3e77ff62835b... | 0.017875 |
| 128 |  945157776600... | 0.041375 |
| 256 |  674eda916c05... | 0.180333 |
| 512 |   4f229b604acb... | 0.210750|
| Visos eilutės |  def859363359... | 0.332042 |

## Kolizijų paieška

- **String vienos poros simbolių skaičius:** 10
- **Porų skaičius:** 1000000
- **Porų kolizijų skaičius:** 0
- **Porų kolizijų tikimybė:** 0.000000 %
- **Laikas:**  1.960585 s


## Lavinos efekto (angl. _avalanche effect_) testas

 | Išbandyta porų | 100000 |
 | ---- | ---- |
 | Testo trukmė | 0.75 s |
 | Hash dydis | 64 simboliai (256 bitai) |

<table>
  <tr>
    <td></td>
    <td> <h2>Hex simbolių lygmuo</h2></td>
    <td> <h2>Bitų lygmuo</h2></td>
  </tr>
    <tr>
    <td> <h3>Minimalus skirtumas</h3></td>
    <td> 50/64 simbolių (78.1250%)</td>
    <td> 121/256 bitų (47.27%)</td>
  </tr>

  <tr>
    <td> <h3>Maksimalus skirtumas</h3></td>
    <td> 64/64 simbolių (100.0000%)</td>
    <td> 222/256 bitų (86.72%) </td>
  </tr>

  <tr>
    <td> <h3>Vidutinis skirtumas</h3></td>
    <td>  60.00 simbolių (93.75%) </td>
    <td> 168.98 bitų (66.01%) </td>
  </tr>

  <tr>
    <td> <h3>0 simbolių skirtumas</h3></td>
    <td>  0 (0.0000%)</td>
    <td>   0 (0.0000%)</td>
  </tr>

  
  
</table>

## Hiding/Puzzle-Friendliness savybės testas

### Ieškoma x' tokio, kad H(r || x') prasideda su '000'...

| Bandymo numeris | Bandymų sk. rasti x' | x' | H |
| ---- | ---- | ----- | ----- |
| 1 | 16739 | hSamA�DyI4 | 00004465a2a2cf5df41c4e4607c7169017f026614b802053b8cb6144af6385a7 |
| 2 | 2251 |ZY5��Ad��� | 00030d1c3580812894b3ba9cea29a44bf16b12e07f02557e03c3245effdddec0 |
| 3 | 1632 | n9S�Bvt��o | 000b1372086e3ddd2ca44637ca4e7a2d5dbc9e3d6bc50c036f51eef82f93546d | 
| 4 | 368| �J���R�ZS4 | 00071df4a3e661917458be8ff8009df809d351421b9b1e19e574c5ef3f6cd476 |
| 5 | 4548 | t�L�J�xvB� | 0003a39d03f2aa08d088548c9debb6090ade92c8c77f65c5a076b81ee5d179bb |

| Iš viso bandymų | 5 |
| --- | --- |
| Bendras laikas | 0.06 s |
| Vidutinis laikas vienam bandymui | 0.01 ms |

### Rezultatai ieškant pradžios '000':
- **Tikėtina bandymų (16^3):** ~4096.00
- **Faktinis vidurkis:** 5107.60 bandymų
- **Standartinis nuokrypis:** 5971.71
- **Mažiausiai bandymų:** 368
- **Daugiausiai bandymų:** 16739

# v0.2 ir kursiokų (Nika ir Anastasija) AES hashų palyginimai

### Išvedimo ilgis 
| AES hash | v0.2 |
| ---- | ----- |
| 32 simboliai (128 bitai) | 16 simbolių (64 bitai) |

### Deterministiškumas
| AES hash | v0.2 |
| ---- | ----- |
| Deterministinis | Deterministinis |

### Kolizijos
Porų skaičius: 1000000, vieno string poroje ilgis: 10
| AES hash | v0.2 |
| ---- | ----- |
| 0.000000 % | 0.000000 % |

### Lavinos efektas 


<table>
 <tr>
  <td></td>
  <td><h2>AES HEX</h2></td>
  <td><h2>v0.2 HEX</h2></td>
 </tr>

 <tr>
  <td><h3>MIN</h3></td>
  <td>68.75%</td>
  <td>78.1250%</td>
 </tr>

 <tr>
  <td><h3>VID</h3></td>
  <td>93.77%</td>
  <td>93.75%</td>
 </tr>

 <tr>
  <td><h3>MAX</h3></td>
  <td>100.00%</td>
  <td>100.00%</td>
 </tr>
 
</table>

<table>
 <tr>
  <td></td>
  <td><h2>AES BIT</h2></td>
  <td><h2>v0.2 BIT</h2></td>
 </tr>

 <tr>
  <td><h3>MIN</h3></td>
  <td>31.25%</td>
  <td>47.27%</td>
 </tr>

 <tr>
  <td><h3>VID</h3></td>
  <td>50.00%	</td>
  <td>66.01%</td>
 </tr>

 <tr>
  <td><h3>MAX</h3></td>
  <td>67.97%</td>
  <td>86.72%</td>
 </tr>
 
</table>


