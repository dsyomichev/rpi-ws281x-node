#ifndef _RPI_HW_H_
#define _RPI_HW_H_

#include "module.h"

#define RPI_HW_PROPS 5

napi_ref rpi_hw_obj_ref;

napi_status init_rpi_hw_obj(napi_env env, napi_value *target);
napi_status free_rpi_hw_obj(napi_env env);

napi_property_descriptor make_rpi_hw_type_prop(napi_env env);
napi_value               get_rpi_hw_type_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_rpi_hw_hwver_prop(napi_env env);
napi_value               get_rpi_hw_hwver_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_rpi_hw_periph_base_prop(napi_env env);
napi_value               get_rpi_hw_periph_base_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_rpi_hw_videocore_base_prop(napi_env env);
napi_value               get_rpi_hw_videocore_base_val(napi_env env, napi_callback_info info);

napi_property_descriptor make_rpi_hw_desc_prop(napi_env env);
napi_value               get_rpi_hw_desc_val(napi_env env, napi_callback_info info);

#endif