//------------------------------------------------------------------------------
// Gimg.cpp - Runtime image format
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2016 Lachlan Orr
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

#include "core/HashMap.h"
#include "core/String.h"

#include "assets/Gimg.h"

namespace gaen
{

typedef HashMap<kMEM_Const, PixelFormat, String<kMEM_Const>> PixelFormatToStrMap;
typedef HashMap<kMEM_Const, String<kMEM_Const>, PixelFormat> PixelFormatFromStrMap;

const char * pixel_format_to_str(PixelFormat pixelFormat)
{
    static const PixelFormatToStrMap map =
        {{ kPXL_R8,        "R8"        },
         { kPXL_RGB8,      "RGB8"      },
         { kPXL_RGBA8,     "RGBA8"     },
         { kPXL_RGB_DXT1,  "RGB_DXT1"  },
         { kPXL_RGBA_DXT1, "RGBA_DXT1" },
         { kPXL_RGBA_DXT3, "RGBA_DXT3" },
         { kPXL_RGBA_DXT5, "RGBA_DXT5" }
        };

    auto it = map.find(pixelFormat);
    PANIC_IF(it == map.end(), "Invalid PixelFormat: %d", pixelFormat);
    return it->second.c_str();
}

const PixelFormat pixel_format_from_str(const char * str)
{
    static const PixelFormatFromStrMap map =
        {{ "R8",        kPXL_R8 },
         { "RGB8",      kPXL_RGB8 },
         { "RGBA8",     kPXL_RGBA8 },
         { "RGB_DXT1",  kPXL_RGB_DXT1 },
         { "RGBA_DXT1", kPXL_RGBA_DXT1 },
         { "RGBA_DXT3", kPXL_RGBA_DXT3 },
         { "RGBA_DXT5", kPXL_RGBA_DXT5 }
        };

    auto it = map.find(str);
    PANIC_IF(it == map.end(), "Invlaid PixelFormat string: %s", str);
    return it->second;
}


bool Gimg::is_valid(const u8 * pBuffer, u32 size)
{
    if (size < sizeof(Gimg))
        return false;

    const Gimg * pGimg = reinterpret_cast<const Gimg*>(pBuffer);

    if (pGimg->totalSize() != size)
        return false;

    switch (pGimg->mPixelFormat)
    {
    case kPXL_RGB_DXT1:
    case kPXL_RGBA_DXT1:
    case kPXL_RGBA_DXT3:
    case kPXL_RGBA_DXT5:
        // DXT textures should have multiples of 4 for width and height
        if (pGimg->mWidth % 4 != 0 || pGimg->mHeight % 4 != 0)
            return false;
    }

    return true;
}

u32 Gimg::required_size(PixelFormat pixelFormat, u32 width, u32 height)
{
    u32 size = sizeof(Gimg);
    
    switch (pixelFormat)
    {
    case kPXL_R8:
        size += width * height;
        break;
    case kPXL_RGB8:
        size += width * height * 3;
        break;
    case kPXL_RGBA8:
        size += width * height * 4;
        break;
    case kPXL_RGB_DXT1:
    case kPXL_RGBA_DXT1:
        PANIC_IF(width % 4 != 0 || height % 4 != 0, "DXT1 texture with width or height not a multiple of 4");
        size += width * height / 2; // every block of 16 pixels becomes 8 bytes
        break;
    case kPXL_RGBA_DXT3:
    case kPXL_RGBA_DXT5:
        PANIC_IF(width % 4 != 0 || height % 4 != 0, "DXT texture with width or height not a multiple of 4");
        size += width * height; // every block of 16 pixels becomes 16 bytes
        break;
    }

    return size;
}

Gimg * Gimg::create(MemType memType, PixelFormat pixelFormat, u32 width, u32 height)
{
    u32 size = Gimg::required_size(pixelFormat, width, height);
    Gimg * pGimg = (Gimg*)GALLOC(memType, size);
    pGimg->mPixelFormat = pixelFormat;
    pGimg->mWidth = width;
    pGimg->mHeight = height;
    return pGimg;
}

u32 Gimg::totalSize() const
{
    return required_size(mPixelFormat, mWidth, mHeight);
}

u8 * Gimg::scanline(u32 idx)
{
    PANIC_IF(idx + 1 > mHeight, "Invalid scanline %d, for image with height %d", idx, mHeight);
    
    u8 * pScanline = (u8*)this + sizeof(Gimg);
    
    switch (mPixelFormat)
    {
    case kPXL_R8:
        pScanline += idx * mWidth;
        break;
    case kPXL_RGB8:
        pScanline += idx * mWidth * 3;
        break;
    case kPXL_RGBA8:
        pScanline += idx * mWidth * 4;
        break;
    default:
        PANIC("Unable to return scanline for this PixelFormat: %s", pixel_format_to_str(mPixelFormat));
        break;
    }

    return pScanline;
}

const u8 * Gimg::scanline(u32 idx) const
{
    Gimg * pGimg = const_cast<Gimg*>(this);
    return pGimg->scanline(idx);
}

void Gimg::convertFormat(Gimg ** pGimgOut, MemType memType, PixelFormat newPixelFormat) const
{
    Gimg *pGimg = Gimg::create(kMEM_Chef, newPixelFormat, mWidth, mHeight);
    *pGimgOut = pGimg;

    if (mPixelFormat == newPixelFormat)
    {
        memcpy(pGimg, this, totalSize());
        return;
    }

    switch (mPixelFormat)
    {
    case kPXL_R8:
    {
        switch (newPixelFormat)
        {
        case kPXL_RGB8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = pix;
                    u32 tpix = 3 * pix;
                    toLine[tpix+0] = fromLine[fpix];
                    toLine[tpix+1] = fromLine[fpix];
                    toLine[tpix+2] = fromLine[fpix];
                }
            }
            return;
        }
        case kPXL_RGBA8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = pix;
                    u32 tpix = 4 * pix;
                    toLine[tpix+0] = fromLine[fpix];
                    toLine[tpix+1] = fromLine[fpix];
                    toLine[tpix+2] = fromLine[fpix];
                    toLine[tpix+3] = 255;
                }
            }
            return;
        }
        }
        break;
    }
    case kPXL_RGB8:
    {
        switch (newPixelFormat)
        {
        case kPXL_R8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = 3 * pix;
                    u32 tpix = pix;

                    u8 lum = luminance(fromLine[fpix+0],
                                       fromLine[fpix+1],
                                       fromLine[fpix+2]);
                    toLine[tpix] = lum;
                }
            }
            return;
        }
        case kPXL_RGBA8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = 3 * pix;
                    u32 tpix = 4 * pix;

                    toLine[tpix+0] = fromLine[fpix+0];
                    toLine[tpix+1] = fromLine[fpix+1];
                    toLine[tpix+2] = fromLine[fpix+2];
                    toLine[tpix+3] = 255;
                }
            }
            return;
        }
        }
        break;
    }
    case kPXL_RGBA8:
    {
        switch (newPixelFormat)
        {
        case kPXL_R8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = 4 * pix;
                    u32 tpix = pix;

                    u8 lum = luminance(fromLine[fpix+0],
                                       fromLine[fpix+1],
                                       fromLine[fpix+2]);
                    toLine[tpix] = lum;
                }
            }
            return;
        }
        case kPXL_RGB8:
        {
            for (u32 line = 0; line < mHeight; ++line)
            {
                const u8 * fromLine = scanline(line);
                u8 * toLine = pGimg->scanline(line);
                for (u32 pix = 0; pix < mWidth; ++pix)
                {
                    u32 fpix = 4 * pix;
                    u32 tpix = 3 * pix;

                    toLine[tpix+0] = fromLine[fpix+0];
                    toLine[tpix+1] = fromLine[fpix+1];
                    toLine[tpix+2] = fromLine[fpix+2];
                }
            }
            return;
        }
        }
        break;
    }
    }

    GFREE(pGimg);
    PANIC("Unsupported Gimg conversion from: %d -> %d", mPixelFormat, newPixelFormat);
}



} // namespace gaen

