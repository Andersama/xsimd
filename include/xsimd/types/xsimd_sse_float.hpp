/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XSIMD_SSE_FLOAT_HPP
#define XSIMD_SSE_FLOAT_HPP

#include "xsimd_base.hpp"

namespace xsimd
{

    class vector4fb : public simd_vector_bool<vector4fb>
    {

    public:

        vector4fb();
        explicit vector4fb(bool b);
        vector4fb(bool b0, bool b1, bool b2, bool b3);
        vector4fb(const __m128& rhs);
        vector4fb& operator=(const __m128& rhs);

        operator __m128() const;

    private:

        __m128 m_value;
    };

    vector4fb operator&(const vector4fb& lhs, const vector4fb& rhs);
    vector4fb operator|(const vector4fb& lhs, const vector4fb& rhs);
    vector4fb operator^(const vector4fb& lhs, const vector4fb& rhs);
    vector4fb operator~(const vector4fb& rhs);

    vector4fb operator==(const vector4fb& lhs, const vector4fb& rhs);
    vector4fb operator!=(const vector4fb& lhs, const vector4fb& rhs);

    class vector4f;

    template <>
    struct simd_vector_traits<vector4f>
    {
        using value_type = float;
        using vector_bool = vector4fb;
    };

    class vector4f : public simd_vector<vector4f>
    {

    public:

        vector4f();
        explicit vector4f(float f);
        vector4f(float f0, float f1, float f2, float f3);
        vector4f(const __m128& rhs);
        vector4f& operator=(const __m128& rhs);

        operator __m128() const;

        vector4f& load_aligned(const float* src);
        vector4f& load_unaligned(const float* src);

        void store_aligned(float* dst) const;
        void store_unaligned(float* dst) const;

    private:

        __m128 m_value;
    };

    vector4f operator-(const vector4f& rhs);
    vector4f operator+(const vector4f& lhs, const vector4f& rhs);
    vector4f operator-(const vector4f& lhs, const vector4f& rhs);
    vector4f operator*(const vector4f& lhs, const vector4f& rhs);
    vector4f operator/(const vector4f& lhs, const vector4f& rhs);
    
    vector4fb operator==(const vector4f& lhs, const vector4f& rhs);
    vector4fb operator!=(const vector4f& lhs, const vector4f& rhs);
    vector4fb operator<(const vector4f& lhs, const vector4f& rhs);
    vector4fb operator<=(const vector4f& lhs, const vector4f& rhs);

    vector4f operator&(const vector4f& lhs, const vector4f& rhs);
    vector4f operator|(const vector4f& lhs, const vector4f& rhs);
    vector4f operator^(const vector4f& lhs, const vector4f& rhs);
    vector4f operator~(const vector4f& rhs);

    vector4f min(const vector4f& lhs, const vector4f& rhs);
    vector4f max(const vector4f& lhs, const vector4f& rhs);

    vector4f abs(const vector4f& rhs);

    vector4f fma(const vector4f& x, const vector4f& y, const vector4f& z);

    vector4f sqrt(const vector4f& rhs);

    float hadd(const vector4f& rhs);
    vector4f haddp(const vector4f* row);

    vector4f select(const vector4fb& cond, const vector4f& a, const vector4f& b);


    /******************************
     * vector4fb implementation
     ******************************/

    inline vector4fb::vector4fb()
    {
    }

    inline vector4fb::vector4fb(bool b)
        : m_value(_mm_castsi128_ps(_mm_set1_epi32(-(int)b)))
    {
    }

    inline vector4fb::vector4fb(bool b0, bool b1, bool b2, bool b3)
        : m_value(_mm_castsi128_ps(_mm_setr_epi32(-(int)b0, -(int)b1, -(int)b2, -(int)b3)))
    {
    }

    inline vector4fb::vector4fb(const __m128& rhs)
        : m_value(rhs)
    {
    }

    inline vector4fb& vector4fb::operator=(const __m128& rhs)
    {
        m_value = rhs;
        return *this;
    }

    inline vector4fb::operator __m128() const
    {
        return m_value;
    }

    inline vector4fb operator&(const vector4fb& lhs, const vector4fb& rhs)
    {
        return _mm_and_ps(lhs, rhs);
    }

    inline vector4fb operator|(const vector4fb& lhs, const vector4fb& rhs)
    {
        return _mm_or_ps(lhs, rhs);
    }

    inline vector4fb operator^(const vector4fb& lhs, const vector4fb& rhs)
    {
        return _mm_xor_ps(lhs, rhs);
    }

    inline vector4fb operator~(const vector4fb& rhs)
    {
        return _mm_xor_ps(rhs, _mm_castsi128_ps(_mm_set1_epi32(-1)));
    }

    inline vector4fb operator==(const vector4fb& lhs, const vector4fb& rhs)
    {
        return _mm_cmpeq_ps(lhs, rhs);
    }

    inline vector4fb operator!=(const vector4fb& lhs, const vector4fb& rhs)
    {
        return _mm_cmpneq_ps(lhs, rhs);
    }


    /*****************************
     * vector4f implementation
     *****************************/

    inline vector4f::vector4f()
    {
    }

    inline vector4f::vector4f(float f)
        : m_value(_mm_set1_ps(f))
    {
    }
    
    inline vector4f::vector4f(float f0, float f1, float f2, float f3)
        : m_value(_mm_setr_ps(f0, f1, f2, f3))
    {
    }

    inline vector4f::vector4f(const __m128& rhs)
        : m_value(rhs)
    {
    }

    inline vector4f& vector4f::operator=(const __m128& rhs)
    {
        m_value = rhs;
        return *this;
    }

    inline vector4f::operator __m128() const
    {
        return m_value;
    }

    inline vector4f& vector4f::load_aligned(const float* src)
    {
        m_value = _mm_load_ps(src);
        return *this;
    }

    inline vector4f& vector4f::load_unaligned(const float* src)
    {
        m_value = _mm_loadu_ps(src);
        return *this;
    }

    inline void vector4f::store_aligned(float* dst) const
    {
        _mm_store_ps(dst, m_value);
    }

    inline void vector4f::store_unaligned(float* dst) const
    {
        _mm_storeu_ps(dst, m_value);
    }

    inline vector4f operator-(const vector4f& rhs)
    {
        return _mm_xor_ps(rhs, _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
    }

    inline vector4f operator+(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_add_ps(lhs, rhs);
    }

    inline vector4f operator-(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_sub_ps(lhs, rhs);
    }
    
    inline vector4f operator*(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_mul_ps(lhs, rhs);
    }

    inline vector4f operator/(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_div_ps(lhs, rhs);
    }
    
    inline vector4fb operator==(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_cmpeq_ps(lhs, rhs);
    }

    inline vector4fb operator!=(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_cmpneq_ps(lhs, rhs);
    }

    inline vector4fb operator<(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_cmplt_ps(lhs, rhs);
    }

    inline vector4fb operator<=(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_cmple_ps(lhs, rhs);
    }

    inline vector4f operator&(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_and_ps(lhs, rhs);
    }

    inline vector4f operator|(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_or_ps(lhs, rhs);
    }

    inline vector4f operator^(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_xor_ps(lhs, rhs);
    }

    inline vector4f operator~(const vector4f& rhs)
    {
        return _mm_xor_ps(rhs, _mm_castsi128_ps(_mm_set1_epi32(-1)));
    }

    inline vector4f min(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_min_ps(lhs, rhs);
    }

    inline vector4f max(const vector4f& lhs, const vector4f& rhs)
    {
        return _mm_max_ps(lhs, rhs);
    }

    inline vector4f abs(const vector4f& rhs)
    {
        __m128 sign_mask = _mm_set1_ps(-0.f); // -0.f = 1 << 31
        return _mm_andnot_ps(sign_mask, rhs);
    }

    inline vector4f fma(const vector4f& x, const vector4f& y, const vector4f& z)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_FMA3_VERSION
        return _mm_fmadd_ps(x, y, z);
#else
        return x * y + z;
#endif
    }

    inline vector4f sqrt(const vector4f& rhs)
    {
        return _mm_sqrt_ps(rhs);
    }

    inline float hadd(const vector4f& rhs)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_SSE3_VERSION
        __m128 tmp0 = _mm_hadd_ps(rhs, rhs);
        __m128 tmp1 = _mm_hadd_ps(tmp0, tmp0);
#else
        __m128 tmp0 = _mm_add_ps(rhs, _mm_movehl_ps(rhs, rhs));
        __m128 tmp1 = _mm_add_ss(tmp0, _mm_shuffle_ps(tmp0, tmp0, 1));
#endif
        return _mm_cvtss_f32(tmp1);
    }
    
    inline vector4f haddp(const vector4f* row)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_SSE3_VERSION
        return _mm_hadd_ps(_mm_hadd_ps(row[0], row[1]),
                           _mm_hadd_ps(row[2], row[3]));
#else
        __m128 tmp0 = _mm_unpacklo_ps(row[0], row[1]);
        __m128 tmp1 = _mm_unpackhi_ps(row[0], row[1]);
        __m128 tmp2 = _mm_unpackhi_ps(row[2], row[3]);
        tmp0 = _mm_add_ps(tmp0, tmp1);
        tmp1 = _mm_unpacklo_ps(row[2], row[3]);
        tmp1 = _mm_add_ps(tmp1, tmp2);
        tmp2 = _mm_movehl_ps(tmp1, tmp0);
        tmp0 = _mm_movelh_ps(tmp0, tmp1);
        return _mm_add_ps(tmp0, tmp2);
#endif
    }

    inline vector4f select(const vector4fb& cond, const vector4f& a, const vector4f& b)
    {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_SSE4_1_VERSION
        return _mm_blendv_ps(b, a, cond);
#else
        return _mm_or_ps(_mm_and_ps(cond, a), _mm_andnot_ps(cond, b));
#endif
    }
}

#endif

