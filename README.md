this is very WIP

#### build instructions
```
sudo pacman -S fmt meson base-devel
git clone https://github.com/treeshateorcs/bathory1.git
cd bathory1
meson builddir --buildtype=release
ninja -C builddir
./builddir/bathory1 144.png 144.qoi
```

#### working conversions

##### from
- [x]  bmp
- [x]  gif
- [x]  jpeg
- [x]  png
- [x]  qoi
- [x]  psd
- [ ]  tga
- [x]  psd

##### to
- [x]  bmp
- [ ]  gif
- [x]  jpeg
- [x]  png
- [x]  qoi
- [x]  tga
- [ ]  psd

the conversions that i've tested are 2 to 5 times faster than the `convert`
command from the imagemagick package

![Screenshot](https://raw.githubusercontent.com/treeshateorcs/bathory1/main/screenshot.jpg)

