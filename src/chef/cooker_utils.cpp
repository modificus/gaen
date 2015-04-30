//------------------------------------------------------------------------------
// cooker_utils.h - Shared utilities used by various cookers
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2015 Lachlan Orr
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.
//------------------------------------------------------------------------------

#include "assets/file_utils.h"

#include "chef/Tga.h"

#include "chef/cooker_utils.h"

namespace gaen
{

ImageInfo read_image_info(char * path)
{
    const char * ext = get_ext(path);

    FileReader rdr(path);

    if (0 == strcmp(ext, "tga"))
    {
        Tga tga;
        rdr.read(&tga);
        return ImageInfo(kORIG_TopLeft, tga.width, tga.height);
    }
    else
    {
        PANIC("Unknown image format: %s", ext);
        return ImageInfo(kORIG_TopLeft, 0, 0);
    }
}


} // namespace gaen