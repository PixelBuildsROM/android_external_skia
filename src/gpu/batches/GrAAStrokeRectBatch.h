/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrAAStrokeRectBatch_DEFINED
#define GrAAStrokeRectBatch_DEFINED

#include "GrColor.h"

class GrBatch;
class GrDrawBatch;
class GrResourceProvider;
class SkMatrix;
struct SkRect;

namespace GrAAStrokeRectBatch {

GrDrawBatch* Create(GrColor color,
                    const SkMatrix& viewMatrix,
                    const SkRect& devOutside,
                    const SkRect& devOutsideAssist,
                    const SkRect& devInside,
                    bool miterStroke,
                    bool degenerate);

bool Append(GrBatch*,
            GrColor color,
            const SkMatrix& viewMatrix,
            const SkRect& devOutside,
            const SkRect& devOutsideAssist,
            const SkRect& devInside,
            bool miterStroke,
            bool degenerate);

};

#endif
