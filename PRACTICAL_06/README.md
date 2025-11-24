# Raylib Template Guide <a name="raylib-template-guide"></a>

A guide for creating new projects using the raylib_template repository, which includes raylib_starter as a submodule. This guide walks through the process of setting up a new project while maintaining the benefits of the starter kit's structure and build system.

## Table of Contents

- [Overview](#overview)
- [Initial Setup](#initial-setup)
  - [Repository Setup](#repository-setup)
  - [Remote Configuration](#remote-configuration)
- [Project Structure](#project-structure)
- [Build Configuration](#build-configuration)
- [Maintenance](#maintenance)
- [Resources](#resources)
- [Support](#support)

## Overview <a name="overview"></a>

This guide provides:

- Step-by-step project initialization
- Repository configuration instructions
- Project structure organization
- Build system customization
- Maintenance procedures

## Initial Setup <a name="initial-setup"></a>

### Repository Setup <a name="repository-setup"></a>

1. **Clone Template Repository**
   ```bash
   git clone https://bitbucket.org/MuddyGames/raylib_template.git new_project_name
   cd new_project_name
   ```

2. **Create Remote Repository**
   - Create a new repository on your Git hosting service
   - Name it according to your project (e.g., `my_new_project`)

### Remote Configuration <a name="remote-configuration"></a>

1. **Update Remote URL**
   ```bash
   git remote set-url origin https://bitbucket.org/YourUsername/my_new_project.git
   ```

2. **Initialize Project**
   ```bash
   git push -u origin main
   ```

## Project Structure <a name="project-structure"></a>

Organize your project files within the provided structure:

- Place source files in the `src` directory
- Keep project-specific headers in `include`
- Maintain assets in `resources`
- Configure builds in the root `Makefile`

		```
		new_project/
		├── include/ 
		│   └── game.h           # Game update methods
		├── src/                 # Your project-specific source files
		│   ├── game.c           # Game update implementation
		│   └── main.c           # Main entry point
		├── raylib_starter/      # Submodule containing the starter kit
		├── template/
		│   └── template.html    # Basic index HTML game page template
		├── Makefile             # Project-specific build configuration
		└── README.md            # Project documentation
		```

## Build Configuration <a name="build-configuration"></a>

The template includes a preconfigured Makefile with the following targets:

```bash
# Build all targets (desktop)
make all

# Build desktop version
make build

# Run desktop version
make run

# Build web version
make build_web

# Run web version (starts local server)
make run_web

# Clean build files
make clean

# Clean toolchain files
make clean_toolchain

# Build release (desktop)
make CONFIG=release
```

## Maintenance <a name="maintenance"></a>

### Updating Raylib Starter

To get the latest updates from the starter kit:

```bash
git submodule update --remote raylib_starter
```

### Project Updates

Maintain your project with regular commits:

```bash
git add .
git commit -m "Update project files"
git push origin main
```

## Resources <a name="resources"></a>

- [Raylib Template Repository](https://bitbucket.org/MuddyGames/raylib_template)
- [Raylib Starter Documentation](https://bitbucket.org/MuddyGames/raylib_starter)
- [Git Submodule Documentation](https://git-scm.com/book/en/v2/Git-Tools-Submodules)

## Support <a name="support"></a>

For questions and support, contact:
- MuddyGames

[Back to top](#raylib-template-guide)