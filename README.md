# AMR (Au Mai Ramas)
Aceasta aplicatie faciliteaza gestionarea zilelor libere (recuperari), obtinute pe parcursul activitatii, la servici.

AMR poate functiona atat ca aplicatie de sine statatoare, cat si integrata cu diferite solutii terte.

Functiile cheie ale acestei aplicatii sunt:
- sumar concis al zilelor de recuperare disponibile pe anul curent.
- gestionarea zilelor de recuperare, adaugate si utilizate.

## Structura
1. Sumar: Numarul de zile de recuperare disponibile pe anul curent.
2. Actiuni:
    - "+" Adaugare zile libere:
        - Data cand s-a lucrat
        - Numar zile care se adauga
        - Categoria: Liber de serviciu, Exercitiu, Misiune, Recompensa
        - Detalii.
    - "-" Utilizare zile libere:
        - Numar zile (recuperari) care se folosesc
        - Detalii
3. Istoric - listare intrari, cele recente aparand primele.

## Cerinte
- Descrierea detailata a functiilor principale
- Interactiuni intre utilizatori si aplicatie
- Fluxuri de utilizare si scenarii
- Performanta (timpi incarcare, capacitate utilizare)
- Securitate
- Scalabilitate (adaugare de utilizatori noi, functionalitati noi)
- Accesibilitate (compatibilitate cu diferite dispozitive)

## Interne
1. Design si Interfata
- Prototip, mockup, demo
- Culori, fonturi, elemente vizuale
- UX si UI
2. Tehnologii folosite
- Limbaj de programare folosit: HTML, CSS, Javascript
- Framework-uri
- BD

## Planificare
- timpi estimativi pentru fiecare faza de dezvoltare
- livrabile prin fiecare etapa (prototip, beta, versiune finala)

## Intretinere si Suport


- plan de intretinere
- responsabilitatile echipei de suport tehnic

## Consideratii legale si de conformitate
Fiind o aplicatie utilizata fara un cont/autentificare, datele personale sunt salvate doar local, in deplina gestiune a utilizatorului.
**Atentie**: Nodulul de autentificare este unul pur academic si demonstrativ - dupa sesiunea de prezentare, acest modul va fi inlaturat integral.

## Roadmap
- PWA (Progressive Web App) - instalabil ca si client de sine statator
    Avantaje urmarite:
    - instalare facila atat pe dispozitive mobile cat si desktop.
    - utilizarea aplicatiei pe sisteme de operare care nu mai sunt in suport si deci nu se poate instala altfel - BBOS, dumbphone
    - utilizare a aplicatiei in mod nativ, offline. 
- REST API - care sa poata fi integrat in alte aplicatii.
- calendar view - imagine de ansamplu prin intermediul unui calendar
- sumar recurent ce poate fi trimis ca email (HTML) prin smtp relay.
    - ar putea fi incluse grafie (eg. Pie Chart) cu Statistici.
- alerte cand balanta atinge un anumit prag;
- alerta de "expirare" a zilelor (daca acestea expira)
- backup al intrarilor pe un an de zile, si resetul contorului, pastrand recuperarile restante din anul anterior.
- balanta exprimata in ore si zile, deoarece se mai pot da si ore libere, nu o zi intreaga.