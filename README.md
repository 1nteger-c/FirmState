# FirmState: Bringing Cellular Protocol States to Shannon Baseband Emulation

<p align="center">
<img src="https://img.shields.io/badge/Paper-WiSec%202025-blue.svg" alt="WiSec 2025">
<img src="https://img.shields.io/badge/Target-Samsung%20Shannon-green.svg" alt="Samsung Shannon">
<img src="https://img.shields.io/badge/Protocol-LTE%20RRC%2FNAS-orange.svg" alt="LTE RRC/NAS">
<img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
</p>

**FirmState** is a state-aware methodology that augments Samsung Shannon baseband emulation by integrating cellular protocol state information. 

It can work as add-on plugin of the state-of-the-art baseband emulator [FirmWire](https://github.com/FirmWire/FirmWire) 

## 🎯 Key Features

- **State-Aware Emulation**: Semi-automatically recovers and applies protocol states from physical devices
- **BTL Decoding**: Advanced Back Trace Log decoder supporting 4 different BTL versions

## 🚀 Quick Start

### Prerequisites

- We highly recommend to use the Docker

### Installation

1. **Clone the repository with submodules:**
```bash
git clone --recursive https://github.com/1nteger-c/FirmState.git
cd FirmState
git lfs install 
```

### Basic Usage

- please highly reference the [FirmWire Experiment](https://github.com/FirmWire/ndss22_experiments)

## 📁 Repository Structure

```
FirmState/
├── FirmWire/                 # FirmWire submodule
├── BTL_decoder/
│   ├── src/                  # BTL decoder implementation
│   ├── BTL/                  # BTL log samples
│   └── modem/                # Modem data samples for BTL
├── samples/
│   ├── firmware/             # Sample firmware binaries
│   └── memory_dumps/         # State memory dumps
├── modkit/                   # Additional modkit for FirmWire
└── Evaluations/
    ├── Evaluation_rrc_basic  # Evaluation folder of rrc (basic state)
    ├── Evaluation_rrc_setup  # Evaluation folder of rrc (state setup)
    ├── Evaluation_preaka     # Evaluation folder of rrc (preaka)
    └── Evaluation_postaka    # Evaluation folder of rrc (preaka)
```

## 🔬 BTL Decoder

FirmState includes an advanced BTL (Back Trace Log) decoder that supports multiple Shannon baseband versions:

### Supported BTL Versions
- **Version 1100**: Galaxy Note8 (N950NKOU5DSL1)
- **Version 1200**: Galaxy S10 (G973NKOU7HWD1)
- **Version 1300**: Galaxy S21 (G991NKOU4EWE2)
- **Version 1410**: Galaxy S21 (S921NKSU2AXE4)

Note that it might be different according to the device versions. We only provide one example for each versions.

### Usage
```bash
python ./BTL_decoder/decoder.py ./BTL_decoder/modem/sample.bin_MAIN_40010000 ./BTL_decoder/BTL/sample.btl
```

## 📋 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📖 Citation

If you use FirmState in your research, please cite our paper:

```bibtex
@inproceedings{jeong2025firmstate,
  title={FirmState: Bringing Cellular Protocol States to Shannon Baseband Emulation},
  author={Jeong, Suhwan and Oh, Beomseok and Kim, Kwangmin and Yun, Insu and Kim, Yongdae and Park, CheolJun},
  booktitle={18th ACM Conference on Security and Privacy in Wireless and Mobile Networks (WiSec 2025)},
  year={2025},
  month={June},
  location={Arlington, VA, USA},
  publisher={ACM},
  doi={10.1145/3734477.3734726}
}
```


## 📧 Contact

- **Suhwan Jeong** - shjeong.b@enki.co.kr / korea.1nteger@gmail.com
- **Project Link**: https://github.com/1nteger-c/FirmState

---
