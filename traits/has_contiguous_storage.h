/*  This file is part of the Vc library. {{{
Copyright © 2014-2015 Matthias Kretz <kretz@kde.org>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_
#define VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_

#include <initializer_list>
#include <memory>

#ifdef _LIBCPP_BEGIN_NAMESPACE_STD
_LIBCPP_BEGIN_NAMESPACE_STD
#else
namespace std
{
#endif
template <typename T, size_t N> struct array;
template <typename T, typename Allocator> class vector;
#ifdef _LIBCPP_END_NAMESPACE_STD
_LIBCPP_END_NAMESPACE_STD
#else
}  // namespace std
#endif

namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{

template <typename T> struct has_contiguous_storage_impl : public std::false_type {};

template <typename T>
struct has_contiguous_storage
    : public has_contiguous_storage_impl<
          typename std::remove_cv<typename std::remove_reference<T>::type>::type>
{
};

// spezializations:
template <typename T> struct has_contiguous_storage_impl<T *> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::unique_ptr<T[]>> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::initializer_list<T>> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<T[N]> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<std::array<T, N>> : public std::true_type {};
template <typename T, typename A> struct has_contiguous_storage_impl<std::vector<T, A>> : public std::true_type {};

}  // namespace Traits
}  // namespace Vc

#endif // VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_
