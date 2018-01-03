
Debian
====================
This directory contains files used to package bitcoind/bitcoin-qt
for Debian-based Linux systems. If you compile bitcoind/bitcoin-qt yourself, there are some useful files here.

To add URI support and clickable links (coinking:<coinking addres>) for the coinking Core QT wallet

This can be installed for either all users or the current user

### All users

#### Install desktop shortcut
    cd coinking
    sudo desktop-file-validate ./contrib/debian/coinking-qt.desktop # See Note
    sudo cp ./contrib/debian/coinking-qt.desktop /usr/share/applications/
    sudo update-desktop-database

#### Install icon graphics
    sudo cp share/pixmaps/coinking128.png /usr/share/pixmaps/

### Current user

#### Install desktop shortcut
    cd coinking
    sudo desktop-file-validate ./contrib/debian/coinking-qt.desktop # Check paths in coinking-qt.desktop match the installation path usually /usr/local/bin
    sudo cp ./contrib/debian/coinking-qt.desktop ~/.local/share/applications/
    sudo update-desktop-database

#### Install icon graphics
    sudo cp share/pixmaps/coinking128.png /usr/share/pixmaps/


**Note:** If you build yourself, you will either need to modify the paths in
the .desktop file or copy coinking-qt or symlink your coinking-qt binary to `/usr/local/bin`
and copy the `../../share/pixmaps/coinking128.png` to `/usr/share/pixmaps`


KDE
====================
bitcoin-qt.protocol (KDE)