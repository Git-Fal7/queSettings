pkgname=queSettings
pkgver=0.1
pkgrel=1
arch=("x86_64")
makedepends=("cmake")
depends=("qt5-base")
url="https://github.com/git-fal7/$pkgname"
source=("$pkgname::git+$url.git")
sha512sums=('SKIP')

build() {
	cd "$pkgname"
	mkdir -p build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
	cd "$pkgname"
	cd build
	make DESTDIR="$pkgdir" install
}
