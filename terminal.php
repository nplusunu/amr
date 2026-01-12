<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>AMR - Terminal</title>
<style>
    body { font-family: monospace; background:#fff; color:#000; padding:1rem; }
    h1,h2 { margin: 0.5rem 0; }
    table { border-collapse: collapse; width: 100%; }
    th, td { border: 1px solid #000; padding: 0.25rem; }
    input, select { width: 100%; }
    button { margin-top:0.5rem; }
</style>
</head>
<body>

<h1>Au Mai Ramas (Terminal)</h1>

<h2>Inregistrare noua:</h2>
<form method="POST" action="terminal.php">
    <p>Data:<br><input type="date" name="date" required></p>
    <p>Recuperare Obtinuta (+) / Utilizata (-):<br>
        <select name="type">
            <option value="earned">Obtinuta</option>
            <option value="used">Utilizata</option>
        </select>
    </p>
    <p>Categorie:<br>
        <select name="category">
            <option value="liber">Liber de serviciu - 24h, Liber de Stat</option>
            <option value="exercitiu">Exercitiu, Alerta</option>
            <option value="recompensa">Recompensa</option>
        </select>
    </p>
    <p>Numar Zile:<br><input type="number" step="0.5" name="amount" required></p>
    <p>Detalii:<br><input type="text" name="note"></p>
    <input type="submit" value="Adauga">
</form>

<h2>Istoric</h2>
<?php
// Super lightweight backend simulation for terminal
session_start();
if (!isset($_SESSION['entries'])) {
    $_SESSION['entries'] = [];
}

// Handle form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $entry = [
        'id' => time(),
        'date' => $_POST['date'],
        'type' => $_POST['type'],
        'category' => $_POST['category'],
        'amount' => floatval($_POST['amount']),
        'note' => $_POST['note']
    ];
    $_SESSION['entries'][] = $entry;
}

// Calculate balance
$balance = 0;
foreach ($_SESSION['entries'] as $e) {
    $balance += ($e['type'] === 'earned') ? $e['amount'] : -$e['amount'];
}

echo "<p>Balance: " . number_format($balance, 1) . "</p>";

if (!empty($_SESSION['entries'])) {
    echo "<table><tr><th>Date</th><th>Type</th><th>Category</th><th>Amount</th><th>Note</th></tr>";
    foreach ($_SESSION['entries'] as $e) {
        echo "<tr>
            <td>{$e['date']}</td>
            <td>" . ($e['type']==='earned'?'Obtinuta':'Utilizata') . "</td>
            <td>{$e['category']}</td>
            <td>{$e['amount']}</td>
            <td>{$e['note']}</td>
        </tr>";
    }
    echo "</table>";
}
?>

<h2>Export</h2>
<p>
<form method="POST" action="server_export.php">
    <input type="hidden" name="entries" value='<?php echo json_encode($_SESSION['entries']); ?>'>
    <button type="submit">Export CSV via Server (PHP)</button>
</form>
</p>

</body>
</html>