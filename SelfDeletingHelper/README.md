# SelfDeletingHelper
A tiny C experiment that demonstrates how to create a temporary file and spawn a helper program which deletes the temp file and then deletes itself after a short delay. Useful as a simple proof-of-concept for self-cleaning disposable executables. This project was inspired from the concept of quine. **Quines** are programs that doesn't take any input and produces a copy of its own source code.

## Use Cases
- **Installer cleanup:** Run temporary setup tasks and delete leftover helper files automatically.
- **Secure temp data:** Wipe sensitive scratch files after use.
- **One-time scripts:** Execute config tweaks or quick fixes and self-remove.
