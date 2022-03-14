const FREQ = 800000;
const DMANUM = 10;

const GPIONUM_1 = 18;
const GPIONUM_2 = 13;
const INVERT = 1;
const COUNT = 100;
const STRIP_TYPE = 0x00081000;
const BRIGHNESS = 255;
const LEDS = new Uint32Array(COUNT).fill(0x000000);
const WSHIFT = 0;
const RSHIFT = 8;
const GSHIFT = 16;
const BSHIFT = 0;
const GAMMA = new Uint8Array(256);

for (let i = 0; i < 256; i += 1) {
  GAMMA[i] = i;
}

// eslint-disable-next-line camelcase
const make_gamma_table = (buffer, value) => {
  for (let i = 0; i < 256; i += 1) {
    // eslint-disable-next-line no-param-reassign
    buffer[i] = value > 0 ? Math.floor((i / 255.0) ** value * 255.0 + 0.5) : i;
  }
};

const GAMMA_FACTOR = 50;
const MODIFIED_GAMMA = new Uint8Array(256);
make_gamma_table(MODIFIED_GAMMA, GAMMA_FACTOR);

const { expect } = require('chai');
const driver = require('../dist/index');

const reset = () => {
  driver.freq = FREQ;
  driver.dmanum = DMANUM;

  driver.channel[0].gpionum = GPIONUM_1;
  driver.channel[0].invert = INVERT;
  driver.channel[0].count = COUNT;
  driver.channel[0].strip_type = STRIP_TYPE;
  driver.channel[0].brightness = BRIGHNESS;
};

describe('rpi_ws281x_node', function () {
  describe('render_wait_time', function () {
    it('should create a valid getter for the "render_wait_time" property', function () {
      expect(driver).to.have.property('render_wait_time');
      expect(driver.render_wait_time).to.exist;
      // eslint-disable-next-line no-undef
      expect(driver.render_wait_time).to.equal(BigInt(0));
    });
  });

  describe('freq', function () {
    it('should create a valid getter for the "freq" property', function () {
      expect(driver).to.have.property('freq');
      expect(driver.freq).to.exist;
      expect(driver.freq).to.equal(0);
    });

    it('should create a valid setter for the "freq" property', function () {
      driver.freq = FREQ;
      expect(driver.freq).to.equal(FREQ);
    });

    it('should throw an error when an invalid value is provided', function () {
      expect(() => {
        driver.freq = -1;
      }).to.throw;
    });
  });

  describe('dmanum', function () {
    it('should create a valid getter for the "dmanum" property', function () {
      expect(driver).to.have.property('dmanum');
      expect(driver.dmanum).to.exist;
      expect(driver.dmanum).to.equal(0);
    });

    it('should create a valid setter for the "dmanum" property', function () {
      driver.dmanum = DMANUM;
      expect(driver.dmanum).to.equal(DMANUM);
    });

    it('should throw an error when an invalid value is provided', function () {
      expect(() => {
        driver.freq = 1.23;
      }).to.throw;
    });
  });

  describe('channel', function () {
    it('should create a valid getter for the "channel" property', function () {
      expect(driver).to.have.property('channel');
      expect(driver.channel).to.exist;
      expect(driver.channel).to.be.an('array').of.length(2);
    });

    for (let k = 0; k < 2; k += 1) {
      describe(`channel[${k}]`, function () {
        describe('gpionum', function () {
          it('should create a valid getter for the "gpionum" property', function () {
            expect(driver.channel[k]).to.have.property('gpionum');
            expect(driver.channel[k].gpionum).to.exist;
            expect(driver.channel[k].gpionum).to.equal(0);
          });

          it('should create a valid setter for the "gpionum" property', function () {
            driver.channel[k].gpionum = k === 0 ? GPIONUM_1 : GPIONUM_2;
            expect(driver.channel[k].gpionum).to.equal(k === 0 ? GPIONUM_1 : GPIONUM_2);
          });

          it('should throw an error when an invalid value is provided', function () {
            expect(() => {
              driver.channel[k].gpionum = 1.23;
            }).to.throw;
          });
        });

        describe('invert', function () {
          it('should create a valid getter for the "invert" property', function () {
            expect(driver.channel[k]).to.have.property('invert');
            expect(driver.channel[k].invert).to.exist;
            expect(driver.channel[k].invert).to.equal(0);
          });

          it('should create a valid setter for the "invert" property', function () {
            driver.channel[k].invert = INVERT;
            expect(driver.channel[k].invert).to.equal(INVERT);
          });

          it('should throw an error when an invalid value is provided', function () {
            expect(() => {
              driver.channel[k].invert = 1.23;
            }).to.throw;
          });
        });

        describe('count', function () {
          it('should create a valid getter for the "count" property', function () {
            expect(driver.channel[k]).to.have.property('count');
            expect(driver.channel[k].count).to.exist;
            expect(driver.channel[k].count).to.equal(0);
          });

          it('should create a valid setter for the "count" property', function () {
            driver.channel[k].count = COUNT;
            expect(driver.channel[k].count).to.equal(COUNT);
          });

          it('should throw an error when an invalid value is provided', function () {
            expect(() => {
              driver.channel[k].count = Infinity;
            }).to.throw;
          });
        });

        describe('strip_type', function () {
          it('should create a valid getter for the "strip_type" property', function () {
            expect(driver.channel[k]).to.have.property('strip_type');
            expect(driver.channel[k].strip_type).to.exist;
            expect(driver.channel[k].strip_type).to.equal(0);
          });

          it('should create a valid setter for the "strip_type" property', function () {
            driver.channel[k].strip_type = STRIP_TYPE;
            expect(driver.channel[k].strip_type).to.equal(STRIP_TYPE);
          });

          it('should throw an error when an invalid value is provided', function () {
            expect(() => {
              driver.channel[k].gpionum = 5.54;
            }).to.throw;
          });
        });

        describe('leds', function () {
          it('should return undefined before initialization', function () {
            expect(driver.channel[k]).to.have.property('leds');
            expect(driver.channel[k].leds).to.be.undefined;
          });
        });

        describe('brightness', function () {
          it('should create a valid getter for the "brightness" property', function () {
            expect(driver.channel[k]).to.have.property('brightness');
            expect(driver.channel[k].brightness).to.exist;
            expect(driver.channel[k].brightness).to.equal(0);
          });

          it('should create a valid setter for the "brightness" property', function () {
            driver.channel[k].brightness = BRIGHNESS;
            expect(driver.channel[k].brightness).to.equal(BRIGHNESS);
          });

          it('should throw an error when an invalid value is provided', function () {
            expect(() => {
              driver.channel[k].brightness = -1;
            }).to.throw;

            expect(() => {
              driver.channel[k].brightness = 256;
            }).to.throw;
          });
        });

        describe('wshift', function () {
          it('should create a valid getter for the "wshift" property', function () {
            expect(driver.channel[k]).to.have.property('wshift');
            expect(driver.channel[k].wshift).to.exist;
            expect(driver.channel[k].wshift).to.equal(0);
          });
        });

        describe('rshift', function () {
          it('should create a valid getter for the "rshift" property', function () {
            expect(driver.channel[k]).to.have.property('rshift');
            expect(driver.channel[k].rshift).to.exist;
            expect(driver.channel[k].rshift).to.equal(0);
          });
        });

        describe('gshift', function () {
          it('should create a valid getter for the "gshift" property', function () {
            expect(driver.channel[k]).to.have.property('gshift');
            expect(driver.channel[k].gshift).to.exist;
            expect(driver.channel[k].gshift).to.equal(0);
          });
        });

        describe('bshift', function () {
          it('should create a valid getter for the "bshift" property', function () {
            expect(driver.channel[k]).to.have.property('bshift');
            expect(driver.channel[k].bshift).to.exist;
            expect(driver.channel[k].bshift).to.equal(0);
          });
        });

        describe('gamma', function () {
          it('should return undefined before initialization', function () {
            expect(driver.channel[k]).to.have.property('gamma');
            expect(driver.channel[k].gamma).to.be.undefined;
          });
        });
      });
    }
  });

  describe('init()', function () {
    before(function () {
      reset();
    });

    after(function () {
      driver.fini();
    });

    it('should execute without throwing', function () {
      expect(driver.init()).to.not.throw;
    });

    it('should initiaize the hardware information', function () {
      expect(driver).to.have.property('rpi_hw');
      expect(driver.rpi_hw).to.exist;

      expect(driver.rpi_hw).to.have.property('type');
      expect(driver.rpi_hw.type).to.exist;
      expect(driver.rpi_hw.type).to.be.a('number');

      expect(driver.rpi_hw).to.have.property('hwver');
      expect(driver.rpi_hw.hwver).to.exist;
      expect(driver.rpi_hw.hwver).to.be.a('number');

      expect(driver.rpi_hw).to.have.property('periph_base');
      expect(driver.rpi_hw.periph_base).to.exist;
      expect(driver.rpi_hw.periph_base).to.be.a('number');

      expect(driver.rpi_hw).to.have.property('videocore_base');
      expect(driver.rpi_hw.videocore_base).to.exist;
      expect(driver.rpi_hw.videocore_base).to.be.a('number');

      expect(driver.rpi_hw).to.have.property('desc');
      expect(driver.rpi_hw.desc).to.exist;
      expect(driver.rpi_hw.desc).to.be.a('string');
    });

    it('should initialize the channel led buffers', function () {
      for (let k = 0; k < driver.channel.length; k += 1) {
        expect(driver.channel[k]).to.have.property('leds');
        expect(driver.channel[k].leds).to.exist;
        expect(driver.channel[k].leds).to.deep.equal(LEDS);
      }
    });

    it('should initialize the channel shifts', function () {
      for (let k = 0; k < driver.channel.length; k += 1) {
        expect(driver.channel[k]).to.have.property('wshift');
        expect(driver.channel[k].wshift).to.exist;
        expect(driver.channel[k].wshift).to.equal(WSHIFT);

        expect(driver.channel[k]).to.have.property('rshift');
        expect(driver.channel[k].rshift).to.exist;
        expect(driver.channel[k].rshift).to.equal(RSHIFT);

        expect(driver.channel[k]).to.have.property('gshift');
        expect(driver.channel[k].gshift).to.exist;
        expect(driver.channel[k].gshift).to.equal(GSHIFT);

        expect(driver.channel[k]).to.have.property('bshift');
        expect(driver.channel[k].bshift).to.exist;
        expect(driver.channel[k].bshift).to.equal(BSHIFT);
      }
    });

    it('should initialize the channel gamma tables', function () {
      for (let k = 0; k < driver.channel.length; k += 1) {
        expect(driver.channel[k]).to.have.property('gamma');
        expect(driver.channel[k].gamma).to.exist;
        expect(driver.channel[k].gamma).to.deep.equal(GAMMA);
      }
    });
  });

  describe('render()', function () {
    before(function () {
      reset();
    });

    after(function () {
      driver.fini();
    });

    it('should throw an error before initialization', function () {
      expect(() => driver.render()).to.throw;

      driver.init();
    });

    it('should execute without throwing', function () {
      expect(driver.render()).to.not.throw;
    });

    it('should throw an error when trying to render an invalid buffer', function () {
      driver.leds = '';
      expect(driver.render()).to.throw;

      driver.leds = new Uint16Array(driver.count);
      expect(driver.render()).to.throw;

      driver.leds = new Uint32Array(driver.count + 1);
      expect(driver.render()).to.throw;
    });
  });

  describe('wait()', function () {
    before(function () {
      reset();
    });

    after(function () {
      driver.fini();
    });

    it('should throw an error before initialization', function () {
      expect(() => driver.wait()).to.throw;

      driver.init();
    });

    it('should execute without throwing', function () {
      expect(driver.wait()).to.not.throw;
    });
  });

  describe('set_custom_gamma_factor()', function () {
    before(function () {
      reset();
    });

    after(function () {
      driver.fini();
    });

    it('should throw an error before initialization', function () {
      expect(() => driver.set_custom_gamma_factor(GAMMA_FACTOR)).to.throw;

      driver.init();
    });

    it('should execute without throwing', function () {
      expect(driver.set_custom_gamma_factor(GAMMA_FACTOR)).to.not.throw;
    });

    it('should update the gamma tables of each channal', function () {
      for (let k = 0; k < driver.channel.length; k += 1) {
        expect(driver.channel[k]).to.have.property('gamma');
        expect(driver.channel[k].gamma).to.exist;
        expect(driver.channel[k].gamma).to.deep.equal(MODIFIED_GAMMA);
      }
    });
  });

  describe('fini()', function () {
    before(function () {
      reset();
    });

    it('should throw an error before initialization', function () {
      expect(() => driver.fini(GAMMA_FACTOR)).to.throw;

      driver.init();
    });

    it('should execute without throwing', function () {
      expect(driver.fini()).to.not.throw;
    });
  });
});
