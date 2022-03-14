# rpi-ws281x-node

Node API wrapper for the [rpi_ws281x](https://github.com/jgarff/rpi_ws281x) library.

## Compilation

This project can be compiled using node-gyp.

```
$ npm install -g node-gyp
$ git clone https://github.com/dsyomichev/rpi-ws281x-node.git && cd rpi-ws281x-node
$ node-gyp configure && node-gyp build
```

However, it is recommended to install through npm.

## Installation

You can add this package to your own project using npm.

```
$ npm install rpi-ws281x-node
```

Then load it into your own project. This project includes type declarations for Typescript.

```javascript
const driver = require('rpi-ws281x-node');
```

## Notes

- This project is intended to be compiled on a Raspberry Pi device. On unsupported platforms, an empty interface is returned.

- Root priveledges are required to acces PWM channels. Start the process as `sudo`.

## Usage

The purpose of this project is to provide an interface between a node process and the rpi_ws281x driver. The configuration of this interface matches that of the parent library. Each property is provided via getter and/or setter, with the exception of the `leds` property of `ws2811_channel`.

```javascript
driver.freq = 800000; // uint32_t;
driver.dmanum = 10; // int32_t

driver.channel[0].gpionum = 18; // int32_t
driver.channel[0].invert = 0; // int32_t
driver.channel[0].count = 100; // int32_t
driver.channel[0].strip_type = 0x00081000; // int32_t
driver.channel[0].brightness = 255; // uint8_t

driver.init();
```

These values will be checked through the setter to verify their validity for that particular parameter.

LEDs can be modified through the `leds` property. When the `render` method is called, the underlying buffers are copied to the driver.

```javascript
driver.channel[0].leds = new UInt32Array(driver.channel[0].count).fill(0xffffff);
driver.channel[0].leds[0] = 0x000000;

driver.render();
```

The `leds` property will be checked for validity when the `render` method is called. It will throw an `ERR_INVALID_ARG` error if the property is not a Uint32Array or if the size does not match.

For more information on the structure of the driver, see [index.d.ts](dist/index.d.ts) and the [usage](https://github.com/jgarff/rpi_ws281x#usage) section of the rpi_ws281x README.

## Tested Devices

- Raspberry Pi 3b v1.2

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
