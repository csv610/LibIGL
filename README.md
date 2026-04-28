# libigl (Fork with CLI & Documentation)

**Disclaimer:** This repository is a copy of the original [libigl](https://github.com/libigl/libigl) work. **Absolutely no credit is taken for the original library or its mathematical implementations.** The core geometry processing algorithms are the brilliant work of the original libigl contributors.

---

## 🌟 About this Fork
This version of the library has been modified to enhance its accessibility for researchers and undergraduate students. While the core engine remains identical to the original, this repository includes several additive contributions:

### 🛠 Contributions in this version:
1.  **CLI Applications Suite:** A comprehensive set of over 80 Command Line Interface (CLI) applications (located in the `/cli` folder). These allow users to run libigl algorithms (like Ray Tracing, Boolean operations, and Geodesic distances) directly from the terminal without writing C++ code.
2.  **Extended Testing:** Implementation of rigorous build and verification steps to ensure the CLI tools work seamlessly across different platforms.
3.  **Undergraduate User Guide:** A new, book-style documentation (`docs/UserGuide.md`) tailored specifically for students learning Discrete Differential Geometry.
4.  **RandomRotate Utility:** A new utility for applying random transformations to meshes, useful for data augmentation and testing.

---

## 📖 Getting Started
For students and new users, we recommend starting with our new guide:
👉 **[User Guide for Undergraduates](docs/UserGuide.md)**

### Building the CLI Apps
```bash
cmake -B cli/build -S cli -DLIBIGL_GLFW=ON
cmake --build cli/build --parallel 8
```
Executables will be generated in `cli/build/`.

---

## 🔗 Original Work
For the official documentation, tutorials, and the most up-to-date core library, please visit the official libigl pages:
- **Official Repository:** <https://github.com/libigl/libigl>
- **Official Website:** <https://libigl.github.io>

---

## 📝 License
This fork adheres to the original licensing of libigl (MPL2 for the core, and GPL for certain copyleft modules like TetGen and CGAL). Please refer to `LICENSE.MPL2` and `LICENSE.GPL` for details.
