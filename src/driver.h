#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "channel.h"
#include "module.h"
#include "rpi_hw.h"

#define DRIVER_PROPS 10

napi_ref driver_obj_ref;

napi_status init_driver_obj(napi_env env, napi_value *target);
napi_status free_driver_obj(napi_env env);

napi_property_descriptor make_render_wait_time_prop();
napi_value               get_render_wait_time_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_rpi_hw_prop();
napi_value               get_rpi_hw_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_freq_prop();
napi_value               get_freq_val(napi_env env, napi_callback_info info);
napi_value               set_freq_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_dmanum_prop();
napi_value               get_dmanum_val(napi_env env, napi_callback_info info);
napi_value               set_dmanum_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_channel_prop();
napi_value               get_channel_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_init_prop();
napi_value               run_init_func(napi_env env, napi_callback_info info);

napi_property_descriptor make_fini_prop();
napi_value               run_fini_func(napi_env env, napi_callback_info info);

napi_property_descriptor make_render_prop();
napi_value               run_render_func(napi_env env, napi_callback_info info);

napi_property_descriptor make_wait_prop();
napi_value               run_wait_func(napi_env env, napi_callback_info info);

napi_property_descriptor make_set_custom_gamma_factor_prop();
napi_value               run_set_custom_gamma_factor_func(napi_env env, napi_callback_info info);

#endif