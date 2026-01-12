const rules = {
  liber: 2,
  exercitiu: 1,
  recompensa: 1
};

let entries = JSON.parse(localStorage.getItem("entries")) || [];

const dateInput = document.getElementById("date");
const typeSelect = document.getElementById("type");
const categorySelect = document.getElementById("category");
const amountInput = document.getElementById("amount");
const noteInput = document.getElementById("note");

/* Set today as default date (safe cross-browser) */
dateInput.value = new Date().toISOString().split("T")[0];

categorySelect.addEventListener("change", autoSetAmount);
typeSelect.addEventListener("change", toggleCategory);

function autoSetAmount() {
  if (typeSelect.value === "earned" && rules[categorySelect.value]) {
    amountInput.value = rules[categorySelect.value];
  }
}

function toggleCategory() {
  const isUsed = typeSelect.value === "used";
  categorySelect.disabled = isUsed;

  if (isUsed) {
    amountInput.value = amountInput.value || 1;
  } else {
    autoSetAmount();
  }
}

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

function deleteEntry(id) {
  entries = entries.filter(e => e.id !== id);
  save();
  render();
}

function calculateBalance() {
  return entries.reduce((sum, e) => {
    return e.type === "earned"
      ? sum + e.amount
      : sum - e.amount;
  }, 0);
}

function save() {
  localStorage.setItem("entries", JSON.stringify(entries));
}

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
}

/* Initial load */
toggleCategory();
render();

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