/*******************************************************************************
 *
 * Copyright (c) 2004-2008 by Vivante Corp.  All rights reserved.
 *
 * The material in this file is confidential and contains trade secrets of
 * Vivante Corporation.  This is proprietary information owned by Vivante
 * Corporation.  No part of this work may be disclosed, reproduced, copied,
 * transmitted, or used in any way for any purpose, without the express
 * written permission of Vivante Corporation.
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * This file is automatically generated on Mon Apr 13 01:22:32 2009
 *
 * Any changes made to this file are lost at the next compile run!
 * So better make sure you update the source .r files instead!
 *
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//                             ~~~~~~~~~~~~~~~~~~                             //
//                             Module TextureUnit                             //
//                             ~~~~~~~~~~~~~~~~~~                             //
////////////////////////////////////////////////////////////////////////////////

// Register AQTextureSampleMode (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleModeRegAddrs                                       0x0800
#define AQ_TEXTURE_SAMPLE_MODE_Address                                   0x02000
#define AQ_TEXTURE_SAMPLE_MODE_MSB                                            15
#define AQ_TEXTURE_SAMPLE_MODE_LSB                                             4
#define AQ_TEXTURE_SAMPLE_MODE_Count                                          12
#define AQ_TEXTURE_SAMPLE_MODE_FieldMask                              0x000FFFFF
#define AQ_TEXTURE_SAMPLE_MODE_ReadMask                               0x000FFFFF
#define AQ_TEXTURE_SAMPLE_MODE_WriteMask                              0x000FFFFF
#define AQ_TEXTURE_SAMPLE_MODE_ResetValue                             0x00000000

// Texture type.
#define AQ_TEXTURE_SAMPLE_MODE_TYPE                                          2:0
#define AQ_TEXTURE_SAMPLE_MODE_TYPE_End                                        2
#define AQ_TEXTURE_SAMPLE_MODE_TYPE_Start                                      0
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_NONE                                   0x0
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_1D                                     0x1
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_2D                                     0x2
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_3D                                     0x3
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_PROJECTED                              0x4
#define   AQ_TEXTURE_SAMPLE_MODE_TYPE_CUBIC_MAP                              0x5

// Texture wrapping mode in U.
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE                                    4:3
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE_End                                  4
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE_Start                                3
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE_WRAP                             0x0
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE_MIRROR                           0x1
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_UMODE_CLAMP                            0x2

// Texture wrapping mode in V.
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE                                    6:5
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE_End                                  6
#define AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE_Start                                5
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE_WRAP                             0x0
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE_MIRROR                           0x1
#define   AQ_TEXTURE_SAMPLE_MODE_ADDR_VMODE_CLAMP                            0x2

// Minification filter type.
#define AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER                                    8:7
#define AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_End                                  8
#define AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_Start                                7
#define   AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_NONE                             0x0
#define   AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_POINT                            0x1
#define   AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_LINEAR                           0x2
#define   AQ_TEXTURE_SAMPLE_MODE_MIN_FILTER_ANISOTROPIC                      0x3

// Mip filter type. 
#define AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER                                   10:9
#define AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_End                                 10
#define AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_Start                                9
#define   AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_NONE                             0x0
#define   AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_POINT                            0x1
#define   AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_LINEAR                           0x2
#define   AQ_TEXTURE_SAMPLE_MODE_MIP_FILTER_ANISOTROPIC                      0x3

// Magnification filter type.
#define AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER                                  12:11
#define AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_End                                 12
#define AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_Start                               11
#define   AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_NONE                             0x0
#define   AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_POINT                            0x1
#define   AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_LINEAR                           0x2
#define   AQ_TEXTURE_SAMPLE_MODE_MAG_FILTER_ANISOTROPIC                      0x3

// Texture Format.
#define AQ_TEXTURE_SAMPLE_MODE_FORMAT                                      17:13
#define AQ_TEXTURE_SAMPLE_MODE_FORMAT_End                                     17
#define AQ_TEXTURE_SAMPLE_MODE_FORMAT_Start                                   13
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_A8                                  0x01
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_L8                                  0x02
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_I8                                  0x03
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_A8L8                                0x04
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_ARGB4                               0x05
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_XRGB4                               0x06
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_ARGB8                               0x07
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_XRGB8                               0x08
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_ABGR8                               0x09
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_XBGR8                               0x0A
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_R5G6B5                              0x0B
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_A1RGB5                              0x0C
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_X1RGB5                              0x0D
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_YUY2                                0x0E
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_UYVY                                0x0F
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_D16                                 0x10
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_D24X8                               0x11
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_A8_OES                              0x12
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_DXT1                                0x13
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_DXT2                                0x14
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_DXT3                                0x14
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_DXT4                                0x15
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_DXT5                                0x15
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_HDR7E3                              0x16
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_HDR6E4                              0x17
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_HDR5E5                              0x18
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_HDR6E5                              0x19
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_RGBE8                               0x1A
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_RGBE8F                              0x1B
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_RGB9E5                              0x1C
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_RGB9E5F                             0x1D
#define   AQ_TEXTURE_SAMPLE_MODE_FORMAT_ETC1                                0x1E

// Filter Constant
#define AQ_TEXTURE_SAMPLE_MODE_FILTER_CONSTANT                             18:18
#define AQ_TEXTURE_SAMPLE_MODE_FILTER_CONSTANT_End                            18
#define AQ_TEXTURE_SAMPLE_MODE_FILTER_CONSTANT_Start                          18
#define   AQ_TEXTURE_SAMPLE_MODE_FILTER_CONSTANT_DISABLE                     0x0
#define   AQ_TEXTURE_SAMPLE_MODE_FILTER_CONSTANT_ENABLE                      0x1

// Round U and V coordinates.
#define AQ_TEXTURE_SAMPLE_MODE_ROUND_UV                                    19:19
#define AQ_TEXTURE_SAMPLE_MODE_ROUND_UV_End                                   19
#define AQ_TEXTURE_SAMPLE_MODE_ROUND_UV_Start                                 19
#define   AQ_TEXTURE_SAMPLE_MODE_ROUND_UV_DISABLE                            0x0
#define   AQ_TEXTURE_SAMPLE_MODE_ROUND_UV_ENABLE                             0x1

// Register AQTextureSampleWH (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleWHRegAddrs                                         0x0810
#define AQ_TEXTURE_SAMPLE_WH_Address                                     0x02040
#define AQ_TEXTURE_SAMPLE_WH_MSB                                              15
#define AQ_TEXTURE_SAMPLE_WH_LSB                                               4
#define AQ_TEXTURE_SAMPLE_WH_Count                                            12
#define AQ_TEXTURE_SAMPLE_WH_FieldMask                                0x3FFF3FFF
#define AQ_TEXTURE_SAMPLE_WH_ReadMask                                 0x3FFF3FFF
#define AQ_TEXTURE_SAMPLE_WH_WriteMask                                0x3FFF3FFF
#define AQ_TEXTURE_SAMPLE_WH_ResetValue                               0x00000000

// Texture width size in integer format.
#define AQ_TEXTURE_SAMPLE_WH_INT_WIDTH                                      13:0
#define AQ_TEXTURE_SAMPLE_WH_INT_WIDTH_End                                    13
#define AQ_TEXTURE_SAMPLE_WH_INT_WIDTH_Start                                   0

// Texture height size in integer format.
#define AQ_TEXTURE_SAMPLE_WH_INT_HEIGHT                                    29:16
#define AQ_TEXTURE_SAMPLE_WH_INT_HEIGHT_End                                   29
#define AQ_TEXTURE_SAMPLE_WH_INT_HEIGHT_Start                                 16

// Register AQTextureSampleLogWH (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLogWHRegAddrs                                      0x0820
#define AQ_TEXTURE_SAMPLE_LOG_WH_Address                                 0x02080
#define AQ_TEXTURE_SAMPLE_LOG_WH_MSB                                          15
#define AQ_TEXTURE_SAMPLE_LOG_WH_LSB                                           4
#define AQ_TEXTURE_SAMPLE_LOG_WH_Count                                        12
#define AQ_TEXTURE_SAMPLE_LOG_WH_FieldMask                            0x000FFFFF
#define AQ_TEXTURE_SAMPLE_LOG_WH_ReadMask                             0x000FFFFF
#define AQ_TEXTURE_SAMPLE_LOG_WH_WriteMask                            0x000FFFFF
#define AQ_TEXTURE_SAMPLE_LOG_WH_ResetValue                           0x00000000

// Log of texture width size.
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_WIDTH                                   9:0
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_WIDTH_End                                 9
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_WIDTH_Start                               0

// Log of texture width size.
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_HEIGHT                                19:10
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_HEIGHT_End                               19
#define AQ_TEXTURE_SAMPLE_LOG_WH_LOG_HEIGHT_Start                             10

// Register AQTextureSampleLod (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLodRegAddrs                                        0x0830
#define AQ_TEXTURE_SAMPLE_LOD_Address                                    0x020C0
#define AQ_TEXTURE_SAMPLE_LOD_MSB                                             15
#define AQ_TEXTURE_SAMPLE_LOD_LSB                                              4
#define AQ_TEXTURE_SAMPLE_LOD_Count                                           12
#define AQ_TEXTURE_SAMPLE_LOD_FieldMask                               0x7FFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD_ReadMask                                0x7FFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD_WriteMask                               0x7FFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD_ResetValue                              0x00000000

// Disable/Enable LOD Bias
#define AQ_TEXTURE_SAMPLE_LOD_EN_LOD_BIAS                                    0:0
#define AQ_TEXTURE_SAMPLE_LOD_EN_LOD_BIAS_End                                  0
#define AQ_TEXTURE_SAMPLE_LOD_EN_LOD_BIAS_Start                                0
#define   AQ_TEXTURE_SAMPLE_LOD_EN_LOD_BIAS_DISABLE                          0x0
#define   AQ_TEXTURE_SAMPLE_LOD_EN_LOD_BIAS_ENABLE                           0x1

// Max LOD in 5.5 fixed point format.
#define AQ_TEXTURE_SAMPLE_LOD_MAX_LOD_FIX5DOT5                              10:1
#define AQ_TEXTURE_SAMPLE_LOD_MAX_LOD_FIX5DOT5_End                            10
#define AQ_TEXTURE_SAMPLE_LOD_MAX_LOD_FIX5DOT5_Start                           1

// Min LOD in 5.5 fixed point format.
#define AQ_TEXTURE_SAMPLE_LOD_MIN_LOD_FIX5DOT5                             20:11
#define AQ_TEXTURE_SAMPLE_LOD_MIN_LOD_FIX5DOT5_End                            20
#define AQ_TEXTURE_SAMPLE_LOD_MIN_LOD_FIX5DOT5_Start                          11

// User LOD bias in 5.5 fixed point format.
#define AQ_TEXTURE_SAMPLE_LOD_BIAS_LOD_FIX5DOT5                            30:21
#define AQ_TEXTURE_SAMPLE_LOD_BIAS_LOD_FIX5DOT5_End                           30
#define AQ_TEXTURE_SAMPLE_LOD_BIAS_LOD_FIX5DOT5_Start                         21

////////////////////////////////////////////////////////////////////////////////
//                             ~~~~~~~~~~~~~~~~~~~                            //
//                             Module AQTetxureLOD                            //
//                             ~~~~~~~~~~~~~~~~~~~                            //
////////////////////////////////////////////////////////////////////////////////

// Register AQTextureSampleLod00Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod00AddressRegAddrs                               0x0900
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_Address                          0x02400
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_ResetValue                    0x00000000

// Address of LOD 0
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD00_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod01Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod01AddressRegAddrs                               0x0910
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_Address                          0x02440
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_ResetValue                    0x00000000

// Address of LOD 1
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD01_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod02Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod02AddressRegAddrs                               0x0920
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_Address                          0x02480
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_ResetValue                    0x00000000

// Address of LOD 2
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD02_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod03Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod03AddressRegAddrs                               0x0930
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_Address                          0x024C0
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_ResetValue                    0x00000000

// Address of LOD 3
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD03_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod04Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod04AddressRegAddrs                               0x0940
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_Address                          0x02500
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_ResetValue                    0x00000000

// Address of LOD 4
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD04_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod05Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod05AddressRegAddrs                               0x0950
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_Address                          0x02540
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_ResetValue                    0x00000000

// Address of LOD 5
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD05_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod06Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod06AddressRegAddrs                               0x0960
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_Address                          0x02580
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_ResetValue                    0x00000000

// Address of LOD 6
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD06_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod07Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod07AddressRegAddrs                               0x0970
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_Address                          0x025C0
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_ResetValue                    0x00000000

// Address of LOD 7
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD07_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod08Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod08AddressRegAddrs                               0x0980
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_Address                          0x02600
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_ResetValue                    0x00000000

// Address of LOD 8
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD08_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod09Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod09AddressRegAddrs                               0x0990
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_Address                          0x02640
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_ResetValue                    0x00000000

#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD09_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod10Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod10AddressRegAddrs                               0x09A0
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_Address                          0x02680
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_ResetValue                    0x00000000

#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD10_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod11Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod11AddressRegAddrs                               0x09B0
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_Address                          0x026C0
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_ResetValue                    0x00000000

#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD11_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod12Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod12AddressRegAddrs                               0x09C0
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_Address                          0x02700
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_ResetValue                    0x00000000

#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD12_ADDRESS_ADDR_Start                             0

// Register AQTextureSampleLod13Address (12 in total).
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define AQTextureSampleLod13AddressRegAddrs                               0x09D0
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_Address                          0x02740
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_MSB                                   15
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_LSB                                    4
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_Count                                 12
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_FieldMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_ReadMask                      0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_WriteMask                     0xFFFFFFFF
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_ResetValue                    0x00000000

#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_ADDR                                31:0
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_ADDR_End                              31
#define AQ_TEXTURE_SAMPLE_LOD13_ADDRESS_ADDR_Start                             0

////////////////////////////////////////////////////////////////////////////////
//                              ~~~~~~~~~~~~~~~~~                             //
//                              Command AQTexture                             //
//                              ~~~~~~~~~~~~~~~~~                             //
////////////////////////////////////////////////////////////////////////////////

// Offset AQTextureToShader.
// ~~~~~~~~~~~~~~~~~~~~~~~~

#define AQ_TEXTURE_TO_SHADER_FORMAT                                          2:0
#define AQ_TEXTURE_TO_SHADER_FORMAT_End                                        2
#define AQ_TEXTURE_TO_SHADER_FORMAT_Start                                      0
#define   AQ_TEXTURE_TO_SHADER_FORMAT_INTERNAL                               0x0
#define   AQ_TEXTURE_TO_SHADER_FORMAT_U16                                    0x1
#define   AQ_TEXTURE_TO_SHADER_FORMAT_U24                                    0x2
#define   AQ_TEXTURE_TO_SHADER_FORMAT_RGBE8                                  0x3
#define   AQ_TEXTURE_TO_SHADER_FORMAT_RGB9E5                                 0x4

// Offset AQTexture.
// ~~~~~~~~~~~~~~~~

#define AQ_TEXTURE_TYPE                                                      2:0
#define AQ_TEXTURE_TYPE_End                                                    2
#define AQ_TEXTURE_TYPE_Start                                                  0
#define   AQ_TEXTURE_TYPE_NONE                                               0x0
#define   AQ_TEXTURE_TYPE_1D                                                 0x1
#define   AQ_TEXTURE_TYPE_2D                                                 0x2
#define   AQ_TEXTURE_TYPE_3D                                                 0x3
#define   AQ_TEXTURE_TYPE_PROJECTED                                          0x4
#define   AQ_TEXTURE_TYPE_CUBIC_MAP                                          0x5

#define AQ_TEXTURE_ADDRESS_MODE                                              4:3
#define AQ_TEXTURE_ADDRESS_MODE_End                                            4
#define AQ_TEXTURE_ADDRESS_MODE_Start                                          3
#define   AQ_TEXTURE_ADDRESS_MODE_WRAP                                       0x0
#define   AQ_TEXTURE_ADDRESS_MODE_MIRROR                                     0x1
#define   AQ_TEXTURE_ADDRESS_MODE_CLAMP                                      0x2

#define AQ_TEXTURE_FORMAT                                                    9:5
#define AQ_TEXTURE_FORMAT_End                                                  9
#define AQ_TEXTURE_FORMAT_Start                                                5
#define   AQ_TEXTURE_FORMAT_A8                                              0x01
#define   AQ_TEXTURE_FORMAT_L8                                              0x02
#define   AQ_TEXTURE_FORMAT_I8                                              0x03
#define   AQ_TEXTURE_FORMAT_A8L8                                            0x04
#define   AQ_TEXTURE_FORMAT_ARGB4                                           0x05
#define   AQ_TEXTURE_FORMAT_XRGB4                                           0x06
#define   AQ_TEXTURE_FORMAT_ARGB8                                           0x07
#define   AQ_TEXTURE_FORMAT_XRGB8                                           0x08
#define   AQ_TEXTURE_FORMAT_ABGR8                                           0x09
#define   AQ_TEXTURE_FORMAT_XBGR8                                           0x0A
#define   AQ_TEXTURE_FORMAT_R5G6B5                                          0x0B
#define   AQ_TEXTURE_FORMAT_A1RGB5                                          0x0C
#define   AQ_TEXTURE_FORMAT_X1RGB5                                          0x0D
#define   AQ_TEXTURE_FORMAT_YUY2                                            0x0E
#define   AQ_TEXTURE_FORMAT_UYVY                                            0x0F
#define   AQ_TEXTURE_FORMAT_D16                                             0x10
#define   AQ_TEXTURE_FORMAT_D24X8                                           0x11
#define   AQ_TEXTURE_FORMAT_A8_OES                                          0x12
#define   AQ_TEXTURE_FORMAT_DXT1                                            0x13
#define   AQ_TEXTURE_FORMAT_DXT2                                            0x14
#define   AQ_TEXTURE_FORMAT_DXT3                                            0x14
#define   AQ_TEXTURE_FORMAT_DXT4                                            0x15
#define   AQ_TEXTURE_FORMAT_DXT5                                            0x15
#define   AQ_TEXTURE_FORMAT_HDR7E3                                          0x16
#define   AQ_TEXTURE_FORMAT_HDR6E4                                          0x17
#define   AQ_TEXTURE_FORMAT_HDR5E5                                          0x18
#define   AQ_TEXTURE_FORMAT_HDR6E5                                          0x19
#define   AQ_TEXTURE_FORMAT_RGBE8                                           0x1A
#define   AQ_TEXTURE_FORMAT_RGBE8F                                          0x1B
#define   AQ_TEXTURE_FORMAT_RGB9E5                                          0x1C
#define   AQ_TEXTURE_FORMAT_RGB9E5F                                         0x1D
#define   AQ_TEXTURE_FORMAT_ETC1                                            0x1E

#define AQ_TEXTURE_FILTER                                                  11:10
#define AQ_TEXTURE_FILTER_End                                                 11
#define AQ_TEXTURE_FILTER_Start                                               10
#define   AQ_TEXTURE_FILTER_NONE                                             0x0
#define   AQ_TEXTURE_FILTER_POINT                                            0x1
#define   AQ_TEXTURE_FILTER_LINEAR                                           0x2
#define   AQ_TEXTURE_FILTER_ANISOTROPIC                                      0x3

// Define AQConst.
// ~~~~~~~~~~~~~~
#define   AQ_CONST_VS_TEXTURE_SAMPLES                                 0x00000004
#define   AQ_CONST_PS_TEXTURE_SAMPLES                                 0x00000008
#define   AQ_CONST_LOD_COUNT                                          0x0000000E

// Define AQTextureLoad.
// ~~~~~~~~~~~~~~~~~~~~
#define   AQ_TEXTURE_LOAD_PLAIN                                       0x00000000
#define   AQ_TEXTURE_LOAD_USER_LOD_BIAS                               0x00000001
#define   AQ_TEXTURE_LOAD_USER_LOD                                    0x00000002
#define   AQ_TEXTURE_LOAD_PCF                                         0x00000003

