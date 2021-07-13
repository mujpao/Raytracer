#ifndef RTSTBIMAGE_H
#define RTSTBIMAGE_H

#ifdef _MSC_VER
#pragma warning(push, 0)
#elif __GNUC__
#pragma GCC system_header
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb_image_write.h"

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
