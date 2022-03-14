#include "driver.h"

napi_ref driver_obj_ref;

napi_status init_driver_obj(napi_env env, napi_value *target) {
  napi_status              status;
  napi_property_descriptor prop[DRIVER_PROPS];
  napi_value               rpi_hw_obj, channel_arr;

  status = napi_create_object(env, target);

  if (status != napi_ok) {
    return status;
  }

  status = init_rpi_hw_obj(env, &rpi_hw_obj);

  if (status != napi_ok) {
    return status;
  }

  status = init_channel_arr(env, &channel_arr);

  if (status != napi_ok) {
    return status;
  }

  prop[0] = make_render_wait_time_prop();
  prop[1] = make_rpi_hw_prop();
  prop[2] = make_freq_prop();
  prop[3] = make_dmanum_prop();
  prop[4] = make_channel_prop();
  prop[5] = make_init_prop();
  prop[6] = make_fini_prop();
  prop[7] = make_render_prop();
  prop[8] = make_wait_prop();
  prop[9] = make_set_custom_gamma_factor_prop();

  status = napi_define_properties(env, *target, DRIVER_PROPS, prop);

  if (status != napi_ok) {
    return status;
  }

  status = napi_create_reference(env, *target, 1, &driver_obj_ref);

  if (status != napi_ok) {
    return status;
  }

  return status;
}

napi_status free_driver_obj(napi_env env) {
  napi_status status;

  status = free_reference(env, driver_obj_ref);

  return status;
}

napi_property_descriptor make_render_wait_time_prop() {
  static char      name[] = "render_wait_time";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_accessor_prop(name, &get_render_wait_time_val, NULL, &data);
}

napi_value get_render_wait_time_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = napi_create_bigint_int64(env, ws2811.render_wait_time, &result);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  return result;
}

napi_property_descriptor make_rpi_hw_prop() {
  static char      name[] = "rpi_hw";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_accessor_prop(name, get_rpi_hw_val, NULL, &data);
}

napi_value get_rpi_hw_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = napi_get_reference_value(env, rpi_hw_obj_ref, &target);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  return target;
}

napi_property_descriptor make_freq_prop() {
  static char      name[] = "freq";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_accessor_prop(name, &get_freq_val, set_freq_val, &data);
}

napi_value get_freq_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = napi_create_uint32(env, ws2811.freq, &result);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  return result;
}

napi_value set_freq_val(napi_env env, napi_callback_info info) {
  napi_status status;
  uint32_t    value;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = parse_arg_value_uint32(env, info, &value, NULL);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.freq = value;

  return NULL;
}

napi_property_descriptor make_dmanum_prop() {
  static char      name[] = "dmanum";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_accessor_prop(name, &get_dmanum_val, set_dmanum_val, &data);
}

napi_value get_dmanum_val(napi_env env, napi_callback_info info) {
  napi_value  result;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = napi_create_int32(env, ws2811.dmanum, &result);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  return result;
}

napi_value set_dmanum_val(napi_env env, napi_callback_info info) {
  napi_status status;
  int         value;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }
  status = parse_arg_value_int32(env, info, &value, NULL);

  if (status != napi_ok) {
    throw_invalid_arg_error(env);
    return NULL;
  }

  ws2811.dmanum = value;

  return NULL;
}

napi_property_descriptor make_channel_prop() {
  static char      name[] = "channel";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_accessor_prop(name, &get_channel_val, NULL, &data);
}

napi_value get_channel_val(napi_env env, napi_callback_info info) {
  napi_value  target;
  napi_status status;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = napi_get_reference_value(env, channel_arr_ref, &target);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  return target;
}

napi_property_descriptor make_init_prop() {
  static char      name[] = "init";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_method_prop(name, &run_init_func, &data);
}

napi_value run_init_func(napi_env env, napi_callback_info info) {
  int        status;
  napi_value rpi_hw_obj, channel_arr;
  prop_data *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = ws2811_init(&ws2811);

  if (status != WS2811_SUCCESS) {
    napi_throw_error(env, NULL, ws2811_get_return_t_str(status)); // UPDATE ERROR THROW
    return NULL;
  }

  status = free_channel_arr(env);

  if (status != napi_ok) {
    printf("Error %d", status);
    return NULL; // ADD ERROR THROW
  }

  status = init_rpi_hw_obj(env, &rpi_hw_obj);

  if (status != napi_ok) {
    return NULL; // ADD ERROR THROW
  }

  status = init_channel_arr(env, &channel_arr);

  if (status != napi_ok) {
    return NULL; // ADD ERROR THROW
  }

  return NULL;
}

napi_property_descriptor make_fini_prop() {
  static char      name[] = "fini";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_method_prop(name, &run_fini_func, &data);
}

napi_value run_fini_func(napi_env env, napi_callback_info info) {
  napi_status status;
  int         channel_arr_index;
  prop_data  *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  if (ws2811.device != NULL) { // THROW ERROR INSTEAD
    ws2811_fini(&ws2811);
  }

  status = free_rpi_hw_obj(env);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = free_channel_arr(env);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  status = free_driver_obj(env);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  for (channel_arr_index = 0; channel_arr_index < RPI_PWM_CHANNELS; channel_arr_index++) {
    status = free_channel_leds_arr(env, channel_arr_index);

    if (status != napi_ok) {
      return NULL; // ADD THROW ERROR
    }
  }

  return NULL;
}

napi_property_descriptor make_render_prop() {
  static char      name[] = "render";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_method_prop(name, &run_render_func, &data);
}

napi_value run_render_func(napi_env env, napi_callback_info info) {
  int        status, channel_arr_index;
  prop_data *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  if (ws2811.device == NULL) {
    return NULL; // THROW ERROR INSTEAD
  }

  for (channel_arr_index = 0; channel_arr_index < RPI_PWM_CHANNELS; channel_arr_index++) {
    status = push_channel_leds_arr(env, channel_arr_index);

    if (status != napi_ok) {
      return NULL; // ADD THROW ERROR
    }
  }

  status = ws2811_render(&ws2811);

  if (status != WS2811_SUCCESS) {
    napi_throw_error(env, NULL, ws2811_get_return_t_str(status)); // UPDATE THROW ERROR
    return NULL;
  }

  return NULL;
}

napi_property_descriptor make_wait_prop() {
  static char      name[] = "wait";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_method_prop(name, &run_wait_func, &data);
}

napi_value run_wait_func(napi_env env, napi_callback_info info) {
  int        status;
  prop_data *data;

  status = napi_get_cb_info(env, info, NULL, NULL, NULL, (void **)&data);

  if (status != napi_ok) {
    return NULL; // ADD THROW ERROR
  }

  if (ws2811.device == NULL) { // THROW ERROR INSTEAD
    return NULL;
  }

  status = ws2811_wait(&ws2811);

  if (status != WS2811_SUCCESS) {
    napi_throw_error(env, NULL, ws2811_get_return_t_str(status)); // UPDATE THROW ERROR
    return NULL;
  }

  return NULL;
}

napi_property_descriptor make_set_custom_gamma_factor_prop() {
  static char      name[] = "set_custom_gamma_factor";
  static prop_data data;

  data.name = name;
  data.channel_arr_index = -1;

  return make_method_prop(name, &run_set_custom_gamma_factor_func, &data);
}

napi_value run_set_custom_gamma_factor_func(napi_env env, napi_callback_info info) {
  int        status;
  double     value;
  prop_data *data;

  if (ws2811.device == NULL) { // THROW ERROR INSTEAD
    return NULL;
  }

  status = parse_arg_value_double(env, info, &value, (void **)&data);

  if (status != napi_ok) {
    throw_invalid_arg_error(env); // UPDATE THROW ERROR
    return NULL;
  }

  ws2811_set_custom_gamma_factor(&ws2811, value);

  return NULL;
}