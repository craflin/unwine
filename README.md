
# unwine

unwine is a front end for PuTTY's `plink` tool to launch a command on localhost. It is intended to be used in Wine to integrate tools from the host system into Wine environment.

# Motivation

This tool is the byproduct of my attempt to run a Windows build slave for Jenkins CI on a Linux server using Wine. Git for Windows crashes in Wine, but unwine allows us to use the Git client of the host system instead.

## Build Instructions

Just build it with CMake using some version of Visual Studio. Other compilers like MinGW might also work...

## Installation

* Install PuTTY in your Wine environment.
* Copy `unwine.exe` into some directory of your Wine environment.
* Create a private key using `puttygen` with the file name `key.ppk` in the same folder.
* Login to localhost using `wine plink -ssh 127.0.0.1` and accept the key.
* Rename `unwine.exe` to the tool you would like to integrate in your Wine environment. (`git.exe` for instance.)
* Add the folder you just used to the `PATH` environment variable in the Wine environment. This can be done by editing `HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\Session Manager\Environment` with `wine regedit`.
* Add the pubic key matching the created private key to the `~/.ssh/authorized_key` file of the host system.

# How Does it Work?

unwine recognizes its file name and it arguments and uses `plink` to launch the same command that was launched in Wine on the host system (in the corresponding working directory). Command arguments that look like a windows paths (starting c:, d:, etc.) are translated to the corresponding path on the host system.


