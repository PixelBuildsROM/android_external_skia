/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrTiledGradientEffect.fp; do not modify.
 **************************************************************************************************/
#include "GrTiledGradientEffect.h"
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "GrTexture.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLTiledGradientEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLTiledGradientEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder*     fragBuilder = args.fFragBuilder;
        const GrTiledGradientEffect& _outer      = args.fFp.cast<GrTiledGradientEffect>();
        (void)_outer;
        auto mirror = _outer.mirror();
        (void)mirror;
        auto makePremul = _outer.makePremul();
        (void)makePremul;
        auto colorsAreOpaque = _outer.colorsAreOpaque();
        (void)colorsAreOpaque;
        SkString _child1("_child1");
        this->emitChild(_outer.gradLayout_index(), &_child1, args);
        fragBuilder->codeAppendf(
                "half4 t = %s;\nif (!%s && t.y < 0.0) {\n    %s = half4(0.0);\n} else {\n    @if "
                "(%s) {\n        half t_1 = t.x - 1.0;\n        half tiled_t = (t_1 - 2.0 * "
                "floor(t_1 * 0.5)) - 1.0;\n        if (sk_Caps.mustDoOpBetweenFloorAndAbs) {\n     "
                "       tiled_t = clamp(tiled_t, -1.0, 1.0);\n        }\n        t.x = "
                "abs(tiled_t);\n    } else {\n        t.x = fract(t.x);\n    }",
                _child1.c_str(),
                (_outer.childProcessor(_outer.gradLayout_index()).preservesOpaqueInput() ? "true"
                                                                                         : "false"),
                args.fOutputColor,
                (_outer.mirror() ? "true" : "false"));
        SkString _input0("t");
        SkString _child0("_child0");
        this->emitChild(_outer.colorizer_index(), _input0.c_str(), &_child0, args);
        fragBuilder->codeAppendf("\n    %s = %s;\n}\n@if (%s) {\n    %s.xyz *= %s.w;\n}\n",
                                 args.fOutputColor,
                                 _child0.c_str(),
                                 (_outer.makePremul() ? "true" : "false"),
                                 args.fOutputColor,
                                 args.fOutputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor&      _proc) override {}
};
GrGLSLFragmentProcessor* GrTiledGradientEffect::onCreateGLSLInstance() const {
    return new GrGLSLTiledGradientEffect();
}
void GrTiledGradientEffect::onGetGLSLProcessorKey(const GrShaderCaps&    caps,
                                                  GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)fMirror);
    b->add32((int32_t)fMakePremul);
}
bool GrTiledGradientEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrTiledGradientEffect& that = other.cast<GrTiledGradientEffect>();
    (void)that;
    if (fMirror != that.fMirror)
        return false;
    if (fMakePremul != that.fMakePremul)
        return false;
    if (fColorsAreOpaque != that.fColorsAreOpaque)
        return false;
    return true;
}
GrTiledGradientEffect::GrTiledGradientEffect(const GrTiledGradientEffect& src)
        : INHERITED(kGrTiledGradientEffect_ClassID, src.optimizationFlags())
        , fColorizer_index(src.fColorizer_index)
        , fGradLayout_index(src.fGradLayout_index)
        , fMirror(src.fMirror)
        , fMakePremul(src.fMakePremul)
        , fColorsAreOpaque(src.fColorsAreOpaque) {
    this->registerChildProcessor(src.childProcessor(fColorizer_index).clone());
    this->registerChildProcessor(src.childProcessor(fGradLayout_index).clone());
}
std::unique_ptr<GrFragmentProcessor> GrTiledGradientEffect::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrTiledGradientEffect(*this));
}
