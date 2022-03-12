#ifndef CHANNEL_H
#define CHANNEL_H

#include "../module.h"

/**
 * Create a new channel array.
 **/
Napi::Array init_channel(Napi::Env env);

/** Descriptors **/

/**
 * Create an accessor descriptor to the 'gpionum' property.
 **/
extern Napi::PropertyDescriptor gpionum_desc(void *data);

/**
 * Create an accessor descriptor to the 'invert' property.
 **/
extern Napi::PropertyDescriptor invert_desc(void *data);

/**
 * Create an accessor descriptor to the 'count' property.
 **/
extern Napi::PropertyDescriptor count_desc(void *data);

/**
 * Create an accessor descriptor to the 'strip_type' property.
 **/
extern Napi::PropertyDescriptor strip_type_desc(void *data);

/**
 * Create an accessor descriptor to the 'leds' property.
 **/
extern Napi::PropertyDescriptor leds_desc(void *data);

/**
 * Create an accessor descriptor to the 'brightness' property.
 **/
extern Napi::PropertyDescriptor brightness_desc(void *data);

/**
 * Create an accessor descriptor to the 'wshift' property.
 **/
extern Napi::PropertyDescriptor wshift_desc(void *data);

/**
 * Create an accessor descriptor to the 'rshift' property.
 **/
extern Napi::PropertyDescriptor rshift_desc(void *data);

/**
 * Create an accessor descriptor to the 'gshift' property.
 **/
extern Napi::PropertyDescriptor gshift_desc(void *data);

/**
 * Create an accessor descriptor to the 'bshift' property.
 **/
extern Napi::PropertyDescriptor bshift_desc(void *data);

/**
 * Create an accessor descriptor to the 'gamma' property.
 **/
extern Napi::PropertyDescriptor gamma_desc(void *data);

/** Getters **/

/**
 * Get a value for the 'gpionum' property.
 **/
Napi::Value gpionum_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'invert' property.
 **/
Napi::Value invert_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'count' property.
 **/
Napi::Value count_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'strip_type' property.
 **/
Napi::Value strip_type_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'leds' property.
 **/
Napi::Value leds_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'brightness' property.
 **/
Napi::Value brightness_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'wshift' property.
 **/
Napi::Value wshift_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'rshift' property.
 **/
Napi::Value rshift_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'gshift' property.
 **/
Napi::Value gshift_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'bshift' property.
 **/
Napi::Value bshift_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'gamma' property.
 **/
Napi::Value gamma_get(const Napi::CallbackInfo &info);

/** Setters **/

/**
 * Set a value for the 'gpionum' property.
 **/
void gpionum_set(const Napi::CallbackInfo &info);

/**
 * Set a value for the 'invert' property.
 **/
void invert_set(const Napi::CallbackInfo &info);
/**
 * Set a value for the 'count' property.
 **/
void count_set(const Napi::CallbackInfo &info);

/**
 * Set a value for the 'strip_type' property.
 **/
void strip_type_set(const Napi::CallbackInfo &info);

/**
 * Set a value for the 'leds' property.
 **/
void leds_set(const Napi::CallbackInfo &info);

/**
 * Set a value for the 'brightness' property.
 **/
void brightness_set(const Napi::CallbackInfo &info);

#endif