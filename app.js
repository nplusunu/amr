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

    dateInput.valueAsDate = new Date();

    categorySelect.addEventListener("change", autoSetAmount);
    typeSelect.addEventListener("change", toggleCategory);

    function autoSetAmount() {
      if (typeSelect.value === "earned") {
        amountInput.value = rules[categorySelect.value];
      }
    }

    function toggleCategory() {
      const disabled = typeSelect.value === "used";
      categorySelect.disabled = disabled;
      if (disabled) {
        amountInput.value = 1;
      } else {
        autoSetAmount();
      }
    }

    function addEntry() {
      const entry = {
        id: Date.now(),
        date: dateInput.value,
        type: typeSelect.value,
        category: categorySelect.value,
        amount: parseFloat(amountInput.value),
        note: document.getElementById("note").value
      };

      if (!entry.amount || entry.amount <= 0) return;

      entries.unshift(entry);
      save();
      render();
      document.getElementById("note").value = "";
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
      balanceEl.style.color = balance >= 0 ? "var(--positive)" : "var(--negative)";

      const history = document.getElementById("history");
      history.innerHTML = "";

      entries.forEach(e => {
        const div = document.createElement("div");
        div.className = "history-item";

        const sign = e.type === "earned" ? "+" : "−";
        const amountClass = e.type === "earned" ? "amount-positive" : "amount-negative";

        div.innerHTML = `
          <div>
            <div class="${amountClass}">
              ${sign}${e.amount} ${e.type === "earned" ? e.category : "used"}
            </div>
            <div class="note">${e.date} ${e.note ? "– " + e.note : ""}</div>
          </div>
          <button class="delete-btn" onclick="deleteEntry(${e.id})">✕</button>
        `;

        history.appendChild(div);
      });
    }

    autoSetAmount();
    render();