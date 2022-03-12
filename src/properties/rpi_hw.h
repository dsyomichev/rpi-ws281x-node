#ifndef RPI_HW_H
#define RPI_HW_H

#include "../module.h"

/**
 * Create a new rpi_hw object.
 **/
extern Napi::Object init_rpi_hw(Napi::Env env);

/** Descriptors **/

/**
 * Create an accessor descriptor to the 'type' property.
 **/
extern Napi::PropertyDescriptor type_desc(void *data);

/**
 * Create an accessor descriptor to the 'hwver' property.
 **/
extern Napi::PropertyDescriptor hwver_desc(void *data);

/**
 * Create an accessor descriptor to the 'periph_base' property.
 **/
extern Napi::PropertyDescriptor periph_base_desc(void *data);

/**
 * Create an accessor descriptor to the 'videocore_base' property.
 **/
extern Napi::PropertyDescriptor videocore_base_desc(void *data);

/**
 * Create an accessor descriptor to the 'desc' property.
 **/
extern Napi::PropertyDescriptor desc_desc(void *data);

/** Getters **/

/**
 * Get a value for the 'type' property.
 **/
Napi::Value type_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'hwver' property.
 **/
Napi::Value hwver_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'periph_base' property.
 **/
Napi::Value periph_base_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'videocore_base' property.
 **/
Napi::Value videocore_base_get(const Napi::CallbackInfo &info);

/**
 * Get a value for the 'desc' property.
 **/
Napi::Value desc_get(const Napi::CallbackInfo &info);

#endif