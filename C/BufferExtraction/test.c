#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COL (2080UL)
#define MAX_ROW (3096UL)
#define MAX_BUFF_SIZE (MAX_COL * MAX_ROW)

// Stubbing this function to be able to test the blue pixels extraction
int GetImagineBufferSize(uint32_t* pBufferSize)
{
    *pBufferSize = (uint32_t) MAX_BUFF_SIZE;
    return 0;
}

// Same for this one
int GetImagingData(uint8_t* pBuffer, uint32_t* pBuffSize)
{
    int err = GetImagineBufferSize(pBuffSize);

    if (0 == err)
    {
        // Reject requests with invalid size, otherwise we may
        // write data to the wrong place
        if (MAX_BUFF_SIZE < *pBuffSize)
        {
            return -1;
        }

        // Erase pBuffSize
        memset(pBuffer, 0, *pBuffSize * sizeof(uint8_t));
        for (uint32_t i = 1 ; i < (MAX_ROW / 2) ; i++)
        {
            for (uint32_t j = 1 ; j < (MAX_COL / 2); j++)
            {
                pBuffer[(i * 2 - 1) * MAX_COL + (j * 2 -1)] = 1U;
            }
        }
    }
    return err;
}

// Debug functionality to help print out the content of buffers
void printBuffer(const uint32_t max_row , const uint32_t max_col, const uint32_t max_columns,  uint8_t* pBuffer)
{
    for (uint32_t i = 0 ; i < max_row ; i++)
    {
        for (uint32_t j = 0 ; j < max_col ; j++)
        {
            printf("%d ", pBuffer[i * max_columns + j]);
        }
        printf("\n");
    }
}

/**
 * @brief this enum gives information about internal error of either
 * the camera driver.
*/
typedef enum
{
    IMAGE_ERR_OK = 0,                   /**< All good                                                   */
    IMAGE_ERR_NULLPTR,                  /**< One or more null pointer was given                         */
    IMAGE_ERR_OUT_OF_BOUNDS_BUFFER,     /**< Given buffer is out of bounds                              */
    IMAGE_ERR_CAMERA_ISSUE              /**< Caught an error while trying to reach camera's hardware    */
} image_error_t;

image_error_t GetBlueImageRaw(uint8_t* pBuffer)
{
    image_error_t ret = IMAGE_ERR_OK;

    // A regular Assert would play the same role, but
    // That's always a good idea to check input!
    if (NULL == pBuffer)
    {
        ret = IMAGE_ERR_NULLPTR;
    }

    // Extract blue pixels from raw image (not unmatriced yet)
    if (IMAGE_ERR_OK == ret)
    {
        // Blue pixels x and y are located into x = y = 2k - 1 ; with k > 0
        uint32_t buffer_size;
        // Agregate allocation and initialization to 0
        uint8_t* raw_buffer = (uint8_t*) calloc(MAX_COL * MAX_ROW, sizeof(uint8_t));

        int camera_err = GetImagineBufferSize(&buffer_size);
        if (0 != camera_err)
        {
            ret = IMAGE_ERR_CAMERA_ISSUE;
        }
        else
        {
            // Not sure what GetImagingData will do with the buffer size, no documentation provided!
            camera_err = GetImagingData(raw_buffer, &buffer_size);
        }

        // Reject camera driver error, we don't want to use garbage data
        if (0 != camera_err)
        {
            ret = IMAGE_ERR_CAMERA_ISSUE;
        }
        else
        {
            // Iterate over rows
            for (uint32_t row = 1 ; row < (MAX_ROW / 2) ; row++ )
            {
                for (uint32_t col = 1 ; col < (MAX_COL / 2) ; col++)
                {
                    // pBuffer is half the width and length of raw_buffer, so it has 3096/2 = 1548 columns and 2080/2 = 1040 rows.
                    uint8_t* pBufferPixel = &pBuffer[(row - 1) * (MAX_COL / 2)+ (col - 1) ];
                    uint8_t* rawBufferPixel = &raw_buffer[(row * 2 - 1) * MAX_COL + (col * 2 - 1)];

                    // Copy data to pBuffer using pointers (not necessary but illustrates the thinking process)
                    *pBufferPixel = *rawBufferPixel;
                }

            }
            free(raw_buffer);
        }
    }

    return ret;
}

int main(void)
{
    image_error_t err = IMAGE_ERR_OK;
    uint8_t* blue_buffer = (uint8_t*) calloc((MAX_COL/2) * (MAX_ROW/2), sizeof(uint8_t));
    uint8_t* raw_buffer = (uint8_t*) calloc((MAX_COL) * (MAX_ROW), sizeof(uint8_t));
    err = GetBlueImageRaw(blue_buffer);
    if (IMAGE_ERR_OK != err)
    {
        // handles this error
    }

    printBuffer(20, 20, MAX_COL/2, blue_buffer);
    uint32_t BufferSize = 0;
    GetImagingData(raw_buffer, &BufferSize);
    printf("\n\n\n\n");
    printBuffer(50, 50, MAX_COL, raw_buffer);

    free(blue_buffer);
    free(raw_buffer);
    return 0;
}