module.exports = process.platform === 'linux' ? require('../build/Release/rpi_ws281x_node.node') : undefined;
