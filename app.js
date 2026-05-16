// 1. Integrarea cu WebAssembly (CRITICAL: Trebuie sa fie la inceput!)
var Module = {
  preRun: [],
  postRun: [],
  print: (function() {
    return function(text) {
      const element = document.getElementById('output');
      if (element) {
        element.value += text + "\n";
        element.scrollTop = element.scrollHeight; // Auto-scrolls the terminal textarea
      }
    };
  })(),
  //Se executa de indata ce Wasm termina incarcarea sa in browser
  onRuntimeInitialized: function() {
    console.log("WebAssembly Engine is fully loaded. Performing initial state sync...");
    syncStateToWasm(); 
  }
};

//2. Rules, State, DOM, functions
// Seteaza valorile implicite a fiecarui tip de zi lucrata si liberele obtinute in mod normal.
const rules = {
  liber: 2,
  exercitiu: 1,
  recompensa: 1
};

// Obtine inregistrarile salvate cu localStorage, iar daca nu exista, initializeaza cu un array fara continut.
let entries = JSON.parse(localStorage.getItem("entries")) || [];

// DOM (Document Object Model)
const dateInput = document.getElementById("date");
const typeSelect = document.getElementById("type");
const categorySelect = document.getElementById("category");
const amountInput = document.getElementById("amount");
const noteInput = document.getElementById("note");

// Setare ca valoare implicita a Datei, data zilei curente
dateInput.value = new Date().toISOString().split("T")[0];

categorySelect.addEventListener("change", autoSetAmount);
typeSelect.addEventListener("change", toggleCategory);

// Setare automata a valorii pentru Numar Zile, cand campul "Obtinut" este selectat anterior.
function autoSetAmount() {
  if (typeSelect.value === "earned" && rules[categorySelect.value]) {
    amountInput.value = rules[categorySelect.value];
  }
}

// Comutare camp Obtinuta/Utilizata
// Daca e selectata optiunea Utilizata, dezactiveaza campul Categorie
function toggleCategory() {
  const isUsed = typeSelect.value === "used";
  categorySelect.disabled = isUsed;

  if (isUsed) {
    amountInput.value = amountInput.value || 1;
  } else {
    autoSetAmount();
  }
}

// Adauga o noua inregistrare - functie actualizata cu Wasm Sync Hooks
// Dupa adaugare, goleste campurile pentru a fi gata de o noua completare.
function addEntry() {
  const amount = parseFloat(amountInput.value);

  if (!dateInput.value || isNaN(amount) || amount <= 0) {
    alert("Va rugam completati corect data si numarul de zile.");
    return;
  }

  const entry = {
    id: Date.now(),
    date: dateInput.value,
    type: typeSelect.value,
    category: typeSelect.value === "earned" ? categorySelect.value : null,
    amount: amount,
    note: noteInput.value.trim()
  };

  entries.unshift(entry);
  save();
  render();

  noteInput.value = "";
}

// Stergere inregistrare, dupa ID
function deleteEntry(id) {
  entries = entries.filter(e => e.id !== id);
  save();
  render();
}

// Calcul balanta (Nr zilelor obtinute - Nr zilelor utilizate)
function calculateBalance() {
  return entries.reduce((sum, e) => {
    return e.type === "earned"
      ? sum + e.amount
      : sum - e.amount;
  }, 0);
}

// Salvarea in localStorage
function save() {
  localStorage.setItem("entries", JSON.stringify(entries));
}

// Sincronizarea intrarilor din JS catre WebAssembly
function syncStateToWasm() {
  // Verifica daca WebAssembly e disponibil
  if (typeof Module._clearWasmList !== "function" || typeof Module._addEntryFromJS !== "function") {
    return; // Wasm nu e complet initializat
  }

  // 1. Goleste lista din engine.cpp
  Module._clearWasmList();

  // 2. Repopuleaza lista invers - traversarea inversa pastreaza ordinea cronologica
  for (let i = entries.length - 1; i >= 0; i--) {
    const e = entries[i];
    
    // Conversia stringurilor in ASCII bytes pentru compilatorul C++
    Module.ccall(
      'addEntryFromJS', 
      null, 
      ['number', 'string', 'string', 'string', 'number', 'string'], 
      [e.id, e.date, e.type, e.category || "", e.amount, e.note || ""]
    );
  }
}

// Vizualizarea inregistrarilor si a balantei in UI
// Rezultatul balantei cu o zecimala
// Daca e un rezultat pozitiv, va aparea colorat cu verde
// Daca e un rezultat negativ, va aparea colorat cu rosu
function render() {
  const balance = calculateBalance();
  const balanceEl = document.getElementById("balance");

  balanceEl.textContent = balance.toFixed(1);
  balanceEl.style.color =
    balance >= 0 ? "var(--positive)" : "var(--negative)";

  const history = document.getElementById("history");
  history.innerHTML = "";

  if (entries.length === 0) {
    history.innerHTML = `<p class="note">Nu exista inregistrari.</p>`;
    return;
  }

  // Trece prin toate intrarile si construieste HTML pentru vizionare
  // In functie de tipul inregistrarii, se va colora cu rosu sau verde. 
  entries.forEach(e => {
    const div = document.createElement("div");
    div.className = "history-item";

    const sign = e.type === "earned" ? "+" : "−";
    const amountClass =
      e.type === "earned" ? "amount-positive" : "amount-negative";

    div.innerHTML = `
      <div>
        <div class="${amountClass}">
          ${sign}${e.amount} ${e.category ?? "utilizata"}
        </div>
        <div class="note">
          ${e.date}${e.note ? " – " + e.note : ""}
        </div>
      </div>
      <button class="delete-btn" onclick="deleteEntry(${e.id})">✕</button>
    `;

    history.appendChild(div);
  });
  syncStateToWasm();
}

/* Initial load */
toggleCategory();
render();

// Exportul inregistrarilor in format CSV
function exportCSV() {
  if (entries.length === 0) {
    alert("Nu exista date pentru export.");
    return;
  }

  const headers = [
    "Data",
    "Tip",
    "Categorie",
    "Numar Zile",
    "Detalii"
  ];

  const rows = entries.map(e => [
    e.date,
    e.type === "earned" ? "Obtinuta" : "Utilizata",
    e.category ?? "",
    e.amount,
    e.note ?? ""
  ]);

  let csvContent = headers.join(";") + "\n";

  rows.forEach(row => {
    csvContent += row
      .map(value => `"${String(value).replace(/"/g, '""')}"`)
      .join(";") + "\n";
  });

  const blob = new Blob([csvContent], { type: "text/csv;charset=utf-8;" });
  const url = URL.createObjectURL(blob);

  const link = document.createElement("a");
  link.href = url;
  link.download = `recuperari_${new Date().toISOString().split("T")[0]}.csv`;

  document.body.appendChild(link);
  link.click();
  document.body.removeChild(link);

  URL.revokeObjectURL(url);
}

// 3. TUI (Terminal User Interface) Event Listeners
document.addEventListener("DOMContentLoaded", () => {
  const termInput = document.getElementById("terminal-input");
  
  if (termInput) {
    termInput.addEventListener("keydown", (event) => {
      if (event.key === "Enter") {
        const value = termInput.value.trim();
        termInput.value = ""; // Clear input immediately
        
        if (value === "") return;
        
        // Print the typed command to our log window mimicry
        const outputEl = document.getElementById("output");
        if (outputEl) {
          outputEl.value += `api-shell$ ${value}\n`;
        }
        
        const option = parseInt(value, 10);
        
        if (isNaN(option) || option < 1 || option > 3) {
          if (outputEl) outputEl.value += "Invalid selection. Choose 1, 2, or 3.\n";
          return;
        }
        
        // Safely trigger the clean execution without causing any browser prompt pop-up!
        if (typeof Module._routeRESTCommand === "function") {
          Module._routeRESTCommand(option);
        } else {
          console.error("WebAssembly Engine module is still processing initialization.");
        }
      }
    });
  }
});