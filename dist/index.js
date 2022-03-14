// eslint-disable-next-line import/no-unresolved
module.exports = process.platform === 'linux' ? require('../build/Release/rpi_ws281x_node.node') : {};
