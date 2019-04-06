/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrEllipseEffect.fp; do not modify.
 **************************************************************************************************/
#include "GrEllipseEffect.h"
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "GrTexture.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLEllipseEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLEllipseEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrEllipseEffect&   _outer      = args.fFp.cast<GrEllipseEffect>();
        (void)_outer;
        auto edgeType = _outer.edgeType();
        (void)edgeType;
        auto center = _outer.center();
        (void)center;
        auto radii = _outer.radii();
        (void)radii;
        prevRadii   = float2(-1.0);
        useScale    = !sk_Caps.floatIs32Bits;
        fEllipseVar = args.fUniformHandler->addUniform(
                kFragment_GrShaderFlag, kFloat4_GrSLType, "ellipse");
        if (useScale) {
            fScaleVar = args.fUniformHandler->addUniform(
                    kFragment_GrShaderFlag, kFloat2_GrSLType, "scale");
        }
        fragBuilder->codeAppendf(
                "float2 prevCenter;\nfloat2 prevRadii = float2(%f, %f);\nbool useScale = "
                "%s;\nfloat2 d = sk_FragCoord.xy - %s.xy;\n@if (useScale) {\n    d *= "
                "%s.y;\n}\nfloat2 Z = d * %s.zw;\nfloat implicit = dot(Z, d) - 1.0;\nfloat "
                "grad_dot = 4.0 * dot(Z, Z);\ngrad_dot = max(grad_dot, 0.0001);\nfloat approx_dist "
                "= implicit * inversesqrt(grad_dot);\n@if (useScale) {\n    approx_dist *= "
                "%s.x;\n}\nhalf alpha;\n@switch (%d) {\n    case 0:\n        alpha = approx_dist > "
                "0.0 ? 0.0 : 1.0;\n        break;\n    case 1:\n        alph",
                prevRadii.fX,
                prevRadii.fY,
                (useScale ? "true" : "false"),
                args.fUniformHandler->getUniformCStr(fEllipseVar),
                fScaleVar.isValid() ? args.fUniformHandler->getUniformCStr(fScaleVar) : "float2(0)",
                args.fUniformHandler->getUniformCStr(fEllipseVar),
                fScaleVar.isValid() ? args.fUniformHandler->getUniformCStr(fScaleVar) : "float2(0)",
                (int)_outer.edgeType());
        fragBuilder->codeAppendf(
                "a = clamp(0.5 - half(approx_dist), 0.0, 1.0);\n        break;\n    case 2:\n      "
                "  alpha = approx_dist > 0.0 ? 1.0 : 0.0;\n        break;\n    case 3:\n        "
                "alpha = clamp(0.5 + half(approx_dist), 0.0, 1.0);\n        break;\n    default:\n "
                "       discard;\n}\n%s = %s * alpha;\n",
                args.fOutputColor,
                args.fInputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor&      _proc) override {
        const GrEllipseEffect& _outer   = _proc.cast<GrEllipseEffect>();
        auto                   edgeType = _outer.edgeType();
        (void)edgeType;
        auto center = _outer.center();
        (void)center;
        auto radii = _outer.radii();
        (void)radii;
        UniformHandle& ellipse = fEllipseVar;
        (void)ellipse;
        UniformHandle& scale = fScaleVar;
        (void)scale;

        if (radii != prevRadii || center != prevCenter) {
            float invRXSqd;
            float invRYSqd;
            // If we're using a scale factor to work around precision issues, choose the larger
            // radius as the scale factor. The inv radii need to be pre-adjusted by the scale
            // factor.
            if (scale.isValid()) {
                if (radii.fX > radii.fY) {
                    invRXSqd = 1.f;
                    invRYSqd = (radii.fX * radii.fX) / (radii.fY * radii.fY);
                    pdman.set2f(scale, radii.fX, 1.f / radii.fX);
                } else {
                    invRXSqd = (radii.fY * radii.fY) / (radii.fX * radii.fX);
                    invRYSqd = 1.f;
                    pdman.set2f(scale, radii.fY, 1.f / radii.fY);
                }
            } else {
                invRXSqd = 1.f / (radii.fX * radii.fX);
                invRYSqd = 1.f / (radii.fY * radii.fY);
            }
            pdman.set4f(ellipse, center.fX, center.fY, invRXSqd, invRYSqd);
            prevCenter = center;
            prevRadii  = radii;
        }
    }
    SkPoint       prevCenter = float2(0);
    SkPoint       prevRadii  = float2(0);
    bool          useScale   = false;
    UniformHandle fEllipseVar;
    UniformHandle fScaleVar;
};
GrGLSLFragmentProcessor* GrEllipseEffect::onCreateGLSLInstance() const {
    return new GrGLSLEllipseEffect();
}
void GrEllipseEffect::onGetGLSLProcessorKey(const GrShaderCaps&    caps,
                                            GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)fEdgeType);
}
bool GrEllipseEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrEllipseEffect& that = other.cast<GrEllipseEffect>();
    (void)that;
    if (fEdgeType != that.fEdgeType)
        return false;
    if (fCenter != that.fCenter)
        return false;
    if (fRadii != that.fRadii)
        return false;
    return true;
}
GrEllipseEffect::GrEllipseEffect(const GrEllipseEffect& src)
        : INHERITED(kGrEllipseEffect_ClassID, src.optimizationFlags())
        , fEdgeType(src.fEdgeType)
        , fCenter(src.fCenter)
        , fRadii(src.fRadii) {}
std::unique_ptr<GrFragmentProcessor> GrEllipseEffect::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrEllipseEffect(*this));
}
GR_DEFINE_FRAGMENT_PROCESSOR_TEST(GrEllipseEffect);
#if GR_TEST_UTILS
std::unique_ptr<GrFragmentProcessor> GrEllipseEffect::TestCreate(GrProcessorTestData* testData) {
    SkPoint center;
    center.fX         = testData->fRandom->nextRangeScalar(0.f, 1000.f);
    center.fY         = testData->fRandom->nextRangeScalar(0.f, 1000.f);
    SkScalar       rx = testData->fRandom->nextRangeF(0.f, 1000.f);
    SkScalar       ry = testData->fRandom->nextRangeF(0.f, 1000.f);
    GrClipEdgeType et;
    do {
        et = (GrClipEdgeType)testData->fRandom->nextULessThan(kGrClipEdgeTypeCnt);
    } while (GrClipEdgeType::kHairlineAA == et);
    return GrEllipseEffect::Make(
            et, center, SkPoint::Make(rx, ry), *testData->caps()->shaderCaps());
}
#endif
