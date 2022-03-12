const os = require('os');
const fallback = require('./fallback');

const unsupported = os.platform() !== 'linux';

module.exports = unsupported ? { ...fallback } : require('bindings')('rpi_ws281x_node');
