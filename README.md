# AMR

## Descriere
AMR (Au Mai Ramas) isi propune sa faciliteze:
- evidenta zilelor libere obtinute lucrand in zile de sarbatoare, activitati speciale etc.
- evidenta zilelor libere folosite
- un sumar al balantei

AMR este o aplicatie locala (fara autentificare deocamdata).

## Structura
1. Denumire si Balanta
2. Actiuni:
    - "+" Adaugare zile libere:
        - Data cand s-a lucrat
        - Numar zile care se adauga
        - Categoria: Zi libera la Stat, Activitati Speciale etc.
        - Detalii.
    - "-" Utilizare zile libere:
        - Numar zile (recuperari) care se folosesc
        - Detalii
3. Istoric - listare intrari, cele recente aparand primele.

## Roadmap
- PWA (Progressive Web App) - instalabil ca si client de sine statator
- REST API - care sa poata fi integrat in alte aplicatii.
- calendar view - imagine de ansamplu prin intermediul unui calendar
- sumar recurent ce poate fi trimis ca email (HTML) prin smtp relay. 