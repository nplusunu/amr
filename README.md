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
- Web UI: disponibila la adresa:[https://amr.nplusunu.ro](https://amr.nplusunu.ro).
- CLI: disponibila la adresa:[https://amr.nplusunu.ro/terminal.php](https://amr.nplusunu.ro/terminal.php).

Ambele variante urmeaza aceasi logica, difera ca mod de executie. Logica aplicatiei este dupa cum urmeaza:
- Utilizatorul completeaza campurile din sectiunea **Actiuni**, in functie de ce isi doreste - fie sa adauge (+) sau sa scada (-) zile.
- In functie de varianta utilizata (Web sau CLI), informatiile sunt verificate, iar apoi sunt salvate.
- Balanta zilelor este recalculata si rezultatul se afiseaza in prima sectiune ca si **Sumar**.
- **Istoricul** se actualizeaza cu inregistrarile completate anterior, impreuna cu datele lor specifice.
    - aceste intrari sunt prezentate in ordinea in care au fost adaugate.
    - ele pot fi sterse, apasand butonul de stergere [x].
- Informatiile vizibile in Istoric pot fi exportate ca si fisier CSV.

## Caracteristici

**Compatibilitate**: Aceasta aplicatie este disponibila pentru o varietate larga de dispozitive, ce pot comunica prin intermediul protocolului **HTTP**, indiferent de sistemul de operare.
AMR poate functiona atat ca aplicatie de sine statatoare, cat si integrata cu diferite solutii terte, datorita atat protocolului de comunicare extrem de versatil, dar si formatului standard ales pentru salvare a datelor (**CSV**), acestea putand fi folosite la randul lor ca date de intrare pentru diferite automatizari (pipelines) sau aplicatii.
Formatul standard al datelor de iesire este util si in situatia in care se doreste efectuarea de copii de siguranta, copii ce pot fi vizionate si editate in aplicatii office Saas (Google Docs etc.) sau locale (Office, LibreOffice etc.).

**Atentie**: Aceasta aplicatie poate functiona si pe dispozitive cu sisteme de operare ce nu mai sunt in sumport (ex. Blackberry BBOS10) dar pot aparea probleme de conectare datorata suportului in permanenta actualizare pentru certificatele de securitate TLS/SSL, lucru ce poate cauza diferite mesaje de alerta sau eroare.
Prin prezenta aplicatie ne dorim o acoperire cat mai larga, insa nu intra in scopul nostru suportul dispozitivelor iesite din suportul lor oficial.

**Securitate**: Se foloseste ecriptare SSL aplicata conexiunii HTTP (**HTTPS**), prin intermediul certificatului Let's Encrypt, aplicat domeniului nplusunu.ro.
Pentru varianta Web a aplicatiei, prelucrarea si retinerea datelor se realizeaza local, pe dispozitivul utilizatorului, astfel ele raman confidentiale.
Pentru varianta CLI a aplicatiei, datele raman salvate cat timp sesiunea este deschisa.

Pentru o siguranta mai sporita, se poate opta pentru encriptarea documentului CSV salvat local.

**Performanta**: Fiind o aplicatie simpla, atat ca si limbaj de programare cat si ca logica, utilizarea acesteia nu ridica probleme, nici pentru dispozitivul utilizatorului, nici pentru serverul unde aceasta aplicatie este gazduita, nici pentru conexiunea la internet, putand fi utilizata in medii oricat de ostile (CPU, RAM, Disc limitat, Conexiune problematica etc.)
Nu este un plafon de numar de utilizatori sau sesiuni deschise.

**Scalabilitate**: Adaugarea de functionalitati noi este facila deoarece structura aplicatiei este una foarte simpla.

## Interne
1. Design si Interfata
AMR isi propune sa functioneze in doua regimuri:
- Web UI: aceasta este varianta vizibila folosind oricare din web-browserele moderne.
- CLI (Command Line Interface): varianta "prietenoasa" cu consola (Terminal)

2. Tehnologii folosite
**HTML** si **CSS** este utilizat pentru a construi interfata de baza, urmarind o compatibilitate Terminal/Web browser:
    - **Forms** pentru adaugarea noilor intrari, pentru configuratiile fara JS.
    - **Table-view** pentru vizionarea Istoricului intr-un text browser.
    - Vizionarea Balantei
    - linkuri de Export si Stergere
**Javascript** ofera functionalitatile critice ale aplicatiei in varianta Web UI, functionalitati ce asigura procesarea si retinerea informatiei la utilizator (client-side).
    - adaugarea/setregerea de intrari
    - CSV export
**PHP** ofera functionalitatile critice ale aplicatiei in varianta CLI, de la nivelul serverului (server-side). In aceasta varianta optiunile oferite de JS nu sunt disponibile.

## Planificare
Aplicatia AMR a fost dezvoltata ad-hoc, coordonand efortul prin intermediul sistemului de versionare git, folosind ca si solutie GitHub.
Deoarece acesta este un efort voluntar, organizarea nu poate urma metodologiile clasice (ex. Agile), care sa poata oferi predictii ale unor livrabile.
Organizarea noastra consta in:
- Consolidarea si prioritizarea unui **Backlog** care sa contina: bug fixes, feature requests, imbunatatiri/optimizari etc.
    - Pe baza Feature-urilor cu impact major, se traseaza si un **Roadmap** (descris mai jos).
- **Implementarea** modificarilor si aducerea lor in mediul de **Live** (amr.nplusunu.ro)

## Intretinere si Suport
Aceasta aplicatie este una libera, gratuita, pentru care nu putem oferi suport oficial, dar suntem deschisi pentru intrebari, observatii si recomandari la adresa de email: amr [at] nplusunu . ro.

## Consideratii legale si de conformitate
Fiind o aplicatie utilizata individual, datele personale sunt salvate local, in deplina gestiune a utilizatorului.

## Roadmap
- REST API - care sa poata fi integrat in alte aplicatii.