# rpi-ws281x-node

`node-addon-api` module around the [`rpi_ws281x`](https://github.com/jgarff/rpi_ws281x) library.

## Installing

You can add this package to your own project using

```
npm install rpi-ws281x-node
```

and then importing it with

```javascript
const driver = require('rpi-ws281x-node');
```

```typescript
import driver from 'rpi-ws281x-node';
```

Type declarations for the module are provided.

## Notes

- This library is meant for the Raspberry PI. An unbound interface will be provided on non-linux platforms.

- Root privledges are required. Start the process as `sudo`.

## Usage

This library attempts to modularize the `rpi_ws281x::ws2811_t` struct. The object is exported nearly one for one as a NodeJS value. For more information on configuring the driver, see [this page](https://github.com/jgarff/rpi_ws281x#usage).

Private driver information is also ignored for the purposes of this library.

```javascript
driver.freq = 80000;
driver.dmanum = 10;
driver.channel[0].gpionum = 18;
driver.channel[0].invert = 0;
driver.channel[0].count = 100;
driver.channel[0].strip_type = 0x00081000;
driver.channel[0].brightness = 255;

driver.init();

driver.channel[0].leds = new Uint32Array(driver.channel[0].count).fill(0xffffff);
driver.channel[0].leds[0] = 0x000000;
driver.render();
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
