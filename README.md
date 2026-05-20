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
Aplicatia se prezinta in doua variante.
- Install: descrierea pasilor de instalare sunt disponibili in sectiunea [Instalare](#instalare) (mai jos).
- Web UI: disponibila la adresa:[https://amr.nplusunu.ro](https://amr.nplusunu.ro).

**Nota:** Aceasta aplicatie a continut si o versiune CLI, scrisa sub forma unor scripturi PHP, versiune ce a fost creata in scop pur academic, pentru a evidentia diferentele de executare client-side/server-side. Desi aceste scripturi au fost inlaturate de pe server, ele sunt in continuare pastrate in interiorul directorului ["retired"](https://github.com/nplusunu/amr/tree/main/retired), din cadrul prezentului repository.

Ambele variante ale aplicatiei urmeaza aceasi logica:
- Utilizatorul completeaza campurile din sectiunea **Actiuni (WebCLI) / Intrari (TUI)**, in functie de ce isi doreste - fie sa adauge sau sa scada zile.
- Informatiile sunt verificate, iar apoi sunt salvate.
- Balanta zilelor este calculata, si disponibila sub forma unui **Sumar**.
- **Istoricul** se actualizeaza cu inregistrarile completate anterior, impreuna cu datele lor specifice.
- Informatiile vizibile in Istoric pot fi exportate ca si fisier CSV.

## Instalare
Codul sursa poate fi obtinut prin downloadul arhivei Zip direct din prezentul repository, sau utilizand comanda git.
Instalarea aplicatiei consta in copierea locala a fisierului sursa **/bin/amr.cpp** , si compilarea acestuia. Pasii de mai jos descriu instalarea pe un setup Linux sau WSL:
- git clone https://github.com/nplusunu/amr.git
- cd <cale-catre-directorul-amr/bin/>
- g++ -o amr amr.cpp
- ./amr

## Interne
1. Design si Interfata
- TUI (Terminal User Interface): varianta instalabila local contine un **Meniu**, interactiunea cu aplicatia realizandu-se selectand o optiune numerica 1-5.
- Web UI: aceasta este varianta vizibila folosind oricare din web-browserele moderne (compatibile cu JS). Elementul de noutate aici este **Wasm Demo Console** - o consola intr-o interfata web (mai multe detalii mai jos).

2. Tehnologii folosite

AMR in varianta executabila local, este realizata in limbaj **C++**, fiind o scriere si adaptare a variantei javascript, facand uz de structuri de date si operatii cu fisiere (functia de export CSV).

Am folosit acest prilej pentru a pregati dezvoltarea acestui program sub forma unui REST API. In acest context, cu ajutorul **WebAssembly**, am creat Wasm Demo Console, un mediu de lansare a comenzilor ce simuleaza aplicatia AMR sub forma de REST API.

**Nota:** WebAssembly (Wasm) este un runtime environment, o "masina virtuala" low-level ce permite executabilelor (precum /bin/amr) sa poata rula in interiorul unui website.
Fiind o masina virtuala, aceasta vine cu multe limitari, ceea ce a impus rescrierea executabilului nostru, pentru a putea rula in interiorul consolei disponibile in interfata web.
Deasemenea, vorbim doar de un Demo de REST API, deoarece unul autentic presupune comunicarea HTTP, iar WebAssembly, ca si sandbox, nu poate acomoda asemenea comunicare. Pentru realizarea acestui Demo, a fost scris un engine.cpp, unde API "routes" au fost definite ca functii standard, utilizand structuri de date si liste.

3. Arhitectura

Interfata **Web** (HTML, CSS) primeste prin intermediul JS input:
- din **Formular** - backendul aici este in app.js (pana aici e un Single-Page WebApp clasic)
- din **Wasm Console** - "engine.js" (fisier generat prin compilarea cu **emcc**) capteaza inputul (Emscripten Bridge stdin/stdout) si apeleaza functiile C compilate direct.

## Planificare
AMR este un exercitiu demonstrativ de dezvoltare. Functionalitatea de baza - cea de gestionare a zilelor libere - este privita ca un "use-case". Scopul din spatele acestei aplicatii este de a testa diferite tehnologii si combinatii ale acestora.

- (Original) - WebApp care sa puna in valoare diferitele Interfete si moduri de functionare (client-side/server-side): HTML, CSS, JS, PHP
- (Curent) - Aplicatie standalone care sa puna in valoare utilizarea structurilor de date: C++
- (Viitor) - REST API real (nu demo).