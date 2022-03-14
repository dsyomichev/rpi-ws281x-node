export interface ws2811_channel {
  gpionum: number;
  invert: number;
  count: number;
  strip_type: number;
  leds?: Uint32Array;
  brightness: number;
  readonly wshift: number;
  readonly rshift: number;
  readonly gshift: number;
  readonly bshift: number;
  readonly gamma?: Uint8Array;
}

export interface rpi_hw {
  readonly type: number;
  readonly hwver: number;
  readonly periph_base: number;
  readonly videocore_base: number;
  readonly desc: string;
}

export interface ws2811 {
  readonly render_wait_time: number;
  readonly rpi_hw?: rpi_hw;
  freq: number;
  dmanum: number;
  readonly channel: [ws2811_channel, ws2811_channel];

  readonly init: () => void;
  readonly fini: () => void;
  readonly render: () => void;
  readonly wait: () => void;
  readonly set_custom_gamma_factor: (value: number) => void;
}

declare const driver: ws2811;
export default driver;
