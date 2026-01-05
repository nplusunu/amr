# AMR

## Descriere
AMR (Au Mai Ramas) este o aplicatie web, care isi propune sa vina in ajutorul cadrelor MAPN, si care sa faciliteze evidenta recuperarilor obtinute pe parcursul activitatii lor.

AMR este o aplicatie locala, fara autentificare, care sa poata functiona atat de sine statator, cat si integrata cu solutii proprii.

Functiile cheie ale acestei aplicatii sunt:
- sumar concis al zilelor de recuperare disponibile pe anul curent.
- evidenta zilelor de recuperare adaugate si utilizate.

## Cerinte
- Descrierea detailata a functiilor principale
- Interactiuni intre utilizatori si aplicatie
- Fluxuri de utilizare si scenarii
- Performanta (timpi incarcare, capacitate utilizare)
- Securitate
- Scalabilitate (adaugare de utilizatori noi, functionalitati noi)
- Accesibilitate (compatibilitate cu diferite dispozitive)

## Structura
1. Denumire si Balanta
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

## Roadmap
- PWA (Progressive Web App) - instalabil ca si client de sine statator
    Avantaje urmarite:
    - instalare facila atat pe dispozitive mobile cat si desktop.
    - utilizare a aplicatiei in mod nativ, offline. 
- REST API - care sa poata fi integrat in alte aplicatii.
- calendar view - imagine de ansamplu prin intermediul unui calendar
- sumar recurent ce poate fi trimis ca email (HTML) prin smtp relay.
- backup al intrarilor pe un an de zile, si resetul contorului, pastrand recuperarile restante din anul anterior.