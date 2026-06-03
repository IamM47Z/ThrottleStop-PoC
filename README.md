# ThrottleStop-PoC

Proof of Concept for a ThrottleStop driver vulnerability that allows user-mode code to read and write Model-Specific Registers (MSRs) through the `\.\ThrottleStop` device.

## Overview

This repository contains a simple Windows PoC executable that:
- opens a handle to the `ThrottleStop` driver
- issues custom IOCTL requests to read and write the `IA32_DEBUGCTL` MSR
- toggles the `LBR` and `BTF` bits on every logical CPU core

The exploit is implemented in `main.cpp` and `exploit/exploit.cpp`, with driver IOCTL definitions in `includes.h`.

## Disclaimer

This code is provided for security research and educational use only. Do not run it on systems without explicit authorization. Improper use may cause system instability or violate policy.

