# Server/client example using <sys/socket.h>
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

Open your cmd, go to the directory where you have downloaded the files typing this:

```
cd Documents/Projects/source  for example
```
Now you have to compile them, typing:
```
make server
```
And:
```
make client
```
Or if you prefer you can type:
```
make all
```

## Deployment 📦

Then open two terminals and go to the directory where you have the files compiled.

It's very important to run the server before de client. At the first terminal run the server:
```
./server 8080
```
On the second the client:
```
./client 127.0.0.1 8080
```
When you do this you recieve a message on the server and on the client side saying that it was successfully or not in case of error.
Once connected you can send messages to the host until you type "Exit" to get disconnected.

As you can see the format is ./server port_number and ./client hostname port_number so you can try whatever you want.

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





