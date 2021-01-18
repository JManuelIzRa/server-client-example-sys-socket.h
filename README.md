# Server/client example using <sys-socket.h>
A TCP server/client example using sys/socket.h

## Summary

- [Getting Started](#getting-started)
- [Pre-installation](#pre-installation)
- [Installation](#installation)
- [Deployment](#deployment)
- [Build with](#build-with)
- [License](#license)

## Getting started 🚀

Download the source's folder on your computer.

## Pre-installation 📋

You need make packet to execute the files.

To install it:
```
sudo apt-get update
```
```
sudo apt-get install make
```

## Installation 🔧

Open your cmd, go to the PATH where you have downloaded the files and type make.

```
cd Documents/Projects/source  for example

```
```
make
```

## Deployment 📦

If you want to prove other ports you can, doing that:

```
cd Documents/Projects/source  for example

```
It's very important to run the server before de client. You can run this on the same machine on differents terminals.
```
./server 8080

```
```
./client 127.0.0.1 8080

```
As you can see the format is ./server port_number and ./client hostname port_number

## Build with 🛠️

* [VS Code](https://code.visualstudio.com/) - Code editor used
* [Creative Commons](https://creativecommons.org/) - Used to choose the license

## License 📄

This project is licensed under the [CC0 1.0 Universal](LICENSE.md)
Creative Commons License - see the [LICENSE.md](LICENSE.md) file for
details

## Acknowledgments 📢
* https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
* https://www.binarytides.com/server-client-example-c-sockets-linux/
* https://pubs.opengroup.org/onlinepubs/009696899/basedefs/sys/socket.h.html





