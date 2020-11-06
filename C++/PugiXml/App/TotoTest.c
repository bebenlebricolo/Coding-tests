#include "TotoTest.h"
#include <stddef.h>
#include <string.h>

toto_test_error_codes_t string_allocate(size_t size, string_t *const str) {
  if (NULL == str) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  toto_test_error_codes_t err = TOTO_TEST_ERROR_OK;

  if (NULL == str->msg) {
    // Allocate size bytes
    str->msg = malloc(size * sizeof(char));

    // A bit of branchless programming, just for fun
    err = ((NULL == str->msg) * TOTO_TEST_ERROR_BAD_ALLOC) +
          ((NULL != str->msg) * TOTO_TEST_ERROR_OK);
    str->length = (NULL != str->msg) * size;
  }

  return err;
}

toto_test_error_codes_t string_destroy(string_t *const str) {
  if (NULL == str) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  if (NULL != str->msg) {
    free(str->msg);
    str->length = 0;
  }

  return TOTO_TEST_ERROR_OK;
}

toto_test_error_codes_t
toto_test_config_init(toto_test_config_t *const config) {
  if (NULL == config) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  config->name.length = 0;
  config->name.msg = NULL;
  config->version.length = 0;
  config->version.msg = NULL;
  config->param1 = 0;
  config->param2 = 0;
  config->param3 = 0;

  return TOTO_TEST_ERROR_OK;
}

toto_test_error_codes_t
toto_test_config_allocate(const size_t name_length, const size_t version_length,
                          toto_test_config_t *const config) {
  if (NULL == config) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  toto_test_error_codes_t ret = string_allocate(name_length, &config->name);
  if (TOTO_TEST_ERROR_OK == ret) {
    ret = string_allocate(version_length, &config->version);
  }

  return ret;
}

static toto_test_error_codes_t config_set_string(char const *const msg,
                                                 const size_t size,
                                                 string_t *const str) {
  toto_test_error_codes_t ret = TOTO_TEST_ERROR_OK;
  if ((0 == str->length) || (NULL == str->msg)) {
    ret = string_allocate(size + 1, str);
    if (TOTO_TEST_ERROR_OK != ret) {
      return ret;
    }
    strncpy(str->msg, msg, str->length);
  }

  return ret;
}

toto_test_error_codes_t
toto_test_config_set_name(char const *const name, const size_t size,
                          toto_test_config_t *const config) {
  if (NULL == config) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  return config_set_string(name, size, &config->name);
}

toto_test_error_codes_t
toto_test_config_set_version(char const *const version, const size_t size,
                             toto_test_config_t *const config) {
  if (NULL == config) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  return config_set_string(version, size, &config->version);
}

toto_test_error_codes_t
toto_test_config_destroy(toto_test_config_t *const config) {
  if (NULL == config) {
    return TOTO_TEST_ERROR_NULL_POINTER;
  }

  toto_test_error_codes_t ret = string_destroy(&config->name);
  if (TOTO_TEST_ERROR_OK != ret) {
    ret = string_destroy(&config->version);
  }
  return ret;
}
