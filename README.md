# AMR

## Descriere
AMR (Au Mai Ramas) este o aplicatie web, care se adreseaza in mod deosebit angajatilor din sistemul de Stat, si care isi propune sa faciliteze gestionarea zilelor de recuperare, obtinute pe parcursul activitatii lor.

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
- reguli si reglementari aplicabile (GDRP, drepturi de autor)
- masuri de protectie a datelor utilizatorilor

## Roadmap
- PWA (Progressive Web App) - instalabil ca si client de sine statator
    Avantaje urmarite:
    - instalare facila atat pe dispozitive mobile cat si desktop.
    - utilizare a aplicatiei in mod nativ, offline. 
- REST API - care sa poata fi integrat in alte aplicatii.
- calendar view - imagine de ansamplu prin intermediul unui calendar
- sumar recurent ce poate fi trimis ca email (HTML) prin smtp relay.
- backup al intrarilor pe un an de zile, si resetul contorului, pastrand recuperarile restante din anul anterior.