#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <cstdint>
#include <DirectXMath.h>
#include <d3d11.h>
#include <windows.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

template <typename T, uint32_t N>
constexpr uint32_t count_of(T(&)[N]) { return N; }