#ifndef MODULE_H
#define MODULE_H

extern "C" {
#include <jgarff/rpi_ws281x/pwm.h>
#include <jgarff/rpi_ws281x/ws2811.h>
};

#include <napi.h>

#include "properties/channel.h"
#include "properties/rpi_hw.h"

/**
 * The controller that will be used to manipulate the light strip.
 **/
extern ws2811_t controller;

/**
 * Create a new driver object.
 **/
Napi::Object init_driver(Napi::Env env, Napi::Object exports);

/** Descriptors **/

/**
 * Create an accessor descriptor to the 'render_wait_time' property.
 **/
extern Napi::PropertyDescriptor render_wait_time_desc(void *data);

/**
 * Create an accessor descriptor to the 'rpi_hw' property.
 **/
extern Napi::PropertyDescriptor rpi_hw_desc(void *data);

/**
 * Create an accessor descriptor to the 'freq_desc' property.
 **/
extern Napi::PropertyDescriptor freq_desc(void *data);

/**
 * Create an accessor descriptor to the 'dmanum' property.
 **/
extern Napi::PropertyDescriptor dmanum_desc(void *data);

/**
 * Create an accessor descriptor to the 'channel' property.
 **/
extern Napi::PropertyDescriptor channel_desc(void *data);

/**
 * Create a function descriptor to the 'init' function.
 **/
extern Napi::PropertyDescriptor init_desc(void *data);

/**
 * Create a function descriptor to the 'fini' function.
 **/
extern Napi::PropertyDescriptor fini_desc(void *data);

/**
 * Create a function descriptor to the 'render' function.
 **/
extern Napi::PropertyDescriptor render_desc(void *data);

/**
 * Create a function descriptor to the 'wait' function.
 **/
extern Napi::PropertyDescriptor wait_desc(void *data);

/**
 * Create a function descriptor to the 'set_custom_gamma_factor' function.
 **/
extern Napi::PropertyDescriptor set_custom_gamma_factor_desc(void *data);

/** Functions **/

/**
 * Initialize the driver. Wrapper for the 'init' function.
 **/
void init_func(const Napi::CallbackInfo &info);

/**
 * Finalize the driver. Wrapper for the 'fini' function.
 **/
void fini_func(const Napi::CallbackInfo &info);

/**
 * Render the strip. Wrapper for the 'render' function.
 **/
void render_func(const Napi::CallbackInfo &info);

/**
 * Wait for the DMA completion. Wrapper for the 'wait' function.
 **/
void wait_func(const Napi::CallbackInfo &info);

/**
 * Set a custom gamma factor. Wrapper for the 'set_custom_gamma_factor' function.
 **/
void set_custom_gamma_factor_func(const Napi::CallbackInfo &info);

/** Getters **/

/**
 * Get a value for the 'render_wait_time' property.
 **/
Napi::Value render_wait_time_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'rpi_hw' property.
 **/
Napi::Value rpi_hw_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'freq' property.
 **/
Napi::Value freq_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'dmanum' property.
 **/
Napi::Value dmanum_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'channel' property.
 **/
Napi::Value channel_get(const Napi::CallbackInfo &info);

/** Setters **/

/**
 * Set a value for the 'freq' property.
 **/
void freq_set(const Napi::CallbackInfo &info);

/**
 * Set a value for the 'dmanum' property.
 **/
void dmanum_set(const Napi::CallbackInfo &info);

#endif
