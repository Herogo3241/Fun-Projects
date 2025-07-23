# 🎧 WAV Audio Steganography Tool (C)

This is a simple command-line **steganography** tool that hides secret messages inside WAV audio files by tweaking the least significant bit (LSB) of each audio sample.


## 📦 Features

✅ Embed a secret text message in a WAV file  
✅ Extract the hidden message back  
✅ Supports variable-length messages (length is stored inside audio)  
✅ Command-line interface for easy usage  


## ⚙️ Requirements

- GCC or any C compiler
- A 16-bit PCM WAV file as input


## 🚀 Build

```bash
gcc embed.c -o embed
gcc extract.c -o extract
````


## 🗂️ Usage

```bash
./embed <input.wav> <output.wav>
./extract <stego.wav>
```



