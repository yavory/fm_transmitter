/*
    fm_transmitter - use Raspberry Pi as FM transmitter

    Copyright (c) 2019, Marcin Kondej
    All rights reserved.

    See https://github.com/markondej/fm_transmitter

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may be
    used to endorse or promote products derived from this software without specific
    prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
    WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "sample.h"

Sample::Sample(int8_t *data, uint16_t channels, uint16_t bitsPerChannel)
    : value(0)
{
    uint32_t sum = 0;
    int16_t *channelValues = new int16_t[channels];
    int16_t multiplier = bitsPerChannel >> 3;
    for (uint16_t i = 0; i < channels; i++) {
        if (multiplier > 1) {
            channelValues[i] = (data[(i + 1) * multiplier - 1] << 8) | data[(i + 1) * multiplier - 2];
        } else {
            channelValues[i] = ((int16_t)(uint8_t)data[i] - 0x80) << 8;
        }
        sum += channelValues[i];
    }
    value = sum / channels;
    delete[] channelValues;
}

Sample::Sample(const Sample &source)
    : value(source.value)
{
}

Sample &Sample::operator=(const Sample &source)
{
    value = source.value;
    return *this;
}

float Sample::getMonoValue()
{
    return value / 32768.0;
}
