#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "module.h"

#define CHANNEL_PROPS 11
#define GAMMA_TABLE_SIZE 256

napi_ref channel_arr_ref, channel_obj_ref[RPI_PWM_CHANNELS];

napi_status init_channel_arr(napi_env env, napi_value *target);
napi_status free_channel_arr(napi_env env);

napi_status init_channel_leds_arr(napi_env, napi_value *target, int channel_arr_index);
napi_status free_channel_leds_arr(napi_env env, int channel_arr_index);
napi_status push_channel_leds_arr(napi_env env, int channel_arr_index);

napi_property_descriptor make_channel_gpionum_prop(int channel_arr_index);
napi_value               get_channel_gpionum_val(napi_env env, napi_callback_info info);
napi_value               set_channel_gpionum_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_invert_prop(int channel_arr_index);
napi_value               get_channel_invert_val(napi_env env, napi_callback_info info);
napi_value               set_channel_invert_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_count_prop(int channel_arr_index);
napi_value               get_channel_count_val(napi_env env, napi_callback_info info);
napi_value               set_channel_count_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_strip_type_prop(int channel_arr_index);
napi_value               get_channel_strip_type_val(napi_env env, napi_callback_info info);
napi_value               set_channel_strip_type_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_leds_prop(napi_env env, int channel_arr_index, napi_value value);

napi_property_descriptor make_channel_brightness_prop(int channel_arr_index);
napi_value               get_channel_brightness_val(napi_env env, napi_callback_info info);
napi_value               set_channel_brightness_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_wshift_prop(int channel_arr_index);
napi_value               get_channel_wshift_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_rshift_prop(int channel_arr_index);
napi_value               get_channel_rshift_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_gshift_prop(int channel_arr_index);
napi_value               get_channel_gshift_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_bshift_prop(int channel_arr_index);
napi_value               get_channel_bshift_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_gamma_prop(int channel_arr_index);
napi_value               get_channel_gamma_val(napi_env env, napi_callback_info info);

#endif