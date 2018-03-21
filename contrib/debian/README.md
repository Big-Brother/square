
Debian
====================
This directory contains files used to package squared/square-qt
for Debian-based Linux systems. If you compile squared/square-qt yourself, there are some useful files here.

## square: URI support ##


square-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install square-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your square-qt binary to `/usr/bin`
and the `../../share/pixmaps/square128.png` to `/usr/share/pixmaps`

square-qt.protocol (KDE)

