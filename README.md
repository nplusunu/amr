# AMR (Au Mai Ramas)
Aceasta aplicatie faciliteaza gestionarea zilelor libere (recuperari), obtinute pe parcursul activitatii, la servici.

## Structura
1. **Sumar**: Numarul de zile de recuperare disponibile.
2. **Actiuni**:
    - "+" Adaugare zile libere:
        - Data cand s-a lucrat.
        - Categoria: Liber de serviciu, Exercitiu, Alerta, Recompensa.
        - Numar zile care se adauga.
        - Detalii (optional).
    - "-" Utilizare zile libere:
        - Numar zile (recuperari) care se folosesc.
        - Detalii (optional).
3. **Istoric**: listare inregistrari efectuate anterior.

## Utilizare
Aplicatia se prezinta in trei variante.
- Install: varianta [instalabila](#amr---install) local, disponibila offline.
- Web UI: disponibila la adresa [amr.nplusunu.ro](https://amr.nplusunu.ro).
- REST API (Demo): disponibila alaturi de Web UI, la aceasi adresa, sub forma **[Wasm Console](#amr---wasm)**.

**Nota:** Aceasta aplicatie a continut si o versiune CLI, scrisa sub forma unor scripturi PHP, versiune ce a fost creata in scop pur academic, pentru a evidentia diferentele de executare client-side/server-side. Desi aceste scripturi au fost inlaturate de pe server, ele sunt in continuare pastrate in interiorul directorului ["retired"](https://github.com/nplusunu/amr/tree/main/retired), din cadrul prezentului repository.

### AMR - Install
Codul sursa poate fi obtinut prin downloadul arhivei Zip direct din prezentul repository, sau utilizand comanda git.
Instalarea aplicatiei consta in copierea locala a fisierului sursa **/bin/amr.cpp** , si compilarea acestuia. Pasii de mai jos descriu instalarea pe un setup Linux sau WSL:
- git clone https://github.com/nplusunu/amr.git
- cd <cale-catre-directorul-amr/bin/>
- g++ -o amr amr.cpp
- ./amr

Interactiunea cu ./amr se realizeaza prin selectarea unei optiuni numerice, din cadrul unui **Meniu**:

**1. Vizualizare intrari** - simuleaza un **GET /api/entries**, listand intrarile disponibile (**Istoric**), fiind populate implicit cu un mockup entry. Acest mockup serveste drept model de intrare si poarta si o notificare ca "Sistemul a pornit cu succes."

**2. Adaugare intrare noua** - simuleaza un **POST /api/entries**, adaugand o noua linie in Istoric, astfel:
- Utilizatorul alege Tipul: recuperare **obtinuta** (tastand "o") sau **utilizata** (tastand "u")
- Se introduce Data recuperarii in format AAAA-LL-ZZ
- Se alege Categoria: "liber" (implicit numarul de zile completat va fi 2), "exercitiu" (implicit 1 zi) sau "recompensa" (implicit 1 zi)
- Se completeaza optional campul de detalii

**3. Sumar** - simuleaza un **GET /api/balance**, indicand numarul de zile libere disponibile.

**4. Export catre fisier CSV** - aceasta optiune va crea un fisier **libere.csv**, servind ca modalitate de salvare a intrarilor, care altfel s-ar pierde la iesirea din aplicatie.

**5. Iesire**

AMR in varianta executabila local, este realizata in limbaj **C++**, fiind o scriere si adaptare a variantei javascript, facand uz de structuri de date si operatii cu fisiere (functia de export CSV).

### AMR - Wasm
Am folosit scrierea si adaptarea variantei Web la varianta Instalabila, drept prilej pentru a pregati dezvoltarea acestui program sub forma unui REST API. In acest context, cu ajutorul **WebAssembly**, am creat **Wasm Demo Console**, un mediu de lansare a comenzilor ce simuleaza aplicatia AMR sub forma de REST API.

**Nota:** WebAssembly (Wasm) este un runtime environment, o "masina virtuala" low-level ce permite executabilelor (precum /bin/amr) sa poata rula in interiorul unui website.
Fiind o masina virtuala, aceasta vine cu multe limitari, ceea ce a impus rescrierea aplicatiei noastre locale (amr.cpp), pentru a putea rula in interiorul consolei disponibile in interfata web.
Deasemenea, vorbim doar de un Demo de REST API, deoarece unul autentic presupune comunicarea HTTP, iar WebAssembly, ca si sandbox, nu poate acomoda asemenea comunicare. Pentru realizarea acestui Demo, a fost scris un engine.cpp, unde API "routes" au fost definite ca functii standard, utilizand structuri de date si liste.

Interactiunea cu AMR sub forma (simulata) de REST API, are loc in cadrul **Wasm Engine Demo Console (C++ Layer)**, in cadrul aplicatiei web [amr.nplusunu.ro](https://amr.nplusunu.ro), astfel:

**[ 1 ] GET entries** - utilizatorul tasteaza "1" pentru a vizualiza intrarile existente.
- aici nu mai avem un mockup entry, astfel cand nu este introdusa nici o intrare, va aparea mesajul: "(No entries found in Wasm Memory Stack)"

**[ 2 ] POST entry** - utilizatorul tasteaza "2" pentru a adauga o intrare noua.
- utilizarea acestei optiuni, se va face printr-un pop-up de input, introducand: tip ("earned" / "used"), data (YYYY-MM-DD), categorie ("liber" / "exercitiu" / "recompensa"), detalii (optional).
- datorita unui [bug](https://github.com/nplusunu/amr/issues/10) care se manifesta ca un infinite loop si pop-up-ul de input nu se mai inchide, pentru a iesi din pop-up trebuie selectata optiunea de "cancel".

Exemplu de input: *earned* [press OK] *2026-05-01* [press OK] *liber* [press OK] *Ziua Muncii* [press OK] **[press Cancel]**

- informatia adaugata astfel **NU** se retine, fiind disponibila pana la urmatorul Page Refresh.

**[ 3 ] GET balance** - utilizatorul tasteaza "3" pentru a obtine sumarul zilelor libere.

**NOTA:** Cum WebAssembly **NU** comunica prin HTTP, mesajele de HTTP (eg. "200 OK") sunt defapt cosmetizari, care sa simuleze existenta unui server HTTP, asa cum ne-am astepta din partea unui REST API.
Deasemenea, datorita diferentelor de stocarea a informatiei dintre WebUI (localStorage) si WebAssembly (Wasm Memory), a fost adaugata o functie de sincronizare intre cele 2 interfete, cu mentiunea ca aceasta sincronizare functioneaza **DOAR** in directia WEBUI -> WASM, nu si invers. Altfel spus, ce se introduce prin WASM **NU** se va putea vedea in aplicatia web.
Pentru ca informatiile introduse prin WebUI (campurile formularului) sa fie vizibile si in Wasm Console, va fi necesar un Page Refresh.

Principiu de functionare: interfata **Web** (HTML, CSS) primeste prin intermediul JS input:
- din **Formular** - backendul aici este in app.js (pana aici e un Single-Page WebApp clasic)
- din **Wasm Console** - "engine.js" (fisier generat prin compilarea cu **emcc**) capteaza inputul (Emscripten Bridge stdin/stdout) si apeleaza functiile C compilate direct.

## Planificare
AMR este un exercitiu demonstrativ de dezvoltare. Functionalitatea de baza - cea de gestionare a zilelor libere - este privita ca un "use-case". Scopul din spatele acestei aplicatii este de a testa diferite tehnologii si combinatii ale acestora.

- (Original) - WebApp care sa puna in valoare diferitele Interfete si moduri de functionare (client-side/server-side): HTML, CSS, JS, PHP
- (Curent) - Aplicatie standalone care sa puna in valoare utilizarea structurilor de date: C/C++
- (Viitor) - REST API real (nu demo).