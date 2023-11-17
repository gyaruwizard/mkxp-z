#!/bin/bash -e

apt update
apt install -y pulseaudio libportaudio2 dbus-x11
dbus-launch pulseaudio --start
