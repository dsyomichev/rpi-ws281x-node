# rpi-ws281x-node

NAPI wrapper around the [rpi_ws281x](https://github.com/jgarff/rpi_ws281x) library.

## Installing

You can add this package to your own project using

```
npm install rpi-ws281x-node
```

and then importing it with

```typescript
import driver from 'rpi-ws281x-node';
```

```javascript
const driver = require('rpi-ws281x-node');
```

## Notes

- This library is meant for the Raspberry PI. An unbound interface will be provided on non-linux platforms.

- Root privledges are required. Start the process as `sudo`.

## Usage

This library wraps the `rpi_ws281x::ws2811_t` struct one for one, with the exception of being able to modify individual LEDs.

```javascript
driver.freq = 80000;
driver.dmanum = 10;
driver.channel[0].gpionum = 18;
driver.channel[0].invert = 0;
driver.channel[0].count = 100;
driver.channel[0].strip_type = 0x00081000;
driver.channel[0].brightness = 255;

driver.init();

driver.channel[0].leds = new Uint32Array().fill(0xffffff);
driver.render();
```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
