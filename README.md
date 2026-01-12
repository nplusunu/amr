# AMR (Au Mai Ramas)
Aceasta aplicatie faciliteaza gestionarea zilelor libere (recuperari), obtinute pe parcursul activitatii, la servici.

## Structura
1. **Sumar**: Numarul de zile de recuperare disponibile.
2. **Actiuni**:
    - "+" Adaugare zile libere:
        - Data cand s-a lucrat.
        - Categoria: Liber de serviciu, Exercitiu, Alerta, Recompensa (acestea au configurate valori implicite, ce pot fi modificate).
        - Numar zile care se adauga.
        - Detalii.
    - "-" Utilizare zile libere:
        - Numar zile (recuperari) care se folosesc.
        - Detalii.
3. **Istoric**: listare intrari efectuate anterior.

## Utilizare
- Aplicatia se poate accesa prin intermediul URL: [https://amr.nplusunu.ro](https://amr.nplusunu.ro).
- In prima sectiune va fi vizibil un **Sumar** al zilelor libere disponibile.
    - Valoarea initiala cand aplicatia se deschide este 0.
    - Aceasta valoare va reflecta rezultatul total al adaugarilor/stergerilor realizate pe parcurs.
- Se completeaza detaliile **Actiunii** ce se doreste realizata - adaugare (+) sau scadere (-) a zilelor - completand caracteristicile specifice fiecareia dintre actiuni.
- In cadrul sectiunii **Istoric** vor aparea intrarile completate anterior, cu detaliile specifice.
    - Aceste intrari sunt prezentate in ordinea in care au fost adaugate.
    - Ele pot fi sterse, apasand butonul [X] de stergere.

**Atentie**: Datele completate si zilele adaugate/scazute sunt valabile doar in sesiunea existenta. Odata inchisa sesiunea, datele care nu sunt salvate/exportate se pierd.

## Caracteristici
**Compatibilitate**: Aceasta aplicatie este disponibila pentru toate dispozitivele ce pot comunica prin intermediul protocolului **HTTP**, indiferent de sistemul de operare.
AMR poate functiona atat ca aplicatie de sine statatoare, cat si integrata cu diferite solutii terte, datorita atat protocolului de comunicare extrem de versatil, dar si formatului standard ales pentru salvare a datelor (**CSV**), acestea putand fi folosite la randul lor ca date de intrare pentru diferite automatizari (pipelines) sau aplicatii.
Formatul standard al datelor de iesire este util si in situatia in care se doreste efectuarea de copii de siguranta, copii ce pot fi vizionate si editate in aplicatii office Saas (Google Docs etc.) sau locale (Office, LibreOffice etc.).

**Atentie**: Aceasta aplicatie poate functiona si pe dispozitive cu sisteme de operare ce nu mai sunt in sumport (ex. Blackberry BBOS10) dar pot aparea probleme de conectare datorata suportului in permanenta actualizare pentru certificatele de securitate TLS/SSL, lucru ce poate cauza diferite mesaje de alerta sau eroare.
Prin prezenta aplicatie ne dorim o acoperire cat mai larga, insa nu intra in scopul nostru suportul dispozitivelor iesite din suportul lor oficial.

**Securitate**: Se foloseste ecriptare SSL aplicata conexiunii HTTP (**HTTPS**), prin intermediul certificatului Let's Encrypt.
Prelucrarea si retinerea datelor se realizeaza local, pe dispozitivul utilizatorului, astfel ele raman confidentiale.

**Atentie**: Pentru o siguranta mai sporita, se poate opta pentru encriptarea documentului CSV salvat local.

**Performanta**: Fiind o aplicatie simpla, atat ca si limbaj de programare cat si ca logica, utilizarea acesteia nu ridica probleme, nici pentru dispozitivul utilizatorului, nici pentru serverul unde aceasta aplicatie este gazduita, nici pentru conexiunea la internet, putand fi utilizata in medii oricat de ostile (CPU, RAM, Disc limitat, Conexiune problematica etc.)
Nu este un plafon de numar de utilizatori sau sesiuni deschise.

**Scalabilitate**:
- Scalabilitate (adaugare de utilizatori noi, functionalitati noi)

## Interne
1. Design si Interfata
AMR isi propune sa functioneze in doua regimuri:
- Complet: aceasta este varianta vizibila folosind oricare din web-browserele moderne.
- CLI (Command Line Interface): varianta "prietenoasa" cu consola (Terminal)

2. Tehnologii folosite
**HTML** si **CSS** este utilizat pentru a construi interfata de baza, urmarind o compatibilitate Terminal/Web browser:
    - **Forms** pentru adaugarea noilor intrari, pentru configuratiile fara JS.
    - **Table-view** pentru vizionarea Istoricului intr-un text browser.
    - Vizionarea Balantei
    - linkuri de Export si Stergere
**Javascript** ofera functionalitatile critice ale aplicatiei, functionalitati ce asigura procesarea si retinerea informatiei la utilizator (client-side).
    - adaugarea/setregerea de intrari
    - CSV export
**PHP** ofera functionalitatile ajutatoare, la cerere (on-demand), de la nivelul serverului (server-side):
    - analiza si creare de grafice, care sa construiasca un raport.
    - trimiterea pe email a respectivului raport.

## Planificare
Aplicatia AMR a fost dezvoltata ad-hoc, coordonand efortul prin intermediul sistemului de versionare git, folosind ca si solutie GitHub.
Deoarece acesta este un efort voluntar, organizarea nu poate urma metodologiile clasice (ex. Agile), care sa poata oferi predictii ale unor livrabile.
Organizarea noastra consta in:
- Consolidarea si prioritizarea unui **Backlog** care sa contina: bug fixes, feature requests, imbunatatiri/optimizari etc.
    - Pe baza Feature-urilor cu impact major, se traseaza si un **Roadmap** (descris mai jos).
- **Implementarea** modificarilor si aducerea lor in mediul de **Test**
- Dupa evaluarea continutului din mediul de Test, daca noua versiune functioneaza corect, se aduce in mediul **Live**.

## Intretinere si Suport
Aceasta aplicatie este una libera, gratuita, pentru care nu putem oferi suport oficial, dar suntem deschisi pentru intrebari, observatii si recomandari la adresa de email: amr [at] nplusunu . ro.

## Consideratii legale si de conformitate
Fiind o aplicatie utilizata individual, datele personale sunt salvate local, in deplina gestiune a utilizatorului.

## Roadmap
- PWA (Progressive Web App) - instalabil ca si client nativ, functional offline.
- REST API - care sa poata fi integrat in alte aplicatii.