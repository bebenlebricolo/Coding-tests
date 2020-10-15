#ifndef _TOTO_TEST_HEADER_
#define _TOTO_TEST_HEADER_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>

#ifdef WIN32
#define TOTOTEST_API __declspec(dllexport)
#else 
#define TOTOTEST_API 
#endif

  /**
   * @brief Basic error codes .
   */
  typedef enum
  {
    TOTO_TEST_ERROR_OK,           /**< Operation went well                                            */
    TOTO_TEST_ERROR_NULL_POINTER, /**< A null pointer (uninitialized memory was used as a parameter)  */
    TOTO_TEST_ERROR_BAD_ALLOC     /**< Allocation did not went well                                   */
  } toto_test_error_codes_t;

  /**
   * @brief Basic C string .
   */
  typedef struct
  {
    char* msg;      /**< Pointer to the allocated memory containing the message data  */
    size_t length;  /**< Size of the actual string placed in memory                   */
  } string_t;

  /**
   * @brief Example structure, just to test .
   */
  typedef struct
  {
    string_t name;      /**< Fake name member                                 */
    string_t version;   /**< Fake version member                              */
    int param1;         /**< First parameter of this configuration structure  */
    int param2;         /**< Second parameter of this configuration structure */
    unsigned int param3;/**< Last parameter of this configuration structure   */
  } toto_test_config_t;

  /**
   * @brief allocates memory within the given string object .
   * @param[in]       size  : size to be allocated 
   * @param[in/out]   str   : string object to be modified
   * @return 
   *    TOTO_TEST_ERROR_OK            : operation succeeded
   *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
   *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
   */
  TOTOTEST_API toto_test_error_codes_t string_allocate(size_t size, string_t* const str);
  
  /**
  * @brief frees allocated memory of the given string
  * @param[in/out]   str   : string object to be modified
  * @return 
  *    TOTO_TEST_ERROR_OK            : operation succeeded
  *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
  *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
  */
  TOTOTEST_API toto_test_error_codes_t string_destroy(string_t* const str);

  /**
   * @brief Initializes config object .
   * @param[in/out] config  : configuration to be initialized
   * @return
   *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
   */
  TOTOTEST_API toto_test_error_codes_t toto_test_config_init(toto_test_config_t* const config);

  /**
   * @brief Allocates memory to fill toto_test_config object.
   * @param[in]  name_length     : size of the string to be allocated
   * @param[in]  version_length  : size of the string to be allocated
   * @param[out] config          : configuration object to be allocated
   * @return
   *    TOTO_TEST_ERROR_OK            : operation succeeded
   *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
   *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
   */
  TOTOTEST_API toto_test_error_codes_t toto_test_config_allocate(const size_t name_length, const size_t version_length, toto_test_config_t* const config);

  /**
  * @brief Allocates memory for the name member and copies input data into the newly created memory slot
  * @param[in]  name    : input name in the form of a c string array
  * @param[in]  size    : size of the input data
  * @param[out] config  : configuration object to be modified
  * @return
  *    TOTO_TEST_ERROR_OK            : operation succeeded
  *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
  *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
  */
  TOTOTEST_API toto_test_error_codes_t toto_test_config_set_name(char const* const name, size_t size, toto_test_config_t* const config);

  /**
  * @brief Allocates memory for the name member and copies input data into the newly created memory slot
  * @param[in]  version : input version in the form of a c string array
  * @param[in]  size    : size of the input data
  * @param[out] config  : configuration object to be modified
  * @return
  *    TOTO_TEST_ERROR_OK            : operation succeeded
  *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
  *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
  */
  TOTOTEST_API toto_test_error_codes_t toto_test_config_set_version(char const* const version, size_t size, toto_test_config_t* const config);

  /**
  * @brief Releases ownership on data and frees memory
  * @param[out] config          : configuration object to be allocated
  * @return
  *    TOTO_TEST_ERROR_OK            : operation succeeded
  *    TOTO_TEST_ERROR_NULL_POINTER  : Uninitialised memory was given as input (null pointer)
  *    TOTO_TEST_ERROR_BAD_ALLOC     : Error while allocating memory for this object
  */
  TOTOTEST_API toto_test_error_codes_t toto_test_config_destroy(toto_test_config_t* const config);


#ifdef __cplusplus
}
#endif


#endif /* _TOTO_TEST_HEADER_ */