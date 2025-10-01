<h1>LIDL HASHAS<h1>
<p>Šis ranka kurtas hashas kaip vieną iš savo unikalių savybių naudoja "LIDL" prekių kodus (juos galima rasti <a href="https://www.lidl.lt/static/assets/NMP-ispardavimas-parduotuvese-182_185_175-1-673101.pdf">čia</a>). Hash'o pseudokodas pateikiamas žemiau:</p>

<p>Hash'o pseudokodas:</p>

```
1. Skaičiuojama svertinė įvesties simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
2. Gautas skaičius naudojamas kaip indeksas į Maximos prekių kodų masyvą
3. Maximos prekės kodas naudojamas kaip seed (custom linear generatoriui)
4. Įvestis verčiama į hex ir paskaičiuojama svertinė hex simbolių suma: c₁×1 + c₂×2 + c₃×3 + ...
5. Gautas skaičius naudojamas kaip offset (custom linear generatoriui)
6. Custom linear generatorius naudoja seed ir offset, kad gautų hash'o reikšmę (output verčiamas į hex)
7. Gaunamas 8 simbolių hex stringas, kuris ir yra hashas
```

<h1>Savybės</h1>
<h2>Veikimas su įvairiais failais<h2>
<h2>Efektyvumo tyrimas<h2>
<h2>Kolizijų paieška<h2>
<h2>Lavinos efekto testas<h2>
<h2>Hiding/puzzle-friendliness testas<h2>

