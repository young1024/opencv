// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html

// This header is not standalone. Don't include directly, use "intrin.hpp" instead.
#ifdef OPENCV_HAL_INTRIN_HPP  // defined in intrin.hpp

namespace CV__SIMD_NAMESPACE {

/* Universal Intrinsics implementation of sin, cos, exp and log

   Inspired by Intel Approximate Math library, and based on the
   corresponding algorithms of the cephes math library
*/

/* Copyright (C) 2010,2011  RJVB - extensions */
/* Copyright (C) 2011  Julien Pommier

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  (this is the zlib license)
*/

#ifndef OPENCV_HAL_MATH_HAVE_EXP

//! @name Exponential
//! @{
#if defined(CV_SIMD_FP16) && CV_SIMD_FP16
    // Implementation is the same as float32 vector.
    inline v_float16 v_exp(const v_float16 &x) {
        const v_float16 _vexp_lo_f16 = vx_setall_f16(-10.7421875f);
        const v_float16 _vexp_hi_f16 = vx_setall_f16(11.f);
        const v_float16 _vexp_half_fp16 = vx_setall_f16(0.5f);
        const v_float16 _vexp_one_fp16 = vx_setall_f16(1.f);
        const v_float16 _vexp_LOG2EF_f16 = vx_setall_f16(1.44269504088896341f);
        const v_float16 _vexp_C1_f16 = vx_setall_f16(-6.93359375E-1f);
        const v_float16 _vexp_C2_f16 = vx_setall_f16(2.12194440E-4f);
        const v_float16 _vexp_p0_f16 = vx_setall_f16(1.9875691500E-4f);
        const v_float16 _vexp_p1_f16 = vx_setall_f16(1.3981999507E-3f);
        const v_float16 _vexp_p2_f16 = vx_setall_f16(8.3334519073E-3f);
        const v_float16 _vexp_p3_f16 = vx_setall_f16(4.1665795894E-2f);
        const v_float16 _vexp_p4_f16 = vx_setall_f16(1.6666665459E-1f);
        const v_float16 _vexp_p5_f16 = vx_setall_f16(5.0000001201E-1f);
        const v_int16 _vexp_bias_s16 = vx_setall_s16(0xf);

        v_float16 _vexp_, _vexp_x, _vexp_y, _vexp_xx;
        v_int16 _vexp_mm;

        // compute exponential of x
        _vexp_x = v_max(x, _vexp_lo_f16);
        _vexp_x = v_min(_vexp_x, _vexp_hi_f16);

        _vexp_ = v_fma(_vexp_x, _vexp_LOG2EF_f16, _vexp_half_fp16);
        _vexp_mm = v_floor(_vexp_);
        _vexp_ = v_cvt_f16(_vexp_mm);
        _vexp_mm = v_add(_vexp_mm, _vexp_bias_s16);
        _vexp_mm = v_shl(_vexp_mm, 10);

        _vexp_x = v_fma(_vexp_, _vexp_C1_f16, _vexp_x);
        _vexp_x = v_fma(_vexp_, _vexp_C2_f16, _vexp_x);
        _vexp_xx = v_mul(_vexp_x, _vexp_x);

        _vexp_y = v_fma(_vexp_x, _vexp_p0_f16, _vexp_p1_f16);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p2_f16);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p3_f16);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p4_f16);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p5_f16);

        _vexp_y = v_fma(_vexp_y, _vexp_xx, _vexp_x);
        _vexp_y = v_add(_vexp_y, _vexp_one_fp16);
        _vexp_y = v_mul(_vexp_y, v_reinterpret_as_f16(_vexp_mm));

        // exp(NAN) -> NAN
        v_float16 mask_not_nan = v_not_nan(x);
        return v_select(mask_not_nan, _vexp_y, v_reinterpret_as_f16(vx_setall_s16(0x7e00)));
    }
#endif

    inline v_float32 v_exp(const v_float32 &x) {
        const v_float32 _vexp_lo_f32 = vx_setall_f32(-88.3762626647949f);
        const v_float32 _vexp_hi_f32 = vx_setall_f32(89.f);
        const v_float32 _vexp_half_fp32 = vx_setall_f32(0.5f);
        const v_float32 _vexp_one_fp32 = vx_setall_f32(1.f);
        const v_float32 _vexp_LOG2EF_f32 = vx_setall_f32(1.44269504088896341f);
        const v_float32 _vexp_C1_f32 = vx_setall_f32(-6.93359375E-1f);
        const v_float32 _vexp_C2_f32 = vx_setall_f32(2.12194440E-4f);
        const v_float32 _vexp_p0_f32 = vx_setall_f32(1.9875691500E-4f);
        const v_float32 _vexp_p1_f32 = vx_setall_f32(1.3981999507E-3f);
        const v_float32 _vexp_p2_f32 = vx_setall_f32(8.3334519073E-3f);
        const v_float32 _vexp_p3_f32 = vx_setall_f32(4.1665795894E-2f);
        const v_float32 _vexp_p4_f32 = vx_setall_f32(1.6666665459E-1f);
        const v_float32 _vexp_p5_f32 = vx_setall_f32(5.0000001201E-1f);
        const v_int32 _vexp_bias_s32 = vx_setall_s32(0x7f);

        v_float32 _vexp_, _vexp_x, _vexp_y, _vexp_xx;
        v_int32 _vexp_mm;

        // compute exponential of x
        _vexp_x = v_max(x, _vexp_lo_f32);
        _vexp_x = v_min(_vexp_x, _vexp_hi_f32);

        _vexp_ = v_fma(_vexp_x, _vexp_LOG2EF_f32, _vexp_half_fp32);
        _vexp_mm = v_floor(_vexp_);
        _vexp_ = v_cvt_f32(_vexp_mm);
        _vexp_mm = v_add(_vexp_mm, _vexp_bias_s32);
        _vexp_mm = v_shl(_vexp_mm, 23);

        _vexp_x = v_fma(_vexp_, _vexp_C1_f32, _vexp_x);
        _vexp_x = v_fma(_vexp_, _vexp_C2_f32, _vexp_x);
        _vexp_xx = v_mul(_vexp_x, _vexp_x);

        _vexp_y = v_fma(_vexp_x, _vexp_p0_f32, _vexp_p1_f32);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p2_f32);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p3_f32);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p4_f32);
        _vexp_y = v_fma(_vexp_y, _vexp_x, _vexp_p5_f32);

        _vexp_y = v_fma(_vexp_y, _vexp_xx, _vexp_x);
        _vexp_y = v_add(_vexp_y, _vexp_one_fp32);
        _vexp_y = v_mul(_vexp_y, v_reinterpret_as_f32(_vexp_mm));

        // exp(NAN) -> NAN
        v_float32 mask_not_nan = v_not_nan(x);
        return v_select(mask_not_nan, _vexp_y, v_reinterpret_as_f32(vx_setall_s32(0x7fc00000)));
    }

#if CV_SIMD_64F || CV_SIMD_SCALABLE_64F
    inline v_float64 v_exp(const v_float64 &x) {
        const v_float64 _vexp_lo_f64 = vx_setall_f64(-709.43613930310391424428);
        const v_float64 _vexp_hi_f64 = vx_setall_f64(710.);
        const v_float64 _vexp_half_f64 = vx_setall_f64(0.5);
        const v_float64 _vexp_one_f64 = vx_setall_f64(1.0);
        const v_float64 _vexp_two_f64 = vx_setall_f64(2.0);
        const v_float64 _vexp_LOG2EF_f64 = vx_setall_f64(1.44269504088896340736);
        const v_float64 _vexp_C1_f64 = vx_setall_f64(-6.93145751953125E-1);
        const v_float64 _vexp_C2_f64 = vx_setall_f64(-1.42860682030941723212E-6);
        const v_float64 _vexp_p0_f64 = vx_setall_f64(1.26177193074810590878E-4);
        const v_float64 _vexp_p1_f64 = vx_setall_f64(3.02994407707441961300E-2);
        const v_float64 _vexp_p2_f64 = vx_setall_f64(9.99999999999999999910E-1);
        const v_float64 _vexp_q0_f64 = vx_setall_f64(3.00198505138664455042E-6);
        const v_float64 _vexp_q1_f64 = vx_setall_f64(2.52448340349684104192E-3);
        const v_float64 _vexp_q2_f64 = vx_setall_f64(2.27265548208155028766E-1);
        const v_float64 _vexp_q3_f64 = vx_setall_f64(2.00000000000000000009E0);
        const v_int64 _vexp_bias_s64 = vx_setall_s64(0x3ff);

        v_float64 _vexp_, _vexp_x, _vexp_y, _vexp_z, _vexp_xx;
        v_int64 _vexp_mm;

        // compute exponential of x
        _vexp_x = v_max(x, _vexp_lo_f64);
        _vexp_x = v_min(_vexp_x, _vexp_hi_f64);

        _vexp_ = v_fma(_vexp_x, _vexp_LOG2EF_f64, _vexp_half_f64);
        _vexp_mm = v_expand_low(v_floor(_vexp_));
        _vexp_ = v_cvt_f64(_vexp_mm);
        _vexp_mm = v_add(_vexp_mm, _vexp_bias_s64);
        _vexp_mm = v_shl(_vexp_mm, 52);

        _vexp_x = v_fma(_vexp_, _vexp_C1_f64, _vexp_x);
        _vexp_x = v_fma(_vexp_, _vexp_C2_f64, _vexp_x);
        _vexp_xx = v_mul(_vexp_x, _vexp_x);

        _vexp_y = v_fma(_vexp_xx, _vexp_p0_f64, _vexp_p1_f64);
        _vexp_y = v_fma(_vexp_y, _vexp_xx, _vexp_p2_f64);
        _vexp_y = v_mul(_vexp_y, _vexp_x);

        _vexp_z = v_fma(_vexp_xx, _vexp_q0_f64, _vexp_q1_f64);
        _vexp_z = v_fma(_vexp_xx, _vexp_z, _vexp_q2_f64);
        _vexp_z = v_fma(_vexp_xx, _vexp_z, _vexp_q3_f64);

        _vexp_z = v_div(_vexp_y, v_sub(_vexp_z, _vexp_y));
        _vexp_z = v_fma(_vexp_two_f64, _vexp_z, _vexp_one_f64);
        _vexp_z = v_mul(_vexp_z, v_reinterpret_as_f64(_vexp_mm));

        // exp(NAN) -> NAN
        v_float64 mask_not_nan = v_not_nan(x);
        return v_select(mask_not_nan, _vexp_z, v_reinterpret_as_f64(vx_setall_s64(0x7FF8000000000000)));
    }
#endif

#define OPENCV_HAL_MATH_HAVE_EXP 1
//! @}
#endif

#ifndef OPENCV_HAL_MATH_HAVE_LOG

//! @name Natural Logarithm
//! @{
#if defined(CV_SIMD_FP16) && CV_SIMD_FP16
    inline v_float16 v_log(const v_float16 &x) {
        const v_float16 _vlog_one_fp16 = vx_setall_f16(1.0f);
        const v_float16 _vlog_SQRTHF_fp16 = vx_setall_f16(0.707106781186547524f);
        const v_float16 _vlog_q1_fp16 = vx_setall_f16(-2.12194440E-4f);
        const v_float16 _vlog_q2_fp16 = vx_setall_f16(0.693359375f);
        const v_float16 _vlog_p0_fp16 = vx_setall_f16(7.0376836292E-2f);
        const v_float16 _vlog_p1_fp16 = vx_setall_f16(-1.1514610310E-1f);
        const v_float16 _vlog_p2_fp16 = vx_setall_f16(1.1676998740E-1f);
        const v_float16 _vlog_p3_fp16 = vx_setall_f16(-1.2420140846E-1f);
        const v_float16 _vlog_p4_fp16 = vx_setall_f16(1.4249322787E-1f);
        const v_float16 _vlog_p5_fp16 = vx_setall_f16(-1.6668057665E-1f);
        const v_float16 _vlog_p6_fp16 = vx_setall_f16(2.0000714765E-1f);
        const v_float16 _vlog_p7_fp16 = vx_setall_f16(-2.4999993993E-1f);
        const v_float16 _vlog_p8_fp16 = vx_setall_f16(3.3333331174E-1f);
        const v_int16 _vlog_inv_mant_mask_s16 = vx_setall_s16(~0x7c00);

        v_float16 _vlog_x, _vlog_e, _vlog_y, _vlog_z, _vlog_tmp;
        v_int16 _vlog_ux, _vlog_emm0;

        _vlog_ux = v_reinterpret_as_s16(x);
        _vlog_emm0 = v_shr(_vlog_ux, 10);

        _vlog_ux = v_and(_vlog_ux, _vlog_inv_mant_mask_s16);
        _vlog_ux = v_or(_vlog_ux, v_reinterpret_as_s16(vx_setall_f16(0.5f)));
        _vlog_x = v_reinterpret_as_f16(_vlog_ux);

        _vlog_emm0 = v_sub(_vlog_emm0, vx_setall_s16(0xf));
        _vlog_e = v_cvt_f16(_vlog_emm0);

        _vlog_e = v_add(_vlog_e, _vlog_one_fp16);

        v_float16 _vlog_mask = v_lt(_vlog_x, _vlog_SQRTHF_fp16);
        _vlog_tmp = v_and(_vlog_x, _vlog_mask);
        _vlog_x = v_sub(_vlog_x, _vlog_one_fp16);
        _vlog_e = v_sub(_vlog_e, v_and(_vlog_one_fp16, _vlog_mask));
        _vlog_x = v_add(_vlog_x, _vlog_tmp);

        _vlog_z = v_mul(_vlog_x, _vlog_x);

        _vlog_y = v_fma(_vlog_p0_fp16, _vlog_x, _vlog_p1_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p2_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p3_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p4_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p5_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p6_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p7_fp16);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p8_fp16);
        _vlog_y = v_mul(_vlog_y, _vlog_x);
        _vlog_y = v_mul(_vlog_y, _vlog_z);

        _vlog_y = v_fma(_vlog_e, _vlog_q1_fp16, _vlog_y);

        _vlog_y = v_sub(_vlog_y, v_mul(_vlog_z, vx_setall_f16(0.5f)));

        _vlog_x = v_add(_vlog_x, _vlog_y);
        _vlog_x = v_fma(_vlog_e, _vlog_q2_fp16, _vlog_x);
        // log(0) -> -INF
        v_float16 mask_zero = v_eq(x, vx_setzero_f16());
        _vlog_x = v_select(mask_zero, v_reinterpret_as_f16(vx_setall_s16(0xfc00)), _vlog_x);
        // log(NEG), log(NAN) -> NAN
        v_float16 mask_not_nan = v_ge(x, vx_setzero_f16());
        _vlog_x = v_select(mask_not_nan, _vlog_x, v_reinterpret_as_f16(vx_setall_s16(0x7e00)));
        // log(INF) -> INF
        v_float16 mask_inf = v_eq(x, v_reinterpret_as_f16(vx_setall_s16(0x7c00)));
        _vlog_x = v_select(mask_inf, x, _vlog_x);
        return _vlog_x;
    }
#endif

    inline v_float32 v_log(const v_float32 &x) {
        const v_float32 _vlog_one_fp32 = vx_setall_f32(1.0f);
        const v_float32 _vlog_SQRTHF_fp32 = vx_setall_f32(0.707106781186547524f);
        const v_float32 _vlog_q1_fp32 = vx_setall_f32(-2.12194440E-4f);
        const v_float32 _vlog_q2_fp32 = vx_setall_f32(0.693359375f);
        const v_float32 _vlog_p0_fp32 = vx_setall_f32(7.0376836292E-2f);
        const v_float32 _vlog_p1_fp32 = vx_setall_f32(-1.1514610310E-1f);
        const v_float32 _vlog_p2_fp32 = vx_setall_f32(1.1676998740E-1f);
        const v_float32 _vlog_p3_fp32 = vx_setall_f32(-1.2420140846E-1f);
        const v_float32 _vlog_p4_fp32 = vx_setall_f32(1.4249322787E-1f);
        const v_float32 _vlog_p5_fp32 = vx_setall_f32(-1.6668057665E-1f);
        const v_float32 _vlog_p6_fp32 = vx_setall_f32(2.0000714765E-1f);
        const v_float32 _vlog_p7_fp32 = vx_setall_f32(-2.4999993993E-1f);
        const v_float32 _vlog_p8_fp32 = vx_setall_f32(3.3333331174E-1f);
        const v_int32 _vlog_inv_mant_mask_s32 = vx_setall_s32(~0x7f800000);

        v_float32 _vlog_x, _vlog_e, _vlog_y, _vlog_z, _vlog_tmp;
        v_int32 _vlog_ux, _vlog_emm0;

        _vlog_ux = v_reinterpret_as_s32(x);
        _vlog_emm0 = v_shr(_vlog_ux, 23);

        _vlog_ux = v_and(_vlog_ux, _vlog_inv_mant_mask_s32);
        _vlog_ux = v_or(_vlog_ux, v_reinterpret_as_s32(vx_setall_f32(0.5f)));
        _vlog_x = v_reinterpret_as_f32(_vlog_ux);

        _vlog_emm0 = v_sub(_vlog_emm0, vx_setall_s32(0x7f));
        _vlog_e = v_cvt_f32(_vlog_emm0);

        _vlog_e = v_add(_vlog_e, _vlog_one_fp32);

        v_float32 _vlog_mask = v_lt(_vlog_x, _vlog_SQRTHF_fp32);
        _vlog_tmp = v_and(_vlog_x, _vlog_mask);
        _vlog_x = v_sub(_vlog_x, _vlog_one_fp32);
        _vlog_e = v_sub(_vlog_e, v_and(_vlog_one_fp32, _vlog_mask));
        _vlog_x = v_add(_vlog_x, _vlog_tmp);

        _vlog_z = v_mul(_vlog_x, _vlog_x);

        _vlog_y = v_fma(_vlog_p0_fp32, _vlog_x, _vlog_p1_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p2_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p3_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p4_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p5_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p6_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p7_fp32);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p8_fp32);
        _vlog_y = v_mul(_vlog_y, _vlog_x);
        _vlog_y = v_mul(_vlog_y, _vlog_z);

        _vlog_y = v_fma(_vlog_e, _vlog_q1_fp32, _vlog_y);

        _vlog_y = v_sub(_vlog_y, v_mul(_vlog_z, vx_setall_f32(0.5)));

        _vlog_x = v_add(_vlog_x, _vlog_y);
        _vlog_x = v_fma(_vlog_e, _vlog_q2_fp32, _vlog_x);
        // log(0) -> -INF
        v_float32 mask_zero = v_eq(x, vx_setzero_f32());
        _vlog_x = v_select(mask_zero, v_reinterpret_as_f32(vx_setall_s32(0xff800000)), _vlog_x);
        // log(NEG), log(NAN) -> NAN
        v_float32 mask_not_nan = v_ge(x, vx_setzero_f32());
        _vlog_x = v_select(mask_not_nan, _vlog_x, v_reinterpret_as_f32(vx_setall_s32(0x7fc00000)));
        // log(INF) -> INF
        v_float32 mask_inf = v_eq(x, v_reinterpret_as_f32(vx_setall_s32(0x7f800000)));
        _vlog_x = v_select(mask_inf, x, _vlog_x);
        return _vlog_x;
    }

#if CV_SIMD_64F || CV_SIMD_SCALABLE_64F
    inline v_float64 v_log(const v_float64 &x) {
        const v_float64 _vlog_one_fp64 = vx_setall_f64(1.0);
        const v_float64 _vlog_SQRTHF_fp64 = vx_setall_f64(0.7071067811865475244);
        const v_float64 _vlog_p0_fp64 = vx_setall_f64(1.01875663804580931796E-4);
        const v_float64 _vlog_p1_fp64 = vx_setall_f64(4.97494994976747001425E-1);
        const v_float64 _vlog_p2_fp64 = vx_setall_f64(4.70579119878881725854);
        const v_float64 _vlog_p3_fp64 = vx_setall_f64(1.44989225341610930846E1);
        const v_float64 _vlog_p4_fp64 = vx_setall_f64(1.79368678507819816313E1);
        const v_float64 _vlog_p5_fp64 = vx_setall_f64(7.70838733755885391666);
        const v_float64 _vlog_q0_fp64 = vx_setall_f64(1.12873587189167450590E1);
        const v_float64 _vlog_q1_fp64 = vx_setall_f64(4.52279145837532221105E1);
        const v_float64 _vlog_q2_fp64 = vx_setall_f64(8.29875266912776603211E1);
        const v_float64 _vlog_q3_fp64 = vx_setall_f64(7.11544750618563894466E1);
        const v_float64 _vlog_q4_fp64 = vx_setall_f64(2.31251620126765340583E1);

        const v_float64 _vlog_C0_fp64 = vx_setall_f64(2.121944400546905827679e-4);
        const v_float64 _vlog_C1_fp64 = vx_setall_f64(0.693359375);
        const v_int64 _vlog_inv_mant_mask_s64 = vx_setall_s64(~0x7ff0000000000000);

        v_float64 _vlog_x, _vlog_e, _vlog_y, _vlog_z, _vlog_tmp, _vlog_xx;
        v_int64 _vlog_ux, _vlog_emm0;

        _vlog_ux = v_reinterpret_as_s64(x);
        _vlog_emm0 = v_shr(_vlog_ux, 52);

        _vlog_ux = v_and(_vlog_ux, _vlog_inv_mant_mask_s64);
        _vlog_ux = v_or(_vlog_ux, v_reinterpret_as_s64(vx_setall_f64(0.5)));
        _vlog_x = v_reinterpret_as_f64(_vlog_ux);

        _vlog_emm0 = v_sub(_vlog_emm0, vx_setall_s64(0x3ff));
        _vlog_e = v_cvt_f64(_vlog_emm0);

        _vlog_e = v_add(_vlog_e, _vlog_one_fp64);

        v_float64 _vlog_mask = v_lt(_vlog_x, _vlog_SQRTHF_fp64);
        _vlog_tmp = v_and(_vlog_x, _vlog_mask);
        _vlog_x = v_sub(_vlog_x, _vlog_one_fp64);
        _vlog_e = v_sub(_vlog_e, v_and(_vlog_one_fp64, _vlog_mask));
        _vlog_x = v_add(_vlog_x, _vlog_tmp);

        _vlog_xx = v_mul(_vlog_x, _vlog_x);

        _vlog_y = v_fma(_vlog_p0_fp64, _vlog_x, _vlog_p1_fp64);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p2_fp64);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p3_fp64);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p4_fp64);
        _vlog_y = v_fma(_vlog_y, _vlog_x, _vlog_p5_fp64);
        _vlog_y = v_mul(_vlog_y, _vlog_x);
        _vlog_y = v_mul(_vlog_y, _vlog_xx);

        _vlog_z = v_add(_vlog_x, _vlog_q0_fp64);
        _vlog_z = v_fma(_vlog_z, _vlog_x, _vlog_q1_fp64);
        _vlog_z = v_fma(_vlog_z, _vlog_x, _vlog_q2_fp64);
        _vlog_z = v_fma(_vlog_z, _vlog_x, _vlog_q3_fp64);
        _vlog_z = v_fma(_vlog_z, _vlog_x, _vlog_q4_fp64);

        _vlog_z = v_div(_vlog_y, _vlog_z);
        _vlog_z = v_sub(_vlog_z, v_mul(_vlog_e, _vlog_C0_fp64));
        _vlog_z = v_sub(_vlog_z, v_mul(_vlog_xx, vx_setall_f64(0.5)));

        _vlog_z = v_add(_vlog_z, _vlog_x);
        _vlog_z = v_fma(_vlog_e, _vlog_C1_fp64, _vlog_z);

        // log(0) -> -INF
        v_float64 mask_zero = v_eq(x, vx_setzero_f64());
        _vlog_z = v_select(mask_zero, v_reinterpret_as_f64(vx_setall_s64(0xfff0000000000000)), _vlog_z);
        // log(NEG), log(NAN) -> NAN
        v_float64 mask_not_nan = v_ge(x, vx_setzero_f64());
        _vlog_z = v_select(mask_not_nan, _vlog_z, v_reinterpret_as_f64(vx_setall_s64(0x7ff8000000000000)));
        // log(INF) -> INF
        v_float64 mask_inf = v_eq(x, v_reinterpret_as_f64(vx_setall_s64(0x7ff0000000000000)));
        _vlog_z = v_select(mask_inf, x, _vlog_z);
        return _vlog_z;
    }
#endif

#define OPENCV_HAL_MATH_HAVE_LOG 1
//! @}
#endif
}
#endif  // OPENCV_HAL_INTRIN_HPP
