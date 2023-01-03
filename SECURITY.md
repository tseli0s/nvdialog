# Security Policy
This file defines the security policy for NvDialog. As NvDialog does not use any libraries to detect stack overflows and use after frees, patches are
done manually on a regular basis (Usually included as a whole under a single release). For the best results, you are advised to always update to the latest version
and abstract NvDialog to a safer "shell" within your project that will do all the checking for you.

## Supported Versions
Only the latest major / minor version of NvDialog is supported when it comes to security releases. Each patch release will focus on fixing 
vulnerabilities of a minor version.

There was an exception for 0.3.0, which received a security update as an attacker could gain access to the application by overflowing a string, causing stack corruption.
However it only received the said update as part of the 0.5.0 upgrade.

| Version | Supported          |
| ------- | ------------------ |
| 0.5.x   | :white_check_mark: |
| 0.3.x   | 〰️                  |
| 0.2.x   | :x:                |
| < 0.2.0 | :x:                |

## Reporting a Vulnerability
If you find a vulnerability, make sure to immediately report it to the [Issues](https://github.com/AndroGR/nvdialog/issues) page so it can be fixed as soon as
possible. Vulnerabilities will usually be prioritized unless they are not threatening (eg. an integer overflow that could cause a segmentation fault can be fixed with a cast), and are expected to be
fixed at most in one to two weeks.
