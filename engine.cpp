#include <iostream>
#include <cstring>
#include <cstdlib>

// Structura de date ce reflecta schema de obiecte din app.js
struct LeaveEntry {
    long long id;          // IDul ca si timestamp obtinut prin Date.now()
    char date[11];         // Format: YYYY-MM-DD
    char type[8];          // "earned" or "used"
    char category[12];     // "liber", "exercitiu", "recompensa"
    double amount;         // Numarul de zile
    char note[128];        // Optional: comentariu utilizator
    
    LeaveEntry* next;      // Linked list reference pointer
};


LeaveEntry* head = nullptr;


void addNode(long long id, const char* date, const char* type, const char* cat, double amount, const char* note) {
    LeaveEntry* newEntry = new LeaveEntry();
    newEntry->id = id;
    std::strncpy(newEntry->date, date, 11);
    std::strncpy(newEntry->type, type, 8);
    std::strncpy(newEntry->category, cat, 12);
    newEntry->amount = amount;
    std::strncpy(newEntry->note, note, 128);
    
    newEntry->next = head;
    head = newEntry;
}

// REST Route Simulation: GET /api/entries
void handleGetEntries() {
    std::cout << "\nHTTP/1.1 200 OK\nContent-Type: application/json\n\n";
    if (!head) {
        std::cout << "[]\n(No entries found in Wasm Memory Stack)\n";
        return;
    }
    
    LeaveEntry* current = head;
    while (current != nullptr) {
        std::cout << " -> [ID: " << current->id << "] " 
                  << current->date << " | " 
                  << current->type << " | "
                  << (std::strlen(current->category) > 0 ? current->category : "utilizata") << " | "
                  << current->amount << " zile (" << current->note << ")\n";
        current = current->next;
    }
}

// REST Route Simulation: POST /api/entries
void handlePostEntry() {
    char date[11], type[8], cat[12] = "", note[128] = "";
    double amount;
    long long id = 12345678; //Timestamp de test care sa mimeze un ID

    std::cout << "\n--- POST /api/entries (Create Resource) ---\n";
    std::cout << "Enter Type ('earned' / 'used'): "; std::cin >> type;
    std::cout << "Enter Date (YYYY-MM-DD): "; std::cin >> date;
    
    if (std::strcmp(type, "earned") == 0) {
        std::cout << "Enter Category ('liber' [2], 'exercitiu' [1], 'recompensa' [1]): ";
        std::cin >> cat;
        if (std::strcmp(cat, "liber") == 0) amount = 2.0;
        else if (std::strcmp(cat, "exercitiu") == 0 || std::strcmp(cat, "recompensa") == 0) amount = 1.0;
        else { std::cout << "Invalid category!\n"; return; }
    } else {
        std::cout << "Enter Amount of used days: "; std::cin >> amount;
    }
    
    std::cin.ignore(); // Clear newline buffer
    std::cout << "Enter Details/Note: "; std::cin.getline(note, 128);

    addNode(id, date, type, cat, amount, note);
    std::cout << "\nHTTP/1.1 201 Created\nResource added successfully to Linked List!\n";
}

// REST Route Simulation: GET /api/balance
void handleGetBalance() {
    double balance = 0.0;
    LeaveEntry* current = head;
    while (current != nullptr) {
        if (std::strcmp(current->type, "earned") == 0) balance += current->amount;
        else balance -= current->amount;
        current = current->next;
    }
    std::cout << "\nHTTP/1.1 200 OK\n";
    std::cout << "Computed Free Day Balance: " << balance << " days\n";
}

// Bucla ce se executa in interiorul WebAssembly
extern "C" {
    void runRESTTerminal() {
        int option;
        char buffer[256];
        
        while (true) {
            std::cout << "\n=========================================\n";
            std::cout << "   FREE DAY ENGINE: SIMULATED REST-TUI   \n";
            std::cout << "=========================================\n";
            std::cout << "1. GET  /api/entries    - View memory records\n";
            std::cout << "2. POST /api/entries    - Store a new record\n";
            std::cout << "3. GET  /api/balance    - Fetch dynamic balance\n";
            std::cout << "4. EXIT                 - Close Console Frame\n";
            std::cout << "Select command code [1-4]: ";
            
            if (!(std::cin >> option)) {
                std::cin.clear();
                std::cin >> buffer; // Clean buffer stream error
                continue;
            }

            switch (option) {
                case 1: handleGetEntries(); break;
                case 2: handlePostEntry(); break;
                case 3: handleGetBalance(); break;
                case 4: std::cout << "Exiting terminal module context...\n"; return;
                default: std::cout << "404 Error: Request route match failed.\n";
            }
        }
    }
}

int main() {
    return 0;
}