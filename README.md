# P-LAN #10 Badge Challenge

## Introduction

This is a challenge coin/electronic badge for P-LAN #10 LAN party. It's a custom PCB designed in KiCad and firmware for an ATTiny402. It runs on 2 x AAA batteries with a voltage booster to provide the ~ 5V needed for the WS2812B LEDs.

The original design was missing reverse polarity protection. I've thrown a diode in on the ground connection to prevent this but I need to look into this more.

The badge has hints to the solution printed on it and if you read the code, you can see how it works.

## Thanks

Thanks to people in the DEFCON 32 Badge Hacking discord for inspiration and everyone in the #BadgeLife community.

## License

The MIT License (MIT)

Copyright (c) 2024 Jessica Smith

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
