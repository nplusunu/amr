<?php
// Start the session to access the session data
session_start();

// Check if the 'entries' data exists in the session
if (!isset($_POST['entries'])) {
    die("No entries to export.");
}

// Get the entries from the POST data
$entries = json_decode($_POST['entries'], true);

// Set headers to indicate a file download
header('Content-Type: text/csv');
header('Content-Disposition: attachment; filename="amr_entries.csv"');

// Open output stream to send the CSV data directly to the browser
$output = fopen('php://output', 'w');

// Write the header row to the CSV
fputcsv($output, ['Date', 'Type', 'Category', 'Amount', 'Note']);

// Write the data rows to the CSV
foreach ($entries as $entry) {
    // Prepare the data to be written into the CSV
    $row = [
        $entry['date'],
        ($entry['type'] === 'earned' ? 'Obținută' : 'Utilizată'),
        $entry['category'],
        number_format($entry['amount'], 1),
        $entry['note']
    ];
    fputcsv($output, $row);
}

// Close the file stream (optional as it's output)
fclose($output);
exit();
