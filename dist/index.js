/* eslint-disable global-require */
const fs = require('fs');
const path = require('path');

const file = '../build/Release/rpi_ws281x_node.node';

// eslint-disable-next-line import/no-unresolved
if (fs.existsSync(path.join(__dirname, file))) module.exports = require(path.join(__dirname, file));
else module.exports = {};
