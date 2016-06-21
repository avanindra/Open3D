// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 Qianyi Zhou <Qianyi.Zhou@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "FloatImage.h"

namespace three{

std::pair<bool, double> FloatImage::ValueAt(double u, double v)
{
	if (u < 0.0 || u > (double)(width_ - 1) || 
			v < 0.0 || v > (double)(height_ - 1)) {
		return std::make_pair(false, 0.0);
	}
	int ui = std::max(std::min((int)u, width_ - 2), 0);
	int vi = std::max(std::min((int)v, height_ - 2), 0);
	double pu = u - ui;
	double pv = v - vi;
	float value[4] = {
		ValueAtUnsafe(ui, vi),
		ValueAtUnsafe(ui, vi + 1),
		ValueAtUnsafe(ui + 1, vi),
		ValueAtUnsafe(ui + 1, vi + 1)
	};
	return std::make_pair(true,
			(value[0] * (1 - pv) + value[1] * pv) * (1 - pu) +
			(value[2] * (1 - pv) + value[3] * pv) * pu);
}

}	// namespace three