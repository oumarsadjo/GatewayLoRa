const express = require('express');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

// Route pour servir le fichier index.html
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname,  'maCarte.html'));
});

// Démarrage du serveur
app.listen(PORT, () => {
  console.log(`Le serveur est démarré sur le port ${PORT}`);
});
