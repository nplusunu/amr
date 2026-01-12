<?php
session_start();

if (!isset($_POST['entries'])) {
    die("No entries to export.");
}

// Obtinerea datelor din inregistrarea efectuata, retinuta in format JSON
$entries = json_decode($_POST['entries'], true);

//Indicatii a carui tip de fisier va fi downloadat de browser
header('Content-Type: text/csv');
header('Content-Disposition: attachment; filename="amr_entries.csv"');

$output = fopen('php://output', 'w');

// Scrie primul rand - headerul CSV
fputcsv($output, ['Date', 'Type', 'Category', 'Amount', 'Note']);

// Adauga inregistrarile ca noi linii la CSV
foreach ($entries as $entry) {
    $row = [
        $entry['date'],
        ($entry['type'] === 'earned' ? 'Obținută' : 'Utilizată'),
        $entry['category'],
        number_format($entry['amount'], 1),
        $entry['note']
    ];
    fputcsv($output, $row);
}

fclose($output);
exit();
