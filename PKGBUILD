# Maintainer: AndroGR <aggelostselios777@gmail.com>
# This file is part of NvDialog, licensed under the MIT license.

pkgname=libnvdialog-git
pkgver=0.1.3
pkgrel=58
pkgdesc="Cross-platform library to show window dialogs"
arch=('any')
url="https://github.com/AndroGR/nvdialog/"
license=('MIT')
groups=()
depends=( gtk3 glibc )
makedepends=(
        cmake
        gcc
        ninja
)
optdepends=(
        'xorg: Required for graphical UIs, but left out for Wayland-only applications.'
        'wayland: Alternative to X.org, but not a dependency if X.org is available.'
)
provides=(libnvdialog)
conflicts=()
replaces=(libnvdialog)
backup=()
options=()
install=
changelog=
source=()
noextract=()
md5sums=()

build() {
        echo "Building directory: $(pwd)"
        cd ..
        git clone https://github.com/AndroGR/nvdialog/ --depth=1 && cd nvdialog/
        [[ -d build/ ]] || mkdir build/
        cd build/
        cmake .. -DNVD_USE_GTK4=OFF -DNVD_BUILD_STATIC=OFF -G "Ninja" -DWIN32_TARGET=OFF
        ninja
        echo "Finished building..."
}

package() {
        cd ../build/ && ninja install && echo "Installed successfully."
}